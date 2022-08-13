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
	protected const float timeStep = 60;
	
	protected bool m_isActive = false;
	protected float m_activationTime = -1.0;
	
	// Spawned AI groups
	ref array<AIGroup> m_groups = {};
	
	// Characters in capture area (75m)
	ref array<SCR_ChimeraCharacter> m_FIA_Occupants = {};
	ref array<SCR_ChimeraCharacter> m_USSR_Occupants = {};
	ref array<SCR_ChimeraCharacter> m_US_Occupants = {};
	
	protected SCR_FlagComponent m_flagComponent;
	protected SCR_SpawnPoint m_sPoint;
	protected SCR_CTI_MapDescriptorComponent m_mapComponent;
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_ActivationArea m_activationArea;

	string getTownName()
	{
		return m_townName;
	}
	
	vector getFlagPos()
	{
		vector transform[4];
		GetTransform(transform);
		
		return transform[3];
	}
	
	FactionKey getFactionKey()
	{
		return m_factionKey;
	}
	
	void setFactionKey(FactionKey newKey)
	{
		m_factionKey = newKey;
	}
	
	Faction getFaction()
	{
		return m_faction;
	}
	
	void setFaction(Faction newFaction)
	{
		m_faction = newFaction;
	}
	
	void setFactionByKey(FactionKey newKey)
	{
		m_faction = GetGame().GetFactionManager().GetFactionByKey(newKey);
	}
	
	bool isActive()
	{
		return m_isActive;
	}
	
	void setActive(bool value)
	{
		m_isActive = value;
	}
		
	void checkCapture()
	{
		int fia = m_FIA_Occupants.Count();
		int ussr = m_USSR_Occupants.Count();
		int us = m_US_Occupants.Count();
		
		if (fia < 1 && ussr < 1 && us < 1) return;
		
		if (ussr > 0 && us == 0 && fia == 0 && m_factionKey != "USSR")
		{
			setFactionByKey("USSR");
			setFactionKey("USSR");
			changeFlag("USSR");
			m_sPoint.SetFactionKey("USSR");
			PrintFormat("CTI :: Town %1 captured by %2", m_townName, m_factionKey);
			foreach(SCR_ChimeraCharacter charactersInside : m_USSR_Occupants)
			{
				int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(charactersInside);
				if (m_gameMode.ClientDataArray)
				{
					foreach(SCR_CTI_ClientData clientData : m_gameMode.ClientDataArray)
					if (playerId == clientData.getPlayerId()) clientData.changeFunds(m_townValue * 10);
					m_gameMode.SendHint(playerId, m_townName + " captured", "Information", 15); // send message to all players inside capture zone
				}
			}
		}
		
		if (us > 0 && ussr == 0 && fia == 0 && m_factionKey != "US")
		{
			setFactionByKey("US");
			setFactionKey("US");
			changeFlag("US");
			m_sPoint.SetFactionKey("US");
			PrintFormat("CTI :: Town %1 captured by %2", m_townName, m_factionKey);
			foreach(SCR_ChimeraCharacter charactersInside : m_US_Occupants)
			{
				int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(charactersInside);
				if (m_gameMode.ClientDataArray)
				{
					foreach(SCR_CTI_ClientData clientData : m_gameMode.ClientDataArray)
					if (playerId == clientData.getPlayerId()) clientData.changeFunds(m_townValue * 10);
					m_gameMode.SendHint(playerId, m_townName + " captured", "Information", 15); // send message to all players inside capture zone
				}
			}
		}
		
		if (fia > 0 && ussr == 0 && us == 0 && m_factionKey != "FIA")
		{
			setFactionByKey("FIA");
			setFactionKey("FIA");
			changeFlag("FIA");
			m_sPoint.SetFactionKey("FIA");
			PrintFormat("CTI :: Town %1 captured by %2", m_townName, m_factionKey);
		}
	}
	
	void changeFlag(FactionKey key)
	{
		switch (key)
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
	
	void initMapComponent()
	{
		m_mapComponent.init();
	}

	override void EOnInit(IEntity owner)
	{
		m_FIA_Occupants.Clear();
		m_USSR_Occupants.Clear();
		m_US_Occupants.Clear();
		
		m_groups.Clear();
		
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
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
		
		child = owner.GetChildren();
		while (child)
		{
			SCR_CTI_ActivationArea activationArea = SCR_CTI_ActivationArea.Cast(child);
			if (activationArea)
				{
					m_activationArea = activationArea;
					break;
				} else {
					child = child.GetSibling();
				}
		}

		m_mapComponent = SCR_CTI_MapDescriptorComponent.Cast(owner.FindComponent(SCR_CTI_MapDescriptorComponent));
		
		m_timeDelta = 0;
		this.SetEventMask(EntityEvent.FIXEDFRAME);
	}

	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > timeStep)
			{
				timeOutCheck();
				m_timeDelta = 0;
			}
	}
	
	protected void timeOutCheck()
	{
		if (m_isActive && m_gameMode.GetElapsedTime() - m_activationTime >= 240)
		{
			FactionManager fm = GetGame().GetFactionManager();
			int ussr = m_activationArea.GetOccupantsCount(fm.GetFactionByKey("USSR"));
			int us = m_activationArea.GetOccupantsCount(fm.GetFactionByKey("US"));
			int fia = m_activationArea.GetOccupantsCount(fm.GetFactionByKey("FIA"));
			switch (m_factionKey)
			{
				case "FIA": if (ussr + us == 0) {m_isActive = false; PrintFormat("CTI :: Town %1 is Inactive", m_townName);} break;
				case "US": if (fia + ussr == 0) {m_isActive = false; PrintFormat("CTI :: Town %1 is Inactive", m_townName);} break;
				case "USSR": if (fia + us == 0) {m_isActive = false; PrintFormat("CTI :: Town %1 is Inactive", m_townName);} break;
			}
		}
	}
};