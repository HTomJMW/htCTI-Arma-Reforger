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
			case "Exit":
			{
				auto menuManager = GetGame().GetMenuManager();
				//auto menu = ChimeraMenuPreset.CTI_GUI_MainMenu;
				//auto menu2 = ChimeraMenuPreset.CTI_GUI_BuildMenu;
				//menuManager.CloseMenuByPreset(menu);
				//menuManager.CloseMenyByPreset(menu2);
				menuManager.CloseAllMenus();
				break;
			}
			case "Back":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
				break;
			}
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

				SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
				
				cdc.setCommander(false);
				
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
				
				SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
				if (!cdc.isCommander()) break;
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
				
				SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
				if (!cdc.isCommander()) break;
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
				switch (fk)
				{
					case "USSR":
					{
						SCR_CTI_FactoryData facData = gameMode.FactoriesUSSR.g_USSR_Factories[selected];
						ResourceName res = facData.getRes();
						float dist = facData.getDis();
						int placement = facData.getPla();

						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						
						SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
						netComp.buildStructureServer(fk, res, mat, dist, placement);

						break;
					}
					case "US":
					{
						SCR_CTI_FactoryData facData = gameMode.FactoriesUS.g_US_Factories[selected];
						ResourceName res = facData.getRes();
						float dist = facData.getDis();
						int placement = facData.getPla();

						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						
						SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
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
				switch (fk)
				{
					case "USSR":
					{
						SCR_CTI_DefenseData defData = gameMode.DefensesUSSR.g_USSR_Defenses[selected];
						ResourceName res = defData.getRes();
						float dist = defData.getDis();
						
						// get player position
						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						
						// get player direction
						vector dir = pc.GetControlledEntity().GetWorldTransformAxis(2);

						// calc def placement
						mat[3] = mat[3] + (dir * dist);

						// find empty pos on terrain level
						vector emptyPos;
						bool found = SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, mat[3], 3);
						if (found)
						{
							mat[3] = emptyPos;
						} else {
							// if not found, use the original on terrain level (temporary)
							BaseWorld world = GetGame().GetWorld();
							mat[3][1] = world.GetSurfaceY(mat[3][0], mat[3][2]);
						}
						
						SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
						netComp.buildDefenseServer(res, mat);

						break;
					}
					case "US":
					{
						SCR_CTI_DefenseData defData = gameMode.DefensesUS.g_US_Defenses[selected];
						ResourceName res = defData.getRes();
						float dist = defData.getDis();
						
						// get player position
						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						
						// get player direction
						vector dir = pc.GetControlledEntity().GetWorldTransformAxis(2);

						// calc def placement
						mat[3] = mat[3] + (dir * dist);

						// find empty pos on terrain level
						vector emptyPos;
						bool found = SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, mat[3], 3);
						if (found)
						{
							mat[3] = emptyPos;
						} else {
							// if not found, use the original on terrain level (temporary)
							BaseWorld world = GetGame().GetWorld();
							mat[3][1] = world.GetSurfaceY(mat[3][0], mat[3][2]);
						}
						
						SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
						netComp.buildDefenseServer(res, mat);

						break;
					}
				}
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
				ResourceName res = unitData.getRes();
				
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
				PlayerController pc = GetGame().GetPlayerController();
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				
				int senderId = pc.GetPlayerId();
				
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				SliderWidget slider = SliderWidget.Cast(root.FindAnyWidget("Slider"));
				int value = slider.GetCurrent();
				
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected < 0) break;
				
				AIGroup selectedgorup = AIGroup.Cast(listboxcomp.GetItemData(selected));
				int receiverId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(selectedgorup.GetLeaderEntity());
				
				netComp.transferResourcesServer(senderId, receiverId, value);

				break;
			}
			
		}
		
		return true;
	}
};