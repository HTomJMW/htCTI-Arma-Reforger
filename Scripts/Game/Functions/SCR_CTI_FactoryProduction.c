class SCR_CTI_FactoryProduction
{
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	void build(ResourceName resourcename, FactionKey factionkey, EntityID groupID, RplId factRplId, vector mat[4], int playerId, int buildTime, CTI_PurchaseInfos purchaseInfo)
	{
		SCR_CTI_PurchaseInfoCoder infoCoder = new SCR_CTI_PurchaseInfoCoder();
		bool driver, gunner, commander, crew, locked;
		infoCoder.deCode(driver, gunner, commander, crew, locked, purchaseInfo);
		PrintFormat("%1, %2, %3, %4, %5", driver.ToString(), gunner.ToString(), commander.ToString(), crew.ToString(), locked.ToString());

		RplComponent factRplComp = RplComponent.Cast(Replication.FindItem(factRplId));
		IEntity factory = factRplComp.GetEntity(); // TODO Is alive?

		IEntity entity = null;

		Resource resource = Resource.Load(resourcename);

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;

		entity = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		
		if (entity)
		{
			int gridX, gridZ;
			SCR_MapEntity.GetGridPos(entity.GetOrigin(), gridX, gridZ);
			PrintFormat("CTI :: Entity spawned: %1, Pos: %2 (GRID: %3)", entity, entity.GetOrigin(), gridX.ToString() + ", " + gridZ.ToString());
			
			// TODO temporary -> 180deg turn
			vector angles = entity.GetAngles();
			angles[1] = angles[1] + 180;
			entity.SetAngles(angles);

			AIControlComponent AgentControlComponent = AIControlComponent.Cast(entity.FindComponent(AIControlComponent));
			AIAgent agent = null;
			if (AgentControlComponent)
			{
				AgentControlComponent.ActivateAI();
				agent = AgentControlComponent.GetControlAIAgent();
			}
			
			AIGroup group = AIGroup.Cast(GetGame().GetWorld().FindEntityByID(groupID));
			if (agent && group) group.AddAgent(agent);

			SCR_VehicleSpawnProtectionComponent vspc = SCR_VehicleSpawnProtectionComponent.Cast(entity.FindComponent(SCR_VehicleSpawnProtectionComponent));
			if (vspc) vspc.SetVehicleOwner(playerId);
			
			SCR_BaseLockComponent blc = SCR_BaseLockComponent.Cast(entity.FindComponent(SCR_BaseLockComponent));
			if (blc) if (locked) blc.lockVehicle(true);
			
			if (gunner)
			{
				//Temporary, need check turrent on client.
				SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(entity.FindComponent(SCR_BaseCompartmentManagerComponent));
				if (bcmc)
				{
					array<ECompartmentType> compartmentTypes = {ECompartmentType.Turret};
					bcmc.SpawnDefaultOccupants(compartmentTypes);
				}
			}
			
			Vehicle vehicle = Vehicle.Cast(entity);
			if (vehicle) removeSupplyBoxes(vehicle);

			SCR_CTI_UnitData unitData;
			int index = -1;
			switch (factionkey)
			{
				case "USSR":
				{
					index = m_gameMode.UnitsUSSR.findIndexFromResourcename(resourcename);
					unitData = m_gameMode.UnitsUSSR.g_USSR_Units[index];
					break;
				}
				case "US":
				{
					index = m_gameMode.UnitsUS.findIndexFromResourcename(resourcename);
					unitData = m_gameMode.UnitsUS.g_US_Units[index];
					break;
				}
			}

			m_gameMode.SendHint(playerId, "Your <color rgba='255,210,115,255'>" + unitData.getName() + "</color> has arrived from the <color rgba='255,210,115,255'>" + unitData.getFactory() + "</color> at grid <color rgba='255,210,115,255'>[" + gridX.ToString() + ", " + gridZ.ToString() + "]</color>.", "Information", 15);
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
			            // Force change value event
			            rc.SetResourceValueEx(100);
			            rc.SetResourceValueEx(0);
			        }
				}
		    }
		
		    child = child.GetSibling();
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_FactoryProduction()
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_FactoryProduction()
	{
	}
};