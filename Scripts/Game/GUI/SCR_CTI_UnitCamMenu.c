class SCR_CTI_UnitCamMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected PlayerManager pm;
	protected SCR_GroupsManagerComponent gmc;
	protected CameraManager camMan;
	
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

		m_external.SetColor(Color.Orange);
		m_external.AddHandler(m_unitCamButtonEventHandler);
		
		m_internal.SetColor(Color.Orange);
		m_internal.AddHandler(m_unitCamButtonEventHandler);

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_commonButtonHandler);
		
		IEntity player = pc.GetControlledEntity();
		SCR_CharacterCameraHandlerComponent cchc = SCR_CharacterCameraHandlerComponent.Cast(player.FindComponent(SCR_CharacterCameraHandlerComponent));
		cchc.SetThirdPerson(true);
		
		m_unit.SetText("Unit: " + pm.GetPlayerName(playerId) + " " + gmc.GetPlayerGroup(playerId).GetCustomName());
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
	}
};