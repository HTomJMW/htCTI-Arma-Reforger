class SCR_CTI_TransferResourcesMenuButtonHandler : ScriptedWidgetEventHandler
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
		}
		
		return true;
	}
};