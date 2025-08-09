## StaffBesting UE5 Plugin (Legal Rendering + Input)

- Purpose: Replace legacy offset-based DLL hooks with a proper UE5 runtime plugin using public APIs only.
- Rendering: Uses AHUD::DrawHUD via `AStaffBestingHUD`.
- Input: Uses Enhanced Input via `UEnhancedInputLocalPlayerSubsystem` in a `UStaffBestingSubsystem`.
- No internals: No VMT swapping, VEH, memory pokes, or name pool access.
- Platforms: Cross-platform UE5. Avoids Windows-only dependencies.

Quick start
- Enable the plugin in your UE5 project.
- Set your GameMode HUDClass to `AStaffBestingHUD` or call a helper from code to set it at runtime.
- Add your own Input Mapping Context and actions; use the subsystem to inject contexts at BeginPlay.

Diagnostics
- Logging category: `LogStaffBesting`.

Testing
- Add unit tests for math (FRotator/FQuat/FTransform) in your project tests.

Security/Ethics
- This plugin is designed for lawful, internal visualization and input prototyping only.
- It removes all hooking or exploit patterns and fails closed on unsupported engine versions.