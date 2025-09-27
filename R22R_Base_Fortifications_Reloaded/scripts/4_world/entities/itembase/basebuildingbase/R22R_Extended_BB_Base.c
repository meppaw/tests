class R22R_Palisade_Wall_Base extends R22R_Watchtower_Base
{
	override string GetConstructionKitType()
	{
		return (this.GetType() + "_Kit");
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		super.CanDisplayAttachmentCategory( category_name );
		if( category_name == "Level_1_Wall_1")
		{
			return ( GetConstruction().IsPartConstructed( "level_1_base" ) );
		}
		if( category_name == "Wall_Defense")
		{
			return (  GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left" ) && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right" ) );
		}
		if( category_name == "Tier_2")
		{
			return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left" ) && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right" ) );
		}
		if( category_name == "Tier_3")
		{
			return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_t2" ));
		}
		if( category_name == "Level_2")
		{
			return ( GetConstruction().IsPartConstructed( "level_1_roof" ) );
		}
		return true;
	}

	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		string slot_name = InventorySlots.GetSlotName(slot_id);

		if( slot_name == "Material_L1_8_Lumber" || slot_name == "Material_L1_WoodenPlanks" || slot_name == "Material_L1_Nails" )
		{
			return ( GetConstruction().IsPartConstructed( "level_1_base" ) );
		}
		return true;
	}
};

class R22R_Barricade_X_Base extends R22R_Watchtower_Base
{
	override string GetConstructionKitType()
	{
		return (this.GetType() + "_Kit");
	}

	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		return true;
	}
};

class R22R_Basic_Defense_Wall_Base extends R22R_Watchtower_Base
{
	override string GetConstructionKitType()
	{
		return (this.GetType() + "_Kit");
	}

	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		return true;
	}

	override bool CanDisplayAttachmentCategory(string category_name)
	{
		switch (category_name)
		{
			case "Level_2":
			case "Wall_Defense":
				return GetConstruction().IsPartConstructed("level_1_wall");

			case "Level_3":
				return GetConstruction().IsPartConstructed("level_1_wall_t2");
			default:
				return true;
		}
		return true;
	}

	override bool CheckSlotVerticalDistance( int slot_id, PlayerBase player )
	{
		return true;
	}
};

class R22R_Camping_Tent_Base extends R22R_Watchtower_Base
{
	override string GetConstructionKitType()
	{
		return (this.GetType() + "_Kit");
	}

	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		return true;
	}
	
	override bool CanDisplayCargo()
	{
		return GetConstruction().IsPartConstructed( "level_1_roof" );
	}
};


//* Create simple base class here based on global custom watchtower ::
class R22R_Halfwall_Base extends R22R_Watchtower_Base
{

	override string GetConstructionKitType()
	{
		return "R22R_Halfwall_Kit";
	}

	bool HasHalfwallL1Base()
	{
		return ( GetConstruction().IsPartConstructed( "level_1_base" ) || GetConstruction().IsPartConstructed( "level_1_base_door" ) || GetConstruction().IsPartConstructed( "level_1_base_slanted_left" ) || GetConstruction().IsPartConstructed( "level_1_base_slanted_right" ) );
	}

	override bool CanDisplayAttachmentSlot( int slot_id )
	{

		string slot_name = InventorySlots.GetSlotName(slot_id);
		slot_name.ToLower();
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );

		if ( slot_name.Contains( "material_l1" ) || slot_name.Contains( "level_1_" ) )
		{
			if ( slot_name.Contains( "woodenlogs" ) )
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
			else
			{
				return HasHalfwallL1Base() && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
		}

		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{

		category_name.ToLower();
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );

		if ( category_name.Contains( "level_1" ) )
		{
			if ( category_name.Contains( "level_1_" ) )
			{
				return HasHalfwallL1Base() && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
			else
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
		}
		if( category_name == "Wall_Defense" )
		{
			return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left" ) && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right" ) );
		}

