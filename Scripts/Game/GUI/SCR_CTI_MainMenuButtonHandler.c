class SCR_CTI_MainMenuButtonHandler : ScriptedWidgetEventHandler
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
				netComp.updateClientDataCommanderServer(playerId);
				
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
			case "VideoSettingsButton":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_VideoSettingsMenu);

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