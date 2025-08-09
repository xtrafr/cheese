# StaffBesting UE5 Refactor

This repository now contains a clean Unreal Engine 5 plugin that replaces the legacy offset/hooking approach with supported UE APIs.

Highlights:
- UE5 module-based plugin (no DLL injection, no VMT swaps, no memory patching)
- Rendering via `AHUD::DrawHUD` and UMG widgets
- Input via Enhanced Input (mapping contexts and input actions)
- Safe per-frame logic in a `UTickableGameInstanceSubsystem`
- Logging with `UE_LOG(LogStaffBesting, ...)` and runtime guards

Structure:
- `Plugins/StaffBestingRefactor/` – UE5 plugin
  - `Source/StaffBestingRefactor/`
    - `Public/` `Private/` C++ sources
    - `AStaffBestingHUD` – draws overlay via `Canvas`
    - `AStaffBestingPlayerController` – sets up Enhanced Input
    - `UStaffBestingSubsystem` – tickable per-frame logic
    - `UStaffBestingWidget` – sample UMG widget

Build requirements:
- Unreal Engine 5.3+
- Enable the Enhanced Input plugin in your project

Usage:
1) Copy `Plugins/StaffBestingRefactor` into your UE5 project.
2) Regenerate project files and compile.
3) Set your GameMode to use `AStaffBestingHUD` and `AStaffBestingPlayerController`.
4) Provide a `UInputMappingContext` and `UInputAction` assets and assign to the controller.

Removed (legacy):
- Hardcoded offsets and function pointers
- VMT hooks and VEH-based memory readers/writers
- Access to internal name pools and engine internals
- Windows-only DirectX/Detours dependencies

Security/ethics:
- This code uses only public UE5 APIs and is suitable for real UE projects.

Testing:
- Add Automation Tests to validate math (`FRotator`/`FQuat`/`FTransform`) and rendering if needed.