#ifdef CodeLock
class ActionManageLockOnBBSBase : ActionInteractBase
{
    protected string lockState;

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText() {
        return lockState;
    }

    override typename GetInputType() {
        return ContinuousInteractActionInput;
    }

    override bool HasProgress() {
        return false;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        R22R_BBS_Base storageItem = R22R_BBS_Base.Cast(target.GetObject());
        CodeLock codelock;

        if (storageItem && !storageItem.IsOpened()) {
            if (!GetDayZGame().GetCodeLockConfig().CanOpenAnywhere()) {
                string selection = storageItem.GetActionComponentName(target.GetComponentIndex());

                if (selection != "att_combinationlock") {
                    return false;
                }
            }
            codelock = CodeLock.Cast(storageItem.GetCodeLock());

            if (codelock) {
                bool isOwner = codelock.IsOwner(player.GetIdentity().GetId());
                bool isGuest = codelock.IsGuest(player.GetIdentity().GetId());
                
                if (codelock.GetLockState()) {
                    if (isOwner) {
                        lockState = "Manage Lock";
                        return true;
                    } else if (codelock.HasNoOwner()) {
                        lockState = "Claim Ownership";
                        return true;
                    }
                }
            }
        }
        return false;
    }

    override bool CanContinue(ActionData action_data) {
        return true;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        R22R_BBS_Base storageItem = R22R_BBS_Base.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (storageItem) {
            codelock = CodeLock.Cast(storageItem.GetCodeLock());

            if (codelock) {
                if (codelock.GetLockState()) {
                    if (codelock.IsOwner(identity.GetId())) {
                        GetCLUIManager().ShowMenu(CLMENU.ENTER_CODE_MENU, storageItem);
                    } else if (codelock.HasNoOwner()) {
                        GetCLUIManager().ShowMenu(CLMENU.CLAIM_CODE_MENU, storageItem);
                    }
                }
            }
        }
    }

    override void CreateAndSetupActionCallback(ActionData action_data) {
        super.CreateAndSetupActionCallback(action_data);
    }
}
#endif