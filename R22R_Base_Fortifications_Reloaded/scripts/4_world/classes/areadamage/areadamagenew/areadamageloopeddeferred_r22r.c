class AreaDamageLoopedDeferred_R22R: AreaDamageLoopedDeferred
{
	override bool OnEvaluateDamageEx( TriggerInsider insider, float deltaTime )
	{
		// For case where player is inside vehicle 
		//EntityAI victim = insider.GetObject(); 

		EntityAI victim = EntityAI.Cast(insider.GetObject());

		// Create a random chance of breaking a zombie leg ::
		float legBreakChance = Math.RandomFloatInclusive(0, 1);
		float heavyDamageChance = Math.RandomFloatInclusive(0, 1);

		if( victim )
		{
			if ( victim.IsInherited(DayZCreatureAI) )
			{
				if( victim.IsInherited(DayZInfected) )
				{
					if( legBreakChance > 0.7 )
					{
						victim.SetHealth("LeftLeg", "", 0);
					}
					else
					{
						victim.SetHealth("", "", 0);
					}
					
				}
				else
				{
					victim.SetHealth("", "", 0);
				}
				
			}
			else if ( victim.IsInherited(SurvivorBase) )
			{

				if( legBreakChance > 0.9 )
				{
					victim.SetHealth("LeftLeg",	 "", 0);
				}
				if( heavyDamageChance > 0.8 )
				{
					victim.SetHealth("", "", 30);
				}
				
			}
		}
		
		return super.OnEvaluateDamageEx( insider, deltaTime );
	}
}