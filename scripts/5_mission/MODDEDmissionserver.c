modded class MissionServer
{
	// Called when server initializes
	override void OnInit()
	{
		super.OnInit();
		Print("[R22RBaseFortificationsConfig] OnInit -> GetR22RBaseFortificationsConfig()");

		// Load config
		GetR22RBaseFortificationsConfig();
	}

	// Called when a player connects to the server
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity) 
	{
		super.InvokeOnConnect(player, identity);

		if (!player || !identity) 
			return;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SendBaseFortificationsConfig, 1, false, player);
	}

	void SendBaseFortificationsConfig(PlayerBase player)
	{
		if (!player || !player.GetIdentity())
			return;
		
		Param1<ref R22RStorageRaidClientConfig, bool> configParams = new Param1<ref R22RStorageRaidClientConfig, bool>(
			GetR22RBaseFortificationsConfig().ClientSyncConfig);

			
		GetRPCManager().SendRPC("RPC_R22RBBS", "RPC_ReceiveR22RBaseFortificationsConfigOnClient",configParams, true);
		Print("[R22RBaseFortificationsConfig] InvokeOnConnect -> GetRPCManager().SendRPC() -> SENT!");
	}
};