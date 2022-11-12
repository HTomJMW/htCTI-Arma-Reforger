[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Vehicle Spawn")]
class SCR_CTI_VehicleSpawn : SCR_BasePrefabSpawner
{
	protected Vehicle m_spawnedVehicle;
	protected FactionKey m_factionkey;
	protected ref array<IEntity> m_items = {};
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	protected override bool CanSpawn()
	{
		return !m_spawnedVehicle;
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnSpawn(IEntity newEnt)
	{
		m_spawnedVehicle = Vehicle.Cast(newEnt);
		
		if (m_items) insertItem(m_spawnedVehicle);
		
		GarbageManager garbagemanager = GetGame().GetGarbageManager();
		// todo add lifetime for support vehicles
		switch (m_rnPrefab)
		{
			case m_gameMode.USSRMHQ:
			{
				// Keep out of garbage manager
				newEnt.SetName(m_gameMode.USSRMHQNAME);
				break;
			}
			case m_gameMode.USMHQ:
			{
				// Keep out of garbage manager
				newEnt.SetName(m_gameMode.USMHQNAME);
				break;
			}
			default:
			{
				garbagemanager.Insert(newEnt, 3600);
				PrintFormat("CTI :: Default vehicle: %1", m_rnPrefab);
				break;
			}
		}
		PrintFormat("CTI :: Vehicle in garbage manager: %1 (%2)", garbagemanager.IsInserted(newEnt).ToString(), m_rnPrefab);
		PrintFormat("CTI :: Lifetime: %1 (%2)", garbagemanager.GetLifetime(newEnt), m_rnPrefab);
		
		Deactivate(); // Deactivate after vehicle spawned
	}

	//------------------------------------------------------------------------------------------------
	void setPrefab(ResourceName newPrefab)
	{
		m_rnPrefab = newPrefab;
	}

	//------------------------------------------------------------------------------------------------
	void addItemPrefab(ResourceName prefab)
	{
		Resource res = Resource.Load(prefab);
		IEntity item = GetGame().SpawnEntityPrefab(res, GetWorld());
		m_items.Insert(item);
	}

	//------------------------------------------------------------------------------------------------
	void addItemsPrefab(map<ResourceName, int> prefabMap)
	{
		foreach (ResourceName prefab, int piece : prefabMap)
		{
			Resource res = Resource.Load(prefab);
			for (int i = 0; i < piece; i++)
			{
				IEntity item = GetGame().SpawnEntityPrefab(res, GetWorld());
				m_items.Insert(item);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void insertItem(Vehicle veh)
	{
		InventoryStorageManagerComponent ismc = InventoryStorageManagerComponent.Cast(veh.FindComponent(SCR_VehicleInventoryStorageManagerComponent));
		
		foreach (IEntity item : m_items)
		{
			ismc.TryInsertItem(item);
		}
	}
};

class SCR_CTI_VehicleSpawnClass : SCR_BasePrefabSpawnerClass
{
};