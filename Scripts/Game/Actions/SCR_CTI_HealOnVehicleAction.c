[EntityEditorProps(category: "GameScripted/CTI", description: "Heal on Vehicle - User Action")]
class SCR_CTI_HealOnVehicleAction : SCR_VehicleActionBase
{
	protected CarControllerComponent_SA m_pCarController;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_pCarController = CarControllerComponent_SA.Cast(pOwnerEntity.FindComponent(CarControllerComponent_SA));
		m_rplComponent = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
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
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(pUserEntity.FindComponent(SCR_CharacterDamageManagerComponent));
		if (cdmc && !cdmc.IsDestroyed()) cdmc.FullHeal();
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionStart(IEntity pUserEntity)
	{
		/*IEntity veh = m_pCarController.GetOwner();
		InventoryStorageManagerComponent ismc = InventoryStorageManagerComponent.Cast(veh.FindComponent(InventoryStorageManagerComponent));
		bool hasBandage = false;
		SCR_PrefabNamePredicate predicate = new SCR_PrefabNamePredicate();
		array<IEntity> bandages = {};
		predicate.prefabName = SCR_CTI_Constants.USSR_BANDAGE;
		if (ismc) ismc.FindItems(bandages, predicate, EStoragePurpose.PURPOSE_ANY);
		Print(bandages);

		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character)
			return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			charController.TryUseBandage(bandages[0], 3, 16, true);

			//CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			//int itemActionId = pAnimationComponent.BindCommand("CMD_HealSelf");
			//charController.TryUseItemOverrideParams(bandages[0], false, false, itemActionId, 1, 0, int.MAX, 0, 0, false, null);
		}*/
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionCanceled(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		/*ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character)
			return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			CharacterCommandHandlerComponent cmdHandler = CharacterCommandHandlerComponent.Cast(pAnimationComponent.GetCommandHandler());
			if (cmdHandler)
				cmdHandler.FinishItemUse();
		}*/
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnConfirmed(IEntity pUserEntity)
	{
		/*ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);
		if (!character)
			return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			CharacterCommandHandlerComponent cmdHandler = CharacterCommandHandlerComponent.Cast(pAnimationComponent.GetCommandHandler());
			cmdHandler.FinishItemUse();
		}*/
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		IEntity veh = m_pCarController.GetOwner();
		VehicleWheeledSimulation_SA simulation = VehicleWheeledSimulation_SA.Cast(veh.FindComponent(VehicleWheeledSimulation_SA));

		SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(user.FindComponent(SCR_CharacterDamageManagerComponent));

		if (cdmc.GetHealth() > cdmc.GetMaxHealth() * 0.8 && !cdmc.IsDamagedOverTime(EDamageType.BLEEDING)) return false;
		if (Math.AbsFloat(simulation.GetSpeedKmh()) > 5) return false; // check vehicle speed

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Heal";

		return true;
	}
};