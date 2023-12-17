class SCR_CTI_BaseManagementMenuButtonHandler : ScriptedWidgetEventHandler
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
			case "Demolish":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey factionkey = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				RplComponent objectRplComp = RplComponent.Cast(listboxcomp.GetItemData(selected));
				
				IEntity object = objectRplComp.GetEntity();
				
				if (!object || object.Type() == SCR_ChimeraCharacter || listboxcomp.GetItemCount() == 0) break;
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				
				listboxcomp.RemoveItem(selected); // For release reference of stored RplComponent
				if (netComp) netComp.deleteObjectServer(factionkey, objectRplComp.Id());

				break;
			}
			case "Disband":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey factionkey = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				RplComponent workerRplComp = RplComponent.Cast(listboxcomp.GetItemData(selected));

				IEntity worker = workerRplComp.GetEntity();
				
				if (!worker || worker.Type() != SCR_ChimeraCharacter || listboxcomp.GetItemCount() == 0) break;

				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));

				listboxcomp.RemoveItem(selected); // For release reference of stored RplComponent
				if (netComp) netComp.disbandWorkerServer(factionkey, workerRplComp.Id());

				break;
			}
		}
		
		return true;
	}
};