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
				SCR_CTI_UnflipNearestVehicle unflipveh = new SCR_CTI_UnflipNearestVehicle;
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
				int upgradeindex = gameMode.Upgrades.findIndexFromName(upgradeData.getName());
				
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
				if (distance > gameMode.BUILDRANGE) break;
				
				SCR_CTI_FactoryData facData;
				ResourceName res;
				float dist;
				int placement;
				vector mat[4];
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				switch (fk)
				{
					case "USSR":
					{
						facData = gameMode.FactoriesUSSR.g_USSR_Factories[selected];
						res = facData.getResname();
						dist = facData.getDistance();
						placement = facData.getPlacement();

						pc.GetControlledEntity().GetTransform(mat);
						
						netComp.buildStructureServer(fk, res, mat, dist, placement);

						break;
					}
					case "US":
					{
						facData = gameMode.FactoriesUS.g_US_Factories[selected];
						res = facData.getResname();
						dist = facData.getDistance();
						placement = facData.getPlacement();

						pc.GetControlledEntity().GetTransform(mat);
						
						netComp.buildStructureServer(fk, res, mat, dist, placement);

						break;
					}
				}
				menuManager.CloseAllMenus();
				break;
			}
			case "BuildDefense":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBoxRight"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
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
				if (distance > gameMode.BUILDRANGE) break;
				
				SCR_CTI_DefenseData defData;
				ResourceName res;
				float dist;
				vector mat[4];
				vector dir;
				vector emptyPos;
				
				BaseWorld world = GetGame().GetWorld();
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				switch (fk)
				{
					case "USSR":
					{
						defData = gameMode.DefensesUSSR.g_USSR_Defenses[selected];
						res = defData.getResname();
						dist = defData.getDistance();
						
						// get player position
						pc.GetControlledEntity().GetTransform(mat);
						
						// get player direction
						dir = pc.GetControlledEntity().GetWorldTransformAxis(2);

						// calc def placement
						mat[3] = mat[3] + (dir * dist);

						// find empty pos on terrain level
						bool found = SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, mat[3], 3);
						if (found)
						{
							mat[3] = emptyPos;
						} else {
							// if not found, use the original on terrain level (temporary)
							mat[3][1] = world.GetSurfaceY(mat[3][0], mat[3][2]);
						}

						break;
					}
					case "US":
					{
						defData = gameMode.DefensesUS.g_US_Defenses[selected];
						res = defData.getResname();
						dist = defData.getDistance();
						
						// get player position
						pc.GetControlledEntity().GetTransform(mat);
						
						// get player direction
						dir = pc.GetControlledEntity().GetWorldTransformAxis(2);

						// calc def placement
						mat[3] = mat[3] + (dir * dist);

						// find empty pos on terrain level
						bool found = SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, mat[3], 3);
						if (found)
						{
							mat[3] = emptyPos;
						} else {
							// if not found, use the original on terrain level (temporary)
							mat[3][1] = world.GetSurfaceY(mat[3][0], mat[3][2]);
						}

						break;
					}
				}
				
				netComp.buildDefenseServer(res, mat);
				
				menuManager.CloseAllMenus();
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
				
				SCR_CTI_FactorySpawnComponent fscomp = SCR_CTI_FactorySpawnComponent.Cast(facts[combofacitem].FindComponent(SCR_CTI_FactorySpawnComponent));
				vector mat[4];
				fscomp.GetSpawnTransform(mat);
				
				mat[3] = mat[3] + facts[combofacitem].GetOrigin();
				
				SCR_CTI_UnitData unitData = SCR_CTI_UnitData.Cast(listboxcomp.GetItemData(selected));
				ResourceName res = unitData.getResname();
				
				EntityID groupID = pm.getGroupforCombobox().GetID();
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				netComp.factoryProductionServer(res, fk, groupID, mat);

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
				
				netComp.changeFundsServer(playerId, -value);

				RplComponent rplCompReceiver = RplComponent.Cast(listboxcomp.GetItemData(listboxcomp.GetSelectedItem()));
				RplId rplid = rplCompReceiver.Id();
				int receiverId = GetGame().GetPlayerManager().GetPlayerIdFromEntityRplId(rplid);

				netComp.changeFundsServer(receiverId, value);

				break;
			}
			
		}
		
		return true;
	}
};