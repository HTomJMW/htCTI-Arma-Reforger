[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Spawn AI groups")]
class SCR_CTI_CreateTeamComponentClass : ScriptComponentClass
{
};

class SCR_CTI_CreateTeamComponent : ScriptComponent
{
	protected RplComponent m_RplComponent;
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;

	[Attribute("", UIWidgets.EditBox, "Group spawn position.", params: "inf inf 0 0 purposeCoords spaceWorld")]
	protected vector m_SpawnPos;
	[Attribute("", UIWidgets.EditBox, "Group spawn direction. (only yaw used)", params: "inf inf 0 0 purposeAngles spaceWorld")]
	protected vector m_SpawnDir;
	
	//------------------------------------------------------------------------------------------------
	vector defaultCoords()
	{
		SCR_BaseTriggerEntity parent = SCR_BaseTriggerEntity.Cast(GetOwner());
		SCR_CTI_Town grandParent = SCR_CTI_Town.Cast(parent.GetParent());
		vector coords = grandParent.getFlagPos();
		
		return coords;
	}

	//------------------------------------------------------------------------------------------------
	vector GetSpawnPos()
	{
		if (m_SpawnPos == "0 0 0")
		{
			PrintFormat("CTI :: AI Spawn position is not set at %1! Flag's position will be default", m_town.getTownName());
			return defaultCoords();
		}
		
		return m_SpawnPos;
	}

	//------------------------------------------------------------------------------------------------
	vector GetSpawnDir()
	{
		return Vector(0.0, m_SpawnDir[1], 0.0);
	}

	//------------------------------------------------------------------------------------------------
	void GetSpawnTransform(out vector transformMatrix[4])
	{
		vector rotation = GetSpawnDir();
		vector yawPitchRoll = Vector(rotation[1], rotation[0], rotation[2]);
		Math3D.AnglesToMatrix(rotation, transformMatrix);		
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, GetSpawnPos(), 3);
		transformMatrix[3] = emptyPos;
	}

	//------------------------------------------------------------------------------------------------
	bool DoSpawn(ResourceName aiAgentPrefab, array<string> wayPoints = null)
	{
		if (!VerifyRplComponentPresent())
		{			
			Print("RPL Component missing!");
			return false;
		}
		
		Resource agentPrefab = Resource.Load(aiAgentPrefab);
		if (!agentPrefab)
		{
			Print("AgentPrefab load failed!");
			return false;
		}
		
		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.TransformMode = ETransformMode.WORLD;
		GetSpawnTransform(spawnParams.Transform);
		
		IEntity spawnedEntity = GetGame().SpawnEntityPrefab(agentPrefab, GetOwner().GetWorld(), spawnParams);
		if (!spawnedEntity)
		{
			Print("Spawn Failed!");
			return false;
		}

		AIAgent agent = AIAgent.Cast(spawnedEntity);
		if (!agent)
		{
			Print("AI Agent type fail!");
			RplComponent.DeleteRplEntity(spawnedEntity, false);
			return false;
		}

		SCR_AIGroup aiGroup = SCR_AIGroup.Cast(agent);
		
		if (aiGroup)
		{
			m_town.m_townGroups.Insert(aiGroup);
			
			//Set AI Skill
			SCR_AIConfigComponent aiConfigComponent = SCR_AIConfigComponent.Cast(aiGroup.FindComponent(SCR_AIConfigComponent));
			aiConfigComponent.m_Skill = SCR_CTI_Constants.AISKILL; // AI combat component skill better?
		}
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	bool SpawnVehicle(ResourceName resourceName)
	{
		if (!VerifyRplComponentPresent())
		{			
			Print("RPL Component missing!");
			return false;
		}
		
		Resource resource = Resource.Load(resourceName);
		if (!resource)
		{
			Print("Vehicle prefab load failed!");
			return false;
		}
		
		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.TransformMode = ETransformMode.WORLD;		
		GetSpawnTransform(spawnParams.Transform);
		
		IEntity spawnedEntity = GetGame().SpawnEntityPrefab(resource, GetOwner().GetWorld(), spawnParams);
		if (!spawnedEntity)
		{
			Print("Spawn Failed!");
			return false;
		}

		Vehicle vehicle = Vehicle.Cast(spawnedEntity);
		if (!vehicle)
		{
			Print("Vehicle type fail!");
			RplComponent.DeleteRplEntity(spawnedEntity, false);
			return false;
		}
		
		SCR_VehicleFactionAffiliationComponent vfac = SCR_VehicleFactionAffiliationComponent.Cast(spawnedEntity.FindComponent(SCR_VehicleFactionAffiliationComponent));
		ResourceName resName;
		
		switch (vfac.GetDefaultAffiliatedFaction().GetFactionKey())
		{
			case "FIA": resName = SCR_CTI_Constants.FIA_SOLDIER; break;
			case "USSR": resName = SCR_CTI_Constants.USSR_SOLDIER; break;
			case "US": resName = SCR_CTI_Constants.US_SOLDIER; break;
		}
		
		SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(spawnedEntity.FindComponent(SCR_BaseCompartmentManagerComponent));
		array<ECompartmentType> compartmentTypes = {ECompartmentType.Pilot, ECompartmentType.Turret};
		//bcmc.SpawnDefaultOccupants(compartmentTypes); // TODO FIX SIDE problem

		// Temporary fix maybe need merge later
		array<BaseCompartmentSlot> outCompartments = {};
		bcmc.GetCompartments(outCompartments);
		
		AIGroup vehGroup;
		foreach (BaseCompartmentSlot slot : outCompartments)
		{
			if (compartmentTypes.Contains(slot.GetType())) slot.SpawnCharacterInCompartment(resName, vehGroup);
		}

		/*array<IEntity> occupants = {};
		bcmc.GetOccupants(occupants);

		foreach (IEntity crew : occupants)
		{
			AIAgent agent = AIAgent.Cast(crew);
			if (agent) vehGroup.AddAgent(agent);
		}*/

		//m_town.m_groups.Insert(vehGroup);

		return true;
	}

	//------------------------------------------------------------------------------------------------
#ifdef WORKBENCH
	protected override void _WB_AfterWorldUpdate(IEntity owner, float timeSlice)
	{
		super._WB_AfterWorldUpdate(owner, timeSlice);
		
		vector spawnPosition = GetSpawnPos();
		Shape shape = Shape.CreateSphere(COLOR_YELLOW, ShapeFlags.ONCE | ShapeFlags.NOOUTLINE, spawnPosition, 0.3);
		Shape arrow = Shape.CreateArrow(GetOwner().GetOrigin(), spawnPosition, 0.1, COLOR_YELLOW, ShapeFlags.ONCE);
	}
#endif

	//------------------------------------------------------------------------------------------------
	protected bool VerifyRplComponentPresent()
	{
		if (!m_RplComponent)
		{
			Print("RPL Component missing!");
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------------------
	// Server only
	void OnTriggerActivate()
	{
		if (m_RplComponent.IsProxy()) return;
		
		m_town.m_townGroups.Clear();

		SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(m_gameMode.FindComponent(SCR_CTI_UpgradeComponent));
		int TO1index = m_gameMode.Upgrades.findIndexByName("Towns Occupation Level 1");
		int TO2index = m_gameMode.Upgrades.findIndexByName("Towns Occupation Level 2");
		int TO3index = m_gameMode.Upgrades.findIndexByName("Towns Occupation Level 3");

		int rnd = Math.RandomIntInclusive(0,5);
		switch (m_town.getFactionKey())
		{
			case "FIA":
			{
				DoSpawn(SCR_CTI_Constants.FIA_FireTeam);

				// First match will break, bigger value need upper
				switch (true)
				{
					case (m_town.getTownValue() > 300):
					{
						DoSpawn(SCR_CTI_Constants.FIA_ATTeam);
						DoSpawn(SCR_CTI_Constants.FIA_SniperTeam);
						SpawnVehicle(SCR_CTI_Constants.FIA_BTR70);
						break;
					}
					case (m_town.getTownValue() > 250):
					{
						DoSpawn(SCR_CTI_Constants.FIA_ATTeam);
						SpawnVehicle(SCR_CTI_Constants.FIA_UAZ_PKM);
						break;
					}
					case (m_town.getTownValue() > 200):
					{
						DoSpawn(SCR_CTI_Constants.FIA_ATTeam);
						SpawnVehicle(SCR_CTI_Constants.FIA_UAZ_UK_59);
						break;
					}
				}

				switch (rnd)
				{
					case 0: DoSpawn(SCR_CTI_Constants.FIA_MGTeam); break;
					case 1:	DoSpawn(SCR_CTI_Constants.FIA_SniperTeam); break;
					case 2:	DoSpawn(SCR_CTI_Constants.FIA_ATTeam); break;
					case 3:	DoSpawn(SCR_CTI_Constants.FIA_MedicalSection); break;
					case 4:	DoSpawn(SCR_CTI_Constants.FIA_ReconTeam); break;
					case 5:	DoSpawn(SCR_CTI_Constants.FIA_ATTeam); break;
				}
				break;
			}
			case "USSR":
			{
				UpgradeStatus status = upgradeComp.getUpgradeStatus("USSR", TO1index);
				if (status != UpgradeStatus.FINISHED) break;

				DoSpawn(SCR_CTI_Constants.USSR_FireGroup);
				if (m_town.getTownValue() > 250 && upgradeComp.getUpgradeStatus("USSR", TO2index) == UpgradeStatus.FINISHED) DoSpawn(SCR_CTI_Constants.USSR_ATTeam);
				if (m_town.getTownValue() > 300 && upgradeComp.getUpgradeStatus("USSR", TO3index) == UpgradeStatus.FINISHED) DoSpawn(SCR_CTI_Constants.USSR_MGTeam);
				switch (rnd)
				{
					case 0: DoSpawn(SCR_CTI_Constants.USSR_MGTeam); break;
					case 1:	DoSpawn(SCR_CTI_Constants.USSR_GLTeam); break;
					case 2:	DoSpawn(SCR_CTI_Constants.USSR_ATTeam); break;
					case 3:	DoSpawn(SCR_CTI_Constants.USSR_MedicalSection); break;
					case 4:	DoSpawn(SCR_CTI_Constants.USSR_ManeuverGroup); break;
					case 5:	DoSpawn(SCR_CTI_Constants.USSR_ATTeam); break;
				}

				status = upgradeComp.getUpgradeStatus("USSR", TO2index);
				if (status == UpgradeStatus.FINISHED) SpawnVehicle(SCR_CTI_Constants.USSR_BTR70);

				break;
			}
			case "US":
			{
				UpgradeStatus status = upgradeComp.getUpgradeStatus("US", TO1index);
				if (status != UpgradeStatus.FINISHED) break;

				DoSpawn(SCR_CTI_Constants.US_FireTeam);
				if (m_town.getTownValue() > 250 && upgradeComp.getUpgradeStatus("US", TO2index) == UpgradeStatus.FINISHED) DoSpawn(SCR_CTI_Constants.US_ATTeam);
				if (m_town.getTownValue() > 300 && upgradeComp.getUpgradeStatus("US", TO3index) == UpgradeStatus.FINISHED) DoSpawn(SCR_CTI_Constants.US_MGTeam);
				switch (rnd)
				{
					case 0: DoSpawn(SCR_CTI_Constants.US_MGTeam); break;
					case 1:	DoSpawn(SCR_CTI_Constants.US_GLTeam); break;
					case 2:	DoSpawn(SCR_CTI_Constants.US_ATTeam); break;
					case 3:	DoSpawn(SCR_CTI_Constants.US_MedicalSection); break;
					case 4:	DoSpawn(SCR_CTI_Constants.US_SniperTeam); break;
					case 5:	DoSpawn(SCR_CTI_Constants.US_ATTeam); break;
				}

				status = upgradeComp.getUpgradeStatus("US", TO2index);
				if (status == UpgradeStatus.FINISHED) SpawnVehicle(SCR_CTI_Constants.US_M1025_M2);

				break;
			}
		}
		PrintFormat("CTI :: Town %1 (%2) - Spawned groups: %3", m_town.getTownName(), m_town.getFactionKey(), m_town.m_townGroups);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		if (!VerifyRplComponentPresent())
			return;

		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		SCR_CTI_ActivationArea parent = SCR_CTI_ActivationArea.Cast(owner);
		if (!parent)
		{
			Print("Must be SCR_CTI_ActivationArea component!");
			return;
		}
		
		m_town = SCR_CTI_Town.Cast(GetOwner().GetParent());
		m_town.m_townGroups.Clear();
		
		m_gameMode = SCR_CTI_GameMode.GetInstance();
	}

	//------------------------------------------------------------------------------------------------	
	void SCR_CTI_CreateTeamComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_CreateTeamComponent()
	{
	}
};