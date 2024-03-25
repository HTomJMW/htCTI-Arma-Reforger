[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Randomize start positions.")]
class SCR_CTI_RandomStartComponentClass : ScriptComponentClass
{
};

class SCR_CTI_RandomStartComponent : ScriptComponent
{
	protected bool m_ussrAtNorth = false;

	//------------------------------------------------------------------------------------------------	
	void randomStart()
	{
		RandomGenerator randomgen = new RandomGenerator();
		int h, m, s;
		System.GetHourMinuteSecond(h, m, s);
		randomgen.SetSeed(s * 100000);

		if (randomgen.RandIntInclusive(0, 1) == 0)
		{
			m_ussrAtNorth = true;
		} else {
			m_ussrAtNorth = false;
		}
		PrintFormat("CTI :: USSR Spawn at north: %1", m_ussrAtNorth.ToString());
		
		setupStart();
	}

	//------------------------------------------------------------------------------------------------
	protected void setupStart()
	{
		BaseWorld world = GetGame().GetWorld();

		SCR_CTI_VehicleSpawn svNorth1 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleNorth1"));
		SCR_CTI_VehicleSpawn svNorth2 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleNorth2"));
		SCR_CTI_VehicleSpawn svNorth3 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleNorth3"));
		
		SCR_CTI_VehicleSpawn svSouth1 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleSouth1"));
		SCR_CTI_VehicleSpawn svSouth2 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleSouth2"));
		SCR_CTI_VehicleSpawn svSouth3 = SCR_CTI_VehicleSpawn.Cast(world.FindEntityByName("SpawnVehicleSouth3"));

		// UAZ items
		map<ResourceName, int> itemMapUaz = new map<ResourceName, int>();
		itemMapUaz.Set(SCR_CTI_Constants.USSR_BANDAGE, 5);
		itemMapUaz.Set(SCR_CTI_Constants.USSR_AK_MAG, 10);
		itemMapUaz.Set(SCR_CTI_Constants.USSR_RPG7, 3);
		itemMapUaz.Set(SCR_CTI_Constants.USSR_RPG7_AMMO, 6);
		itemMapUaz.Set(SCR_CTI_Constants.USSR_GRENADE, 4);
		itemMapUaz.Set(SCR_CTI_Constants.TOOLKIT, 1);
		itemMapUaz.Set(SCR_CTI_Constants.EXTINGUISHER, 1);
		itemMapUaz.Set(SCR_CTI_Constants.USSR_BACKPACK, 2);

		// Ural items
		map<ResourceName, int> itemMapUral = new map<ResourceName, int>();
		itemMapUral.Set(SCR_CTI_Constants.USSR_BANDAGE, 5);
		itemMapUral.Set(SCR_CTI_Constants.USSR_AK_MAG, 10);
		itemMapUral.Set(SCR_CTI_Constants.USSR_RPG7, 3);
		itemMapUral.Set(SCR_CTI_Constants.USSR_RPG7_AMMO, 6);
		itemMapUral.Set(SCR_CTI_Constants.USSR_GRENADE, 4);
		itemMapUral.Set(SCR_CTI_Constants.TOOLKIT, 1);
		itemMapUral.Set(SCR_CTI_Constants.EXTINGUISHER, 1);
		itemMapUral.Set(SCR_CTI_Constants.USSR_BACKPACK, 2);
		
		// Ural MHQ items
		map<ResourceName, int> intemMapUralMHQ = new map<ResourceName, int>();
		intemMapUralMHQ.Set(SCR_CTI_Constants.USSR_BANDAGE, 5);
		intemMapUralMHQ.Set(SCR_CTI_Constants.TOOLKIT, 1);
		intemMapUralMHQ.Set(SCR_CTI_Constants.EXTINGUISHER, 1);
		intemMapUralMHQ.Set(SCR_CTI_Constants.USSR_BACKPACK, 2);
		
		// Jeep items
		map<ResourceName, int> itemMapM151 = new map<ResourceName, int>();
		itemMapM151.Set(SCR_CTI_Constants.US_BANDAGE, 5);
		itemMapM151.Set(SCR_CTI_Constants.US_M16_MAG, 10);
		itemMapM151.Set(SCR_CTI_Constants.US_M72, 9);
		itemMapM151.Set(SCR_CTI_Constants.US_GRENADE, 4);
		itemMapM151.Set(SCR_CTI_Constants.TOOLKIT, 1);
		itemMapM151.Set(SCR_CTI_Constants.EXTINGUISHER, 1);
		itemMapM151.Set(SCR_CTI_Constants.US_BACKPACK, 2);
		
		// M923 Items
		map<ResourceName, int> itemMapM923 = new map<ResourceName, int>();
		itemMapM923.Set(SCR_CTI_Constants.US_BANDAGE, 5);
		itemMapM923.Set(SCR_CTI_Constants.US_M16_MAG, 10);
		itemMapM923.Set(SCR_CTI_Constants.US_M72, 9);
		itemMapM923.Set(SCR_CTI_Constants.US_GRENADE, 4);
		itemMapM923.Set(SCR_CTI_Constants.TOOLKIT, 1);
		itemMapM923.Set(SCR_CTI_Constants.EXTINGUISHER, 1);
		itemMapM923.Set(SCR_CTI_Constants.US_BACKPACK, 2);
		
		// M923 MHQ items
		map<ResourceName, int> intemMapM923MHQ = new map<ResourceName, int>();
		intemMapM923MHQ.Set(SCR_CTI_Constants.US_BANDAGE, 5);
		intemMapM923MHQ.Set(SCR_CTI_Constants.TOOLKIT, 1);
		intemMapM923MHQ.Set(SCR_CTI_Constants.EXTINGUISHER, 1);
		intemMapM923MHQ.Set(SCR_CTI_Constants.US_BACKPACK, 2);
		
		if (m_ussrAtNorth)
		{
			// UAZ + equipment
			svNorth1.addItemsPrefab(itemMapUaz);
			svNorth1.spawnPrefab(SCR_CTI_Constants.USSR_UAZ);
			
			// Ural truck + equipment
			svNorth2.addItemsPrefab(itemMapUral);
			svNorth2.spawnPrefab(SCR_CTI_Constants.USSR_TRUCK);
			
			// USSR MHQ + equipment
			svNorth3.addItemsPrefab(intemMapUralMHQ);
			svNorth3.spawnPrefab(SCR_CTI_Constants.USSR_MHQ);
			
			// Jeep + equipment
			svSouth1.addItemsPrefab(itemMapM151);
			svSouth1.spawnPrefab(SCR_CTI_Constants.US_JEEP);
			
			// M923A1 truck + equipment
			svSouth2.addItemsPrefab(itemMapM923);
			svSouth2.spawnPrefab(SCR_CTI_Constants.US_TRUCK);
			
			// US MHQ + equipment
			svSouth3.addItemsPrefab(intemMapM923MHQ);
			svSouth3.spawnPrefab(SCR_CTI_Constants.US_MHQ);
		} else {
			// Jeep + equipment
			svNorth1.addItemsPrefab(itemMapM151);
			svNorth1.spawnPrefab(SCR_CTI_Constants.US_JEEP);

			// M923A1 truck + equipment
			svNorth2.addItemsPrefab(itemMapM923);
			svNorth2.spawnPrefab(SCR_CTI_Constants.US_TRUCK);
			
			// US MHQ + equipment
			svNorth3.addItemsPrefab(intemMapM923MHQ);
			svNorth3.spawnPrefab(SCR_CTI_Constants.US_MHQ);
			
			// UAZ + equipment
			svSouth1.addItemsPrefab(itemMapUaz);
			svSouth1.spawnPrefab(SCR_CTI_Constants.USSR_UAZ);
			
			// Ural truck + equipment
			svSouth2.addItemsPrefab(itemMapUral);
			svSouth2.spawnPrefab(SCR_CTI_Constants.USSR_TRUCK);
			
			// USSR MHQ + equipment
			svSouth3.addItemsPrefab(intemMapUralMHQ);
			svSouth3.spawnPrefab(SCR_CTI_Constants.USSR_MHQ);
		}
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