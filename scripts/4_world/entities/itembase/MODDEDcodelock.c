#ifdef CodeLock
modded class CodeLock : ItemBase
{

    void UnlockServerFromRaid( EntityAI player, EntityAI parent, bool ruinLock = true, bool isBaseBuilding = false )
	{
		Print("[R22RBaseFortificationsConfig] UnlockServerFromRaid -> Called.");
//		if (LogManager.IsBaseBuildingLogEnable()) bsbDebugPrint("[bsb] CombinationLock.UnlockServer " + " m_Combination=" + m_Combination + " m_CombinationLocked=" + m_CombinationLocked);
		if ( GetLockState() )
		{
			Print("[R22RBaseFortificationsConfig] UnlockServerFromRaid -> IsCodeLocked.");	
			
			//set slot unlock
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );

			if( isBaseBuilding )
			{
				Print("[R22RBaseFortificationsConfig] UnlockServerFromRaid -> isBaseBuilding");
				R22R_Wooden_Palisade_Gate_Base baseBuildingEntity = R22R_Wooden_Palisade_Gate_Base.Cast( parent );
				if( baseBuildingEntity )
					Print("[R22RBaseFortificationsConfig] UnlockServerFromRaid -> IsCodeLocked && isBaseBuilding && R22R_Wooden_Palisade_Gate_Base");
					baseBuildingEntity.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );	
			}
			else
			{
				R22R_BBS_Base storageItem = R22R_BBS_Base.Cast( parent );
				if( storageItem )
					Print("[R22RBaseFortificationsConfig] UnlockServerFromRaid -> IsCodeLocked && storageItem && R22R_BBS_Base");
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
			GetLockState();
		}	
		Print("[R22RBaseFortificationsConfig] UnlockServerFromRaid -> !IsCodeLocked.");
	}

    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionAttachCodeLockOnPalisadeGate);
        AddAction(ActionAttachCodeLockOnBBSBase);
    }
};
#endif


