[EntityEditorProps(category: "GameScripted/CTI", description: "CTI GameMode")]
class SCR_CTI_GameModeClass : SCR_BaseGameModeClass
{
};

// CTI mission faction keys, indexes:
// FIA: 0
// US: 1
// USSR: 2
class SCR_CTI_GameMode : SCR_BaseGameMode
{
	ref array<SCR_CTI_Town> CTI_Towns = {};

	protected SCR_CTI_WeatherAndTimeComponent WeatherAndTimeComponent;
	protected SCR_CTI_RandomStartComponent RandomStartComponent;
	protected SCR_CTI_UpdateVictoryComponent UpdateVictoryComponent;
	protected SCR_CTI_UpgradeComponent UpgradeComponent;
	protected SCR_CTI_BaseComponent BaseComponent;
	protected SCR_CTI_UpdateResourcesComponent UpdateResourcesComponent;
	protected SCR_CTI_UpdateWorkersComponent UpdateWorkersComponent;

	[RplProp()]
	protected int ussrCommanderId = -2;
	[RplProp()]
	protected int usCommanderId = -2;
	[RplProp()]
	protected int ussrCommanderFunds = SCR_CTI_Constants.STARTCOMMFUNDS;
	[RplProp()]
	protected int usCommanderFunds = SCR_CTI_Constants.STARTCOMMFUNDS;
	[RplProp()]
	protected RplId ussrMHQrplId = RplId.Invalid();
	[RplProp()]
	protected RplId usMHQrplId = RplId.Invalid();
	[RplProp()]
	protected string ussrPriority = "None";
	[RplProp()]
	protected string usPriority = "None";

	[RplProp()]
	ref array<ref SCR_CTI_ClientData> ClientDataArray = new array<ref SCR_CTI_ClientData>;

	ref SCR_CTI_UnitsFIA UnitsFIA 			= new SCR_CTI_UnitsFIA();
	ref SCR_CTI_UnitsUSSR UnitsUSSR			= new SCR_CTI_UnitsUSSR();
	ref SCR_CTI_UnitsUS UnitsUS 			= new SCR_CTI_UnitsUS();

	ref SCR_CTI_FactoriesUSSR FactoriesUSSR = new SCR_CTI_FactoriesUSSR();
	ref SCR_CTI_FactoriesUS FactoriesUS		= new SCR_CTI_FactoriesUS();

	ref SCR_CTI_DefensesUSSR DefensesUSSR	= new SCR_CTI_DefensesUSSR();
	ref SCR_CTI_DefensesUS DefensesUS		= new SCR_CTI_DefensesUS();

	ref SCR_CTI_GearFIA GearFIA				= new SCR_CTI_GearFIA();
	ref SCR_CTI_GearUSSR GearUSSR			= new SCR_CTI_GearUSSR();
	ref SCR_CTI_GearUS GearUS				= new SCR_CTI_GearUS();

	ref SCR_CTI_Upgrades Upgrades			= new SCR_CTI_Upgrades();

	ref map<int, int> playersDeathTimes		= new map<int, int>();

