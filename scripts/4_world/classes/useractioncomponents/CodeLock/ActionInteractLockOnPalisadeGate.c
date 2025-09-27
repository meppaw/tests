#ifdef CodeLock
class ActionInteractLockOnPalisadeGate : ActionInteractBase
{
    protected string lockState;
    protected R22R_Wooden_Palisade_Gate_Base currentTarget;

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
            if (!GetDayZGame().GetCodeLockConfig().CanOpenAnywhere()) {
                string selection = gate.GetActionComponentName(target.GetComponentIndex());

                if (selection != "att_combinationlock") {
                    return false;
                }
            }
            codelock = CodeLock.Cast(gate.GetCodeLock());

            if (codelock) {
                bool isOwner = codelock.IsOwner(player.GetIdentity().GetId());
                bool isGuest = codelock.IsGuest(player.GetIdentity().GetId());
                
                if (codelock.GetLockState()) {
                    if (isOwner || isGuest) {
                        lockState = "Open Locked Door";
                    } else if (!codelock.HasNoOwner()) {
                        lockState = "Enter Passcode";
                    } else {
                        return false;
                    }
                } else {
                    lockState = "Set Passcode";
                }
                return true;
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        EntityAI targetObject = EntityAI.Cast(action_data.m_Target.GetObject());
        R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast(targetObject);
        CodeLock codelock;

        if (gate) {
            codelock = CodeLock.Cast(gate.GetCodeLock());

            if (codelock) {
                if (codelock.GetLockState()) {
                    if (!codelock.IsOwner(identity.GetId()) && !codelock.IsGuest(identity.GetId())) {
                        GetCLUIManager().ShowMenu(CLMENU.GUEST_CODE_MENU, ItemBase.Cast(targetObject));
                    }
                } else {
                    GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, ItemBase.Cast(targetObject));
                }
            }
        }
    }

    override void OnStartServer(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        R22R_Wooden_Palisade_Gate_Base gate = R22R_Wooden_Palisade_Gate_Base.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (gate) {
            codelock = CodeLock.Cast(gate.GetCodeLock());

            if (codelock) {
                if (codelock.GetLockState()) {
                    if (codelock.IsOwner(identity.GetId()) || codelock.IsGuest(identity.GetId())) {
                        GetCodeLockLogger().WriteLog("acceSS", action_data.m_Player.GetIdentity(), codelock.GetPosition());
                        gate.OpenGate();
                    }
                }
            }
        }
    }
}
#endif