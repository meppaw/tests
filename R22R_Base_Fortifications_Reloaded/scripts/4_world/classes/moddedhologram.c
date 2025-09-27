modded class Hologram
{
	

	protected const float HEIGHT_INCREMENT = 0.1;


	//* Gets the class name of the projection needed ::
	override string GetProjectionName(ItemBase item)
	{
		R22R_BBS_Kit item_in_hands = R22R_BBS_Kit.Cast( item );
		if ( item_in_hands )
			return (item_in_hands.GetType() + "Placing");
		
		return super.GetProjectionName(item);
	}
/*
		UAInput hologramUpInput = GetUApi().GetInputByName("HologramUP");
    	UAInput hologramDownInput = GetUApi().GetInputByName("HologramDown");
*/
	void AddProjectionHeight( float addition )
	{
		vector projectionpos = GetProjectionPosition();
		projectionpos[1] = projectionpos[1] + addition;
		SetProjectionPosition(projectionpos);
	}

	void SubtractProjectionHeight( float subtraction )
	{	
		vector projectionpos = GetProjectionPosition();
		projectionpos[1] = projectionpos[1] - subtraction;
		SetProjectionPosition(projectionpos);
	}

	override void SetProjectionPosition(vector position)
	{
		m_Projection.SetPosition( position );
	/*	
		if (IsFloating())
		{
			m_Projection.SetPosition(SetOnGround(position));
		}
	*/
	}

	void SetProjectionPositionXZ(vector position)
	{
		vector currentPos = m_Projection.GetPosition();

		// Get the x, y, and z components as strings
		float x = position[0];
		float y = currentPos[1];
		float z = position[2];
		

		// Convert the string to a vector
		vector finalpos = Vector(x, y, z);

		// Set the position of the projection
		m_Projection.SetPosition(finalpos);
	}


	// update loop for visuals and collisions of the hologram
	override void UpdateHologram(float timeslice)
	{
		if (!m_Parent)
		{
			m_Player.TogglePlacingLocal();
			
			return;
		}
		
		if (IsRestrictedFromAdvancedPlacing())
		{
			m_Player.TogglePlacingLocal();
			
			return;
		}

		if (!GetUpdatePosition())
			return;
		
		
		#ifdef DIAG_DEVELOPER
		DebugConfigValues();
		DestroyDebugCollisionBox();
		#endif

		// update hologram position	
		SetProjectionPositionXZ(GetProjectionEntityPosition(m_Player));
		SetProjectionOrientation(AlignProjectionOnTerrain(timeslice));

		EvaluateCollision();
		RefreshTrigger();
		CheckPowerSource();
		RefreshVisual();

		m_Projection.OnHologramBeingPlaced(m_Player);
	}
}
