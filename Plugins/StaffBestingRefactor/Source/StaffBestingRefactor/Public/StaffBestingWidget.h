#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StaffBestingWidget.generated.h"

UCLASS(BlueprintType)
class STAFFBESTINGREFACTOR_API UStaffBestingWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "StaffBesting")
    void SetOverlayText(const FText& InText) { OverlayText = InText; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaffBesting")
    FText OverlayText = FText::FromString(TEXT("StaffBestingRefactor Overlay"));
};