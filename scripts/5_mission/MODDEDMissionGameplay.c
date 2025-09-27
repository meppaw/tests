modded class MissionGameplay
{
    // Register RPC
    void MissionGameplay()
    {
        GetRPCManager().AddRPC("RPC_R22RBBS", "RPC_ReceiveR22RBaseFortificationsConfigOnClient", this, SingeplayerExecutionType.Client);
    }

    // Receive config sent from server -> client
    void RPC_ReceiveR22RBaseFortificationsConfigOnClient(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (type == CallType.Client)
        {
            ref Param1<ref R22RStorageRaidClientConfig, bool> data;

            // If data fails to read, stop here.
            if (!ctx.Read(data))
            {
                Print("IMPORTANT ERROR: R22RBaseFortificationsConfig failed to be read on client! Please tell Stern he fucked up!");
                return;
            }
            Print("[R22RBaseFortificationsConfig] MissionGameplay -> RPC_ReceiveR22RBaseFortificationsConfigOnClient()");
            // Data received - sync to client config
            GetR22RBaseFortificationsConfig().ClientSyncConfig = data.param1;
        }
    }

    override void OnUpdate(float timeslice)
	{
        super.OnUpdate(timeslice);

        Man player_ = GetGame().GetPlayer();
		PlayerBase playerPB_ = PlayerBase.Cast(player_);
        UIScriptedMenu menu_ = m_UIManager.GetMenu();
        if (menu_ == NULL && playerPB_.IsPlacingLocal() && playerPB_.GetHologramLocal().GetParentEntity().PlacementCanBeRotated())
        {
            if (GetUApi().GetUApi().GetInputByName("HologramUP").LocalPress())//LocalPress,LocalHold, LocalHoldBegin
            {
                playerPB_.GetHologramLocal().AddProjectionHeight(0.1);
            }
            if (GetUApi().GetUApi().GetInputByName("HologramUP").LocalHold())//LocalPress,LocalHold, LocalHoldBegin
            {
                playerPB_.GetHologramLocal().AddProjectionHeight(0.025);
            }

            if (GetUApi().GetUApi().GetInputByName("HologramDown").LocalPress())
            {
                playerPB_.GetHologramLocal().SubtractProjectionHeight(0.1);
            }
            if (GetUApi().GetUApi().GetInputByName("HologramDown").LocalHold())
            {
                playerPB_.GetHologramLocal().SubtractProjectionHeight(0.025);
            }
        }
    }
}
