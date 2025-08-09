#include "StaffBestingHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"

void AStaffBestingHUD::DrawHUD()
{
    Super::DrawHUD();

    if (Canvas)
    {
        const FVector2D ScreenCenter(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
        FLinearColor Color = FLinearColor::White;
        const FString Msg = TEXT("StaffBestingUE5 HUD (legal Canvas draw)");
        FVector2D TextSize;
        GetTextSize(Msg, TextSize.X, TextSize.Y, GEngine->GetMediumFont());
        DrawText(Msg, Color, ScreenCenter.X - TextSize.X * 0.5f, 30.0f, GEngine->GetMediumFont());
    }
}