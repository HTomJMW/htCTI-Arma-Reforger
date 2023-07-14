[EntityEditorProps(category: "GameScripted/CTI", description: "CTI - Modded Spawn point entity", visible: false)]
modded class SCR_SpawnPointClass : SCR_PositionClass
{
};

//------------------------------------------------------------------------------------------------
modded class SCR_SpawnPoint : SCR_Position
{
	[RplProp(onRplName: "OnDisplayNameChangedClient", condition: RplCondition.Custom, customConditionName: "RpcCondition")]
	string m_displayName = "SpawnPoint";
	
	//------------------------------------------------------------------------------------------------
	void setDisplayName(string name)
	{
		m_displayName = name;
		setUIInfo(m_displayName);

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	protected void setUIInfo(LocalizedString name)
	{
		SCR_UIInfo m_uiInfo = SCR_UIInfo.CreateInfo(name);
		m_Info = m_uiInfo;
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		m_bShowInDeployMapOnly = true;

		setUIInfo(m_displayName);
	}

	//------------------------------------------------------------------------------------------------
	protected bool RpcCondition()
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected void OnDisplayNameChangedClient()
	{
		setUIInfo(m_displayName);
	}
};