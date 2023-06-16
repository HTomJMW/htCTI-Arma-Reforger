[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Player Marker entity")]
class SCR_CTI_PlayerMarkerClass : BaseGameEntityClass
{
};

class SCR_CTI_PlayerMarker : BaseGameEntity
{
	protected RplComponent m_rplComponent;
	protected SCR_ChimeraCharacter m_player;
	protected SCR_CharacterControllerComponent m_characterControllerComp;
	protected SCR_MapDescriptorComponent m_mapComponent;
	protected FactionAffiliationComponent m_faffComponent;
	[RplProp()]
	protected int m_factionIndex;
	protected MapItem m_mapItem;
	protected Color m_color = Color.Black;;
	protected string m_name;
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
			m_player = SCR_ChimeraCharacter.Cast(this.GetParent()); // Get on client too
			int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(m_player);
			m_name = GetGame().GetPlayerManager().GetPlayerName(playerId);
			if (!m_name) m_name = "Player";
	
			switch(m_factionIndex)
			{
				case 2: m_color = Color.Red; break;
				case 1: m_color = Color.Blue; break;
			}

			if (m_factionIndex == clientData.getFactionIndex()) createMarker();
		} else {
			GetGame().GetCallqueue().CallLater(initMarker, 2000, false);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void createMarker()
	{
		m_mapItem = m_mapComponent.Item();

		m_mapItem.SetVisible(true);
		m_mapItem.SetFactionIndex(m_factionIndex);
		m_mapItem.SetDisplayName(m_name);
		m_mapItem.SetBaseType(EMapDescriptorType.MDT_NAME_GENERIC);
		m_mapItem.SetImageDef("Unit");
		m_mapItem.SetPriority(3);
		
		MapDescriptorProps props = m_mapItem.GetProps();
			props.SetDetail(96);
			props.SetIconSize(0.1, 0.2, 3);
			props.SetTextSize(32, 4, 32);
			props.SetTextColor(Color.Black);
			props.SetFrontColor(m_color);
			props.SetTextVisible(true);
			props.SetIconVisible(true);
			props.Activate(true);
		
		m_mapItem.SetProps(props);

		m_characterControllerComp = SCR_CharacterControllerComponent.Cast(m_player.FindComponent(SCR_CharacterControllerComponent));
		m_characterControllerComp.m_OnPlayerDeath.Insert(OnDeath);
	}

	//------------------------------------------------------------------------------------------------
	protected void OnDeath()
	{
		m_mapItem.SetVisible(false);
		m_characterControllerComp.m_OnPlayerDeath.Remove(OnDeath);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));

		// Server or Master
		if (!m_rplComponent.IsProxy() || m_rplComponent.IsMaster())
		{
			m_player = SCR_ChimeraCharacter.Cast(owner.GetParent());
			//m_characterControllerComp = SCR_CharacterControllerComponent.Cast(m_player.FindComponent(SCR_CharacterControllerComponent));
			m_faffComponent = FactionAffiliationComponent.Cast(m_player.FindComponent(FactionAffiliationComponent));
			m_factionIndex = GetGame().GetFactionManager().GetFactionIndex(m_faffComponent.GetAffiliatedFaction());
			Replication.BumpMe();
		}

		// client
		if (m_rplComponent.IsProxy() || m_rplComponent.IsMaster())
		{
			m_mapComponent = SCR_MapDescriptorComponent.Cast(owner.FindComponent(SCR_MapDescriptorComponent));
			m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
			GetGame().GetCallqueue().CallLater(initMarker, 1000, false);
		}
	}
};