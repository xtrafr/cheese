#include "StaffBestingUE5.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogStaffBesting);

class FStaffBestingUE5ModuleImpl : public FStaffBestingUE5Module
{
public:
    virtual void StartupModule() override
    {
        UE_LOG(LogStaffBesting, Log, TEXT("StaffBestingUE5 module starting"));
    }

    virtual void ShutdownModule() override
    {
        UE_LOG(LogStaffBesting, Log, TEXT("StaffBestingUE5 module shutting down"));
    }
};

IMPLEMENT_MODULE(FStaffBestingUE5ModuleImpl, StaffBestingUE5)