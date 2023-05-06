class SCR_CTI_PurchaseMenuButtonHandler : ScriptedWidgetEventHandler
{
	protected bool infSelected = false;
	protected bool lightSelected = false;
	protected bool heavySelected = false;
	protected bool airSelected = false;
	protected bool repSelected = false;
	protected bool ammoSelected = false;
	protected bool navalSelected = false;
	protected bool flagSelected = false;
	
	protected bool driverSelected = false;
	protected bool gunnerSelected = false;
	protected bool commanderSelected = false;
	protected bool crewSelected = false;
	protected bool lockSelected = true; // default lock - maybe not need for AIs
	protected bool unlockSelected = false;
	
	//------------------------------------------------------------------------------------------------
	string getSelectedFactoryTypeIcon()
	{
		string selected = "None";
		
		switch (true)
		{
			case infSelected: selected = "Barracks"; break;
			case lightSelected: selected = "Light Factory"; break;
			case heavySelected: selected = "Heavy Factory"; break;
			case airSelected: selected = "Air Factory"; break;
			case repSelected: selected = "Repair Depot"; break;
			case ammoSelected: selected = "Ammo Depot"; break;
			case navalSelected: selected = "Naval"; break;
			case flagSelected: selected = "Flag"; break;
		}
		
		return selected;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnUpdate(Widget w)
	{
		if (w.GetName() == "ButtonLock") changeColor(w, lockSelected);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		ButtonWidget bw = ButtonWidget.Cast(w);
		
		switch (w.GetName())
		{
			case "ButtonInf":
			{
				infSelected = true;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColorAllType(w);

				break;
			}
			case "ButtonLight":
			{
				infSelected = false;
				lightSelected = true;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColorAllType(w);

				break;
			}
			case "ButtonHeavy":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = true;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColorAllType(w);
			
				break;
			}
			case "ButtonAir":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = true;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColorAllType(w);
			
				break;
			}
			case "ButtonRep":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = true;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColorAllType(w);
				
				break;
			}
			case "ButtonAmmo":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = true;
				navalSelected = false;
				flagSelected = false;
				
				changeColorAllType(w);
			
				break;
			}
			case "ButtonNaval":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = true;
				flagSelected = false;
				
				changeColorAllType(w);
			
				break;
			}
			case "ButtonFlag":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = true;
				
				changeColorAllType(w);
			
				break;
			}
			case "ButtonDriver":
			{
				if (driverSelected)
				{
					driverSelected = false;
				} else {
					driverSelected = true;
				}
				changeColor(w, driverSelected);

				break;
			}
			case "ButtonGunner":
			{
				if (gunnerSelected)
				{
					gunnerSelected = false;
				} else {
					gunnerSelected = true;
				}
				changeColor(w, gunnerSelected);
			
				break;
			}
			case "ButtonCommander":
			{
				if (commanderSelected)
				{
					commanderSelected = false;
				} else {
					commanderSelected = true;
				}
				changeColor(w, commanderSelected);
			
				break;
			}
			case "ButtonCrew":
			{
				if (crewSelected)
				{
					crewSelected = false;
				} else {
					crewSelected = true;
				}
				changeColor(w, crewSelected);
			
				break;
			}
			case "ButtonLock":
			{
				lockSelected = true;
				unlockSelected = false;
				
				changeColor(w, lockSelected);

				ButtonWidget unlock = ButtonWidget.Cast(w.GetParent().FindAnyWidget("ButtonUnlock"));
				
				changeColor(unlock, unlockSelected);

				break;
			}
			case "ButtonUnlock":
			{
				unlockSelected = true;
				lockSelected = false;

				changeColor(w, unlockSelected);
				
				ButtonWidget lock = ButtonWidget.Cast(w.GetParent().FindAnyWidget("ButtonLock"));
				
				changeColor(lock, lockSelected);

				break;
			}
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (w.GetName() == "Purchase") w.SetColor(Color.White);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (w.GetName() == "Purchase") w.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		switch (w.GetName())
		{
			case "Purchase":
			{
				auto menuManager = GetGame().GetMenuManager();
				MenuBase openedMenu = MenuBase.Cast(menuManager.GetTopMenu());
				Widget root = openedMenu.GetRootWidget();
				OverlayWidget listbox = OverlayWidget.Cast(root.FindAnyWidget("ListBox"));
				SCR_ListBoxComponent listboxcomp = SCR_ListBoxComponent.Cast(listbox.FindHandler(SCR_ListBoxComponent));
				int selected = listboxcomp.GetSelectedItem();
				if (selected == -1) break;
				SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
				PlayerController pc = GetGame().GetPlayerController();
				FactionAffiliationComponent affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
				FactionKey factionkey = affiliationComp.GetAffiliatedFaction().GetFactionKey();
				
				XComboBoxWidget comboboxfactory = XComboBoxWidget.Cast(root.FindAnyWidget("XComboBoxFactory"));
				int combofacitem = comboboxfactory.GetCurrentItem();
				
				SCR_CTI_PurchaseMenu pm = SCR_CTI_PurchaseMenu.Cast(openedMenu);
				array<IEntity> facts = pm.getSortedFactoriesForCombobox();
				
				RplComponent factRplComp = RplComponent.Cast(facts[combofacitem].FindComponent(RplComponent));
				RplId factRplid = factRplComp.Id();

				SCR_CTI_FactoryData factData;
				int factIndex = -1;
				switch(factionkey)
				{
					case "USSR":
					{
						factIndex = gameMode.FactoriesUSSR.findIndexFromResourcename(facts[combofacitem].GetPrefabData().GetPrefabName());
						factData = gameMode.FactoriesUSSR.g_USSR_Factories[factIndex];
						break;
					}
					case "US":
					{
						factIndex = gameMode.FactoriesUS.findIndexFromResourcename(facts[combofacitem].GetPrefabData().GetPrefabName());
						factData = gameMode.FactoriesUS.g_US_Factories[factIndex];
						break;
					}
				}

				float dist = factData.getDistance();
				float placement = factData.getPlacement();
				vector dir = facts[combofacitem].GetTransformAxis(2);

				vector mat[4];
				facts[combofacitem].GetTransform(mat);

				vector angles = mat[2].VectorToAngles();
				angles[0] = angles[0] + placement;
				mat[2] = angles.AnglesToVector();

				if (placement == 0) mat[3] = mat[3] - (dir * dist);
				if (placement == 180) mat[3] = mat[3] + (dir * dist);
				mat[3][1] = GetGame().GetWorld().GetSurfaceY(mat[3][0], mat[3][2]);
				
				vector emptyPos;
				SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, mat[3], 20, 4, 3);
				mat[3] = emptyPos;

				SCR_CTI_UnitData unitData = SCR_CTI_UnitData.Cast(listboxcomp.GetItemData(selected));
				ResourceName res = unitData.getResname();
				int buildTime = unitData.getBuildtime();
				int cost = unitData.getPrice();

				int funds = 0;
				SCR_CTI_ClientData clientData = gameMode.getClientData(pc.GetPlayerId());
				if (clientData && clientData.isCommander())
				{
					funds = gameMode.getCommanderFunds(factionkey);
				} else {
					funds = clientData.getFunds();
				}

				if (funds < cost) break; // TODO make warning?

				EntityID groupID = pm.getGroupforCombobox().GetID();
				
				SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
				netComp.factoryProductionServer(res, factionkey, groupID, factRplid, mat, pc.GetPlayerId(), buildTime);

				break;
			}
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	protected void changeColor(Widget w, bool selected)
	{
		ImageWidget children = ImageWidget.Cast(w.GetChildren());
		
		if (selected)
		{
			w.SetColor(Color.White);
			children.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		} else {
			w.SetColor(SCR_CTI_Constants.CTI_ORANGE);
			children.SetColor(Color.White);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void changeColorAllType(Widget w)
	{
		Widget parent = w.GetParent();
		
		ButtonWidget inf = ButtonWidget.Cast(parent.FindAnyWidget("ButtonInf"));
		if (inf.IsEnabled()) changeColor(inf, infSelected);
		ButtonWidget light = ButtonWidget.Cast(parent.FindAnyWidget("ButtonLight"));
		if (light.IsEnabled()) changeColor(light, lightSelected);
		ButtonWidget heavy = ButtonWidget.Cast(parent.FindAnyWidget("ButtonHeavy"));
		if (heavy.IsEnabled()) changeColor(heavy, heavySelected);
		ButtonWidget air = ButtonWidget.Cast(parent.FindAnyWidget("ButtonAir"));
		if (air.IsEnabled()) changeColor(air, airSelected);
		ButtonWidget rep = ButtonWidget.Cast(parent.FindAnyWidget("ButtonRep"));
		if (rep.IsEnabled()) changeColor(rep, repSelected);
		ButtonWidget ammo = ButtonWidget.Cast(parent.FindAnyWidget("ButtonAmmo"));
		if (ammo.IsEnabled()) changeColor(ammo, ammoSelected);
		ButtonWidget naval = ButtonWidget.Cast(parent.FindAnyWidget("ButtonNaval"));
		if (naval.IsEnabled()) changeColor(naval, navalSelected);
		ButtonWidget flag = ButtonWidget.Cast(parent.FindAnyWidget("ButtonFlag"));
		if (flag.IsEnabled()) changeColor(flag, flagSelected);
	}
};