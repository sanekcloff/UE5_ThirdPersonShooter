// Shoot Them Up Game. All Rights Reserved.,

using UnrealBuildTool;
using System.Collections.Generic;

public class ShooThemUpTarget : TargetRules
{
    public ShooThemUpTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;

        ExtraModuleNames.AddRange(new string[] { "ShooThemUp" });
    }
}
