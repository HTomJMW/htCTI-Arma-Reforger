class SCR_CTI_ConfirmMenu : SCR_InfoDisplayExtended
{
	protected SCR_CTI_GameMode m_gameMode;
	protected InputManager m_inputManager;
	protected PlayerController m_pc;
	protected ChimeraCharacter m_ch;
	
	protected SCR_CTI_PlacingDefenseComponent m_pdc;
	protected SCR_CTI_PlacingStructureComponent m_psc;

	protected float m_timeDelta;
	protected const float TIMESTEP = 0.02;
	protected int runCounter = 0;
	protected int scrollCounter = 0;

	protected ButtonWidget m_confirm;
	protected ButtonWidget m_cancel;
	
	protected RichTextWidget m_confirmText;
	protected RichTextWidget m_cancelText;
	
	protected ref ScriptInvoker m_OnMouseScrollUsed = new ScriptInvoker();
	protected ref ScriptInvoker m_OnMouseMiddleUsed = new ScriptInvoker();

	//------------------------------------------------------------------------------------------------
	protected void CreateHud(IEntity owner)
	{
		m_confirm = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ConfirmButton"));
		m_cancel = ButtonWidget.Cast(m_wRoot.FindAnyWidget("CancelButton"));
		
		m_confirmText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("ConfirmText"));
		m_cancelText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("CancelText"));
		
		m_confirm.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_cancel.SetColor(Color.White);

		m_cancelText.SetText("[ - Cancel - ]"); // default

		m_wRoot.SetVisible(false);
	}

	//------------------------------------------------------------------------------------------------
	protected void DestroyHud()
	{		
		if (!m_wRoot)
			return;		

		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
		
		m_wRoot = null;		
	}

	//------------------------------------------------------------------------------------------------
	override event void DisplayUpdate(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
		{
			if (!m_wRoot)
				return;

			bool menuOpen = GetGame().GetMenuManager().IsAnyMenuOpen();
			m_ch = ChimeraCharacter.Cast(m_pc.GetControlledEntity());
			if (!menuOpen && !m_ch.IsInVehicle() && (m_pdc.getStartPlacing() || m_psc.getStartPlacing()))
			{
				m_wRoot.SetVisible(true);

				bool mw = m_inputManager.GetActionValue("MouseWheel"); // need disable moving speed change on scroll
				if (mw)
				{
					m_OnMouseScrollUsed.Invoke();
				} else {
					scrollCounter = 0;
				}

				bool wheeldown = m_inputManager.GetActionValue("MouseMiddle"); // reset action value not working, its called more than once
				if (wheeldown)
				{
					m_OnMouseMiddleUsed.Invoke();
				} else {
					runCounter = 0;
				}
			} else {
				m_wRoot.SetVisible(false);

				m_confirm.SetColor(SCR_CTI_Constants.CTI_ORANGE);
				m_confirmText.SetText("Confirm");
				
				m_cancel.SetColor(Color.White);
				m_cancelText.SetText("[ - Cancel - ]");
				
				runCounter = 0;
				scrollCounter = 0;
			}
			m_timeDelta = 0;
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnMouseMiddleDown()
	{
		if (runCounter == 0)
		{
			runCounter++;
			
			if (m_confirmText.GetText() == "[ - Confirm - ]")
			{
				if (m_pdc.getStartPlacing()) m_pdc.performBuilding();
				if (m_psc.getStartPlacing()) m_psc.performBuilding();
			} else {
				if (m_pdc.getStartPlacing()) m_pdc.cancelBuilding();
				if (m_psc.getStartPlacing()) m_psc.cancelBuilding();
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnMouseScroll()
	{
		if (scrollCounter == 0)
		{
			scrollCounter++;
			
			if (m_confirmText.GetText() == "Confirm")
			{
				m_confirm.SetColor(Color.White);
				m_confirmText.SetText("[ - Confirm - ]");
	
				m_cancel.SetColor(SCR_CTI_Constants.CTI_ORANGE);
				m_cancelText.SetText("Cancel");
			} else {
				m_confirm.SetColor(SCR_CTI_Constants.CTI_ORANGE);
				m_confirmText.SetText("Confirm");
	
				m_cancel.SetColor(Color.White);
				m_cancelText.SetText("[ - Cancel - ]");
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool DisplayStartDrawInit(IEntity owner)
	{
		if (m_LayoutPath == "") m_LayoutPath = "{8C4B0F3E158814B4}UI/layouts/ConfirmMenu.layout";
		
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_inputManager = GetGame().GetInputManager();
		m_pc = GetGame().GetPlayerController();
		
		m_pdc = SCR_CTI_PlacingDefenseComponent.Cast(m_pc.FindComponent(SCR_CTI_PlacingDefenseComponent));
		m_psc = SCR_CTI_PlacingStructureComponent.Cast(m_pc.FindComponent(SCR_CTI_PlacingStructureComponent));

		m_timeDelta = 0;

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayStartDraw(IEntity owner)
	{
		if (!m_wRoot)
		{
			return;
		}

		CreateHud(owner);
		
		m_OnMouseMiddleUsed.Insert(OnMouseMiddleDown);
		m_OnMouseScrollUsed.Insert(OnMouseScroll);
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayInit(IEntity owner)
	{
		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayStopDraw(IEntity owner)
	{
		m_OnMouseMiddleUsed.Remove(OnMouseMiddleDown);
		m_OnMouseScrollUsed.Remove(OnMouseScroll);
		
		DestroyHud();
	}
};