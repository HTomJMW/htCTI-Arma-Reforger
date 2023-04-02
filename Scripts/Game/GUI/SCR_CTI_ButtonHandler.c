class SCR_CTI_ButtonHandler : ScriptedWidgetEventHandler
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
		w.SetColor(Color.Orange);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		switch (w.GetName())
		{
			case "UnitsButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_PurchaseMenu);
				break;
			}
			case "BuildButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_BuildMenu);
				break;
			}
			case "UnflipNearestVehicleButton":
			{
				SCR_CTI_UnflipNearestVehicle unflipveh = new SCR_CTI_UnflipNearestVehicle();
				unflipveh.unflip();
				break;
			}
			case "LeaveComButton":
			{
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				netComp.clearCommanderIdRpl(affiliationComp.GetAffiliatedFaction().GetFactionKey());

				SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
				if (clientData) clientData.setCommander(false);
				
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();

				break;
			}
			case "GearButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_GearMenu);
				
				break;
			}
			case "UpgradesButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_UpgradeMenu);
				
				break;
			}
			case "StartUpgrade":
			{
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());

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
				int cost = upgradeData.getCost();
				int commanderFunds = gameMode.getCommanderFunds(fk);
				if (cost < commanderFunds)
				{
					netComp.changeCommanderFundsServer(fk, -cost);
				} else {
					break;
				}				
				int upgradeindex = gameMode.Upgrades.findIndexByName(upgradeData.getName());
				
				netComp.StartUpgradeServer(fk, upgradeindex);
				
				menuManager.CloseAllMenus();
				
				break;
			}
			case "CancelUpgrade":
			{
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());

				SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
				if (!clientData && !clientData.isCommander()) break;
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();

				netComp.StopUpgradeServer(fk);

				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				
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
						res = facData.getResname();
						dist = facData.getDistance();
						placement = facData.getPlacement();
						cost = facData.getPrice();

						break;
					}
					case "US":
					{
						facData = gameMode.FactoriesUS.g_US_Factories[selected];
						res = facData.getResname();
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
			case "VideoSettingsButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_VideoSettingsMenu);

				break;
			}
			case "Purchase":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				
				XComboBoxWidget comboboxfactory = XComboBoxWidget.Cast(root.FindAnyWidget("XComboBoxFactory"));
				int combofacitem = comboboxfactory.GetCurrentItem();
				
				SCR_CTI_PurchaseMenu pm = SCR_CTI_PurchaseMenu.Cast(openedMenu);
				array<IEntity> facts = pm.getSortedFactoriesForCombobox();
				
				RplComponent factRplComp = RplComponent.Cast(facts[combofacitem].FindComponent(RplComponent));
				RplId factRplid = factRplComp.Id();

				SCR_CTI_FactoryData factData;
				int factIndex = -1;
				switch(fk)
				{
					case "USSR":
					{
						factIndex = gameMode.FactoriesUSSR.findIndexFromResourcename(facts[combofacitem].GetPrefabData().GetPrefabName());
						factData = gameMode.FactoriesUSSR.g_USSR_Factories[factIndex];
						break;
					}
					case "US":
					{
						factIndex = gameMode.FactoriesUS.findIndexFromResourcename(facts[combofacitem].GetPrefabData().GetPrefabName());
						factData = gameMode.FactoriesUS.g_US_Factories[factIndex];
						break;
					}
				}

				float dist = factData.getDistance();
				float placement = factData.getPlacement();
				vector dir = facts[combofacitem].GetTransformAxis(2);

				vector mat[4];
				facts[combofacitem].GetTransform(mat);

				vector angles = mat[2].VectorToAngles();
				angles[0] = angles[0] + placement;
				mat[2] = angles.AnglesToVector();

				if (placement == 0) mat[3] = mat[3] - (dir * dist);
				if (placement == 180) mat[3] = mat[3] + (dir * dist);
				mat[3][1] = GetGame().GetWorld().GetSurfaceY(mat[3][0], mat[3][2]);
				
				vector emptyPos;
				SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, mat[3], 20, 4, 3);
				mat[3] = emptyPos;

				SCR_CTI_UnitData unitData = SCR_CTI_UnitData.Cast(listboxcomp.GetItemData(selected));
				ResourceName res = unitData.getResname();
				int buildTime = unitData.getBuildtime();
				int cost = unitData.getPrice();
				
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData && clientData.getFunds() < cost) break;

				EntityID groupID = pm.getGroupforCombobox().GetID();
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				netComp.factoryProductionServer(res, fk, groupID, factRplid, mat, pc.GetPlayerId(), buildTime);

				break;
			}
			case "UnitsCameraButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_UnitCamMenu);

				break;
			}
			case "OnlineHelpButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_OnlineHelpMenu);

				break;
			}
			case "TransferResourcesButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_TransferResourcesMenu);

				break;
			}
			case "Transfer":
			{
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				SliderWidget slider = SliderWidget.Cast(root.FindAnyWidget("Slider"));
				int value = slider.GetCurrent();
				
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected < 0) break;
				
				SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
				
				if (clientData)
				{
					FactionKey factionkey = GetGame().GetFactionManager().GetFactionByIndex(clientData.getFactionIndex()).GetFactionKey();
					if (clientData.isCommander())
					{
						netComp.changeCommanderFundsServer(factionkey, -value);
					} else {
						netComp.changeFundsServer(playerId, -value);
					}
				}

				RplComponent rplCompReceiver = RplComponent.Cast(listboxcomp.GetItemData(listboxcomp.GetSelectedItem()));
				RplId rplid = rplCompReceiver.Id();
				int receiverId = GetGame().GetPlayerManager().GetPlayerIdFromEntityRplId(rplid);
				
				clientData = null;
				clientData = gameMode.getClientData(receiverId);

				if (clientData)
				{
					FactionKey receiverFactionKey = GetGame().GetFactionManager().GetFactionByIndex(clientData.getFactionIndex()).GetFactionKey();
					if (clientData.isCommander())
					{
						netComp.changeCommanderFundsServer(receiverFactionKey, value);
					} else {
						netComp.changeFundsServer(receiverId, value);
					}
				}

				break;
			}
			case "SetPriorityTownButton":
			{
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());

				SCR_MapEntity.GetOnMapOpen().Insert(gameMode.OnPrioMapOpen);
				SCR_MapEntity.GetOnSelection().Insert(gameMode.OnPrioMapSelection);
				SCR_MapEntity.GetOnMapClose().Insert(gameMode.OnPrioMapClose);

				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.MapMenu);

				break;
			}
			case "ClearPriorityButton":
			{
				PlayerController pc = GetGame().GetPlayerController();
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				netComp.setPriorityServer(fk, "");
				
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				
				break;
			}
			case "ServiceMenuButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_ServiceMenu);
				
				break;
			}
			case "RadioButton":
			{
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();
				SCR_CTI_RadioConnectionComponent rcc = SCR_CTI_RadioConnectionComponent.Cast(player.FindComponent(SCR_CTI_RadioConnectionComponent));
				if (rcc && rcc.hasRadio())
				{
					if (rcc.radioIsOn())
					{
						rcc.setRadioOn(false);
					} else {
						rcc.setRadioOn(true);
					}
				}
				
				break;
			}
			case "SatelliteCameraButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_SatCamMenu);
				break;
			}
		}
		
		return true;
	}
};