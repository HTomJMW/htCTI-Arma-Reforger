class SCR_CTI_OnlineHelpButtonHandler : ScriptedWidgetEventHandler
{
	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		auto menuManager = GetGame().GetMenuManager();
		MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
		Widget root = openedMenu.GetRootWidget();
		RichTextWidget descRTW = RichTextWidget.Cast(root.FindAnyWidget("Description"));
		
		switch (w.GetName())
		{
			case "WelcomeScreen":
			{
				string desc = "Welcome in Arma Reforger HTCTI mission\n\nThe Mission:\n\nThis mission based on original MF|CR|BE and BECTI Zerty mod CTI missions, made by [H]Tom.\n\nObjective:\n\nTake towns, destroy enemy facilities and MHQ.\nCommander setting the team strategy, build bases, run upgrades.\nWith more controlled towns the team eran more money.";
				descRTW.SetText(desc);
				
				break;
			}
			case "Base":
			{
				string desc = "Base:\n\nOn Bases, you can buy units, weapons and equipment. You can use factories and depos.";
				descRTW.SetText(desc);
				
				break;
			}
			case "Commander":
			{
				string desc = "Commander:\n\nThe Commander sets up strategy, build bases, set Priority and starts tech upgrades.\nThere can only be one of them per faction and only he can use MHQ.";
				descRTW.SetText(desc);
				
				break;
			}
			case "Economy":
			{
				string desc = "Economy:\n\nCapture towns for more money. For Economy Win, your faction need hold more than 75% of towns.";
				descRTW.SetText(desc);
				
				break;
			}
			case "Map":
			{
				string desc = "The Map:\n\nThe map contains all of the information what you need.\nFirst of all you need to be aware of the colors.\n\n- US (West) is identified by the blue color.\n- USSR (East) is identified by red color.\n- FIA (Resistance) is identified by green color.";
				descRTW.SetText(desc);
				
				break;
			}
			case "Credits":
			{
				string desc = "Credits:\n\nMission by [H]Tom\n[2022-2023]";
				descRTW.SetText(desc);
				
				break;
			}
		}
		
		return true;
	}
};