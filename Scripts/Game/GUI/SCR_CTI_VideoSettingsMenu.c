class SCR_CTI_VideoSettingsMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected int m_playerId;
	
	protected float m_vd;
	protected float m_tg;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.25;
	
	protected Widget m_wRoot;
	
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	
	protected SliderWidget m_vdSlider;
	protected SliderWidget m_tgSlider;
	
	protected RichTextWidget m_vdText;
	protected RichTextWidget m_tgText;
	
	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_VideoSettingsMenuButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_VideoSettingsMenuButtonHandler();

		m_wRoot = GetRootWidget();
		
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);
		
		m_vdText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("ViewDistance"));
		m_tgText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TerrainGrid"));
		
		m_vdSlider = SliderWidget.Cast(m_wRoot.FindAnyWidget("SliderVD"));
		m_tgSlider = SliderWidget.Cast(m_wRoot.FindAnyWidget("SliderTG"));
		
		// maybe need get server limit?
		float vdmax = GetGame().GetMaximumViewDistance();
		float vdmin = GetGame().GetMinimumViewDistance();
		m_vd = GetGame().GetViewDistance();
		m_vdSlider.SetMax(vdmax);
		m_vdSlider.SetMin(vdmin);
		m_vdSlider.SetCurrent(m_vd);
		
		float tgmax = GetGame().GetMaximumGrassDistance();
		float tgmin = GetGame().GetMinimumGrassDistance();
		m_tg = GetGame().GetGrassDistance();
		m_tgSlider.SetMax(tgmax);
		m_tgSlider.SetMin(tgmin);
		m_tgSlider.SetCurrent(m_tg);
		
		m_vdText.SetText("View Distance: " + m_vdSlider.GetCurrent().ToString() + "m");
		m_tgText.SetText("Terrain Grid: " + m_tgSlider.GetCurrent().ToString() + "m");
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
			if (m_vd != m_vdSlider.GetCurrent() || m_tg != m_tgSlider.GetCurrent())
			{
				m_vdText.SetText("View Distance: " + m_vdSlider.GetCurrent().ToString() + "m");
				m_tgText.SetText("Terrain Grid: " + m_tgSlider.GetCurrent().ToString() + "m");
				
				GetGame().SetViewDistance(m_vdSlider.GetCurrent());
				GetGame().SetGrassDistance(m_tgSlider.GetCurrent());

				SCR_JsonSaveContext saveContext = new SCR_JsonSaveContext();
				saveContext.WriteValue("VD", m_vdSlider.GetCurrent());
				saveContext.WriteValue("TG", m_tgSlider.GetCurrent());
				saveContext.SaveToFile("$profile:.save\\htCTI_VideoSettings.json");

				m_vd = m_vdSlider.GetCurrent();
				m_tg = m_tgSlider.GetCurrent();
			}
			m_timeDelta = 0;
		}
	}
};