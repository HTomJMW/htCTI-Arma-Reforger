class SCR_CTI_UpgradeMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;
	
	protected Widget m_wRoot;
	protected WindowWidget m_window;
	
	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;
	
	protected ButtonWidget m_cancelupgrade;
	protected ButtonWidget m_upgrade;
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	
	protected RichTextWidget m_labeltext;
	protected RichTextWidget m_upgradeleveltext;
	protected RichTextWidget m_neededfundstext;
	protected RichTextWidget m_neededtimetext;
	protected RichTextWidget m_dependencelabeltext;
	protected RichTextWidget m_dependencetext;
	protected RichTextWidget m_descriptionlabeltext;
	protected RichTextWidget m_descriptiontext;
	
	protected RichTextWidget m_backtext;
	protected RichTextWidget m_exittext;

	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;
	
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		playerFaction = affiliationComp.GetAffiliatedFaction();
		
		m_wRoot = GetRootWidget();
		m_window = WindowWidget.Cast(m_wRoot.FindAnyWidget("Window"));
		
		// listbox
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));
		
		// buttons
		m_cancelupgrade = ButtonWidget.Cast(m_wRoot.FindAnyWidget("CancelUpgrade"));
		m_upgrade = ButtonWidget.Cast(m_wRoot.FindAnyWidget("StartUpgrade"));
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		// button texts
		m_backtext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("BackText"));
		m_exittext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("ExitText"));
		
		m_labeltext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UpgradeLabel"));
		m_upgradeleveltext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UpgradeLevel"));
		m_neededfundstext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UpgradeFunds"));
		m_neededtimetext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UpgradeTime"));
		m_dependencelabeltext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UpgradeDependence"));
		m_dependencetext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("DependenceText"));
		m_descriptionlabeltext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("UpgradeDescription"));
		m_descriptiontext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("DescriptionText"));

		// handler
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		
		m_cancelupgrade.SetName("CANCELUPGRADE");
		m_cancelupgrade.SetColor(Color.Orange);
		m_cancelupgrade.AddHandler(m_buttonEventHandler);
		
		m_upgrade.SetName("STARTUPGRADE");
		m_upgrade.SetColor(Color.Orange);
		m_upgrade.AddHandler(m_buttonEventHandler);
		
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
				for (int i = 0; i < gameMode.UpgradesUSSR.g_Upgrades.Count(); i++)
				{
					SCR_CTI_UpgradeData upgradeData;
					upgradeData = gameMode.UpgradesUSSR.g_Upgrades[i];
					m_listboxcomp.AddItem(upgradeData.getName());
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < gameMode.UpgradesUS.g_Upgrades.Count(); i++)
				{
					SCR_CTI_UpgradeData upgradeData;
					upgradeData = gameMode.UpgradesUS.g_Upgrades[i];
					m_listboxcomp.AddItem(upgradeData.getName());
				}
				break;
			}		
		}
	}
	
	override void OnMenuOpen()
	{
	}
	
	override void OnMenuUpdate(float tDelta)
	{
		/*int sizeCDA = gameMode.ClientDataArray.Count();
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
			// todo
		}*/
		
		int selected = m_listboxcomp.GetSelectedItem();
		if (selected == -1) return;
		
		FactionKey fk = playerFaction.GetFactionKey();
		switch (fk)
		{
			case "USSR":
			{
				SCR_CTI_UpgradeData upgradeData = gameMode.UpgradesUSSR.g_Upgrades[selected];
				m_labeltext.SetText(upgradeData.getLabel());
				m_upgradeleveltext.SetText("Upgrade Level: " + upgradeData.getLevel().ToString());
				m_neededfundstext.SetText("Needed Funds: " + upgradeData.getCost().ToString() + "$");
				m_neededtimetext.SetText("Needed Time: " + upgradeData.getTime().ToString() + "s");
				
				m_dependencetext.SetText(upgradeData.getLink());
				m_descriptiontext.SetText(upgradeData.getDesc());
				
				break;
			}
			
			case "US":
			{
				SCR_CTI_UpgradeData upgradeData = gameMode.UpgradesUS.g_Upgrades[selected];
				m_labeltext.SetText(upgradeData.getLabel());
				m_upgradeleveltext.SetText("Upgrade Level: " + upgradeData.getLevel().ToString());
				m_neededfundstext.SetText("Needed Funds: " + upgradeData.getCost().ToString() + "$");
				m_neededtimetext.SetText("Needed Time: " + upgradeData.getTime().ToString() + "s");
				
				m_dependencetext.SetText(upgradeData.getLink());
				m_descriptiontext.SetText(upgradeData.getDesc());
				
				break;
			}		
		}
	}
};