class SCR_CTI_ServiceMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected IEntity m_player;
	protected FactionAffiliationComponent m_userAffiliationComponent;
	protected FactionKey m_factionkey;
	protected int m_playerId;
	protected SCR_CTI_ClientData clientData;

	protected BaseWorld m_world;
	protected ref array<IEntity> m_vehiclesNearRepDepot = {};
	protected ref array<IEntity> m_vehiclesNearAmmoDepot = {};
	protected ref array<IEntity> m_vehiclesNearRepairTruck = {};
	protected ref array<IEntity> m_vehiclesNearAmmoTruck = {};
	protected ref array<IEntity> m_vehiclesNearFuelTruck = {};

	protected float m_timeDelta;
	protected const float TIMESTEP = 0.5;
	
	protected Widget m_wRoot;

	protected ButtonWidget m_repair;
	protected ButtonWidget m_rearm;
	protected ButtonWidget m_refuel;
	protected ButtonWidget m_heal;
	
	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;

	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_ServiceMenuButtonHandler m_serviceMenubuttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_player = m_pc.GetControlledEntity();
		m_userAffiliationComponent = FactionAffiliationComponent.Cast(m_player.FindComponent(FactionAffiliationComponent));
		m_factionkey = m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey();
		m_playerId = m_pc.GetPlayerId();

		m_wRoot = GetRootWidget();

		m_repair = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Repair"));
		m_rearm = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Rearm"));
		m_refuel = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Refuel"));
		m_heal = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Heal"));
		
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));
		
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));

		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_serviceMenubuttonEventHandler = new SCR_CTI_ServiceMenuButtonHandler();

		//m_repair.SetColor(Color.Gray);
		//m_repair.SetEnabled(false);
		m_repair.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_repair.AddHandler(m_serviceMenubuttonEventHandler);

		//m_rearm.SetColor(Color.Gray);
		//m_rearm.SetEnabled(false);
		m_rearm.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_rearm.AddHandler(m_serviceMenubuttonEventHandler);

		//m_refuel.SetColor(Color.Gray);
		//m_refuel.SetEnabled(false);
		m_refuel.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_refuel.AddHandler(m_serviceMenubuttonEventHandler);

		//m_heal.SetColor(Color.Gray);
		//m_heal.SetEnabled(false);
		m_heal.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_heal.AddHandler(m_serviceMenubuttonEventHandler);

		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);

		m_world = GetGame().GetWorld();

		array<IEntity> repDepots = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionkey, "Repair Depot");
		array<IEntity> ammoDepots = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionkey, "Ammo Depot");

		SCR_CTI_GetSupportVehicles getSupportVehiclesRep = new SCR_CTI_GetSupportVehicles();
		array<IEntity> repairTrucks = getSupportVehiclesRep.GetSupportVehiclesInRangeByType(m_factionkey, m_player.GetOrigin(), SCR_CTI_Constants.SERVICERANGE, CTI_SupportVehicleTypes.REPAIR);
		
		SCR_CTI_GetSupportVehicles getSupportVehiclesAmmo = new SCR_CTI_GetSupportVehicles();
		array<IEntity> ammoTrucks = getSupportVehiclesAmmo.GetSupportVehiclesInRangeByType(m_factionkey, m_player.GetOrigin(), SCR_CTI_Constants.SERVICERANGE, CTI_SupportVehicleTypes.AMMO);

		SCR_CTI_GetSupportVehicles getSupportVehiclesFuel = new SCR_CTI_GetSupportVehicles();
		array<IEntity> fuelTrucks = getSupportVehiclesFuel.GetSupportVehiclesInRangeByType(m_factionkey, m_player.GetOrigin(), SCR_CTI_Constants.SERVICERANGE, CTI_SupportVehicleTypes.FUEL);

		bool mhqIsWreck = false;
		bool mhqWreckInRange = false;
		IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(m_factionkey);
		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(mhq.FindComponent(SCR_VehicleDamageManagerComponent));
		if (vdmc && vdmc.IsDestroyed()) mhqIsWreck = true;

		// Vehicles near player if repair truck available
		if (!repairTrucks.IsEmpty())
		{
			for (int k = 0; k < repairTrucks.Count(); k++)
			{
				m_world.QueryEntitiesBySphere(repairTrucks[k].GetOrigin(), SCR_CTI_Constants.SERVICERANGE, GetEntityNearRepTruck, FilterEntities, EQueryEntitiesFlags.DYNAMIC);

				if (mhqIsWreck)
				{
					float distance = vector.Distance(mhq.GetOrigin(), repairTrucks[k].GetOrigin());
					if (distance <= SCR_CTI_Constants.SERVICERANGE) mhqWreckInRange = true;
				}
			}

			if (!m_vehiclesNearRepairTruck.IsEmpty())
			{
				m_listboxcomp.AddSeparator("Vehicles near closest Repair Truck:");

				foreach (IEntity vehicle : m_vehiclesNearRepairTruck)
				{
					string displayName, dam, ammo, fu, health;
					getVehicleInformations(vehicle, displayName, dam, fu, ammo, health);
	
					// Get vehicle rplcomp for data
					RplComponent rplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));

					m_listboxcomp.AddItem(displayName + " | Damege: " + dam + " | Ammo: " + ammo + " | Fuel: " + fu + " | Health: " + health, rplComp);
				}
				
				m_listboxcomp.AddSeparator("_______________________________________________________________________________");
			}
		}
		
		// Vehicles near player if ammo truck available
		if (!ammoTrucks.IsEmpty())
		{
			for (int l = 0; l < ammoTrucks.Count(); l++)
			{
				m_world.QueryEntitiesBySphere(ammoTrucks[l].GetOrigin(), SCR_CTI_Constants.SERVICERANGE, GetEntityNearAmmoTruck, FilterEntities, EQueryEntitiesFlags.DYNAMIC);
			}

			if (!m_vehiclesNearAmmoTruck.IsEmpty())
			{
				m_listboxcomp.AddSeparator("Vehicles near closest Ammo Truck:");

				foreach (IEntity vehicle : m_vehiclesNearAmmoTruck)
				{
					string displayName, dam, ammo, fu, health;
					getVehicleInformations(vehicle, displayName, dam, fu, ammo, health);
	
					// Get vehicle rplcomp for data
					RplComponent rplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));

					m_listboxcomp.AddItem(displayName + " | Damege: " + dam + " | Ammo: " + ammo + " | Fuel: " + fu + " | Health: " + health, rplComp);
				}
				
				m_listboxcomp.AddSeparator("_______________________________________________________________________________");
			}
		}
		
		// Vehicles near player if fuel truck available
		if (!fuelTrucks.IsEmpty())
		{
			for (int m = 0; m < fuelTrucks.Count(); m++)
			{
				m_world.QueryEntitiesBySphere(fuelTrucks[m].GetOrigin(), SCR_CTI_Constants.SERVICERANGE, GetEntityNearFuelTruck, FilterEntities, EQueryEntitiesFlags.DYNAMIC);
			}

			if (!m_vehiclesNearFuelTruck.IsEmpty())
			{
				m_listboxcomp.AddSeparator("Vehicles near closest Fuel Truck:");

				foreach (IEntity vehicle : m_vehiclesNearFuelTruck)
				{
					string displayName, dam, ammo, fu, health;
					getVehicleInformations(vehicle, displayName, dam, fu, ammo, health);
	
					// Get vehicle rplcomp for data
					RplComponent rplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));

					m_listboxcomp.AddItem(displayName + " | Damege: " + dam + " | Ammo: " + ammo + " | Fuel: " + fu + " | Health: " + health, rplComp);
				}
				
				m_listboxcomp.AddSeparator("_______________________________________________________________________________");
			}
		}

		// Vehicles near repair depots
		for (int i = 0; i < repDepots.Count(); i++)
		{
			m_world.QueryEntitiesBySphere(repDepots[i].GetOrigin(), SCR_CTI_Constants.SERVICERANGE, GetEntityNearRepDepot, FilterEntities, EQueryEntitiesFlags.DYNAMIC);
		
			if (mhqIsWreck)
			{
				float distance = vector.Distance(mhq.GetOrigin(), repDepots[i].GetOrigin());
				if (distance <= SCR_CTI_Constants.SERVICERANGE) mhqWreckInRange = true;
			}
		}

		// Vehicles near ammo depots
		for (int j = 0; j < ammoDepots.Count(); j++)
		{
			m_world.QueryEntitiesBySphere(ammoDepots[j].GetOrigin(), SCR_CTI_Constants.SERVICERANGE, GetEntityNearAmmoDepot, FilterEntities, EQueryEntitiesFlags.DYNAMIC);
		}

		if (!m_vehiclesNearRepDepot.IsEmpty())
		{
			m_listboxcomp.AddSeparator("Vehicles Near Repair Depot:");
			
			foreach (IEntity vehicle : m_vehiclesNearRepDepot)
			{
				string displayName, dam, ammo, fu, health;
				getVehicleInformations(vehicle, displayName, dam, fu, ammo, health);

				// Get vehicle rplcomp for data
				RplComponent rplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));

				m_listboxcomp.AddItem(displayName + " | Damege: " + dam + " | Ammo: " + ammo + " | Fuel: " + fu + " | Health: " + health, rplComp);
			}
			
			m_listboxcomp.AddSeparator("_______________________________________________________________________________");
		}
		
		if (!m_vehiclesNearAmmoDepot.IsEmpty())
		{
			m_listboxcomp.AddSeparator("Vehicles near Ammo Depot:");

			foreach (IEntity vehicle : m_vehiclesNearAmmoDepot)
			{
				string displayName, dam, ammo, fu, health;
				getVehicleInformations(vehicle, displayName, dam, fu, ammo, health);

				// Get vehicle rplcomp for data
				RplComponent rplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));

				m_listboxcomp.AddItem(displayName + " | Damege: " + dam + " | Ammo: " + ammo + " | Fuel: " + fu + " | Health: " + health, rplComp);
			}

			m_listboxcomp.AddSeparator("_______________________________________________________________________________");
		}

		// Only Comm can repair MHQ
		clientData = m_gameMode.getClientData(m_playerId);
		if (mhqWreckInRange && clientData && clientData.isCommander())
		{
			m_listboxcomp.AddSeparator("MHQ Wreck [Repair Cost: " + SCR_CTI_Constants.MHQREPAIRCOST.ToString() + "$]:");
			RplComponent rplComp = RplComponent.Cast(mhq.FindComponent(RplComponent));
			m_listboxcomp.AddItem("MHQ Wreck", rplComp);
			m_listboxcomp.AddSeparator("_______________________________________________________________________________");
		}
	}

	//------------------------------------------------------------------------------------------------
	protected bool GetEntityNearRepDepot(IEntity ent)
	{
		if (!m_vehiclesNearRepDepot.Contains(ent)) m_vehiclesNearRepDepot.Insert(ent);

		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected bool GetEntityNearRepTruck(IEntity ent)
	{
		if (!m_vehiclesNearRepairTruck.Contains(ent)) m_vehiclesNearRepairTruck.Insert(ent);

		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected bool GetEntityNearAmmoDepot(IEntity ent)
	{
		if (!m_vehiclesNearAmmoDepot.Contains(ent)) m_vehiclesNearAmmoDepot.Insert(ent);

		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected bool GetEntityNearAmmoTruck(IEntity ent)
	{
		if (!m_vehiclesNearAmmoTruck.Contains(ent)) m_vehiclesNearAmmoTruck.Insert(ent);

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	protected bool GetEntityNearFuelTruck(IEntity ent)
	{
		if (!m_vehiclesNearFuelTruck.Contains(ent)) m_vehiclesNearFuelTruck.Insert(ent);

		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected bool FilterEntities(IEntity ent)
	{
		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (vdmc && !vdmc.IsDestroyed()) return true;

		return false;
	}

	//------------------------------------------------------------------------------------------------
	protected void getVehicleInformations(IEntity vehicle, out string displayName, out string dam, out string fu, out string ammo, out string health)
	{
		// TODO check vehicle fire

		// Get vehicle name
		SCR_EditableVehicleComponent vehComp = SCR_EditableVehicleComponent.Cast(vehicle.FindComponent(SCR_EditableVehicleComponent));
		SCR_UIInfo info = vehComp.GetInfo();
		displayName = WidgetManager.Translate(info.GetName());

		// Get vehicle damages
		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(vehicle.FindComponent(SCR_VehicleDamageManagerComponent));
		array<HitZone> hitZones = {};
		vehicleDamageManager.GetAllHitZones(hitZones);
		float hp = 0.0;
		float maxhp = 0.0;

		foreach (HitZone hitzone : hitZones)
		{
			hp += hitzone.GetHealth();
			maxhp += hitzone.GetMaxHealth();
		}
		float damage = 100 - (Math.Round((hp / maxhp) * 100));
		dam = damage.ToString() + "%";
				
		// Get vehicle fuel
		FuelManagerComponent fuelManagerComp = FuelManagerComponent.Cast(vehicle.FindComponent(FuelManagerComponent));
		int fuel = (fuelManagerComp.GetTotalFuel() / fuelManagerComp.GetTotalMaxFuel()) * 100;
		fu = fuel.ToString() + "%";

		// Get vehicle ammo
		SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(vehicle.FindComponent(SCR_BaseCompartmentManagerComponent));
		ammo = "Unarmed";
		string ammoInfo = "";

		array<BaseCompartmentSlot> outCompartments = {};
		bcmc.GetCompartments(outCompartments);

		foreach(BaseCompartmentSlot slot : outCompartments)
		{
			if (slot.Type() == TurretCompartmentSlot)
			{
				TurretControllerComponent tcc = TurretControllerComponent.Cast(slot.GetController());
				BaseWeaponManagerComponent bwmc = tcc.GetWeaponManager();

				array<IEntity> outWeapons = {};
				bwmc.GetWeaponsList(outWeapons);

				foreach(IEntity weapon : outWeapons)
				{
					WeaponComponent wc = WeaponComponent.Cast(weapon.FindComponent(WeaponComponent));
					BaseMagazineComponent bmc = wc.GetCurrentMagazine();

					int maxAmmo = bmc.GetMaxAmmoCount();
					int currentAmmo = bmc.GetAmmoCount();

					ammoInfo = wc.GetUIInfo().GetName();

					switch(true)
					{
						case (maxAmmo == currentAmmo): ammoInfo += ": Full"; break;
						case (maxAmmo * 0.75 < currentAmmo && maxAmmo != currentAmmo): ammoInfo += ": Enough"; break;
						case (maxAmmo * 0.75 > currentAmmo): ammoInfo += ": Few"; break;
						case (currentAmmo == 0): ammoInfo += ": Empty"; break;
					}
				}
			}
		}
		if (ammoInfo) ammo = ammoInfo;

		// Get vehicle crew condition
		array<IEntity> occupants = {};
		bcmc.GetOccupants(occupants);

		health = "No Crew";
		if (!occupants.IsEmpty()) health = "Good";

		foreach(IEntity crew : occupants)
		{
			if (health == "Injurned") break;

			SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(crew.FindComponent(SCR_CharacterDamageManagerComponent));
			array<HitZone> outHitZones = {};
			cdmc.GetAllHitZones(outHitZones);

			foreach(HitZone hitzone : outHitZones)
			{
				if (hitzone.GetMaxHealth() * 0.75 > hitzone.GetHealth())
				{
					health = "Injurned";
					break;
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		m_vehiclesNearRepDepot.Clear();
		m_vehiclesNearRepDepot = null;
		m_vehiclesNearAmmoDepot.Clear();
		m_vehiclesNearAmmoDepot = null;
		m_vehiclesNearRepairTruck.Clear();
		m_vehiclesNearRepairTruck = null;
		m_vehiclesNearAmmoTruck.Clear();
		m_vehiclesNearAmmoTruck = null;
		m_vehiclesNearFuelTruck.Clear();
		m_vehiclesNearFuelTruck = null;
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			//TODO

			m_timeDelta = 0;
		}
	}
};