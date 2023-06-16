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

	protected ButtonWidget m_confirm;
	protected ButtonWidget m_cancel;
	
	protected RichTextWidget m_confirmText;
	protected RichTextWidget m_cancelText;

	protected bool listenerAdded = false;
	protected float scrollValue;

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
		removeListener();
			
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
				if (!listenerAdded) addListener();
			} else {
				m_wRoot.SetVisible(false);
				if (listenerAdded) removeListener();

				m_confirm.SetColor(SCR_CTI_Constants.CTI_ORANGE);
				m_confirmText.SetText("Confirm");
				
				m_cancel.SetColor(Color.White);
				m_cancelText.SetText("[ - Cancel - ]");
				
				// TODO cancel placing if other menu open
			}
			m_timeDelta = 0;
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
		DestroyHud();
	}

	//------------------------------------------------------------------------------------------------
	protected void addListener()
	{
		m_inputManager.AddActionListener("MouseWheel", EActionTrigger.VALUE, onScroll);
		m_inputManager.AddActionListener("MouseMiddle", EActionTrigger.UP, onClick);
		
		listenerAdded = true;
	}

	//------------------------------------------------------------------------------------------------
	protected void removeListener()
	{
		m_inputManager.RemoveActionListener("MouseWheel", EActionTrigger.VALUE, onScroll);
		m_inputManager.RemoveActionListener("MouseMiddle", EActionTrigger.UP, onClick);

		listenerAdded = false;
	}
	
	//------------------------------------------------------------------------------------------------
	protected void onScroll(float value)
	{
		if (value != 0)
		{
			if (value != scrollValue)
			{
				scrollValue = value;

				SCR_CharacterControllerComponent ccc = SCR_CharacterControllerComponent.Cast(m_ch.FindComponent(SCR_CharacterControllerComponent));			
				
				if (value > 0)
				{
					ccc.SetDynamicSpeed(ccc.GetDynamicSpeed() - 0.05);

					if (m_confirmText.GetText() == "Confirm")
					{
						m_confirm.SetColor(Color.White);
						m_confirmText.SetText("[ - Confirm - ]");

						m_cancel.SetColor(SCR_CTI_Constants.CTI_ORANGE);
						m_cancelText.SetText("Cancel");
					}
				} else {
					ccc.SetDynamicSpeed(ccc.GetDynamicSpeed() + 0.05);

					if (m_cancelText.GetText() == "Cancel")
					{
						m_confirm.SetColor(SCR_CTI_Constants.CTI_ORANGE);
						m_confirmText.SetText("Confirm");

						m_cancel.SetColor(Color.White);
						m_cancelText.SetText("[ - Cancel - ]");
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void onClick()
	{
		if (m_confirmText.GetText() == "[ - Confirm - ]")
		{
			if (m_pdc.getStartPlacing()) m_pdc.performBuilding();
			if (m_psc.getStartPlacing()) m_psc.performBuilding();
		} else {
			if (m_pdc.getStartPlacing()) m_pdc.cancelBuilding();
			if (m_psc.getStartPlacing()) m_psc.cancelBuilding();
		}
	}
};