modded class CombinationLock extends ItemBase
{
    // Helper method to cast parent to the base class
    private R22R_Wooden_Palisade_Gate_Base GetGateOrDoorBase(EntityAI parent)
    {
        return R22R_Wooden_Palisade_Gate_Base.Cast(parent);
    }

    private R22R_BBS_Base GetBBStorageItem(EntityAI parent)
    {
        return R22R_BBS_Base.Cast(parent);
    }

    override void UnlockServer(EntityAI player, EntityAI parent)
    {
        R22R_Wooden_Palisade_Gate_Base gateOrDoor = GetGateOrDoorBase(parent);
        R22R_BBS_Base storageItem = GetBBStorageItem(parent);

        PlayerBase playerB = PlayerBase.Cast( GetGame().GetPlayer() );

        if (IsLockAttached() && (gateOrDoor || storageItem))
        {
            InventoryLocation inventory_location = new InventoryLocation;

            GetInventory().GetCurrentInventoryLocation(inventory_location);

            if(gateOrDoor)
                gateOrDoor.GetInventory().SetSlotLock(inventory_location.GetSlot(), false);
                SetPosition(gateOrDoor.GetKitSpawnPosition());

            if(storageItem)
                storageItem.GetInventory().SetSlotLock(inventory_location.GetSlot(), false);
                SetPosition(storageItem.GetKitSpawnPosition()); 

            if (playerB)
                playerB.ServerDropEntity(this);

            else
                parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
/*
            if(gateOrDoor)
                SetPosition(gateOrDoor.GetKitSpawnPosition());

            if(storageItem)
                SetPosition(storageItem.GetKitSpawnPosition());  
*/            
            
            PlaceOnSurface();
            m_LockActionPerformed = LockAction.UNLOCKED;
            SetTakeable(true);
            Synchronize();
        }
        
        super.UnlockServer(playerB, parent);
    }

    override bool IsLockedOnGate()
    {
//        super.IsLockedOnGate();
        R22R_Wooden_Palisade_Gate_Base gateOrDoor = GetGateOrDoorBase(GetHierarchyParent());
        R22R_BBS_Base storageItem = GetBBStorageItem(GetHierarchyParent());

        if (gateOrDoor && IsLocked())
        {
            return true;
        }
        if (storageItem && IsLocked())
        {
            return true;
        }

        return super.IsLockedOnGate();
    }

    override bool IsLockAttached()
    {
//        super.IsLockAttached();
        R22R_Wooden_Palisade_Gate_Base gateOrDoor = GetGateOrDoorBase(GetHierarchyParent());
        R22R_BBS_Base storageItem = GetBBStorageItem(GetHierarchyParent());

        if(gateOrDoor || storageItem)
        {
            return true;
        }

        return super.IsLockAttached();;
            
    }

    void UnlockServerFromRaid( EntityAI player, EntityAI parent, bool ruinLock = true, bool isBaseBuilding = false )
	{
		if ( IsLockAttached() )
		{
			//set slot unlock
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );

            if( isBaseBuilding )
			{
				R22R_Wooden_Palisade_Gate_Base baseBuildingEntity = R22R_Wooden_Palisade_Gate_Base.Cast( parent );
				if( baseBuildingEntity )
					baseBuildingEntity.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );	
			}
			else
			{
				R22R_BBS_Base storageItem = R22R_BBS_Base.Cast( parent );
				if( storageItem )
					storageItem.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );	
			}
					
	
			//drop entity from attachment slot
			if (GetGame().IsMultiplayer())
			{
				if (player)
					player.ServerDropEntity(this);
				else
					parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
			}
			else 
			{
				if (player)
					player.LocalDropEntity(this);
				else
					parent.GetInventory().DropEntity(InventoryMode.LOCAL, parent, this);
			}
				
			if( isBaseBuilding )
			{
				SetPosition( baseBuildingEntity.GetKitSpawnPosition() );
			}
			else
			{
				SetPosition( storageItem.GetKitSpawnPosition() );
			}

            if( ruinLock )
            {
                AddHealth("","", -5000);
            }
            
			PlaceOnSurface();
			
			m_LockActionPerformed = LockAction.UNLOCKED;
			SetTakeable(true);
			CheckLockedStateServer();
			Synchronize();
		}
		
		//reset performed action
		//m_LockActionPerformed = LockAction.NONE;		
	}

    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionNextCombinationLockDialOnPalisadeGate);
        AddAction(ActionDialCombinationLockOnPalisadeGate);

        AddAction(ActionNextCombinationLockDialOnBBSBase);
        AddAction(ActionDialCombinationLockOnBBSBase);

    }
}
