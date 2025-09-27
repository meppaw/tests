class ActionDialCombinationLockOnPalisadeGateCB : ActionContinuousBaseCB
{
	private const float REPEAT_AFTER_SEC = 0.5;
	
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(REPEAT_AFTER_SEC);
	}
}

class ActionDialCombinationLockOnPalisadeGate: ActionContinuousBase
{
	void ActionDialCombinationLockOnPalisadeGate()
	{
		m_CallbackClass = ActionDialCombinationLockOnPalisadeGateCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_LOW;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINotPresent;
		m_ConditionTarget = new CCTNone;
	}
	
	override bool HasProneException()
	{
		return true;
	}

	override string GetText()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		string combination_lock_text;
		
		if ( player )
		{
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			combination_lock_text = construction_action_data.GetDialNumberText();
		}

		return "#dial_combination_lock" + " " + combination_lock_text;	
	}

	override typename GetInputType()
	{
		return ContinuousInteractActionInput;
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		if ( targetObject && targetObject.CanUseConstruction() )
		{
			R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast( targetObject );
			 
			if ( gate && gate.IsLocked() )
			{
				string selection = gate.GetActionComponentName( target.GetComponentIndex() );
				
				if ( selection == "att_combinationlock" )
				{
					ConstructionActionData construction_action_data = player.GetConstructionActionData();
					construction_action_data.SetCombinationLock( gate.GetCombinationLock() );
					
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast( action_data.m_Target.GetObject() );
		if (gate)
		{
		
			ConstructionActionData construction_action_data = action_data.m_Player.GetConstructionActionData();
			CombinationLock combination_lock =  construction_action_data.GetCombinationLock();
			if ( combination_lock )
			{
				combination_lock.DialNextNumber();
	
				//check for unlock state
				if ( !combination_lock.IsLockedOnGate() )
				{
					EntityAI target_entity = EntityAI.Cast( action_data.m_Target.GetObject() );
					combination_lock.UnlockServer( action_data.m_Player, target_entity );
				}
			}
		}
	}
}