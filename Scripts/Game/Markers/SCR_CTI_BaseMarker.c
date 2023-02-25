[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Base Marker entity")]
class SCR_CTI_BaseMarkerClass : BaseGameEntityClass
{
};

class SCR_CTI_BaseMarker : BaseGameEntity
{
	protected vector m_pos;
	protected FactionKey m_factionkey;
	
	[RplProp()]
	protected int m_factionindex;
	
	protected Color m_color;
	protected Color m_textcolor;
	protected string m_name;
	
	protected SCR_MapDescriptorComponent m_mapComponent;

	//------------------------------------------------------------------------------------------------
	void setOwnerFaction(FactionKey fk)
	{
		Faction faction = GetGame().GetFactionManager().GetFactionByKey(fk);
		m_factionindex = GetGame().GetFactionManager().GetFactionIndex(faction);

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	protected void initMarker()
	{
		m_mapComponent = SCR_MapDescriptorComponent.Cast(this.FindComponent(SCR_MapDescriptorComponent));

		m_pos = this.GetOrigin();
		m_name = "Base";
		m_textcolor = Color.Black;
		
		switch(m_factionindex)
		{
			case 2: m_color = Color.Red; break;
			case 1: m_color = Color.Blue; break;
		}

		createMarker();
	}
	
	//------------------------------------------------------------------------------------------------
	protected void createMarker()
	{
		MapItem mapitem = m_mapComponent.Item();
		
		mapitem.SetDisplayName(m_name);
		mapitem.SetBaseType(EMapDescriptorType.MDT_ICON);
		mapitem.SetFactionIndex(m_factionindex);
		
		MapDescriptorProps props = mapitem.GetProps();
			mapitem.SetImageDef("Flag");
			props.SetDetail(96);
			props.SetIconSize(32, 1, 4);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(m_textcolor);
			m_color.SetA(0.8);
			props.SetFrontColor(m_color);
			props.SetTextVisible(true);
			props.SetIconVisible(true);
			props.Activate(true);
		
		mapitem.SetProps(props);
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		GetGame().GetCallqueue().CallLater(initMarker, 1000, false);
	}
};