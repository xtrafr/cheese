#pragma once
#include "Alignments.h"
#include "decryption.h" 
#include <Windows.h> 
#include <string>
#include <vector>


uint64 BaseAddress = (uint64)GetModuleHandleA(0);
class FNamePool* NamePoolData = nullptr;
#define DecryptWideOffset 0x32D05D0
#define DecryptNonWideOffset 0x32D0560
#define NamePoolDataOffset 0x9095380

static constexpr uint32 FNameMaxBlockBits = 13;
static constexpr uint32 FNameBlockOffsetBits = 16;
static constexpr uint32 FNameMaxBlocks = 1 << FNameMaxBlockBits;
static constexpr uint32 FNameBlockOffsets = 1 << FNameBlockOffsetBits;

struct FNameEntryId
{
	FNameEntryId() : Value(0) {}

	FNameEntryId(uint32 Id) : Value(Id) {}

	explicit operator bool() const { return Value != 0; }

	FORCEINLINE bool operator==(FNameEntryId Other) const
	{
		return Value == Other.Value;
	}

	FORCEINLINE static FNameEntryId FromUnstableInt(uint32 UnstableInt)
	{
		FNameEntryId Id;
		Id.Value = UnstableInt;
		return Id;
	}

	FORCEINLINE uint32 ToUnstableInt() const {
		return Value;
	}

	uint32 Value;
};

struct FNameEntryHandle
{
	uint32 Block = 0;
	uint32 Offset = 0;

	FNameEntryHandle(uint32 InBlock, uint32 InOffset)
		: Block(InBlock)
		, Offset(InOffset)
	{}

	FNameEntryHandle(FNameEntryId Id)
		: Block(Id.ToUnstableInt() >> FNameBlockOffsetBits)
		, Offset(Id.ToUnstableInt()& (FNameBlockOffsets - 1))
	{}

	operator FNameEntryId() const
	{
		return FNameEntryId::FromUnstableInt(Block << FNameBlockOffsetBits | Offset);
	}

	explicit operator bool() const { return Block | Offset; }
};

struct FNameEntryHeader
{
	uint16 bIsWide : 1;
	uint16 Len : 15;
};

struct FNameEntry {
	enum { NAME_SIZE = 1024 };
public:
	FORCEINLINE bool IsWide() const
	{
		return Header.bIsWide;
	}

	FORCEINLINE int32 GetNameLength() const
	{
		return Header.Len;
	}

	FORCEINLINE FNameEntryHeader GetEntryHeader() const
	{
		return Header;
	}

	static int32 GetSize(int32 Length, bool bIsPureAnsi);

	// Return owned decrypted strings to avoid returning stack buffers
	std::string DecryptNonWide();
	std::wstring DecryptWide();

	FORCEINLINE void CopyUnterminatedName(ANSICHAR* Out)
	{
		if (!IsWide())
		{
			auto s = DecryptNonWide();
			const size_t len = std::min(static_cast<size_t>(Header.Len), s.size());
			memcpy(Out, s.data(), sizeof(ANSICHAR) * len);
		}
	}

	FORCEINLINE void CopyUnterminatedName(WIDECHAR* Out)
	{
		if (IsWide())
		{
			auto ws = DecryptWide();
			const size_t len = std::min(static_cast<size_t>(Header.Len), ws.size());
			memcpy(Out, ws.data(), sizeof(WIDECHAR) * len);
		}
	}

	FORCEINLINE static int32 GetDataOffset()
	{
		return offsetof(FNameEntry, AnsiName);
	}

	void GetAnsiName(ANSICHAR(&Out)[NAME_SIZE]);

	void GetWideName(WIDECHAR(&Out)[NAME_SIZE]);

	std::wstring Wchar();

	std::string String();

	FNameEntryId ComparisonId;

	FNameEntryHeader Header;

	union
	{
		ANSICHAR	AnsiName[NAME_SIZE];
		WIDECHAR	WideName[NAME_SIZE];
	};

};

void FNameEntry::GetAnsiName(ANSICHAR(&Out)[NAME_SIZE])
{
	if (!IsWide())
	{
		CopyUnterminatedName(Out);
		Out[Header.Len] = '\0';
	}
}

void FNameEntry::GetWideName(WIDECHAR(&Out)[NAME_SIZE])
{
	if (IsWide())
	{
		CopyUnterminatedName(Out);
		Out[Header.Len] = '\0';
	}
}

