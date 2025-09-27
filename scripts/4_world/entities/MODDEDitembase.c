modded class ItemBase {


	//* Simply gets the item class from custom config line ::

	string GetSpawnableItemFromConfig(string itemName) {

		if( GetGame().ConfigIsExisting("CfgVehicles" + " " + itemName + " " + "createdItem") ) {
			return ConfigGetString("createdItem");
		}
		return "";
	}

	//* Gets the projection model from custom config ::
//	// NOT USED
	string GetProjectionModelFromConfig(string itemName) {

		if( GetGame().ConfigIsExisting("CfgVehicles" + " " + itemName + " " + "modelProjected") ) {
			return ConfigGetString("modelProjected");
		}
		return "";
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionRaidBBSBase);
		AddAction(ActionRaidBaseBuildingBase);
	}
};