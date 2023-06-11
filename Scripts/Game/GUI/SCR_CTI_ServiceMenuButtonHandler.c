class SCR_CTI_ServiceMenuButtonHandler : ScriptedWidgetEventHandler
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
			case "Repair":
			{
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				
				RplComponent rplComp = RplComponent.Cast(listboxcomp.GetItemData(selected));
				RplId rplid = rplComp.Id();

				IEntity vehicle = rplComp.GetEntity();
				SCR_VehicleFactionAffiliationComponent vfaffComp = SCR_VehicleFactionAffiliationComponent.Cast(vehicle.FindComponent(SCR_VehicleFactionAffiliationComponent));
				FactionKey factionkey = vfaffComp.GetDefaultAffiliatedFaction().GetFactionKey();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				int index = -1;
				SCR_CTI_UnitData unitData;

				switch (factionkey)
				{
					case "USSR":
					{
						index = gameMode.UnitsUSSR.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsUSSR.g_USSR_Units[index];
						break;
					}
					case "US":
					{
						index = gameMode.UnitsUS.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsUS.g_US_Units[index];
						break;
					}
					case "FIA":
					{
						index = gameMode.UnitsFIA.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsFIA.g_FIA_Units[index];
						break;
					}			
				}

				int repairTime = 20;
				int repairCost = 1000;
				if (unitData)
				{
					repairTime = Math.Round(unitData.getBuildtime() * SCR_CTI_Constants.REPAIRMULTIPLIER);
					repairCost = Math.Round(unitData.getPrice() * SCR_CTI_Constants.REPAIRMULTIPLIER);
				}

				int funds = 0;
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData)
				{
					if (clientData.isCommander())
					{
						FactionKey playerFactionkey = GetGame().GetFactionManager().GetFactionByIndex(clientData.getFactionIndex()).GetFactionKey();
						funds = gameMode.getCommanderFunds(playerFactionkey);
						if (funds < repairCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeCommanderFundsServer(playerFactionkey, -repairCost);
						}
					} else {
						funds = clientData.getFunds();
						if (funds < repairCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeFundsServer(pc.GetPlayerId(), -repairCost);
						}
					}
				}
			
				SCR_HintManagerComponent.ShowCustomHint("Repair vehicle in " + repairTime.ToString() + "s", "Information", 5);
				netComp.repairVehicleServer(pc.GetPlayerId(), rplid, repairTime);

				break;
			}
			case "Rearm":
			{
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				
				RplComponent rplComp = RplComponent.Cast(listboxcomp.GetItemData(selected));
				RplId rplid = rplComp.Id();
				
				IEntity vehicle = rplComp.GetEntity();
				SCR_VehicleFactionAffiliationComponent vfaffComp = SCR_VehicleFactionAffiliationComponent.Cast(vehicle.FindComponent(SCR_VehicleFactionAffiliationComponent));
				FactionKey factionkey = vfaffComp.GetDefaultAffiliatedFaction().GetFactionKey();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				int index = -1;
				SCR_CTI_UnitData unitData;

				switch (factionkey)
				{
					case "USSR":
					{
						index = gameMode.UnitsUSSR.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsUSSR.g_USSR_Units[index];
						break;
					}
					case "US":
					{
						index = gameMode.UnitsUS.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsUS.g_US_Units[index];
						break;
					}
					case "FIA":
					{
						index = gameMode.UnitsFIA.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsFIA.g_FIA_Units[index];
						break;
					}			
				}

				int rearmTime = 20;
				int rearmCost = 1000;
				if (unitData)
				{
					rearmTime = Math.Round(unitData.getBuildtime() * SCR_CTI_Constants.REARMMULTIPLIER);
					rearmCost = Math.Round(unitData.getPrice() * SCR_CTI_Constants.REARMMULTIPLIER);
				}

				int funds = 0;
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData)
				{
					if (clientData.isCommander())
					{
						FactionKey playerFactionkey = GetGame().GetFactionManager().GetFactionByIndex(clientData.getFactionIndex()).GetFactionKey();
						funds = gameMode.getCommanderFunds(playerFactionkey);
						if (funds < rearmCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeCommanderFundsServer(playerFactionkey, -rearmCost);
						}
					} else {
						funds = clientData.getFunds();
						if (funds < rearmCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeFundsServer(pc.GetPlayerId(), -rearmCost);
						}
					}
				}
			
				SCR_HintManagerComponent.ShowCustomHint("Rearm vehicle in " + rearmTime.ToString() + "s", "Information", 5);
				netComp.rearmVehicleServer(pc.GetPlayerId(), rplid, rearmTime);
				
				break;
			}
			case "Refuel":
			{
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();

				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				
				RplComponent rplComp = RplComponent.Cast(listboxcomp.GetItemData(selected));
				RplId rplid = rplComp.Id();

				IEntity vehicle = rplComp.GetEntity();
				SCR_VehicleFactionAffiliationComponent vfaffComp = SCR_VehicleFactionAffiliationComponent.Cast(vehicle.FindComponent(SCR_VehicleFactionAffiliationComponent));
				FactionKey factionkey = vfaffComp.GetDefaultAffiliatedFaction().GetFactionKey();
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				int index = -1;
				SCR_CTI_UnitData unitData;

				switch (factionkey)
				{
					case "USSR":
					{
						index = gameMode.UnitsUSSR.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsUSSR.g_USSR_Units[index];
						break;
					}
					case "US":
					{
						index = gameMode.UnitsUS.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsUS.g_US_Units[index];
						break;
					}
					case "FIA":
					{
						index = gameMode.UnitsFIA.findIndexFromResourcename(vehicle.GetPrefabData().GetPrefabName());
						if (index > -1) unitData = gameMode.UnitsFIA.g_FIA_Units[index];
						break;
					}			
				}

				int refuelTime = 20;
				int refuelCost = 1000;
				if (unitData)
				{
					refuelTime = Math.Round(unitData.getBuildtime() * SCR_CTI_Constants.REFUELMULTIPLIER);
					refuelCost = Math.Round(unitData.getPrice() * SCR_CTI_Constants.REFUELMULTIPLIER);
				}

				int funds = 0;
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData)
				{
					if (clientData.isCommander())
					{
						FactionKey playerFactionkey = GetGame().GetFactionManager().GetFactionByIndex(clientData.getFactionIndex()).GetFactionKey();
						funds = gameMode.getCommanderFunds(playerFactionkey);
						if (funds < refuelCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeCommanderFundsServer(playerFactionkey, -refuelCost);
						}
					} else {
						funds = clientData.getFunds();
						if (funds < refuelCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeFundsServer(pc.GetPlayerId(), -refuelCost);
						}
					}
				}
			
				SCR_HintManagerComponent.ShowCustomHint("Refuel vehicle in " + refuelTime.ToString() + "s", "Information", 5);
				netComp.refuelVehicleServer(pc.GetPlayerId(), rplid, refuelTime);

				break;
			}
			case "Heal":
			{
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();

				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				
				RplComponent rplComp = RplComponent.Cast(listboxcomp.GetItemData(selected));
				RplId rplid = rplComp.Id();

				IEntity vehicle = rplComp.GetEntity();

				int healTime = 20;
				int healCost = 200;
				
				SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(vehicle.FindComponent(SCR_BaseCompartmentManagerComponent));
				array<IEntity> occupants = {};
				bcmc.GetOccupants(occupants);
				
				healCost = occupants.Count() * 50;
				
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());

				int funds = 0;
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData)
				{
					if (clientData.isCommander())
					{
						FactionKey playerFactionkey = GetGame().GetFactionManager().GetFactionByIndex(clientData.getFactionIndex()).GetFactionKey();
						funds = gameMode.getCommanderFunds(playerFactionkey);
						if (funds < healCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeCommanderFundsServer(playerFactionkey, -healCost);
						}
					} else {
						funds = clientData.getFunds();
						if (funds < healCost)
						{
							SCR_HintManagerComponent.ShowCustomHint("Not enough funds!", "Information", 5);
							break;
						} else {
							netComp.changeFundsServer(pc.GetPlayerId(), -healCost);
						}
					}
				}
			
				SCR_HintManagerComponent.ShowCustomHint("Heal vehicle crew in " + healTime.ToString() + "s", "Information", 5);
				netComp.healVehicleCrewServer(pc.GetPlayerId(), rplid, healTime);

				break;
			}
		}
		
		return true;
	}
};