// Shoot Them Up Game. All Rights Reserved.,

using UnrealBuildTool;

public class ShooThemUp : ModuleRules
{
	public ShooThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
            "Niagara",
			"PhysicsCore",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{ 
			"ShooThemUp/Public/Player", 
			"ShooThemUp/Public/Components", 
			"ShooThemUp/Public/Dev",
			"ShooThemUp/Public/Weapon",
			"ShooThemUp/Public/Weapon/Components",
			"ShooThemUp/Public/UI",
			"ShooThemUp/Public/Pickups",
			"ShooThemUp/Public/AI",
			"ShooThemUp/Public/AI/Tasks",
			"ShooThemUp/Public/AI/Services",
			"ShooThemUp/Public/AI/EQS",
			"ShooThemUp/Public/AI/Decorators",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
