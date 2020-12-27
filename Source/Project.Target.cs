using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectTarget : TargetRules {
	public ProjectTarget( TargetInfo Target) : base(Target) {
		Type = TargetType.Game;
		ExtraModuleNames.AddRange( new string[] { "Project" } );
	}
}
