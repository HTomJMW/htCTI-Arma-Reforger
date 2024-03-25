[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Startup Vehicle Spawner")]
class SCR_CTI_VehicleSpawnClass : GenericEntityClass
{
};

class SCR_CTI_VehicleSpawn : GenericEntity
{
	protected Vehicle m_spawnedVehicle;
	
	protected ref array<IEntity> m_items = {};

	//------------------------------------------------------------------------------------------------
	void spawnPrefab(ResourceName resName)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		
		Resource resource = Resource.Load(resName);

		vector transform[4];
		GetTransform(transform);

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = transform;

		IEntity newEnt = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		m_spawnedVehicle = Vehicle.Cast(newEnt);

		if (m_spawnedVehicle)
		{
			CarControllerComponent_SA carController = CarControllerComponent_SA.Cast(m_spawnedVehicle.FindComponent(CarControllerComponent_SA));
			if (carController) carController.SetPersistentHandBrake(true);
		
			Physics physicsComponent = m_spawnedVehicle.GetPhysics();
			if (physicsComponent) physicsComponent.SetVelocity("0 -1 0");

			if (m_items) insertItem(m_spawnedVehicle);
		
			removeSupplyBoxes(m_spawnedVehicle);

			ChimeraWorld world = newEnt.GetWorld();
			GarbageSystem garbageSystem = world.GetGarbageSystem();

			switch (resName)
			{
				case SCR_CTI_Constants.USSR_MHQ:
				{
					RplId rplId = Replication.FindId(newEnt);
					gameMode.setMHQrplId("USSR", rplId);

					garbageSystem.Insert(newEnt);
					garbageSystem.Withdraw(newEnt); // UpdateVictory Component handles MHQ lifetime

					IEntity child = newEnt.GetChildren();
					while (child)
					{
						SCR_SpawnPoint spawnPoint = SCR_SpawnPoint.Cast(child);
						if (spawnPoint)
						{
							spawnPoint.setDisplayName("USSR MHQ");
							break;
						}

						child = child.GetSibling();
					}

					break;
				}
				case SCR_CTI_Constants.US_MHQ:
				{
					RplId rplId = Replication.FindId(newEnt);
					gameMode.setMHQrplId("US", rplId);
	
					garbageSystem.Insert(newEnt);
					garbageSystem.Withdraw(newEnt); // UpdateVictory Component handles MHQ lifetime
	
					IEntity child = newEnt.GetChildren();
					while (child)
					{
						SCR_SpawnPoint spawnPoint = SCR_SpawnPoint.Cast(child);
						if (spawnPoint)
						{
							spawnPoint.setDisplayName("US MHQ");
							break;
						}
	
						child = child.GetSibling();
					}
	
					break;
				}
				default:
				{
					garbageSystem.Insert(newEnt, SCR_CTI_Constants.VEHICLECOLLECTIONTIME);
					garbageSystem.Withdraw(newEnt); // First GetIn event will start GM countdown timer
					//PrintFormat("CTI :: Default vehicle: %1", resName);
					break;
				}
			}
			//PrintFormat("CTI :: DEBUG :: Vehicle in garbage manager: %1 (%2)", garbageSystem.IsInserted(newEnt).ToString(), resName);
			//PrintFormat("CTI :: DEBUG :: Lifetime: %1 (%2)", garbageSystem.GetLifetime(newEnt), resName);
	
			if (m_items) m_items.Clear();
			m_items = null;
		} else {
			Print("CTI :: DEBUG :: VehicleSpawner did not created vehicle!");
		}
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
		UniversalInventoryStorageComponent uisc = UniversalInventoryStorageComponent.Cast(veh.FindComponent(UniversalInventoryStorageComponent));

		foreach (IEntity item : m_items)
		{
			//ismc.TryInsertItem(item); // Items may stacked
			ismc.TryInsertItemInStorage(item, uisc);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void removeSupplyBoxes(Vehicle veh)
	{
		IEntity child = veh.GetChildren();
		while (child)
		{
		    SCR_ResourceComponent resourceComponent = SCR_ResourceComponent.Cast(child.FindComponent(SCR_ResourceComponent));
		    if (resourceComponent)
		    {
		        array<SCR_ResourceContainer> containers = resourceComponent.GetContainers();
				if (containers)
				{
					foreach(SCR_ResourceContainer rc : containers)
					{
			            // Force change value event (TODO need test after updates, maybe not need)
			            rc.SetResourceValue(100, false);
			            rc.SetResourceValue(0, false);
			        }
				}
		    }
		
		    child = child.GetSibling();
		}
	}
};