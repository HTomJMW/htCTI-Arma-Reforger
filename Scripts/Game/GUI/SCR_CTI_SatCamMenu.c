class SCR_CTI_SatCamMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected int m_playerId;
	protected PlayerManager m_pm;
	protected SCR_GroupsManagerComponent m_gmc;
	protected FactionAffiliationComponent m_faffComp;
	protected CameraManager m_camMan;
	protected CameraBase m_playerCam;
	protected SCR_ManualCamera m_manualCam = null;
	protected TimeAndWeatherManagerEntity m_timeAndWeatherManager;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.1;
	
	protected Widget m_wRoot;
	
	protected ButtonWidget m_info;
	protected ButtonWidget m_exit;
	protected ButtonWidget m_normalnv;

	protected RichTextWidget m_infoWindowText;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_SatCamMenuButtonHandler m_satCamButtonHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_timeAndWeatherManager = GetGame().GetTimeAndWeatherManager();
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_pm = GetGame().GetPlayerManager();
		m_gmc = SCR_GroupsManagerComponent.GetInstance();
		m_faffComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		
		m_camMan = GetGame().GetCameraManager();
		
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_satCamButtonHandler = new SCR_CTI_SatCamMenuButtonHandler();

		m_wRoot = GetRootWidget();
		
		m_info = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Info"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		m_normalnv = ButtonWidget.Cast(m_wRoot.FindAnyWidget("NormalNV"));
		
		m_infoWindowText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("InfoWindowText"));
		
		//m_normalnv.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_normalnv.AddHandler(m_satCamButtonHandler);
		m_normalnv.SetColor(Color.Gray);
		m_normalnv.SetEnabled(false);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);

		IEntity player = m_pc.GetControlledEntity();
		//m_playerCam = m_camMan.CurrentCamera();
		m_playerCam = m_pc.GetPlayerCamera();

		vector transform[4];
		transform[0] = "1 0 0";
		transform[1] = "0 0 1";
		transform[2] = "0 -1 0";
		transform[3] = player.GetOrigin() + "0 300 0";
		
		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.Transform = transform;
	
		m_manualCam = SCR_ManualCamera.Cast(GetGame().SpawnEntityPrefabLocal(Resource.Load("{D6DE32D1C0FCC1C7}Prefabs/Editor/Camera/ManualCameraBase.et"), GetGame().GetWorld(), spawnParams));
		if (m_manualCam)
		{
			m_camMan.SetCamera(m_manualCam);
		}

	}
	
	//------------------------------------------------------------------------------------------------
	SCR_ManualCamera getManualCam()
	{
		return m_manualCam;
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		GetGame().GetInputManager().AddActionListener("MenuUp", EActionTrigger.UP, moveCamNorth);
		GetGame().GetInputManager().AddActionListener("MenuDown", EActionTrigger.UP, moveCamSouth);
		GetGame().GetInputManager().AddActionListener("MenuLeft", EActionTrigger.UP, moveCamWest);
		GetGame().GetInputManager().AddActionListener("MenuRight", EActionTrigger.UP, moveCamEast);
		GetGame().GetInputManager().AddActionListener("MouseWheelUp", EActionTrigger.UP, CamZoomIn);
		GetGame().GetInputManager().AddActionListener("MouseWheelDown", EActionTrigger.UP, CamZoomOut);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		GetGame().GetInputManager().RemoveActionListener("MenuUp", EActionTrigger.UP, moveCamNorth);
		GetGame().GetInputManager().RemoveActionListener("MenuDown", EActionTrigger.UP, moveCamSouth);
		GetGame().GetInputManager().RemoveActionListener("MenuLeft", EActionTrigger.UP, moveCamWest);
		GetGame().GetInputManager().RemoveActionListener("MenuRight", EActionTrigger.UP, moveCamEast);
		GetGame().GetInputManager().RemoveActionListener("MouseWheelUp", EActionTrigger.UP, CamZoomIn);
		GetGame().GetInputManager().RemoveActionListener("MouseWheelDown", EActionTrigger.UP, CamZoomOut);

		m_camMan.SetCamera(m_playerCam);
		SCR_EntityHelper.DeleteEntityAndChildren(m_manualCam);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void moveCamNorth()
	{
		vector orig = m_manualCam.GetOrigin();
		orig[2] = orig[2] + 50;
		
		m_manualCam.SetOrigin(orig);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void moveCamSouth()
	{
		vector orig = m_manualCam.GetOrigin();
		orig[2] = orig[2] - 50;
		
		m_manualCam.SetOrigin(orig);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void moveCamWest()
	{
		vector orig = m_manualCam.GetOrigin();
		orig[0] = orig[0] - 50;
		
		m_manualCam.SetOrigin(orig);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void moveCamEast()
	{
		vector orig = m_manualCam.GetOrigin();
		orig[0] = orig[0] + 50;
		
		m_manualCam.SetOrigin(orig);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void CamZoomIn()
	{
		vector orig = m_manualCam.GetOrigin();
		orig[1] = orig[1] - 50;
		
		if (orig[1] < 200) orig[1] = 200;
		
		m_manualCam.SetOrigin(orig);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void CamZoomOut()
	{
		vector orig = m_manualCam.GetOrigin();
		orig[1] = orig[1] + 50;
		
		if (orig[1] > 2000) orig[1] = 2000;
		
		m_manualCam.SetOrigin(orig);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			if (m_manualCam)
			{
				// TODO if MHQ down satcam OFF
				string info = "Info:\n";
				string weekday = m_timeAndWeatherManager.GetWeekDayString() + "\n";
				int year, month, day, hour, min, sec;
				m_timeAndWeatherManager.GetDate(year, month, day);
				m_timeAndWeatherManager.GetHoursMinutesSeconds(hour, min, sec);
				string yyyy, mm, dd, h, m, s;
				yyyy = year.ToString();
				if (month < 10) mm = "0" + month.ToString(); else mm = month.ToString();
				if (day < 10) dd = "0" + day.ToString(); else dd = day.ToString();
				string date = yyyy + "/" + mm + "/" + dd + "\n";
				if (hour < 10) h = "0" + hour.ToString(); else h = hour.ToString();
				if (min < 10) m = "0" + min.ToString(); else m = min.ToString();
				if (sec < 10) s = "0" + sec.ToString(); else s = sec.ToString();
				string time = h + ":" + m + ":" + s + "\n";
				string position = "Grid position: [" + SCR_MapEntity.GetGridPos(m_manualCam.GetOrigin()) + "]\n";
				m_infoWindowText.SetText(info + weekday + date + time + position);
			}
			m_timeDelta = 0;
		}
	}
};