[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Base Marker US")]
class SCR_CTI_BaseMarkerUSClass : BaseGameEntityClass
{
};

class SCR_CTI_BaseMarkerUS : BaseGameEntity
{
	protected vector m_pos;
	protected int m_factionindex;
	protected Color m_color;
	protected Color m_textcolor;
	protected string m_name;
	
	protected SCR_MapDescriptorComponent m_mapComponent;

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_mapComponent = SCR_MapDescriptorComponent.Cast(owner.FindComponent(SCR_MapDescriptorComponent));

		m_pos = owner.GetOrigin();
		m_name = "Base";
		m_textcolor = Color.Black;
		m_factionindex = 1;
		m_color = Color.Blue;

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
};