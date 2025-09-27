class CfgPatches
{
	class R22R_Base_Fortifications_Reloaded
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Camping",
			"DZ_Gear_Containers",
			"DZ_Gear_Crafting"
		};
	};
};
class CfgMods
{
	class R22R_Base_Fortifications_Reloaded
	{
		dir="R22R_Base_Fortifications_Reloaded";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="R22R_Base_Fortifications_Reloaded";
		author="[R22R]Stern & CanadianSniper";
		authorID="";
		version="0.1";
		extra=0;
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		type="mod";
		inputs="R22R_Base_Fortifications_Reloaded\inputs\inputs.xml";
		class defs
		{
			class imageSets
			{
				files[]=
				{
					"R22R_Base_Fortifications_Reloaded/gui/R22R_Lumber.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"R22R_Base_Fortifications_Reloaded/scripts/3_game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"R22R_Base_Fortifications_Reloaded/scripts/4_world"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"R22R_Base_Fortifications_Reloaded/scripts/5_mission"
				};
			};
		};
	};
};
