class R22R_BBS_Base extends BaseBuildingBase
{

	const int STORAGE_STATE_NONE 					= 0;
	const int STORAGE_STATE_PARTIAL 				= 1;
	const int STORAGE_STATE_FULL 					= 2;
	
	const string ATTACHMENT_SLOT_COMBINATION_LOCK 	= "Att_CombinationLock";
	const string SOUND_LID_OPEN_START				= "R22R_Open_Lid_Slide_SoundSet";
	const string SOUND_LID_CLOSE_START				= "R22R_Close_Lid_Slide_SoundSet";
	const string SOUND_LID_CLOSE_END				= "R22R_End_Lid_Slide_SoundSet";

	const float LID_ROTATION_ANGLE_DEG 				= 50;      // 100
	const float LID_ROTATION_TIME_APPROX			= 2000;		//ms
	const float MAX_WEIGHT_LIMIT_FOR_PICKUP			= 75000.0;  // Includes 25Kg for item itself, 75kg total ::
	
	const float MAX_ACTION_DETECTION_ANGLE_RAD 		= 1.3;		//1.3 RAD = ~75 DEG
	const float MAX_ACTION_DETECTION_DISTANCE 		= 2.0;		//meters
	
	typename ATTACHMENT_COMBINATION_LOCK			= CombinationLock;
	typename ATTACHMENT_PLANKS						= WoodenPlank;
	typename ATTACHMENT_NAILS						= Nail;

	#ifdef CodeLock
	typename ATTACHMENT_CODE_LOCK = CodeLock;
	#endif
	
	protected bool m_ToDiscard 						= false; //for legacy OnStoreLoad handling
	protected bool m_IsOpened 						= false;
	protected bool m_IsOpenedClient					= false;

	protected bool m_IsTooHeavy 					= false;
	protected bool m_IsDynamicStorage				= false;
	protected bool m_IsStaticItem					= false;

	protected int m_StorageState 					= 0;

	protected int m_storedGoodsQty					= 0;
	protected int m_storedGoodsQtyClient			= 0;

	protected int STORAGE_LOW						= 1;
	protected int STORAGE_MEDIUM					= 10;
	protected int STORAGE_HIGH						= 16;
	protected int STORAGE_FULL						= 20;

	protected string MAIN_STORAGE_SLOT				= "Material_L1_20_WoodenPlanks";

	//* -------------- <Client-Side> ---------------
	
	
	protected EffectSound m_SoundLid_Start;
	protected EffectSound m_SoundLid_End;
	
	void R22R_BBS_Base()
	{
		RegisterNetSyncVariableBool( "m_IsOpened" );
		RegisterNetSyncVariableBool( "m_IsTooHeavy" );
		RegisterNetSyncVariableInt( "m_StorageState" );
		RegisterNetSyncVariableInt( "m_storedGoodsQty" );
	}

	void ~R22R_BBS_Base()
	{
	}
	
	override string GetConstructionKitType()
	{
		//return "R22R_BBS_Kit";
		return (this.GetType() + "_Kit");
	}
	
	override int GetMeleeTargetType()
	{
		return EMeleeTargetType.NONALIGNABLE;
	}
	
	bool HasLid()
	{
		return ( GetConstruction().IsPartConstructed( "bbs_lid" ) );
	}

	bool HasSmallInventory()
	{
		return false;
	}

	bool IsDynamicStorage()
	{
		return m_IsDynamicStorage;
	}

	bool IsStaticItem()
	{
		return m_IsStaticItem;
	}

	//* Different from constructionpart.c -> To work with CodeLock ::
	bool IsGate() 
    {
        return ( GetConstruction().IsPartConstructed( "bbs_lid" ) );
    }

	override bool CanFoldBaseBuildingObject()
	{
		if ( GetConstruction().IsPartConstructed( "bbs_base" ) || GetInventory().AttachmentCount() > 0 )
		{
			return false;
		}
		
		return true;
	}

