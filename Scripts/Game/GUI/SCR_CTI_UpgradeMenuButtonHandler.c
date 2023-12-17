class SCR_CTI_UpgradeMenuButtonHandler : ScriptedWidgetEventHandler
{
	//------------------------------------------------------------------------------------------------
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		w.SetColor(Color.White);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		w.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		switch (w.GetName())
		{
			case "StartUpgrade":
			{
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();

				SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
				if (!clientData && !clientData.isCommander()) break;

				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();

				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				SCR_CTI_UpgradeData upgradeData = SCR_CTI_UpgradeData.Cast(listboxcomp.GetItemData(selected));
				
				int indexLink = gameMode.Upgrades.findIndexByName(upgradeData.getLink());
				int indexLink2 = gameMode.Upgrades.findIndexByName(upgradeData.getLink2());
				SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(gameMode.FindComponent(SCR_CTI_UpgradeComponent));
				bool dependencesReady = false;
				switch (fk)
				{
					case "USSR":
					{
						switch (true)
						{
							case (upgradeData.getLink() == "None"): dependencesReady = true; break;
							case (indexLink == -1 && indexLink2 == -1): dependencesReady = true; break;
							case ((indexLink > -1 && upgradeComp.getUpgradeStatus(fk, indexLink) == UpgradeStatus.FINISHED) && indexLink2 == -1): dependencesReady = true; break;
							case ((indexLink > -1 && upgradeComp.getUpgradeStatus(fk, indexLink) == UpgradeStatus.FINISHED) && (indexLink2 > -1 && upgradeComp.getUpgradeStatus(fk, indexLink) == UpgradeStatus.FINISHED)): dependencesReady = true; break;
						}

						break;
					}
					case "US":
					{
						switch (true)
						{
							case (upgradeData.getLink() == "None"): dependencesReady = true; break;
							case (indexLink == -1 && indexLink2 == -1): dependencesReady = true; break;
							case ((indexLink > -1 && upgradeComp.getUpgradeStatus(fk, indexLink) == UpgradeStatus.FINISHED) && indexLink2 == -1): dependencesReady = true; break;
							case ((indexLink > -1 && upgradeComp.getUpgradeStatus(fk, indexLink) == UpgradeStatus.FINISHED) && (indexLink2 > -1 && upgradeComp.getUpgradeStatus(fk, indexLink) == UpgradeStatus.FINISHED)): dependencesReady = true; break;
						}
						
						break;
					}
				}

				if (!dependencesReady)
				{
					SCR_HintManagerComponent.ShowCustomHint("Not all dependencies are met to start this upgrade.", "Information", 5);
					break;
				}

				int cost = upgradeData.getCost();
				int commanderFunds = gameMode.getCommanderFunds(fk);
				if (cost <= commanderFunds)
				{
					netComp.changeCommanderFundsServer(fk, -cost);
				} else {
					SCR_HintManagerComponent.ShowCustomHint("You do not have enough funds to perform this operation.", "Information", 5);
					break;
				}				
				int upgradeindex = gameMode.Upgrades.findIndexByName(upgradeData.getName());
				
				netComp.StartUpgradeServer(fk, upgradeindex);
				SCR_HintManagerComponent.ShowCustomHint("Upgrade started.", "Information", 5);
				
				//menuManager.CloseAllMenus();
				
				break;
			}
			case "CancelUpgrade":
			{
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();

				SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
				if (!clientData && !clientData.isCommander()) break;
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();

				netComp.StopUpgradeServer(fk);
				SCR_HintManagerComponent.ShowCustomHint("Upgrade cancelled.", "Information", 5);

				//auto menuManager = GetGame().GetMenuManager();
				//menuManager.CloseAllMenus();

				break;
			}
		}
		
		return true;
	}
};