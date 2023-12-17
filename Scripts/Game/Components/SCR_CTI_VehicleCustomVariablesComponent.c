[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Custrom Variables")]
class SCR_CTI_VehicleCustomVariablesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_VehicleCustomVariablesComponent : ScriptComponent
{
	[Attribute("0", UIWidgets.ComboBox, "Support Vehicle Type", "", ParamEnumArray.FromEnum(CTI_SupportVehicleTypes))]
	protected CTI_SupportVehicleTypes supportVehicleType;

	//------------------------------------------------------------------------------------------------
	CTI_SupportVehicleTypes getSupportVehicleType()
	{
		return supportVehicleType;
	}

	//------------------------------------------------------------------------------------------------
	void setSupportVehicleType(CTI_SupportVehicleTypes supportType)
	{
		supportVehicleType = supportType;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_VehicleCustomVariablesComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_VehicleCustomVariablesComponent()
	{
	}
};