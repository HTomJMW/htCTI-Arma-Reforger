class SCR_CTI_VehicleInfoHud : SCR_InfoDisplayExtended
{
	protected RichTextWidget Name;
	protected RichTextWidget Fuel;
	protected RichTextWidget Damage;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.5;
	
	SCR_CTI_GameMode gameMode;
	PlayerController pc;
	IEntity ent;
	CompartmentAccessComponent compartmentAccessComp;
	IEntity vehicle;
	SCR_VehicleDamageManagerComponent vehicleDamageManager;
	FuelManagerComponent fuelManagerComp;

	//------------------------------------------------------------------------------------------------
	protected void CreateHud(IEntity owner)
	{
		Name = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Name"));
		Fuel = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Fuel"));
		Damage = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Damage"));
		
		Name.SetText("Vehicle Name");
		Name.SetVisible(true);
		
		Fuel.SetText("Vehicle Fuel");
		Fuel.SetVisible(true);
		
		Damage.SetText("Vehicle Damage");
		Damage.SetVisible(true);
		
		m_wRoot.SetVisible(false);
	}

	//------------------------------------------------------------------------------------------------
	protected void DestroyHud()
	{		
		if (!m_wRoot)
			return;		

		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
		
		m_wRoot = null;		
	}

	//------------------------------------------------------------------------------------------------
	override event void DisplayUpdate(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
		{
			if (!m_wRoot)
				return;	
			
			pc = GetGame().GetPlayerController();
			ent = pc.GetControlledEntity();
			compartmentAccessComp = CompartmentAccessComponent.Cast(ent.FindComponent(CompartmentAccessComponent));
			vehicle = compartmentAccessComp.GetVehicleIn(ent);
			if (vehicle) {if (vehicle.Type().ToString() != "Vehicle") return;} // prevent use hud on static weapons
			bool menuOpen = GetGame().GetMenuManager().IsAnyMenuOpen();
			if (vehicle && !menuOpen)
			{
				m_wRoot.SetVisible(true);
			} else {
				m_wRoot.SetVisible(false);
			}
			if (vehicle)
			{
				EntityPrefabData data = vehicle.GetPrefabData();
				BaseContainer container = data.GetPrefab();
				//Name.SetText(container.GetClassName());
				SCR_EditableVehicleComponent vehComp = SCR_EditableVehicleComponent.Cast(vehicle.FindComponent(SCR_EditableVehicleComponent));
				SCR_UIInfo info = vehComp.GetInfo(); // Entityinfo better?
				string displayName = WidgetManager.Translate(info.GetName());
				displayName.Replace(" ", "\n");
				Name.SetText(displayName);
				
				vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(vehicle.FindComponent(SCR_VehicleDamageManagerComponent));
				array<HitZone> hitZones = {};
				vehicleDamageManager.GetAllHitZones(hitZones);
				float hp = 0.0;
				float maxhp = 0.0;
				
				foreach (HitZone hitzone : hitZones)
				{
					hp += hitzone.GetHealth();
					maxhp += hitzone.GetMaxHealth();
				}
				float condition = Math.Round((hp / maxhp) * 100);
				
				string cond;
				switch (true)
				{
					case (hp < 75 && hp > 25): cond = string.Format("<color rgba='255,255,0,255'>%1%2</color>", condition.ToString(), "%"); break;
					case (hp < 25): cond = string.Format("<color rgba='255,0,0,255'>%1%2</color>", condition.ToString(), "%"); break;
					default: cond = string.Format("<color rgba='0,255,0,255'>%1%2</color>", condition.ToString(), "%"); break;
				}
				Damage.SetText("Condition: " + cond);
				
				fuelManagerComp = FuelManagerComponent.Cast(vehicle.FindComponent(FuelManagerComponent));
				int fuel = (fuelManagerComp.GetTotalFuel() / fuelManagerComp.GetTotalMaxFuel()) * 100; // maybe L better than %?

				string fu;
				switch (true)
				{
					case (fuel < 75 && fuel > 25): fu = string.Format("<color rgba='255,255,0,255'>%1%2</color>", fuel.ToString(), "%"); break;
					case (fuel < 25): fu = string.Format("<color rgba='255,0,0,255'>%1%2</color>", fuel.ToString(), "%"); break;
					default: fu = string.Format("<color rgba='0,255,0,255'>%1%2</color>", fuel.ToString(), "%"); break;
				}
				Fuel.SetText("Fuel: " + fu);
			}
			m_timeDelta = 0;
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool DisplayStartDrawInit(IEntity owner)
	{
		if (m_LayoutPath == "") m_LayoutPath = "{FA2748932AA7B28A}UI/layouts/VehicleInfoHud.layout";
		
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_timeDelta = 0;

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayStartDraw(IEntity owner)
	{
		if (!m_wRoot)
		{
			return;
		}

		CreateHud(owner);
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayInit(IEntity owner)
	{
		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayStopDraw(IEntity owner)
	{
		DestroyHud();
	}
};