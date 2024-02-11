[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Support vehicles.")]
class SCR_CTI_SupportVehiclesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_SupportVehiclesComponent : ScriptComponent
{
	ref array<IEntity> supportVehicles = {}; // TODO check null removes

	//------------------------------------------------------------------------------------------------
	array<IEntity> getSupportVehiclesByType(CTI_SupportVehicleTypes type)
	{
		array<IEntity> vehicles = {};

		foreach (IEntity vehicle : supportVehicles)
		{
			if (!vehicle) continue;
			
			SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(vehicle.FindComponent(SCR_VehicleDamageManagerComponent));
			if (vdmc.IsDestroyed()) continue;

			SCR_CTI_VehicleCustomVariablesComponent vcvc = SCR_CTI_VehicleCustomVariablesComponent.Cast(vehicle.FindComponent(SCR_CTI_VehicleCustomVariablesComponent));
			if (vcvc)
			{
				if (vcvc.getSupportVehicleType() == type) {vehicles.Insert(vehicle)};
			}
		}

		return vehicles;
	}
	
	//------------------------------------------------------------------------------------------------
	void addSupportVehicle(IEntity vehicle)
	{
		supportVehicles.Insert(vehicle);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_SupportVehiclesComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_SupportVehiclesComponent()
	{
		if (!supportVehicles) return;
		supportVehicles.Clear();
		supportVehicles = null;
	}
};