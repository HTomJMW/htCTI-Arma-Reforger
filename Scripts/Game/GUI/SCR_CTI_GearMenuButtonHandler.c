class SCR_CTI_GearMenuButtonHandler : ScriptedWidgetEventHandler
{
	//------------------------------------------------------------------------------------------------
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (w.GetName() == "Buy" || w.GetName() == "Exit") w.SetColor(Color.White);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (w.GetName() == "Buy" || w.GetName() == "Exit") w.SetColor(Color.Orange);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		auto menuManager = GetGame().GetMenuManager();
		SCR_CTI_GearMenu gearMenu = SCR_CTI_GearMenu.Cast(menuManager.GetTopMenu());
		
		Widget root = gearMenu.GetRootWidget();
		OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
		SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
		int selected = listboxcomp.GetSelectedItem();
		SCR_CTI_GearData gearData;
		if (selected != -1) gearData = SCR_CTI_GearData.Cast(listboxcomp.GetItemData(selected));
		
		switch (w.GetName())
		{
			case "PreViewHelmet":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewUpperItem":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewBackPack":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewJacket":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewVest":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewTrousers":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewBoots":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewBottomItem":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewItem":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewPrimary1":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewPrimary2":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewSecondary":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewGrenade1":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "PreViewGrenade2":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT0":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT1":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT2":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT3":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT4":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT5":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT6":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT7":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT8":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT9":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT10":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT11":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA0":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA1":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA2":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA3":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA4":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA5":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA6":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA7":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA8":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA9":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA10":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA11":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ0":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ1":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ2":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ3":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ4":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ5":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ6":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ7":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ8":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ9":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ10":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ11":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB0":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB1":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB2":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB3":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB4":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB5":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB6":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB7":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB8":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB9":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB10":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB11":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV0":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV1":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV2":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV3":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV4":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV5":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV6":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV7":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV8":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV9":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV10":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV11":
			{
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "Buy":
			{
				gearMenu.clean();
				gearMenu.buy();
				
				break;
			}
			case "Exit":
			{	
				menuManager.CloseAllMenus();
				
				break;
			}
		}
		
		return true;
	}
};