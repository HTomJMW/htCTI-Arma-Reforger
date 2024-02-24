[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Air Unit Marker entity for Radar")]
class SCR_CTI_AirUnitRadarMarkerClass : BaseGameEntityClass
{
};

class SCR_CTI_AirUnitRadarMarker : BaseGameEntity
{
	protected RplComponent m_rplComponent;
	protected IEntity m_unit;
	protected SCR_VehicleFactionAffiliationComponent m_vfaffComp;
	protected SCR_MapDescriptorComponent m_mapComponent;
	protected int m_factionIndex = -1;
	protected MapItem m_mapItem;
	protected Color m_textColor = Color.Black;
	protected Color m_iconColor = Color.Yellow;
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	protected void initMarker()
	{	
		switch (m_factionIndex)
		{
			case 2: m_iconColor = Color.Red; break;
			case 1: m_iconColor = Color.Blue; break;
			case 0: m_iconColor = Color.Green; break;
		}

		createMarker();
	}
	
	//------------------------------------------------------------------------------------------------
	protected void createMarker()
	{
		m_mapItem = m_mapComponent.Item();
		m_mapItem.SetPriority(1);
		m_mapItem.SetFactionIndex(m_factionIndex);
		m_mapItem.SetBaseType(EMapDescriptorType.MDT_ICON);
		m_mapItem.SetImageDef("Icon_Seize");
		m_mapItem.SetDisplayName("AIR");
	
		MapDescriptorProps props = m_mapItem.GetProps();
			props.SetDetail(96);
			props.SetIconSize(0.2, 0.3, 2);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(m_textColor);
			props.SetFrontColor(m_iconColor);
			props.SetTextBold();
			props.SetTextVisible(false);
			props.SetIconVisible(false);
			props.Activate(true);

		m_mapItem.SetProps(props);
			
		GetGame().GetCallqueue().CallLater(checkHeight, 1000, true, m_unit);
	}

	//------------------------------------------------------------------------------------------------
	protected void checkHeight(IEntity ent)
	{

		
		// TODO check radar and upgrade		
		
		
		vector origin = ent.GetOrigin();
		if (origin[1] > SCR_CTI_Constants.AIRRADARDETECTIONHEIGHT)
		{
			MapDescriptorProps props = m_mapItem.GetProps();
				props.SetTextVisible(true);
				props.SetIconVisible(true);

			m_mapItem.SetProps(props);
		} else {
			MapDescriptorProps props = m_mapItem.GetProps();
				props.SetTextVisible(false);
				props.SetIconVisible(false);

			m_mapItem.SetProps(props);
		}

		SCR_HelicopterDamageManagerComponent hdmc = SCR_HelicopterDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (hdmc && hdmc.IsDestroyed())
		{
			MapDescriptorProps props = m_mapItem.GetProps();
				props.SetTextVisible(false);
				props.SetIconVisible(false);
				props.Activate(false);
	
			m_mapItem.SetProps(props);
		
			GetGame().GetCallqueue().Remove(checkHeight);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		m_mapComponent = SCR_MapDescriptorComponent.Cast(owner.FindComponent(SCR_MapDescriptorComponent));
		m_unit = owner.GetParent();
		m_vfaffComp = SCR_VehicleFactionAffiliationComponent.Cast(m_unit.FindComponent(SCR_VehicleFactionAffiliationComponent));
		m_factionIndex = GetGame().GetFactionManager().GetFactionIndex(m_vfaffComp.GetDefaultAffiliatedFaction());

		GetGame().GetCallqueue().CallLater(initMarker, 1000, false);
	}
};