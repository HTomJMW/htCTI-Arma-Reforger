[EntityEditorProps(category: "GameScripted/CTI", description: "Extinguish Vehicle - User Action")]
class SCR_CTI_ExtinguishAction : SCR_VehicleActionBase
{
	protected IEntity m_vehicle;
	protected FactionAffiliationComponent m_vehAffiliationComp;
	protected RplComponent m_rplComponent;

	protected bool hasExtinguisher = false;
	protected bool isFlaming = false;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_vehicle = pOwnerEntity;
		m_vehAffiliationComp = FactionAffiliationComponent.Cast(pOwnerEntity.FindComponent(FactionAffiliationComponent));
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
		if (!hasExtinguisher)
		{
			SetCannotPerformReason("Extinguisher required");
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
			SCR_FlammableHitZone part = SCR_FlammableHitZone.Cast(hz);
			
			if (!part) continue;
			if (part.GetFireState() != EFireState.NONE)
			{
				part.SetFireState(EFireState.NONE);
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
		
		hasExtinguisher = false;
		SCR_PrefabNamePredicate predicate = new SCR_PrefabNamePredicate();
		array<IEntity> extinguishers = {};
		predicate.prefabName = SCR_CTI_Constants.EXTINGUISHER;
		SCR_InventoryStorageManagerComponent ismc = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		if (ismc) ismc.FindItems(extinguishers, predicate, EStoragePurpose.PURPOSE_ANY);
		if (!extinguishers.IsEmpty()) hasExtinguisher = true;

		isFlaming = false;
		array<HitZone> outHitZones = {};
		vdmc.GetAllHitZones(outHitZones);
	
		foreach (HitZone hz : outHitZones)
		{
			SCR_FlammableHitZone fhz = SCR_FlammableHitZone.Cast(hz);
			if (fhz && (fhz.GetFireState() != EFireState.NONE))
			{
				isFlaming = true;
				break;
			}
		}

		if (wheeledSimulation && Math.AbsFloat(wheeledSimulation.GetSpeedKmh()) > 5) return false; // check vehicle speed
		if (heliSimulation && heliSimulation.GetAltitudeAGL() > 4) return false;
		if (!isFlaming) return false;

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Extinguish";

		return true;
	}
};