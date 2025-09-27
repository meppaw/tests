class ActionRaidBBSBaseCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		if (m_ActionData && m_ActionData.m_MainItem && m_ActionData.m_MainItem)
		{
			RaidItemConfig config = GetR22RBaseFortificationsConfig().GetRaidConfigForType(m_ActionData.m_MainItem.GetType());

			if (config)
			{
				m_ActionData.m_ActionComponent = new CAContinuousTime(config.RaidTimeInSeconds);
				Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> " + m_ActionData.m_MainItem.GetType() + " found in config with a raid time of : " + config.RaidTimeInSeconds.ToString() + " seconds.");
			}
		}
	}
};

class ActionRaidBBSBase: ActionContinuousBase
{
	void ActionRaidBBSBase()
	{
		m_CallbackClass = ActionRaidBBSBaseCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;	
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
		m_Text = "Force Open";
	}

	//ItemBase itemInHands;
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;//CCTNonRuined( UAMaxDistances.BASEBUILDING );
	}
	
	
	override bool CanBeUsedLeaning()
	{
		return false;
	}
	
	override bool CanBeUsedInFreelook()
	{
		return false;
	}

	override string GetText()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		if ( player )
		{
			ItemBase itemInHands = ItemBase.Cast(player.GetItemInHands());
			if( itemInHands && itemInHands.IsKindOf("Lockpick"))
	
			return "Lockpick Storage";
			
		}
		
		return "Force Open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		BaseBuildingBase base_building = target.GetObject();
		R22R_BBS_Base storageItem = R22R_BBS_Base.Cast( base_building );
		ItemBase itemInHands = ItemBase.Cast(player.GetItemInHands());
		bool isRaidingEnabled = false;

		if( GetR22RBaseFortificationsConfig().ClientSyncConfig )
		{
			isRaidingEnabled = GetR22RBaseFortificationsConfig().ClientSyncConfig.StorageRaidConfig.EnableStorageRaiding;
			if( isRaidingEnabled )
			{
				if( GetR22RBaseFortificationsConfig().GetRaidConfigForType(item.GetType()) )
				{
					#ifdef CodeLock
					if( storageItem && ( storageItem.IsCodeLocked() || storageItem.IsLocked() ) )
					{
						return DismantleCondition( player, target, item, true );
					}
					#endif
					if( storageItem && storageItem.IsLocked() )
					{
						return DismantleCondition( player, target, item, true );
					}
					
				}
			}
		}
		
		return false;
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{	
		return DismantleCondition( action_data.m_Player, action_data.m_Target, action_data.m_MainItem , false ) && action_data.m_Player.m_MovementState.m_iStanceIdx != DayZPlayerConstants.STANCEIDX_PRONE;
	}	
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer()");
		PlayerBase player = action_data.m_Player;
		BaseBuildingBase base_building = action_data.m_Target.GetObject();
		R22R_BBS_Base storageItem = R22R_BBS_Base.Cast( base_building );
		//ItemBase itemInHands = ItemBase.Cast(action_data.m_MainItem); //m_ActionData.m_MainItem //player.GetItemInHands()
		ItemBase itemInHands = ItemBase.Cast(player.GetItemInHands());

		CombinationLock combination_lock = storageItem.GetCombinationLock();

		#ifdef CodeLock
		CodeLock codelock = storageItem.GetCodeLock();
		#endif

		//* ---- CONFIG STUFF -----
		float percentHealthRemovedToRaidTool;
		float percentChanceBreakingRaidTool;
		float percentChanceBreakingLoot;
		float minHealthDamageToLoot;
		float maxHealthDamageToLoot;
		float combinationLockDamage;

		float raidItemCurrentHealth;
		float raidItemMaxHealth;

		float healthValueRemovedFromTool;

		float randomGeneratedChanceOfBreakingItem; //* Rand
		float randomGeneratedChanceOfDamagingLoot; //* Rand

		bool EnableHealthAffectsRaiding;

		if( GetR22RBaseFortificationsConfig().ClientSyncConfig )
		{
			RaidItemConfig config = GetR22RBaseFortificationsConfig().GetRaidConfigForType(itemInHands.GetType());

			if( config && itemInHands && storageItem )
			{
				array<EntityAI> cargoItems = new array<EntityAI>;
				storageItem.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER,cargoItems);

				Construction construction = base_building.GetConstruction();
				ConstructionActionData construction_action_data = action_data.m_Player.GetConstructionActionData();
				ConstructionPart construction_part = construction_action_data.GetTargetPart();

				percentHealthRemovedToRaidTool = config.PercentHealthRemovedItem / 100;
				percentChanceBreakingRaidTool = config.PercentChanceOfBreakingItem / 100;
				percentChanceBreakingLoot = config.PercentChanceOfBreakingLoot / 100;
				minHealthDamageToLoot = config.MinPercentHealthDamageToLoot / 100;
				maxHealthDamageToLoot = config.MaxPercentHealthDamageToLoot / 100;

				combinationLockDamage = 33;

				raidItemCurrentHealth = itemInHands.GetHealth01();
				raidItemMaxHealth = itemInHands.GetMaxHealth();

				healthValueRemovedFromTool = percentHealthRemovedToRaidTool * raidItemMaxHealth;

				randomGeneratedChanceOfBreakingItem = Math.RandomFloatInclusive( 0.0, 1.0 );
				randomGeneratedChanceOfDamagingLoot = Math.RandomFloatInclusive( 0.0, 1.0 );

				EnableHealthAffectsRaiding = config.EnableHealthAffectsRaiding;

				string genericToolBreakMessage = "Ah crap... I did more damage to my tool than to the storage itself...";

				Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> percentChanceBreakingRaidTool : " + percentChanceBreakingRaidTool.ToString() + " | randomGeneratedChanceOfBreakingItem : " + randomGeneratedChanceOfBreakingItem.ToString() +  " | percentChanceBreakingLoot : " + percentChanceBreakingLoot.ToString() + " | randomGeneratedChanceOfDamagingLoot : " + randomGeneratedChanceOfDamagingLoot.ToString());

				if( EnableHealthAffectsRaiding )
				{
					Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. || randomGeneratedChanceOfBreakingItem : " + randomGeneratedChanceOfBreakingItem.ToString() + " & randomGeneratedChanceOfDamagingLoot : " + randomGeneratedChanceOfDamagingLoot.ToString());

					if ( raidItemCurrentHealth <= 0.3 ) // < BADLY DAMAGED
					{
						randomGeneratedChanceOfBreakingItem -= 0.3;
						randomGeneratedChanceOfDamagingLoot -= 0.3;
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. Increased randomGeneratedChanceOfBreakingItem & randomGeneratedChanceOfDamagingLoot by : 0.3");
					}
					else if ( raidItemCurrentHealth <= 0.5 ) // < DAMAGED
					{
						randomGeneratedChanceOfBreakingItem -= 0.2;
						randomGeneratedChanceOfDamagingLoot -= 0.2;
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. Increased randomGeneratedChanceOfBreakingItem & randomGeneratedChanceOfDamagingLoot by : 0.2");
					}
					else if ( raidItemCurrentHealth <= 0.7 ) // < WORN
					{
						randomGeneratedChanceOfBreakingItem -= 0.1;
						randomGeneratedChanceOfDamagingLoot -= 0.1;
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. Increased randomGeneratedChanceOfBreakingItem & randomGeneratedChanceOfDamagingLoot by : 0.1");
					}
					else
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding -> Item was pristine and does not affect raiding results.");
					}

					Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding New Values || randomGeneratedChanceOfBreakingItem : " + randomGeneratedChanceOfBreakingItem.ToString() + " & randomGeneratedChanceOfDamagingLoot : " + randomGeneratedChanceOfDamagingLoot.ToString());
				}


				
				//* Does little damage, does not break the lid ::
				if( itemInHands.IsKindOf("Lockpick") )
				{
					if( randomGeneratedChanceOfBreakingItem <= percentChanceBreakingRaidTool )
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Lockpick and broke.");
						itemInHands.AddHealth("","", -1000);

						#ifdef CodeLock
						if( codelock )
						{
							codelock.AddHealth("","", -combinationLockDamage);
						}
						#endif

						if( combination_lock )
						{
							combination_lock.AddHealth("","", -combinationLockDamage);
						}
							
						
						
						GetGame().ChatMP(player, "Ah crap... I really had to break my lockpick trying to open this...", "colorAction");
						
					}
					else
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Lockpick and did not break.");
						#ifdef CodeLock
						if( codelock )
						{
							codelock.AddHealth("","", -(combinationLockDamage / 2));
							codelock.UnlockServer( player , storageItem );
							storageItem.HandleDropAttachment(codelock);
						}
						#endif
						if( combination_lock )
						{
							combination_lock.AddHealth("","", -(combinationLockDamage / 2));
							combination_lock.UnlockServer( player , storageItem );
							storageItem.HandleDropAttachment(combination_lock);
						}
						
						
						itemInHands.AddHealth("","", -healthValueRemovedFromTool);

						if( randomGeneratedChanceOfDamagingLoot <= percentChanceBreakingLoot )
						{
							Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Lockpick and destroys items in cargo.");
							DamageLootInsideStorage(cargoItems, minHealthDamageToLoot, maxHealthDamageToLoot);
							
						}
						
					}
					return;
				
				}
				//* Deals more damage, does not break the Lid ::
				if( itemInHands.IsKindOf("Hacksaw") || itemInHands.IsKindOf("HandSaw") )
				{	
					if( randomGeneratedChanceOfBreakingItem <= percentChanceBreakingRaidTool )
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Hacksaw and broke.");
						itemInHands.AddHealth("","", -1000);
						#ifdef CodeLock
						if( codelock )
						{
							codelock.AddHealth("","", -combinationLockDamage);
						}
						#endif
						if( combination_lock )
						{
							combination_lock.AddHealth("","", -combinationLockDamage);
						}
						
						GetGame().ChatMP(player, genericToolBreakMessage, "colorAction");
						
					}
					else
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Hacksaw and did not break.");
						#ifdef CodeLock
						if( codelock )
						{
							codelock.UnlockServerFromRaid( player , storageItem, true );
						}
						#endif
						if( combination_lock )
						{
							combination_lock.UnlockServerFromRaid( player , storageItem, true );
						}
						
						itemInHands.AddHealth("","", -healthValueRemovedFromTool);			

						if( randomGeneratedChanceOfDamagingLoot <= percentChanceBreakingLoot )
						{
							Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Hacksaw and destroys items in cargo.");
							DamageLootInsideStorage(cargoItems, minHealthDamageToLoot, maxHealthDamageToLoot);
							
						}
						
					}
					return;
					
				}
				//* Deals heavy damage and breaks the lid + ruins codelock ::
				else
				{
					if( randomGeneratedChanceOfBreakingItem <= percentChanceBreakingRaidTool )
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Various and broke.");
						itemInHands.AddHealth("","", -1000);
						#ifdef CodeLock
						if( codelock )
						{
							codelock.AddHealth("","", -(combinationLockDamage * 1.5));
						}
						#endif
						if( combination_lock )
						{
							combination_lock.AddHealth("","", -(combinationLockDamage * 1.5));
						}
						
						GetGame().ChatMP(player, genericToolBreakMessage, "colorAction");
						
					}
					else
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Various and did not break.");
						#ifdef CodeLock
						if( codelock )
						{
							codelock.UnlockServerFromRaid( player , storageItem );
						}
						#endif
						if( combination_lock )
						{
							combination_lock.UnlockServerFromRaid( player , storageItem );
						}
						
						construction.DismantlePartServer( player, "bbs_lid", AT_DESTROY_PART );
						itemInHands.AddHealth("","", -healthValueRemovedFromTool);	

						if( randomGeneratedChanceOfDamagingLoot <= percentChanceBreakingLoot )
						{
							Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> OnFinishProgressServer() -> Item in hands is Various and destroys items in cargo.");
							DamageLootInsideStorage(cargoItems, minHealthDamageToLoot, maxHealthDamageToLoot);
							
						}
						
					}
					return;	
				}
				
			}
		}
	}
		
	//setup
	override bool SetupAction( PlayerBase player, ActionTarget target, ItemBase item, out ActionData action_data, Param extra_data = NULL )
	{	
		if ( super.SetupAction( player, target, item, action_data, extra_data ) )
		{
			SetBuildingAnimation( item );
			
			return true;
		}
		
		return false;
	}

	void DamageLootInsideStorage( array<EntityAI> lootItems, float minHealthPercent, float maxHealthPercent ) 
	{
		Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> DamageLootInsideStorage().");
		foreach( EntityAI item : lootItems)
		{
			ItemBase itemToDamage = ItemBase.Cast(item);
			float itemMaxHealth = itemToDamage.GetMaxHealth();
			float randomHealth = Math.RandomFloatInclusive( minHealthPercent, maxHealthPercent );
			itemToDamage.AddHealth("","", -( randomHealth * itemMaxHealth ));
			Print("[R22RBaseFortificationsConfig] DamageLootInsideStorage -> Removed " + (randomHealth * itemMaxHealth).ToString() + " HP to item : " + itemToDamage.GetType());
		}
	}
	
	protected void SetBuildingAnimation( ItemBase item )
	{
		Print("[R22RBaseFortificationsConfig] ActionRaidBBSBaseCB -> SetBuildingAnimation().");
		switch ( item.Type() )
		{
			case Lockpick:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
				break;

			case FirefighterAxe:
			case WoodAxe:
			case Hatchet:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
				break;
			case Hacksaw:
			case HandSaw:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CUTBARK;
				break;				
			default:
				m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
				break;
		}
	}	
	
	protected bool DismantleCondition(PlayerBase player, ActionTarget target, ItemBase item, bool camera_check)
	{	
		if (player && !player.IsPlacingLocal() && !player.IsPlacingServer())
		{
			return true;
		}
		return false;
	}
	
}