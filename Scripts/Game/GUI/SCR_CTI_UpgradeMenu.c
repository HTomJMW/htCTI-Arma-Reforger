class SCR_CTI_UpgradeMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_UpgradeComponent m_upgradeComp;
	protected PlayerController m_pc;
	protected int m_playerId;
	protected FactionKey m_factionKey;
	protected FactionAffiliationComponent m_affiliationComp;
	protected SCR_CTI_ClientData m_clientData;
	
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
	protected RichTextWidget m_currentupgradetext;

	string currentText = "Current Upgrade: No Running Upgrade!";

	protected RichTextWidget m_backtext;
	protected RichTextWidget m_exittext;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_UpgradeMenuButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_upgradeComp = SCR_CTI_UpgradeComponent.Cast(m_gameMode.FindComponent(SCR_CTI_UpgradeComponent));
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_affiliationComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_factionKey = m_affiliationComp.GetAffiliatedFaction().GetFactionKey();
		
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
		m_currentupgradetext = RichTextWidget.Cast(m_wRoot.FindAnyWidget("CurrentUpgrade"));

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_UpgradeMenuButtonHandler();
		
		m_clientData = m_gameMode.getClientData(m_playerId);
		array<IEntity> ccList = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Control Center");
		if (m_clientData && m_clientData.isCommander() && !ccList.IsEmpty())
		{
			m_cancelupgrade.SetColor(SCR_CTI_Constants.CTI_ORANGE);
			m_cancelupgrade.AddHandler(m_buttonEventHandler);

			m_upgrade.SetColor(SCR_CTI_Constants.CTI_ORANGE);
			m_upgrade.AddHandler(m_buttonEventHandler);
		} else {
			m_cancelupgrade.SetColor(Color.Gray);
			m_cancelupgrade.SetEnabled(false);
			
			m_upgrade.SetColor(Color.Gray);
			m_upgrade.SetEnabled(false);
		}

		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);

		listboxLoad();
	}

	//------------------------------------------------------------------------------------------------
	protected void listboxLoad()
	{
		SCR_CTI_UpgradeData upgradeData;
		switch (m_factionKey)
		{
			case "USSR":
			{
				for (int i = 0; i < m_gameMode.Upgrades.g_Upgrades.Count(); i++)
				{
					upgradeData = m_gameMode.Upgrades.g_Upgrades[i];
					if (m_upgradeComp.getUpgradeStatus(m_factionKey, i) != UpgradeStatus.FINISHED)
					{
						int historyIndex = m_gameMode.Upgrades.findIndexByName(upgradeData.getHistrory());
						if (historyIndex == -1 || (historyIndex > -1 && m_upgradeComp.getUpgradeStatus(m_factionKey, historyIndex) == UpgradeStatus.FINISHED))
						{
							m_listboxcomp.AddItem(upgradeData.getName(), upgradeData);
						}
					}
				}
				if (m_upgradeComp.getRunningUpgradeIndex(m_factionKey) != -1)
				{
					upgradeData = m_gameMode.Upgrades.g_Upgrades[m_upgradeComp.getRunningUpgradeIndex(m_factionKey)];
					int remaringTime = m_upgradeComp.getRemainingTime(m_factionKey);
					m_currentupgradetext.SetText("Current Upgrade: " + upgradeData.getName() + " :: " + remaringTime + "s");
				} else {
					m_currentupgradetext.SetText(currentText);
				}
				break;
			}
			case "US":
			{
				for (int i = 0; i < m_gameMode.Upgrades.g_Upgrades.Count(); i++)
				{
					upgradeData = m_gameMode.Upgrades.g_Upgrades[i];
					if (m_upgradeComp.getUpgradeStatus(m_factionKey, i) != UpgradeStatus.FINISHED)
					{
						int historyIndex = m_gameMode.Upgrades.findIndexByName(upgradeData.getHistrory());
						if (historyIndex == -1 || (historyIndex > -1 && m_upgradeComp.getUpgradeStatus(m_factionKey, historyIndex) == UpgradeStatus.FINISHED))
						{
							m_listboxcomp.AddItem(upgradeData.getName(), upgradeData);
						}
					}
				}
				if (m_upgradeComp.getRunningUpgradeIndex(m_factionKey) != -1)
				{
					upgradeData = m_gameMode.Upgrades.g_Upgrades[m_upgradeComp.getRunningUpgradeIndex(m_factionKey)];
					int remaringTime = m_upgradeComp.getRemainingTime(m_factionKey);
					m_currentupgradetext.SetText("Current Upgrade: " + upgradeData.getName() + " :: " + remaringTime + "s");
				} else {
					m_currentupgradetext.SetText(currentText);
				}
				break;
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void listboxClear()
	{
		for (int i = m_listboxcomp.GetItemCount() - 1; i >= 0; i--)
		{
			m_listboxcomp.RemoveItem(i);
		}
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
			bool needListboxChange = false;
			SCR_CTI_UpgradeData upgradeData;
			switch (m_factionKey)
			{
				case "USSR":
				{
					if (m_upgradeComp.getRunningUpgradeIndex(m_factionKey) != -1)
					{
						upgradeData = m_gameMode.Upgrades.g_Upgrades[m_upgradeComp.getRunningUpgradeIndex(m_factionKey)];
						int remaringTime = m_upgradeComp.getRemainingTime(m_factionKey);
						m_currentupgradetext.SetText("Current Upgrade: " + upgradeData.getName() + " :: " + remaringTime + "s");
					} else {
						m_currentupgradetext.SetText(currentText);
					}
					for (int i = 0; i < m_listboxcomp.GetItemCount(); i++)
					{
						upgradeData = SCR_CTI_UpgradeData.Cast(m_listboxcomp.GetItemData(i));
 						int upgradeIndex = m_gameMode.Upgrades.findIndexByName(upgradeData.getName());
						if (m_upgradeComp.getUpgradeStatus(m_factionKey, upgradeIndex) == UpgradeStatus.FINISHED) needListboxChange = true;
					}
					break;
				}	
				case "US":
				{
					if (m_upgradeComp.getRunningUpgradeIndex(m_factionKey) != -1)
					{
						upgradeData = m_gameMode.Upgrades.g_Upgrades[m_upgradeComp.getRunningUpgradeIndex(m_factionKey)];
						int remaringTime = m_upgradeComp.getRemainingTime(m_factionKey);
						m_currentupgradetext.SetText("Current Upgrade: " + upgradeData.getName() + " :: " + remaringTime + "s");
					} else {
						m_currentupgradetext.SetText(currentText);
					}
					for (int i = 0; i < m_listboxcomp.GetItemCount(); i++)
					{
						upgradeData = SCR_CTI_UpgradeData.Cast(m_listboxcomp.GetItemData(i));
 						int upgradeIndex = m_gameMode.Upgrades.findIndexByName(upgradeData.getName());
						if (m_upgradeComp.getUpgradeStatus(m_factionKey, upgradeIndex) == UpgradeStatus.FINISHED) needListboxChange = true;
					}
					break;
				}
			}
			
			if (needListboxChange)
			{
				listboxClear();
				listboxLoad();
			}

			int selected = m_listboxcomp.GetSelectedItem();
			if (selected == -1) return;

			int funds = 0;
			if (m_clientData)
			{
				if (m_clientData.isCommander())
				{
					funds = m_gameMode.getCommanderFunds(m_factionKey);
				} else {
					funds = m_clientData.getFunds();
				}
			}

			upgradeData = SCR_CTI_UpgradeData.Cast(m_listboxcomp.GetItemData(selected));
			m_labeltext.SetText(upgradeData.getLabel());
			m_upgradeleveltext.SetText("Upgrade Level: " + upgradeData.getLevel().ToString());
			m_neededfundstext.SetText("Needed Funds: " + upgradeData.getCost().ToString() + "$ / " + funds.ToString() + "$");
			m_neededtimetext.SetText("Needed Time: " + upgradeData.getTime().ToString() + "s");
			m_dependencetext.SetText(upgradeData.getLink() + "\n" + upgradeData.getLink2());
			m_descriptiontext.SetText(upgradeData.getDesc());

			m_timeDelta = 0;
		}
	}
};