		return true;
	}	
	
	//returns true if attachment slot position is within given range
	override bool CheckSlotVerticalDistance( int slot_id, PlayerBase player )
	{

		string slot_name;
		InventorySlots.GetSelectionForSlotId( slot_id , slot_name );		
		slot_name.ToLower();

		if ( slot_name.Contains( "material_l1" ) || slot_name.Contains( "level_1_" ) )
		{
			if ( slot_name.Contains( "woodenlogs" ) )
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
			else
			{
				return HasHalfwallL1Base() && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
		}

		return true;		
	}
};


//*==================================
//*		 PALISADE GATE ::
//*==================================


class R22R_Wooden_Palisade_Gate_Base extends R22R_Watchtower_Base
{
	const int GATE_STATE_NONE 				= 0;
	const int GATE_STATE_PARTIAL 			= 1;
	const int GATE_STATE_FULL 				= 2;

	
	const string SOUND_GATE_OPEN_START				= "DoorWoodTowerOpen_SoundSet";
	const string SOUND_GATE_CLOSE_START				= "DoorWoodTowerClose_start_SoundSet";
	const string SOUND_GATE_CLOSE_END				= "DoorWoodTowerClose_end_SoundSet";

	const float GATE_ROTATION_ANGLE_DEG 			= 100;
	const float GATE_ROTATION_TIME_APPROX			= 2000;		//ms

	typename ATTACHMENT_COMBINATION_LOCK	= CombinationLock;

	#ifdef CodeLock
	typename ATTACHMENT_CODE_LOCK = CodeLock;
	#endif

	protected bool m_ToDiscard 				= false; //for legacy OnStoreLoad handling
	protected bool m_IsOpened 				= false;
	protected bool m_IsOpenedClient			= false;

	protected int m_GateState 				= 0;

	protected EffectSound m_SoundGate_Start;
	protected EffectSound m_SoundGate_End;

	void R22R_Wooden_Palisade_Gate_Base()
	{
		RegisterNetSyncVariableBool( "m_IsOpened" );
		RegisterNetSyncVariableInt( "m_GateState" );
	}

	override string GetConstructionKitType()
	{
		return (this.GetType() + "_Kit");
	}
	
