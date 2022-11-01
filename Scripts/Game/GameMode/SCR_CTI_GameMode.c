[EntityEditorProps(category: "GameScripted/CTI", description: "CTI GameMode")]
class SCR_CTI_GameModeClass: SCR_BaseGameModeClass
{
};

class SCR_CTI_GameMode : SCR_BaseGameMode
{
	ref array<SCR_CTI_Town> CTI_Towns = {};
	ref array<string> CTI_TownList = {"Town0", "Town1", "Town2", "Town3", "Town4", "Town5", "Town6", "Town7", "Town8", "Town9", "Town10", "Town11"};

	protected SCR_CTI_WeatherAndTimeComponent WeatherAndTimeComponent;
	protected SCR_CTI_RandomStartComponent RandomStartComponent;
	protected SCR_CTI_UpdateVictoryComponent UpdateVictoryComponent;
	protected SCR_CTI_UpdateResourcesComponent UpdateResourcesComponent;
	protected SCR_CTI_UpgradeComponent UpgradeComponent;
	protected SCR_CTI_BaseComponent BaseComponent;

	const int MAXBASES = 2;
	const bool ECOWIN = true;
	const int WINRATE = 75;
	const int STARTFUNDS = 2400;
	const int STARTCOMMFUNDS = 7500;
	const float AISKILL = 0.75;
	
	protected int playerGroupSize = 8;

	[RplProp()]
	protected int ussrCommanderId = -2;
	[RplProp()]
	protected int usCommanderId = -2;
	[RplProp()]
	protected int ussrCommanderFunds = STARTCOMMFUNDS;
	[RplProp()]
	protected int usCommanderFunds = STARTCOMMFUNDS;
	
	ref array<ref SCR_CTI_ClientData> ClientDataArray = new array<ref SCR_CTI_ClientData>;

	ref SCR_CTI_UnitsFIA UnitsFIA = new SCR_CTI_UnitsFIA();
	ref SCR_CTI_UnitsUSSR UnitsUSSR = new SCR_CTI_UnitsUSSR();
	ref SCR_CTI_UnitsUS UnitsUS = new SCR_CTI_UnitsUS();

	ref SCR_CTI_FactoriesUSSR FactoriesUSSR = new SCR_CTI_FactoriesUSSR();
	ref SCR_CTI_FactoriesUS FactoriesUS = new SCR_CTI_FactoriesUS();
	ref SCR_CTI_DefensesUSSR DefensesUSSR = new SCR_CTI_DefensesUSSR();
	ref SCR_CTI_DefensesUS DefensesUS = new SCR_CTI_DefensesUS();

	ref SCR_CTI_Upgrades UpgradesUSSR = new SCR_CTI_Upgrades();
	ref SCR_CTI_Upgrades UpgradesUS = new SCR_CTI_Upgrades();

	//------------------------------------------------------------------------------------------------
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		WeatherAndTimeComponent = SCR_CTI_WeatherAndTimeComponent.Cast(owner.FindComponent(SCR_CTI_WeatherAndTimeComponent));
		RandomStartComponent = SCR_CTI_RandomStartComponent.Cast(owner.FindComponent(SCR_CTI_RandomStartComponent));
		UpdateVictoryComponent = SCR_CTI_UpdateVictoryComponent.Cast(owner.FindComponent(SCR_CTI_UpdateVictoryComponent));
		UpdateResourcesComponent = SCR_CTI_UpdateResourcesComponent.Cast(owner.FindComponent(SCR_CTI_UpdateResourcesComponent));
		UpgradeComponent = SCR_CTI_UpgradeComponent.Cast(owner.FindComponent(SCR_CTI_UpgradeComponent));
		BaseComponent = SCR_CTI_BaseComponent.Cast(owner.FindComponent(SCR_CTI_BaseComponent));
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
		townsToArray();
		initMap();

		UnitsFIA.init();
		UnitsUSSR.init();
		UnitsUS.init();
		
		FactoriesUSSR.init();
		FactoriesUS.init();
		DefensesUSSR.init();
		DefensesUS.init();
		
		UpgradesUSSR.init();
		UpgradesUS.init();
		
		BaseComponent.init();
		UpgradeComponent.init();

