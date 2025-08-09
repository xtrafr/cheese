#include "StaffBestingPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "StaffBestingRefactor.h"

AStaffBestingPlayerController::AStaffBestingPlayerController()
{
    bShowMouseCursor = true;
}

void AStaffBestingPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, /*Priority*/ 0);
                UE_LOG(LogStaffBesting, Log, TEXT("Added default input mapping context."));
            }
            else
            {
                UE_LOG(LogStaffBesting, Warning, TEXT("DefaultMappingContext is not set. Input will be limited."));
            }
        }
    }
}

void AStaffBestingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (ToggleOverlayAction)
        {
            EIC->BindAction(ToggleOverlayAction, ETriggerEvent::Started, this, &AStaffBestingPlayerController::OnToggleOverlay);
        }
        else
        {
            UE_LOG(LogStaffBesting, Warning, TEXT("ToggleOverlayAction is not set."));
        }
    }
    else
    {
        UE_LOG(LogStaffBesting, Warning, TEXT("EnhancedInputComponent not found. Ensure Enhanced Input is enabled for this project."));
    }
}

void AStaffBestingPlayerController::OnToggleOverlay(const FInputActionValue& /*Value*/)
{
    // Placeholder for toggling HUD/UMG overlay or feature flags
    UE_LOG(LogStaffBesting, Log, TEXT("ToggleOverlay input received."));
}