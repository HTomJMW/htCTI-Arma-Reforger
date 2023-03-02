[EntityEditorProps(category: "GameScripted/CTI", description: "CTI GameMode")]
class SCR_CTI_GameModeClass: SCR_BaseGameModeClass
{
};

class SCR_CTI_GameMode : SCR_BaseGameMode
{
	ref array<SCR_CTI_Town> CTI_Towns = {};

	protected SCR_CTI_WeatherAndTimeComponent WeatherAndTimeComponent;
	protected SCR_CTI_RandomStartComponent RandomStartComponent;
	protected SCR_CTI_UpdateVictoryComponent UpdateVictoryComponent;
	protected SCR_CTI_UpgradeComponent UpgradeComponent;
	protected SCR_CTI_BaseComponent BaseComponent;
	protected SCR_CTI_UpdateResourcesComponent UpdateResourcesComponent;

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
	protected string ussrPriority;
	[RplProp()]
	protected string usPriority;

	[RplProp()]
	ref array<ref SCR_CTI_ClientData> ClientDataArray = new array<ref SCR_CTI_ClientData>;

	ref SCR_CTI_UnitsFIA UnitsFIA = new SCR_CTI_UnitsFIA();
	ref SCR_CTI_UnitsUSSR UnitsUSSR = new SCR_CTI_UnitsUSSR();
	ref SCR_CTI_UnitsUS UnitsUS = new SCR_CTI_UnitsUS();

	ref SCR_CTI_FactoriesUSSR FactoriesUSSR = new SCR_CTI_FactoriesUSSR();
	ref SCR_CTI_FactoriesUS FactoriesUS = new SCR_CTI_FactoriesUS();
	ref SCR_CTI_DefensesUSSR DefensesUSSR = new SCR_CTI_DefensesUSSR();
	ref SCR_CTI_DefensesUS DefensesUS = new SCR_CTI_DefensesUS();
	
	ref SCR_CTI_GearUSSR GearUSSR = new SCR_CTI_GearUSSR();
	ref SCR_CTI_GearUS GearUS = new SCR_CTI_GearUS();

