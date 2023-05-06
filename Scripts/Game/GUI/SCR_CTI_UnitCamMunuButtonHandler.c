class SCR_CTI_UnitCamMenuButtonHandler : ScriptedWidgetEventHandler
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
			case "IronSight":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				SCR_CTI_UnitCamMenu ucm = SCR_CTI_UnitCamMenu.Cast(openedMenu);
				
				ucm.setIronSight();

				break;
			}
			case "Internal":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				SCR_CTI_UnitCamMenu ucm = SCR_CTI_UnitCamMenu.Cast(openedMenu);
				
				ucm.setInternal();
	
				break;
			}
			case "External":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				SCR_CTI_UnitCamMenu ucm = SCR_CTI_UnitCamMenu.Cast(openedMenu);
				
				ucm.setExternal();

				break;
			}
			case "Unflip":
			{
				// todo check team members
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();
				SCR_CompartmentAccessComponent cac = SCR_CompartmentAccessComponent.Cast(player.FindComponent(SCR_CompartmentAccessComponent));
				IEntity vehicle = cac.GetVehicle();
				if (vehicle)
				{
					RplComponent vehRplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));
					RplId rplid = vehRplComp.Id();

					SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
					netComp.unflipNearestVehicleServer(rplid);
				}
				
				break;
			}
			case "Disband":
			{
				
				
				break;
			}
			case "Info":
			{
				
				
				break;
			}
			case "NormalNV":
			{
				
				
				break;
			}
		}
		
		return true;
	}
};