#pragma once
#include <cstdint>
namespace Hook
{
	void VMT(void* addr, void* pDes, int index, void** ret)
	{
		auto vtable = *(uintptr_t**)addr;
		int methods = 0;
		// Count entries
		while (vtable[methods]) { ++methods; }

		// Allocate a new vtable copy (methods entries)
		auto vtable_copy = new uint64_t[methods];
		for (int i = 0; i < methods; ++i) {
			vtable_copy[i] = vtable[i];
		}

		// Save original and replace
		if (ret) { *ret = (void*)vtable[index]; }
		vtable_copy[index] = (uintptr_t)pDes;
		*(uint64_t**)addr = vtable_copy;
	}

	void vhook(void* addr, void* pDes, int index, void** ret) {
		auto vtable = Memory::ReadStub<uintptr_t*>(std::uintptr_t(addr));
		int methods = 0;
		while (Memory::ReadStub<uintptr_t>((uintptr_t)vtable + (methods * 0x8))) { ++methods; }

		auto vtable_copy = new uint64_t[methods];
		for (int i = 0; i < methods; ++i) {
			vtable_copy[i] = Memory::ReadStub<uintptr_t>((uintptr_t)vtable + (i * 0x8));
		}

		if (ret) { *ret = (void*)vtable[index]; }
		vtable_copy[index] = (uintptr_t)pDes;
		*(uint64_t**)(std::uintptr_t(addr)) = vtable_copy;
	}
}