	override bool IsGate()
    {
        return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door" ) && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door" ) );
    }


	void SetOpenedState( bool state )
	{
		m_IsOpened = state;
	}
	
	override bool IsOpened()
	{
		return m_IsOpened;
	}

	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		//write
		ctx.Write( m_GateState );
		ctx.Write( m_IsOpened );
		if (LogManager.IsBaseBuildingLogEnable()) bsbDebugPrint("[bsb] OnStoreSave - build=" + m_GateState + " opened=" + m_IsOpened);
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;

		//--- Fence data ---
		//has gate
		if (version < 110)
		{
			if ( !ctx.Read( m_ToDiscard ) )
			{
				m_ToDiscard = false;
				return false;
			}
			m_GateState = GATE_STATE_NONE;
		}
		else if ( !ctx.Read( m_GateState ) )
		{
			m_GateState = GATE_STATE_NONE;
			return false;
		}
		
		//is opened
		if ( !ctx.Read( m_IsOpened ) )
		{
			m_IsOpened = false;
			return false;
		}
		
		if (LogManager.IsBaseBuildingLogEnable()) bsbDebugPrint("[bsb] OnStoreLoad - build=" + m_GateState + " opened=" + m_IsOpened);
		//---
		
		return true;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		//set gate state
		ConstructionPart gate_part = GetConstruction().GetGateConstructionPart();
		if( gate_part )
		{
			SetGateState( CheckGateState() );
		}
		
		//update gate state visual
		if ( IsOpened() )
		{
			OpenGate();
		}
		
		UpdateVisuals();
		
		if (LogManager.IsBaseBuildingLogEnable()) bsbDebugPrint("[bsb] AfterStoreLoad - build=" + gate_part.IsBuilt() + " opened=" + IsOpened());
	}	
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if ( m_IsOpenedClient != m_IsOpened )
		{
			m_IsOpenedClient = m_IsOpened;
			
			if ( m_IsOpenedClient )
			{
				OpenGate();
			}
			else
			{
				CloseGate();
			}
		}
	}

	override bool IsLocked()
	{
		CombinationLock combination_lock = GetCombinationLock();
		if ( combination_lock && combination_lock.IsLocked() )
		{
			return true;
		}
		
		return false;
	}

	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		//super
		if ( !super.CanDisplayAttachmentCategory( category_name ) )
			return false;
		
		if ( category_name == "CodeLock" )
		{
			return IsGate();
		}

		if( category_name == "Tier_2" )
		{
			return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door" ) || GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door" ) )
		}

		if( category_name == "Tier_3" )
		{
			return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door_t2" ) || GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door_t2" ) )
		}

		return true;
	}

	
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		super.CanReceiveAttachment(attachment, slotId);	

		#ifdef CodeLock
		if (attachment.Type() == ATTACHMENT_CODE_LOCK && (!IsGate() || !GetDayZGame().GetCodeLockConfig().CanAttachToGates())) 
		{ 
			return false; 
		}
		#endif

		return true;
	}
	

	override void OnPartDismantledServer( notnull Man player, string part_name, int action_id )
	{
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart( part_name );
		PlayerBase playerB = PlayerBase.Cast( player ); //GetGame().GetPlayer()

		if ( constrution_part.IsGate() )
		{
			if ( IsLocked() )
			{
				CombinationLock combination_lock = CombinationLock.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_COMBINATION_LOCK ) );
				combination_lock.UnlockServer( playerB , this );
			}

			#ifdef CodeLock
			if (IsCodeLocked()) {
                CodeLock codelock = CodeLock.Cast(GetCodeLock());
                codelock.UnlockServer(playerB, this);
            }
			#endif 
		}

		super.OnPartDismantledServer( player, part_name, action_id );


		if ( m_PartsWithDamageTriggers.Find(part_name) != -1 )
		{
			DestroyAreaDamage(part_name);
		}

		SetGateState( CheckGateState() );

		UpdateVisuals();
	}

	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
		super.OnPartDestroyedServer( player, part_name, action_id );
	
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart( part_name );
		if ( constrution_part.IsGate() && destroyed_by_connected_part ) //avoids attachment dropping on regular hinges destruction
		{
			//drop regular attachments
			HandleDropAttachment(GetCombinationLock());
			
			//rotate back to place
			if ( IsOpened() )
				CloseGate();
		}
		if ( part_name == "level_1_wall_1_wood_left_door" )
		{
			HandleDropAttachment(GetCombinationLock());
		}
		if ( part_name == "level_1_wall_1_wood_right_door" )
		{
			HandleDropAttachment(GetCombinationLock());
		}
		
		SetGateState( CheckGateState() );
		//update visuals (server)
		UpdateVisuals();
	}

	void GateAttachmentsSanityCheck()
	{
		ConstructionPart left_door = GetConstruction().GetConstructionPart("level_1_wall_1_wood_left_door");
		ConstructionPart right_door = GetConstruction().GetConstructionPart("level_1_wall_1_wood_right_door");
		if( !left_door.IsBuilt() )
		{
			HandleDropAttachment(GetCombinationLock());
		}
		if( !right_door.IsBuilt() )
		{
			HandleDropAttachment(GetCombinationLock());
		}
	}

	//--- OPEN/CLOSE ACTIONS
	bool CanOpenGate()
	{
		#ifdef CodeLock
		if ( !IsOpened() && !IsLocked() && !IsCodeLocked() )
		{
			return true;
		}
		#else

		if ( !IsOpened() && !IsLocked() )
		{
			return true;
		} 
		
		#endif
		
		return false;

		
	}
	
	bool CanCloseGate()
	{
		return (IsOpened() && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door" ) && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door" ) );
	}
	
	void OpenGate()
	{
		//server or single player
		if ( GetGame().IsServer() )
		{
			float value = GATE_ROTATION_ANGLE_DEG;
			SetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_Rotate", 				value );
			SetAnimationPhase( "Level_1_Wall_1_Wood_Right_Door_Rotate", 			value );

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door_t2" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_T2_Rotate", 			value );
			}

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door_t2" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Right_Door_T2_Rotate", 			value );
			}

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door_t3" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_T3_Rotate", 			value );
			}

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door_t3" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Right_Door_T3_Rotate", 			value );
			}

			SetOpenedState( true );
			
			//regenerate navmesh
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false );
			
			//synchronize
			SynchronizeBaseState();
		}
		
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			//play sound
			SoundGateOpenStart();
		}
		
		//remove BarbedWire AreaDamageTrigger
