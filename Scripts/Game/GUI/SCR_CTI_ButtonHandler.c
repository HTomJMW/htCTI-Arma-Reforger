class SCR_CTI_ButtonHandler : ScriptedWidgetEventHandler
{
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		w.SetColor(Color.White);
		
		return true;
	}
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		w.SetColor(Color.Orange);
		
		return true;
	}
	
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
				unflipveh.init();
				unflipveh.unflip();
				break;
			}
			case "LEAVECOM":
			{
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				int playerId = pc.GetPlayerId();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				gameMode.clearCommanderId(affiliationComp.GetAffiliatedFaction().GetFactionKey());
				
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
				}

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
				// todo cancel upgrade
				
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
						Resource resource = Resource.Load(res);
						EntitySpawnParams params = new EntitySpawnParams();
						params.TransformMode = ETransformMode.WORLD;
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
						float dist = 10; // distance from facts file
						mat[3] = mat[3] + (dir * dist); // maybe need get the new position ATL 
						params.Transform = mat;
						IEntity fact = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
						
						SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
						if (baseComp.ussrBases.Count() < 1)
						{
							baseComp.addBase(fk, mat[3], baseComp.ussrBases.Count());
							//baseComp.ussrBases[0].structures.Insert(fact);
						}
						
						
						// TODO money things
						break;
					}
					case "US":
					{
						SCR_CTI_FactoryData facData = gameMode.FactoriesUS.g_US_Factories[selected];
						ResourceName res = facData.getRes();
						Resource resource = Resource.Load(res);
						EntitySpawnParams params = new EntitySpawnParams();
						params.TransformMode = ETransformMode.WORLD;
						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						vector dir = pc.GetControlledEntity().GetWorldTransformAxis(2);
						float dist = 10; // distance from facts file
						mat[3] = mat[3] + (dir * dist);	
						params.Transform = mat;
						IEntity fact = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
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
						Resource resource = Resource.Load(res);
						EntitySpawnParams params = new EntitySpawnParams();
						params.TransformMode = ETransformMode.WORLD;
						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						vector dir = pc.GetControlledEntity().GetWorldTransformAxis(2);
						float dist = 10; // distance from facts file
						mat[3] = mat[3] + (dir * dist);	
						params.Transform = mat;
						IEntity fact = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
						break;
					}
					case "US":
					{
						SCR_CTI_DefenseData defData = gameMode.DefensesUS.g_US_Defenses[selected];
						ResourceName res = defData.getRes();
						Resource resource = Resource.Load(res);
						EntitySpawnParams params = new EntitySpawnParams();
						params.TransformMode = ETransformMode.WORLD;
						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						vector dir = pc.GetControlledEntity().GetWorldTransformAxis(2);
						float dist = 10; // distance from facts file
						mat[3] = mat[3] + (dir * dist);	
						params.Transform = mat;
						IEntity fact = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
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