	//------------------------------------------------------------------------------------------------
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		WeatherAndTimeComponent = SCR_CTI_WeatherAndTimeComponent.Cast(owner.FindComponent(SCR_CTI_WeatherAndTimeComponent));
		RandomStartComponent = SCR_CTI_RandomStartComponent.Cast(owner.FindComponent(SCR_CTI_RandomStartComponent));
		UpdateVictoryComponent = SCR_CTI_UpdateVictoryComponent.Cast(owner.FindComponent(SCR_CTI_UpdateVictoryComponent));
		UpgradeComponent = SCR_CTI_UpgradeComponent.Cast(owner.FindComponent(SCR_CTI_UpgradeComponent));
		BaseComponent = SCR_CTI_BaseComponent.Cast(owner.FindComponent(SCR_CTI_BaseComponent));
		UpdateResourcesComponent = SCR_CTI_UpdateResourcesComponent.Cast(owner.FindComponent(SCR_CTI_UpdateResourcesComponent));
		UpdateWorkersComponent = SCR_CTI_UpdateWorkersComponent.Cast(owner.FindComponent(SCR_CTI_UpdateWorkersComponent));
	}

	//------------------------------------------------------------------------------------------------
	static SCR_CTI_GameMode GetInstance()
	{
		return SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}
	
	//------------------------------------------------------------------------------------------------
	protected override void OnGameStart()
	{
		super.OnGameStart();

		if (!m_RplComponent.IsProxy())
		{
			StartGameMode();
			PrintFormat("CTI :: GameMode running: %1", IsRunning().ToString());
			Print("CTI :: Mission version: 0.7.18");

			if (RplSession.Mode() == RplMode.Dedicated)
			{
				Print("CTI :: Server: Dedicated");
			} else {
				Print("CTI :: Server: Player-Hosted");
			}
		}

		// Common
		setTownsArray();

		// Create town markers
		foreach (SCR_CTI_Town town : CTI_Towns)
		{
			SCR_CTI_TownMapDescriptorComponent mdc = SCR_CTI_TownMapDescriptorComponent.Cast(town.FindComponent(SCR_CTI_TownMapDescriptorComponent));
			if (mdc) mdc.createMarker("FIA");
		}

		BaseComponent.init();
		UpgradeComponent.init();

		// Action Listener for Main Menu
		GetGame().GetInputManager().AddActionListener("CTI_OpenMainMenu", EActionTrigger.DOWN, openMenu);

		// Action Listeners for Save Loadout
		GetGame().GetInputManager().AddActionListener("Inventory", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("CharacterDropItem", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("Inventory_StepBack", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("CharacterAction", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("CharacterReload", EActionTrigger.UP, saveLoadout); // May save empty mags

		if (!m_RplComponent.IsProxy())
		{
			// Server
			SCR_PlayerSpawnPointManagerComponent playerSpawnPointManager = SCR_PlayerSpawnPointManagerComponent.Cast(FindComponent(SCR_PlayerSpawnPointManagerComponent));
			if (playerSpawnPointManager) playerSpawnPointManager.EnablePlayerSpawnPoints(false);

			WeatherAndTimeComponent.randomStartTime();
			WeatherAndTimeComponent.randomWeather();
			RandomStartComponent.randomStart();
		} else {
			// Client
			WeatherAndTimeComponent.Deactivate(this);
			UpdateVictoryComponent.Deactivate(this);
			UpdateResourcesComponent.Deactivate(this);
			UpdateWorkersComponent.Deactivate(this);

			loadUserSettings();
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void openMenu()
	{
		GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
	}

	//------------------------------------------------------------------------------------------------
	void saveLoadout()
	{
		PlayerController pc = GetGame().GetPlayerController();
		RplComponent rplComp = RplComponent.Cast(pc.GetControlledEntity().FindComponent(RplComponent));
		SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_CharacterDamageManagerComponent));
		if (!rplComp || !cdmc) return;
		if (cdmc.IsDestroyed()) return;

		RplId rplid = rplComp.Id();
		SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
		if (netComp) netComp.savePlayerLoadout(pc.GetPlayerId(), rplid);

		// Set saved loadout for use at next respawn
		SCR_PlayerLoadoutComponent loadoutComp = SCR_PlayerLoadoutComponent.Cast(pc.FindComponent(SCR_PlayerLoadoutComponent));
		SCR_LoadoutManager loadoutManager = GetGame().GetLoadoutManager();

		SCR_CTI_ClientData clientData = getClientData(pc.GetPlayerId());
		if (clientData)
		{
			int factionIndex = clientData.getFactionIndex();
			FactionKey factionkey = GetGame().GetFactionManager().GetFactionByIndex(factionIndex).GetFactionKey();
			string loadoutName;
			switch (factionkey)
			{
				case "USSR": loadoutName = "USSR Last Saved Gear"; break;
				case "US": loadoutName = "US Last Saved Gear"; break;
			}
			SCR_BasePlayerLoadout savedLoadout = loadoutManager.GetLoadoutByName(loadoutName);
			loadoutComp.RequestLoadout(savedLoadout);
		} else {
			FactionAffiliationComponent faffcomp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
			string loadoutName;
			switch (faffcomp.GetAffiliatedFaction().GetFactionKey())
			{
				case "USSR": loadoutName = "USSR Default Gear"; break;
				case "US": loadoutName = "US Default Gear"; break;
			}
			SCR_BasePlayerLoadout defaultLoadout = loadoutManager.GetLoadoutByName(loadoutName);
			loadoutComp.RequestLoadout(defaultLoadout);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerDisconnected(int playerId, KickCauseCode cause, int timeout)
	{
		super.OnPlayerDisconnected(playerId, cause, timeout);

		SCR_CTI_ClientData clientData = getClientData(playerId);
		if (clientData && clientData.isCommander()) clientData.setCommander(false);

		switch (playerId)
		{
			case ussrCommanderId: clearCommanderId("USSR"); break;
			case usCommanderId: clearCommanderId("US"); break;
		}

		playersDeathTimes.Remove(playerId);

		PlayerManager pm = GetGame().GetPlayerManager();
		PrintFormat("CTI :: Player %1 disconnected", pm.GetPlayerName(playerId));
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerRegistered(int playerId)
	{
		super.OnPlayerRegistered(playerId);

		if (RplSession.Mode() == RplMode.None)
		{
			applyClientData(playerId);
		}

		SCR_CTI_ClientData clientData = getClientData(playerId);
		if (!clientData)
		{
			clientData = new SCR_CTI_ClientData;
			clientData.setPlayerId(playerId);
			clientData.changeFunds(SCR_CTI_Constants.STARTFUNDS);
			ClientDataArray.Insert(clientData);

			Replication.BumpMe();
		}

		SCR_PlayerController pc = SCR_PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(playerId));
		if (pc)
		{
			SCR_PlayerFactionAffiliationComponent playerFactionAff = SCR_PlayerFactionAffiliationComponent.Cast(pc.FindComponent(SCR_PlayerFactionAffiliationComponent));

			if (playerFactionAff)
			{
				playerFactionAff.GetOnPlayerFactionResponseInvoker_O().Insert(OnPlayerFactionResponse_O);
				playerFactionAff.GetOnPlayerFactionResponseInvoker_S().Insert(OnPlayerFactionResponse_S);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerAuditSuccess(int iPlayerID)
	{
		super.OnPlayerAuditSuccess(iPlayerID);

		if (RplSession.Mode() != RplMode.None)
		{
			GetGame().GetCallqueue().CallLater(applyClientData, 100, false, iPlayerID);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void applyClientData(int playerId)
	{
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		if (!pc) return;

		SCR_CTI_ClientData clientData = getClientData(playerId);
		if (!clientData) return;

		int forcedFaction = clientData.getFactionIndex();

		if (forcedFaction != 0)
		{
			SCR_PlayerFactionAffiliationComponent playerFactionAff = SCR_PlayerFactionAffiliationComponent.Cast(pc.FindComponent(SCR_PlayerFactionAffiliationComponent));

			if (playerFactionAff)
			{
				Faction faction = GetGame().GetFactionManager().GetFactionByIndex(forcedFaction);
				playerFactionAff.RequestFaction(faction);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnPlayerFactionResponse_O(SCR_PlayerFactionAffiliationComponent component, int factionIndex, bool response)
	{
		if (!response) return;

		FactionManager factionManager = GetGame().GetFactionManager();
		if (!factionManager) return;

		SCR_Faction faction = SCR_Faction.Cast(factionManager.GetFactionByIndex(factionIndex));
		if (!faction) return;

		SCR_PlayerController playerController = SCR_PlayerController.Cast(component.GetPlayerController());
		if (!playerController) return;

		int playerID = playerController.GetPlayerId();

		if (SCR_PlayerController.GetLocalPlayerId() == playerID)
		{
			foreach (SCR_CTI_Town town : CTI_Towns)
			{
				SCR_CTI_TownMapDescriptorComponent mdc = SCR_CTI_TownMapDescriptorComponent.Cast(town.FindComponent(SCR_CTI_TownMapDescriptorComponent));
				if (mdc)
				{
					if (town.getFactionKey() == faction.GetFactionKey())
					{
						mdc.changeMarker(faction.GetFactionKey());
						continue;
					}
					if (town.getFactionKey() != "FIA" && town.getOldFactionKey() != "FIA")
					{
						mdc.changeMarker(town.getFactionKey());
					}
				}
			}

			// Necessary delay
			GetGame().GetCallqueue().CallLater(missionHintsCallLater, 20000, false, playerID);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnPlayerFactionResponse_S(SCR_PlayerFactionAffiliationComponent component, int factionIndex, bool response)
	{
		if (!response) return;

		FactionManager factionManager = GetGame().GetFactionManager();
		if (!factionManager) return;

		SCR_Faction faction = SCR_Faction.Cast(factionManager.GetFactionByIndex(factionIndex));
		if (!faction) return;

		SCR_PlayerController playerController = SCR_PlayerController.Cast(component.GetPlayerController());
		if (!playerController) return;

		int playerId = playerController.GetPlayerId();

		SCR_CTI_ClientData clientData = getClientData(playerId);

		if (clientData && faction)
		{
			clientData.setFactionIndex(factionManager.GetFactionIndex(faction));
			Replication.BumpMe();
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void missionHintsCallLater(int playerId)
	{
		SendHint(playerId, "htCTI Eden\nDefault menu key: Numpad 0", "Mission", 30);
		SendPopUpNotif(playerId, "<h1 align='left' scale='2'>                                   Arma Reforger CTI</h1>", 15, "", -1);
	}

	//------------------------------------------------------------------------------------------------
	/*override void OnPlayerSpawnFinalize_S(SCR_SpawnRequestComponent requestComponent, SCR_SpawnHandlerComponent handlerComponent, SCR_SpawnData data, IEntity entity)
	{
		super.OnPlayerSpawnFinalize_S(requestComponent, handlerComponent, data, entity);
	}*/

	//------------------------------------------------------------------------------------------------
	override void OnPlayerKilled(int playerId, IEntity playerEntity, IEntity killerEntity, notnull Instigator killer)
	{
		super.OnPlayerKilled(playerId, playerEntity, killerEntity, killer);

		int lastDeath;
		playersDeathTimes.Find(playerId, lastDeath);
		int currentMissionTime = GetElapsedTime();
		playersDeathTimes.Set(playerId, currentMissionTime);

		SCR_RespawnTimerComponent rtc = SCR_RespawnTimerComponent.Cast(this.FindComponent(SCR_RespawnTimerComponent));
		if (rtc)
		{
			switch (true)
			{
				case (currentMissionTime - lastDeath < 15): rtc.SetRespawnTime(playerId, 30); break;
				case (currentMissionTime - lastDeath < 30): rtc.SetRespawnTime(playerId, 20); break;
				default: rtc.SetRespawnTime(playerId, 15); break;
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void setTownsArray()
	{
		array<string> CTI_TownList = {"Town0", "Town1", "Town2", "Town3", "Town4", "Town5", "Town6", "Town7", "Town8", "Town9", "Town10", "Town11"};

		for (int i = 0; i < CTI_TownList.Count(); i++)
		{
			SCR_CTI_Town town = SCR_CTI_Town.Cast(GetGame().GetWorld().FindEntityByName(CTI_TownList[i]));
			CTI_Towns.Insert(town);
		}
		PrintFormat("CTI :: Number of Towns: %1", CTI_Towns.Count());
	}

	//------------------------------------------------------------------------------------------------
	int getCommanderId(FactionKey factionkey)
	{
		int Id = -2;

		switch (factionkey)
		{
			case "USSR": Id = ussrCommanderId; break;
			case "US": Id = usCommanderId; break;
		}

		return Id;
	}

	//------------------------------------------------------------------------------------------------
	void setCommanderId(FactionKey factionkey, int playerId)
	{
		RplIdentity commIdentity = GetGame().GetPlayerManager().GetPlayerController(playerId).GetRplIdentity();

		switch (factionkey)
		{
			case "USSR":
			{
				ussrCommanderId = playerId;

				foreach (RplId workerRplId : UpdateWorkersComponent.m_ussrWorkerRplIds)
				{
					RplComponent workerRplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
					workerRplComp.EnableStreamingForConnection(commIdentity, true);
				}

				break;
			}
			case "US":
			{
				usCommanderId = playerId;
				
				foreach (RplId workerRplId : UpdateWorkersComponent.m_usWorkerRplIds)
				{
					RplComponent workerRplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
					workerRplComp.EnableStreamingForConnection(commIdentity, true);
				}
				
				break;
			}
		}

		Replication.BumpMe();

		sendFactionNotifPAndF(factionkey, ENotification.CTI_NOTIF_COMMANDER_ASSIGNED, playerId);
	}

	//------------------------------------------------------------------------------------------------
	void clearCommanderId(FactionKey factionkey)
	{
		int cid = getCommanderId(factionkey);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(cid);
		RplIdentity commIdentity = RplIdentity.Invalid();
		if (pc) commIdentity = pc.GetRplIdentity();
		
		switch (factionkey)
		{
			case "USSR":
			{
				ussrCommanderId = -2;

				if (!commIdentity.IsValid()) break;
				foreach (RplId workerRplId : UpdateWorkersComponent.m_ussrWorkerRplIds)
				{
					RplComponent workerRplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
					workerRplComp.EnableStreamingForConnection(commIdentity, false);
				}
				
				break;
			}
			case "US":
			{
				usCommanderId = -2;

				if (!commIdentity.IsValid()) break;
				foreach (RplId workerRplId : UpdateWorkersComponent.m_usWorkerRplIds)
				{
					RplComponent workerRplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
					workerRplComp.EnableStreamingForConnection(commIdentity, false);
				}
				
				break;
			}
		}

		Replication.BumpMe();

		sendFactionNotifP(factionkey, ENotification.CTI_NOTIF_COMMANDER_LEFT);
	}

	//------------------------------------------------------------------------------------------------
	int getCommanderFunds(FactionKey factionkey)
	{
		int funds;

		switch (factionkey)
		{
			case "USSR": funds = ussrCommanderFunds; break;
			case "US": funds = usCommanderFunds; break;
		}

		return funds;
	}

	//------------------------------------------------------------------------------------------------
	// Only on server
	void changeCommanderFunds(FactionKey factionKey, int value)
	{
		switch (factionKey)
		{
			case "USSR": ussrCommanderFunds += value; break;
			case "US": usCommanderFunds += value; break;
		}

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	RplId getMHQrplId(FactionKey factionKey)
	{
		RplId mhqId = RplId.Invalid();

		switch (factionKey)
		{
			case "USSR": mhqId = ussrMHQrplId; break;
			case "US": mhqId = usMHQrplId; break;
		}

		return mhqId;
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	void setMHQrplId(FactionKey factionKey, RplId id)
	{
		switch (factionKey)
		{
			case "USSR": ussrMHQrplId = id; break;
			case "US": usMHQrplId = id; break;
		}

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	string getPriority(FactionKey factionKey)
	{
		string priority;

		switch (factionKey)
		{
			case "USSR": priority = ussrPriority; break;
			case "US": priority = usPriority; break;
		}

		return priority;
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	void setPriority(FactionKey factionKey, string townName)
	{
		switch (factionKey)
		{
			case "USSR": ussrPriority = townName; break;
			case "US": usPriority = townName; break;
		}

		Replication.BumpMe();

		if (townName != "None") sendFactionNotifP(factionKey, ENotification.CTI_NOTIF_TOWN_PRIORITY_CHANGED);
	}

	//------------------------------------------------------------------------------------------------
	SCR_CTI_ClientData getClientData(int playerId)
	{
		SCR_CTI_ClientData clientData = null;
		if (playerId < 1) return clientData;

		int sizeCDA = ClientDataArray.Count();
		for (int i = 0; i < sizeCDA; i++)
		{
			if (ClientDataArray[i].getPlayerId() == playerId)
			{
				clientData = ClientDataArray[i];
				break;
			}
		}

		return clientData;
	}

	//------------------------------------------------------------------------------------------------
	// For remoted update
	void bumpMeServer()
	{
		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	void delayedRepair(int playerId, RplId rplid)
	{
		// TODO check rep near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		SCR_CTI_VehicleCustomVariablesComponent vcvc = SCR_CTI_VehicleCustomVariablesComponent.Cast(ent.FindComponent(SCR_CTI_VehicleCustomVariablesComponent));

		if (vcvc && vcvc.getSupportVehicleType() == CTI_SupportVehicleTypes.MHQ && vehicleDamageManager.IsDestroyed())
		{
			FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
			SCR_CTI_RepairMHQ.repairMHQ(faffComp.GetDefaultAffiliatedFaction().GetFactionKey());
			return;
		}

		if (!vehicleDamageManager.IsDestroyed()) vehicleDamageManager.FullHeal();

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle</color> repaired!", "Information", 5);
	}

	//------------------------------------------------------------------------------------------------
	void delayedRearm(int playerId, RplId rplid)
	{
		// TODO check ammo near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(ent.FindComponent(SCR_BaseCompartmentManagerComponent));

			array<BaseCompartmentSlot> outCompartments = {};
			bcmc.GetCompartments(outCompartments);

			foreach (BaseCompartmentSlot slot : outCompartments)
			{
				if (slot.Type() == TurretCompartmentSlot)
				{
					TurretControllerComponent tcc = TurretControllerComponent.Cast(slot.GetController());
					BaseWeaponManagerComponent bwmc = tcc.GetWeaponManager();

					array<IEntity> outWeapons = {};
					bwmc.GetWeaponsList(outWeapons);

					if (outWeapons.IsEmpty()) return;

					foreach (IEntity weapon : outWeapons)
					{
						WeaponComponent wc = WeaponComponent.Cast(weapon.FindComponent(WeaponComponent));
						BaseMagazineComponent bmc = wc.GetCurrentMagazine();

						bmc.SetAmmoCount(bmc.GetMaxAmmoCount());
					}
				}
			}
		}

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle</color> rearmed!", "Information", 5);
	}

	//------------------------------------------------------------------------------------------------
	void delayedRefuel(int playerId, RplId rplid)
	{
		// TODO check fuel near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			FuelManagerComponent fuelManagerComp = FuelManagerComponent.Cast(ent.FindComponent(FuelManagerComponent));
			array<BaseFuelNode> outNodes = {};
			fuelManagerComp.GetFuelNodesList(outNodes);

			foreach (BaseFuelNode node : outNodes)
			{
				node.SetFuel(node.GetMaxFuel());
			}
		}

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle</color> refuelled!", "Information", 5);
	}

	//------------------------------------------------------------------------------------------------
	void delayedHeal(int playerId, RplId rplid)
	{
		// TODO rep near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(ent.FindComponent(SCR_BaseCompartmentManagerComponent));
			array<IEntity> occupants = {};
			bcmc.GetOccupants(occupants);

			foreach (IEntity crew : occupants)
			{
				if (!crew) break;
				SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(crew.FindComponent(SCR_CharacterDamageManagerComponent));
				if (!cdmc.IsDestroyed()) cdmc.FullHeal();
			}
		}

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle crew</color> healed!", "Information", 5);
	}

	//------------------------------------------------------------------------------------------------
	void sendFactionNotifPAndF(FactionKey factionkey, ENotification notification, int param1)
	{
		array<int> outPlayers = {};
		GetGame().GetPlayerManager().GetPlayers(outPlayers);

		foreach (int pid : outPlayers)
		{
			Faction playerFaction = SCR_FactionManager.SGetPlayerFaction(pid);
			if (!playerFaction) continue;
			if (playerFaction.GetFactionKey() == factionkey) SCR_NotificationsComponent.SendToPlayer(pid, notification, param1);
		}
	}

	//------------------------------------------------------------------------------------------------
	void sendFactionNotifP(FactionKey factionkey, ENotification notification)
	{
		array<int> outPlayers = {};
		GetGame().GetPlayerManager().GetPlayers(outPlayers);

		foreach (int pid : outPlayers)
		{
			Faction playerFaction = SCR_FactionManager.SGetPlayerFaction(pid);
			if (!playerFaction) continue;
			if (playerFaction.GetFactionKey() == factionkey) SCR_NotificationsComponent.SendToPlayer(pid, notification);
		}
	}

	//------------------------------------------------------------------------------------------------
	void sendFactionNotifT(FactionKey factionkey, ENotification notification, int param1)
	{
		array<int> outPlayers = {};
		GetGame().GetPlayerManager().GetPlayers(outPlayers);

		foreach (int pid : outPlayers)
		{
			Faction playerFaction = SCR_FactionManager.SGetPlayerFaction(pid);
			if (!playerFaction) continue;
			if (playerFaction.GetFactionKey() == factionkey) SCR_NotificationsComponent.SendToPlayer(pid, notification, param1);
		}
	}

	//------------------------------------------------------------------------------------------------
	void sendFactionNotifF(FactionKey factionkey, ENotification notification, int param1, int param2, int param3, int param4, int param5)
	{
		array<int> outPlayers = {};
		GetGame().GetPlayerManager().GetPlayers(outPlayers);

		foreach (int pid : outPlayers)
		{
			Faction playerFaction = SCR_FactionManager.SGetPlayerFaction(pid);
			if (!playerFaction) continue;
			if (playerFaction.GetFactionKey() == factionkey) SCR_NotificationsComponent.SendToPlayer(pid, notification, param1, param2, param3, param4, param5);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SendHint(int playerId, string message = "", string messageTitle = "", int hintTime = 5.0)
	{
		if (RplSession.Mode() == RplMode.Dedicated)
		{
			Rpc(RpcDo_RecieveHint, playerId, message, messageTitle, hintTime);
		} else {
			RpcDo_RecieveHint(playerId, message, messageTitle, hintTime);
		}
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void RpcDo_RecieveHint(int playerId, string message, string messageTitle, int hintTime)
	{
		int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
		if (playerId != localPlayerId) return;

		SCR_HintManagerComponent.ShowCustomHint(message, messageTitle, hintTime);
	}

	//------------------------------------------------------------------------------------------------
	void SendPopUpNotif(int playerId, string message = "", float duration = 5.0, string message2 = "", int prio = -1)
	{
		if (RplSession.Mode() == RplMode.Dedicated)
		{
			Rpc(RpcDo_RecievePopUpNotif, playerId, message, duration, message2, prio);
		} else {
			RpcDo_RecievePopUpNotif(playerId, message, duration, message2, prio);
		}
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void RpcDo_RecievePopUpNotif(int playerId, string message, float duration, string message2, int prio)
	{
		int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
		if (playerId != localPlayerId) return;

		SCR_PopUpNotification popUpNotif = SCR_PopUpNotification.GetInstance();
		popUpNotif.PopupMsg(message, duration, message2);
	}

	//------------------------------------------------------------------------------------------------
	void OnPrioMapOpen(MapConfiguration config)
	{
		//if (!SCR_PlayerController.GetLocalControlledEntity()) return;

		SCR_MapEntity mapEntity = SCR_MapEntity.GetMapInstance();
		mapEntity.ZoomOut();
	}

	//------------------------------------------------------------------------------------------------
	void OnPrioMapSelection(vector selectionPos)
	{
		// TODO Check new selection pos thing!
		SCR_MapEntity mapEntity = SCR_MapEntity.GetMapInstance();

		float worldX;
		float worldY;
		mapEntity.GetMapCursorWorldPosition(worldX, worldY);

		vector cursortarget;
		cursortarget[0] = worldX;
		cursortarget[2] = worldY;

		SCR_CTI_Town town = SCR_CTI_GetTownFromMapCoords.GetTownFromMapCoords(cursortarget, CTI_Towns);

		PlayerController pc = GetGame().GetPlayerController();
		FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));

		netComp.setPriorityServer(affiliationComp.GetAffiliatedFaction().GetFactionKey(), town.getTownName());

		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();
	}

	//------------------------------------------------------------------------------------------------
	void OnPrioMapClose(MapConfiguration config)
	{
		SCR_MapEntity.GetOnMapOpen().Remove(OnPrioMapOpen);
		SCR_MapEntity.GetOnSelection().Remove(OnPrioMapSelection);
		SCR_MapEntity.GetOnMapClose().Remove(OnPrioMapClose);
	}

	//------------------------------------------------------------------------------------------------
	protected void loadUserSettings()
	{
		SCR_JsonLoadContext loadContext = new SCR_JsonLoadContext();
		bool found = loadContext.LoadFromFile("$profile:.save\\htCTI_VideoSettings.json");

		if (found)
		{
			float vd, tg;
			loadContext.ReadValue("VD", vd);
			loadContext.ReadValue("TG", tg);

			if (vd) GetGame().SetViewDistance(vd);
			if (tg) GetGame().SetGrassDistance(tg);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_GameMode(IEntitySource src, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GameMode()
	{
		if (CTI_Towns) CTI_Towns.Clear();
		CTI_Towns = null;

		UnitsFIA = null;
		UnitsUSSR = null;
		UnitsUS = null;

		FactoriesUSSR = null;
		FactoriesUS = null;
		DefensesUSSR = null;
		DefensesUS = null;

		Upgrades = null;

		if (ClientDataArray) ClientDataArray.Clear();
		ClientDataArray = null;

		if (playersDeathTimes) playersDeathTimes.Clear();
		playersDeathTimes = null;
	}
};