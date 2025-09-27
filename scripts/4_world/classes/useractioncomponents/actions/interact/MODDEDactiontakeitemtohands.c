modded class ActionTakeItemToHands : ActionInteractBase
{
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        ItemBase targetItem = ItemBase.Cast(target.GetObject());
        if (!targetItem)
            return false;

        if (targetItem.IsKindOf("R22R_BBS_Base"))
        {
            R22R_BBS_Base storageUnit = R22R_BBS_Base.Cast(targetItem);
            if (storageUnit)
            {
                storageUnit.UpdateWeightStatus();

                if (!CanTakeToHands(storageUnit))
                {
                    return false;
                }
            }

            return player.GetInventory().CanAddEntityIntoHands(targetItem);
        }

        // Call super if not R22R_BBS_Base
        return super.ActionCondition(player, target, item);
    }

    protected bool CanTakeToHands(R22R_BBS_Base storageUnit)
    {
        return !storageUnit.IsTooHeavy() && storageUnit.IsTakeable() && !storageUnit.IsBeingPlaced() && !storageUnit.IsSetForDeletion() && storageUnit.HasValidParent();
    }
}