//		UpdateBarbedWireAreaDamagePos(0,true);
		
		//add check
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove(CheckGateClosed);
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( CheckGateOpened, 0, true );

		
	}
	
	void CloseGate()
	{

		//server or single player
		if ( GetGame().IsServer() )
		{
			float value = 0;
			SetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_Rotate", 				value );
			SetAnimationPhase( "Level_1_Wall_1_Wood_Right_Door_Rotate", 			value );

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door_t2" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_T2_Rotate", 			value );
			}

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door_t2" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Right_Door_T2_Rotate", 			value );
			}

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left_door_t3" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_T3_Rotate", 			value );
			}

			if(GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right_door_t3" ))
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Right_Door_T3_Rotate", 			value );
			}
			
			SetOpenedState( false );
			
			//regenerate navmesh
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false );
			
			//synchronize
			SynchronizeBaseState();
			
		}
		
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			//play sound
			
			//GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( SoundGateCloseStart, 2000, false );
			SoundGateCloseStart();
		}
		
		//remove BarbedWire AreaDamageTrigger
//		UpdateBarbedWireAreaDamagePos(0,true);
		
		//add check
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove(CheckGateOpened);
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( CheckGateClosed, 0, true );

		
	}
	
	protected void CheckGateOpened()
	{
		if ( GetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_Rotate" ) == GATE_ROTATION_ANGLE_DEG )			//animation finished - open
		{
//			UpdateBarbedWireAreaDamagePos(GetAnimationPhase( "Wall_Gate_Rotate" ));
			//remove check
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove( CheckGateOpened );
		}
	}
	
	protected void CheckGateClosed()
	{
		if ( GetAnimationPhase( "Level_1_Wall_1_Wood_Left_Door_Rotate" ) == 0 )			//animation finished - closed
		{
			//client or single player
			if ( !GetGame().IsDedicatedServer() )
			{
				//play sound
				if ( this ) SoundGateCloseEnd();
			}
//			UpdateBarbedWireAreaDamagePos(GetAnimationPhase( "Wall_Gate_Rotate" ));
			//remove check
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove( CheckGateClosed );
		}
	}

	void SetGateState( int state )
	{
		m_GateState = state;
		SetSynchDirty();
	}
	
	int GetGateState()
	{
		return m_GateState;
	}

	int CheckGateState()
	{
		ConstructionPart gate_part = GetConstruction().GetGateConstructionPart();
		if( gate_part )
		{
			int state = GATE_STATE_NONE;
		
			if( gate_part.IsBuilt() )
			{
				ConstructionPart req_part;
				array<string> req_parts = gate_part.GetRequiredParts();
				for (int i = 0; i < req_parts.Count(); i++)
				{
					req_part = GetConstruction().GetConstructionPart(req_parts.Get(i));
					if(!req_part.IsBuilt())
						break;
				}
				
				if( i != req_parts.Count() )
				{
					state = GATE_STATE_PARTIAL;
				}
				else
				{
					state = GATE_STATE_FULL;
				}
				
			}
		}
		return state;
	}

	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundGateOpenStart()
	{
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			PlaySoundSet( m_SoundGate_Start, SOUND_GATE_OPEN_START, 0.1, 0.1 );
		}
	}

	protected void SoundGateCloseStart()
	{
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			PlaySoundSet( m_SoundGate_Start, SOUND_GATE_CLOSE_START, 0.1, 0.1 );
		}
	}

	protected void SoundGateCloseEnd()
	{
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			PlaySoundSet( m_SoundGate_End, SOUND_GATE_CLOSE_END, 0.1, 0.1 );
		}
	}

	// Add open & close actions ::
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionOpenPalisadeGate);
		


		// Vanilla ::
		AddAction(ActionNextCombinationLockDialOnPalisadeGate);
		AddAction(ActionDialCombinationLockOnPalisadeGate);


		#ifdef CodeLock
		AddAction(ActionAttachCodeLockOnPalisadeGate);
        AddAction(ActionInteractLockOnPalisadeGate);
        AddAction(ActionManageLockOnPalisadeGate);
        AddAction(ActionLockAdminOnPalisadeGate);
        #endif

		AddAction(ActionClosePalisadeGate);
		
	}

};


