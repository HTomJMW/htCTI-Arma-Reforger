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
	[Attribute(defvalue: "FIA", UIWidgets.EditBox, "Faction key:"), RplProp(onRplName: "OnTownCapturedClient", condition: RplCondition.Custom, customConditionName: "RpcCondition")]
	protected FactionKey m_factionKey;
	[RplProp()]
	protected FactionKey m_oldFactionKey = "FIA";
	[RplProp()]
	protected bool m_isActive = false;
	
	protected float m_activeTime = -1.0;
	
	protected ref map<FactionKey, float> m_capTimes = new map<FactionKey, float>;
	
	ref array<AIGroup> m_townGroups = {};
	ref array<IEntity> m_townMines = {};

	protected SCR_FlagComponent m_flagComponent;
	protected SCR_CTI_TownMapDescriptorComponent m_mapComponent;
	protected SCR_CTI_TownPatrolComponent m_townPatrolComponent;
	protected SCR_CTI_GameMode m_gameMode;
	protected FactionManager m_factionManager;
	protected RplComponent m_rplComponent;
	protected SCR_SpawnPoint m_spawnPoint;

	protected SCR_CTI_ActivationArea m_activationArea;
	protected SCR_CTI_CaptureArea m_captureArea;
	
	ref ScriptInvoker m_onTimeOutInvoker = new ScriptInvoker();

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
		return this.GetOrigin();
	}

	//------------------------------------------------------------------------------------------------
	FactionKey getFactionKey()
	{
		return m_factionKey;
	}

	//------------------------------------------------------------------------------------------------
	FactionKey getOldFactionKey()
	{
		return m_oldFactionKey;
	}

	//------------------------------------------------------------------------------------------------
	// server only
	void setFactionKey(FactionKey newKey)
	{
		m_factionKey = newKey;
		
		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	void setOldFactionKey(FactionKey newKey)
	{
		m_oldFactionKey = newKey;
	
		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	bool isActive()
	{
		return m_isActive;
	}

	//------------------------------------------------------------------------------------------------
	// server only
	void setActive(bool value)
	{
		m_isActive = value;
		
		Replication.BumpMe();
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
	override void EOnInit(IEntity owner)
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_factionManager = GetGame().GetFactionManager();
		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		m_flagComponent = SCR_FlagComponent.Cast(owner.FindComponent(SCR_FlagComponent));
		m_mapComponent = SCR_CTI_TownMapDescriptorComponent.Cast(owner.FindComponent(SCR_CTI_TownMapDescriptorComponent));
		m_townPatrolComponent = SCR_CTI_TownPatrolComponent.Cast(owner.FindComponent(SCR_CTI_TownPatrolComponent));
		
		IEntity child = owner.GetChildren();
		while (child)
		{
			SCR_CTI_CaptureArea captureArea = SCR_CTI_CaptureArea.Cast(child);
			SCR_CTI_ActivationArea activationArea = SCR_CTI_ActivationArea.Cast(child);
			if (captureArea) m_captureArea = captureArea;
			if (activationArea) m_activationArea = activationArea;
			
			child = child.GetSibling();
		}

		changeFlag(m_factionKey); // For running missions and JIPs (TODO: maybe RplProp better?)
		
		m_spawnPoint = createSpawnPoint();
		m_spawnPoint.SetFactionKey(m_factionKey);
		m_spawnPoint.setDisplayName("Town: " + m_townName);

		if (m_rplComponent.IsProxy())
		{
			m_activationArea.Deactivate();
			m_captureArea.Deactivate();
		} else {
			RandomGenerator randomgen = new RandomGenerator();
			int rnd = randomgen.RandIntInclusive(9, 12);
			GetGame().GetCallqueue().CallLater(townLoop, rnd * 1000, true);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void townLoop()
	{
		if (isActive())
		{
			removeEmptyGroups();
			addWayPointToGroups();
			checkCapture();
			timeOutCheck();
		}
	}

	//------------------------------------------------------------------------------------------------
	// server only
	void checkCapture()
	{
		int fia = m_captureArea.GetOccupantsCount(m_factionManager.GetFactionByKey("FIA"));
		int ussr = m_captureArea.GetOccupantsCount(m_factionManager.GetFactionByKey("USSR"));
		int us = m_captureArea.GetOccupantsCount(m_factionManager.GetFactionByKey("US"));
		
		if (fia < 1 && ussr < 1 && us < 1) return;
		
		switch (true)
		{
			case (ussr > 0 && us == 0 && fia == 0 && m_factionKey != "USSR"): OnTownCapturedServer("USSR", "US", "FIA"); break;
			case (us > 0 && ussr == 0 && fia == 0 && m_factionKey != "US"):	OnTownCapturedServer("US", "USSR", "FIA"); break;
			case (fia > 0 && ussr == 0 && us == 0 && m_factionKey != "FIA"): OnTownCapturedServer("FIA", "USSR", "US"); break;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	bool RpcCondition()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	// Proxys
	protected void OnTownCapturedClient()
	{
		changeFlag(m_factionKey);

		PlayerController pc = GetGame().GetPlayerController();
		if (pc)
		{
			FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
			switch (true)
			{
				case (affiliationComp.GetAffiliatedFaction().GetFactionKey() == m_factionKey):
				{
					m_mapComponent.changeMarker(m_factionKey);
					break;
				}
				case (affiliationComp.GetAffiliatedFaction().GetFactionKey() == m_oldFactionKey):
				{
					m_mapComponent.changeMarker(m_factionKey);
					break;
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	// Server
	void OnTownCapturedServer(FactionKey newSide, FactionKey enemySide1, FactionKey enemySide2)
	{
		setOldFactionKey(m_factionKey);
			
		setFactionKey(newSide);
		changeFlag(newSide);
		m_mapComponent.changeMarker(m_factionKey);
		m_spawnPoint.SetFactionKey(newSide);

		PrintFormat("CTI :: Town %1 captured by %2", m_townName, m_factionKey);

		if (m_townGroups.IsEmpty() && m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey(enemySide1)) < 1 && m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey(enemySide2)) < 1)
		{
			setActive(false);
			PrintFormat("CTI :: Town %1 is Inactive", m_townName);
		}
		
		bool recap = false;
		if (m_capTimes.Get(newSide) > 0 && m_gameMode.GetElapsedTime() - m_capTimes.Get(newSide) <= SCR_CTI_Constants.RECAPTUREDELAY)
		{
			recap = true;
		}
		
		PrintFormat("CTI :: Town %1 Recap: %2", m_townName, recap.ToString());
		
		if (!recap)
		{
			m_gameMode.changeCommanderFunds(newSide, m_townValue * 10);
		} else {
			m_gameMode.changeCommanderFunds(newSide, m_townValue * 5);
		}
		
		array<SCR_ChimeraCharacter> outCharacters = {};
		m_activationArea.GetOccupants(m_factionManager.GetFactionByKey(m_factionKey), outCharacters);
		
		foreach (SCR_ChimeraCharacter character : outCharacters)
		{
			int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(character);
			m_gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>" + m_townName + "</color> captured.", "Information", 15);
			
			SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId);
			if (clientData && !clientData.isCommander())
			{
				if (!recap)
				{
					clientData.changeFunds(m_townValue * 10);
				} else {
					clientData.changeFunds(m_townValue * 5);
				}
			}
		}
		
		m_gameMode.bumpMeServer();

		m_capTimes.Set(newSide, m_gameMode.GetElapsedTime());

		int townIndex = m_gameMode.CTI_Towns.Find(this);
		m_gameMode.sendFactionNotifT(newSide, ENotification.CTI_NOTIF_TOWN_CAPTURED, townIndex);
		
		if (m_oldFactionKey != "FIA") m_gameMode.sendFactionNotifT(m_oldFactionKey, ENotification.CTI_NOTIF_TOWN_LOST, townIndex);
		
		if (m_gameMode.getPriority(newSide) == m_townName) m_gameMode.setPriority(newSide, "");
	}

	//------------------------------------------------------------------------------------------------
	protected void changeFlag(FactionKey factionkey)
	{
		switch (m_factionKey)
  		{
  			case "USSR": m_flagComponent.ChangeMaterial("Assets/Props/Fabric/Flags/Data/Flag_1_2_Red.emat", ""); break;
  			case "US": m_flagComponent.ChangeMaterial("Assets/Props/Fabric/Flags/Data/Flag_1_2_Blue.emat", ""); break;
  			case "FIA": m_flagComponent.ChangeMaterial("Assets/Props/Fabric/Flags/Data/Flag_1_2_Green.emat", ""); break;
  		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void removeEmptyGroups()
	{
		for (int i = m_townGroups.Count() - 1; i >= 0; i--)
		{
			if (!m_townGroups[i]) m_townGroups.Remove(i);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void timeOutCheck()
	{
		bool priority = (m_gameMode.getPriority("USSR") == m_townName || m_gameMode.getPriority("US") == m_townName);

		if (m_isActive && !priority && m_gameMode.GetElapsedTime() - m_activeTime >= SCR_CTI_Constants.INACTIVATIONTIME)
		{
			switch (m_factionKey)
			{
				case "FIA": if (m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey("USSR")) < 1 && m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey("US")) < 1)
							{
								setActive(false);
								m_onTimeOutInvoker.Invoke();
							}
							break;
				case "US": if (m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey("USSR")) < 1 && m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey("FIA")) < 1)
							{
								setActive(false);
								m_onTimeOutInvoker.Invoke();
							}
							break;
				case "USSR": if (m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey("US")) < 1 && m_activationArea.GetOccupantsCount(m_factionManager.GetFactionByKey("FIA")) < 1)
							{
								setActive(false);
								m_onTimeOutInvoker.Invoke();
							}
							break;
			}
			
			if (!m_isActive) PrintFormat("CTI :: Town %1 is Inactive", m_townName);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void addWayPointToGroups()
	{
		if (!m_isActive || m_townGroups.IsEmpty() || m_townPatrolComponent.waypoints.IsEmpty()) return;
		
		for (int i = 0; i < m_townGroups.Count(); i++)
		{
			if (!m_townGroups[i]) break;
			if (!m_townGroups[i].GetCurrentWaypoint())
			{
				int rnd = Math.RandomIntInclusive(0, m_townPatrolComponent.waypoints.Count() - 1);
				//m_townGroups[i].FinishCurrentOrder(); // removed by BI
				m_townGroups[i].AddWaypoint(m_townPatrolComponent.waypoints[rnd]);
				//PrintFormat("Group: %1, WP: %2", m_townGroups[i], m_townGroups[i].GetCurrentWaypoint());
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected SCR_SpawnPoint createSpawnPoint()
	{
		ResourceName sp = "{E7F4D5562F48DDE4}Prefabs/MP/Spawning/SpawnPoint_Base.et";
		Resource spRes = Resource.Load(sp);

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		vector mat[4];
		GetTransform(mat);
		params.Transform = mat;
		
		IEntity spEnt = GetGame().SpawnEntityPrefab(spRes, GetWorld(), params);

		return SCR_SpawnPoint.Cast(spEnt);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void removeTownGroups()
	{
		for (int i = m_townGroups.Count() - 1; i >= 0; i--)
		{
			AIGroup group = m_townGroups[i];
			SCR_EntityHelper.DeleteEntityAndChildren(group);
		}

		m_townGroups.Clear();
		PrintFormat("CTI :: Town %1 Groups: %2", m_townName, m_townGroups);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void removeTownMines()
	{
		for (int i = m_townMines.Count() - 1; i >= 0; i--)
		{
			IEntity mine = m_townMines[i];
			SCR_EntityHelper.DeleteEntityAndChildren(mine);
		}

		m_townMines.Clear();
		PrintFormat("CTI :: Town %1 Mines: %2", m_townName, m_townMines);
	}

	//------------------------------------------------------------------------------------------------
	protected void OnTimeOut()
	{
		if (m_rplComponent.IsProxy()) return;
		
		removeTownGroups();
		removeTownMines();
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_Town(IEntitySource src, IEntity parent)
	{
		m_onTimeOutInvoker.Insert(OnTimeOut);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_Town()
	{
		m_onTimeOutInvoker.Remove(OnTimeOut);

		if (m_townGroups) m_townGroups.Clear();
		m_townGroups = null;
		if (m_townMines) m_townMines.Clear();
		m_townMines = null;
	}
};