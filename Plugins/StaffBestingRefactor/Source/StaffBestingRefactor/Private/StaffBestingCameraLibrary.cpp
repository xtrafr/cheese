#include "StaffBestingCameraLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"

bool UStaffBestingCameraLibrary::GetPlayerCameraLocation(const UObject* WorldContextObject, FVector& OutLocation)
{
    OutLocation = FVector::ZeroVector;

    if (!WorldContextObject)
    {
        return false;
    }

    const UWorld* World = WorldContextObject->GetWorld();
    if (!World)
    {
        return false;
    }

    APlayerController* PC = World->GetFirstPlayerController();
    if (!PC)
    {
        return false;
    }

    APlayerCameraManager* PCM = PC->PlayerCameraManager;
    if (!PCM)
    {
        return false;
    }

    OutLocation = PCM->GetCameraLocation();
    return true;
}

bool UStaffBestingCameraLibrary::SetPlayerFOV(APlayerController* PlayerController, float NewFOV)
{
    if (!PlayerController)
    {
        return false;
    }

    if (APlayerCameraManager* PCM = PlayerController->PlayerCameraManager)
    {
        PCM->SetFOV(NewFOV);
        return true;
    }

    return false;
}