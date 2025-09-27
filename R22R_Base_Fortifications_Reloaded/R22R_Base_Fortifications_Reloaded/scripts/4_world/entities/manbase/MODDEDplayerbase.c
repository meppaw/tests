modded class PlayerBase
{
	protected bool 					m_IsInsideNoBuildZone;
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableBool("m_IsInsideNoBuildZone");
	}

	void SetInNoBuildZone(bool state)
	{
		if (m_IsInsideNoBuildZone != state)
		{
			m_IsInsideNoBuildZone = state;
			SetSynchDirty();
		}
	}

	bool IsInNoBuildZone()
	{
		return m_IsInsideNoBuildZone;
	}
};