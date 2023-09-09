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
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		CharacterControllerComponent ccc = CharacterControllerComponent.Cast(pUserEntity.FindComponent(CharacterControllerComponent));
		if (ccc) ccc.StopCharacterGesture();
		
		if (m_rplComponent && m_rplComponent.IsProxy()) return; // Need check fullheal on client?

		SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(pUserEntity.FindComponent(SCR_CharacterDamageManagerComponent));
		if (cdmc && !cdmc.IsDestroyed()) cdmc.FullHeal();
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionStart(IEntity pUserEntity)
	{
		CharacterControllerComponent ccc = CharacterControllerComponent.Cast(pUserEntity.FindComponent(CharacterControllerComponent));
		if (ccc) ccc.TryStartCharacterGesture(ECharacterGestures.POINT_WITH_FINGER, 0); // ccc.TryPlayItemGesture(EItemGesture.EItemGesturePickUp);
	}

	//------------------------------------------------------------------------------------------------
	override void OnActionCanceled(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		CharacterControllerComponent ccc = CharacterControllerComponent.Cast(pUserEntity.FindComponent(CharacterControllerComponent));
		if (ccc) ccc.StopCharacterGesture();
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		IEntity veh = m_pCarController.GetOwner();
		VehicleWheeledSimulation_SA simulation = VehicleWheeledSimulation_SA.Cast(veh.FindComponent(VehicleWheeledSimulation_SA));

		SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(user.FindComponent(SCR_CharacterDamageManagerComponent));

		if (cdmc.GetHealth() > cdmc.GetMaxHealth() * 0.8 && !cdmc.IsDamagedOverTime(EDamageType.BLEEDING)) return false;
		if (Math.AbsFloat(simulation.GetSpeedKmh()) > 5) return false; // check vehicle speed less then 5

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Heal";

		return true;
	}
};