		// Server
		if (!m_RplComponent.IsProxy())
		{
			WeatherAndTimeComponent.init();
			RandomStartComponent.init();
			UpdateVictoryComponent.init();
			UpdateResourcesComponent.Deactivate(this); // disabled on server
		} else {
			UpdateResourcesComponent.init(); // run on proxys temporary
			WeatherAndTimeComponent.Deactivate(this); // force disabled on proxy
			UpdateVictoryComponent.Deactivate(this);
		}

		// Client or Player-Hosted server (not dedicated server)
		if (m_RplComponent.IsProxy() || m_RplComponent.IsMaster())
		{
			GetGame().GetInputManager().AddActionListener("CTI_OpenMainMenu", EActionTrigger.DOWN, openMenu);

			PlayerController pc = GetGame().GetPlayerController();
			int playerId = pc.GetPlayerId();
			SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
			netComp.SendHint(playerId, "htCTI Eden", "Mission", 15);
			netComp.SendPopUpNotif(playerId, "Arma Reforger", 15, 0.25, "");
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void openMenu()
	{
		GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerSpawned(int playerId, IEntity controlledEntity)
	{
		super.OnPlayerSpawned(playerId, controlledEntity);

		if (playerId < 1) return;
			
		int sizeCDA = ClientDataArray.Count();
		SCR_CTI_ClientData clientData;
		for (int i = 0; i < sizeCDA; i++)
		{
			if (ClientDataArray[i].getPlayerId() == playerId)
			{
				clientData = ClientDataArray[i];
				break;
			}
		}
		
		if (clientData)
		{
			int funds = clientData.getFunds();
			string name = clientData.getPlayerName();
			PrintFormat("CTI :: Player: %1, PlayerId: %2, Funds: %3", name, playerId, funds);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerKilled(int playerId, IEntity player, IEntity killer)
	{
		super.OnPlayerKilled(playerId, player, killer);

		if (playerId < 1) return;
		
		int sizeCDA = ClientDataArray.Count();
		SCR_CTI_ClientData clientData;
		for (int i = 0; i < sizeCDA; i++)
		{
			if (ClientDataArray[i].getPlayerId() == playerId)
			{
				clientData = ClientDataArray[i];
				break;
			}
		}

		if (clientData)
		{
			// todo
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerConnected(int playerId)
	{
		super.OnPlayerConnected(playerId);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerDisconnected(int playerId, KickCauseCode cause)
	{
		super.OnPlayerDisconnected(playerId, cause);
		
		if (playerId < 1) return;

		int sizeCDA = ClientDataArray.Count();
		int removeIndex = -1;
		for (int i = 0; i < sizeCDA; i++)
		{
			if (ClientDataArray[i].getPlayerId() == playerId)
			{
				removeIndex = i;
				break;
			}
		}
		if (removeIndex != -1) 
		{
			if (playerId == ussrCommanderId)
			{
				ussrCommanderId = -2;
				Replication.BumpMe();
			}
			if (playerId == usCommanderId)
			{
				usCommanderId = -2;
				Replication.BumpMe();
			}
		
			ClientDataArray.Remove(removeIndex);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPlayerRegistered(int playerId)
	{
		super.OnPlayerRegistered(playerId);
		
		if (playerId < 1) return;

		int sizeCDA = ClientDataArray.Count();
		SCR_CTI_ClientData clientData;
		for (int i = 0; i < sizeCDA; i++)
		{
			if (ClientDataArray[i].getPlayerId() == playerId)
			{
				clientData = ClientDataArray[i];
				break;
			}
		}

		if (!clientData)
		{
			clientData = new SCR_CTI_ClientData;
			clientData.setPlayerId(playerId);
			clientData.changeFunds(STARTFUNDS);
			ClientDataArray.Insert(clientData);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void townsToArray()
	{
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
	void SCR_CTI_GameMode(IEntitySource src, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GameMode()
	{
		CTI_Towns.Clear();
		CTI_Towns = null;
		
		ClientDataArray.Clear();
		ClientDataArray = null;
		
		UnitsFIA = null;
		UnitsUSSR = null;
		UnitsUS = null;
		
		FactoriesUSSR = null;
		FactoriesUS = null;
		DefensesUSSR = null;
		DefensesUS = null;
		
		UpgradesUSSR = null;
		UpgradesUS = null;
	}
};