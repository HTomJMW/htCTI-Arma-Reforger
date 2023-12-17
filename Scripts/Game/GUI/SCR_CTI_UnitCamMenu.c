class SCR_CTI_UnitCamMenu : ChimeraMenuBase
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
	
	protected bool ironsightView = false;
	protected bool internalView = true;
	protected bool externalView = false;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.1;
	
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
	
	protected OverlayWidget m_listboxTeams;
	protected OverlayWidget m_listboxTeamMembers;
	protected SCR_ListBoxComponent m_listboxTeamsComp;
	protected SCR_ListBoxComponent m_listboxTeamMembersComp;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_UnitCamMenuButtonHandler m_unitCamButtonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_pm = GetGame().GetPlayerManager();
		m_gmc = SCR_GroupsManagerComponent.GetInstance();
		m_faffComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		
		m_camMan = GetGame().GetCameraManager();
		
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_unitCamButtonEventHandler = new SCR_CTI_UnitCamMenuButtonHandler();

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

		m_unflip.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_unflip.AddHandler(m_unitCamButtonEventHandler);

		m_ironsight.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_ironsight.AddHandler(m_unitCamButtonEventHandler);

		m_external.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_external.AddHandler(m_unitCamButtonEventHandler);
		
		m_internal.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_internal.AddHandler(m_unitCamButtonEventHandler);
		
		//m_normalnv.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_normalnv.AddHandler(m_unitCamButtonEventHandler);
		m_normalnv.SetColor(Color.Gray);
		m_normalnv.SetEnabled(false);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);
		
		// listboxes
		m_listboxTeams = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxTeams"));
		m_listboxTeamMembers = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxTeamMembers"));
		m_listboxTeamsComp = SCR_ListBoxComponent.Cast(m_listboxTeams.FindHandler(SCR_ListBoxComponent));
		m_listboxTeamMembersComp = SCR_ListBoxComponent.Cast(m_listboxTeamMembers.FindHandler(SCR_ListBoxComponent));
		
		IEntity player = m_pc.GetControlledEntity();
		//m_playerCam = m_camMan.CurrentCamera();
		m_playerCam = m_pc.GetPlayerCamera();
	
		array<int> sidePlayers = {};
		m_pm.GetPlayers(sidePlayers);
		
		foreach(int pId : sidePlayers)
		{
			IEntity ent = m_pm.GetPlayerControlledEntity(pId);
			FactionAffiliationComponent faffCompPlayer = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
			if (faffCompPlayer.GetDefaultAffiliatedFaction() != m_faffComp.GetDefaultAffiliatedFaction())
			{
				sidePlayers.RemoveItem(pId);
				break;
			}

			m_listboxTeamsComp.AddItem(m_pm.GetPlayerName(pId), ent);
		}

		m_unit.SetText("Unit: " + m_pm.GetPlayerName(m_playerId) + " " + m_gmc.GetPlayerGroup(m_playerId).GetCustomName());

		vector transform[4];
		m_playerCam.GetTransform(transform);
		EntitySpawnParams spawnParams = new EntitySpawnParams();
		//vector dir = m_playerCam.GetWorldTransformAxis(2);
		//transform[3] = transform[3] + (dir * -1.3);
		//transform[3][1] = transform[3][1] + 2.2;
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
	bool isIronSight()
	{
		return ironsightView;
	}
	
	//------------------------------------------------------------------------------------------------
	void setIronSight()
	{
		ironsightView = true;
		internalView = false;
		externalView = false;
	}

	//------------------------------------------------------------------------------------------------
	bool isInternal()
	{
		return internalView;
	}
	
	//------------------------------------------------------------------------------------------------
	void setInternal()
	{
		ironsightView = false;
		internalView = true;
		externalView = false;
	}
	
	//------------------------------------------------------------------------------------------------
	bool isExternal()
	{
		return externalView;
	}
	
	//------------------------------------------------------------------------------------------------
	void setExternal()
	{
		ironsightView = false;
		internalView = false;
		externalView = true;
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{		
		GetGame().GetInputManager().AddActionListener("MenuBack", EActionTrigger.DOWN, back);

		setInternal();
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		GetGame().GetInputManager().RemoveActionListener("MenuBack", EActionTrigger.DOWN, back);
		
		m_camMan.SetCamera(m_playerCam);
		SCR_EntityHelper.DeleteEntityAndChildren(m_manualCam);
	}

	//------------------------------------------------------------------------------------------------
	protected void back()
	{
		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();

		GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			if (m_manualCam)
			{
				// TODO update listbox
				if (m_listboxTeamsComp.GetSelectedItem() != -1)
				{
					vector transform[4];
					IEntity ent = IEntity.Cast(m_listboxTeamsComp.GetItemData(m_listboxTeamsComp.GetSelectedItem()));
					ent.GetTransform(transform);
					vector dir = ent.GetTransformAxis(2);
					
					switch(true)
					{
						case (isIronSight()):
						{
							transform[3] = transform[3] + (dir * 0.3);
							transform[3][1] = transform[3][1] + 1.2;
							break;
						}
						case (isInternal()):
						{
							transform[3] = transform[3] + (dir * 0.3);
							transform[3][1] = transform[3][1] + 1.6;
							break;
						}
						case (isExternal()):
						{
							transform[3] = transform[3] + (dir * -1.3);
							transform[3][1] = transform[3][1] + 2.2;
							break;
						}
					}
					
					m_manualCam.SetTransform(transform);

					m_unit.SetText("Unit"); // TODO get name from entity?
				} else {
					vector transform[4];
					IEntity ent = m_pc.GetControlledEntity();
					ent.GetTransform(transform);
					vector dir = ent.GetTransformAxis(2);
					
					switch(true)
					{
						case (isIronSight()):
						{
							transform[3] = transform[3] + (dir * 0.3);
							transform[3][1] = transform[3][1] + 1.2;
							break;
						}
						case (isInternal()):
						{
							transform[3] = transform[3] + (dir * 0.3);
							transform[3][1] = transform[3][1] + 1.6;
							break;
						}
						case (isExternal()):
						{
							transform[3] = transform[3] + (dir * -1.3);
							transform[3][1] = transform[3][1] + 2.2;
							break;
						}
					}
					
					m_manualCam.SetTransform(transform);
				}
			}
			m_timeDelta = 0;
		}
	}
};