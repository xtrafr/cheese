#include "StaffBestingSubsystem.h"
#include "StaffBestingUE5.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"

void UStaffBestingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    UE_LOG(LogStaffBesting, Log, TEXT("UStaffBestingSubsystem::Initialize"));
}

void UStaffBestingSubsystem::Deinitialize()
{
    UE_LOG(LogStaffBesting, Log, TEXT("UStaffBestingSubsystem::Deinitialize"));
}

void UStaffBestingSubsystem::Tick(float DeltaTime)
{
    EnsureInputSetupOnce();
}

void UStaffBestingSubsystem::EnsureInputSetupOnce()
{
    if (bDidSetupInput)
    {
        return;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    APlayerController* PC = World->GetFirstPlayerController();
    if (!PC)
    {
        return;
    }

    ULocalPlayer* LP = PC->GetLocalPlayer();
    if (!LP)
    {
        return;
    }

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
    {
        // If you have a mapping context asset, load it via soft ref path and add here
        // For now we just validate subsystem presence and mark setup complete
        UE_LOG(LogStaffBesting, Log, TEXT("Enhanced Input subsystem present for local player"));
        bDidSetupInput = true;
    }
}