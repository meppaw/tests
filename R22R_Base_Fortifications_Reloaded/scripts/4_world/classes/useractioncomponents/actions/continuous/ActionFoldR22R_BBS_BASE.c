class ActionFoldR22R_BBS_BASECB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.DEFAULT_DEPLOY );
	}
}

class ActionFoldR22R_BBS_BASE: ActionContinuousBase
{
	void ActionFoldR22R_BBS_BASE()
	{
		m_CallbackClass = ActionFoldR22R_BBS_BASECB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_CRAFTING;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
		m_Text = "Undo Construction Plans";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
		m_ConditionItem = new CCINotPresent;
	}
	
	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		
		if ( targetObject.CanUseConstruction() )
		{
			
			R22R_BBS_Base base_building_storage = R22R_BBS_Base.Cast( targetObject );
			R22R_Watchtower_Base base_building = R22R_Watchtower_Base.Cast( targetObject );
		/*	
			if ( base_building_storage.CanFoldBaseBuildingObject() || base_building.CanFoldBaseBuildingObject() )
			{
				return true;
			}
		*/
			if( base_building_storage )
			{
				return base_building_storage.CanFoldBaseBuildingObject();
			}

			if( base_building )
			{
				return base_building.CanFoldBaseBuildingObject();
			}
		}
		
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		ItemBase item;
		R22R_Watchtower_Base base_building_storage = R22R_Watchtower_Base.Cast( action_data.m_Target.GetObject() );
		R22R_BBS_Base base_building = R22R_BBS_Base.Cast( action_data.m_Target.GetObject() );
		
		if(base_building_storage)
		{
			base_building_storage.CreateConstructionKitInHands(action_data.m_Player);
			base_building_storage.DestroyConstruction();
		}
		if(base_building)
		{
			base_building.CreateConstructionKitInHands(action_data.m_Player);
			base_building.DestroyConstruction();
		}
		
	}
	
	override string GetAdminLogMessage(ActionData action_data)
	{
		return " folded " + action_data.m_Target.GetObject().GetDisplayName();
	}
}