	ref SCR_CTI_Upgrades Upgrades = new SCR_CTI_Upgrades();

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
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnGameStart()
	{
		super.OnGameStart();

		if (!m_RplComponent.IsProxy())
		{
			StartGameMode();
			PrintFormat("CTI :: GameMode running: %1", IsRunning().ToString());
			
			if (RplSession.Mode() == RplMode.Dedicated)
			{
				Print("CTI :: Server: Dedicated");
			} else {
				Print("CTI :: Server: Player-Hosted");
			}
		}

		// Common
		uploadTownsArray();
		
		foreach (SCR_CTI_Town town : CTI_Towns)
		{
			SCR_CTI_TownMapDescriptorComponent mdc = SCR_CTI_TownMapDescriptorComponent.Cast(town.FindComponent(SCR_CTI_TownMapDescriptorComponent));
			if (mdc) mdc.createMarker(town.getFactionKey());
		}

		BaseComponent.init();
		UpgradeComponent.init();

		GetGame().GetInputManager().AddActionListener("CTI_OpenMainMenu", EActionTrigger.DOWN, openMenu);

		GetGame().GetInputManager().AddActionListener("Inventory", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("CharacterDropItem", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("Inventory_StepBack", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("CharacterAction", EActionTrigger.UP, saveLoadout);
		GetGame().GetInputManager().AddActionListener("CharacterReload", EActionTrigger.UP, saveLoadout);

		// Server
		if (!m_RplComponent.IsProxy())
		{
			WeatherAndTimeComponent.randomStartTime();
			RandomStartComponent.randomStart();
			UpdateVictoryComponent.init();
		} else {
			// Client
			WeatherAndTimeComponent.Deactivate(this);
			UpdateVictoryComponent.Deactivate(this);
			UpdateResourcesComponent.Deactivate(this);
			
			loadUserSettings();
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void openMenu()
	{
		GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
	}

	//------------------------------------------------------------------------------------------------
	protected void saveLoadout()
	{
		// save loadout
		PlayerController pc = GetGame().GetPlayerController();
		IEntity controlledEnt = pc.GetControlledEntity();
		RplComponent rplComp = RplComponent.Cast(controlledEnt.FindComponent(RplComponent));
		if (!rplComp) return;
		RplId rplid = rplComp.Id();
		SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
		if (netComp)
		{
			netComp.savePlayerLoadout(pc.GetPlayerId(), rplid);
		}

		// set saved loadout for use at next respawn
		SCR_RespawnComponent respawnComp = SCR_RespawnComponent.GetInstance();
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
			respawnComp.RequestPlayerLoadout(savedLoadout);
		} else {
			SCR_RespawnComponent.GetInstance().RequestClearPlayerLoadout();
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerDisconnected(int playerId, KickCauseCode cause,  int timeout)
	{
		super.OnPlayerDisconnected(playerId, cause, timeout);

		SCR_CTI_ClientData clientData = getClientData(playerId);
		
		if (clientData && clientData.isCommander()) clientData.setCommander(false);

		if (playerId == ussrCommanderId)
		{
			clearCommanderId("USSR");
		}
		if (playerId == usCommanderId)
		{
			clearCommanderId("US");
		}
		
		PlayerManager pm = GetGame().GetPlayerManager();
		PrintFormat("CTI :: Player %1 disconnected", pm.GetPlayerName(playerId));
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerRegistered(int playerId)
	{
		super.OnPlayerRegistered(playerId);

		SCR_CTI_ClientData clientData = getClientData(playerId);
		
		SCR_RespawnSystemComponent respawnSystem = SCR_RespawnSystemComponent.Cast(GetRespawnSystemComponent());

		if (!clientData)
		{
			clientData = new SCR_CTI_ClientData;
			clientData.setPlayerId(playerId);
			clientData.changeFunds(SCR_CTI_Constants.STARTFUNDS);
			ClientDataArray.Insert(clientData);
			
			Replication.BumpMe();
		} else {
			int forcedFactionIndex = clientData.getFactionIndex();
			respawnSystem.DoSetPlayerFaction(playerId, forcedFactionIndex);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void HandleOnFactionAssigned(int playerID, Faction assignedFaction)
	{
		super.HandleOnFactionAssigned(playerID, assignedFaction);
		
		if (!m_RplComponent.IsProxy())
		{
			SCR_CTI_ClientData clientData = getClientData(playerID);

			if (clientData && assignedFaction)
			{
				int factionIndex = GetGame().GetFactionManager().GetFactionIndex(assignedFaction);
				clientData.setFactionIndex(factionIndex);
				Replication.BumpMe();
			}
		}

		// necessary delay due to proxy playercontroller check
		GetGame().GetCallqueue().CallLater(missionHintsCallLater, 20000, false, playerID);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void missionHintsCallLater(int playerId)
	{
		SendHint(playerId, "htCTI Eden", "Mission", 30);
		SendPopUpNotif(playerId, "Arma Reforger CTI", 20, "", -1);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerSpawned(int playerId, IEntity controlledEntity)
	{
		super.OnPlayerSpawned(playerId, controlledEntity);
		
		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		SCR_AIGroup group = gmc.GetPlayerGroup(playerId);
		int groupId = group.GetID();
		
		SCR_CTI_ClientData clientData = getClientData(playerId);
		if (clientData && clientData.getGroupId() == -1)
		{
			clientData.setGroupId(groupId);
			Replication.BumpMe();
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void uploadTownsArray()
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
		switch (factionkey)
		{
			case "USSR":
			{
				ussrCommanderId = playerId;
				break;
			}
			case "US":
			{
				usCommanderId = playerId;
				break;
			}
		}
		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	void clearCommanderId(FactionKey factionkey)
	{
		switch (factionkey)
		{
			case "USSR":
			{
				ussrCommanderId = -2;
				break;
			}
			case "US":
			{
				usCommanderId = -2;
				break;
			}
		}
		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	int getCommanderFunds(FactionKey fk)
	{
		int funds;
		switch (fk)
		{
			case "USSR": funds = ussrCommanderFunds; break;
			case "US": funds = usCommanderFunds; break;
		}
		
		return funds;
	}

	//------------------------------------------------------------------------------------------------
	// Only on server
	void changeCommanderFunds(FactionKey fk, int value)
	{
		switch (fk)
		{
			case "USSR": ussrCommanderFunds += value; break;
			case "US": usCommanderFunds += value; break;
		}
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	RplId getMHQrplId(FactionKey fk)
	{
		RplId mhqId = null;
		switch (fk)
		{
			case "USSR": mhqId = ussrMHQrplId; break;
			case "US": mhqId = usMHQrplId; break;
		}
		
		return mhqId;
	}
	
	//------------------------------------------------------------------------------------------------
	// Only on Server
	void setMHQrplId(FactionKey fk, RplId id)
	{
		switch (fk)
		{
			case "USSR": ussrMHQrplId = id; break;
			case "US": usMHQrplId = id; break;
		}
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	string getPriority(FactionKey fk)
	{
		string priority;
		switch (fk)
		{
			case "USSR": priority = ussrPriority; break;
			case "US": priority = usPriority; break;
		}
		
		return priority;
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	void setPriority(FactionKey fk, string townName)
	{
		switch (fk)
		{
			case "USSR": ussrPriority = townName; break;
			case "US": usPriority = townName; break;
		}
		
		Replication.BumpMe();
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
	void bumpMeServer()
	{
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	void SendHint(int playerId, string message = "", string messageTitle = "", int hintTime = 5.0)
    {
        Rpc(RpcDo_RecieveHint, playerId, message, messageTitle, hintTime);
    }
   
	//------------------------------------------------------------------------------------------------
    [RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
    protected void RpcDo_RecieveHint(int playerId, string message, string messageTitle, int hintTime)
    {
        int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
        if(playerId != localPlayerId) return;
        
        SCR_HintManagerComponent.ShowCustomHint(message, messageTitle, hintTime);
    }

	//------------------------------------------------------------------------------------------------
	void SendPopUpNotif(int playerId, string message = "", float duration = 5.0, string message2 = "", int prio = -1)
	{
        Rpc(RpcDo_RecievePopUpNotif, playerId, message, duration, message2, prio);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
    protected void RpcDo_RecievePopUpNotif(int playerId, string message, float duration, string message2, int prio)
    {
        int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
        if(playerId != localPlayerId) return;

		SCR_PopUpNotification popUpNotif = SCR_PopUpNotification.GetInstance();
		popUpNotif.PopupMsg(message, duration, message2);
    }
	
	//------------------------------------------------------------------------------------------------
	void UpdateMHQSpawnPoint(RplId spId, vector pos)
	{
        Rpc(RpcDo_UpdateMHQSpawnPoint, spId, pos);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
    protected void RpcDo_UpdateMHQSpawnPoint(RplId spId, vector pos)
    {
		SCR_SpawnPoint sp = SCR_SpawnPoint.Cast(Replication.FindItem(spId));
		sp.SetOrigin(pos);
    }

	//------------------------------------------------------------------------------------------------
	protected void OnPrioMapOpen()
	{
		//if (!SCR_PlayerController.GetLocalControlledEntity()) return;

		SCR_MapEntity mapEntity = SCR_MapEntity.GetMapInstance();
		mapEntity.ZoomOut();
	}

	//------------------------------------------------------------------------------------------------
	protected void OnPrioMapSelection()
	{
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
		
		setPriority(affiliationComp.GetAffiliatedFaction().GetFactionKey(), town.getTownName());

		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();
	}

	//------------------------------------------------------------------------------------------------
	protected void OnPrioMapClose()
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
		CTI_Towns.Clear();
		CTI_Towns = null;
		
		UnitsFIA = null;
		UnitsUSSR = null;
		UnitsUS = null;
		
		FactoriesUSSR = null;
		FactoriesUS = null;
		DefensesUSSR = null;
		DefensesUS = null;
		
		Upgrades = null;

		ClientDataArray.Clear();
		ClientDataArray = null;
	}
};