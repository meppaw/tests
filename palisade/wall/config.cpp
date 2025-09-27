class CfgPatches
{
	class R22R_Wooden_Palisade
	{
		units[]=
		{
			"R22R_Wooden_Palisade"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Camping",
			"DZ_Gear_Crafting"
		};
	};
};
class CfgSlots
{
	class Slot_Material_WoodenLogs
	{
		name="Material_WoodenLogs";
		displayName="#STR_CfgWoodenLogs0";
		selection="Material_WoodenLogs";
		ghostIcon="set:dayz_inventory image:woodenlog";
		stackMax=20;
	};
};
class CfgVehicles
{
	class BaseBuildingBase;
	class R22R_Wooden_Palisade: BaseBuildingBase
	{
		scope=2;
		displayName="Wooden Palisade";
		descriptionShort="A sturdy wooden palisade. By Stern.";
		model="R22R_Base_Fortifications_Reloaded\palisade\wall\R22R_Palisade_Wall.p3d";
		bounding="bsphere";
		overrideDrawArea="3.0";
		forceFarBubble="true";
		handheld="false";
		lootCategory="Crafted";
		carveNavmesh=1;
		weight=10000;
		itemSize[]={6,6};
		physLayer="item_large";
		createProxyPhysicsOnInit="false";
		createdProxiesOnInit[]=
		{
			"Deployed"
		};
		mountables[]={};
		rotationFlags=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								""
							}
						},
						
						{
							0.69999999,
							
							{
								""
							}
						},
						
						{
							0.5,
							
							{
								""
							}
						},
						
						{
							0.30000001,
							
							{
								""
							}
						},
						
						{
							0,
							
							{
								""
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
			class DamageZones
			{
				class Body
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=0;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"body"
					};
					fatalInjuryCoef=-1;
				};
				class Material_L1_WoodenLogs
				{
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=53;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"Material_L1_WoodenLogs"
					};
					inventorySlots[]=
					{
						"Material_L1_WoodenLogs"
					};
					fatalInjuryCoef=-1;
				};
				class Material_L1_4_WoodenLogs
				{
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=53;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"Material_L1_4_WoodenLogs"
					};
					inventorySlots[]=
					{
						"Material_L1_4_WoodenLogs"
					};
					fatalInjuryCoef=-1;
				};
				class Material_L1_8_Lumber: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_8_Lumber"
					};
					inventorySlots[]=
					{
						"Material_L1_8_Lumber"
					};
				};
				class Material_L1_WoodenPlanks: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_WoodenPlanks"
					};
					inventorySlots[]=
					{
						"Material_L1_WoodenPlanks"
					};
				};
				class Material_L1_Nails: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_Nails"
					};
					inventorySlots[]=
					{
						"Material_L1_Nails"
					};
				};
				class Material_L1_3_WoodenLogs: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_3_WoodenLogs"
					};
					inventorySlots[]=
					{
						"Material_L1_3_WoodenLogs"
					};
				};
				class Material_L1_Rope: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_Rope"
					};
					inventorySlots[]=
					{
						"Material_L1_Rope"
					};
				};
				class Material_L2_3_WoodenLogs: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L2_3_WoodenLogs"
					};
					inventorySlots[]=
					{
						"Material_L2_3_WoodenLogs"
					};
				};
				class Material_L1_2_Rope: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_2_Rope"
					};
					inventorySlots[]=
					{
						"Material_L1_2_Rope"
					};
				};
				class Material_L1_Defense_WoodenLogs: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_Defense_WoodenLogs"
					};
					inventorySlots[]=
					{
						"Material_L1_Defense_WoodenLogs"
					};
				};
				class Material_L1_Defense_Sticks: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_Defense_Sticks"
					};
					inventorySlots[]=
					{
						"Material_L1_Defense_Sticks"
					};
				};
				class Material_L1_Defense_Rope: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_Defense_Rope"
					};
					inventorySlots[]=
					{
						"Material_L1_Defense_Rope"
					};
				};
				class Material_L1W1_Nails: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1W1_Nails"
					};
					inventorySlots[]=
					{
						"Material_L1W1_Nails"
					};
				};
				class Material_L1_6_WoodenLogs: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_6_WoodenLogs"
					};
					inventorySlots[]=
					{
						"Material_L1_6_WoodenLogs"
					};
				};
				class Material_L1_8_WoodenPlanks: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_8_WoodenPlanks"
					};
					inventorySlots[]=
					{
						"Material_L1_8_WoodenPlanks"
					};
				};
				class Material_L1W2_R22R_Rope: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1W2_R22R_Rope"
					};
					inventorySlots[]=
					{
						"Material_L1W2_R22R_Rope"
					};
				};
				class Material_L1_32_Nails: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_32_Nails"
					};
					inventorySlots[]=
					{
						"Material_L1_32_Nails"
					};
				};
				class Material_L1_5_MetalSheets: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_5_MetalSheets"
					};
					inventorySlots[]=
					{
						"Material_L1_5_MetalSheets"
					};
				};
				class Material_L1_24_Nails: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_24_Nails"
					};
					inventorySlots[]=
					{
						"Material_L1_24_Nails"
					};
				};
				class Material_L1_6_Lumber: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_6_Lumber"
					};
					inventorySlots[]=
					{
						"Material_L1_6_Lumber"
					};
				};
				class Material_L1_10_WoodenPlanks: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_10_WoodenPlanks"
					};
					inventorySlots[]=
					{
						"Material_L1_10_WoodenPlanks"
					};
				};
				class Material_L1_20_Nails: Material_L1_4_WoodenLogs
				{
					componentNames[]=
					{
						"Material_L1_20_Nails"
					};
					inventorySlots[]=
					{
						"Material_L1_20_Nails"
					};
				};
				class Level_1_Base
				{
					displayName="Palisade Base";
					componentNames[]=
					{
						"level_1_base"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=48000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Roof
				{
					displayName="Palisade Roof";
					componentNames[]=
					{
						"level_1_roof"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=48000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Roof_Stairway
				{
					displayName="Palisade Roof - Stairway";
					componentNames[]=
					{
						"level_1_roof_stairway"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=48000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Stairs
				{
					displayName="Palisade Stairs";
					componentNames[]=
					{
						"level_1_stairs"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=10000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Wall_1_Wood_Left
				{
					displayName="Palisade Wall - Left";
					componentNames[]=
					{
						"level_1_wall_1_wood_left"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=48000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Wall_1_Wood_Right
				{
					displayName="Palisade Wall - Right";
					componentNames[]=
					{
						"level_1_wall_1_wood_right"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=48000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Wall_1_Wood_Defense_Down
				{
					displayName="Palisade Wall Defense";
					componentNames[]=
					{
						"level_1_wall_1_wood_defense_down"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=12000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Wall_1_Wood_Defense_Up
				{
					displayName="Palisade Wall Defense";
					componentNames[]=
					{
						"level_1_wall_1_wood_defense_up"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=12000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Wall_1_Wood_T2
				{
					displayName="Reinforced Palisade Wall";
					componentNames[]=
					{
						"level_1_wall_1_wood_t2"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=40000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_1_Wall_1_Wood_T3
				{
					displayName="Metal Reinforced Palisade Wall";
					componentNames[]=
					{
						"level_1_wall_1_wood_t3"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=40000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_2_Base
				{
					displayName="Upper Wooden Wall Base";
					componentNames[]=
					{
						"level_2_base"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=20000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_2_Wall_1_Wood
				{
					displayName="Upper Wooden Wall";
					componentNames[]=
					{
						"level_2_wall_1_wood"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=40000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
				class Level_2_Roof
				{
					displayName="Upper Wooden Wall Roof";
					componentNames[]=
					{
						"level_2_roof"
					};
					fatalInjuryCoef=-1;
					class Health
					{
						hitpoints=20000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_worn.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks_bdamage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"hidden"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
			};
		};
		attachments[]=
		{
			"Material_L1_4_WoodenLogs",
			"Material_L1_8_Lumber",
			"Material_L1_WoodenPlanks",
			"Material_L1_Nails",
			"Material_L1_3_WoodenLogs",
			"Material_L1_Rope",
			"Material_L2_3_WoodenLogs",
			"Material_L1_2_Rope",
			"Material_L1_Defense_WoodenLogs",
			"Material_L1_Defense_Sticks",
			"Material_L1_Defense_Rope",
			"Material_L1W1_Nails",
			"Material_L1_6_WoodenLogs",
			"Material_L1_8_WoodenPlanks",
			"Material_L1W2_R22R_Rope",
			"Material_L1_32_Nails",
			"Material_L1_5_MetalSheets",
			"Material_L1_24_Nails",
			"Material_L1_6_Lumber",
			"Material_L1_10_WoodenPlanks",
			"Material_L1_20_Nails"
		};
		class GUIInventoryAttachmentsProps
		{
			class Level_1
			{
				name="Palisade Base";
				description="";
				attachmentSlots[]=
				{
					"Material_L1_4_WoodenLogs",
					"Material_L1_8_Lumber",
					"Material_L1_WoodenPlanks",
					"Material_L1_Nails"
				};
				icon="set:dayz_inventory image:cat_bb_watchtower_wall_2";
				selection="level_1";
			};
			class Level_1_Wall_1
			{
				name="Palisade Walls";
				description="";
				attachmentSlots[]=
				{
					"Material_L1_3_WoodenLogs",
					"Material_L1_Rope",
					"Material_L2_3_WoodenLogs",
					"Material_L1_2_Rope"
				};
				icon="set:dayz_inventory image:cat_bb_watchtower";
				selection="level_1_wall_1";
			};
			class Wall_Defense
			{
				name="Palisade Defense";
				description="";
				attachmentSlots[]=
				{
					"Material_L1_Defense_WoodenLogs",
					"Material_L1_Defense_Sticks",
					"Material_L1_Defense_Rope",
					"Material_L1W1_Nails"
				};
				icon="set:dayz_inventory image:cat_bb_watchtower";
				selection="wall_defense";
			};
			class Tier_2
			{
				name="Reinforced Palisade Wall";
				description="";
				attachmentSlots[]=
				{
					"Material_L1_6_WoodenLogs",
					"Material_L1_8_WoodenPlanks",
					"Material_L1W2_R22R_Rope",
					"Material_L1_32_Nails"
				};
				icon="set:dayz_inventory image:cat_bb_watchtower";
				selection="level_1_wall_1";
			};
			class Tier_3
			{
				name="Metal Reinforced Palisade Wall";
				description="";
				attachmentSlots[]=
				{
					"Material_L1_5_MetalSheets",
					"Material_L1_24_Nails"
				};
				icon="set:dayz_inventory image:cat_bb_watchtower";
				selection="level_1_wall_1";
			};
			class Level_2
			{
				name="Upper Palisade Wall";
				description="";
				attachmentSlots[]=
				{
					"Material_L1_6_Lumber",
					"Material_L1_10_WoodenPlanks",
					"Material_L1_20_Nails"
				};
				icon="set:dayz_inventory image:cat_bb_watchtower_wall_2";
				selection="level_2";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Deployed: AnimSourceHidden
			{
			};
			class Level_1: AnimSourceHidden
			{
			};
			class Level_1_Base: AnimSourceHidden
			{
			};
			class Level_1_Roof: AnimSourceHidden
			{
			};
			class Level_1_Roof_Stairway: AnimSourceHidden
			{
			};
			class Level_1_Stairs: AnimSourceHidden
			{
			};
			class Level_1_Wall_1: AnimSourceHidden
			{
			};
			class Level_1_Wall_1_Wood_Left: AnimSourceHidden
			{
			};
			class Level_1_Wall_1_Wood_Right: AnimSourceHidden
			{
			};
			class Level_1_Wall_1_Wood_Defense_Down: AnimSourceHidden
			{
			};
			class Level_1_Wall_1_Wood_Defense_Up: AnimSourceHidden
			{
			};
			class Level_1_Wall_1_Wood_T2: AnimSourceHidden
			{
			};
			class Level_1_Wall_1_Wood_T3: AnimSourceHidden
			{
			};
			class Level_2: AnimSourceHidden
			{
			};
			class Level_2_Base: AnimSourceHidden
			{
			};
			class Level_2_Wall_1_Wood: AnimSourceHidden
			{
			};
			class Level_2_Roof: AnimSourceHidden
			{
			};
		};
		class Construction
		{
			class level_1
			{
				class level_1_base
				{
					name="Palisade Base";
					id=1;
					is_base=1;
					platform_support="level_1";
					required_parts[]={};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_stairs_min",
						"level_1_stairs_max"
					};
					build_action_type=4;
					dismantle_action_type=4;
					material_type=1;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_L1_4_WoodenLogs";
							quantity=4;
							lockable=1;
						};
					};
				};
				class level_1_roof_stairway
				{
					name="Palisade Walkway - Staircase";
					id=2;
					required_parts[]=
					{
						"level_1_base",
						"level_1_roof"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_roof_stairway_min",
						"level_1_roof_stairwayf_max"
					};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_WoodenPlanks";
							quantity=10;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_Nails";
							quantity=20;
						};
						class Material3
						{
							type="R22R_Lumber";
							slot_name="Material_L1_8_Lumber";
							quantity=8;
						};
					};
				};
				class level_1_stairs
				{
					name="Palisade Stairs";
					id=3;
					required_parts[]=
					{
						"level_1_base",
						"level_1_roof_stairway"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_stairs_min",
						"level_1_stairs_max"
					};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=3;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_WoodenPlanks";
							quantity=10;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_Nails";
							quantity=20;
						};
						class Material3
						{
							type="R22R_Lumber";
							slot_name="Material_L1_8_Lumber";
							quantity=2;
						};
					};
				};
				class level_1_roof
				{
					name="Palisade Walkway";
					id=4;
					required_parts[]=
					{
						"level_1_base"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_roof_min",
						"level_1_roof_max"
					};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_WoodenPlanks";
							quantity=10;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_Nails";
							quantity=20;
						};
						class Material3
						{
							type="R22R_Lumber";
							slot_name="Material_L1_8_Lumber";
							quantity=4;
						};
					};
				};
			};
			class level_1_wall_1
			{
				class level_1_wall_1_wood_left
				{
					name="Palisade Wall - Left";
					id=5;
					required_parts[]=
					{
						"level_1_base"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_wall_1_wood_left_min",
						"level_1_wall_1_wood_left_max"
					};
					build_action_type=4;
					dismantle_action_type=4;
					material_type=1;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_L1_3_WoodenLogs";
							quantity=3;
							lockable=1;
						};
						class Material2
						{
							type="Rope";
							slot_name="Material_L1_Rope";
							quantity=-1;
							lockable=1;
						};
					};
				};
				class level_1_wall_1_wood_right
				{
					name="Palisade Wall - Right";
					id=6;
					required_parts[]=
					{
						"level_1_base"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_wall_1_wood_right_min",
						"level_1_wall_1_wood_right_max"
					};
					build_action_type=4;
					dismantle_action_type=4;
					material_type=1;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_L2_3_WoodenLogs";
							quantity=3;
							lockable=1;
						};
						class Material2
						{
							type="Rope";
							slot_name="Material_L1_2_Rope";
							quantity=-1;
							lockable=1;
						};
					};
				};
				class level_1_wall_1_wood_defense_down
				{
					name="Lower Defense";
					id=7;
					required_parts[]=
					{
						"level_1_wall_1_wood_right",
						"level_1_wall_1_wood_left"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_wall_1_wood_defense_down_min",
						"level_1_wall_1_wood_defense_down_max"
					};
					build_action_type=4;
					dismantle_action_type=4;
					material_type=1;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_L1_Defense_WoodenLogs";
							quantity=3;
						};
						class Material2
						{
							type="Rope";
							slot_name="Material_L1_Defense_Rope";
							quantity=-1;
						};
					};
				};
				class level_1_wall_1_wood_defense_up
				{
					name="Upper Defense";
					id=8;
					required_parts[]=
					{
						"level_1_wall_1_wood_right",
						"level_1_wall_1_wood_left"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_1_wall_1_wood_defense_up_min",
						"level_1_wall_1_wood_defense_up_max"
					};
					build_action_type=8;
					dismantle_action_type=8;
					material_type=1;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_L1_Defense_WoodenLogs";
							quantity=1;
						};
						class Material2
						{
							type="WoodenStick";
							slot_name="Material_L1_Defense_Sticks";
							quantity=10;
						};
						class Material3
						{
							type="Rope";
							slot_name="Material_L1_Defense_Rope";
							quantity=-1;
						};
					};
				};
				class level_1_wall_1_wood_t2
				{
					name="Reinforced Wooden Wall";
					id=9;
					required_parts[]=
					{
						"level_1_wall_1_wood_right",
						"level_1_wall_1_wood_left"
					};
					conflicted_parts[]={};
					collision_data[]={};
					build_action_type=8;
					dismantle_action_type=8;
					material_type=1;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_L1_6_WoodenLogs";
							quantity=6;
							lockable=1;
						};
						class Material2
						{
							type="WoodenPlank";
							slot_name="Material_L1_8_WoodenPlanks";
							quantity=8;
							lockable=1;
						};
						class Material3
						{
							type="Rope";
							slot_name="Material_L1W2_R22R_Rope";
							quantity=-1;
							lockable=1;
						};
						class Material4
						{
							type="Nail";
							slot_name="Material_L1_32_Nails";
							quantity=32;
							lockable=1;
						};
					};
				};
				class level_1_wall_1_wood_t3
				{
					name="Reinforced Metal Wall";
					id=10;
					required_parts[]=
					{
						"level_1_wall_1_wood_t2"
					};
					conflicted_parts[]={};
					collision_data[]={};
					build_action_type=8;
					dismantle_action_type=8;
					material_type=1;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_L1_5_MetalSheets";
							quantity=5;
							lockable=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_24_Nails";
							quantity=24;
							lockable=1;
						};
					};
				};
			};
			class level_2
			{
				class level_2_base
				{
					name="Palisade Upper Base";
					id=11;
					platform_support="level_2";
					required_parts[]={};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_2_base_min",
						"level_2_base_max"
					};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=3;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_10_WoodenPlanks";
							quantity=10;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_20_Nails";
							quantity=20;
						};
						class Material3
						{
							type="R22R_Lumber";
							slot_name="Material_L1_6_Lumber";
							quantity=6;
						};
					};
				};
				class level_2_wall_1_wood
				{
					name="Palisade Upper Wall";
					id=12;
					required_parts[]=
					{
						"level_2_base"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_2_wall_1_wood_min",
						"level_2_wall_1_wood_max"
					};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=3;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_10_WoodenPlanks";
							quantity=10;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_20_Nails";
							quantity=20;
						};
						class Material3
						{
							type="R22R_Lumber";
							slot_name="Material_L1_6_Lumber";
							quantity=6;
						};
					};
				};
				class level_2_roof
				{
					name="Palisade Upper Wall Roof";
					id=13;
					required_parts[]=
					{
						"level_2_base"
					};
					conflicted_parts[]={};
					collision_data[]=
					{
						"level_2_wall_1_wood_min",
						"level_2_wall_1_wood_max"
					};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=3;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_L1_10_WoodenPlanks";
							quantity=10;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_L1_20_Nails";
							quantity=20;
						};
						class Material3
						{
							type="R22R_Lumber";
							slot_name="Material_L1_6_Lumber";
							quantity=6;
						};
					};
				};
			};
		};
	};
};
