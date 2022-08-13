[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Vehicle Spawn")]
class SCR_CTI_VehicleSpawn : SCR_BasePrefabSpawner
{
	protected Vehicle m_spawnedVehicle;
	protected ref array<IEntity> m_items = {};
	
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
			IEntity item = GetGame().SpawnEntityPrefab(res, GetWorld());
			for (int i = 0; i < piece; i++)
			{
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
}

class SCR_CTI_VehicleSpawnClass : SCR_BasePrefabSpawnerClass
{
}