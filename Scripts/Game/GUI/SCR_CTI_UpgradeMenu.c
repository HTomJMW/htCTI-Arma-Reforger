class SCR_CTI_UpgradeMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected SCR_CTI_UpgradeComponent upgradeComp;
	protected PlayerController pc;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;
	protected SCR_CTI_ClientData clientData;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.3;
	
	protected Widget m_wRoot;
	
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

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		upgradeComp = SCR_CTI_UpgradeComponent.Cast(gameMode.FindComponent(SCR_CTI_UpgradeComponent));
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		playerFaction = affiliationComp.GetAffiliatedFaction();
		
		m_wRoot = GetRootWidget();
		
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

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		
		clientData = gameMode.getClientData(playerId);
		array<IEntity> ccList = SCR_CTI_GetSideFactories.GetSideFactoriesByType(playerFaction.GetFactionKey(), "Control Center");
		if (clientData && clientData.isCommander() && ccList)
		{
			m_cancelupgrade.SetColor(Color.Orange);
			m_cancelupgrade.AddHandler(m_buttonEventHandler);

			m_upgrade.SetColor(Color.Orange);
			m_upgrade.AddHandler(m_buttonEventHandler);
		} else {
			m_cancelupgrade.SetColor(Color.Gray);
			m_cancelupgrade.SetEnabled(false);
			
			m_upgrade.SetColor(Color.Gray);
			m_upgrade.SetEnabled(false);
		}

		m_back.SetColor(Color.Orange);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_commonButtonHandler);
		
		FactionKey fk = playerFaction.GetFactionKey();
		SCR_CTI_UpgradeData upgradeData;
		switch (fk)
		{
			case "USSR":
			{
				for (int i = 0; i < gameMode.Upgrades.g_Upgrades.Count(); i++)
				{
					if (upgradeComp.getUpgradeStatus(fk, i) != UpgradeStatus.FINISHED)
					{
						upgradeData = gameMode.Upgrades.g_Upgrades[i];				
						m_listboxcomp.AddItem(upgradeData.getName(), upgradeData);
					}
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < gameMode.Upgrades.g_Upgrades.Count(); i++)
				{
					if (upgradeComp.getUpgradeStatus(fk, i) != UpgradeStatus.FINISHED)
					{
						upgradeData = gameMode.Upgrades.g_Upgrades[i];		
						m_listboxcomp.AddItem(upgradeData.getName(), upgradeData);
					}
				}
				break;
			}		
		}
		m_listboxcomp.SetItemSelected(0, true); // not working? 0 not selected by default (false marker)
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
			int selected = m_listboxcomp.GetSelectedItem();
			if (selected == -1) return;

			FactionKey fk = playerFaction.GetFactionKey();

			int funds = 0;
			if (clientData)
			{
				if (clientData.isCommander())
				{
					funds = gameMode.getCommanderFunds(fk);
				} else {
					funds = clientData.getFunds();
				}
			}

			SCR_CTI_UpgradeData upgradeData = SCR_CTI_UpgradeData.Cast(m_listboxcomp.GetItemData(selected));
			switch (fk)
			{
				case "USSR":
				{
					m_labeltext.SetText(upgradeData.getLabel());
					m_upgradeleveltext.SetText("Upgrade Level: " + upgradeData.getLevel().ToString());
					m_neededfundstext.SetText("Needed Funds: " + upgradeData.getCost().ToString() + "$ / " + funds.ToString() + "$");
					m_neededtimetext.SetText("Needed Time: " + upgradeData.getTime().ToString() + "s");
					
					m_dependencetext.SetText(upgradeData.getLink());
					m_descriptiontext.SetText(upgradeData.getDesc());
					
					break;
				}
				
				case "US":
				{
					m_labeltext.SetText(upgradeData.getLabel());
					m_upgradeleveltext.SetText("Upgrade Level: " + upgradeData.getLevel().ToString());
					m_neededfundstext.SetText("Needed Funds: " + upgradeData.getCost().ToString() + "$ / " + funds.ToString() + "$");
					m_neededtimetext.SetText("Needed Time: " + upgradeData.getTime().ToString() + "s");
					
					m_dependencetext.SetText(upgradeData.getLink());
					m_descriptiontext.SetText(upgradeData.getDesc());
					
					break;
				}		
			}
			// need remove finished upgrades from list when complete

			m_timeDelta = 0;
		}
	}
};