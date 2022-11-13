[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Town")]
class SCR_CTI_TownClass : BaseGameEntityClass
{
};

class SCR_CTI_Town : BaseGameEntity
{
	[Attribute("", UIWidgets.EditBox, "Town name:")]
	protected string m_townName;
	[Attribute(defvalue: "250", desc: "Town value:", params: "50 500 50")]
	protected int m_townValue;
	[Attribute(defvalue: "FIA", UIWidgets.EditBox, "Faction key:")]
	protected FactionKey m_factionKey;
	protected Faction m_faction;
	[Attribute()]
	protected ref SCR_UIInfo m_Info;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 60;
	
	protected bool m_isActive = false;
	protected float m_activeTime = -1.0;
	protected const float ACTIVETIMEMAX = 30;
	
	// Spawned AI groups
	ref array<AIGroup> m_groups = {};
	
	// Characters in town area
	ref array<SCR_ChimeraCharacter> m_FIA_Occupants = {};
	ref array<SCR_ChimeraCharacter> m_USSR_Occupants = {};
	ref array<SCR_ChimeraCharacter> m_US_Occupants = {};
	
	// Characters in capture area (75m)
	ref array<SCR_ChimeraCharacter> m_FIA_CapArea_Occ = {};
	ref array<SCR_ChimeraCharacter> m_USSR_CapArea_Occ = {};
	ref array<SCR_ChimeraCharacter> m_US_CapArea_Occ = {};
	
	protected SCR_FlagComponent m_flagComponent;
	protected SCR_SpawnPoint m_sPoint;
	protected SCR_CTI_MapDescriptorComponent m_mapComponent;
	protected SCR_CTI_TownPatrolComponent m_townPatrolComponent;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	string getTownName()
	{
		return m_townName;
	}

	//------------------------------------------------------------------------------------------------
	int getTownValue()
	{
		return m_townValue;
	}

	//------------------------------------------------------------------------------------------------
	vector getFlagPos()
	{
		vector transform[4];
		GetTransform(transform);
		
		return transform[3];
		
		// GETORIGIN BETTER?
	}

	//------------------------------------------------------------------------------------------------
	FactionKey getFactionKey()
	{
		return m_factionKey;
	}

	//------------------------------------------------------------------------------------------------
	void setFactionKey(FactionKey newKey)
	{
		m_factionKey = newKey;
	}

	//------------------------------------------------------------------------------------------------
	Faction getFaction()
	{
		return m_faction;
	}

	//------------------------------------------------------------------------------------------------
	void setFaction(Faction newFaction)
	{
		m_faction = newFaction;
	}

	//------------------------------------------------------------------------------------------------
	void setFactionByKey(FactionKey newKey)
	{
		m_faction = GetGame().GetFactionManager().GetFactionByKey(newKey);
	}

	//------------------------------------------------------------------------------------------------
	bool isActive()
	{
		return m_isActive;
	}

	//------------------------------------------------------------------------------------------------
	void setActive(bool value)
	{
		m_isActive = value;
	}

	//------------------------------------------------------------------------------------------------
	void setActiveTime(float newTime)
	{
		m_activeTime = newTime;
	}

	//------------------------------------------------------------------------------------------------
	float getActiveTime()
	{
		return m_activeTime;
	}

	//------------------------------------------------------------------------------------------------
	void checkCapture()
	{
		int fia = m_FIA_CapArea_Occ.Count();
		int ussr = m_USSR_CapArea_Occ.Count();
		int us = m_US_CapArea_Occ.Count();
		
		if (fia < 1 && ussr < 1 && us < 1) return;
		
		if (ussr > 0 && us == 0 && fia == 0 && m_factionKey != "USSR")
		{
			setFactionByKey("USSR");
			setFactionKey("USSR");
			changeFlag();
			m_mapComponent.changeMarker();
			m_sPoint.SetFactionKey("USSR");
			PrintFormat("CTI :: Town %1 captured by %2", m_townName, m_factionKey);
			foreach(SCR_ChimeraCharacter charactersInside : m_USSR_CapArea_Occ)
			{
				int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(charactersInside);
				if (m_gameMode.ClientDataArray)
				{
					foreach(SCR_CTI_ClientData clientData : m_gameMode.ClientDataArray)
					if (playerId == clientData.getPlayerId() && !clientData.isCommander()) clientData.changeFunds(m_townValue * 10);
					PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
					SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
					netComp.SendHint(playerId, m_townName + " captured", "Information", 15);
				}
			}
			if (m_FIA_Occupants.Count() + m_US_Occupants.Count() == 0)
			{
				m_isActive = false;
				removeTownGroups();
				PrintFormat("CTI :: Town %1 is Inactive", m_townName);
			}
			
			// commander reward
			m_gameMode.changeCommanderFunds("USSR", m_townValue * 10);
			int sizeCDA = m_gameMode.ClientDataArray.Count();
			SCR_CTI_ClientData clientData;
			for (int i = 0; i < sizeCDA; i++)
			{
					if (m_gameMode.ClientDataArray[i].getPlayerId() == m_gameMode.getCommanderId("USSR"))
					{
						clientData = m_gameMode.ClientDataArray[i];
						break;
					}
			}
			if (clientData) clientData.changeFunds(m_townValue * 10);
		}
		
		if (us > 0 && ussr == 0 && fia == 0 && m_factionKey != "US")
		{
			setFactionByKey("US");
			setFactionKey("US");
			changeFlag();
			m_mapComponent.changeMarker();
			m_sPoint.SetFactionKey("US");
			PrintFormat("CTI :: Town %1 captured by %2", m_townName, m_factionKey);
			foreach(SCR_ChimeraCharacter charactersInside : m_US_CapArea_Occ)
			{
				int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(charactersInside);
				if (m_gameMode.ClientDataArray)
				{
					foreach(SCR_CTI_ClientData clientData : m_gameMode.ClientDataArray)
					if (playerId == clientData.getPlayerId() && !clientData.isCommander()) clientData.changeFunds(m_townValue * 10);
					PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
					SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
					netComp.SendHint(playerId, m_townName + " captured", "Information", 15);
				}
			}
			if (m_FIA_Occupants.Count() + m_USSR_Occupants.Count() == 0)
			{
				m_isActive = false;
				removeTownGroups();
				PrintFormat("CTI :: Town %1 is Inactive", m_townName);
			}
			
			// commander reward
			m_gameMode.changeCommanderFunds("US", m_townValue * 10);
			int sizeCDA = m_gameMode.ClientDataArray.Count();
			SCR_CTI_ClientData clientData;
			for (int i = 0; i < sizeCDA; i++)
			{
					if (m_gameMode.ClientDataArray[i].getPlayerId() == m_gameMode.getCommanderId("US"))
					{
						clientData = m_gameMode.ClientDataArray[i];
						break;
					}
			}
			if (clientData) clientData.changeFunds(m_townValue * 10);
		}
		
		if (fia > 0 && ussr == 0 && us == 0 && m_factionKey != "FIA")
		{
			setFactionByKey("FIA");
			setFactionKey("FIA");
			changeFlag();
			m_mapComponent.changeMarker();
			m_sPoint.SetFactionKey("FIA");
			PrintFormat("CTI :: Town %1 captured by %2", m_townName, m_factionKey);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void changeFlag()
	{
		switch (m_factionKey)
  		{
  		case "USSR":
  			m_flagComponent.ChangeMaterial("Assets/Props/Fabric/Flags/Data/Flag_1_2_Red.emat", "");
  			break;
  		case "US":
  			m_flagComponent.ChangeMaterial("Assets/Props/Fabric/Flags/Data/Flag_1_2_Blue.emat", "");
  			break;
  		case "FIA":
  			m_flagComponent.ChangeMaterial("Assets/Props/Fabric/Flags/Data/Flag_1_2_Green.emat", "");
  			break;
  		}
	}

	//------------------------------------------------------------------------------------------------
	void initMapComponent()
	{
		m_mapComponent.init();
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_FIA_CapArea_Occ.Clear();
		m_USSR_CapArea_Occ.Clear();
		m_US_CapArea_Occ.Clear();
		
		m_FIA_Occupants.Clear();
		m_USSR_Occupants.Clear();
		m_US_Occupants.Clear();
		
		m_groups.Clear();
		
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		m_faction = GetGame().GetFactionManager().GetFactionByKey(m_factionKey);
		
		m_flagComponent = SCR_FlagComponent.Cast(owner.FindComponent(SCR_FlagComponent));
		
		IEntity child = owner.GetChildren();
		while (child)
		{
			SCR_SpawnPoint spawnPoint = SCR_SpawnPoint.Cast(child);
			if (spawnPoint)
			{
				m_sPoint = spawnPoint;
				break;
			} else {
				child = child.GetSibling();
			}
		}

		m_mapComponent = SCR_CTI_MapDescriptorComponent.Cast(owner.FindComponent(SCR_CTI_MapDescriptorComponent));
		
		m_townPatrolComponent = SCR_CTI_TownPatrolComponent.Cast(owner.FindComponent(SCR_CTI_TownPatrolComponent));
		m_townPatrolComponent.EOnInit(this);
		
		m_timeDelta = 0;
		this.SetEventMask(EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				timeOutCheck();
				if (m_isActive) {addWayPointToGroups();}
				m_timeDelta = 0;
			}
	}

	//------------------------------------------------------------------------------------------------
	protected void timeOutCheck()
	{
		if (m_isActive && m_gameMode.GetElapsedTime() - m_activeTime >= ACTIVETIMEMAX)
		{
			switch (m_factionKey)
			{
				case "FIA": if (m_USSR_Occupants.Count() + m_US_Occupants.Count() == 0)
							{
								removeTownGroups();
								m_isActive = false;
								PrintFormat("CTI :: Town %1 is Inactive", m_townName);
							}
							break;
				case "US": if (m_FIA_Occupants.Count() + m_USSR_Occupants.Count() == 0)
							{
								removeTownGroups();
								m_isActive = false;
								PrintFormat("CTI :: Town %1 is Inactive", m_townName);
							}
							break;
				case "USSR": if (m_FIA_Occupants.Count() + m_US_Occupants.Count() == 0)
							{
								removeTownGroups();
								m_isActive = false;
								PrintFormat("CTI :: Town %1 is Inactive", m_townName);
							}
							break;
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void removeTownGroups()
	{
		foreach (AIGroup group : m_groups)
		{
			if (!group) continue;
			array<AIAgent> outAgents = {};
			group.GetAgents(outAgents);
			foreach (AIAgent agent : outAgents)
			{
				IEntity ent = agent.GetControlledEntity();
				m_rplComponent.DeleteRplEntity(ent, false);
			}
		}
		m_groups.Clear();
		PrintFormat("CTI :: Town %1 groups: %2", m_townName, m_groups);
	}

	//------------------------------------------------------------------------------------------------
	protected void addWayPointToGroups()
	{
		for (int i = 0; i < m_groups.Count(); i++)
		{
			if (!m_groups[i]) break;
			if (m_groups[i].GetAgentsCount() == 0) break;
			if (!m_groups[i].GetCurrentWaypoint())
			{
				int rnd = Math.RandomIntInclusive(0, m_townPatrolComponent.waypoints.Count() - 1);
				m_groups[i].FinishCurrentOrder();
				m_groups[i].AddWaypoint(m_townPatrolComponent.waypoints[rnd]);
				//PrintFormat("Group: %1, WP: %2", m_groups[i], m_groups[i].GetCurrentWaypoint());
			}
		}
	}
};