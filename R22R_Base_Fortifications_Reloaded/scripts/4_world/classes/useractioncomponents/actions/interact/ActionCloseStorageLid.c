class ActionCloseStorageLid: ActionInteractBase
{
	void ActionCloseStorageLid()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.CloseDoors;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "Close";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject && targetObject.CanUseConstruction() )
		{
			R22R_BBS_Base storageUnit = R22R_BBS_Base.Cast( targetObject );
			string selection = storageUnit.GetActionComponentName(target.GetComponentIndex());
			
			if ( storageUnit && storageUnit.CanCloseLid() && ( selection.Contains("bbs_") || selection == "att_combinationlock") )
			{
				return true;
			}
		}
		return false;
	}

	override void OnStartServer( ActionData action_data )
	{
		R22R_BBS_Base storageUnit = R22R_BBS_Base.Cast( action_data.m_Target.GetObject() );
		storageUnit.CloseLid();
	}
}