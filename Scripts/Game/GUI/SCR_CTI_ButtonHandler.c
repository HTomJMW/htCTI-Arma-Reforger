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
						SCR_CTI_FactoryData facData = gameMode.FactorysUSSR.g_USSR_Factorys[selected];
						ResourceName res = facData.getRes();
						Resource resource = Resource.Load(res);
						EntitySpawnParams params = new EntitySpawnParams();
						params.TransformMode = ETransformMode.WORLD;
						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
						vector posInWorld = vector.Zero;
						if (cam)
						{
							cam.GetCursorTargetWithPosition(posInWorld);
							mat[3] = posInWorld;
						}
						params.Transform = mat;
						IEntity fact = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
						break;
					}
					case "US":
					{
						SCR_CTI_FactoryData facData = gameMode.FactorysUS.g_US_Factorys[selected];
						ResourceName res = facData.getRes();
						Resource resource = Resource.Load(res);
						EntitySpawnParams params = new EntitySpawnParams();
						params.TransformMode = ETransformMode.WORLD;
						vector mat[4];
						pc.GetControlledEntity().GetTransform(mat);
						CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
						vector posInWorld = vector.Zero;
						if (cam)
						{
							cam.GetCursorTargetWithPosition(posInWorld);
							mat[3] = posInWorld;
						}
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
						CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
						vector posInWorld = vector.Zero;
						if (cam)
						{
							cam.GetCursorTargetWithPosition(posInWorld);
							mat[3] = posInWorld;
						}
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
						CameraBase cam = GetGame().GetCameraManager().CurrentCamera();
						vector posInWorld = vector.Zero;
						if (cam)
						{
							cam.GetCursorTargetWithPosition(posInWorld);
							mat[3] = posInWorld;
						}
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