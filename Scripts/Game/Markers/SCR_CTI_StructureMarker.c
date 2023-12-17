[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Structure Marker entity")]
class SCR_CTI_StructureMarkerClass : BaseGameEntityClass
{
};

class SCR_CTI_StructureMarker : BaseGameEntity
{
	protected SCR_CTI_GameMode m_gameMode;
	protected IEntity m_building;
	protected FactionAffiliationComponent m_faffComponent;
	protected SCR_MapDescriptorComponent m_mapComponent;
	[RplProp()]
	protected int m_factionIndex;
	protected MapItem m_mapItem;
	protected Color m_textcolor = Color.Black;
	protected string m_name = "Building";
	protected PlayerController m_pc;

	//------------------------------------------------------------------------------------------------
	protected void initMarker()
	{
		SCR_CTI_ClientData clientData = m_gameMode.getClientData(m_pc.GetPlayerId());
		if (clientData && clientData.getFactionIndex() != 0 && m_factionIndex > 0)
		{
			ResourceName resName = m_building.GetPrefabData().GetPrefabName();
			int factIndex = m_gameMode.FactoriesUSSR.findIndexFromResourcename(resName); // USSR and US factories are same
	
			SCR_CTI_FactoryData factData = m_gameMode.FactoriesUSSR.g_USSR_Factories[factIndex];
			if (factData) m_name = factData.getName();
	
			if (m_factionIndex == clientData.getFactionIndex()) createMarker();
		} else {
			GetGame().GetCallqueue().CallLater(initMarker, 3000, false);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void createMarker()
	{
		m_mapItem = m_mapComponent.Item();

		IEntity structure = IEntity.Cast(GetParent());
		SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(structure.FindComponent(SCR_CTI_StructureCompletionComponent));
		if (!scc)
		{
			m_mapItem.SetDisplayName(m_name);
		} else {
			m_mapItem.SetDisplayName(m_name + "\nWork in progress");
		}

		m_mapItem.SetBaseType(EMapDescriptorType.MDT_ICON);
		m_mapItem.SetImageDef("USSR_Base_Small_Respawn_Bg");
		m_mapItem.SetFactionIndex(m_factionIndex);

		MapDescriptorProps props = m_mapItem.GetProps();
			props.SetDetail(96);
			props.SetIconSize(0.2, 0.3, 3);
			props.SetTextSize(16, 8, 32);
			props.SetTextColor(m_textcolor);
			m_textcolor.SetA(0.8);
			props.SetFrontColor(m_textcolor);
			props.SetTextVisible(true);
			props.SetIconVisible(true);
			props.Activate(true);

		m_mapItem.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	protected void delayForGetFactionIndex(IEntity owner)
	{
		m_building = owner.GetParent();
		m_faffComponent = FactionAffiliationComponent.Cast(m_building.FindComponent(FactionAffiliationComponent));
		m_mapComponent = SCR_MapDescriptorComponent.Cast(owner.FindComponent(SCR_MapDescriptorComponent));
		m_factionIndex = GetGame().GetFactionManager().GetFactionIndex(m_faffComponent.GetAffiliatedFaction());

		if (m_factionIndex > 0)
		{
			Replication.BumpMe();
			// client or master
			m_gameMode = SCR_CTI_GameMode.GetInstance();
			m_pc = GetGame().GetPlayerController();
			if (m_gameMode && m_pc) GetGame().GetCallqueue().CallLater(initMarker, 1000, false);
		} else {
			GetGame().GetCallqueue().CallLater(delayForGetFactionIndex, 2000, false, owner);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		GetGame().GetCallqueue().CallLater(delayForGetFactionIndex, 1000, false, owner);
	}
};