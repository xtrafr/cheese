#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaffBestingCameraLibrary.generated.h"

UCLASS()
class STAFFBESTINGREFACTOR_API UStaffBestingCameraLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "StaffBesting|Camera", meta=(WorldContext="WorldContextObject"))
    static bool GetPlayerCameraLocation(const UObject* WorldContextObject, FVector& OutLocation);

    UFUNCTION(BlueprintCallable, Category = "StaffBesting|Camera")
    static bool SetPlayerFOV(APlayerController* PlayerController, float NewFOV);
};