//*==================================
//*		 SINGLE DOOR ::
//*==================================


class R22R_Single_Door_Base extends R22R_Wooden_Palisade_Gate_Base
{

	void R22R_Single_Door_Base()
	{
	}

	override string GetConstructionKitType()
	{
		return (this.GetType() + "_Kit");
	}

    override bool IsGate() 
    {
        return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_door" ) );
    }

	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		switch (category_name)
		{
			case "CodeLock":
				return GetConstruction().IsPartConstructed("level_1_wall_1_wood_door");

			case "Tier_2_Base":
				return GetConstruction().IsPartConstructed("level_1_base");
			
			case "Tier_3_Base":
				return GetConstruction().IsPartConstructed("level_1_base_t2");

			case "Tier_1_Door":
				return GetConstruction().IsPartConstructed("level_1_base");

			case "Tier_2_Door":
				return GetConstruction().IsPartConstructed("level_1_wall_1_wood_door");

			case "Tier_3_Door":
				return GetConstruction().IsPartConstructed("level_1_wall_1_wood_door_t2");

			default:
				return true;
		}
		return true;
	}

	override bool CheckSlotVerticalDistance( int slot_id, PlayerBase player )
	{
		return true;
	}

	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
		super.OnPartDestroyedServer( player, part_name, action_id );
	
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart( part_name );
		if ( constrution_part.IsGate() && destroyed_by_connected_part ) //avoids attachment dropping on regular hinges destruction
		{
			//drop regular attachments
			HandleDropAttachment(GetCombinationLock());
			
			//rotate back to place
			if ( IsOpened() )
				CloseGate();
		}
		if ( part_name == "level_1_wall_1_wood_door" )
		{
			HandleDropAttachment(GetCombinationLock());
		}
		
		SetGateState( CheckGateState() );
		//update visuals (server)
		UpdateVisuals();
	}

	override void GateAttachmentsSanityCheck()
	{
		ConstructionPart door = GetConstruction().GetConstructionPart("level_1_wall_1_wood_door");
		if( !door.IsBuilt() )
		{
			HandleDropAttachment(GetCombinationLock());
		}
	}

	override bool CanCloseGate()
	{
		return (IsOpened() && IsGate() ); //GetConstruction().IsPartConstructed( "level_1_wall_1_wood_door" )
	}

	override void OpenGate()
	{
		//server or single player
		if ( GetGame().IsServer() )
		{
			float value = GATE_ROTATION_ANGLE_DEG;
			SetAnimationPhase( "Level_1_Wall_1_Wood_Door_Rotate", 				value );

			if( GetConstruction().IsPartConstructed("level_1_wall_1_wood_door_t2") )
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Door_T2_Rotate", 		value );
			}
			if( GetConstruction().IsPartConstructed("level_1_wall_1_wood_door_t3") )
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Door_T3_Rotate", 		value );
			}
			

			SetOpenedState( true );
			
			//regenerate navmesh
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false );
			
			//synchronize
			SynchronizeBaseState();
		}
		
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			//play sound
			SoundGateOpenStart();
		}
		
		//remove BarbedWire AreaDamageTrigger
