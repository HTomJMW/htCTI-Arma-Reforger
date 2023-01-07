class SCR_CTI_VideoSettingsMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	
	protected Widget m_wRoot;
	
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	
	protected SliderWidget m_vd;
	protected SliderWidget m_tg;
	
	protected RichTextWidget m_vdText;
	protected RichTextWidget m_tgText;
	
	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();

		m_wRoot = GetRootWidget();
		
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		m_back.SetColor(Color.Orange);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_commonButtonHandler);
		
		m_vdText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("ViewDistance"));
		m_tgText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TerrainGrid"));
		
		m_vd = SliderWidget.Cast(m_wRoot.FindAnyWidget("SliderVD"));
		m_tg = SliderWidget.Cast(m_wRoot.FindAnyWidget("SliderTG"));
		
		// maybe need get server limit?
		float vdmax = GetGame().GetMaximumViewDistance();
		float vdmin = GetGame().GetMinimumViewDistance();
		float vd = GetGame().GetViewDistance();
		m_vd.SetMax(vdmax);
		m_vd.SetMin(vdmin);
		m_vd.SetCurrent(vd);
		
		float tgmax = GetGame().GetMaximumGrassDistance();
		float tgmin = GetGame().GetMinimumGrassDistance();
		float tg = GetGame().GetGrassDistance();
		m_tg.SetMax(tgmax);
		m_tg.SetMin(tgmin);
		m_tg.SetCurrent(tg);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		// TODO SLOW DOWN RUNS
		
		m_vdText.SetText("View Distance: " + m_vd.GetCurrent().ToString() + "m");
		m_tgText.SetText("Terrain Grid: " + m_tg.GetCurrent().ToString() + "m");
		
		GetGame().SetViewDistance(m_vd.GetCurrent());
		GetGame().SetGrassDistance(m_tg.GetCurrent());
	}
};