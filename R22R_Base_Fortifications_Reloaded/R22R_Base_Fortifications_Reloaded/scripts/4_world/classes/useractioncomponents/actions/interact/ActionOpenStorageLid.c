class ActionOpenStorageLid: ActionInteractBase
{
	void ActionOpenStorageLid()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "Open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject && targetObject.CanUseConstruction() )
		{
			R22R_BBS_Base storageUnit = R22R_BBS_Base.Cast( targetObject );
			string selection = storageUnit.GetActionComponentName(target.GetComponentIndex());
			
			if ( storageUnit && storageUnit.CanOpenLid() && ( selection.Contains("bbs_") || selection == "att_combinationlock") )
			{
				return true;
			}
		}
		return false;
	}
	
	override void OnStartServer( ActionData action_data )
	{
		R22R_BBS_Base storageUnit = R22R_BBS_Base.Cast( action_data.m_Target.GetObject() );
		storageUnit.OpenLid();
	}
}