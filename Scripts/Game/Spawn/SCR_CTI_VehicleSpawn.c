[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Vehicle Spawn")]
class SCR_CTI_VehicleSpawn : SCR_BasePrefabSpawner
{
	protected Vehicle m_spawnedVehicle;
	protected FactionKey m_factionkey;
	protected ref array<IEntity> m_items = {};
	protected bool m_isMHQ = false;
	protected ResourceName USSR_mhq = "{BF0C29DFC138F59A}Prefabs/Vehicles/Wheeled/Ural4320/CTI_HQ_Ural4320_command.et";
	protected ResourceName US_mhq = "{00E39778A1A7C9E5}Prefabs/Vehicles/Wheeled/M923A1/CTI_HQ_M923A1_command.et";
	
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
	}
	
	protected override bool CanSpawn()
	{
		return !m_spawnedVehicle;
	}

	protected override void OnSpawn(IEntity newEnt)
	{
		m_spawnedVehicle = Vehicle.Cast(newEnt);
		
		if (!m_items) return; // Check if items array is not null
		insertItem(m_spawnedVehicle);
		
		if (m_rnPrefab == USSR_mhq || m_rnPrefab == US_mhq)
		{
			GarbageManager garbagemanager = GetGame().GetGarbageManager();
			if (!garbagemanager) { Print("CTI :: Garbage manager not found!"); return; }
			
			PrintFormat("CTI :: MHQ in garbage manager: %1 (%2)", garbagemanager.IsInserted(newEnt).ToString(), m_rnPrefab);
			
			//garbagemanager.Bump(newEnt, -1);

			PrintFormat("CTI :: MHQ wreck lifetime: %1 (%2)", garbagemanager.GetLifetime(newEnt), m_rnPrefab);
		}
	}

	void setPrefab(ResourceName newPrefab)
	{
		m_rnPrefab = newPrefab;
	}
	
	void addItemPrefab(ResourceName prefab)
	{
		Resource res = Resource.Load(prefab);
		IEntity item = GetGame().SpawnEntityPrefab(res, GetWorld());
		m_items.Insert(item);
	}
	
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