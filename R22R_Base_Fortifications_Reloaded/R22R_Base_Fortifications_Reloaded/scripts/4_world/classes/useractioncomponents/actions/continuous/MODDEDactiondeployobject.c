
modded class ActionDeployObject
{
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		super.ActionCondition(player, target, item)

		if( player.IsInNoBuildZone())
		{
			Print( "[R22R ActionDeployObject] -> Player IsInNoBuildZone == true" );
			if( item.IsKindOf("R22R_BBS_Kit") || item.IsKindOf("R22R_BaseBuildingBase_Kit") )
			{
				Print( "[R22R ActionDeployObject] -> Player has in hands either R22R_BBS_Kit or R22R_BaseBuildingBase_Kit" );
				string deployObjectFromKit;
				bool hasNoBuildZonesEnabled;

				deployObjectFromKit = item.GetSpawnableItemFromConfig(item.GetType());
				Print( "[R22R ActionDeployObject] -> deployObjectFromKit = " + deployObjectFromKit );
				if( deployObjectFromKit && deployObjectFromKit != string.Empty )
				{
					BannedTypesInNoBuildZoneConfig config = GetR22RBaseFortificationsConfig().GetBannedItemConfigForType(deployObjectFromKit);

					if( config )
					{
						Print( "[R22R ActionDeployObject] -> config found for value : " + config.ItemType );
						hasNoBuildZonesEnabled = GetR22RBaseFortificationsConfig().ClientSyncConfig.BaseRaidConfig.EnableNoBuildZones;
						if ( hasNoBuildZonesEnabled && ( config.ItemType == deployObjectFromKit ) )
						{
							Print( "[R22R ActionDeployObject] -> hasNoBuildZonesEnabled : " + hasNoBuildZonesEnabled.ToString() + "config.ItemType == deployObjectFromKit : " + config.ItemType + " -> " + deployObjectFromKit );
							return false;
						}
					}
				}

			}
		}
		return true;
	}
/*
	override bool ActionConditionContinue(ActionData action_data)
	{
		super.ActionConditionContinue(action_data)

		if(action_data.m_MainItem.IsKindOf("R22R_BBS_Kit")||action_data.m_MainItem.IsKindOf("R22R_BaseBuildingBase_Kit"))
		
		return true;
	}
*/
};