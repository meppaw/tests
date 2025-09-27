class R22RBaseFortificationsConfig
{
	// Static constant config version (is NOT saved to json)
	static const string CONFIG_VERSION = "3";

	// Config location
	private const static string r22rProfilesFolderPath = "$profile:\\R22R_Stern\\";
	private const static string r22rConfigFile = "R22RBaseFortificationsConfig.json";

	// Main config data
	string ConfigVersion = "";
	ref R22RStorageRaidClientConfig ClientSyncConfig; // Config that sync's to client

	// Load config file or create default file if config doesn't exsit
	void Load()
	{
		if (GetGame().IsDedicatedServer())
		{
			if (FileExist(r22rProfilesFolderPath + r22rConfigFile))
			{ 
				// If config exists, load file
				JsonFileLoader<R22RBaseFortificationsConfig>.JsonLoadFile(r22rProfilesFolderPath + r22rConfigFile, this);

				// If version mismatch, backup old version of json before replacing it
				if (ConfigVersion != CONFIG_VERSION)
				{
					JsonFileLoader<R22RBaseFortificationsConfig>.JsonSaveFile(r22rProfilesFolderPath + r22rConfigFile + "_old", this);
				}
				else
				{
					// Config exists and version matches, stop here.
					return;
				}
			}

			// Set new config version
			ConfigVersion = CONFIG_VERSION;

			// Set default config
			ClientSyncConfig = new R22RStorageRaidClientConfig;

			//* STORAGE RAIDING ::
			ClientSyncConfig.StorageRaidConfig = new R22RStorageRaidConfig;
			ClientSyncConfig.StorageRaidConfig.RaidItems = new array<ref RaidItemConfig>;

			//* BASE BUILDING RAIDING ::
			ClientSyncConfig.BaseRaidConfig = new R22RBaseRaidConfig;
			ClientSyncConfig.BaseRaidConfig.RaidItems = new array<ref RaidItemConfig>;
			ClientSyncConfig.BaseRaidConfig.BannedItemsInNoBuildZones = new array<ref BannedTypesInNoBuildZoneConfig>;

			ref RaidItemConfig raidItem1 = new RaidItemConfig;
			raidItem1.ItemType = "Lockpick";
			raidItem1.RaidTimeInSeconds = 45;
			raidItem1.AdditionalRaidTimeTier2 = 30;
			raidItem1.PercentHealthRemovedItem = 10;
			raidItem1.PercentChanceOfBreakingItem= 33;
			raidItem1.PercentChanceOfBreakingLoot = 5;
			raidItem1.MinPercentHealthDamageToLoot = 0;
			raidItem1.MaxPercentHealthDamageToLoot = 10;
			raidItem1.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem1);

			ref RaidItemConfig raidItem2 = new RaidItemConfig;
			raidItem2.ItemType = "Crowbar";
			raidItem2.RaidTimeInSeconds = 180; 
			raidItem2.AdditionalRaidTimeTier2 = 60;
			raidItem2.PercentHealthRemovedItem = 70;
			raidItem2.PercentChanceOfBreakingItem= 50;
			raidItem2.PercentChanceOfBreakingLoot = 90;
			raidItem2.MinPercentHealthDamageToLoot = 50;
			raidItem2.MaxPercentHealthDamageToLoot = 100;
			raidItem2.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem2);

			ref RaidItemConfig raidItem3 = new RaidItemConfig;
			raidItem3.ItemType = "Hatchet";
			raidItem3.RaidTimeInSeconds = 120;
			raidItem3.AdditionalRaidTimeTier2 = 60;
			raidItem3.PercentHealthRemovedItem = 100; 
			raidItem3.PercentChanceOfBreakingItem= 30;
			raidItem3.PercentChanceOfBreakingLoot = 60;
			raidItem3.MinPercentHealthDamageToLoot = 20;
			raidItem3.MaxPercentHealthDamageToLoot = 90;
			raidItem3.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem3);

			ref RaidItemConfig raidItem4 = new RaidItemConfig;
			raidItem4.ItemType = "Hacksaw";
			raidItem4.RaidTimeInSeconds = 90;
			raidItem4.AdditionalRaidTimeTier2 = 60;
			raidItem4.PercentHealthRemovedItem = 100; 
			raidItem4.PercentChanceOfBreakingItem= 20;
			raidItem4.PercentChanceOfBreakingLoot = 10;
			raidItem4.MinPercentHealthDamageToLoot = 10;
			raidItem4.MaxPercentHealthDamageToLoot = 30;
			raidItem4.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem4);

			ref RaidItemConfig raidItem5 = new RaidItemConfig;
			raidItem5.ItemType = "HandSaw";
			raidItem5.RaidTimeInSeconds = 90; 
			raidItem5.AdditionalRaidTimeTier2 = 60;
			raidItem5.PercentHealthRemovedItem = 100;
			raidItem5.PercentChanceOfBreakingItem= 20;
			raidItem5.PercentChanceOfBreakingLoot = 10;
			raidItem5.MinPercentHealthDamageToLoot = 10;
			raidItem5.MaxPercentHealthDamageToLoot = 30;
			raidItem5.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem5);

			ref RaidItemConfig raidItem6 = new RaidItemConfig;
			raidItem6.ItemType = "Pickaxe";
			raidItem6.RaidTimeInSeconds = 120;
			raidItem6.AdditionalRaidTimeTier2 = 60;
			raidItem6.PercentHealthRemovedItem = 80;
			raidItem6.PercentChanceOfBreakingItem= 50;
			raidItem6.PercentChanceOfBreakingLoot = 95;
			raidItem6.MinPercentHealthDamageToLoot = 30;
			raidItem6.MaxPercentHealthDamageToLoot = 100;
			raidItem6.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem6);

			ref RaidItemConfig raidItem7 = new RaidItemConfig;
			raidItem7.ItemType = "WoodAxe";
			raidItem7.RaidTimeInSeconds = 120; 
			raidItem7.AdditionalRaidTimeTier2 = 60;
			raidItem7.PercentHealthRemovedItem = 80;
			raidItem7.PercentChanceOfBreakingItem= 30;
			raidItem7.PercentChanceOfBreakingLoot = 40;
			raidItem7.MinPercentHealthDamageToLoot = 40;
			raidItem7.MaxPercentHealthDamageToLoot = 90;
			raidItem7.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem7);

			ref RaidItemConfig raidItem8 = new RaidItemConfig;
			raidItem8.ItemType = "FirefighterAxe";
			raidItem8.RaidTimeInSeconds = 120; 
			raidItem8.AdditionalRaidTimeTier2 = 60;
			raidItem8.PercentHealthRemovedItem = 80;
			raidItem8.PercentChanceOfBreakingItem= 20;
			raidItem8.PercentChanceOfBreakingLoot = 30;
			raidItem8.MinPercentHealthDamageToLoot = 10;
			raidItem8.MaxPercentHealthDamageToLoot = 60;
			raidItem8.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem8);

			ref RaidItemConfig raidItem9 = new RaidItemConfig;
			raidItem9.ItemType = "SledgeHammer";
			raidItem9.RaidTimeInSeconds = 180; 
			raidItem9.AdditionalRaidTimeTier2 = 60;
			raidItem9.PercentHealthRemovedItem = 40;
			raidItem9.PercentChanceOfBreakingItem= 40;
			raidItem9.PercentChanceOfBreakingLoot = 100;
			raidItem9.MinPercentHealthDamageToLoot = 30;
			raidItem9.MaxPercentHealthDamageToLoot = 100;
			raidItem9.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.StorageRaidConfig.RaidItems.Insert(raidItem9);



			//* BASE BUILDING RAIDING ::

			ref RaidItemConfig raidItem10 = new RaidItemConfig;
			raidItem10.ItemType = "SledgeHammer";
			raidItem10.RaidTimeInSeconds = 300; 
			raidItem10.AdditionalRaidTimeTier2 = 60;
			raidItem10.AdditionalRaidTimeTier3 = 180;
			raidItem10.PercentHealthRemovedItem = 40;
			raidItem10.PercentChanceOfBreakingItem= 40;
			raidItem10.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.BaseRaidConfig.RaidItems.Insert(raidItem10);

			ref RaidItemConfig raidItem11 = new RaidItemConfig;
			raidItem11.ItemType = "Pickaxe";
			raidItem11.RaidTimeInSeconds = 240; 
			raidItem11.AdditionalRaidTimeTier2 = 60;
			raidItem11.AdditionalRaidTimeTier3 = 180;
			raidItem11.PercentHealthRemovedItem = 40;
			raidItem11.PercentChanceOfBreakingItem= 40;
			raidItem11.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.BaseRaidConfig.RaidItems.Insert(raidItem11);

			ref RaidItemConfig raidItem12 = new RaidItemConfig;
			raidItem12.ItemType = "WoodAxe";
			raidItem12.RaidTimeInSeconds = 240; 
			raidItem12.AdditionalRaidTimeTier2 = 60;
			raidItem12.AdditionalRaidTimeTier3 = 180;
			raidItem12.PercentHealthRemovedItem = 40;
			raidItem12.PercentChanceOfBreakingItem= 40;
			raidItem12.EnableHealthAffectsRaiding = true;
			ClientSyncConfig.BaseRaidConfig.RaidItems.Insert(raidItem12);

			ref BannedTypesInNoBuildZoneConfig bannedItem1 = new BannedTypesInNoBuildZoneConfig;
			bannedItem1.ItemType = "R22R_Standalone_Staircase";
			ClientSyncConfig.BaseRaidConfig.BannedItemsInNoBuildZones.Insert(bannedItem1);

			ref BannedTypesInNoBuildZoneConfig bannedItem2 = new BannedTypesInNoBuildZoneConfig;
			bannedItem2.ItemType = "R22R_Standalone_Walkway";
			ClientSyncConfig.BaseRaidConfig.BannedItemsInNoBuildZones.Insert(bannedItem2);

			// Save config
			Save();
		}
	}

	// Save config
	void Save()
	{
		if (!FileExist(r22rProfilesFolderPath))
		{	
			// If config folder doesn't exist, create it.
			MakeDirectory(r22rProfilesFolderPath);
		}

		// Save JSON config
		JsonFileLoader<R22RBaseFortificationsConfig>.JsonSaveFile(r22rProfilesFolderPath + r22rConfigFile, this);
	}

	// Get raid config for given item type
	RaidItemConfig GetRaidConfigForType(string type, bool isBaseBuilding = false)
	{
		string toFind = type;
		toFind.ToLower();

		if( isBaseBuilding )
		{
			foreach (RaidItemConfig bb_config : ClientSyncConfig.BaseRaidConfig.RaidItems)
			{
				string bb_itemType = bb_config.ItemType;
				bb_itemType.ToLower();

				if (bb_itemType == toFind)
					return bb_config;
			}
		}
		else
		{
			foreach (RaidItemConfig config : ClientSyncConfig.StorageRaidConfig.RaidItems)
			{
				string lockType = config.ItemType;
				lockType.ToLower();

				if (lockType == toFind)
					return config;
			}
		}
		
		return NULL;
	}

	BannedTypesInNoBuildZoneConfig GetBannedItemConfigForType(string type)
	{
		string toFind = type;
		toFind.ToLower();
		
		foreach (BannedTypesInNoBuildZoneConfig config : ClientSyncConfig.BaseRaidConfig.BannedItemsInNoBuildZones)
		{
			string lockType = config.ItemType;
			lockType.ToLower();

			if (lockType == toFind)
				return config;
		}
		
		
		return NULL;
	}

}

