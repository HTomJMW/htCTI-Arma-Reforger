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
			case "EXITBUTTON":
			{
				auto menuManager = GetGame().GetMenuManager();
				//auto menu = ChimeraMenuPreset.CTI_GUI_MainMenu;
				//auto menu2 = ChimeraMenuPreset.CTI_GUI_BuildMenu;
				//menuManager.CloseMenuByPreset(menu);
				//menuManager.CloseMenyByPreset(menu2);
				menuManager.CloseAllMenus();
				break;
			}
			case "BACKBUTTON":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
				break;
			}
			case "BUILD":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_BuildMenu);
				break;
			}
			case "UNFLIPNEARESTVEHICLE":
			{
				SCR_CTI_UnflipNearestVehicle unflipveh = new SCR_CTI_UnflipNearestVehicle;
				unflipveh.unflip();
				break;
			}
			case "LEAVECOM":
			{
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				netComp.clearCommanderIdRpl(affiliationComp.GetAffiliatedFaction().GetFactionKey());
				
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
					clientData.setCommander(false);
					
					if (affiliationComp.GetAffiliatedFaction().GetFactionKey() == "USSR")
					{
						clientData.changeFunds(-gameMode.getCommanderFunds("USSR"));
					} else {
						clientData.changeFunds(-gameMode.getCommanderFunds("US"));
					}
				}
				
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();

				break;
			}
			case "UPGRADES":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_UpgradeMenu);
				
				break;
			}
			case "STARTUPGRADE":
			{
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
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
				if (!clientData.isCommander()) break;
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
				
				netComp.StartUpgradeServer(fk, selected);
				
				menuManager.CloseAllMenus();
				
				break;
			}
			case "CANCELUPGRADE":
			{
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
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
				if (!clientData.isCommander()) break;
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();

				netComp.StopUpgradeServer(fk);

				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				
				break;
			}
			case "BUILDSTRUCTURE":
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
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey fk = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				switch (fk)
				{
					case "USSR":
					{
						SCR_CTI_FactoryData facData = gameMode.FactoriesUSSR.g_USSR_Factories[selected];
						ResourceName res = facData.getRes();
						float dist = facData.getDis();

						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						
						//CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
						//vector posInWorld = vector.Zero;
						//if (cam)
						//{
						//	cam.GetCursorTargetWithPosition(posInWorld);
						//	mat[3] = posInWorld;
						//}
						
						vector dir = pc.GetControlledEntity().GetWorldTransformAxis(2);
						dir.Normalize();
						
						mat[3] = mat[3] + (dir * dist);
						BaseWorld world = GetGame().GetWorld();
						mat[3][1] = world.GetSurfaceY(mat[3][0], mat[3][2]);

						SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
						netComp.buildStructureServer(fk, res, mat);

						// TODO money things
						break;
					}
					case "US":
					{
						SCR_CTI_FactoryData facData = gameMode.FactoriesUS.g_US_Factories[selected];
						ResourceName res = facData.getRes();
						float dist = facData.getDis();

						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						
						//CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
						//vector posInWorld = vector.Zero;
						//if (cam)
						//{
						//	cam.GetCursorTargetWithPosition(posInWorld);
						//	mat[3] = posInWorld;
						//}
						
						vector dir = pc.GetControlledEntity().GetWorldTransformAxis(2);
						dir.Normalize();
						
						mat[3] = mat[3] + (dir * dist);
						BaseWorld world = GetGame().GetWorld();
						mat[3][1] = world.GetSurfaceY(mat[3][0], mat[3][2]);

						SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
						netComp.buildStructureServer(fk, res, mat);

						// TODO money things
						break;
					}
				}
				menuManager.CloseAllMenus();
				break;
			}
			case "BUILDDEFENSE":
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
						dir.Normalize();

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
						dir.Normalize();

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
		}
		
		return true;
	}
};