#ifdef CodeLock
class ActionAttachCodeLockOnPalisadeGate : ActionSingleUseBase
{
    override void CreateConditionComponents() 
    {
        m_ConditionItem = new CCINonRuined;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText() 
    {
        return "Attach";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) 
    {
        R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast(target.GetObject());

        if (gate) {
            if (gate.IsGate()) {
                return true;
            }
            if (!GetDayZGame().GetCodeLockConfig().CanAttachToGates()) {
                return false;
            }
            if (!gate.IsCodeLocked()) {
                return true;
            }
        }
        return false; 
    }

    override void OnExecuteClient(ActionData action_data) 
    {
        R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

		ClearInventoryReservationEx(action_data);

        if (gate) {
            int slotID = InventorySlots.GetSlotIdFromString(CLConst.clAttachment);

            action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx(gate, action_data.m_MainItem, slotID);
            GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, gate);
        }
    }

    override void OnExecuteServer(ActionData action_data) 
    {
        R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast(action_data.m_Target.GetObject());
        PlayerIdentity playerId = action_data.m_Player.GetIdentity();

        if (gate) {
            GetCodeLockLogger().WriteLog("attach", playerId, gate.GetPosition());
        }
    }
}
#endif