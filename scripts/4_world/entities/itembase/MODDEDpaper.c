modded class Paper
{
	ref InventoryLocation m_TargetLocation = new InventoryLocation;

	InventoryLocation GetTargetLocation()
	{
		return m_TargetLocation;
	}

	void SetTargetLocation(InventoryLocation targetLocation)
	{
		m_TargetLocation.CopyLocationFrom(targetLocation, true);
	}
}