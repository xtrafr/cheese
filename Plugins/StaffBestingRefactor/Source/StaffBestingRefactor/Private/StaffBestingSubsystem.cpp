#include "StaffBestingSubsystem.h"
#include "StaffBestingRefactor.h"
#include <atomic>
#include "HAL/IConsoleManager.h"

void UStaffBestingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogStaffBesting, Log, TEXT("StaffBestingSubsystem initialized."));
}

void UStaffBestingSubsystem::Deinitialize()
{
    UE_LOG(LogStaffBesting, Log, TEXT("StaffBestingSubsystem deinitialized."));
    Super::Deinitialize();
}

void UStaffBestingSubsystem::Tick(float DeltaTime)
{
    IConsoleVariable* EnabledCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("StaffBesting.Enabled"));
    const bool bCVarEnabled = EnabledCVar ? (EnabledCVar->GetInt() != 0) : true;
    if (!bCVarEnabled)
    {
        return;
    }

    // Perform safe per-frame work here (no memory pokes, no hooks)
}

TStatId UStaffBestingSubsystem::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(UStaffBestingSubsystem, STATGROUP_Tickables);
}

void UStaffBestingSubsystem::SetEnabled(bool bEnable)
{
    bIsEnabled.store(bEnable, std::memory_order_relaxed);
}