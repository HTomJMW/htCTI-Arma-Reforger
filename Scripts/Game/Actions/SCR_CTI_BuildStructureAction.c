class SCR_CTI_BuildStructureAction : SCR_ScriptedUserAction
{
	protected SCR_CTI_GameMode m_gameMode;
	protected IEntity m_User;
	protected SCR_GadgetManagerComponent m_GadgetManager;
	protected IEntity m_wipStructure;
	
	//------------------------------------------------------------------------------------------------
	protected override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_wipStructure = SCR_EntityHelper.GetMainParent(pOwnerEntity, true);
	}

	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(m_wipStructure.FindComponent(SCR_CTI_StructureCompletionComponent));
		if (scc.getCompletionValue() < 100)
		{
			scc.setCompletionValue(scc.getCompletionValue() + 5);
			m_gameMode.bumpMeServer();

			PrintFormat("CTI :: Building %1", scc.getCompletionValue());
		} else {
			//TODO FINISH
			Print("CTI :: Construction complete!");
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionStart(IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character) return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			int itemActionId = pAnimationComponent.BindCommand("CMD_Item_Action");
			charController.TryUseItemOverrideParams(GetBuildingTool(pUserEntity), false, true, itemActionId, 1, 0, int.MAX, 0, 0, false, null);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionCanceled(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character) return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			CharacterCommandHandlerComponent cmdHandler = CharacterCommandHandlerComponent.Cast(pAnimationComponent.GetCommandHandler());
			if (cmdHandler) cmdHandler.FinishItemUse();
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnConfirmed(IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character) return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			CharacterCommandHandlerComponent cmdHandler = CharacterCommandHandlerComponent.Cast(pAnimationComponent.GetCommandHandler());
			cmdHandler.FinishItemUse();
		}
	}

	//------------------------------------------------------------------------------------------------
	override void PerformContinuousAction(IEntity pOwnerEntity, IEntity pUserEntity, float timeSlice)
	{
		if (!LoopActionUpdate(timeSlice)) return;

		PerformAction(pOwnerEntity, pUserEntity);
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		m_User = user;
		m_GadgetManager = SCR_GadgetManagerComponent.GetGadgetManager(user);

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{			
		SCR_GadgetComponent gadgetComponent = m_GadgetManager.GetHeldGadgetComponent();
		if (!gadgetComponent) return false;

		IEntity tool = GetBuildingTool(user);
		if (!tool && (tool.GetPrefabData().GetPrefabName() != SCR_CTI_Constants.USSR_SHOVEL || tool.GetPrefabData().GetPrefabName() != SCR_CTI_Constants.US_SHOVEL))
		{
			SetCannotPerformReason("Building Tool is not in hand!");
			return false;
		}

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	protected void CancelPlayerAnimation(IEntity pUserEntity)
	{
		if (!pUserEntity) return;
		
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character) return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (!charController) return;

		CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
		if (!pAnimationComponent) return;

		CharacterCommandHandlerComponent handlerComponent = pAnimationComponent.GetCommandHandler();
		if (!handlerComponent) return;

		handlerComponent.FinishItemUse();
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Build";

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	IEntity GetBuildingTool(notnull IEntity ent)
	{
		SCR_GadgetManagerComponent gadgetManager = SCR_GadgetManagerComponent.GetGadgetManager(ent);
		if (!gadgetManager) return null;

		return gadgetManager.GetHeldGadget();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildStructureAction()
	{
		CancelPlayerAnimation(m_User);
	}
}
