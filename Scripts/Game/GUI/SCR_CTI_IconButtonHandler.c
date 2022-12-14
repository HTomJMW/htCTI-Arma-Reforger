class SCR_CTI_IconButtonHandler : ScriptedWidgetEventHandler
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
	protected void changeColor(Widget w, bool selected)
	{
		ImageWidget children = ImageWidget.Cast(w.GetChildren());
		
		if (selected)
		{
			w.SetColor(Color.White);
			children.SetColor(Color.Orange);
		} else {
			w.SetColor(Color.Orange);
			children.SetColor(Color.White);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void changeColorAllType(Widget w)
	{
		Widget parent = w.GetParent();
		
		ButtonWidget inf = ButtonWidget.Cast(parent.FindAnyWidget("ButtonInf"));
		changeColor(inf, infSelected);
		ButtonWidget light = ButtonWidget.Cast(parent.FindAnyWidget("ButtonLight"));
		changeColor(light, lightSelected);
		ButtonWidget heavy = ButtonWidget.Cast(parent.FindAnyWidget("ButtonHeavy"));
		changeColor(heavy, heavySelected);
		ButtonWidget air = ButtonWidget.Cast(parent.FindAnyWidget("ButtonAir"));
		changeColor(air, airSelected);
		ButtonWidget rep = ButtonWidget.Cast(parent.FindAnyWidget("ButtonRep"));
		changeColor(rep, repSelected);
		ButtonWidget ammo = ButtonWidget.Cast(parent.FindAnyWidget("ButtonAmmo"));
		changeColor(ammo, ammoSelected);
		ButtonWidget naval = ButtonWidget.Cast(parent.FindAnyWidget("ButtonNaval"));
		changeColor(naval, navalSelected);
		ButtonWidget flag = ButtonWidget.Cast(parent.FindAnyWidget("ButtonFlag"));
		changeColor(flag, flagSelected);
	}
};