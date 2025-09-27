#ifdef CodeLock
class ActionLockAdminOnPalisadeGate : ActionInteractBase
{
    protected string lockState;

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText() {
        return lockState;
    }

    override bool IsInstant() {
        return true;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast(target.GetObject());
        CodeLock codelock;

        if (gate && !gate.IsOpened()) {
            codelock = CodeLock.Cast(gate.GetCodeLock());

            if (codelock) {
                if (codelock.GetLockState()) {
                    if (GetCLPermissionManager().UserIsAdmin(player.GetIdentity().GetPlainId())) {
                        lockState = "Admin Lock";
                        return true;
                    }
                }
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (gate) {
            codelock = CodeLock.Cast(gate.GetCodeLock());

            if (codelock) {
                if (codelock.GetLockState()) {
                    if (GetCLPermissionManager().UserIsAdmin()) {
                        GetCLUIManager().ShowMenu(CLMENU.ADMIN_CODE_MENU, gate);
                    }
                }
            }
        }
    }
}
#endif