[EntityEditorProps(category: "GameScripted/CTI", description: "Repair Vehicle - User Action")]
class SCR_CTI_RepairAction : SCR_VehicleActionBase
{
	protected IEntity m_vehicle;
	protected FactionAffiliationComponent m_vehAffiliationComp;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;
	
	protected bool hasToolkit = false;
	protected bool wheelDamaged = false;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_vehicle = pOwnerEntity;
		m_vehAffiliationComp = FactionAffiliationComponent.Cast(pOwnerEntity.FindComponent(FactionAffiliationComponent));
		m_gameMode = SCR_CTI_GameMode.GetInstance();
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
		if (!hasToolkit)
		{
			SetCannotPerformReason("Toolkit required");
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(pOwnerEntity.FindComponent(SCR_VehicleDamageManagerComponent));

		array<HitZone> outHitZones = {};
		vdmc.GetAllHitZones(outHitZones);

		foreach(HitZone hz : outHitZones)
		{
			SCR_WheelHitZone whz = SCR_WheelHitZone.Cast(hz);
			if (whz)
			{
				whz.SetHealth(whz.GetMaxHealth());
			} else {
				if (hz.GetHealth() < hz.GetMaxHealth() * 0.7) hz.SetHealth(hz.GetMaxHealth() * 0.7);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(user);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		FactionAffiliationComponent affComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		VehicleWheeledSimulation_SA wheeledSimulation = VehicleWheeledSimulation_SA.Cast(m_vehicle.FindComponent(VehicleWheeledSimulation_SA));
		VehicleHelicopterSimulation heliSimulation = VehicleHelicopterSimulation.Cast(m_vehicle.FindComponent(VehicleHelicopterSimulation));
		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(m_vehicle.FindComponent(SCR_VehicleDamageManagerComponent));

		hasToolkit = false;
		SCR_PrefabNamePredicate predicate = new SCR_PrefabNamePredicate();
		array<IEntity> toolkits = {};
		predicate.prefabName = SCR_CTI_Constants.TOOLKIT;
		SCR_InventoryStorageManagerComponent ismc;
		ismc = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		if (ismc) ismc.FindItems(toolkits, predicate, EStoragePurpose.PURPOSE_ANY);
		if (!toolkits.IsEmpty()) hasToolkit = true;

		array<HitZone> outHitZones = {};
		vdmc.GetAllHitZones(outHitZones);
		
		for (int i = outHitZones.Count() - 1; i >= 0; i--)
		{
			SCR_WheelHitZone whz = SCR_WheelHitZone.Cast(outHitZones[i]);
			if (!whz)
			{
				outHitZones.Remove(i);
			} else {
				if (whz.GetWheelIndex() == 0) outHitZones.Remove(i);
			}
		}

		wheelDamaged = false;
		foreach(HitZone hz : outHitZones)
		{
			SCR_WheelHitZone wheel = SCR_WheelHitZone.Cast(hz);
			if (wheel.GetDamageState() != EDamageState.UNDAMAGED)
			{
				wheelDamaged = true;
				break;
			}
		}
	
		if (wheeledSimulation && Math.AbsFloat(wheeledSimulation.GetSpeedKmh()) > 5) return false; // check vehicle speed
		if (heliSimulation && heliSimulation.GetAltitudeAGL() > 4) return false;
		if (!wheelDamaged)
		{
			if (vdmc.GetHealth() > vdmc.GetMaxHealth() * 0.65) return false;
		}
			
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Repair - Max. 70%";

		return true;
	}
};