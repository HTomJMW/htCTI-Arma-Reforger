class SCR_CTI_BuildMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;
	
	protected Widget m_wRoot;
	protected WindowWidget m_window;
	protected TextWidget m_resources;
	protected TextWidget m_workers;
	protected ButtonWidget m_addworker;
	protected ButtonWidget m_buildstructure;
	protected ButtonWidget m_undostructure;
	protected ButtonWidget m_defautomanning;
	protected ButtonWidget m_autoalignwalls;
	protected ButtonWidget m_builddefense;
	protected ButtonWidget m_undodefense;
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	protected RichTextWidget m_addworkertext;
	protected RichTextWidget m_buildstructuretext;
	protected RichTextWidget m_undostructuretext;
	protected RichTextWidget m_defautomanningtext;
	protected RichTextWidget m_autoalignwallstext;
	protected RichTextWidget m_builddefensetext;
	protected RichTextWidget m_undodefensetext;
	protected RichTextWidget m_backtext;
	protected RichTextWidget m_exittext;

	protected OverlayWidget m_listboxleft;
	protected OverlayWidget m_listboxright;
	protected SCR_ListBoxComponent m_listboxleftcomp;
	protected SCR_ListBoxComponent m_listboxrightcomp;
	
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		playerFaction = affiliationComp.GetAffiliatedFaction();
		
		m_wRoot = GetRootWidget();
		m_window = WindowWidget.Cast(m_wRoot.FindAnyWidget("Window"));
		m_resources = TextWidget.Cast(m_wRoot.FindAnyWidget("Resources"));
		m_workers = TextWidget.Cast(m_wRoot.FindAnyWidget("Workers"));
		
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
		
		// button texts
		m_addworkertext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("AddWorkerText"));
		m_buildstructuretext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("BuildStructureText"));
		m_undostructuretext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UndoStructureText"));
		m_defautomanningtext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("DefAutoManningText"));
		m_autoalignwallstext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("AutoAlignWallsText"));
		m_builddefensetext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("BuildDefenseText"));
		m_undodefensetext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UndoDefenseText"));
		m_backtext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("BackText"));
		m_exittext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("ExitText"));

		// listboxes
		m_listboxleft = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxLeft"));
		m_listboxright = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBoxRight"));
		m_listboxleftcomp = SCR_ListBoxComponent.Cast(m_listboxleft.FindHandler(SCR_ListBoxComponent));
		m_listboxrightcomp = SCR_ListBoxComponent.Cast(m_listboxright.FindHandler(SCR_ListBoxComponent));

		// handler
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		
		m_addworker.SetName("ADDWORKER");
		m_addworker.SetColor(Color.Orange);
		m_addworker.AddHandler(m_buttonEventHandler);
		
		m_buildstructure.SetName("BUILDSTRUCTURE");
		m_buildstructure.SetColor(Color.Orange);
		m_buildstructure.AddHandler(m_buttonEventHandler);
		
		m_undostructure.SetName("UNDOSTRUCTURE");
		m_undostructure.SetColor(Color.Orange);
		m_undostructure.AddHandler(m_buttonEventHandler);
		
		m_defautomanning.SetName("DEFAUTOMANNING");
		m_defautomanning.SetColor(Color.Orange);
		m_defautomanning.AddHandler(m_buttonEventHandler);
		
		m_autoalignwalls.SetName("AUTOALIGNWALLS");
		m_autoalignwalls.SetColor(Color.Orange);
		m_autoalignwalls.AddHandler(m_buttonEventHandler);
		
		m_builddefense.SetName("BUILDDEFENSE");
		m_builddefense.SetColor(Color.Orange);
		m_builddefense.AddHandler(m_buttonEventHandler);
		
		m_undodefense.SetName("UNDODEFENSE");
		m_undodefense.SetColor(Color.Orange);
		m_undodefense.AddHandler(m_buttonEventHandler);
		
		m_back.SetName("BACKBUTTON");
		m_back.SetColor(Color.Orange);
		m_back.AddHandler(m_buttonEventHandler);
		
		m_exit.SetName("EXITBUTTON");
		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_buttonEventHandler);

		FactionKey fk = playerFaction.GetFactionKey();
		switch (fk)
		{
			case "USSR":
			{
				for (int i = 0; i < gameMode.FactoriesUSSR.g_USSR_Factories.Count(); i++)
				{
					SCR_CTI_FactoryData factoryData;
					factoryData = gameMode.FactoriesUSSR.g_USSR_Factories[i];
					m_listboxleftcomp.AddItem(factoryData.getPri().ToString() + "$ " + factoryData.getName());
				}
				
				for (int j = 0; j < gameMode.DefensesUSSR.g_USSR_Defenses.Count(); j++)
				{
					SCR_CTI_DefenseData defData;
					defData = gameMode.DefensesUSSR.g_USSR_Defenses[j];
					m_listboxrightcomp.AddItem(defData.getPri().ToString() + "$ " + defData.getName());
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < gameMode.FactoriesUS.g_US_Factories.Count(); i++)
				{
					SCR_CTI_FactoryData factoryData;
					factoryData = gameMode.FactoriesUS.g_US_Factories[i];
					m_listboxleftcomp.AddItem(factoryData.getPri().ToString() + "$ " + factoryData.getName());
				}
				
				for (int j = 0; j < gameMode.DefensesUS.g_US_Defenses.Count(); j++)
				{
					SCR_CTI_DefenseData defData;
					defData = gameMode.DefensesUS.g_US_Defenses[j];
					m_listboxrightcomp.AddItem(defData.getPri().ToString() + "$ " + defData.getName());
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
		int sizeCDA = gameMode.ClientDataArray.Count();
		SCR_CTI_ClientData clientData;
		for (int i = 0; i < sizeCDA; i++)
		{
			if (gameMode.ClientDataArray[i].getPlayerId() == playerId)
			{
				clientData = gameMode.ClientDataArray[i];
				break;
			}
		}
		if (clientData)
		{
			int funds = clientData.getFunds();
			m_resources.SetText("Resources: " + funds.ToString() + "$");
		}
	}
};