// Config sync'd to client
class R22RStorageRaidClientConfig
{
	ref R22RStorageRaidConfig StorageRaidConfig;
	ref R22RBaseRaidConfig BaseRaidConfig;
};

// Raid config
class R22RStorageRaidConfig
{
	bool EnableStorageRaiding = true;
	bool EnableTier2StorageRaiding = true;
	ref array<ref RaidItemConfig> RaidItems;
};

class R22RBaseRaidConfig
{
	bool EnableBaseRaiding = true;
	bool EnableGateRaiding = true;
	bool EnableWallRaiding = true;
	bool EnableNoBuildZones = true;
	ref array<ref RaidItemConfig> RaidItems;
	ref array<ref BannedTypesInNoBuildZoneConfig> BannedItemsInNoBuildZones;
};

class RaidItemConfig
{
	string ItemType;
	int RaidTimeInSeconds;
	int AdditionalRaidTimeTier2;
	int AdditionalRaidTimeTier3;
	int PercentHealthRemovedItem;
	int PercentChanceOfBreakingItem;
	int PercentChanceOfBreakingLoot;
	int MinPercentHealthDamageToLoot;
	int MaxPercentHealthDamageToLoot;
	bool EnableHealthAffectsRaiding;
};

class BannedTypesInNoBuildZoneConfig
{
	string ItemType;
}

// Save config data
ref R22RBaseFortificationsConfig m_R22RBaseFortificationsConfig;

// Helper function to return Config data storage object
static R22RBaseFortificationsConfig GetR22RBaseFortificationsConfig()
{
	if (!m_R22RBaseFortificationsConfig)
	{
		Print("[R22RBaseFortificationsConfig] Init -> Got called sucessfully!");
		m_R22RBaseFortificationsConfig = new R22RBaseFortificationsConfig;

		// Only load JSON config on the server
		if (GetGame().IsServer())
		{
			m_R22RBaseFortificationsConfig.Load();
			Print("[R22RBaseFortificationsConfig] Init -> Loaded JSON on server!");
		}
	}

	return m_R22RBaseFortificationsConfig;
};