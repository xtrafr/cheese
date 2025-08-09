#include "StaffBestingHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

void AStaffBestingHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!Canvas)
    {
        return;
    }

    DrawSampleOverlay();
}

void AStaffBestingHUD::DrawSampleOverlay()
{
    const float StartX = 50.0f;
    const float StartY = 50.0f;

    DrawLine(StartX, StartY, StartX + 200.0f, StartY, FLinearColor::Red);

    UFont* Font = GEngine ? GEngine->GetSmallFont() : nullptr;
    if (Font)
    {
        const FString Message = TEXT("StaffBestingRefactor HUD (UE5)");
        const FColor Color = FColor::White;
        DrawText(Message, Color, StartX, StartY + 10.0f, Font, 1.0f, false);
    }
}