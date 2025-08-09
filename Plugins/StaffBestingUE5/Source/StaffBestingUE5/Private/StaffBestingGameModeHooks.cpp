#include "StaffBestingUE5.h"
#include "StaffBestingHUD.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"

static void StaffBesting_SetHUDOnCurrentGameMode(UWorld* World)
{
    if (!World)
    {
        return;
    }

    AGameModeBase* GM = World->GetAuthGameMode();
    if (GM && GM->GetHUDClass() != AStaffBestingHUD::StaticClass())
    {
        GM->HUDClass = AStaffBestingHUD::StaticClass();
        UE_LOG(LogStaffBesting, Log, TEXT("Set HUDClass to AStaffBestingHUD"));
    }
}