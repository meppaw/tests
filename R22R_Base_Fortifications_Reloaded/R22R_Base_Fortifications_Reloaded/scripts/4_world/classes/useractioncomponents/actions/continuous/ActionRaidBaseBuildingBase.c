class ActionRaidBaseBuildingBaseCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		string partName; //construction_part.GetPartName()
		int raidTimeInSeconds;
		BaseBuildingBase base_building;
		R22R_Watchtower_Base baseBuildingEntity;

		if (m_ActionData && m_ActionData.m_MainItem && m_ActionData.m_Target)
		{
			Object targetObject = m_ActionData.m_Target.GetObject();
			if( targetObject )
			{
				base_building = BaseBuildingBase.Cast( targetObject );
				baseBuildingEntity = R22R_Watchtower_Base.Cast( base_building );
				partName = targetObject.GetActionComponentName(m_ActionData.m_Target.GetComponentIndex());
			}

			RaidItemConfig config = GetR22RBaseFortificationsConfig().GetRaidConfigForType(m_ActionData.m_MainItem.GetType(), true);

			if (config && baseBuildingEntity && partName)
			{
				if( baseBuildingEntity.IsGate() )
				{
					//* Tier 3 doors ::
					if(baseBuildingEntity.GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door_t3" ) || baseBuildingEntity.GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door_t3" ) || baseBuildingEntity.GetConstruction().IsPartConstructed( "level_1_wall_1_wood_door_t3" ))
					{
						raidTimeInSeconds = config.RaidTimeInSeconds + config.AdditionalRaidTimeTier3;
						m_ActionData.m_ActionComponent = new CAContinuousTime(raidTimeInSeconds);
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> " + m_ActionData.m_MainItem.GetType() + " found in config with a raid time of : " + config.RaidTimeInSeconds.ToString() + " plus an added " + config.AdditionalRaidTimeTier3.ToString() + " seconds for tier 3 Gate");
					}
					//* Tier 2 doors ::
					else if(baseBuildingEntity.GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door_t2" ) || baseBuildingEntity.GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door_t2" ) || baseBuildingEntity.GetConstruction().IsPartConstructed( "level_1_wall_1_wood_door_t2" ))
					{
						raidTimeInSeconds = config.RaidTimeInSeconds + config.AdditionalRaidTimeTier2;
						m_ActionData.m_ActionComponent = new CAContinuousTime(raidTimeInSeconds);
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> " + m_ActionData.m_MainItem.GetType() + " found in config with a raid time of : " + config.RaidTimeInSeconds.ToString() + " plus an added " + config.AdditionalRaidTimeTier2.ToString() + " seconds for tier 2 Gate");
					}
					else
					{
						raidTimeInSeconds = config.RaidTimeInSeconds;
						m_ActionData.m_ActionComponent = new CAContinuousTime(raidTimeInSeconds);
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> " + m_ActionData.m_MainItem.GetType() + " found in config with a raid time of : " + config.RaidTimeInSeconds.ToString() + "  seconds for tier 1 Gate");
					}
				}
				else
				{
					if( partName.Contains("t3") )
					{
						raidTimeInSeconds = config.RaidTimeInSeconds + config.AdditionalRaidTimeTier3;
						m_ActionData.m_ActionComponent = new CAContinuousTime(raidTimeInSeconds);
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> " + m_ActionData.m_MainItem.GetType() + " found in config with a raid time of : " + config.RaidTimeInSeconds.ToString() + " plus an added " + config.AdditionalRaidTimeTier3.ToString() + " seconds for tier 3 -> " + partName);
					}
					else if( partName.Contains("t2") )
					{
						raidTimeInSeconds = config.RaidTimeInSeconds + config.AdditionalRaidTimeTier2;
						m_ActionData.m_ActionComponent = new CAContinuousTime(raidTimeInSeconds);
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> " + m_ActionData.m_MainItem.GetType() + " found in config with a raid time of : " + config.RaidTimeInSeconds.ToString() + " plus an added " + config.AdditionalRaidTimeTier2.ToString() + " seconds for tier 2 -> " + partName);
					}
					else
					{
						raidTimeInSeconds = config.RaidTimeInSeconds;
						m_ActionData.m_ActionComponent = new CAContinuousTime(raidTimeInSeconds);
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> " + m_ActionData.m_MainItem.GetType() + " found in config with a raid time of : " + config.RaidTimeInSeconds.ToString() + " seconds for " + partName );
					}
				}
			}
		}
	}
};

