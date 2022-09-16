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
			case "BUILD":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_BuildMenu);
				break;
			}
		}
		
		return true;
	}
};