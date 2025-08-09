#include "StaffBestingRefactor.h"
#include "Modules/ModuleManager.h"
#include "HAL/IConsoleManager.h"

DEFINE_LOG_CATEGORY(LogStaffBesting);

#if (ENGINE_MAJOR_VERSION < 5)
#error StaffBestingRefactor requires Unreal Engine 5 or newer.
#endif

static TAutoConsoleVariable<int32> CVarStaffBestingEnabled(
    TEXT("StaffBesting.Enabled"),
    1,
    TEXT("Enable/disable StaffBestingRefactor features at runtime (0 = off, 1 = on)"),
    ECVF_Default);

void FStaffBestingRefactorModule::StartupModule()
{
    UE_LOG(LogStaffBesting, Log, TEXT("StaffBestingRefactor module starting (UE %d.%d)."), ENGINE_MAJOR_VERSION, ENGINE_MINOR_VERSION);
}

void FStaffBestingRefactorModule::ShutdownModule()
{
    UE_LOG(LogStaffBesting, Log, TEXT("StaffBestingRefactor module shutting down."));
}

IMPLEMENT_MODULE(FStaffBestingRefactorModule, StaffBestingRefactor)