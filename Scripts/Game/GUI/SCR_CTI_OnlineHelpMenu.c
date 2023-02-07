class SCR_CTI_OnlineHelpMenu : ChimeraMenuBase
{
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

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;
	protected ref SCR_CTI_OnlineHelpButtonHandler m_oHButtonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
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
		m_combokey.AddItem("NumPad 0"); // TODO temporary

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		m_oHButtonEventHandler = new SCR_CTI_OnlineHelpButtonHandler();

		m_back.SetColor(Color.Orange);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(Color.Orange);
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
		// TODO INPUTBINDING
	}
};