	void SynchronizeStorageQty()
	{
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
		}
	}

    override void AfterStoreLoad()
    {    
        super.AfterStoreLoad();
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateStorageAnimationStages, 4000, false, MAIN_STORAGE_SLOT);
    
		ConstructionPart storage_part = GetConstruction().GetGateConstructionPart();
		SetStorageState( CheckStorageState() );
		
		if ( IsOpened() )
		{
			OpenLid();
		}

		
		UpdateStorageAnimationStages(MAIN_STORAGE_SLOT);
		
		
		UpdateVisuals();
	}

    override void EEItemAttached(EntityAI item, string slot_name)
    {
        super.EEItemAttached(item, slot_name);
        
		if( GetGame().IsServer() )
		{
			if(!IsStaticItem())
			{
				if (slot_name == MAIN_STORAGE_SLOT)
				{
					UpdateStorageAnimationStages(MAIN_STORAGE_SLOT);
				}

				if (slot_name == "Material_Shelter_Fabric_1" || slot_name == "Wall_Camonet" )
				{
					SetAnimationPhase("BBS_Cover", 0);
				}
			}
		}
    }

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        super.EEItemDetached(item, slot_name);

        if( GetGame().IsServer() )
		{
			if(!IsStaticItem())
			{
				if (slot_name == MAIN_STORAGE_SLOT)
				{
					SetAnimationPhase("Storage_Low", 1);
					SetAnimationPhase("Storage_Medium", 1);
					SetAnimationPhase("Storage_High", 1);
					SetAnimationPhase("Storage_Full", 1);

					m_storedGoodsQty = 0;
					SynchronizeStorageQty();
				}

				if (slot_name == "Material_Shelter_Fabric_1" || slot_name == "Wall_Camonet" )
				{
					SetAnimationPhase("BBS_Cover", 1);
				} 
			}
		}
    }

	override void OnAttachmentQuantityChanged(ItemBase item)
    {
        super.OnAttachmentQuantityChanged(item);

		if(!IsStaticItem())
		{
			UpdateStorageAnimationStages(MAIN_STORAGE_SLOT);
		}
    }

	void UpdateStorageAnimationStages( string slot_name )
	{
		if( GetGame().IsServer() )
		{
			int storedGoodsQuantity = 0;

			storedGoodsQuantity = CountStoredGoods(slot_name);

			if( storedGoodsQuantity != 0 )
			{
				m_storedGoodsQty = storedGoodsQuantity;
				SynchronizeStorageQty();
			}


			if (storedGoodsQuantity >= STORAGE_LOW)
			{
				SetAnimationPhase("Storage_Low", 0);
			}
			else
			{
				SetAnimationPhase("Storage_Low", 1);
			}

			if (storedGoodsQuantity >= STORAGE_MEDIUM)
			{
				SetAnimationPhase("Storage_Medium", 0);
			}
			else
			{
				SetAnimationPhase("Storage_Medium", 1);
			}

			if (storedGoodsQuantity >= STORAGE_HIGH)
			{
				SetAnimationPhase("Storage_High", 0);
			}
			else
			{
				SetAnimationPhase("Storage_High", 1);
			}

			if (storedGoodsQuantity >= STORAGE_FULL)
			{
				SetAnimationPhase("Storage_Full", 0);
			}
			else
			{
				SetAnimationPhase("Storage_Full", 1);
			}	

			SynchronizeStorageQty();		
		}
	}


	int CountStoredGoods(string slot_name)
    {
        int count = 0;
        int slot_id;
        int stack_max;

        if (!(slot_name == string.Empty)) //slot_name.Length() != 0
        {
            slot_id = InventorySlots.GetSlotIdFromString(slot_name);
            stack_max = InventorySlots.GetStackMaxForSlotId(slot_id);
            EntityAI eAI = GetInventory().FindAttachment(slot_id);
            if (eAI && (slot_id != InventorySlots.INVALID))
            {
                ItemBase itembase = ItemBase.Cast(eAI);
                if (itembase)
                {
                    count = itembase.GetQuantity();
                }
            }
        }

        return count;
    }

	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if ( item.IsKindOf("Rifle_Base") )
		{
			return !HasSmallInventory();
		}

		//* REMOVES the option to add the combinationlock IN the cargo, but still lets you atatch it.
		//* Included since having the combinationlock in the inventory would cause weird issues...
		//* DOES NOT affect CodeLock, which works perfectly somehow, hence why we do not have IsKindOf(Comb...);.
		if ( item.GetType() == "CombinationLock" || item.GetType() == "CombinationLock4" )
		{
			return false;
		}
		
		return super.CanReceiveItemIntoCargo(item);
	}

	override bool CanDisplayCargo()
	{
		
		if(GetConstruction().IsPartConstructed( "bbs_lid" ))
		{
			return IsOpened();
		}
		else 
		{
			return GetConstruction().IsPartConstructed( "bbs_base" );
		}
		
	}

	void UpdateWeightStatus()
	{ 
		SetStorageWeight(this); 
	}

	bool HasValidParent() 
	{ 
		EntityAI targetParent = EntityAI.Cast(GetHierarchyParent()); 
		return !GetHierarchyParent() || BaseBuildingBase.Cast(targetParent); 
	}

	override bool IsTakeable()
	{
		return true;
	}

	void SetStorageWeight( EntityAI parent )
	{
		float tempWeight;

		if( parent )
		{
			tempWeight = parent.GetWeightEx();
			m_IsTooHeavy = tempWeight > MAX_WEIGHT_LIMIT_FOR_PICKUP;
			SetSynchDirty();
		}
	}

	bool IsTooHeavy()
	{
		return m_IsTooHeavy;
	}

	//hands
	override bool CanPutIntoHands( EntityAI parent )
	{
		return !IsTooHeavy() && !IsOpened();
	}

	//this into/outo parent.Cargo
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}
	
	override bool CanRemoveFromCargo( EntityAI parent )
	{
		return false;
	}

	void SetStorageState( int state )
	{
		m_StorageState = state;
		SetSynchDirty();
	}
	
	int GetStorageState()
	{
		return m_StorageState;
	}
	
	int CheckStorageState()
	{

		int state = STORAGE_STATE_NONE;

		if( GetConstruction().IsPartConstructed( "bbs_base" ) )
		{
			state = STORAGE_STATE_PARTIAL;
		}

		if( GetConstruction().IsPartConstructed( "bbs_lid" ) )
		{
			state = STORAGE_STATE_FULL;
		}

		return state;
	}
	
	void SetOpenedState( bool state )
	{
		m_IsOpened = state;
	}
	
	override bool IsOpened()
	{
		return m_IsOpened;
	}

	bool HasStoredGoods()
	{
		return m_storedGoodsQty > 0;
	}

	bool IsLocked()
	{
		CombinationLock combination_lock = GetCombinationLock();
		if ( combination_lock && combination_lock.IsLocked() )
		{
			return true;
		}
		
		return false;
	}
	
	CombinationLock GetCombinationLock()
	{
		CombinationLock combination_lock = CombinationLock.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_COMBINATION_LOCK ) );
		return combination_lock;
	}

	
	//--- CONSTRUCTION KIT
	override vector GetKitSpawnPosition()
	{
		if ( MemoryPointExists( "kit_spawn_position" ) )
		{
			vector position;
			position = GetMemoryPointPos( "kit_spawn_position" );
			
			return ModelToWorld( position );
		}
		
		return GetPosition();
	}	

	// --- INVENTORY
	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		if (!super.CanDisplayAttachmentSlot(slot_id))
			return false;
		
		string slot_name = InventorySlots.GetSlotName(slot_id);
		
		if ( slot_name == "Att_CombinationLock" )
		{
			if ( !HasLid() )
			{
				return false;
			}
		}
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		if( IsDynamicStorage() )
		{
			if (category_name == "Level_1")
			{
				return !GetConstruction().IsPartConstructed("bbs_base");
			}
			if (category_name == "Storage")
			{
				return GetConstruction().IsPartConstructed("bbs_base");
			}
			if (category_name == "Cover")
			{
				return GetConstruction().IsPartConstructed("bbs_base");
			}
			return true;
		}
		else if( IsStaticItem() )
		{
			if (category_name == "Level_1")
			{
				return !GetConstruction().IsPartConstructed("bbs_base");
			}
			if (category_name == "Cover")
			{
				return GetConstruction().IsPartConstructed("bbs_base");
			}
			return true;
		}
		else
		{
			if( category_name == "Level_1" )
			{
				return !HasLid();
			} 
			if (category_name == "Cover")
			{
				return GetConstruction().IsPartConstructed("bbs_lid");
			}
			return true;
		}
		
		return true;
	}	

	bool HasCover()
	{
		EntityAI cover_fabric = FindAttachmentBySlotName("Material_Shelter_Fabric_1");
		EntityAI cover_camonet = FindAttachmentBySlotName("Wall_Camonet");
		if( cover_fabric || cover_camonet )
			return true;

		return false;
	}

	// ---
	
	// --- EVENTS
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		//write
		ctx.Write( m_StorageState );
		ctx.Write( m_IsOpened );
		ctx.Write( m_IsTooHeavy );
		ctx.Write( m_storedGoodsQty );
		if (LogManager.IsBaseBuildingLogEnable()) bsbDebugPrint("[bsb] OnStoreSave - build=" + m_StorageState + " opened=" + m_IsOpened);
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;

		//--- StorageUnit data ---
		//has Lid
		if (version < 110)
		{
			if ( !ctx.Read( m_ToDiscard ) )
			{
				m_ToDiscard = false;
				return false;
			}
			m_StorageState = STORAGE_STATE_NONE;
		}
		else if ( !ctx.Read( m_StorageState ) )
		{
			m_StorageState = STORAGE_STATE_NONE;
			return false;
		}
		
		//is opened
		if ( !ctx.Read( m_IsOpened ) )
		{
			m_IsOpened = false;
			return false;
		}

		//is too heavy
		if ( !ctx.Read( m_IsTooHeavy ) )
		{
			m_IsTooHeavy = false;
			return false;
		}

		if( !ctx.Read( m_storedGoodsQty ))
		{
			m_IsOpened = 0;
			return false;
		}
		
		if (LogManager.IsBaseBuildingLogEnable()) bsbDebugPrint("[bsb] OnStoreLoad - build=" + m_StorageState + " opened=" + m_IsOpened);
		//---
		
		return true;
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if ( m_IsOpenedClient != m_IsOpened )
		{
			m_IsOpenedClient = m_IsOpened;
			
			if ( m_IsOpenedClient )
			{
				OpenLid();
			}
			else
			{
				CloseLid();
			}
		}
		if( m_storedGoodsQtyClient != m_storedGoodsQty )
		{
			m_storedGoodsQtyClient = m_storedGoodsQty;

			if( m_storedGoodsQtyClient > 0)
			{
				UpdateStorageAnimationStages(MAIN_STORAGE_SLOT);
			}
			
		}
	}
	
	//--- BUILD EVENTS
	//CONSTRUCTION EVENTS

	void OnLidBuiltServer(PlayerBase player)
	{
		if(player)
		{
			vector playerPosition = player.GetPosition();
			int plankAmount = 0;
			int nailAmount = 0;

			//* TO DO :: Find all attachements of the item
			//* Count how many nails are in Material_Nails and planks in Material_WoodenPlanks
			//* assign values to integers above
			//* spawn the nails and planks at player's position.

			EntityAI planksAttached = this.FindAttachmentBySlotName("Material_WoodenPlanks");
			EntityAI nailsAttached = this.FindAttachmentBySlotName("Material_Nails");

			if( planksAttached )
			{	
				ItemBase plankItem = ItemBase.Cast(planksAttached);
				plankAmount = plankItem.GetQuantity();
				HandleDropAttachment(plankItem);
			}

			if( nailsAttached )
			{	
				ItemBase nailItem = ItemBase.Cast(nailsAttached);
				nailAmount = nailItem.GetQuantity();
				HandleDropAttachment(nailItem);
			}
		}		
	}

	override void OnPartBuiltServer( notnull Man player, string part_name, int action_id )
	{
		ConstructionPart construtionPart = GetConstruction().GetConstructionPart(part_name);
		PlayerBase playerB = PlayerBase.Cast( player );
		
		//check base state
		if (construtionPart.IsBase())
		{
			int randomTen = Math.RandomInt(1,10);
			SetBaseState(true);

			//spawn blueprint
			if(randomTen < 8)
			{
				CreateConstructionKit();
			}
			else
			{
				if( playerB )
				{
					GetGame().ChatMP(playerB, "Ah crap I need to be more careful. I destroyed my blueprint... I will have to craft another one.", "colorAction");
				}
			}
			
		}

		//if ( part_name == "bbs_lid" )
		if(construtionPart.IsGate())
		{
			OnLidBuiltServer(playerB);
		}
			
		//register constructed parts for synchronization
		RegisterPartForSync(construtionPart.GetId());
		
		//register action that was performed on part
		RegisterActionForSync(construtionPart.GetId(), action_id);
		
		//synchronize
		SynchronizeBaseState();

		SetPartFromSyncData(construtionPart); // server part of sync, client will be synced from SetPartsFromSyncData
		
		UpdateNavmesh();
		
		//reset action sync data
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ResetActionSyncData, 100, false, this);
		
		SetStorageState(CheckStorageState());
		
		//update visuals (server)
		UpdateVisuals();
	}

	override void OnPartDismantledServer( notnull Man player, string part_name, int action_id )
	{
		PlayerBase playerB = PlayerBase.Cast( player );
		super.OnPartDismantledServer( player, part_name, action_id );
		//check StorageUnit state

		MiscGameplayFunctions.ThrowAllItemsInInventoryWithFakeVelocity(this, part_name, 0);

//		super.OnPartDismantledServer( player, part_name, action_id );
		
		SetStorageState( CheckStorageState() );
		
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
		super.OnPartDestroyedServer( player, part_name, action_id );

		if ( part_name == "bbs_lid" )
		{
			HandleDropAttachment(GetCombinationLock());
		}

		MiscGameplayFunctions.ThrowAllItemsInInventoryWithFakeVelocity(this, part_name, 0);
		
		SetStorageState( CheckStorageState() );

		//update visuals (server)
		UpdateVisuals();
	}

	//--- ATTACHMENT & CONDITIONS
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		if ( !super.CanReceiveAttachment(attachment, slotId) )
			return false;
		
		//manage action initiator (AT_ATTACH_TO_CONSTRUCTION)
		if ( !GetGame().IsDedicatedServer() )
		{
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			if ( player )
			{
				ConstructionActionData construction_action_data = player.GetConstructionActionData();
				
				//reset action initiator
				construction_action_data.SetActionInitiator( NULL );				
			}
		}
		
		//conditions
		if ( attachment.IsInherited( ATTACHMENT_COMBINATION_LOCK ) )
		{
			return ( HasLid() && !IsOpened() );
		}

		//*! MANAGE the slots so players can't leave planks and nails in the crate ::
		//* NEXT : Remove display of the attachment category
		//* NEXT : On part built (lid) -> Get all attachments and drop on at player's feets.
		if ( attachment.IsInherited( ATTACHMENT_PLANKS ) )
		{
			return !HasLid();
		}
		if( attachment.IsInherited( ATTACHMENT_NAILS ))
		{
			return !HasLid();
		}

		#ifdef CodeLock
		if (attachment.Type() == ATTACHMENT_CODE_LOCK && (!IsGate() || !GetDayZGame().GetCodeLockConfig().CanAttachToGates())) 
		{ 
			return false; 
		}
		#endif
		
		return true;
	}
	
	override bool CanBeRepairedToPristine()
	{
		return true;
	}
	
	//--- OPEN/CLOSE ACTIONS
	bool CanOpenLid()
	{
		#ifdef CodeLock
		if ( HasLid() && !HasCover() && !IsOpened() && !IsLocked() && !IsCodeLocked() )
		{
			return true;
		}
		#else

		if ( HasLid() && !HasCover() && !IsOpened() && !IsLocked() )
		{
			return true;
		}
		
		#endif

		return false;
	}
	
	bool CanCloseLid()
	{
		if ( HasLid() && IsOpened() && !HasCover() )
		{
			return true;
		}
		
		return false;
	}
	
	void OpenLid()
	{
		//server or single player
		if ( GetGame().IsServer() )
		{
			float value = LID_ROTATION_ANGLE_DEG;
			SetAnimationPhase( "BBS_Lid_Rotate", 				value );
			
			SetOpenedState( true );

			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( UpdateNavmesh, LID_ROTATION_TIME_APPROX, false );

			UpdateWeightStatus();
			
			//synchronize
			SynchronizeBaseState();
		}
		
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			//play sound
			SoundLidOpenStart();
		}
		
		
		//add check
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove(CheckLidClosed);
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( CheckLidOpened, 0, true );
	}
	
	void CloseLid()
	{
		//server or single player
		if ( GetGame().IsServer() )
		{
			float value = 0;
			SetAnimationPhase( "BBS_Lid_Rotate", 				value );
			
			SetOpenedState( false );

			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( UpdateNavmesh, LID_ROTATION_TIME_APPROX, false );

			UpdateWeightStatus();

			//synchronize
			SynchronizeBaseState();
		}
		
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			//play sound
			SoundLidCloseStart();
		}
		
		//add check
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove(CheckLidOpened);
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( CheckLidClosed, 0, true );
	}
	
	protected void CheckLidOpened()
	{
		if ( GetAnimationPhase( "BBS_Lid_Rotate" ) == LID_ROTATION_ANGLE_DEG )			//animation finished - open
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove( CheckLidOpened );
		}
	}
	
	protected void CheckLidClosed()
	{
		if ( GetAnimationPhase( "BBS_Lid_Rotate" ) == 0 )			//animation finished - closed
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Remove( CheckLidClosed );
		}
	}
	
	
	//--- ACTION CONDITIONS
	override bool IsPlayerInside( PlayerBase player, string selection )
	{

		return true;
	}
	
	override bool IsFacingPlayer( PlayerBase player, string selection )
	{

		return false;

	}
	
	override bool IsFacingCamera( string selection )
	{

		return false;
	
	}
	
	override bool HasProperDistance( string selection, PlayerBase player )
	{
		if ( MemoryPointExists( selection ) )
		{
			vector selection_pos = ModelToWorld( GetMemoryPointPos( selection ) );
			float distance = vector.Distance( selection_pos, player.GetPosition() );
			if ( distance >= MAX_ACTION_DETECTION_DISTANCE )
			{
				return false;
			}
		}
		
		return true;
	}
	
	override bool CanUseConstructionBuild()
	{
		return !IsOpened();
	}
	
	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundLidOpenStart()
	{
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			PlaySoundSet( m_SoundLid_Start, SOUND_LID_OPEN_START, 0.1, 0.1 );
		}
	}

	protected void SoundLidCloseStart()
	{
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			PlaySoundSet( m_SoundLid_Start, SOUND_LID_CLOSE_START, 0.1, 0.1 );
		}
	}

	protected void SoundLidCloseEnd()
	{
		//client or single player
		if ( !GetGame().IsDedicatedServer() )
		{
			PlaySoundSet( m_SoundLid_End, SOUND_LID_CLOSE_END, 0.0, 0.0 );
		}
	}
	
	void StorageAttachmentsSanityCheck()
	{

		ConstructionPart storageLid = GetConstruction().GetConstructionPart("bbs_lid");

		if( !storageLid.IsBuilt() )
		{
			HandleDropAttachment(GetCombinationLock());
		}
	}

	void HandleDropAttachment(ItemBase item)
	{

		CombinationLock lock;
		
		#ifdef CodeLock
		CodeLock codelock;
		if (Class.CastTo(codelock,item))
		{
			codelock.UnlockServer(null,this);
		}
		#endif

		if (Class.CastTo(lock,item))
		{
			lock.UnlockServer(null,this);
		}
		else if (item)//generic behaviour
		{
			GetInventory().DropEntity(InventoryMode.SERVER, this, item);
		}
	}

	void HandleDropAttachmentFromRaid(ItemBase item)
	{

		CombinationLock lock;

		#ifdef CodeLock
		CodeLock codelock;
		if (Class.CastTo(codelock,item))
		{
			codelock.UnlockServer(null,this);
		}
		#endif

		if (Class.CastTo(lock,item))
		{
			lock.SetHealth("","", 0);
			lock.UnlockServer(null,this);
			
		}
		else if (item)//generic behaviour
		{
			GetInventory().DropEntity(InventoryMode.SERVER, this, item);
		}
	}
	
	
	override void SetActions()
	{
		super.SetActions();

		RemoveAction(ActionFoldBaseBuildingObject);

		AddAction(ActionOpenStorageLid);

		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
		AddAction(ActionFoldR22R_BBS_BASE);

		

		//* CODELOCK STUFF :
		// Vanilla ::
		AddAction(ActionNextCombinationLockDialOnBBSBase);
        AddAction(ActionDialCombinationLockOnBBSBase);


		#ifdef CodeLock
		AddAction(ActionAttachCodeLockOnBBSBase);
        AddAction(ActionInteractLockOnBBSBase);
        AddAction(ActionManageLockOnBBSBase);
        AddAction(ActionLockAdminOnBBSBase);
        #endif

		//* END ::

		AddAction(ActionTakeItemToHands);

		AddAction(ActionCloseStorageLid);
	}
	
	//================================================================
	// DEBUG
	//================================================================	
	
	//! Excludes certain parts from being built by OnDebugSpawn, uses Contains to compare
	override array<string> OnDebugSpawnBuildExcludes()
	{
		array<string> excludes = {};
		
		#ifdef DIAG_DEVELOPER
		bool bWood = DiagMenu.GetBool(DiagMenuIDs.BASEBUILDING_WOOD);
		#else
		bool bWood = false;
		#endif
		
		if (bWood)
		{
			excludes.Insert("_metal_");
		}
		else
		{
			excludes.Insert("_wood_");
		}
		
		#ifdef DIAG_DEVELOPER
		bool bGate = DiagMenu.GetBool(DiagMenuIDs.BASEBUILDING_GATE);
		#else
		bool bGate = false;
		#endif
		
		if (bGate)
		{
			excludes.Insert("platform");
		}
		else
		{
			excludes.Insert("gate");
		}
		
		return excludes;
	}
			
	//Debug menu Spawn Ground Special
	override void OnDebugSpawn()
	{
		super.OnDebugSpawn();
	}
}


