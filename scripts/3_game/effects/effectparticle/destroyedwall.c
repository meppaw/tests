class R22RDestroyedWall : EffectParticle
{
	void R22RDestroyedWall()
	{
		SetParticleID(ParticleList.EXPLOSION_LANDMINE);
	}
}

class R22RDismantledWall : EffectParticle
{
	void R22RDismantledWall()
	{
		int randomChoice = Math.RandomInt(1, 2);

		switch(randomChoice)
		{
			case 1:
				SetParticleID(ParticleList.SMOKE_GENERIC_WRECK);
				break;
			case 2:
				SetParticleID(ParticleList.BONFIRE_SMOKE);
				break;
			default:
				SetParticleID(ParticleList.BONFIRE_SMOKE);
				break;
		}
		
	}
}