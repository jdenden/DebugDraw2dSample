// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class DebugDraw2dSampleEditorTarget : TargetRules
{
	public DebugDraw2dSampleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "DebugDraw2dSample" } );
	}
}
