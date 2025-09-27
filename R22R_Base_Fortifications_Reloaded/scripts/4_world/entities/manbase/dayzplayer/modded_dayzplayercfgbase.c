modded class ModItemRegisterCallbacks
{

    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterOneHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("R22R_WoodenPlank",								"dz/anims/workspaces/player/player_main/player_main_2h.asi",						pBehavior, 	"dz/anims/anm/player/ik/two_handed/wooden_plank.anm");
	};

    override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{
		super.RegisterHeavy(pType, pBehavior);
		pType.AddItemInHandsProfileIK("R22R_Spiked_WoodenLog",							"dz/anims/workspaces/player/player_main/player_main_heavy.asi",						pBehavior, 	"dz/anims/anm/player/ik/heavy/wooden_crate.anm");
		pType.AddItemInHandsProfileIK("R22R_BBS_LargeCrate",							"dz/anims/workspaces/player/player_main/player_main_heavy.asi",						pBehavior, 	"dz/anims/anm/player/ik/heavy/tent_large.anm");
		pType.AddItemInHandsProfileIK("R22R_BBS_SmallCrate",							"dz/anims/workspaces/player/player_main/player_main_heavy.asi",						pBehavior, 	"dz/anims/anm/player/ik/heavy/tent_large.anm");
		pType.AddItemInHandsProfileIK("R22R_BBS_PlankStorage",							"dz/anims/workspaces/player/player_main/player_main_heavy.asi",						pBehavior, 	"dz/anims/anm/player/ik/heavy/tent_large.anm");
		pType.AddItemInHandsProfileIK("R22R_Lumber",									"dz/anims/workspaces/player/player_main/player_main_heavy.asi",						pBehavior, 	"dz/anims/anm/player/ik/heavy/wooden_crate.anm");
	};
}

