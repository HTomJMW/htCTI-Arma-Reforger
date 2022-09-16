class SCR_CTI_MainMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected IEntity ent;
	protected FactionAffiliationComponent userAffiliationComponent;
	protected int playerId;
	
	protected Widget m_wRoot;
	protected WindowWidget m_window;
	
	protected RichTextWidget m_missiontime;
	protected RichTextWidget m_maxmissiontime;
	protected RichTextWidget m_resources;
	protected RichTextWidget m_pools;
	protected RichTextWidget m_income;
	protected RichTextWidget m_townsheldvalue;
	protected RichTextWidget m_victory;

	protected ButtonWidget m_radio;
	protected ButtonWidget m_units;
	protected ButtonWidget m_halo;
	protected ButtonWidget m_build;
	
	protected ButtonWidget m_onlinehelp;
	protected ButtonWidget m_videosettings;
	protected ButtonWidget m_transferresources;
	protected ButtonWidget m_unflipnearestvehicle;
	protected ButtonWidget m_servicemenu;
	protected ButtonWidget m_aimanagement;
	protected ButtonWidget m_unitscamera;
	protected ButtonWidget m_satellitecamera;
	
	protected ButtonWidget m_teams;
	protected ButtonWidget m_mapcommanding;
	protected ButtonWidget m_upgrades;
	protected ButtonWidget m_basemanagement;
	protected ButtonWidget m_teamrequests;
	protected ButtonWidget m_artillery;
	protected ButtonWidget m_setprioritytown;
	protected ButtonWidget m_forcedisactibation;
	
	protected ButtonWidget m_exit;
	protected RichTextWidget m_exittext;
	
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;
	
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		ent = pc.GetControlledEntity();
		userAffiliationComponent = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		playerId = pc.GetPlayerId();
		
		m_wRoot = GetRootWidget();
		m_window = WindowWidget.Cast(m_wRoot.FindAnyWidget("Window"));
		
		m_missiontime = RichTextWidget.Cast(m_wRoot.FindAnyWidget("MissionTime"));
		m_maxmissiontime = RichTextWidget.Cast(m_wRoot.FindAnyWidget("MaxMissionTime"));
		m_resources = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Resources"));
		m_pools = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Pools"));
		m_income = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Income"));
		m_townsheldvalue = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TownsHeldValue"));
		m_victory = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Victory"));

		m_radio = ButtonWidget.Cast(m_wRoot.FindAnyWidget("RadioButton"));
		m_units = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UnitsButton"));
		m_halo = ButtonWidget.Cast(m_wRoot.FindAnyWidget("HALOButton"));
		m_build = ButtonWidget.Cast(m_wRoot.FindAnyWidget("BuildButton"));
		
		m_onlinehelp = ButtonWidget.Cast(m_wRoot.FindAnyWidget("OnlineHelpButton"));
		m_videosettings = ButtonWidget.Cast(m_wRoot.FindAnyWidget("VideoSettingsButton"));
		m_transferresources = ButtonWidget.Cast(m_wRoot.FindAnyWidget("TransferResourcesButton"));
		m_unflipnearestvehicle = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UnflipNearestVehicleButton"));
		m_servicemenu = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ServiceMenuButton"));
		m_aimanagement = ButtonWidget.Cast(m_wRoot.FindAnyWidget("AIManagementButton"));
		m_unitscamera = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UnitsCameraButton"));
		m_satellitecamera = ButtonWidget.Cast(m_wRoot.FindAnyWidget("SatelliteCameraButton"));
	
		m_teams = ButtonWidget.Cast(m_wRoot.FindAnyWidget("TeamsButton"));
		m_mapcommanding = ButtonWidget.Cast(m_wRoot.FindAnyWidget("MapCommandingButton"));
		m_upgrades = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UpgradesButton"));
		m_basemanagement = ButtonWidget.Cast(m_wRoot.FindAnyWidget("BaseManagementButton"));
		m_teamrequests = ButtonWidget.Cast(m_wRoot.FindAnyWidget("TeamRequestsButton"));
		m_artillery = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ArtilleryButton"));
		m_setprioritytown = ButtonWidget.Cast(m_wRoot.FindAnyWidget("SetPriorityTownButton"));
		m_forcedisactibation = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ForceDisactivationButton"));

		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		m_exittext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("ExitText"));
		
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();

		m_radio.SetName("RADIO");
		m_radio.SetColor(Color.Orange);
		m_radio.AddHandler(m_buttonEventHandler);
		
		m_units.SetName("UNITS");
		m_units.SetColor(Color.Orange);
		m_units.AddHandler(m_buttonEventHandler);
		
		m_halo.SetName("HALO");
		m_halo.SetColor(Color.Orange);
		m_halo.AddHandler(m_buttonEventHandler);
		
		m_build.SetName("BUILD");
		m_build.SetColor(Color.Orange);
		m_build.AddHandler(m_buttonEventHandler);
		
		m_onlinehelp.SetName("ONLINEHELP");
		m_onlinehelp.SetColor(Color.Orange);
		m_onlinehelp.AddHandler(m_buttonEventHandler);
		m_videosettings.SetName("VIDEOSETTINGS");
		m_videosettings.SetColor(Color.Orange);
		m_videosettings.AddHandler(m_buttonEventHandler);
		m_transferresources.SetName("TRANSFERRESOURCES");
		m_transferresources.SetColor(Color.Orange);
		m_transferresources.AddHandler(m_buttonEventHandler);
		m_unflipnearestvehicle.SetName("UNFLIPNEARESTVEHICLE");
		m_unflipnearestvehicle.SetColor(Color.Orange);
		m_unflipnearestvehicle.AddHandler(m_buttonEventHandler);
		m_servicemenu.SetName("SERVICEMENU");
		m_servicemenu.SetColor(Color.Orange);
		m_servicemenu.AddHandler(m_buttonEventHandler);
		m_aimanagement.SetName("AIMANAGEMENT");
		m_aimanagement.SetColor(Color.Orange);
		m_aimanagement.AddHandler(m_buttonEventHandler);
		m_unitscamera.SetName("UNITSCAMERA");
		m_unitscamera.SetColor(Color.Orange);
		m_unitscamera.AddHandler(m_buttonEventHandler);
		m_satellitecamera.SetName("SATELLITECAMERA");
		m_satellitecamera.SetColor(Color.Orange);
		m_satellitecamera.AddHandler(m_buttonEventHandler);
		m_teams.SetName("TEAMS");
		m_teams.SetColor(Color.Orange);
		m_teams.AddHandler(m_buttonEventHandler);
		m_mapcommanding.SetName("MAPCOMMANDING");
		m_mapcommanding.SetColor(Color.Orange);
		m_mapcommanding.AddHandler(m_buttonEventHandler);
		m_upgrades.SetName("UPGRADES");
		m_upgrades.SetColor(Color.Orange);
		m_upgrades.AddHandler(m_buttonEventHandler);
		m_basemanagement.SetName("BASEMANAGEMENT");
		m_basemanagement.SetColor(Color.Orange);
		m_basemanagement.AddHandler(m_buttonEventHandler);
		m_teamrequests.SetName("TEAMREQUESTS");
		m_teamrequests.SetColor(Color.Orange);
		m_teamrequests.AddHandler(m_buttonEventHandler);
		m_artillery.SetName("ARTILLERY");
		m_artillery.SetColor(Color.Orange);
		m_artillery.AddHandler(m_buttonEventHandler);
		m_setprioritytown.SetName("SETPRIORITYTOWN");
		m_setprioritytown.SetColor(Color.Orange);
		m_setprioritytown.AddHandler(m_buttonEventHandler);
		m_forcedisactibation.SetName("FORCEDISACTIVATION");
		m_forcedisactibation.SetColor(Color.Orange);
		m_forcedisactibation.AddHandler(m_buttonEventHandler);
		
		m_exit.SetName("EXITBUTTON");
		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_buttonEventHandler);
	}
	
	override void OnMenuOpen()
	{
	}
	
	override void OnMenuUpdate(float tDelta)
	{
		int missiontime = gameMode.GetElapsedTime();
		int days = missiontime / 86400;
		int hours = (missiontime - (days * 86400)) / 3600;
		int mins = (missiontime - (hours * 3600) - (days * 86400)) / 60;
		int secs = missiontime - (mins * 60) - (hours * 3600) - (days * 86400);
		
		string d, h, m, s;
		d = days.ToString() + "D ";
		if (hours < 10) {h = "0" + hours.ToString();} else {h = hours.ToString();}
		if (mins < 10) {m = "0" + mins.ToString();} else {m = mins.ToString();}
		if (secs < 10) {s = "0" + secs.ToString();} else {s = secs.ToString();}
		
		m_missiontime.SetText("Mission Time: " + d + h + ":" + m + ":" + s);
		
		int timelimit = gameMode.GetTimeLimit();
		m_maxmissiontime.SetText("Max Mission Time: " + timelimit.ToString());
		
		int sizeCDA = gameMode.ClientDataArray.Count();
		SCR_CTI_ClientData clientData;
		for (int i = 0; i < sizeCDA; i++)
		{
			if (gameMode.ClientDataArray[i].getPlayerId() == playerId)
			{
				clientData = gameMode.ClientDataArray[i];
				break;
			}
		}
		if (clientData)
		{
			int funds = clientData.getFunds();
			m_resources.SetText("Resources: " + funds.ToString());
		}
		
		int allvalue = 0;
		int sidevalue = 0;
		int townsCNT = gameMode.CTI_Towns.Count();
		for (int i = 0; i < townsCNT; i++)
		{
			allvalue += gameMode.CTI_Towns[i].getTownValue();
			if (userAffiliationComponent.GetAffiliatedFaction() == gameMode.CTI_Towns[i].getFaction())
			{
				sidevalue += gameMode.CTI_Towns[i].getTownValue();
			}
		}
		
		m_townsheldvalue.SetText("Town Held Value: " + sidevalue.ToString() + "/" + allvalue.ToString());
		
		float victoryvalue = allvalue * (gameMode.winRate / 100);
		m_victory.SetText("Victory: " + victoryvalue.ToString());
	}
};