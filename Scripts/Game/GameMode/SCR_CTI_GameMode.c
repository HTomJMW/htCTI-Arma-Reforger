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
	
	protected SCR_HintManagerComponent HintManagerComponent;
	protected SCR_PopUpNotification popUpNotif;
	
	ref array<ref SCR_CTI_ClientData> ClientDataArray = new array<ref SCR_CTI_ClientData>;
	
	ref SCR_CTI_UnitsFIA UnitsFIA = new SCR_CTI_UnitsFIA();
	ref SCR_CTI_UnitsUSSR UnitsUSSR = new SCR_CTI_UnitsUSSR();
	ref SCR_CTI_UnitsUS UnitsUS = new SCR_CTI_UnitsUS();
	
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		WeatherAndTimeComponent = SCR_CTI_WeatherAndTimeComponent.Cast(owner.FindComponent(SCR_CTI_WeatherAndTimeComponent));
		RandomStartComponent = SCR_CTI_RandomStartComponent.Cast(owner.FindComponent(SCR_CTI_RandomStartComponent));
		UpdateVictoryComponent = SCR_CTI_UpdateVictoryComponent.Cast(owner.FindComponent(SCR_CTI_UpdateVictoryComponent));
		UpdateResourcesComponent = SCR_CTI_UpdateResourcesComponent.Cast(owner.FindComponent(SCR_CTI_UpdateResourcesComponent));
		
		HintManagerComponent = SCR_HintManagerComponent.Cast(owner.FindComponent(SCR_HintManagerComponent));
		popUpNotif = SCR_PopUpNotification.GetInstance();
	}

	protected override void OnGameStart()
	{
		super.OnGameStart();
		
		StartGameMode();
		PrintFormat("CTI :: GameMode running: %1", IsRunning().ToString());
		if (RplSession.Mode() == RplMode.Dedicated)
		{
			Print("CTI :: Server: Dedicated");
		} else {
			Print("CTI :: Server: Player-Hosted");
		}

		townsToArray();
		initMap();
		
		WeatherAndTimeComponent.init();
		RandomStartComponent.init();
		UpdateVictoryComponent.init();
		UpdateResourcesComponent.init();

		UnitsFIA.init();
		UnitsUSSR.init();
		UnitsUS.init();

		if (m_RplComponent.IsProxy() || m_RplComponent.IsMaster())
		{
			SCR_HintManagerComponent.ShowCustomHint("htCTI Eden", "Mission", 15);
			//popUpNotif.PopupMsg("Arma Reforger", 15, 0.25, "");
			
			PlayerController pc = GetGame().GetPlayerController();
			int playerId = pc.GetPlayerId();
			
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
				PrintFormat("CTI :: Player: %1 PlayerId: %2, Funds: %3", name, playerId, funds);
			}
		}
		PrintFormat("CTI :: Client Data Array: %1", ClientDataArray);
	}
	
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
			popUpNotif.PopupMsg(("Funds: " + funds.ToString()), 10, 0.25, "");
		}
	}

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
	
	override void OnPlayerConnected(int playerId)
	{
		super.OnPlayerConnected(playerId);
	}
	
	override void OnPlayerDisconnected(int playerId)
	{
		super.OnPlayerDisconnected(playerId);
		
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
		if (removeIndex != -1) ClientDataArray.Remove(removeIndex);
	}
	
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
			ClientDataArray.Insert(clientData);
		}
			
		SCR_HintManagerComponent.ShowCustomHint("htCTI Eden", "Mission", 15);
		popUpNotif.PopupMsg("Arma Reforger", 15, 0.25, "");
	}

	void SendHint(int playerId, string message = "", string messageTitle = "", int hintTime = 5.0)
    {
        RpcAsk_RecieveHint(playerId, message, messageTitle, hintTime);
        Rpc(RpcAsk_RecieveHint, playerId, message, messageTitle, hintTime);
    }
    
    [RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
    protected void RpcAsk_RecieveHint(int playerId, string message,string messageTitle, int hintTime)
    {
        int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
        if(playerId != localPlayerId) return;
        
        SCR_HintManagerComponent.ShowCustomHint(message, messageTitle, hintTime);
    }
	
	void townsToArray()
	{
		for (int i = 0; i < CTI_TownList.Count(); i++)
		{
			SCR_CTI_Town town = SCR_CTI_Town.Cast(GetGame().GetWorld().FindEntityByName(CTI_TownList[i]));
			CTI_Towns.Insert(town);
		}
		PrintFormat("CTI :: Number of Towns: %1", CTI_Towns.Count());
	}
	
	void initMap()
	{
		foreach (SCR_CTI_Town town : CTI_Towns)
		{
			town.initMapComponent();
		}
	}
};