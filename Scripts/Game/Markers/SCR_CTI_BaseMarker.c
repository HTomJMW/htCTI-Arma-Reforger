[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Base Marker entity")]
class SCR_CTI_BaseMarkerClass : BaseGameEntityClass
{
};

class SCR_CTI_BaseMarker : BaseGameEntity
{
	protected SCR_MapDescriptorComponent m_mapComponent;
	[RplProp()]
	protected int m_factionIndex;
	protected MapItem m_mapItem;
	protected Color m_color;
	protected Color m_textcolor = Color.Black;
	protected string m_name;
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;

	//------------------------------------------------------------------------------------------------
	void setOwnerFaction(FactionKey factionkey)
	{
		Faction faction = GetGame().GetFactionManager().GetFactionByKey(factionkey);
		m_factionIndex = GetGame().GetFactionManager().GetFactionIndex(faction);
	}

	//------------------------------------------------------------------------------------------------
	protected void initMarker()
	{
		SCR_CTI_ClientData clientData = m_gameMode.getClientData(m_pc.GetPlayerId());
		if (clientData && clientData.getFactionIndex() != 0 && m_factionIndex > 0)
		{
			switch(m_factionIndex)
			{
				case 2: m_color = Color.Red; break;
				case 1: m_color = Color.Blue; break;
			}

			if (m_factionIndex == clientData.getFactionIndex()) createMarker();
		} else {
			GetGame().GetCallqueue().CallLater(initMarker, 3000, false);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void createMarker()
	{
		m_mapItem = m_mapComponent.Item();
		
		m_mapItem.SetDisplayName(m_name);
		m_mapItem.SetBaseType(EMapDescriptorType.MDT_ICON);
		m_mapItem.SetFactionIndex(m_factionIndex);
		m_mapItem.SetImageDef("CTI_TOWN");

		MapDescriptorProps props = m_mapItem.GetProps();
			props.SetDetail(96);
			props.SetIconSize(128, 0.8, 0.8);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(m_textcolor);
			m_color.SetA(0.8);
			props.SetFrontColor(m_color);
			props.SetTextVisible(true);
			props.SetIconVisible(true);
			props.Activate(true);
		
		m_mapItem.SetProps(props);
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		m_mapComponent = SCR_MapDescriptorComponent.Cast(this.FindComponent(SCR_MapDescriptorComponent));

		// Client or Master
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		if (m_pc)
		{
			GetGame().GetCallqueue().CallLater(initMarker, 1000, false);
		} else {
			GetGame().GetCallqueue().CallLater(EOnInit, 2000, false, owner);
		}
	}
};