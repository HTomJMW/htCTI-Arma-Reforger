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

	const int MAXBASES = 2;
	const int BASERADIUS = 100;
	const int BUILDRANGE = 100;
	const bool ECOWIN = true;
	const int WINRATE = 75;
	const int STARTFUNDS = 2400;
	const int STARTCOMMFUNDS = 7500;
	const int BASEINCOME = 50;
	const float AISKILL = 0.75;
	const ResourceName USSRMHQ = "{1BABF6B33DA0AEB6}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_command.et";
	const ResourceName USMHQ = "{36BDCC88B17B3BFA}Prefabs/Vehicles/Wheeled/M923A1/M923A1_command.et";
	const string USSRMHQNAME = "CTI_USSR_MHQ";
	const string USMHQNAME = "CTI_US_MHQ";

	protected int playerGroupSize = 8;

	[RplProp()]
	protected int ussrCommanderId = -2;
	[RplProp()]
	protected int usCommanderId = -2;
	[RplProp()]
	protected int ussrCommanderFunds = STARTCOMMFUNDS;
	[RplProp()]
	protected int usCommanderFunds = STARTCOMMFUNDS;

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
		
		StartGameMode();
		if (!m_RplComponent.IsProxy()) PrintFormat("CTI :: GameMode running: %1", IsRunning().ToString());
		if (RplSession.Mode() == RplMode.Dedicated)
		{
			Print("CTI :: Server: Dedicated");
		} else {
			Print("CTI :: Server: Player-Hosted");
		}

		// Common
		townsArray();
		initMap();

		BaseComponent.init();
		UpgradeComponent.init();

		GetGame().GetInputManager().AddActionListener("CTI_OpenMainMenu", EActionTrigger.DOWN, openMenu);
		
		// Server
		if (!m_RplComponent.IsProxy())
		{
			WeatherAndTimeComponent.init();
			RandomStartComponent.init();
			UpdateVictoryComponent.init();
			UpdateResourcesComponent.init();
		} else {
			// Client
			WeatherAndTimeComponent.Deactivate(this);
			UpdateVictoryComponent.Deactivate(this);
			UpdateResourcesComponent.Deactivate(this);
			
			PlayerController pc = GetGame().GetPlayerController();
			int playerId = pc.GetPlayerId();
			RpcDo_RecieveHint(playerId, "htCTI Eden", "Mission", 45);
			RpcDo_RecievePopUpNotif(playerId, "Arma Reforger CTI", 20, 0.25, "", -1);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void openMenu()
	{
		GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
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
		FactionManager fm = GetGame().GetFactionManager();

		if (!clientData)
		{
			clientData = new SCR_CTI_ClientData;
			clientData.setPlayerId(playerId);
			clientData.changeFunds(STARTFUNDS);
			ClientDataArray.Insert(clientData);
		} else {
			int forcedFaction = fm.GetFactionIndex(clientData.getFaction());
			respawnSystem.DoSetPlayerFaction(playerId, forcedFaction);
		}
		
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	override void HandleOnFactionAssigned(int playerID, Faction assignedFaction)
	{
		super.HandleOnFactionAssigned(playerID, assignedFaction);
		
		if (!m_RplComponent.IsProxy())
		{
			SCR_CTI_ClientData clientData = getClientData(playerID);

			if (clientData && assignedFaction)
				clientData.setFaction(assignedFaction);
			
				int factionIndex = GetGame().GetFactionManager().GetFactionIndex(assignedFaction);
				clientData.setFactionIndex(factionIndex);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void townsArray()
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
	protected void initMap()
	{
		foreach (SCR_CTI_Town town : CTI_Towns)
		{
			town.initMapComponent();
		}
	}

	//------------------------------------------------------------------------------------------------
	int getPlayerGroupSize()
	{
		return playerGroupSize;
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
	void SendPopUpNotif(int playerId, string message = "", float duration = 5.0, float fade = 0.5, string message2 = "", int prio = -1)
	{
        Rpc(RpcDo_RecievePopUpNotif, playerId, message, duration, fade, message2, prio);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
    protected void RpcDo_RecievePopUpNotif(int playerId, string message, float duration, float fade, string message2, int prio)
    {
        int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
        if(playerId != localPlayerId) return;

		SCR_PopUpNotification popUpNotif = SCR_PopUpNotification.GetInstance();
		popUpNotif.PopupMsg(message, duration, fade, message2);
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
	}
};