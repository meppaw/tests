modded class PluginRecipesManagerBase extends PluginBase
{	
	override void RegisterRecipies()
	{
		super.RegisterRecipies();
		
		RegisterRecipe(new ConstructR22RPalisadeWallKit);
		RegisterRecipe(new ConstructR22RWatchtowerKit);
		RegisterRecipe(new ConstructR22RHalfwallKit);
		RegisterRecipe(new ConstructR22RPalisadeGateKit2);
		RegisterRecipe(new ConstructR22RBarricadeXKit);
		RegisterRecipe(new ConstructR22RCampTentKit);
		RegisterRecipe(new ConstructR22RBasicWallKit);
		RegisterRecipe(new ConstructR22RBasicHalfWallKit);
		RegisterRecipe(new ConstructR22RSingleDoorKit);

		RegisterRecipe(new DestroyR22RSharpLog);

		RegisterRecipe(new CraftR22RSharpenWoodenLog);
		RegisterRecipe(new CraftR22R_Lumber);
		RegisterRecipe(new CraftBBS_SmallCrateKit);
		RegisterRecipe(new CraftBBS_LargeCrateKit);
		RegisterRecipe(new CraftBBS_PlankStorageKit);
		RegisterRecipe(new CraftBBS_WoodenlogStorageKit);
		RegisterRecipe(new CraftBBS_LumberStorageKit);
		RegisterRecipe(new CraftR22RHescoBarrierKit);
		RegisterRecipe(new CraftR22RStandaloneStaircaseBlueprint);
		RegisterRecipe(new CraftR22RStandaloneWalkwayBlueprint);
		RegisterRecipe(new CraftR22RSlumShelter1Blueprint);
	}
};