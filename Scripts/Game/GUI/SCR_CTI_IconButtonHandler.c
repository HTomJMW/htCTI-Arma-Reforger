class SCR_CTI_IconButtonHandler : ScriptedWidgetEventHandler
{
	protected bool infSelected = true; // default selected
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
	protected bool lockSelected = true; // default lock
	protected bool unlockSelected = false;

	//------------------------------------------------------------------------------------------------
	/*override bool OnMouseEnter(Widget w, int x, int y)
	{
		w.SetColor(Color.White);
		ImageWidget children = ImageWidget.Cast(w.GetChildren());
		children.SetColor(Color.Orange);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		w.SetColor(Color.Orange);
		ImageWidget children = ImageWidget.Cast(w.GetChildren());
		children.SetColor(Color.White);
		
		return true;
	}*/

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		switch (w.GetName())
		{
			case "BUTTONINF":
			{
				infSelected = true;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColor(w, infSelected);

				break;
			}
			case "BUTTONLIGHT":
			{
				infSelected = false;
				lightSelected = true;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColor(w, lightSelected);

				break;
			}
			case "BUTTONHEAVY":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = true;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColor(w, heavySelected);
			
				break;
			}
			case "BUTTONAIR":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = true;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColor(w, airSelected);
			
				break;
			}
			case "BUTTONREP":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = true;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = false;
				
				changeColor(w, repSelected);
				
				break;
			}
			case "BUTTONAMMO":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = true;
				navalSelected = false;
				flagSelected = false;
				
				changeColor(w, ammoSelected);
			
				break;
			}
			case "BUTTONNAVAL":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = true;
				flagSelected = false;
				
				changeColor(w, navalSelected);
			
				break;
			}
			case "BUTTONFLAG":
			{
				infSelected = false;
				lightSelected = false;
	 			heavySelected = false;
	  			airSelected = false;
				repSelected = false;
				ammoSelected = false;
				navalSelected = false;
				flagSelected = true;
				
				changeColor(w, flagSelected);
			
				break;
			}
			case "BUTTONDRIVER":
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
			case "BUTTONGUNNER":
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
			case "BUTTONCOMMANDER":
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
			case "BUTTONCREW":
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
			case "BUTTONLOCK":
			{
				lockSelected = true;
				unlockSelected = false;
				
				changeColor(w, lockSelected);
				
				ButtonWidget m_unlock;
				Widget sibling = w.GetParent().GetChildren();
				while (sibling)
				{
					if (sibling.GetName() == "BUTTONUNLOCK")
					{
						m_unlock = ButtonWidget.Cast(sibling);
						break;
					}
					sibling = sibling.GetSibling();
				}
				
				changeColor(m_unlock, unlockSelected);

				break;
			}
			case "BUTTONUNLOCK":
			{
				unlockSelected = true;
				lockSelected = false;

				changeColor(w, unlockSelected);
				
				
				ButtonWidget m_lock;
				Widget sibling = w.GetParent().GetChildren();
				while (sibling)
				{
					if (sibling.GetName() == "BUTTONLOCK")
					{
						m_lock = ButtonWidget.Cast(sibling);
						break;
					}
					sibling = sibling.GetSibling();
				}
				
				changeColor(m_lock, lockSelected);

				break;
			}
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	protected void changeColor(Widget w, bool selected)
	{
		if (selected)
		{
			w.SetColor(Color.White);
			ImageWidget children = ImageWidget.Cast(w.GetChildren());
			children.SetColor(Color.Orange);
		} else {
			w.SetColor(Color.Orange);
			ImageWidget children = ImageWidget.Cast(w.GetChildren());
			children.SetColor(Color.White);
		}
	}
};