class R22R_Watchtower_Base extends BaseBuildingBase			//basebuilding
{
	typename ATTACHMENT_BARBED_WIRE			= BarbedWire;
	typename ATTACHMENT_CAMONET 			= CamoNet;
	
	const float MAX_FLOOR_VERTICAL_DISTANCE 		= 5.0;//0.5 -> 2.0
	const int MAX_CONSTRUCTION_ID					= 50;
	
	const float MIN_ACTION_DETECTION_ANGLE_RAD 		= 0.35;		//0.35 RAD = 20 DEG
	const float MAX_ACTION_DETECTION_DISTANCE 		= 2.0;		//meters
	
	static const string BASE_VIEW_NAME				= "level_";
	static const string BASE_WALL_NAME				= "_wall_";
	static const string BASE_ROOF_NAME				= "_roof";
	static const int	MAX_WATCHTOWER_FLOORS		= 3;
	static const int	MAX_WATCHTOWER_WALLS		= 3;

	const string ATTACHMENT_SLOT_COMBINATION_LOCK 	= "Att_CombinationLock";

	ref protected Effect 		m_Smoke;

	ref map<string, ref AreaDamageManager> m_R22RDamageTriggers;
	ref array<string> m_PartsWithDamageTriggers = {
			"level_1_wall_1_wood_defense_down",
			"level_1_wall_1_wood_defense_up",
			"level_3_wall_1_roof_defense",
			"level_2_wall_2_roof_defense",
			"level_1_wall_1_defense_down",
			"level_1_wall_1_defense_up",
			
			//* CAMP
			"level_1_defense",
		};

	ref map<string, ref AreaDamageManager> m_R22RNoBuildZoneTriggers;

	//! TODO :: Review the use of "UpdatePhysics" ::

