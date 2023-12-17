[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Support vehicles.")]
class SCR_CTI_SupportVehiclesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_SupportVehiclesComponent : ScriptComponent
{
	ref array<IEntity> supportVehicles = {};

	//------------------------------------------------------------------------------------------------
	IEntity getSupportVehiclesByType()
	{
		IEntity x = null;
		return x; // TODO
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