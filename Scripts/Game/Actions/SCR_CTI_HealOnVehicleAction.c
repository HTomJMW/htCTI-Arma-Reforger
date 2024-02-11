[EntityEditorProps(category: "GameScripted/CTI", description: "Heal on Vehicle - User Action")]
class SCR_CTI_HealOnVehicleAction : SCR_ScriptedUserAction
{
	protected IEntity m_User;

	//------------------------------------------------------------------------------------------------
	protected override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(pUserEntity.FindComponent(SCR_CharacterDamageManagerComponent));
		if (cdmc && !cdmc.IsDestroyed()) cdmc.FullHeal();
		
		CancelPlayerAnimation(m_User);
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
			IEntity bandage = spawnAndTakeBandage();
			charController.SetStanceChange(ECharacterStanceChange.STANCECHANGE_TOCROUCH);
			if (bandage) charController.TryUseBandage(bandage, 3, 4.0, true);
		}

		super.OnActionStart(pUserEntity);
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionCanceled(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character)
			return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			CharacterCommandHandlerComponent cmdHandler = CharacterCommandHandlerComponent.Cast(pAnimationComponent.GetCommandHandler());
			if (cmdHandler)
				cmdHandler.FinishItemUse();
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnConfirmed(IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character)
			return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			CharacterCommandHandlerComponent cmdHandler = CharacterCommandHandlerComponent.Cast(pAnimationComponent.GetCommandHandler());
			cmdHandler.FinishItemUse();
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		m_User = user;

		SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(user.FindComponent(SCR_CharacterDamageManagerComponent));
		if (cdmc.GetHealth() > cdmc.GetMaxHealth() * 0.8 && !cdmc.IsDamagedOverTime(EDamageType.BLEEDING)) return false;

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Heal";

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
	protected IEntity spawnAndTakeBandage()
	{
		IEntity bandage = GetGame().SpawnEntityPrefabLocal(Resource.Load("{CDCC313B2FB76FE7}Prefabs/Items/Medicine/Gauze_01.et"), GetGame().GetWorld(), null);

		CharacterControllerComponent ccc =  CharacterControllerComponent.Cast(m_User.FindComponent(CharacterControllerComponent));
		ccc.TakeGadgetInLeftHand(bandage, EGadgetType.CONSUMABLE);
		
		return bandage;
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_HealOnVehicleAction()
	{
		CancelPlayerAnimation(m_User);
	}
};