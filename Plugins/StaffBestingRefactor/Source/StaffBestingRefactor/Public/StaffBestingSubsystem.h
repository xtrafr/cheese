#pragma once

#include "CoreMinimal.h"
#include "Subsystems/TickableGameInstanceSubsystem.h"
#include <atomic>
#include "StaffBestingSubsystem.generated.h"

UCLASS()
class STAFFBESTINGREFACTOR_API UStaffBestingSubsystem : public UTickableGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    virtual void Tick(float DeltaTime) override;
    virtual TStatId GetStatId() const override;

    virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Conditional; }
    virtual bool IsTickable() const override { return bIsEnabled; }

    void SetEnabled(bool bEnable);

private:
    std::atomic<bool> bIsEnabled{true};
};