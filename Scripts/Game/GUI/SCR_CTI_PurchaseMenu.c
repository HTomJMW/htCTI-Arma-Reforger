class SCR_CTI_PurchaseMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;
	
	protected Widget m_wRoot;
	
	protected RichTextWidget m_cost;
	protected RichTextWidget m_resources;
	
	protected ButtonWidget m_buttoninf;
	protected ButtonWidget m_buttonlight;
	protected ButtonWidget m_buttonheavy;
	protected ButtonWidget m_buttonair;
	protected ButtonWidget m_buttonrep;
	protected ButtonWidget m_buttonammo;
	protected ButtonWidget m_buttonnaval;
	protected ButtonWidget m_buttonflag;
	
	protected ButtonWidget m_driver;
	protected ButtonWidget m_gunner;
	protected ButtonWidget m_commander;
	protected ButtonWidget m_crew;
	protected ButtonWidget m_lock;
	protected ButtonWidget m_unlock;
	
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;

	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;

	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;
	protected ref SCR_CTI_IconButtonHandler m_iconbuttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		playerFaction = affiliationComp.GetAffiliatedFaction();
		
		m_wRoot = GetRootWidget();
		
		m_cost = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Cost"));
		m_resources = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Resources"));
		
		// buttons
		m_buttoninf = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonInf"));
		m_buttonlight = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonLight"));
		m_buttonheavy = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonHeavy"));
		m_buttonair = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonAir"));
		m_buttonrep = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonRep"));
		m_buttonammo = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonAmmo"));
		m_buttonnaval = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonNaval"));
		m_buttonflag = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonFlag"));
		
		m_driver = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonDriver"));
		m_gunner = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonGunner"));
		m_commander = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonCommander"));
		m_crew = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonCrew"));
		m_lock = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonLock"));
		m_unlock = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonUnlock"));
		
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		// listbox
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));

		// handler
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		m_iconbuttonEventHandler = new SCR_CTI_IconButtonHandler();
		
		m_buttoninf.AddHandler(m_iconbuttonEventHandler);
		m_buttonlight.AddHandler(m_iconbuttonEventHandler);
		m_buttonheavy.AddHandler(m_iconbuttonEventHandler);
		m_buttonair.AddHandler(m_iconbuttonEventHandler);
		m_buttonrep.AddHandler(m_iconbuttonEventHandler);
		m_buttonammo.AddHandler(m_iconbuttonEventHandler);
		m_buttonnaval.AddHandler(m_iconbuttonEventHandler);
		m_buttonflag.AddHandler(m_iconbuttonEventHandler);

		m_driver.AddHandler(m_iconbuttonEventHandler);
		m_gunner.AddHandler(m_iconbuttonEventHandler);
		m_commander.AddHandler(m_iconbuttonEventHandler);
		m_crew.AddHandler(m_iconbuttonEventHandler);
		m_lock.AddHandler(m_iconbuttonEventHandler);
		m_unlock.AddHandler(m_iconbuttonEventHandler);

		m_back.SetColor(Color.Orange);
		m_back.AddHandler(m_buttonEventHandler);

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_buttonEventHandler);

		FactionKey fk = playerFaction.GetFactionKey();
		SCR_CTI_UnitData unitData;
		switch (fk)
		{
			case "USSR":
			{
				for (int i = 0; i < gameMode.UnitsUSSR.g_USSR_Units.Count(); i++)
				{
					unitData = gameMode.UnitsUSSR.g_USSR_Units[i];
					m_listboxcomp.AddItem(unitData.getName());
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < gameMode.UnitsUS.g_US_Units.Count(); i++)
				{
					unitData = gameMode.UnitsUS.g_US_Units[i];
					m_listboxcomp.AddItem(unitData.getName());
				}
				break;
			}		
		}
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