class ActionRaidBaseBuildingBase: ActionContinuousBase
{
	void ActionRaidBaseBuildingBase()
	{
		m_CallbackClass = ActionRaidBaseBuildingBaseCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;	
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
		m_Text = "Raid";
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
			{
				return "Lockpick";
			}
			else if( itemInHands.IsKindOf("Hacksaw") || itemInHands.IsKindOf("HandSaw") )
			{
				return "Saw Off Lock";
			}
			else if( itemInHands.IsKindOf("ElectronicRepairKit"))
			{
				return "Bypass Lock";
			}
			else
			{
				return "Raid";
			}
		}
		return "Raid";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		BaseBuildingBase base_building = target.GetObject();
		R22R_Watchtower_Base baseBuildingEntity = R22R_Watchtower_Base.Cast( base_building );
		ItemBase itemInHands = ItemBase.Cast(player.GetItemInHands());
		bool isRaidingEnabled = false;
		bool canRaidGate = false;
		bool canRaidWalls = false;

		if( GetR22RBaseFortificationsConfig().ClientSyncConfig )
		{
			isRaidingEnabled = GetR22RBaseFortificationsConfig().ClientSyncConfig.BaseRaidConfig.EnableBaseRaiding;
			canRaidGate = GetR22RBaseFortificationsConfig().ClientSyncConfig.BaseRaidConfig.EnableGateRaiding;
			canRaidWalls = GetR22RBaseFortificationsConfig().ClientSyncConfig.BaseRaidConfig.EnableWallRaiding;

			if( isRaidingEnabled && baseBuildingEntity )
			{
				if( GetR22RBaseFortificationsConfig().GetRaidConfigForType(item.GetType(), true) )
				{
					if( baseBuildingEntity.IsGate() )
					{
						#ifdef CodeLock
						if( baseBuildingEntity && canRaidGate && ( baseBuildingEntity.IsCodeLocked() || baseBuildingEntity.IsLocked() ) )
						{
							return DismantleCondition( player, target, item, true );
						}
						#endif
						if( baseBuildingEntity && canRaidGate && baseBuildingEntity.IsLocked() )
						{
							return DismantleCondition( player, target, item, true );
						}
					}

					else
					{
						if( canRaidWalls && !( itemInHands.IsKindOf("Lockpick") || itemInHands.IsKindOf("Hacksaw") || itemInHands.IsKindOf("HandSaw") ))
						{
							return DismantleCondition( player, target, item, true );
						}
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
		Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer()");
		PlayerBase player = action_data.m_Player;
		BaseBuildingBase base_building = BaseBuildingBase.Cast( action_data.m_Target.GetObject() );
		R22R_Watchtower_Base baseBuildingEntity = R22R_Watchtower_Base.Cast( base_building );
		ItemBase itemInHands = ItemBase.Cast(player.GetItemInHands());

		ActionTarget target = action_data.m_Target;



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

		if( GetR22RBaseFortificationsConfig().ClientSyncConfig && target )
		{
			RaidItemConfig config = GetR22RBaseFortificationsConfig().GetRaidConfigForType(itemInHands.GetType(), true);

			if( config && itemInHands && baseBuildingEntity )
			{

				//* Rework of fetching construction part... ::
				Object targetObject = target.GetObject();
				string partName = targetObject.GetActionComponentName(target.GetComponentIndex());
				

				Construction construction = baseBuildingEntity.GetConstruction();
				ConstructionPart construction_part = construction.GetConstructionPart(partName);
				
				
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

				string genericToolBreakMessage = "Ah crap... I did more damage to my tool than to the fortification itself...";

//				Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> percentChanceBreakingRaidTool : " + percentChanceBreakingRaidTool.ToString() + " | randomGeneratedChanceOfBreakingItem : " + randomGeneratedChanceOfBreakingItem.ToString() +  " | percentChanceBreakingLoot : " + percentChanceBreakingLoot.ToString() + " | randomGeneratedChanceOfDamagingLoot : " + randomGeneratedChanceOfDamagingLoot.ToString());

				if( EnableHealthAffectsRaiding )
				{
//					Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. || randomGeneratedChanceOfBreakingItem : " + randomGeneratedChanceOfBreakingItem.ToString() + " & randomGeneratedChanceOfDamagingLoot : " + randomGeneratedChanceOfDamagingLoot.ToString());

					if ( raidItemCurrentHealth <= 0.3 ) // < BADLY DAMAGED
					{
						randomGeneratedChanceOfBreakingItem -= 0.3;
						randomGeneratedChanceOfDamagingLoot -= 0.3;
//						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. Increased randomGeneratedChanceOfBreakingItem & randomGeneratedChanceOfDamagingLoot by : 0.3");
					}
					else if ( raidItemCurrentHealth <= 0.5 ) // < DAMAGED
					{
						randomGeneratedChanceOfBreakingItem -= 0.2;
						randomGeneratedChanceOfDamagingLoot -= 0.2;
//						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. Increased randomGeneratedChanceOfBreakingItem & randomGeneratedChanceOfDamagingLoot by : 0.2");
					}
					else if ( raidItemCurrentHealth <= 0.7 ) // < WORN
					{
						randomGeneratedChanceOfBreakingItem -= 0.1;
						randomGeneratedChanceOfDamagingLoot -= 0.1;
//						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding : True. Increased randomGeneratedChanceOfBreakingItem & randomGeneratedChanceOfDamagingLoot by : 0.1");
					}
					else
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding -> Item was pristine and does not affect raiding results.");
					}

//					Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> EnableHealthAffectsRaiding New Values || randomGeneratedChanceOfBreakingItem : " + randomGeneratedChanceOfBreakingItem.ToString() + " & randomGeneratedChanceOfDamagingLoot : " + randomGeneratedChanceOfDamagingLoot.ToString());
				}


				
				//* GATE RAIDING ::
				if( baseBuildingEntity.IsGate())
				{
					
					CombinationLock combination_lock;

					#ifdef CodeLock
					CodeLock codelock = baseBuildingEntity.GetCodeLock();
					Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Modded Code Lock was found.");
					if( !codelock )
					{
						combination_lock = baseBuildingEntity.GetCombinationLock();
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Vanilla Lock was found, Code lock mod installed.");
					}

					#else
					combination_lock = baseBuildingEntity.GetCombinationLock();
					Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Vanilla Lock was found.");

					#endif

					if( itemInHands.IsKindOf("Lockpick"))
					{
						if( randomGeneratedChanceOfBreakingItem <= percentChanceBreakingRaidTool )
						{
							itemInHands.AddHealth("","", -1000);

							#ifdef CodeLock
							if( codelock )
							{
								codelock.AddHealth("","", -combinationLockDamage);
							}
							else if( combination_lock )
							{
								combination_lock.AddHealth("","", -combinationLockDamage);
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
							Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Item in hands is Lockpick and did not break.");
							#ifdef CodeLock
							if( codelock )
							{
								codelock.AddHealth("","", -(combinationLockDamage / 2));
								codelock.UnlockServer( player , baseBuildingEntity );
								baseBuildingEntity.HandleDropAttachment(codelock);
							}
							else if( combination_lock )
							{
								combination_lock.AddHealth("","", -(combinationLockDamage / 2));
								combination_lock.UnlockServer( player , baseBuildingEntity );
								baseBuildingEntity.HandleDropAttachment(combination_lock);
							}
							#endif
							if( combination_lock )
							{
								combination_lock.AddHealth("","", -(combinationLockDamage / 2));
								combination_lock.UnlockServer( player , baseBuildingEntity );
								baseBuildingEntity.HandleDropAttachment(combination_lock);
							}
							
							
							itemInHands.AddHealth("","", -healthValueRemovedFromTool);

							
						}
						return;
					
					}
					//* Deals more damage, does not break the Lid ::
					if( itemInHands.IsKindOf("Hacksaw") || itemInHands.IsKindOf("HandSaw") )
					{	
						if( randomGeneratedChanceOfBreakingItem <= percentChanceBreakingRaidTool )
						{
							Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Item in hands is Hacksaw and broke.");
							itemInHands.AddHealth("","", -1000);
							#ifdef CodeLock
							if( codelock )
							{
								codelock.AddHealth("","", -combinationLockDamage);
							}
							else if( combination_lock )
							{
								combination_lock.AddHealth("","", -combinationLockDamage);
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
							Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Item in hands is Hacksaw and did not break.");
							#ifdef CodeLock
							if( codelock )
							{
								codelock.UnlockServerFromRaid( player , baseBuildingEntity, true, true );
							}
							else if( combination_lock )
							{
								combination_lock.UnlockServerFromRaid( player , baseBuildingEntity, true, true );
							}
							#endif
							if( combination_lock )
							{
								combination_lock.UnlockServerFromRaid( player , baseBuildingEntity, true, true );
							}
							
							itemInHands.AddHealth("","", -healthValueRemovedFromTool);			

							
						}
						return;
						
					}
					//* Deals heavy damage and breaks the lid + ruins codelock ::
					else
					{
						if( randomGeneratedChanceOfBreakingItem <= percentChanceBreakingRaidTool )
						{
							Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Item in hands is Various and broke.");
							itemInHands.AddHealth("","", -1000);
							#ifdef CodeLock
							if( codelock )
							{
								codelock.AddHealth("","", -(combinationLockDamage * 1.5));
							}
							else if( combination_lock )
							{
								combination_lock.UnlockServerFromRaid( player , baseBuildingEntity, true, true );
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
							Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Item in hands is Various and did not break.");
							#ifdef CodeLock
							if( codelock )
							{
								Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> codelock.UnlockServerFromRaid");
								codelock.UnlockServerFromRaid( player , baseBuildingEntity, true, true );
							}
							else if( combination_lock )
							{
								Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> combination_lock.UnlockServerFromRaid");
								combination_lock.UnlockServerFromRaid( player , baseBuildingEntity, true, true );
							}
							#endif
							if( combination_lock )
							{
								combination_lock.UnlockServerFromRaid( player , baseBuildingEntity, true, true );
							}
							
//							construction.DismantlePartServer( player, construction_part.GetPartName(), AT_DISMANTLE_PART );
							itemInHands.AddHealth("","", -healthValueRemovedFromTool);	
							
						}
						return;	
					}
				}
				//* WALL RAIDING ::
				else
				{
					if( randomGeneratedChanceOfBreakingItem <= percentChanceBreakingRaidTool )
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Item in hands is Various and broke.");
						itemInHands.AddHealth("","", -1000);		
						GetGame().ChatMP(player, genericToolBreakMessage, "colorAction");
						
					}
					else
					{
						Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> OnFinishProgressServer() -> Item in hands is Various and did not break.");
						
						construction.DismantlePartServer( player, construction_part.GetPartName(), AT_DISMANTLE_PART ); //GetName -> Collision Bug, GetPartName -> Destroys all, GetMainPartName //AT_DESTROY_PART
						itemInHands.AddHealth("","", -healthValueRemovedFromTool);	
						
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
	
	protected void SetBuildingAnimation( ItemBase item )
	{
		Print("[R22RBaseFortificationsConfig] ActionRaidBaseBuildingBaseCB -> SetBuildingAnimation().");
		switch ( item.Type() )
		{
			case Lockpick:
			case ElectronicRepairKit:
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