class FNameEntryAllocator
{
public:
	enum { Stride = alignof(FNameEntry) };
	enum { BlockSizeBytes = Stride * FNameBlockOffsets };

	void* FRWLock;
	uint32 CurrentBlock = 0;
	uint32 CurrentByteCursor = 0;
	uint8* Blocks[FNameMaxBlocks] = {};

	FORCEINLINE uint32 NumBlocks() const
	{
		return CurrentBlock + 1;
	}

	FORCEINLINE FNameEntry& Resolve(FNameEntryHandle Handle) const
	{
		const bool blockValid = Handle.Block < NumBlocks();
		const bool offsetValid = Handle.Offset < FNameBlockOffsets;
		if (!blockValid || !offsetValid || Blocks[Handle.Block] == nullptr)
		{
			static FNameEntry Dummy{};
			Dummy.Header.bIsWide = 0;
			Dummy.Header.Len = 0;
			return Dummy;
		}
		return *reinterpret_cast<FNameEntry*>(Blocks[Handle.Block] + Stride * Handle.Offset);
	}

};

std::wstring FNameEntry::DecryptWide()
{
	auto _DecryptWideEntry = (__int64(__fastcall*)(FNameEntry* Entry, wchar_t* Buffer))(BaseAddress + DecryptWideOffset);
	wchar_t Buffer[NAME_SIZE]{};
	(void)_DecryptWideEntry(this, Buffer);
	return std::wstring(Buffer, Header.Len);
}

std::string FNameEntry::DecryptNonWide()
{
	auto _DecryptNonWideEntry = (__int64(__fastcall*)(FNameEntry* Entry, char* Buffer))(BaseAddress + DecryptNonWideOffset);
	char Buffer[NAME_SIZE]{};
	(void)_DecryptNonWideEntry(this, Buffer);
	return std::string(Buffer, Header.Len);
}

std::string FNameEntry::String()
{
	if (IsWide()) {
		auto Wide = DecryptWide();
		return std::string(Wide.begin(), Wide.end());
	}

	auto Narrow = DecryptNonWide();
	return Narrow;
}

std::wstring FNameEntry::Wchar()
{
	if (IsWide())
		return DecryptWide();
	else
		return std::wstring();
}

int32 FNameEntry::GetSize(int32 Length, bool bIsPureAnsi)
{
	int32 Bytes = GetDataOffset() + Length * (bIsPureAnsi ? sizeof(ANSICHAR) : sizeof(WIDECHAR));
	return Align(Bytes, alignof(FNameEntry));
}


class FNamePool
{
public:
	enum { MaxENames = 512 };
	FNameEntryAllocator Entries;
	/*
	* Not interested in other members.
	*/
};

struct FName {
	FNameEntryId	ComparisonIndex;

	FNameEntryId	DisplayIndex;

	uint32			Number;

	FORCEINLINE FNameEntryId GetComparisonIndex() const
	{
		return ComparisonIndex;
	}

	FORCEINLINE FNameEntryId GetDisplayIndex() const
	{
		return DisplayIndex;
	}

	FORCEINLINE bool operator==(FName Other) const
	{
		return (ComparisonIndex == Other.ComparisonIndex) && (GetNumber() == Other.GetNumber());
	}

	FORCEINLINE bool operator!=(FName Other) const
	{
		return !(*this == Other);
	}

	FORCEINLINE int32 GetNumber() const
	{
		return Number;
	}

	FName() :
		ComparisonIndex(FNameEntryId()),
		Number(0)
	{ }

	FName(int32 i, int32 n = 0) :
		ComparisonIndex(FNameEntryId(i)),
		Number(n)
	{ }

	const FNameEntry* GetDisplayNameEntry() const;

	std::string GetName();
};

const FNameEntry* FName::GetDisplayNameEntry() const
{
	return &NamePoolData->Entries.Resolve(GetDisplayIndex());
}

std::string FName::GetName()
{
	FNameEntry Entry = NamePoolData->Entries.Resolve(GetDisplayIndex());

	std::string Name = Entry.String();

	if (Number > 0) Name += '_' + std::to_string(Number);

	std::size_t Pos = Name.rfind('/');

	if (Pos != std::string::npos) Name = Name.substr(Pos + 1);

	return Name;
}