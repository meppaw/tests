
/*
enum ThrowEntityFlags
{
	NONE = 0,
	SPLIT = 1, //< Splits the item when it has quantity, recommended to use when called on an attachment
}
*/
modded class MiscGameplayFunctions
{
	static void ThrowAllItemsInInventoryWithFakeVelocity(notnull BaseBuildingBase parent, string part_name, int flags )
	{
		ConstructionPart construction_part = parent.GetConstruction().GetConstructionPart( part_name );

		array<string> slot_names = new array<string>; //new array<string>

		vector fakeVelocity = "1 1 1";
		vector position = parent.GetPosition();
		vector orientation = parent.GetOrientation();
		vector rotation_matrix[3];
		vector randomPos;
		vector minmax[2];

		float direction[4];
		
		
		parent.GetCollisionBox(minmax);

		Math3D.YawPitchRollMatrix( orientation, rotation_matrix );
		Math3D.MatrixToQuat( rotation_matrix, direction );

		slot_names = GetSlotNamesForPart(parent, part_name);

		if( construction_part.IsBase() )
		{
			//* IF a part is a base, we want to remove ANY AND ALL materials ::
			//* This was added since sometimes players would store items in GUI slots of other, not yet built parts...
			//* This ensures that if a base part is removed, any material gets removed too.
			for ( int i = 0; i < parent.GetInventory().AttachmentCount(); ++i )
			{
				EntityAI attachment = parent.GetInventory().GetAttachmentFromIndex(i);
				if( attachment )
				{
					randomPos = Vector(position[0] + Math.RandomFloat(minmax[0][0], minmax[1][0]),
									position[1] + Math.RandomFloat(minmax[0][1], minmax[1][1]),
									position[2] + Math.RandomFloat(minmax[0][2], minmax[1][2]));
				
					ThrowEntityFromInventory(attachment, randomPos, direction, fakeVelocity, ThrowEntityFlags.NONE);
				}
			}
		}
		else
		{
			for ( int j = 0; j < slot_names.Count(); ++j )
			{
				EntityAI slotAttachment = parent.GetInventory().FindAttachmentByName(slot_names[j]);
				{
					if (slotAttachment)
					{
						randomPos = Vector(position[0] + Math.RandomFloat(minmax[0][0], minmax[1][0]) + 0.5,
										position[1] + Math.RandomFloat(minmax[0][1], minmax[1][1]) + 1,
										position[2] + Math.RandomFloat(minmax[0][2], minmax[1][2]) + 0.5 );
				
						ThrowEntityFromInventory(slotAttachment, randomPos, direction, fakeVelocity, ThrowEntityFlags.NONE);
					}
				}
			}
		}
	}


	static array<string> GetSlotNamesForPart(BaseBuildingBase parent, string part_name)
	{
		array<string> slot_names = new array<string>;
		ConstructionPart construction_part = parent.GetConstruction().GetConstructionPart( part_name );
		string main_part_name = construction_part.GetMainPartName();

		string path;
		int numberOfMaterialsFound;

		//* Config Stuff ::
		if( GetGame().ConfigIsExisting("CfgVehicles" + " " + parent.GetType() + " " + "Construction" + " " + main_part_name + " " + part_name + " " + "Materials" ))
		{
			path = "CfgVehicles" + " " + parent.GetType() + " " + "Construction" + " " + main_part_name + " " + part_name + " " + "Materials";

			int maxMaterialAmount = 6; //* JUST TO BE SAFE - I never use more than 6 ::
			for( int i = 0; i < maxMaterialAmount; ++i)
			{
				if(GetGame().ConfigIsExisting(path + " " + "Material" + i.ToString()))
				{
					string slotNameToAdd;
					string currentPath = path + " " + "Material" + i.ToString();
					slotNameToAdd = GetGame().ConfigGetTextOut(currentPath + " " + "slot_name");
					//slotNameToAdd = parent.ConfigGetString(currentPath + " " + "slot_name");

					if( slotNameToAdd.Length() > 0 )
					{
						slot_names.Insert(slotNameToAdd);
					}
				}
			}
		}

		return slot_names;
	}
}