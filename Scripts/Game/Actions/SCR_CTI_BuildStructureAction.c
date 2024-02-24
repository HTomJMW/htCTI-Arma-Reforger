class SCR_CTI_BuildStructureAction : SCR_ScriptedUserAction
{
	protected SCR_CTI_GameMode m_gameMode;
	protected IEntity m_User;
	protected SCR_GadgetManagerComponent m_GadgetManager;
	protected IEntity m_wipStructure;
	protected SCR_CTI_StructureCompletionComponent m_scc;
	protected FactionAffiliationComponent m_wipFaffComp;
	protected RplComponent m_wipRplComp;
	
	//------------------------------------------------------------------------------------------------
	protected override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_wipStructure = SCR_EntityHelper.GetMainParent(pOwnerEntity, true);
		m_scc = SCR_CTI_StructureCompletionComponent.Cast(m_wipStructure.FindComponent(SCR_CTI_StructureCompletionComponent));
		m_wipFaffComp = FactionAffiliationComponent.Cast(m_wipStructure.FindComponent(FactionAffiliationComponent));
		m_wipRplComp = RplComponent.Cast(m_wipStructure.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (m_wipRplComp && m_wipRplComp.IsProxy()) return;
		
		if (m_scc.getCompletionValue() < 100)
		{
			m_scc.setCompletionValue(m_scc.getCompletionValue() + 5);
			m_gameMode.bumpMeServer();

			PrintFormat("CTI :: Building %1", m_scc.getCompletionValue());
		} else {
			SCR_CTI_FinishWipStructure finisher = new SCR_CTI_FinishWipStructure();
			finisher.finishWipStructure(m_wipStructure);

			CancelPlayerAnimation(m_User);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionStart(IEntity pUserEntity)
	{
		super.OnActionStart(pUserEntity);

		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character) return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			int itemActionId = pAnimationComponent.BindCommand("CMD_Item_Action");
			charController.TryUseItemOverrideParams(GetBuildingTool(pUserEntity), false, true, itemActionId, 1, 0, int.MAX, 0, 0, false, null);
		}

		super.OnActionStart(pUserEntity);
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
		if (!tool)
		{
			SetCannotPerformReason("Building Tool is not in hand!");
			return false;
		} else {
			if (tool.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.USSR_SHOVEL || tool.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.US_SHOVEL) return true;
		}

		SetCannotPerformReason("Building Tool is not in hand!");
		return false;
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
		IEntity wipStructure = SCR_EntityHelper.GetMainParent(GetOwner(), true);
		SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(wipStructure.FindComponent(SCR_CTI_StructureCompletionComponent));
		string completitionValue = scc.getCompletionValue().ToString();
		// TODO FIX on CLIENT
		outName = "[Hold] Build " + completitionValue + "% [+5%]";

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
