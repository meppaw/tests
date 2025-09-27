class R22RNoBuildZoneArea: AreaDamageLoopedDeferred //AreaDamageManager
{
	override void OnEnterServerEvent(TriggerInsider insider)
	{
		super.OnEnterServerEvent(insider);
		Print("[R22R No Build Zones] -> Player has entered R22RNoBuildZoneArea.")
		EntityAI victim = EntityAI.Cast(insider.GetObject());
		PlayerBase player = PlayerBase.Cast(victim);
		if( player )
		{
			player.SetInNoBuildZone(true);
		}
		else
		{
			Print("[R22R No Build Zones] -> Could not cast player to victim.")
		}
		
	}
	override void OnLeaveServerEvent(TriggerInsider insider)
	{
		super.OnLeaveServerEvent(insider);
		Print("[R22R No Build Zones] -> Player has left an R22RNoBuildZoneArea.")
		EntityAI victim = EntityAI.Cast(insider.GetObject());
		PlayerBase player = PlayerBase.Cast(victim);
		if( player )
		{
			player.SetInNoBuildZone(false);
		}
		else
		{
			Print("[R22R No Build Zones] -> Could not cast player to victim.")
		}
	}
}