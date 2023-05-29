[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Structure Completion Component")]
class SCR_CTI_StructureCompletionComponentClass : ScriptComponentClass
{
};

class SCR_CTI_StructureCompletionComponent : ScriptComponent
{
	[Attribute(defvalue: "10", desc: "Completion value:", params: "10 100 5"), RplProp()]
	protected int completion;

	//------------------------------------------------------------------------------------------------
	int getCompletionValue()
	{
		return completion;
	}

	//------------------------------------------------------------------------------------------------
	void setCompletionValue(int value)
	{
		if (value > 100) value = 100;
		completion = value;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_StructureCompletionComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_StructureCompletionComponent()
	{
	}
};