using UnrealBuildTool;

public class StaffBestingRefactor : ModuleRules
{
    public StaffBestingRefactor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "Slate",
            "SlateCore",
            "UMG",
            "InputCore",
            "EnhancedInput"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
        });
    }
}