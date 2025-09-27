class R22R_BaseBuildingBase_Kit extends KitBase
{
	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		if ( !super.CanReceiveAttachment(attachment, slotId) )
			return false;
		
		ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		if (att)
			return false;
		
		return true;
	}

	//================================================================
	// ADVANCED PLACEMENT
	//================================================================			
		
	override void OnPlacementComplete( Man player, vector position = "0 0 0", vector orientation = "0 0 0" )
	{
		super.OnPlacementComplete( player, position, orientation );
		
		if ( GetGame().IsServer() )
		{
			EntityAI itemFromKit = EntityAI.Cast(GetGame().CreateObjectEx(GetSpawnableItemFromConfig(this.GetType()), position, ECE_PLACE_ON_SURFACE));
			itemFromKit.SetPosition(position);
			itemFromKit.SetOrientation(orientation);

			BaseBuildingBase bb = BaseBuildingBase.Cast(itemFromKit);
			if( bb )
			{
				bb.m_ConstructionKitHealth = this.GetHealth01();
			}

			HideAllSelections();
		}	
	}
	
	override bool DoPlacingHeightCheck()
	{
		return true;
	}
	
	override float HeightCheckOverride()
	{
		return 2.54;
	}

	override string GetPlaceSoundset()
	{
		return "putDown_FenceKit_SoundSet";
	}

	override string GetLoopDeploySoundset()
	{
		return "";
	}

	override string GetDeploySoundset()
	{
		return "putDown_FenceKit_SoundSet";
	}
	
	

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached( item, slot_name );
/*		
		PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
		if ( player && player.IsPlayerDisconnected() )
			return;
*/
		if (item && slot_name == "Paper")
		{
			if (GetGame().IsServer() && !m_DeployedRegularly)
			{
				DisassembleKit(ItemBase.Cast(item));
				Delete();
			}
		}
	}

	override void AssembleKit()
	{
		if (!IsHologram())
		{
			Paper paper = Paper.Cast(GetInventory().CreateAttachment("Paper"));
		}
	}

	void CreatePaper(Paper paper)
	{
		if (!paper)
			return;
		
		InventoryLocation targetLoc = paper.GetTargetLocation();
		if (targetLoc && targetLoc.GetType() != InventoryLocationType.GROUND)
		{
			MiscGameplayFunctions.TransferItemProperties(this, paper);
			return;
		}
		
		EntityAI newPaper = EntityAI.Cast(GetGame().CreateObjectEx(paper.GetType(), GetPosition(), ECE_PLACE_ON_SURFACE));
		
		if (newPaper)
			MiscGameplayFunctions.TransferItemProperties(this, newPaper);
		
		paper.Delete();
	}
	
	override void DisassembleKit(ItemBase item)
	{
		TStringArray penList = {"Pen_Black","Pen_Blue","Pen_Green","Pen_Red"};

		int randomIndex = Math.RandomInt(0,penList.Count());

		string randomPen = penList[randomIndex];

		if (!IsHologram())
		{
			ItemBase pen = ItemBase.Cast(GetGame().CreateObjectEx(randomPen,GetPosition(),ECE_PLACE_ON_SURFACE));
			MiscGameplayFunctions.TransferItemProperties(this, pen);
			pen.SetQuantity(1);
			pen.AddHealth("","", -4); // 10hp
			Paper paper = Paper.Cast(item);
			CreatePaper(paper);
			paper.AddHealth("","", -6);  // 15hp
		}
	}
}

class R22R_BaseBuildingBase_KitPlacing extends ItemBase
{	
	
}