//		UpdateBarbedWireAreaDamagePos(0,true);
		
		//add check
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove(CheckGateClosed);
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( CheckGateOpened, 0, true );

		
	}
	
	override void CloseGate()
	{

		//server or single player
		if ( GetGame().IsServer() )
		{
			float value = 0;
			SetAnimationPhase( "Level_1_Wall_1_Wood_Door_Rotate", 				value );

			if( GetConstruction().IsPartConstructed("level_1_wall_1_wood_door_t2") )
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Door_T2_Rotate", 		value );
			}

			if( GetConstruction().IsPartConstructed("level_1_wall_1_wood_door_t3") )
			{
				SetAnimationPhase( "Level_1_Wall_1_Wood_Door_T3_Rotate", 		value );
			}
			
			SetOpenedState( false );
			
			//regenerate navmesh
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false );
			
			//synchronize
			SynchronizeBaseState();
			
		}
		
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			//play sound
			
			//GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( SoundGateCloseStart, 2000, false );
			SoundGateCloseStart();
		}
		
		//remove BarbedWire AreaDamageTrigger
//		UpdateBarbedWireAreaDamagePos(0,true);
		
		//add check
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove(CheckGateOpened);
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( CheckGateClosed, 0, true );

		
	}
	
	override void CheckGateOpened()
	{
		if ( GetAnimationPhase( "Level_1_Wall_1_Wood_Door_Rotate" ) == GATE_ROTATION_ANGLE_DEG )			//animation finished - open
		{
//			UpdateBarbedWireAreaDamagePos(GetAnimationPhase( "Wall_Gate_Rotate" ));
			//remove check
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove( CheckGateOpened );
		}
	}
	
	override void CheckGateClosed()
	{
		if ( GetAnimationPhase( "Level_1_Wall_1_Wood_Door_Rotate" ) == 0 )			//animation finished - closed
		{
			//client or single player
			if ( !GetGame().IsDedicatedServer() )
			{
				//play sound
				if ( this ) SoundGateCloseEnd();
			}
//			UpdateBarbedWireAreaDamagePos(GetAnimationPhase( "Wall_Gate_Rotate" ));
			//remove check
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove( CheckGateClosed );
		}
	}

};

class R22R_Hesco_Base extends R22R_Watchtower_Base
{
	override string GetConstructionKitType()
	{
		return (this.GetType() + "_Kit");
	}

	override bool CheckSlotVerticalDistance( int slot_id, PlayerBase player )
	{
		return true;
	}

	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		string slot_name = InventorySlots.GetSlotName(slot_id);

		if( slot_name == "Material_L2_Fabric" || slot_name == "Material_L2_MetalWire" )
		{
			return ( GetConstruction().IsPartConstructed( "level_1_wall" ) );
		}
		if( slot_name == "Material_L3_Fabric" || slot_name == "Material_L3_MetalWire" )
		{
			return ( GetConstruction().IsPartConstructed( "level_2_wall" ) );
		}
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		super.CanDisplayAttachmentCategory( category_name );
		if( category_name == "Level_1")
		{
			return true;
		}
		if( category_name == "Walkway")
		{
			return ( GetConstruction().IsPartConstructed( "level_3_wall" ) );
		}
		if( category_name == "Stairway")
		{
			return ( GetConstruction().IsPartConstructed( "level_1_walkway" ) );
		}
		
		return true;
	}
};

//*==================================
//*		 OTHERS ::
//*==================================

//* Assign the final class to the simple class above ::
class R22R_Wooden_Palisade extends R22R_Palisade_Wall_Base{};
class R22R_Halfwall extends R22R_Halfwall_Base{};
class R22R_Wooden_Palisade_Gate extends R22R_Wooden_Palisade_Gate_Base{};
class R22R_Single_Door extends R22R_Single_Door_Base{};

//* CAMP
class R22R_Barricade_X extends R22R_Barricade_X_Base{};
class R22R_Camp_Tent extends R22R_Camping_Tent_Base{};
class R22R_Basic_Defense_Wall extends R22R_Basic_Defense_Wall_Base{};
class R22R_Basic_Defense_Half_Wall extends R22R_Basic_Defense_Wall_Base{};
class R22R_Hesco extends R22R_Hesco_Base{};
class R22R_Standalone_Staircase extends R22R_Basic_Defense_Wall_Base{};
class R22R_Standalone_Walkway extends R22R_Basic_Defense_Wall_Base{};


