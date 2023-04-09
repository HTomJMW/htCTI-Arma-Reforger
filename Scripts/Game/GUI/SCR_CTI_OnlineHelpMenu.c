class SCR_CTI_OnlineHelpMenu : ChimeraMenuBase
{
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.25;

	protected Widget m_wRoot;
	
	protected ButtonWidget m_welcomescreen;
	protected ButtonWidget m_base;
	protected ButtonWidget m_commander;
	protected ButtonWidget m_economy;
	protected ButtonWidget m_map;
	protected ButtonWidget m_credits;
	
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	
	protected XComboBoxWidget m_combokey;
	
	protected int m_lastItemIndex = -1;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;
	protected ref SCR_CTI_OnlineHelpButtonHandler m_oHButtonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{		
		InputBinding m_binding = GetGame().GetInputManager().CreateUserBinding();
		array<string> currentBinds = {};
		m_binding.GetBindings("CTI_OpenMainMenu", currentBinds, EInputDeviceType.KEYBOARD, "primary:click");

		m_wRoot = GetRootWidget();
		
		// buttons
		m_welcomescreen = ButtonWidget.Cast(m_wRoot.FindAnyWidget("WelcomeScreen"));
		m_base = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Base"));
		m_commander = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Commander"));
		m_economy = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Economy"));
		m_map = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Map"));
		m_credits = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Credits"));

		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));

		// xcombobox
		m_combokey = XComboBoxWidget.Cast(m_wRoot.FindAnyWidget("KeyChangerComboBox"));
		int index_0 = m_combokey.AddItem("Num 0");
		int index_1 = m_combokey.AddItem("Right Ctrl");

		if (WidgetManager.Translate(currentBinds[0]) == "Num 0")
		{
			m_combokey.SetCurrentItem(index_0);
			m_lastItemIndex = index_0;
		}
		if (WidgetManager.Translate(currentBinds[0]) == "Right Ctrl")
		{
			m_combokey.SetCurrentItem(index_1);
			m_lastItemIndex = index_1;
		}

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		m_oHButtonEventHandler = new SCR_CTI_OnlineHelpButtonHandler();

		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);
		
		m_welcomescreen.AddHandler(m_oHButtonEventHandler);
		m_base.AddHandler(m_oHButtonEventHandler);
		m_commander.AddHandler(m_oHButtonEventHandler);
		m_economy.AddHandler(m_oHButtonEventHandler);
		m_map.AddHandler(m_oHButtonEventHandler);
		m_credits.AddHandler(m_oHButtonEventHandler);
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
			int currentItem = m_combokey.GetCurrentItem();
			
			if (m_lastItemIndex != currentItem)
			{
				InputBinding m_binding = GetGame().GetInputManager().CreateUserBinding();
				m_binding.StartCapture("CTI_OpenMainMenu", EInputDeviceType.KEYBOARD, "primary:click", false);
				array<string> bind = {};

				if (currentItem == 0)
				{
					bind.Insert("keyboard:KC_NUMPAD0");
				}
			
				if (currentItem == 1)
				{
					bind.Insert("keyboard:KC_RCONTROL");
				}
				
				if (!bind.IsEmpty())
				{
					m_binding.SaveCapture(bind);
					m_binding.Save(); // Saved to profile
					
					m_lastItemIndex = currentItem;
				}
			}
			m_timeDelta = 0;
		}
	}
};