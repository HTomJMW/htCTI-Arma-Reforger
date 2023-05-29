class SCR_CTI_BuildMenuButtonHandler : ScriptedWidgetEventHandler
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
			case "AddWorker":
			{
				// TODO Information notification if need
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(affiliationComp.GetAffiliatedFaction().GetFactionKey());
				if (!mhq) break;
				
				SCR_CTI_UpdateWorkersComponent uwc = SCR_CTI_UpdateWorkersComponent.Cast(gameMode.FindComponent(SCR_CTI_UpdateWorkersComponent));
				if (uwc.getWorkersCount(affiliationComp.GetAffiliatedFaction().GetFactionKey()) >= SCR_CTI_Constants.WORKERSLIMIT) break;

				int funds = 0;
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData && clientData.isCommander())
				{
					funds = gameMode.getCommanderFunds(affiliationComp.GetAffiliatedFaction().GetFactionKey());
				}
				if (funds < SCR_CTI_Constants.WORKERPRICE) break;

				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				netComp.addWorkerServer(affiliationComp.GetAffiliatedFaction().GetFactionKey());

				break;
			}
			case "BuildStructure":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBoxLeft"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				menuManager.CloseAllMenus(); // close this menu before confirm menu show up
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				ChimeraCharacter player = ChimeraCharacter.Cast(pc.GetControlledEntity());
				if (player.IsInVehicle()) break;
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				
				IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(fk);
				if (!mhq) break;
				
				SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(mhq.FindComponent(SCR_VehicleDamageManagerComponent));
				if (vehicleDamageManager.IsDestroyed()) break;
				
				float distance = vector.Distance(mhq.GetOrigin(), player.GetOrigin());
				if (distance > SCR_CTI_Constants.BUILDRANGE) break;
				
				SCR_CTI_FactoryData facData;
				ResourceName res;
				float dist;
				int placement;
				int cost;

				switch (fk)
				{
					case "USSR":
					{
						facData = gameMode.FactoriesUSSR.g_USSR_Factories[selected];
						res = facData.getResName();
						dist = facData.getDistance();
						placement = facData.getPlacement();
						cost = facData.getPrice();

						break;
					}
					case "US":
					{
						facData = gameMode.FactoriesUS.g_US_Factories[selected];
						res = facData.getResName();
						dist = facData.getDistance();
						placement = facData.getPlacement();
						cost = facData.getPrice();

						break;
					}
				}
				
				if (gameMode.getCommanderFunds(fk) < cost) break;

				SCR_CTI_PlacingStructureComponent placingStructureComp = SCR_CTI_PlacingStructureComponent.Cast(pc.FindComponent(SCR_CTI_PlacingStructureComponent));
				if (!placingStructureComp.getStartPlacing()) placingStructureComp.createStructurePreview(fk, res, dist, placement, true);

				break;
			}
			case "BuildDefense":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBoxRight"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				menuManager.CloseAllMenus(); // close this menu before confirm menu show up
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				ChimeraCharacter player = ChimeraCharacter.Cast(pc.GetControlledEntity());
				if (player.IsInVehicle()) break;
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				
				IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(fk);
				if (!mhq) break;
				
				SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(mhq.FindComponent(SCR_VehicleDamageManagerComponent));
				if (vehicleDamageManager.IsDestroyed()) break;
				
				float distance = vector.Distance(mhq.GetOrigin(), player.GetOrigin());
				if (distance > SCR_CTI_Constants.BUILDRANGE) break;

				SCR_CTI_DefenseData defData;
				ResourceName res;
				float dist;
				float placement;
				int cost;

				switch (fk)
				{
					case "USSR":
					{
						defData = gameMode.DefensesUSSR.g_USSR_Defenses[selected];
						res = defData.getResname();
						dist = defData.getDistance();
						placement = defData.getPlacement();
						cost = defData.getPrice();

						break;
					}
					case "US":
					{
						defData = gameMode.DefensesUS.g_US_Defenses[selected];
						res = defData.getResname();
						dist = defData.getDistance();
						placement = defData.getPlacement();
						cost = defData.getPrice();

						break;
					}
				}
				
				int funds = 0;
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData)
				{
					if (clientData.isCommander())
					{
						funds = gameMode.getCommanderFunds(fk);
					} else {
						funds = clientData.getFunds();
					}
				}
				
				if (funds < cost) break;

				SCR_CTI_PlacingDefenseComponent placingDefComp = SCR_CTI_PlacingDefenseComponent.Cast(pc.FindComponent(SCR_CTI_PlacingDefenseComponent));
				if (!placingDefComp.getStartPlacing()) placingDefComp.createDefPreview(res, dist, placement, true);

				break;
			}
		}
		
		return true;
	}
};