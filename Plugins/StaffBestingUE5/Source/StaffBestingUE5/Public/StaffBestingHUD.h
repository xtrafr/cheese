#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StaffBestingHUD.generated.h"

UCLASS()
class AStaffBestingHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void DrawHUD() override;
};