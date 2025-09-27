

modded class ActionDismantlePart: ActionContinuousBase
{
		
	override protected bool DismantleCondition(PlayerBase player, ActionTarget target, ItemBase item, bool camera_check)
	{	
		if (player && !player.IsPlacingLocal() && !player.IsPlacingServer())
		{
			Object targetObject = target.GetObject();
			EntityAI targetEntity;
			if (targetObject && targetObject.CanUseConstruction())
			{
				//invalid if is gate and is locked
				if (Class.CastTo(targetEntity, targetObject) && (targetEntity.FindAttachmentBySlotName("Att_CombinationLock") || targetEntity.FindAttachmentBySlotName("Material_FPole_Flag")) )
					return false;
				
				string partName = targetObject.GetActionComponentName(target.GetComponentIndex());
				
				BaseBuildingBase baseBuilding = BaseBuildingBase.Cast(targetObject);
				Construction construction = baseBuilding.GetConstruction();		
				ConstructionPart constructionPart = construction.GetConstructionPartToDismantle(partName, item);
				
				if (constructionPart)
				{
					
					//invalid on gate if the gate is opened
					if (constructionPart.IsGate() && baseBuilding.IsOpened())
						return false;
					
					//camera and position checks
					bool checked = false;
					
					if (constructionPart.IsBase())
					{
						//* EXCEPTION :: For custom base building assets which only contain one "level" which is the base itself.
						//* By doing that, we prevent players from dismantling from OUTSIDE the wall even if IsBase returns true.
						//* We therefore make sure the wall / defense can only be dismantled from inside the base and needs to be properly raided.

						if(baseBuilding.IsKindOf("R22R_Basic_Defense_Wall") || baseBuilding.IsKindOf("R22R_Barricade_X") || baseBuilding.IsKindOf("R22R_BBS_Base") || baseBuilding.IsKindOf("R22R_Hesco_Base"))
						{
							if (!checked && baseBuilding.IsPlayerInside(player, partName))
							{
								//Camera check (client-only)
								if (camera_check)
								{
									if (GetGame() && (!GetGame().IsDedicatedServer()))
									{
										if (baseBuilding.IsFacingCamera(partName))
											return false;
									}
								}

								checked = true;
							}
						}
						//* Returns to default vanilla code ::
						else
						{
							checked = true;
						}
					}
						
					
					if (!checked && baseBuilding.IsPlayerInside(player, partName))
					{
						//Camera check (client-only)
						if (camera_check)
						{
							if (GetGame() && (!GetGame().IsDedicatedServer()))
							{
								if (baseBuilding.IsFacingCamera(partName))
									return false;
							}
						}

						checked = true;
					}

					if (checked)
					{
						ConstructionActionData constructionActionData = player.GetConstructionActionData();
						constructionActionData.SetTargetPart(constructionPart);
						
						return true;
					}
				}
			}
		}
		
		return false;
	}
	
}