class R22R_BBS_LargeCrate extends R22R_BBS_Base{};
class R22R_BBS_SmallCrate extends R22R_BBS_Base
{
	override bool HasSmallInventory()
	{
		return true;
	}
};


class R22R_BBS_PlankStorage extends R22R_BBS_Base
{
	void R22R_BBS_PlankStorage()
	{
		m_IsDynamicStorage					= true;

		STORAGE_LOW							= 1;
		STORAGE_MEDIUM						= 6;
		STORAGE_HIGH						= 12;
		STORAGE_FULL						= 18;

		MAIN_STORAGE_SLOT					="Material_L1_20_WoodenPlanks";
	}
}


class R22R_BBS_WoodenlogStorage extends R22R_BBS_Base
{
	void R22R_BBS_WoodenlogStorage()
	{
		m_IsDynamicStorage					= true;

		STORAGE_LOW							= 1;
		STORAGE_MEDIUM						= 15;
		STORAGE_HIGH						= 30;
		STORAGE_FULL						= 45;

		MAIN_STORAGE_SLOT					="Material_L1_50_WoodenLogs";
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
}


class R22R_BBS_LumberStorage extends R22R_BBS_Base
{
	void R22R_BBS_LumberStorage()
	{
		m_IsDynamicStorage					= true;

		STORAGE_LOW							= 1;
		STORAGE_MEDIUM						= 15;
		STORAGE_HIGH						= 30;
		STORAGE_FULL						= 45;

		MAIN_STORAGE_SLOT					="Material_L1_50_Lumber";
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
}

class R22R_SlumShelter_1 extends R22R_BBS_Base
{
	void R22R_SlumShelter_1()
	{
		m_IsDynamicStorage					= false;
		m_IsStaticItem						= true;
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
}

