class SCR_CTI_GearMenuButtonHandler : ScriptedWidgetEventHandler
{
	//------------------------------------------------------------------------------------------------
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (w.Type() == ButtonWidget) w.SetColor(Color.White);

		switch(w.GetName())
		{
			case "Rifles":
			{
				w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
			case "Launchers":
			{
				w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
			case "Pistols":
			{
				w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
			case "Accessories":
			{
				w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
			case "Ammos":
			{
				w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
			case "Items":
			{
				w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
			case "Uniforms":
			{
				w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
			case "Templates":
			{
				//w.GetChildren().SetColor(SCR_CTI_Constants.CTI_ORANGE);
				break;
			}
		}
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (w.Type() == ButtonWidget) w.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		
		switch(w.GetName())
		{
			case "Rifles":
			{
				w.GetChildren().SetColor(Color.White);
				break;
			}
			case "Launchers":
			{
				w.GetChildren().SetColor(Color.White);
				break;
			}
			case "Pistols":
			{
				w.GetChildren().SetColor(Color.White);
				break;
			}
			case "Accessories":
			{
				w.GetChildren().SetColor(Color.White);
				break;
			}
			case "Ammos":
			{
				w.GetChildren().SetColor(Color.White);
				break;
			}
			case "Items":
			{
				w.GetChildren().SetColor(Color.White);
				break;
			}
			case "Uniforms":
			{
				w.GetChildren().SetColor(Color.White);
				break;
			}
			case "Templates":
			{
				//w.GetChildren().SetColor(Color.White);
				break;
			}
		}
		
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
			case "Rifles":
			{
				listboxcomp.SetItemSelected(listboxcomp.GetSelectedItem(), false);
				gearData = null;
				
				for (int i = listboxcomp.GetItemCount() - 1; i >= 0; i--)
				{
					listboxcomp.RemoveItem(i);
				}

				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				switch (affiliationComp.GetAffiliatedFaction().GetFactionKey())
				{
					case "USSR":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
						{
							gd = gameMode.GearUSSR.g_USSR_Gear[i];
							if (gd.getCategory() == "Rifle")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}
					
					case "US":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
						{
							gd = gameMode.GearUS.g_US_Gear[i];
							if (gd.getCategory() == "Rifle")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}		
				}
				
				break;
			}
			case "Launchers":
			{
				listboxcomp.SetItemSelected(listboxcomp.GetSelectedItem(), false);
				gearData = null;
				
				for (int i = listboxcomp.GetItemCount() - 1; i >= 0; i--)
				{
					listboxcomp.RemoveItem(i);
				}

				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				switch (affiliationComp.GetAffiliatedFaction().GetFactionKey())
				{
					case "USSR":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
						{
							gd = gameMode.GearUSSR.g_USSR_Gear[i];
							if (gd.getCategory() == "Launcher")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}
					
					case "US":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
						{
							gd = gameMode.GearUS.g_US_Gear[i];
							if (gd.getCategory() == "Launcher")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}		
				}
				
				break;
			}
			case "Pistols":
			{
				listboxcomp.SetItemSelected(listboxcomp.GetSelectedItem(), false);
				gearData = null;
				
				for (int i = listboxcomp.GetItemCount() - 1; i >= 0; i--)
				{
					listboxcomp.RemoveItem(i);
				}

				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				switch (affiliationComp.GetAffiliatedFaction().GetFactionKey())
				{
					case "USSR":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
						{
							gd = gameMode.GearUSSR.g_USSR_Gear[i];
							if (gd.getCategory() == "Pistol")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}
					
					case "US":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
						{
							gd = gameMode.GearUS.g_US_Gear[i];
							if (gd.getCategory() == "Pistol")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}		
				}
				
				break;
			}
			case "Accessories":
			{
				listboxcomp.SetItemSelected(listboxcomp.GetSelectedItem(), false);
				gearData = null;
				
				for (int i = listboxcomp.GetItemCount() - 1; i >= 0; i--)
				{
					listboxcomp.RemoveItem(i);
				}

				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				switch (affiliationComp.GetAffiliatedFaction().GetFactionKey())
				{
					case "USSR":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
						{
							gd = gameMode.GearUSSR.g_USSR_Gear[i];
							if (gd.getCategory() == "Accessory")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}
					
					case "US":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
						{
							gd = gameMode.GearUS.g_US_Gear[i];
							if (gd.getCategory() == "Accessory")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}		
				}
				
				break;
			}
			case "Ammos":
			{
				listboxcomp.SetItemSelected(listboxcomp.GetSelectedItem(), false);
				gearData = null;
				
				for (int i = listboxcomp.GetItemCount() - 1; i >= 0; i--)
				{
					listboxcomp.RemoveItem(i);
				}

				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				switch (affiliationComp.GetAffiliatedFaction().GetFactionKey())
				{
					case "USSR":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
						{
							gd = gameMode.GearUSSR.g_USSR_Gear[i];
							if (gd.getCategory() == "Ammo")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}
					
					case "US":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
						{
							gd = gameMode.GearUS.g_US_Gear[i];
							if (gd.getCategory() == "Ammo")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}		
				}
				
				break;
			}
			case "Items":
			{
				listboxcomp.SetItemSelected(listboxcomp.GetSelectedItem(), false);
				gearData = null;
				
				for (int i = listboxcomp.GetItemCount() - 1; i >= 0; i--)
				{
					listboxcomp.RemoveItem(i);
				}

				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				switch (affiliationComp.GetAffiliatedFaction().GetFactionKey())
				{
					case "USSR":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
						{
							gd = gameMode.GearUSSR.g_USSR_Gear[i];
							if (gd.getCategory() == "Item")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}
					
					case "US":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
						{
							gd = gameMode.GearUS.g_US_Gear[i];
							if (gd.getCategory() == "Item")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}		
				}
				
				break;
			}
			case "Uniforms":
			{
				listboxcomp.SetItemSelected(listboxcomp.GetSelectedItem(), false);
				gearData = null;
				
				for (int i = listboxcomp.GetItemCount() - 1; i >= 0; i--)
				{
					listboxcomp.RemoveItem(i);
				}

				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				
				switch (affiliationComp.GetAffiliatedFaction().GetFactionKey())
				{
					case "USSR":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
						{
							gd = gameMode.GearUSSR.g_USSR_Gear[i];
							if (gd.getCategory() == "Uniform")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}
					
					case "US":
					{
						SCR_CTI_GearData gd;
						for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
						{
							gd = gameMode.GearUS.g_US_Gear[i];
							if (gd.getCategory() == "Uniform")
							{
								listboxcomp.AddItem(gd.getPrice().ToString() + "$ " + gd.getName(), gd);
							}
						}
						break;
					}		
				}
				
				break;
			}
			case "Templates":
			{
				// disabled
				break;
			}
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
			case "PreViewArmoredVest":
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
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT1":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT2":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT3":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT4":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT5":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT6":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT7":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT8":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT9":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT10":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVT11":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA0":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA1":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA2":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA3":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA4":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA5":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA6":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}case "ItemPVA7":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA8":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA9":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA10":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVA11":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ0":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ1":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ2":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ3":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ4":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ5":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ6":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);

				break;
			}
			case "ItemPVJ7":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);

				break;
			}
			case "ItemPVJ8":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ9":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ10":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVJ11":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB0":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB1":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB2":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB3":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB4":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB5":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB6":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB7":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB8":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB9":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB10":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVB11":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV0":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV1":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV2":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV3":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV4":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV5":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV6":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV7":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV8":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV9":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV10":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "ItemPVV11":
			{
				if (button == 0 && gearData) gearMenu.tryAddItem(w, gearData);
				if (button == 1) gearMenu.removeItem(w);
				
				break;
			}
			case "Buy":
			{
				gearMenu.startproc();
				
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