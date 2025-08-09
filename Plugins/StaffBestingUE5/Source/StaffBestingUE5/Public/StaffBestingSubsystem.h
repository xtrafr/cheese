#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "StaffBestingSubsystem.generated.h"

UCLASS()
class UStaffBestingSubsystem : public UTickableWorldSubsystem
{
    GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UStaffBestingSubsystem, STATGROUP_Tickables); }

private:
    void EnsureInputSetupOnce();
    bool bDidSetupInput = false;
};