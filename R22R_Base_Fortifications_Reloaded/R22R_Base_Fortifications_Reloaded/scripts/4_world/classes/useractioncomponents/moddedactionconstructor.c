modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        actions.Insert(ActionFoldR22R_BBS_BASE);

        actions.Insert(ActionOpenPalisadeGate);
//        actions.Insert(ActionOpenR22RWoodenDoor);
        
        actions.Insert(ActionNextCombinationLockDialOnPalisadeGate);
        actions.Insert(ActionDialCombinationLockOnPalisadeGate);

        #ifdef CodeLock
        actions.Insert(ActionAttachCodeLockOnPalisadeGate);
        actions.Insert(ActionInteractLockOnPalisadeGate);
        actions.Insert(ActionManageLockOnPalisadeGate);

        actions.Insert(ActionAttachCodeLockOnBBSBase);
        actions.Insert(ActionInteractLockOnBBSBase);
        actions.Insert(ActionManageLockOnBBSBase);
        #endif

        actions.Insert(ActionClosePalisadeGate);
//        actions.Insert(ActionCloseR22RWoodenDoor);

        


        actions.Insert(ActionOpenStorageLid);

        actions.Insert(ActionNextCombinationLockDialOnBBSBase);
        actions.Insert(ActionDialCombinationLockOnBBSBase);

        actions.Insert(ActionCloseStorageLid);

        //! RAIDING ::
        actions.Insert(ActionRaidBBSBase);
        actions.Insert(ActionRaidBaseBuildingBase);
    }
};
