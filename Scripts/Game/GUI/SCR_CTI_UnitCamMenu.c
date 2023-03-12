class SCR_CTI_UnitCamMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected PlayerManager pm;
	protected SCR_GroupsManagerComponent gmc;
	protected FactionAffiliationComponent faffComp;
	protected CameraManager camMan;
	protected CameraBase playerCam;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.5;
	
	protected Widget m_wRoot;
	
	protected RichTextWidget m_unit;
	
	protected ButtonWidget m_info;
	protected ButtonWidget m_disband;
	protected ButtonWidget m_unflip;
	protected ButtonWidget m_external;
	protected ButtonWidget m_internal;
	protected ButtonWidget m_ironsight;
	protected ButtonWidget m_exit;
	protected ButtonWidget m_normalnv;
	protected ButtonWidget m_satellite;
	
	protected OverlayWidget m_listboxTeams;
	protected OverlayWidget m_listboxTeamMembers;
	protected SCR_ListBoxComponent m_listboxTeamsComp;
	protected SCR_ListBoxComponent m_listboxTeamMembersComp;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_UnitCamButtonHandler m_unitCamButtonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		pm = GetGame().GetPlayerManager();
		gmc = SCR_GroupsManagerComponent.GetInstance();
		faffComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		
		camMan = GetGame().GetCameraManager();
		
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_unitCamButtonEventHandler = new SCR_CTI_UnitCamButtonHandler();

		m_wRoot = GetRootWidget();

		m_unit = RichTextWidget.Cast(m_wRoot.FindAnyWidget("SelectedUnit"));
		
		m_info = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Info"));
		m_disband = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Disband"));
		m_unflip = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Unflip"));
		m_external = ButtonWidget.Cast(m_wRoot.FindAnyWidget("External"));
		m_internal = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Internal"));
		m_ironsight = ButtonWidget.Cast(m_wRoot.FindAnyWidget("IronSight"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		m_normalnv = ButtonWidget.Cast(m_wRoot.FindAnyWidget("NormalNV"));
		m_satellite = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Satellite"));

		m_unflip.SetColor(Color.Orange);
		m_unflip.AddHandler(m_unitCamButtonEventHandler);

		m_ironsight.SetColor(Color.Orange);
		m_ironsight.AddHandler(m_unitCamButtonEventHandler);

		m_external.SetColor(Color.Orange);
		m_external.AddHandler(m_unitCamButtonEventHandler);
		
		m_internal.SetColor(Color.Orange);
		m_internal.AddHandler(m_unitCamButtonEventHandler);

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_commonButtonHandler);
		
		// listboxes
		m_listboxTeams = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxTeams"));
		m_listboxTeamMembers = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxTeamMembers"));
		m_listboxTeamsComp = SCR_ListBoxComponent.Cast(m_listboxTeams.FindHandler(SCR_ListBoxComponent));
		m_listboxTeamMembersComp = SCR_ListBoxComponent.Cast(m_listboxTeamMembers.FindHandler(SCR_ListBoxComponent));
		
		IEntity player = pc.GetControlledEntity();
		SCR_CharacterCameraHandlerComponent cchc = SCR_CharacterCameraHandlerComponent.Cast(player.FindComponent(SCR_CharacterCameraHandlerComponent));
		cchc.SetThirdPerson(true);
		
		playerCam = camMan.CurrentCamera();
	
		array<int> sidePlayers = {};
		pm.GetPlayers(sidePlayers);
		
		foreach(int pId : sidePlayers)
		{
			PlayerController pPc = pm.GetPlayerController(pId);
			IEntity ent = pPc.GetControlledEntity();
			FactionAffiliationComponent faffCompPlayer = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
			if (faffCompPlayer.GetDefaultAffiliatedFaction() != faffComp.GetDefaultAffiliatedFaction())
			{
				sidePlayers.RemoveItem(pId);
				break;
			}
			PlayerCamera pCam = pPc.GetPlayerCamera();
			m_listboxTeamsComp.AddItem(pm.GetPlayerName(pId), pCam);
		}

		m_unit.SetText("Unit: " + pm.GetPlayerName(playerId) + " " + gmc.GetPlayerGroup(playerId).GetCustomName());
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		camMan.SetCamera(playerCam);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			if (m_listboxTeamsComp.GetSelectedItem() != -1)
			{
				PlayerCamera cam = PlayerCamera.Cast(m_listboxTeamsComp.GetItemData(m_listboxTeamsComp.GetSelectedItem()));
				camMan.SetCamera(cam);
			}
			
			m_timeDelta = 0;
		}
	}
};