	void R22R_Watchtower_Base()
	{
		m_R22RDamageTriggers = new ref map<string, ref AreaDamageManager>;
		m_R22RNoBuildZoneTriggers = new ref map<string, ref AreaDamageManager>;
		

		if ( GetGame().IsServer() )
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( GenerateDamageAreasPostRestart, 30000, false );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( CreateNoBuildZone, 30000, false );
		}
	}

	void ~R22R_Watchtower_Base()
	{
		foreach (AreaDamageManager areaDamage : m_R22RDamageTriggers)
		{
			areaDamage.Destroy();
		}
		foreach (AreaDamageManager areaNoBuild : m_R22RNoBuildZoneTriggers)
		{
			areaNoBuild.Destroy();
		}
		SEffectManager.DestroyEffect(m_Smoke);
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);

		foreach (AreaDamageManager areaDamage : m_R22RDamageTriggers)
		{
			areaDamage.Destroy();
		}
		foreach (AreaDamageManager areaNoBuild : m_R22RNoBuildZoneTriggers)
		{
			areaNoBuild.Destroy();
		}
		
	}

	bool IsGate()
	{
		return false;
	}

	bool IsLocked()
	{
		return false;
	}

	CombinationLock GetCombinationLock()
	{
		CombinationLock combination_lock = CombinationLock.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_COMBINATION_LOCK ) );
		return combination_lock;
	}

	void HandleDropAttachment(ItemBase item)
	{
		CombinationLock lock;
		if (Class.CastTo(lock,item))
		{
			lock.UnlockServer(null,this);
		}
		else if (item)//generic behaviour
		{
			GetInventory().DropEntity(InventoryMode.SERVER, this, item);
		}
	}
	
	override string GetConstructionKitType()
	{
		//return "R22R_Watchtower_Kit";
		return this.GetType() + "_Kit";
	}

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

    override int GetMeleeTargetType()
	{
		return EMeleeTargetType.NONALIGNABLE;
	}

	//overriden for the express purpose of handling view geometry (interaction) animations
	override void UpdateVisuals()
	{
		super.UpdateVisuals();
		
		SetAnimationPhase( "level_1", 0); //always visible
		SetAnimationPhase( "level_1_wall_1", 0); //always visible
		SetAnimationPhase( "level_1_wall_2", 0); //always visible
		SetAnimationPhase( "level_1_wall_3", 0); //always visible
		
		string part_name = "";
		bool built = false;
		
		for ( int i = 1; i < MAX_WATCHTOWER_FLOORS; ++i )
		{
			//roof checks
			part_name = "" + BASE_VIEW_NAME + i + BASE_ROOF_NAME;
			built = GetConstruction().IsPartConstructed(part_name);
			//Print(part_name);
			//Print(built);
			
			//string tmp = "";
			
			if ( built )
			{
				SetAnimationPhase( BASE_VIEW_NAME + (i + 1), 0); //show
				for ( int j = 1; j < MAX_WATCHTOWER_WALLS + 1; ++j )
				{
					//tmp = BASE_VIEW_NAME + (i + 1) + BASE_WALL_NAME + j;
					//Print(tmp);
					SetAnimationPhase( BASE_VIEW_NAME + (i + 1) + BASE_WALL_NAME + j, 0); //show
				}
			}
			else
			{
				SetAnimationPhase( BASE_VIEW_NAME + (i + 1), 1 ); //hide
				for ( j = 1; j < MAX_WATCHTOWER_WALLS + 1; ++j )
				{
					//tmp = BASE_VIEW_NAME + (i + 1) + BASE_WALL_NAME + j;
					//Print(tmp);
					SetAnimationPhase( BASE_VIEW_NAME + (i + 1) + BASE_WALL_NAME + j, 1); //hide
				}
			}
		}
	}
	
	//--- ATTACHMENT & CONDITIONS
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		if ( !super.CanReceiveAttachment( attachment, slotId ) )
			return false;

		//because CanReceiveAttachment() method can be called on all clients in the vicinity, vertical distance check needs to be skipped on clients that don't
		//interact with the object through attach action (AT_ATTACH_TO_CONSTRUCTION)
		PlayerBase player;
		if ( !GetGame().IsDedicatedServer() )
		{
			//check action initiator (AT_ATTACH_TO_CONSTRUCTION)
			player = PlayerBase.Cast( GetGame().GetPlayer() );
			if ( player )
			{
				ConstructionActionData construction_action_data = player.GetConstructionActionData();
				PlayerBase action_initiator = construction_action_data.GetActionInitiator();
				
				if ( action_initiator == player )			
				{
					construction_action_data.SetActionInitiator( NULL );				//reset action initiator
				}
				else
				{
					player = null;					//do not do vertical check (next)
				}
			}
		}
		//
			
		return CheckSlotVerticalDistance( slotId, player );
	}
	
	//can put into hands
	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
	
	override bool CanBeRepairedToPristine()
	{
		return true;
	}

	override bool CanFoldBaseBuildingObject()
	{
		if ( GetConstruction().IsPartConstructed( "level_1_base" ) || GetInventory().AttachmentCount() > 0 )
		{
			return false;
		}
		
		return true;
	}
	
	override bool PerformRoofCheckForBase( string partName, PlayerBase player, out bool result )
	{
		if (CfgGameplayHandler.GetDisablePerformRoofCheck())
			return false;
		
		if (partName != "level_1_base" && partName != "level_2_base" && partName != "level_3_base" && partName != "level_3_roof")
		{
			return false;
		}
		
		vector center;
		vector orientation = GetOrientation();
		vector edge_length;
		vector min_max[2];
		ref array<Object> excluded_objects = new array<Object>;
		ref array<Object> collided_objects = new array<Object>;
		
		excluded_objects.Insert( this );
		excluded_objects.Insert( player );
		
		if ( partName == "level_2_base" )
		{
			min_max[0] = GetMemoryPointPos( "level_2_wall_1_down_min" );
			min_max[1] = GetMemoryPointPos( "level_2_roof_max" );
		}
		else if ( partName == "level_3_base" )
		{
			min_max[0] = GetMemoryPointPos( "level_3_wall_1_down_min" );
			min_max[1] = GetMemoryPointPos( "level_3_wall_2_up_max" );
		}
		else if ( partName == "level_3_roof" )
		{
			min_max[0] = GetMemoryPointPos( "level_3_roof_min" );
			min_max[1] = GetMemoryPointPos( "level_3_roof_max" );
		}
		else
		{
			//min_max[0] = GetMemoryPointPos( "level_1_wall_1_up_min" );
			//min_max[0] = GetMemoryPointPos( "level_1_wall_1_down_min" );
			min_max[0] = GetMemoryPointPos( "level_1_collisioncheck_min" );
			min_max[1] = GetMemoryPointPos( "level_1_roof_max" );
		}
		center = GetPosition();
		center[1] = center[1] + ( min_max[1][1] + min_max[0][1] ) / 2;
		
		edge_length[0] = min_max[1][0] - min_max[0][0];
		edge_length[2] = min_max[1][2] - min_max[0][2];
		edge_length[1] = min_max[1][1] - min_max[0][1];
		
		result = false;
		/*result = */GetGame().IsBoxCollidingGeometry( center, orientation, edge_length, ObjIntersectView, ObjIntersectGeom, excluded_objects, collided_objects );
		if ( collided_objects.Count() > 0 )
		{
			foreach ( Object o : collided_objects )
			{
				if (Building.Cast(o))
				{
					result = true;
				}
			}
		}
		return true;
	}
	
	// --- INVENTORY
	override bool CanDisplayAttachmentSlot( int slot_id )
	{
		//super
		if ( !super.CanDisplayAttachmentSlot( slot_id ) )
			return false;

		string slot_name = InventorySlots.GetSlotName(slot_id);
		slot_name.ToLower();
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );

		//base attachments
		if ( slot_name.Contains( "material_l1" ) || slot_name.Contains( "level_1_" ) )
		{
			if ( slot_name.Contains( "woodenlogs" ) )
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_1_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
		}
		else if ( slot_name.Contains( "material_l2" ) || slot_name.Contains( "level_2_" ) )
		{
			if ( slot_name.Contains( "woodenlogs" ) )
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_2", player );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_2_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_2", player );
			}
		}
		else if ( slot_name.Contains( "material_l3" ) || slot_name.Contains( "level_3_" ) )
		{
			if ( slot_name.Contains( "woodenlogs" ) )
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_3", player );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_3_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_3", player );
			}
		}
				
		return true;
	}

	override bool CanDisplayAttachmentCategory( string category_name )
	{
		//super
		if ( !super.CanDisplayAttachmentCategory( category_name ) )
			return false;
		//
	
		category_name.ToLower();
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );

		//* Custom Defense category ::
		if( category_name == "Wall_Defense" )
		{
			return ( GetConstruction().IsPartConstructed( "level_1_wall_1_wood_left" ) && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_center" ) && GetConstruction().IsPartConstructed( "level_1_wall_1_wood_right" ) ); 
		}

		//level 1
		if ( category_name.Contains( "level_1" ) )
		{
			if ( category_name.Contains( "level_1_" ) )
			{
				return GetConstruction().IsPartConstructed( "level_1_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
			else
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
		}
		//level 2
		if ( category_name.Contains( "level_2" ) )
		{
			if ( category_name.Contains( "level_2_" ) )
			{
				return GetConstruction().IsPartConstructed( "level_2_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_2", player );
			}
			else
			{
				return (GetConstruction().IsPartConstructed( "level_1_roof" ) || GetConstruction().IsPartConstructed( "level_1_roof_stairway" )) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_2", player );
			}
		}
		//level 3
		if ( category_name.Contains( "level_3" ) )
		{
			if ( category_name.Contains( "level_3_" ) )
			{
				return GetConstruction().IsPartConstructed( "level_3_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_3", player );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_2_roof" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_3", player );
			}
		}
		
		return true;
	}	
	
	//returns true if attachment slot position is within given range
	override bool CheckSlotVerticalDistance( int slot_id, PlayerBase player )
	{
		string slot_name;
		InventorySlots.GetSelectionForSlotId( slot_id , slot_name );		
		slot_name.ToLower();

		//wall attachments
		//level 1
		if ( slot_name.Contains( "material_l1" ) || slot_name.Contains( "level_1_" ) )
		{
			if ( slot_name.Contains( "woodenlogs" ) )
			{
				return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
			else
			{
				return GetConstruction().IsPartConstructed( "level_1_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_1", player );
			}
		}
		//level 2
		if ( slot_name.Contains( "material_l2" ) || slot_name.Contains( "level_2_" ) )
		{
			if ( slot_name.Contains( "material_l2w" ) || slot_name.Contains( "level_2_wall" ) )
			{
				return GetConstruction().IsPartConstructed( "level_2_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_2", player );
			}
			else
			{
				if ( slot_name.Contains( "woodenlogs" ) )
				{
					return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_2", player );
				}
				else
				{
					return (GetConstruction().IsPartConstructed( "level_1_roof" ) || GetConstruction().IsPartConstructed( "level_1_roof_stairway" ))  && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_2", player );
				}
			}
		}
		//level 3
		if ( slot_name.Contains( "material_l3" ) || slot_name.Contains( "level_3_" ) )
		{
			if ( slot_name.Contains( "material_l3w" ) || slot_name.Contains( "level_3_wall" ) )
			{
				return GetConstruction().IsPartConstructed( "level_3_base" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_3", player );
			}
			else
			{
				if ( slot_name.Contains( "woodenlogs" ) )
				{
					return CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_3", player );
				}
				else
				{
					return GetConstruction().IsPartConstructed( "level_2_roof" ) && CheckMemoryPointVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, "level_3", player );
				}
			}
		}		
	
		return true;		
	}
	
	//returns true if player->mem_point position is within given range
	override bool CheckMemoryPointVerticalDistance( float max_dist, string selection, PlayerBase player )
	{
		if ( player )
		{
			//check vertical distance
			vector player_pos = player.GetPosition();
			vector pos;
			
			if ( MemoryPointExists( selection ) )
			{
				pos = ModelToWorld( GetMemoryPointPos( selection ) );
			}
			
			if ( Math.AbsFloat( player_pos[1] - pos[1] ) <= max_dist )
			{
				return true;
			}
			else
			{
				return false;
			}
		}			

		return true;
	}	
	
	override bool CheckLevelVerticalDistance( float max_dist, string selection, PlayerBase player )
	{
		if ( player )
		{
			if ( selection.Contains( "level_1_" ) )
				return CheckMemoryPointVerticalDistance( max_dist, "level_1", player );
			
			if ( selection.Contains( "level_2_" ) )
				return CheckMemoryPointVerticalDistance( max_dist, "level_2", player );
			
			if ( selection.Contains( "level_3_" ) )
				return CheckMemoryPointVerticalDistance( max_dist, "level_3", player );
		}
		return false;
	}
	// ---	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		UpdateVisuals();
	}
	
	override void OnPartBuiltServer( notnull Man player, string part_name, int action_id )
	{
		super.OnPartBuiltServer( player, part_name, action_id );
		//update visuals (server)

		if ( m_PartsWithDamageTriggers.Find(part_name) != -1 )
		{
			CreateAreaDamage(part_name);
		}

		UpdateVisuals();
	}
	
	override void OnPartDismantledServer( notnull Man player, string part_name, int action_id )
	{
		super.OnPartDismantledServer( player, part_name, action_id );
		//update visuals (server)

		MiscGameplayFunctions.ThrowAllItemsInInventoryWithFakeVelocity(this, part_name, 0);

//		CreateSmokeEffectOnDismantle(player);

		if ( m_PartsWithDamageTriggers.Find(part_name) != -1 )
		{
			DestroyAreaDamage(part_name);
		}

		UpdateVisuals();
	}
	
	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
		super.OnPartDestroyedServer( player, part_name, action_id );
		//update visuals (server)

		MiscGameplayFunctions.ThrowAllItemsInInventoryWithFakeVelocity(this, part_name, 0);
		

		if ( m_PartsWithDamageTriggers.Find(part_name) != -1 )
		{
			DestroyAreaDamage(part_name);
		}
		
		UpdateVisuals();
	}

	override void OnPartDismantledClient( string part_name, int action_id )
	{
		//play sound
		super.OnPartDismantledClient(part_name,action_id );
		CreateSmokeEffectOnDismantle();

	}

	void CreateSmokeEffectOnDismantle(bool isDestroyed = false)
	{
		if(isDestroyed)
		{
			m_Smoke = new R22RDestroyedWall();
		}
		else
		{
			m_Smoke = new R22RDismantledWall();
		}
		SEffectManager.PlayOnObject(m_Smoke, this, "0.3 0.21 0.4", "270 0 0");
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( RemoveSmokeParticles, 3000, false );
	}

	void RemoveSmokeParticles()
	{
		SEffectManager.DestroyEffect(m_Smoke);
	}
	
	//--- ACTION CONDITIONS
	//returns dot product of player->construction direction based on existing/non-existing reference point
	override bool IsFacingPlayer( PlayerBase player, string selection )
	{
		vector ref_pos;
		vector ref_dir;
		vector player_dir;
		float dot;
		bool has_memory_point = MemoryPointExists( selection );
		
		if ( has_memory_point )
		{
			ref_pos = ModelToWorld( GetMemoryPointPos( selection ) );
			ref_dir = ref_pos - GetPosition();
		}
		else
		{
			ref_pos = GetPosition();
			ref_dir = ref_pos - player.GetPosition();
		}
		
		ref_dir.Normalize();
		ref_dir[1] = 0;				//ignore height
		
		player_dir = player.GetDirection();
		player_dir.Normalize();
		player_dir[1] = 0;			//ignore height
		
		if ( ref_dir.Length() != 0 )
		{
			dot = vector.Dot( player_dir, ref_dir );
		}
		
		if ( has_memory_point )
		{
			if ( dot < 0 && Math.AbsFloat( dot ) > MIN_ACTION_DETECTION_ANGLE_RAD )
			{
				return true;
			}
		}
		else
		{
			if ( dot > 0 && Math.AbsFloat( dot ) > MIN_ACTION_DETECTION_ANGLE_RAD )
			{
				return true;
			}
		}
		
		return false;
	}
		
	override bool IsFacingCamera( string selection )
	{
		vector ref_pos;
		vector ref_dir;
		vector cam_dir = GetGame().GetCurrentCameraDirection();
		
		if ( MemoryPointExists( selection ) )
		{
			ref_pos = ModelToWorld( GetMemoryPointPos( selection ) );
			ref_dir = ref_pos - GetPosition();
			
			ref_dir.Normalize();
			ref_dir[1] = 0;		//ignore height
			
			cam_dir[1] = 0;		//ignore height
			
			if ( ref_dir.Length() > 0.5 )		//if the distance (m) is too low, ignore this check
			{
				float dot = vector.Dot( cam_dir, ref_dir );
			
				if ( dot < 0 )	
				{
					return true;
				}
			}
		}

		return false;
	}
	
	override bool IsPlayerInside( PlayerBase player, string selection )
	{
		if ( selection != "")
		{
			CheckLevelVerticalDistance( MAX_FLOOR_VERTICAL_DISTANCE, selection, player );
		}
		vector player_pos = player.GetPosition();
		vector tower_pos = GetPosition();
		vector ref_dir = GetDirection();
		ref_dir[1] = 0;
		ref_dir.Normalize();
		
		vector min,max;
		
		min = -GetMemoryPointPos( "interact_min" );
		max = -GetMemoryPointPos( "interact_max" );
		
		vector dir_to_tower = tower_pos - player_pos;
		dir_to_tower[1] = 0;
		float len = dir_to_tower.Length();
		

		dir_to_tower.Normalize();
		
		vector ref_dir_angle = ref_dir.VectorToAngles();
		vector dir_to_tower_angle = dir_to_tower.VectorToAngles();
		vector test_angles = dir_to_tower_angle - ref_dir_angle;
		
		vector test_position = test_angles.AnglesToVector() * len;
		
		if (test_position[0] > max[0] || test_position[0] < min[0] || test_position[2] > max[2] || test_position[2] < min[2] )
		{
			return false;
		}

		return true;
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

	//! Override of part sync ::

	//! END of override part sync ::


	//* DAMAGE TRIGGERS ::

	void GenerateDamageAreasPostRestart()
	{
        ref map<string, ref ConstructionPart> constructionParts = m_Construction.GetConstructionParts();
		
		//PlayerBase player = GetGame().GetPlayer();
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

		foreach (string partName, ref ConstructionPart part : constructionParts)
        {
            if (m_PartsWithDamageTriggers.Find(partName) != -1 && part.IsBuilt())
            {
                CreateAreaDamage(partName);
            }
        }
	}


	override void DestroyAreaDamage( string slot_name )
	{
		if (GetGame() && GetGame().IsServer())
		{
			super.DestroyAreaDamage( slot_name );
			
			AreaDamageLoopedDeferred_R22R areaDamage;
			if (m_R22RDamageTriggers.Find(slot_name, areaDamage))
			{
				if (areaDamage)
				{
					areaDamage.Destroy();
				}
				
				m_R22RDamageTriggers.Remove( slot_name );
			}
		}
	}


	override void CreateAreaDamage( string slot_name, float rotation_angle = 0 )
	{
		// Call SUPER before ::
		super.CreateAreaDamage( slot_name, rotation_angle );

		//destroy area damage if some already exists
		DestroyAreaDamage( slot_name );
		
		if ( GetGame() && GetGame().IsServer() )
		{
			vector min_max[2];

			//create new area damage
			AreaDamageLoopedDeferred_R22R areaDamage = new AreaDamageLoopedDeferred_R22R( this );
			areaDamage.SetDamageComponentType(AreaDamageComponentTypes.HITZONE);

			
			// Checks for the mem point + assign to vector ::
			if ( MemoryPointExists( slot_name + "_damage_min" ) )
			{
				min_max[0] = GetMemoryPointPos( slot_name + "_damage_min" );
			}
			if ( MemoryPointExists( slot_name + "_damage_max" ) )
			{
				min_max[1] = GetMemoryPointPos( slot_name + "_damage_max" );
			}

			
			
			//get proper trigger extents (min<max)
			vector extents[2];
			GetConstruction().GetTriggerExtents( min_max, extents );
			
			//get box center
			vector center;
			center = GetConstruction().GetBoxCenter( min_max );
			center = ModelToWorld( center );
			
			//rotate center if needed
			vector orientation = GetOrientation();
			CalcDamageAreaRotation( rotation_angle, center, orientation );
			
			areaDamage.SetExtents( extents[0], extents[1] );
			areaDamage.SetAreaPosition( center );
			areaDamage.SetAreaOrientation( orientation );
			areaDamage.SetLoopInterval( 1.0 );
			areaDamage.SetDeferDuration( 0.2 );
			areaDamage.SetHitZones( { "Torso","LeftHand","LeftLeg","LeftFoot","RightHand","RightLeg","RightFoot" } );
			areaDamage.SetAmmoName( "BarbedWireHit" );
			areaDamage.Spawn();
			
			m_R22RDamageTriggers.Insert( slot_name, areaDamage );
		}
	}

	void CreateNoBuildZone()
	{

		//destroy area damage if some already exists
		DestroyNoBuildZone( "NoBuildZoneGeneric" );
		
		if ( GetGame() && GetGame().IsServer() )
		{
			vector min_max[2];

			//create new area damage
			R22RNoBuildZoneArea areaDamage = new R22RNoBuildZoneArea( this );
			areaDamage.SetDamageComponentType(AreaDamageComponentTypes.HITZONE);

			
			// Checks for the mem point + assign to vector ::
			if ( MemoryPointExists( "nobuildzone_min" ) )
			{
				min_max[0] = GetMemoryPointPos( "nobuildzone_min" );
			}
			if ( MemoryPointExists( "nobuildzone_max" ) )
			{
				min_max[1] = GetMemoryPointPos( "nobuildzone_max" );
			}

			
			
			//get proper trigger extents (min<max)
			vector extents[2];
			GetConstruction().GetTriggerExtents( min_max, extents );
			
			//get box center
			vector center;
			center = GetConstruction().GetBoxCenter( min_max );
			center = ModelToWorld( center );
			
			//rotate center if needed
			vector orientation = GetOrientation();
			CalcDamageAreaRotation( 0, center, orientation );
			
			areaDamage.SetExtents( extents[0], extents[1] );
			areaDamage.SetAreaPosition( center );
			areaDamage.SetAreaOrientation( orientation );
			areaDamage.SetLoopInterval( 1.0 );
			areaDamage.SetDeferDuration( 0.2 );
			areaDamage.SetHitZones( { "Torso","LeftHand","LeftLeg","LeftFoot","RightHand","RightLeg","RightFoot" } );
			areaDamage.SetAmmoName( "" ); //BarbedWireHit
			areaDamage.Spawn();
			
			m_R22RDamageTriggers.Insert( "NoBuildZoneGeneric", areaDamage );
		}
	}

	void DestroyNoBuildZone(string zoneName)
	{
		if (GetGame() && GetGame().IsServer())
		{	
			AreaDamageLoopedDeferred_R22R areaDamage;
			if (m_R22RNoBuildZoneTriggers.Find(zoneName, areaDamage))
			{
				if (areaDamage)
				{
					areaDamage.Destroy();
				}
				
				m_R22RNoBuildZoneTriggers.Remove( zoneName );
			}
		}
	}
/*
	bool IsPlayerInNoBuildZone( PlayerBase player )
	{
		vector player_pos = player.GetPosition();
		vector wall_pos = GetPosition();
		vector ref_dir = GetDirection();
		ref_dir[1] = 0;
		ref_dir.Normalize();
		
		vector min,max;
		
		min = -GetMemoryPointPos( "nobuildzone_min" );
		max = -GetMemoryPointPos( "nobuildzone_max" );
		
		vector dir_to_wall = wall_pos - player_pos;
		dir_to_wall[1] = 0;
		float len = dir_to_wall.Length();
		

		dir_to_wall.Normalize();
		
		vector ref_dir_angle = ref_dir.VectorToAngles();
		vector dir_to_wall_angle = dir_to_wall.VectorToAngles();
		vector test_angles = dir_to_wall_angle - ref_dir_angle;
		
		vector test_position = test_angles.AnglesToVector() * len;
		
		if (test_position[0] > max[0] || test_position[0] < min[0] || test_position[2] > max[2] || test_position[2] < min[2] )
		{
			Print("[R22RNoBuidZone] -> Player is OUTSIDE of a no build zone for object " + this.GetType() + " located at " + this.GetPosition().ToString());
			return false;
		}

		return true;
		Print("[R22RNoBuidZone] -> Player is inside a no build zone for object " + this.GetType() + " located at " + this.GetPosition().ToString());
	}
*/

	//* END DAMAGE TRIGGERS ::
	
	override void SetActions()
	{
		super.SetActions();

		RemoveAction(ActionFoldBaseBuildingObject);
		
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
		AddAction(ActionFoldR22R_BBS_BASE);
	}	
}

class R22R_Wooden_Watchtower_1 extends R22R_Watchtower_Base{};
