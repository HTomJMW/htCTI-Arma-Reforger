class SCR_CTI_MainMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected SCR_CTI_ClientData m_clientData;
	protected IEntity m_ent;
	protected FactionAffiliationComponent m_userAffiliationComponent;
	protected SCR_CTI_RadioConnectionComponent m_rcc;
	protected SCR_CTI_UpgradeComponent m_upgradeComp;
	protected int m_playerId;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.5;
	
	protected Widget m_wRoot;
	
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
	
	protected RichTextWidget m_radioText;
	
	protected ButtonWidget m_leavecom;
	protected ButtonWidget m_gear;
	
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
	protected ButtonWidget m_clearpriority;
	
	protected ButtonWidget m_exit;
	
	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_ent = m_pc.GetControlledEntity();
		m_userAffiliationComponent = FactionAffiliationComponent.Cast(m_ent.FindComponent(FactionAffiliationComponent));
		m_playerId = m_pc.GetPlayerId();
		
		ChimeraCharacter ch = ChimeraCharacter.Cast(m_ent);
		
		m_wRoot = GetRootWidget();
		
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
		
		m_radioText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("RadioText"));
		
		m_leavecom = ButtonWidget.Cast(m_wRoot.FindAnyWidget("LeaveComButton"));
		m_gear = ButtonWidget.Cast(m_wRoot.FindAnyWidget("GearButton"));
		
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
		m_clearpriority = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ClearPriorityButton"));

		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));

		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();

		m_radio.SetColor(Color.Orange);
		m_radio.AddHandler(m_buttonEventHandler);
		
		m_rcc = SCR_CTI_RadioConnectionComponent.Cast(m_ent.FindComponent(SCR_CTI_RadioConnectionComponent));
		if (m_rcc)
		{
			switch(true)
			{
				case (!m_rcc.hasRadio()): m_radioText.SetText("Radio - None"); break;
				case (m_rcc.hasRadio() && m_rcc.radioIsOn()): m_radioText.SetText("Radio - OFF"); break;
				case (m_rcc.hasRadio() && !m_rcc.radioIsOn()): m_radioText.SetText("Radio - ON"); break;
			}
		}
		
		m_units.SetColor(Color.Orange);
		m_units.AddHandler(m_buttonEventHandler);
		
		//m_halo.SetColor(Color.Orange);
		//m_halo.AddHandler(m_buttonEventHandler);
		m_halo.SetColor(Color.Gray);
		m_halo.SetEnabled(false);

		if (!ch.IsInVehicle())
		{
			m_build.SetColor(Color.Orange);
			m_build.AddHandler(m_buttonEventHandler);
		} else {
			m_build.SetColor(Color.Gray);
			m_build.SetEnabled(false);
		}
			
		m_clientData = m_gameMode.getClientData(m_playerId);

		if (m_clientData && m_clientData.isCommander())
		{
			m_leavecom.SetColor(Color.Orange);
			m_leavecom.AddHandler(m_buttonEventHandler);
		} else {
			m_leavecom.SetColor(Color.Gray);
			m_leavecom.SetEnabled(false);
		}
		
		// Todo barrack distance dependent
		m_gear.SetColor(Color.Orange);
		m_gear.AddHandler(m_buttonEventHandler);

		m_onlinehelp.SetColor(Color.Orange);
		m_onlinehelp.AddHandler(m_buttonEventHandler);
		
		m_videosettings.SetColor(Color.Orange);
		m_videosettings.AddHandler(m_buttonEventHandler);
		
		m_transferresources.SetColor(Color.Orange);
		m_transferresources.AddHandler(m_buttonEventHandler);

		m_unflipnearestvehicle.SetColor(Color.Orange);
		m_unflipnearestvehicle.AddHandler(m_buttonEventHandler);
		
		m_servicemenu.SetColor(Color.Orange);
		m_servicemenu.AddHandler(m_buttonEventHandler);
		
		//m_aimanagement.SetColor(Color.Orange);
		//m_aimanagement.AddHandler(m_buttonEventHandler);
		m_aimanagement.SetColor(Color.Gray);
		m_aimanagement.SetEnabled(false);
		
		m_unitscamera.SetColor(Color.Orange);
		m_unitscamera.AddHandler(m_buttonEventHandler);
		
		m_upgradeComp = SCR_CTI_UpgradeComponent.Cast(m_gameMode.FindComponent(SCR_CTI_UpgradeComponent));
		int upgradeIndex = m_gameMode.Upgrades.findIndexByName("Satellite Camera level 1");
		UpgradeStatus upgradeStatus = m_upgradeComp.getUpgradeStatus(m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey(), upgradeIndex);
		
		if (upgradeStatus == UpgradeStatus.FINISHED)
		{
			m_satellitecamera.SetColor(Color.Orange);
			m_satellitecamera.AddHandler(m_buttonEventHandler);
		} else {
			m_satellitecamera.SetColor(Color.Gray);
			m_satellitecamera.SetEnabled(false);
		}

		//m_teams.SetColor(Color.Orange);
		//m_teams.AddHandler(m_buttonEventHandler);
		m_teams.SetColor(Color.Gray);
		m_teams.SetEnabled(false);
		
		//m_mapcommanding.SetColor(Color.Orange);
		//m_mapcommanding.AddHandler(m_buttonEventHandler);
		m_mapcommanding.SetColor(Color.Gray);
		m_mapcommanding.SetEnabled(false);
		
		m_upgrades.SetColor(Color.Orange);
		m_upgrades.AddHandler(m_buttonEventHandler);
		
		//m_basemanagement.SetColor(Color.Orange);
		//m_basemanagement.AddHandler(m_buttonEventHandler);
		m_basemanagement.SetColor(Color.Gray);
		m_basemanagement.SetEnabled(false);

		//m_teamrequests.SetColor(Color.Orange);
		//m_teamrequests.AddHandler(m_buttonEventHandler);
		m_teamrequests.SetColor(Color.Gray);
		m_teamrequests.SetEnabled(false);

		//m_artillery.SetColor(Color.Orange);
		//m_artillery.AddHandler(m_buttonEventHandler);
		m_artillery.SetColor(Color.Gray);
		m_artillery.SetEnabled(false);

		if (m_clientData && m_clientData.isCommander())
		{
			m_setprioritytown.SetColor(Color.Orange);
			m_setprioritytown.AddHandler(m_buttonEventHandler);
			
			m_clearpriority.SetColor(Color.Orange);
			m_clearpriority.AddHandler(m_buttonEventHandler);
		} else {
			m_setprioritytown.SetColor(Color.Gray);
			m_setprioritytown.SetEnabled(false);
			
			m_clearpriority.SetColor(Color.Gray);
			m_clearpriority.SetEnabled(false);
		}

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_commonButtonHandler);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			if (m_rcc)
			{
				switch(true)
				{
					case (!m_rcc.hasRadio()): m_radioText.SetText("Radio - None"); break;
					case (m_rcc.hasRadio() && m_rcc.radioIsOn()): m_radioText.SetText("Radio - OFF"); break;
					case (m_rcc.hasRadio() && !m_rcc.radioIsOn()): m_radioText.SetText("Radio - ON"); break;
				}
			}
			
			int missiontime = m_gameMode.GetElapsedTime();
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
			
			int timelimit = m_gameMode.GetTimeLimit();
			m_maxmissiontime.SetText("Max Mission Time: " + timelimit.ToString());
	
			int funds = 0;
			if (m_clientData)
			{
				if (m_clientData.isCommander())
				{
					funds = m_gameMode.getCommanderFunds(m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey());
				} else {
					funds = m_clientData.getFunds();
				}
			}

			m_resources.SetText("Resources: " + funds.ToString());
			
			int allvalue = 0;
			int sidevalue = 0;
			int townsCNT = m_gameMode.CTI_Towns.Count();
			for (int i = 0; i < townsCNT; i++)
			{
				allvalue += m_gameMode.CTI_Towns[i].getTownValue();
				if (m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == m_gameMode.CTI_Towns[i].getFactionKey())
				{
					sidevalue += m_gameMode.CTI_Towns[i].getTownValue();
				}
			}
			
			m_townsheldvalue.SetText("Town Held Value: " + sidevalue.ToString() + "/" + allvalue.ToString());
			
			float victoryvalue = allvalue * (SCR_CTI_Constants.WINRATE / 100);
			m_victory.SetText("Victory: " + victoryvalue.ToString());
			
			m_timeDelta = 0;
		}
	}
};