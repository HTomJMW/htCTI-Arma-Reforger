class SCR_CTI_BuildMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected SCR_CTI_ClientData m_clientData;
	protected int m_playerId;
	protected Faction m_playerFaction;
	protected FactionAffiliationComponent m_affiliationComp;
	protected SCR_CTI_UpdateWorkersComponent m_updateWorkersComp;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.5;
	
	protected Widget m_wRoot;

	protected TextWidget m_resources;
	protected TextWidget m_workers;
	
	protected RichTextWidget m_addworkertext;

	protected ButtonWidget m_addworker;
	protected ButtonWidget m_buildstructure;
	protected ButtonWidget m_undostructure;
	protected ButtonWidget m_defautomanning;
	protected ButtonWidget m_autoalignwalls;
	protected ButtonWidget m_builddefense;
	protected ButtonWidget m_undodefense;
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;

	protected OverlayWidget m_listboxleft;
	protected OverlayWidget m_listboxright;
	protected SCR_ListBoxComponent m_listboxleftcomp;
	protected SCR_ListBoxComponent m_listboxrightcomp;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_BuildMenuButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_affiliationComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_playerFaction = m_affiliationComp.GetAffiliatedFaction();
		m_updateWorkersComp = SCR_CTI_UpdateWorkersComponent.Cast(m_gameMode.FindComponent(SCR_CTI_UpdateWorkersComponent));
		
		m_wRoot = GetRootWidget();

		m_resources = TextWidget.Cast(m_wRoot.FindAnyWidget("Resources"));
		m_workers = TextWidget.Cast(m_wRoot.FindAnyWidget("Workers"));

		m_addworkertext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("AddWorkerText"));
		
		// buttons
		m_addworker = ButtonWidget.Cast(m_wRoot.FindAnyWidget("AddWorker"));
		m_buildstructure = ButtonWidget.Cast(m_wRoot.FindAnyWidget("BuildStructure"));
		m_undostructure = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UndoStructure"));
		m_defautomanning = ButtonWidget.Cast(m_wRoot.FindAnyWidget("DefAutoManning"));
		m_autoalignwalls = ButtonWidget.Cast(m_wRoot.FindAnyWidget("AutoAlignWalls"));
		m_builddefense = ButtonWidget.Cast(m_wRoot.FindAnyWidget("BuildDefense"));
		m_undodefense = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UndoDefense"));
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));

		// listboxes
		m_listboxleft = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxLeft"));
		m_listboxright = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxRight"));
		m_listboxleftcomp = SCR_ListBoxComponent.Cast(m_listboxleft.FindHandler(SCR_ListBoxComponent));
		m_listboxrightcomp = SCR_ListBoxComponent.Cast(m_listboxright.FindHandler(SCR_ListBoxComponent));

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_BuildMenuButtonHandler();

		m_addworkertext.SetText("Add Worker " + "[" + SCR_CTI_Constants.WORKERPRICE.ToString() + "$]");

		m_clientData = m_gameMode.getClientData(m_playerId);
		if (m_clientData && m_clientData.isCommander())
		{
			m_addworker.SetColor(SCR_CTI_Constants.CTI_ORANGE);
			m_addworker.AddHandler(m_buttonEventHandler);
			m_buildstructure.SetColor(SCR_CTI_Constants.CTI_ORANGE);
			m_buildstructure.AddHandler(m_buttonEventHandler);
		} else {
			m_addworker.SetColor(Color.Gray);
			m_addworker.SetEnabled(false);
			m_buildstructure.SetColor(Color.Gray);
			m_buildstructure.SetEnabled(false);
		}

		//m_undostructure.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_undostructure.AddHandler(m_buttonEventHandler);
		m_undostructure.SetColor(Color.Gray);
		m_undostructure.SetEnabled(false);
		
		//m_defautomanning.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_defautomanning.AddHandler(m_buttonEventHandler);
		m_defautomanning.SetColor(Color.Gray);
		m_defautomanning.SetEnabled(false);

		//m_autoalignwalls.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_autoalignwalls.AddHandler(m_buttonEventHandler);
		m_autoalignwalls.SetColor(Color.Gray);
		m_autoalignwalls.SetEnabled(false);

		m_builddefense.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_builddefense.AddHandler(m_buttonEventHandler);
		
		//m_undodefense.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_undodefense.AddHandler(m_buttonEventHandler);
		m_undodefense.SetColor(Color.Gray);
		m_undodefense.SetEnabled(false);
		
		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);

		FactionKey factionkey = m_playerFaction.GetFactionKey();
		switch (factionkey)
		{
			case "USSR":
			{
				for (int i = 0; i < m_gameMode.FactoriesUSSR.g_USSR_Factories.Count(); i++)
				{
					SCR_CTI_FactoryData factoryData;
					factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[i];
					m_listboxleftcomp.AddItem(factoryData.getPrice().ToString() + "$ " + factoryData.getName());
				}
				
				for (int j = 0; j < m_gameMode.DefensesUSSR.g_USSR_Defenses.Count(); j++)
				{
					SCR_CTI_DefenseData defData;
					defData = m_gameMode.DefensesUSSR.g_USSR_Defenses[j];
					m_listboxrightcomp.AddItem(defData.getPrice().ToString() + "$ " + defData.getName());
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < m_gameMode.FactoriesUS.g_US_Factories.Count(); i++)
				{
					SCR_CTI_FactoryData factoryData;
					factoryData = m_gameMode.FactoriesUS.g_US_Factories[i];
					m_listboxleftcomp.AddItem(factoryData.getPrice().ToString() + "$ " + factoryData.getName());
				}
				
				for (int j = 0; j < m_gameMode.DefensesUS.g_US_Defenses.Count(); j++)
				{
					SCR_CTI_DefenseData defData;
					defData = m_gameMode.DefensesUS.g_US_Defenses[j];
					m_listboxrightcomp.AddItem(defData.getPrice().ToString() + "$ " + defData.getName());
				}
				break;
			}		
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
		GetGame().GetInputManager().AddActionListener("MenuBack", EActionTrigger.DOWN, back);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		GetGame().GetInputManager().RemoveActionListener("MenuBack", EActionTrigger.DOWN, back);
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
			int funds = 0;
			if (m_clientData)
			{
				if (m_clientData.isCommander())
				{
					funds = m_gameMode.getCommanderFunds(m_playerFaction.GetFactionKey());
				} else {
					funds = m_clientData.getFunds();
				}
			}

			m_resources.SetText("Resources: " + funds.ToString() + "$");

			m_workers.SetText("Workers: " + m_updateWorkersComp.getWorkersCount(m_playerFaction.GetFactionKey()).ToString() + "/" + SCR_CTI_Constants.WORKERSLIMIT.ToString());

			m_timeDelta = 0;
		}
	}
};