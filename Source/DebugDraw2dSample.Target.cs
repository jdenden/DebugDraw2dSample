// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class DebugDraw2dSampleTarget : TargetRules
{
	public DebugDraw2dSampleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "DebugDraw2dSample" } );
	}
}
