[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Randomize start positions.")]
class SCR_CTI_RandomStartComponentClass : ScriptComponentClass
{
};

class SCR_CTI_RandomStartComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected bool m_ussrAtNorth = false;

	//------------------------------------------------------------------------------------------------	
	protected void randomStart()
	{
		if (Math.RandomIntInclusive(0, 1) == 0)
		{
			m_ussrAtNorth = true;
		} else {
			m_ussrAtNorth = false;
		}
		PrintFormat("CTI :: USSR Spawn at north: %1", m_ussrAtNorth.ToString());
	}

	//------------------------------------------------------------------------------------------------
	protected void setupStart()
	{
		BaseWorld world = GetGame().GetWorld();
		
		SCR_SpawnPoint spNorth = SCR_SpawnPoint.Cast(world.FindEntityByName("SpawnPointNorth"));
		SCR_SpawnPoint spSouth = SCR_SpawnPoint.Cast(world.FindEntityByName("SpawnPointSouth"));

		SCR_CTI_VehicleSpawn svNorth1 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleNorth1"));
		SCR_CTI_VehicleSpawn svNorth2 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleNorth2"));
		SCR_CTI_VehicleSpawn svNorth3 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleNorth3"));
		
		SCR_CTI_VehicleSpawn svSouth1 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleSouth1"));
		SCR_CTI_VehicleSpawn svSouth2 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleSouth2"));
		SCR_CTI_VehicleSpawn svSouth3 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleSouth3"));
		
		// Additional items for vehicles
		ResourceName ussr_bandage = "{C3F1FA1E2EC2B345}Prefabs/Items/Medicine/FieldDressing_USSR_01.et";
		ResourceName ussr_ak_mag = "{0A84AA5A3884176F}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Last_5Tracer.et";
		ResourceName ussr_rpg7 = "{7A82FE978603F137}Prefabs/Weapons/Launchers/RPG7/Launcher_RPG7.et";
		ResourceName ussr_rpg_ammo = "{32E12D322E107F1C}Prefabs/Weapons/Ammo/Ammo_Rocket_PG7VM.et";
		ResourceName ussr_grenade = "{645C73791ECA1698}Prefabs/Weapons/Grenades/Grenade_RGD5.et";
		
		ResourceName us_bandage = "{A81F501D3EF6F38E}Prefabs/Items/Medicine/FieldDressing_US_01.et";
		ResourceName us_m16_mag = "{D8F2CA92583B23D3}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Last_5Tracer.et";
		ResourceName us_m72 = "{9C5C20FB0E01E64F}Prefabs/Weapons/Launchers/M72/Launcher_M72A3.et";
		ResourceName us_m72_ammo = "{79FA751EEBE25DDE}Prefabs/Weapons/Ammo/Ammo_Rocket_M72A3.et";
		ResourceName us_grenade = "{E8F00BF730225B00}Prefabs/Weapons/Grenades/Grenade_M67.et";
		
		// UAZ items
		map<ResourceName, int> itemMapUaz = new map<ResourceName, int>();
		itemMapUaz.Set(ussr_bandage, 5);
		itemMapUaz.Set(ussr_ak_mag, 10);
		itemMapUaz.Set(ussr_rpg7, 3);
		itemMapUaz.Set(ussr_rpg_ammo, 6);
		itemMapUaz.Set(ussr_grenade, 4);

		// Ural items
		map<ResourceName, int> itemMapUral = new map<ResourceName, int>();
		itemMapUral.Set(ussr_bandage, 5);
		itemMapUral.Set(ussr_ak_mag, 10);
		itemMapUral.Set(ussr_rpg7, 3);
		itemMapUral.Set(ussr_rpg_ammo, 6);
		itemMapUral.Set(ussr_grenade, 4);
		
		// Ural MHQ items
		map<ResourceName, int> intemMapUralMHQ = new map<ResourceName, int>();
		intemMapUralMHQ.Set(ussr_bandage, 5);
		
		// Jeep items
		map<ResourceName, int> itemMapM151 = new map<ResourceName, int>();
		itemMapM151.Set(us_bandage, 5);
		itemMapM151.Set(us_m16_mag, 10);
		itemMapM151.Set(us_m72, 3);
		itemMapM151.Set(us_m72_ammo, 6);
		itemMapM151.Set(us_grenade, 4);
		
		// M923 Items
		map<ResourceName, int> itemMapM923 = new map<ResourceName, int>();
		itemMapM923.Set(us_bandage, 5);
		itemMapM923.Set(us_m16_mag, 10);
		itemMapM923.Set(us_m72, 3);
		itemMapM923.Set(us_m72_ammo, 6);
		itemMapM923.Set(us_grenade, 4);
		
		// M923 MHQ items
		map<ResourceName, int> intemMapM923MHQ = new map<ResourceName, int>();
		intemMapM923MHQ.Set(us_bandage, 5);
		
		if (m_ussrAtNorth)
		{
			// USSR on North
			spNorth.SetFactionKey("USSR");
			spSouth.SetFactionKey("US");

			// UAZ + equipment
			svNorth1.setPrefab("{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et");
			svNorth1.addItemsPrefab(itemMapUaz);
			
			// Ural truck + equipment
			svNorth2.setPrefab("{D9B91FAB817A6033}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport_covered.et");
			svNorth2.addItemsPrefab(itemMapUral);
			
			// USSR MHQ + equipment
			svNorth3.setPrefab(m_gameMode.USSRMHQ);
			svNorth3.addItemsPrefab(intemMapUralMHQ);
			
			// Jeep + equipment
			svSouth1.setPrefab("{47D94E1193A88497}Prefabs/Vehicles/Wheeled/M151A2/M151A2_transport.et");
			svSouth1.addItemsPrefab(itemMapM151);
			
			// M923A1 truck + equipment
			svSouth2.setPrefab("{81FDAD5EB644CC3D}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport_covered.et");
			svSouth2.addItemsPrefab(itemMapM923);
			
			// US MHQ + equipment
			svSouth3.setPrefab(m_gameMode.USMHQ);
			svSouth3.addItemsPrefab(intemMapM923MHQ);
			
		} else {
			
			// USSR on South
			spNorth.SetFactionKey("US");
			spSouth.SetFactionKey("USSR");
			
			// Jeep + equipment
			svNorth1.setPrefab("{47D94E1193A88497}Prefabs/Vehicles/Wheeled/M151A2/M151A2_transport.et");
			svNorth1.addItemsPrefab(itemMapM151);

			// M923A1 truck + equipment
			svNorth2.setPrefab("{81FDAD5EB644CC3D}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport_covered.et");
			svNorth2.addItemsPrefab(itemMapM923);
			
			// US MHQ + equipment
			svNorth3.setPrefab(m_gameMode.USMHQ);
			svNorth3.addItemsPrefab(intemMapM923MHQ);
			
			// UAZ + equipment
			svSouth1.setPrefab("{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et");
			svSouth1.addItemsPrefab(itemMapUaz);
			
			// Ural truck + equipment
			svSouth2.setPrefab("{D9B91FAB817A6033}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport_covered.et");
			svSouth2.addItemsPrefab(itemMapUral);
			
			// USSR MHQ + equipment
			svSouth3.setPrefab(m_gameMode.USSRMHQ);
			svSouth3.addItemsPrefab(intemMapUralMHQ);
		}
	}

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		
		randomStart();
		setupStart();
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_RandomStartComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_RandomStartComponent()
	{
	}	
};