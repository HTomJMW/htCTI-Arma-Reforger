[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Workers")]
class SCR_CTI_UpdateWorkersComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateWorkersComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;
	protected SCR_CTI_BaseComponent m_baseComponent;

	ref array<IEntity> m_ussrWorkers = {};
	ref array<IEntity> m_usWorkers = {};

	[RplProp()]
	protected int m_ussrWorkersCount = 0;
	[RplProp()]
	protected int m_usWorkersCount = 0;
	
	protected const float TIMESTEP = 20;
	
	//------------------------------------------------------------------------------------------------
	//server only
	void addWorker(FactionKey factionkey)
	{
		if (m_rplComponent.IsProxy()) return;

		IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(factionkey);
		vector mat[4];
		mhq.GetTransform(mat);
		
		RandomGenerator randomgen = new RandomGenerator();
		vector rndpos = randomgen.GenerateRandomPointInRadius(4, 8, mat[3], true);
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		ResourceName workerResName;
		switch (factionkey)
		{
			case "USSR": workerResName = SCR_CTI_Constants.USSR_WORKER; break;
			case "US": workerResName = SCR_CTI_Constants.US_WORKER; break;
		}

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;

		IEntity worker = GetGame().SpawnEntityPrefab(Resource.Load(workerResName), GetGame().GetWorld(), params);

		if (worker)
		{
			SCR_AIGroup aiGroup = SCR_AIGroup.Cast(GetGame().SpawnEntityPrefab(Resource.Load("{000CD338713F2B5A}Prefabs/AI/Groups/Group_Base.et"), GetGame().GetWorld()));
			aiGroup.SetFaction(GetGame().GetFactionManager().GetFactionByKey(factionkey));
			aiGroup.AddAIEntityToGroup(worker, 0);
			aiGroup.SetPrivate(true);
			
			switch (factionkey)
			{
				case "USSR": m_ussrWorkers.Insert(worker); m_ussrWorkersCount++; break;
				case "US": m_usWorkers.Insert(worker); m_usWorkersCount++; break;
			}
			
			EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(worker.FindComponent(EventHandlerManagerComponent));
			if (ehManager)
			{
				ehManager.RegisterScriptHandler("OnDestroyed", this, OnDestroyed);
			}

			m_gameMode.changeCommanderFunds(factionkey, -SCR_CTI_Constants.WORKERPRICE);
			
			Replication.BumpMe();
		}
	}

	//------------------------------------------------------------------------------------------------
	int getWorkersCount(FactionKey factionkey)
	{
		int workersCount = 0;

		switch (factionkey)
		{
			case "USSR":
			{
				workersCount = m_ussrWorkersCount;
				break;
			}
			case "US":
			{
				workersCount = m_usWorkersCount;
				break;
			}
		}
		
		return workersCount;
	}

	//------------------------------------------------------------------------------------------------
	protected void OnDestroyed(IEntity ent)
	{
		if (m_rplComponent.IsProxy()) return;
		
		FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		switch (faffComp.GetDefaultAffiliatedFaction().GetFactionKey())
		{
			case "USSR": m_ussrWorkersCount--; break;
			case "US": m_usWorkersCount--; break;
		}
		
		Replication.BumpMe();
		
		EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(ent.FindComponent(EventHandlerManagerComponent));
		if (ehManager)
		{
			ehManager.RemoveScriptHandler("OnDestroyed", this, OnDestroyed);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void workersLoop()
	{
		if (m_ussrWorkersCount > 0)
		{
			array<RplId> ussrWIPStructures = m_baseComponent.getUSSRWIPStructureRplIdArray();
			if (!ussrWIPStructures.IsEmpty())
			{
				RplComponent rplComp = RplComponent.Cast(Replication.FindItem(ussrWIPStructures[0]));
				IEntity wipStructure = rplComp.GetEntity();
			
				foreach (IEntity worker : m_ussrWorkers)
				{
					if (!wipStructure || !worker) break;

					CharacterControllerComponent ccc = CharacterControllerComponent.Cast(worker.FindComponent(CharacterControllerComponent));

					int distance = vector.Distance(worker.GetOrigin(), wipStructure.GetOrigin());

					switch (true)
					{
						case (distance <= SCR_CTI_Constants.WORKERSERVICERANGE && distance > SCR_CTI_Constants.WORKERBUILDRANGE):
						{
							Print("CTI :: Distance < 250m, Not in BuildRange!");
							IEntity child = wipStructure.GetChildren();
							while (child)
							{
								SCR_AIWaypoint waypoint = SCR_AIWaypoint.Cast(child);
								if (waypoint)
								{
									waypoint.SetCompletionRadius(25);

									AIControlComponent AIController = AIControlComponent.Cast(worker.FindComponent(AIControlComponent));
									AIController.ActivateAI();
									AIAgent agent = AIAgent.Cast(AIController.GetControlAIAgent());
									if (!agent) break;
									SCR_AIGroup group = SCR_AIGroup.Cast(agent.GetParentGroup());
									group.Activate();
									if (!group.GetCurrentWaypoint()) group.AddWaypoint(waypoint);
									break;
								} else {
									child = child.GetSibling();
								}
							}
							break;
						}
						case (distance <= SCR_CTI_Constants.WORKERBUILDRANGE):
						{
							Print("CTI :: Worker in Range!");
							RandomGenerator randomgen = new RandomGenerator();
							Math.Randomize(-1);
							int random = randomgen.RandIntInclusive(0, 1);
							if (random == 0)
							{
								ccc.TryStartCharacterGesture(ECharacterGestures.POINT_WITH_FINGER, 10000);
							} else {
								ccc.SetStanceChange(2);
								ccc.TryPlayItemGesture(EItemGesture.EItemGesturePickUp);
							}

							SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(wipStructure.FindComponent(SCR_CTI_StructureCompletionComponent));
							if (scc.getCompletionValue() < 100)
							{
								PrintFormat("CTI :: Completion: %1", scc.getCompletionValue());
								scc.setCompletionValue(scc.getCompletionValue() + 5);
								Replication.BumpMe();
							} else {
								vector mat[4];
								wipStructure.GetTransform(mat);

								int index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(wipStructure.GetPrefabData().GetPrefabName());
								SCR_CTI_FactoryData factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];

								foreach (IEntity ussrWorker : m_ussrWorkers)
								{
									if (!ussrWorker) break;
									AIControlComponent AIController = AIControlComponent.Cast(ussrWorker.FindComponent(AIControlComponent));
									AIAgent agent = AIAgent.Cast(AIController.GetControlAIAgent());
									if (!agent) break;
									SCR_AIGroup group = SCR_AIGroup.Cast(agent.GetParentGroup());
									AIWaypoint waypoint = group.GetCurrentWaypoint();
									if (waypoint) group.RemoveWaypoint(waypoint);
									
									CharacterControllerComponent workerccc = CharacterControllerComponent.Cast(ussrWorker.FindComponent(CharacterControllerComponent));
									workerccc.SetStanceChange(1);
								}

								SCR_EntityHelper.DeleteEntityAndChildren(wipStructure);
								m_baseComponent.removeWIPStructureRplId("USSR", ussrWIPStructures[0]);

								SCR_CTI_BuildStructure buildstructure = new SCR_CTI_BuildStructure();
								buildstructure.build("USSR", factoryData.getResName(), mat);
								Print("CTI :: Construction Complete!");
							}
							break;
						}
					}
				}
			}
		}

		if (m_usWorkersCount > 0)
		{
			array<RplId> usWIPStructures = m_baseComponent.getUSWIPStructureRplIdArray();
			if (!usWIPStructures.IsEmpty())
			{
				RplComponent rplComp = RplComponent.Cast(Replication.FindItem(usWIPStructures[0]));
				IEntity wipStructure = rplComp.GetEntity();
			
				foreach (IEntity worker : m_usWorkers)
				{
					if (!wipStructure || !worker) break;

					CharacterControllerComponent ccc = CharacterControllerComponent.Cast(worker.FindComponent(CharacterControllerComponent));

					int distance = vector.Distance(worker.GetOrigin(), wipStructure.GetOrigin());

					switch (true)
					{
						case (distance <= SCR_CTI_Constants.WORKERSERVICERANGE && distance > SCR_CTI_Constants.WORKERBUILDRANGE):
						{
							Print("CTI :: Distance < 250m, Not in BuildRange!");
							IEntity child = wipStructure.GetChildren();
							while (child)
							{
								SCR_AIWaypoint waypoint = SCR_AIWaypoint.Cast(child);
								if (waypoint)
								{
									waypoint.SetCompletionRadius(25);

									AIControlComponent AIController = AIControlComponent.Cast(worker.FindComponent(AIControlComponent));
									AIController.ActivateAI();
									AIAgent agent = AIAgent.Cast(AIController.GetControlAIAgent());
									if (!agent) break;
									SCR_AIGroup group = SCR_AIGroup.Cast(agent.GetParentGroup());
									group.Activate();
									if (!group.GetCurrentWaypoint()) group.AddWaypoint(waypoint);
									break;
								} else {
									child = child.GetSibling();
								}
							}
							break;
						}
						case (distance <= SCR_CTI_Constants.WORKERBUILDRANGE):
						{
							Print("CTI :: Worker in Range!");
							RandomGenerator randomgen = new RandomGenerator();
							Math.Randomize(-1);
							int random = randomgen.RandIntInclusive(0, 1);
							if (random == 0)
							{
								ccc.TryStartCharacterGesture(ECharacterGestures.POINT_WITH_FINGER, 10000);
							} else {
								ccc.SetStanceChange(2);
								ccc.TryPlayItemGesture(EItemGesture.EItemGesturePickUp);
							}
							
							SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(wipStructure.FindComponent(SCR_CTI_StructureCompletionComponent));
							if (scc.getCompletionValue() < 100)
							{
								PrintFormat("CTI :: Completion: %1", scc.getCompletionValue());
								scc.setCompletionValue(scc.getCompletionValue() + 5);
								Replication.BumpMe();
							} else {
								vector mat[4];
								wipStructure.GetTransform(mat);

								int index = m_gameMode.FactoriesUS.findIndexFromResourcename(wipStructure.GetPrefabData().GetPrefabName());
								SCR_CTI_FactoryData factoryData = m_gameMode.FactoriesUS.g_US_Factories[index];

								foreach (IEntity usWorker : m_usWorkers)
								{
									if (!usWorker) break;
									AIControlComponent AIController = AIControlComponent.Cast(usWorker.FindComponent(AIControlComponent));
									AIAgent agent = AIAgent.Cast(AIController.GetControlAIAgent());
									if (!agent) break;
									SCR_AIGroup group = SCR_AIGroup.Cast(agent.GetParentGroup());
									AIWaypoint waypoint = group.GetCurrentWaypoint();
									if (waypoint) group.RemoveWaypoint(waypoint);

									CharacterControllerComponent workerccc = CharacterControllerComponent.Cast(usWorker.FindComponent(CharacterControllerComponent));
									workerccc.SetStanceChange(1);
								}

								SCR_EntityHelper.DeleteEntityAndChildren(wipStructure);
								m_baseComponent.removeWIPStructureRplId("US", usWIPStructures[0]);

								SCR_CTI_BuildStructure buildstructure = new SCR_CTI_BuildStructure();
								buildstructure.build("US", factoryData.getResName(), mat);
								Print("CTI :: Construction Complete!");
							}
							break;
						}
					}
				}
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_rplComponent = RplComponent.Cast(m_gameMode.FindComponent(RplComponent));
		m_baseComponent = SCR_CTI_BaseComponent.Cast(m_gameMode.FindComponent(SCR_CTI_BaseComponent));

		GetGame().GetCallqueue().CallLater(workersLoop, TIMESTEP * 1000, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateWorkersComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(ent);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateWorkersComponent()
	{
		if (m_ussrWorkers) m_ussrWorkers.Clear();
		m_ussrWorkers = null;
		if (m_usWorkers) m_usWorkers.Clear();
		m_usWorkers = null;
	}
};