#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StaffBestingHUD.generated.h"

UCLASS()
class STAFFBESTINGREFACTOR_API AStaffBestingHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

private:
    void DrawSampleOverlay();
};