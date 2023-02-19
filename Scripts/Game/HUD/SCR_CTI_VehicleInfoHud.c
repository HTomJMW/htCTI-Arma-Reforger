class SCR_CTI_VehicleInfoHud : SCR_InfoDisplayExtended
{
	protected RichTextWidget m_name;
	protected RichTextWidget m_fuel;
	protected RichTextWidget m_damage;
	protected RichTextWidget m_occupants;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.5;
	
	SCR_CTI_GameMode m_gameMode;
	PlayerController m_pc;
	IEntity m_ent;
	CompartmentAccessComponent m_compartmentAccessComp;
	IEntity m_vehicle;
	SCR_VehicleDamageManagerComponent m_vehicleDamageManager;
	FuelManagerComponent m_fuelManagerComp;
	PlayerManager m_playerManager;

	//------------------------------------------------------------------------------------------------
	protected void CreateHud(IEntity owner)
	{
		m_name = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Name"));
		m_fuel = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Fuel"));
		m_damage = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Damage"));
		m_occupants = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Occupants"));

		m_name.SetText("Vehicle Name");
		m_name.SetVisible(true);
		
		m_fuel.SetText("Vehicle Fuel");
		m_fuel.SetVisible(true);
		
		m_damage.SetText("Vehicle Damage");
		m_damage.SetVisible(true);

		m_occupants.SetText("");
		m_occupants.SetVisible(true);
		
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

			m_ent = m_pc.GetControlledEntity();
			m_compartmentAccessComp = CompartmentAccessComponent.Cast(m_ent.FindComponent(CompartmentAccessComponent));
			m_vehicle = m_compartmentAccessComp.GetVehicleIn(m_ent);
			if (m_vehicle) {if (m_vehicle.Type().ToString() != "Vehicle") return;} // prevent use hud on static weapons
			bool menuOpen = GetGame().GetMenuManager().IsAnyMenuOpen();
			if (m_vehicle && !menuOpen)
			{
				m_wRoot.SetVisible(true);
			} else {
				m_wRoot.SetVisible(false);
			}
			if (m_vehicle)
			{
				//EntityPrefabData data = m_vehicle.GetPrefabData();
				//BaseContainer container = data.GetPrefab();
				//m_name.SetText(container.GetClassName());
				SCR_EditableVehicleComponent vehComp = SCR_EditableVehicleComponent.Cast(m_vehicle.FindComponent(SCR_EditableVehicleComponent));
				SCR_UIInfo info = vehComp.GetInfo(); // Entityinfo better?
				string displayName = WidgetManager.Translate(info.GetName());
				displayName.Replace(" ", "\n");
				m_name.SetText(displayName);
				
				m_vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(m_vehicle.FindComponent(SCR_VehicleDamageManagerComponent));
				array<HitZone> hitZones = {};
				m_vehicleDamageManager.GetAllHitZones(hitZones);
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
				m_damage.SetText("Condition: " + cond);
				
				m_fuelManagerComp = FuelManagerComponent.Cast(m_vehicle.FindComponent(FuelManagerComponent));
				int fuel = (m_fuelManagerComp.GetTotalFuel() / m_fuelManagerComp.GetTotalMaxFuel()) * 100; // maybe L better than %?

				string fu;
				switch (true)
				{
					case (fuel < 75 && fuel > 25): fu = string.Format("<color rgba='255,255,0,255'>%1%2</color>", fuel.ToString(), "%"); break;
					case (fuel < 25): fu = string.Format("<color rgba='255,0,0,255'>%1%2</color>", fuel.ToString(), "%"); break;
					default: fu = string.Format("<color rgba='0,255,0,255'>%1%2</color>", fuel.ToString(), "%"); break;
				}
				m_fuel.SetText("Fuel: " + fu);

				string occupants;
				BaseCompartmentManagerComponent bcmc = BaseCompartmentManagerComponent.Cast(m_vehicle.FindComponent(BaseCompartmentManagerComponent));
				array<BaseCompartmentSlot> outCompartments = {};
				bcmc.GetCompartments(outCompartments);

				if (!outCompartments.IsEmpty())
				{
					foreach(BaseCompartmentSlot slot : outCompartments)
					{
						if (slot.GetOccupant())
						{
							int playerId = m_playerManager.GetPlayerIdFromControlledEntity(slot.GetOccupant());
							if (playerId > 0)
							{
								string playerName = m_playerManager.GetPlayerName(playerId);
								occupants = occupants + playerName + "\n";
							}
						}
					}
				}
				m_occupants.SetText(occupants);

			}
			m_timeDelta = 0;
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool DisplayStartDrawInit(IEntity owner)
	{
		if (m_LayoutPath == "") m_LayoutPath = "{FA2748932AA7B28A}UI/layouts/VehicleInfoHud.layout";
		
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_playerManager = GetGame().GetPlayerManager();

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