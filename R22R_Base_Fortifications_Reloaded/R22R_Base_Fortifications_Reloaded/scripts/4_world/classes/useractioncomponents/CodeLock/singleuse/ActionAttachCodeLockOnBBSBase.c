#ifdef CodeLock
class ActionAttachCodeLockOnBBSBase : ActionSingleUseBase
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
        R22R_BBS_Base storageItem = R22R_BBS_Base.Cast(target.GetObject());

        if (storageItem) {
            if (storageItem.HasLid()) {
                return true;
            }
            if (!GetDayZGame().GetCodeLockConfig().CanAttachToGates()) {
                return false;
            }
            if (!storageItem.IsCodeLocked()) {
                return true;
            }
        }
        return false; 
    }

    override void OnExecuteClient(ActionData action_data) 
    {
        R22R_BBS_Base storageItem = R22R_BBS_Base.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

		ClearInventoryReservationEx(action_data);

        if (storageItem) {
            int slotID = InventorySlots.GetSlotIdFromString(CLConst.clAttachment);

            action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx(storageItem, action_data.m_MainItem, slotID);
            GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, storageItem);
        }
    }

    override void OnExecuteServer(ActionData action_data) 
    {
        R22R_BBS_Base storageItem = R22R_BBS_Base.Cast(action_data.m_Target.GetObject());
        PlayerIdentity playerId = action_data.m_Player.GetIdentity();

        if (storageItem) {
            GetCodeLockLogger().WriteLog("attach", playerId, storageItem.GetPosition());
        }
    }
}
#endif