class SCR_CTI_GetSupportVehicles
{
	protected ref array<IEntity> m_supportVehicles = {};
	
	//------------------------------------------------------------------------------------------------
	array<IEntity> GetSupportVehiclesInRangeByType(FactionKey factionkey, vector center, float radius, CTI_SupportVehicleTypes supportType)
	{
		GetGame().GetWorld().QueryEntitiesBySphere(center, radius, GetEntity, FilterEntities, EQueryEntitiesFlags.DYNAMIC);
		
		for (int i = m_supportVehicles.Count() - 1; i >= 0; i--)
		{
			IEntity vehicle = (m_supportVehicles[i]);
			FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(vehicle.FindComponent(FactionAffiliationComponent));
			FactionKey vehFactionKey = faffComp.GetDefaultAffiliatedFaction().GetFactionKey();
			SCR_CTI_VehicleCustomVariablesComponent vcvc = SCR_CTI_VehicleCustomVariablesComponent.Cast(vehicle.FindComponent(SCR_CTI_VehicleCustomVariablesComponent));
			CTI_SupportVehicleTypes vehicleType = vcvc.getSupportVehicleType();
			if (factionkey != vehFactionKey || vehicleType != supportType) m_supportVehicles.Remove(i);
		}

		return m_supportVehicles;
	}
	
	//------------------------------------------------------------------------------------------------
	protected bool GetEntity(IEntity ent)
	{
		m_supportVehicles.Insert(ent);

		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected bool FilterEntities(IEntity ent)
	{
		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		SCR_CTI_VehicleCustomVariablesComponent vcvc = SCR_CTI_VehicleCustomVariablesComponent.Cast(ent.FindComponent(SCR_CTI_VehicleCustomVariablesComponent));
		if (vdmc && !vdmc.IsDestroyed() && vcvc)
		{
			CTI_SupportVehicleTypes supportType = vcvc.getSupportVehicleType();
			if (supportType != CTI_SupportVehicleTypes.NONE) return true;
		}

		return false;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_GetSupportVehicles()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GetSupportVehicles()
	{
		if (!m_supportVehicles) return;
		m_supportVehicles.Clear();
		m_supportVehicles = null;
	}
};