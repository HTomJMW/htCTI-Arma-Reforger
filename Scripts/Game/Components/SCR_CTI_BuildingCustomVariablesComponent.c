[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Custrom Variables")]
class SCR_CTI_BuildingCustomVariablesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_BuildingCustomVariablesComponent : ScriptComponent
{
	[RplProp()]
	protected FactionKey m_factionkey;

	//------------------------------------------------------------------------------------------------
	FactionKey getFactionKey()
	{
		return m_factionkey;
	}

	//------------------------------------------------------------------------------------------------
	void setFactionKey(FactionKey factionkey)
	{
		m_factionkey = factionkey;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BuildingCustomVariablesComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildingCustomVariablesComponent()
	{
	}
};