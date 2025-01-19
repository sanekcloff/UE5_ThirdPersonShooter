// Shoot Them Up Game. All Rights Reserved.,

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooThemUpEditorTarget : TargetRules
{
	public ShooThemUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "ShooThemUp" } );
	}
}
