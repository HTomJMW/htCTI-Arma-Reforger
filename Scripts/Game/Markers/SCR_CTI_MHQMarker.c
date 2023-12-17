[EntityEditorProps(category: "GameScripted/CTI", description: "CTI MHQ Marker entity")]
class SCR_CTI_MHQMarkerClass : BaseGameEntityClass
{
};

class SCR_CTI_MHQMarker : BaseGameEntity
{
	protected RplComponent m_rplComponent;
	protected IEntity m_mhq;
	protected SCR_VehicleFactionAffiliationComponent m_vfaffComp;
	protected SCR_MapDescriptorComponent m_mapComponent;
	[RplProp()]
	protected int m_factionIndex;
	protected MapItem m_mapItem;
	protected Color m_textColor = Color.Black;
	protected string m_name = "MHQ";
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;

	//------------------------------------------------------------------------------------------------
	protected void initMarker()
	{
		m_pc = GetGame().GetPlayerController();
		SCR_CTI_ClientData clientData;
		if (m_pc) clientData = m_gameMode.getClientData(m_pc.GetPlayerId());
		if (clientData && clientData.getFactionIndex() != 0 && m_factionIndex > 0 && m_pc)
		{
			switch(m_factionIndex)
			{
				case 2: m_textColor = Color.Red; break;
				case 1: m_textColor = Color.Blue; break;
			}

			if (m_factionIndex == clientData.getFactionIndex()) createMarker();
		} else {
			GetGame().GetCallqueue().CallLater(initMarker, 2000, false);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void createMarker()
	{
		bool mhqDown = false;
		m_mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(GetGame().GetFactionManager().GetFactionByIndex(m_factionIndex).GetFactionKey());
		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(m_mhq.FindComponent(SCR_VehicleDamageManagerComponent));
		if (vdmc) mhqDown = vdmc.IsDestroyed();

		m_mapItem = m_mapComponent.Item();
		m_mapItem.SetPriority(1);
		m_mapItem.SetFactionIndex(m_factionIndex);
		m_mapItem.SetBaseType(EMapDescriptorType.MDT_ICON);
		m_mapItem.SetImageDef("USSR_Base_Small_Respawn_Bg");
		
		if (mhqDown)
		{
			m_mapItem.SetDisplayName("MHQ Wreck");
	
			MapDescriptorProps props = m_mapItem.GetProps();
				props.SetDetail(96);
				props.SetIconSize(0.2, 0.3, 3);
				props.SetTextSize(32, 16, 64);
				props.SetTextColor(Color.Black);
				props.SetFrontColor(Color.Black);
				props.SetTextBold();
				props.SetTextVisible(true);
				props.SetIconVisible(true);
				props.Activate(true);

			m_mapItem.SetProps(props);
		} else {
			m_mapItem.SetDisplayName("MHQ");
	
			MapDescriptorProps props = m_mapItem.GetProps();
				props.SetDetail(96);
				props.SetIconSize(0.2, 0.3, 3);
				props.SetTextSize(32, 16, 64);
				props.SetTextColor(m_textColor);
				props.SetFrontColor(m_textColor);
				props.SetTextBold();
				props.SetTextVisible(true);
				props.SetIconVisible(true);
				props.Activate(true);

			m_mapItem.SetProps(props);
			
			EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(m_mhq.FindComponent(EventHandlerManagerComponent));
			if (ehManager)
			{
				ehManager.RegisterScriptHandler("OnDestroyed", this, OnDestroyed);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnDestroyed(IEntity ent)
	{
		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(m_mhq.FindComponent(SCR_VehicleDamageManagerComponent));
		if (vdmc && vdmc.IsDestroyed())
		{
			m_mapItem.SetDisplayName("MHQ Wreck");
			MapDescriptorProps props = m_mapItem.GetProps();
				props.SetTextColor(Color.Black);
	
			m_mapItem.SetProps(props);
			
			EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(m_mhq.FindComponent(EventHandlerManagerComponent));
			if (ehManager)
			{
				ehManager.RemoveScriptHandler("OnDestroyed", this, OnDestroyed);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));

		// Server or Master
		if (!m_rplComponent.IsProxy() || m_rplComponent.IsMaster())
		{
			m_mhq = owner.GetParent();
			m_vfaffComp = SCR_VehicleFactionAffiliationComponent.Cast(m_mhq.FindComponent(SCR_VehicleFactionAffiliationComponent));
			m_factionIndex = GetGame().GetFactionManager().GetFactionIndex(m_vfaffComp.GetDefaultAffiliatedFaction());
			Replication.BumpMe();
		}

		// Client
		if (m_rplComponent.IsProxy() || m_rplComponent.IsMaster())
		{
			m_mapComponent = SCR_MapDescriptorComponent.Cast(owner.FindComponent(SCR_MapDescriptorComponent));
			m_gameMode = SCR_CTI_GameMode.GetInstance();
			GetGame().GetCallqueue().CallLater(initMarker, 1000, false);
		}
	}
};