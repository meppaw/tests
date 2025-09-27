class CraftR22RSharpenWoodenLog extends RecipeBase
{	
	override void Init()
	{

		int SPIKED_LOGS_AMOUNT = Math.RandomIntInclusive(1, 2);

		m_Name = "Craft Sharpened Wooden Logs";
		m_IsInstaRecipe = false;						// should this recipe be performed instantly without animation
		m_AnimationLength = 2;							// animation length in relative time units
	
		//conditions	
		m_MinDamageIngredient[0]		= -1;			// -1 = disable check
		m_MaxDamageIngredient[0]		= 3;			// -1 = disable check
		m_MinQuantityIngredient[0]		= -1;			// -1 = disable check
		m_MaxQuantityIngredient[0]		= -1;			// -1 = disable check
	
		m_MinDamageIngredient[1]		= -1;
		m_MaxDamageIngredient[1]		= 3;
		m_MinQuantityIngredient[1]		= -1;
		m_MaxQuantityIngredient[1]		= -1;

		//----------------------------------------------------------------------------------------------------------------------
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"WoodenLog");				// you can insert multiple ingredients this way

		m_IngredientAddHealth[0]		= 0;			// 0 = do nothing
		m_IngredientSetHealth[0]		= -1;			// -1 = do nothing
		m_IngredientAddQuantity[0]		= 0;			// 0 = do nothing
		m_IngredientDestroy[0]			= true;		// true = destroy, false = do nothing

		//ingredient 2
		InsertIngredientEx(1,"Hacksaw"  , 		 "FirewoodSplit_Saw");
		InsertIngredientEx(1,"HandSaw"  , 		 "FirewoodSplit_Saw");
		InsertIngredientEx(1,"Pickaxe"  , 		 "FirewoodSplit_Axe");
		InsertIngredientEx(1,"WoodAxe"  , 		 "FirewoodSplit_Axe");
		InsertIngredientEx(1,"Hatchet"  ,  		 "FirewoodSplit_Axe");
		InsertIngredientEx(1,"FirefighterAxe" ,  "FirewoodSplit_Axe");

		m_IngredientAddHealth[1]		= -2;
		m_IngredientSetHealth[1]		= -1;
		m_IngredientAddQuantity[1]		= 0;
		m_IngredientDestroy[1]			= false;

		//----------------------------------------------------------------------------------------------------------------------
		//RESULTS
		//result1
		AddResult("R22R_Spiked_WoodenLog");							// add results here

		m_ResultSetFullQuantity[0]		= false;		// true = set full quantity, false = do nothing
		m_ResultSetQuantity[0]			= SPIKED_LOGS_AMOUNT;			// -1 = do nothing
		m_ResultSetHealth[0]			= -1;			// -1 = do nothing
		m_ResultInheritsHealth[0]		= 0;			// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0]		= -1;			// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0]			= -2;			// (value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultReplacesIngredient[0]	= -1;			// (value) == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}

	//final check for recipe's validity
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return true;
	}

	//gets called upon recipe's completion
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)
	{
	}

	override void SpawnItems(ItemBase ingredients[], PlayerBase player, array<ItemBase> spawned_objects/*out*/)
	{
		EntityAI woodenlog = ingredients[0];
		EntityAI cuttingTool = ingredients[1];
		float cuttingToolHealth = cuttingTool.GetHealth01();

		// Call the parent SpawnItems function to maintain any inherited behavior
		super.SpawnItems(ingredients, player, spawned_objects);

		// Ensure wooden log is valid before proceeding
		if (woodenlog)
		{   
			int randomLogsAmount = 1;

			// Adjust quantity based on cutting tool health
			if (cuttingToolHealth >= 0.66)
			{
				randomLogsAmount = Math.RandomIntInclusive(1, 3);
			}
			else if (cuttingToolHealth >= 0.45)
			{
				randomLogsAmount = Math.RandomIntInclusive(1, 2);
			}
			else
			{
				return;
			}

			if( randomLogsAmount != 0 )
			{
				ItemBase spikedLogs = ItemBase.Cast(player.SpawnEntityOnGroundOnCursorDir("R22R_Spiked_WoodenLog", DEFAULT_SPAWN_DISTANCE));
				MiscGameplayFunctions.TransferItemProperties(cuttingTool, spikedLogs);
				spikedLogs.SetQuantity(randomLogsAmount);
			}
		}
	}
};
