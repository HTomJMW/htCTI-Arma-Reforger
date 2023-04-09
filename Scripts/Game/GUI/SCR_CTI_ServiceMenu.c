class SCR_CTI_ServiceMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected SCR_CTI_ClientData clientData;
	protected IEntity ent;
	protected FactionAffiliationComponent userAffiliationComponent;
	protected FactionKey factionkey;
	protected int playerId;
	
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
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		ent = pc.GetControlledEntity();
		userAffiliationComponent = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		factionkey = userAffiliationComponent.GetAffiliatedFaction().GetFactionKey();
		playerId = pc.GetPlayerId();
		
		ChimeraCharacter ch = ChimeraCharacter.Cast(ent);
		
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

		clientData = gameMode.getClientData(playerId);

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

		array<IEntity> repDepots = SCR_CTI_GetSideFactories.GetSideFactoriesByType(factionkey, "Repair Depot");
		array<IEntity> ammoDepots = SCR_CTI_GetSideFactories.GetSideFactoriesByType(factionkey, "Ammo Depot");

		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		SCR_AIGroup playerGroup = gmc.GetPlayerGroup(pc.GetPlayerId());

		array<AIAgent> outAgents = {};
		playerGroup.GetAgents(outAgents);

		array<IEntity> vehicles = {};

		foreach(AIAgent agent : outAgents)
		{
			IEntity unit = agent.GetControlledEntity();
			SCR_CompartmentAccessComponent cac = SCR_CompartmentAccessComponent.Cast(unit.FindComponent(SCR_CompartmentAccessComponent));
			IEntity vehicle = cac.GetVehicle();

			if (vehicle && !vehicles.Contains(vehicle) && vehicle.Type().ToString() == "Vehicle")
			{
				vehicles.Insert(vehicle);

				if (repDepots)
				{
					foreach(IEntity repDepot : repDepots)
					{
						float dist = vector.Distance(repDepot.GetOrigin(), vehicle.GetOrigin());
						if (dist > SCR_CTI_Constants.SERVICERANGE) repDepots.RemoveItem(repDepot);
					}
				}

				if (ammoDepots)
				{
					foreach(IEntity ammoDepot : ammoDepots)
					{
						float dist = vector.Distance(ammoDepot.GetOrigin(), vehicle.GetOrigin());
						if (dist > SCR_CTI_Constants.SERVICERANGE) repDepots.RemoveItem(ammoDepot);
					}
				}

				if ((repDepots && !repDepots.IsEmpty()) || (ammoDepots && !ammoDepots.IsEmpty()))
				{
					SCR_EditableVehicleComponent vehComp = SCR_EditableVehicleComponent.Cast(vehicle.FindComponent(SCR_EditableVehicleComponent));
					SCR_UIInfo info = vehComp.GetInfo();
					string displayName = WidgetManager.Translate(info.GetName());

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
					string dam = damage.ToString() + "%";

					FuelManagerComponent fuelManagerComp = FuelManagerComponent.Cast(vehicle.FindComponent(FuelManagerComponent));
					int fuel = (fuelManagerComp.GetTotalFuel() / fuelManagerComp.GetTotalMaxFuel()) * 100;
					string fu = fuel.ToString() + "%";
					
					SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(vehicle.FindComponent(SCR_BaseCompartmentManagerComponent));

					array<IEntity> occupants = {};
					bcmc.GetOccupants(occupants);

					string health = "Good"; // Todo: veh Empty

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

					string ammo = "Unarmed";
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

					RplComponent rplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));
	
					m_listboxcomp.AddItem(displayName + " | Damege: " + dam + " | Ammo: " + ammo + " | Fuel: " + fu + " | Health: " + health, rplComp);
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			/*array<IEntity> repDepots = SCR_CTI_GetSideFactories.GetSideFactoriesByType(factionkey, "Repair Depot");
			array<IEntity> ammoDepots = SCR_CTI_GetSideFactories.GetSideFactoriesByType(factionkey, "Ammo Depot");
	
			if (repDepots || ammoDepots)
			{
				SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
				SCR_AIGroup playerGroup = gmc.GetPlayerGroup(pc.GetPlayerId());
				
				array<AIAgent> outAgents = {};
				playerGroup.GetAgents(outAgents);
				
				array<IEntity> vehicles = {};
				
				foreach(AIAgent agent : outAgents)
				{
					IEntity unit = agent.GetControlledEntity();
					SCR_CompartmentAccessComponent cac = SCR_CompartmentAccessComponent.Cast(unit.FindComponent(SCR_CompartmentAccessComponent));
					IEntity vehicle = cac.GetVehicle();
		
					if (vehicle && !vehicles.Contains(vehicle) && vehicle.Type().ToString() == "Vehicle")
					{
						vehicles.Insert(vehicle);
	
						foreach(IEntity repDepot : repDepots)
						{
							float dist = vector.Distance(repDepot.GetOrigin(), vehicle.GetOrigin());
							if (dist > SCR_CTI_Constants.SERVICERANGE) repDepots.RemoveItem(repDepot);
						}
						
						foreach(IEntity ammoDepot : ammoDepots)
						{
							float dist = vector.Distance(ammoDepot.GetOrigin(), vehicle.GetOrigin());
							if (dist > SCR_CTI_Constants.SERVICERANGE) repDepots.RemoveItem(ammoDepot);
						}
		
						if (!repDepots.IsEmpty() || !ammoDepots.IsEmpty())
						{
							SCR_EditableVehicleComponent vehComp = SCR_EditableVehicleComponent.Cast(vehicle.FindComponent(SCR_EditableVehicleComponent));
							SCR_UIInfo info = vehComp.GetInfo();
							string displayName = WidgetManager.Translate(info.GetName());
							
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
							string dam = damage.ToString() + "%";
		
							FuelManagerComponent fuelManagerComp = FuelManagerComponent.Cast(vehicle.FindComponent(FuelManagerComponent));
							int fuel = (fuelManagerComp.GetTotalFuel() / fuelManagerComp.GetTotalMaxFuel()) * 100;
							string fu = fuel.ToString() + "%";
		
							RplComponent rplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));
		
							m_listboxcomp.AddItem(displayName + " | Damege: " + dam + " | Ammo: " + "AMMO" + " | Fuel: " + fu + " | Heal: " + "HEAL", rplComp);
						}
					}
				}
			}*/
			m_timeDelta = 0;
		}
	}
};