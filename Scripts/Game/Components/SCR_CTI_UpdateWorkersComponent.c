[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Workers")]
class SCR_CTI_UpdateWorkersComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateWorkersComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;
	protected SCR_CTI_BaseComponent m_baseComponent;

	[RplProp()]
	protected int m_ussrWorkersCount = 0;
	[RplProp()]
	protected int m_usWorkersCount = 0;
	
	[RplProp()]
	ref array<RplId> m_ussrWorkerRplIds = {};
	[RplProp()]
	ref array<RplId> m_usWorkerRplIds = {};
	
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
			aiGroup.AddAIEntityToGroup(worker);
			aiGroup.SetPrivate(true);
			
			RplComponent workerRplComp = RplComponent.Cast(worker.FindComponent(RplComponent));
			RplId workerRplId = workerRplComp.Id(); 
			
			int cid = m_gameMode.getCommanderId(factionkey);
			RplIdentity commIdentity = GetGame().GetPlayerManager().GetPlayerController(cid).GetRplIdentity();
			workerRplComp.EnableStreamingForConnection(commIdentity, true);
			
			switch (factionkey)
			{
				case "USSR": m_ussrWorkersCount++; m_ussrWorkerRplIds.Insert(workerRplId); break;
				case "US": m_usWorkersCount++; m_usWorkerRplIds.Insert(workerRplId); break;
			}
			
			EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(worker.FindComponent(EventHandlerManagerComponent));
			if (ehManager)
			{
				ehManager.RegisterScriptHandler("OnDestroyed", this, OnDestroyed);
			}
			
			takeBuildingToolToHand(worker);

			m_gameMode.changeCommanderFunds(factionkey, -SCR_CTI_Constants.WORKERPRICE);
			
			Replication.BumpMe();
		}
	}

	//------------------------------------------------------------------------------------------------
	// Server only
	void disbandWorker(FactionKey factionkey, RplId rplId)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplId));
		IEntity worker = rplComp.GetEntity();
		
		switch (factionkey)
		{
			case "USSR":
			{
				if (m_ussrWorkerRplIds.Contains(rplId))
				{
					m_ussrWorkerRplIds.RemoveItem(rplId);
					m_ussrWorkersCount--;
					break;
				}
			}
			case "US":
			{
				if (m_usWorkerRplIds.Contains(rplId))
				{
					m_usWorkerRplIds.RemoveItem(rplId);
					m_usWorkersCount--;
					break;
				}
			}
		}
		
		Replication.BumpMe();
		
		SCR_EntityHelper.DeleteEntityAndChildren(worker);
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
	void takeBuildingToolToHand(notnull IEntity worker)
	{
		bool hasShovel = false;
		array<IEntity> shovels = {};
		SCR_PrefabNamePredicate predicateUSSR = new SCR_PrefabNamePredicate();
		SCR_PrefabNamePredicate predicateUS = new SCR_PrefabNamePredicate();
		predicateUSSR.prefabName = SCR_CTI_Constants.USSR_SHOVEL;
		predicateUS.prefabName = SCR_CTI_Constants.US_SHOVEL;
		SCR_InventoryStorageManagerComponent ismc;
		ismc = SCR_InventoryStorageManagerComponent.Cast(worker.FindComponent(SCR_InventoryStorageManagerComponent));
		if (ismc)
		{
			ismc.FindItems(shovels, predicateUSSR, EStoragePurpose.PURPOSE_ANY);
			ismc.FindItems(shovels, predicateUS, EStoragePurpose.PURPOSE_ANY);
		}
		if (!shovels.IsEmpty()) hasShovel = true;

		if (hasShovel)
		{
			CharacterControllerComponent ccc = CharacterControllerComponent.Cast(worker.FindComponent(CharacterControllerComponent));
			ccc.TakeGadgetInLeftHand(shovels[0], EGadgetType.BUILDING_TOOL);
		} else {
			// add shovel if need
		}
	}
	
	//------------------------------------------------------------------------------------------------
	IEntity GetBuildingToolFromHand(notnull IEntity worker)
	{
		SCR_GadgetManagerComponent gadgetManager = SCR_GadgetManagerComponent.GetGadgetManager(worker);
		if (!gadgetManager) return null;

		return gadgetManager.GetHeldGadget();
	}
	
	//------------------------------------------------------------------------------------------------
	void startBuildingAction(IEntity worker)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(worker);
		if (!character) return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			if (charController.IsUsingItem()) return;
			
			// TODO utility.m_LookAction.LookAt

			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			int itemActionId = pAnimationComponent.BindCommand("CMD_Item_Action");
			charController.TryUseItemOverrideParams(GetBuildingToolFromHand(worker), false, true, itemActionId, 1, 0, int.MAX, 0, 0, false, null);
		}
	}

	//------------------------------------------------------------------------------------------------
	void stopBuildingAction(IEntity worker)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(worker);
		if (!character) return;

		CharacterControllerComponent charController = character.GetCharacterController();
		if (charController)
		{
			CharacterAnimationComponent pAnimationComponent = charController.GetAnimationComponent();
			CharacterCommandHandlerComponent cmdHandler = CharacterCommandHandlerComponent.Cast(pAnimationComponent.GetCommandHandler());
			if (cmdHandler) cmdHandler.FinishItemUse();
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnDestroyed(IEntity ent)
	{
		if (m_rplComponent.IsProxy()) return;
		
		RplComponent rplComp = RplComponent.Cast(ent.FindComponent(RplComponent));
		RplId rplid = rplComp.Id();
		
		FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		switch (faffComp.GetDefaultAffiliatedFaction().GetFactionKey())
		{
			case "USSR": m_ussrWorkersCount--; m_ussrWorkerRplIds.RemoveItem(rplid); break;
			case "US": m_usWorkersCount--; m_usWorkerRplIds.RemoveItem(rplid); break;
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
			foreach (RplId workerRplId : m_ussrWorkerRplIds)
			{
				RplComponent workerRplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
				IEntity ussrWorker = workerRplComp.GetEntity();
				if (!ussrWorker) continue;

				SCR_CharacterControllerComponent ccc = SCR_CharacterControllerComponent.Cast(ussrWorker.FindComponent(SCR_CharacterControllerComponent));
				if (ccc.IsUnconscious()) continue;

				if (m_baseComponent.ussrWIPStructureRplIds.IsEmpty())
				{
					stopBuildingAction(ussrWorker);
					ccc.SetStanceChange(1);

					continue;
				} else {
					array<IEntity> wipStructures = {};
					foreach (RplId wipStructureRplId : m_baseComponent.ussrWIPStructureRplIds)
					{
						RplComponent wipStructureRplComp = RplComponent.Cast(Replication.FindItem(wipStructureRplId));
						IEntity wipStructure = wipStructureRplComp.GetEntity();
						if (wipStructure) wipStructures.Insert(wipStructure);
					}

					IEntity closestWipStructure = SCR_CTI_GetClosestEntity.GetClosestEntity(ussrWorker, wipStructures);
					int distance = vector.Distance(ussrWorker.GetOrigin(), closestWipStructure.GetOrigin());

					switch (true)
					{
						case (distance <= SCR_CTI_Constants.WORKERSERVICERANGE && distance > SCR_CTI_Constants.WORKERBUILDRANGE):
						{
							Print("CTI :: Distance > 250m, Not in BuildRange!");
							
							stopBuildingAction(ussrWorker);
							ccc.SetStanceChange(1);

							IEntity child = closestWipStructure.GetChildren();
							while (child)
							{
								SCR_AIWaypoint waypoint = SCR_AIWaypoint.Cast(child);
								if (waypoint)
								{
									waypoint.SetCompletionRadius(25);

									AIControlComponent AIController = AIControlComponent.Cast(ussrWorker.FindComponent(AIControlComponent));
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

							takeBuildingToolToHand(ussrWorker);
							
							SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(closestWipStructure.FindComponent(SCR_CTI_StructureCompletionComponent));
							if (scc.getCompletionValue() < 100)
							{
								startBuildingAction(ussrWorker);

								PrintFormat("CTI :: Completion: %1", scc.getCompletionValue());
								scc.setCompletionValue(scc.getCompletionValue() + 5);
								Replication.BumpMe();
							} else {
								stopBuildingAction(ussrWorker);
								ccc.SetStanceChange(1);

								SCR_CTI_FinishWipStructure finisher = new SCR_CTI_FinishWipStructure();
								finisher.finishWipStructure(closestWipStructure);
							}
							break;
						}
					}	
				}
			}
		}
		
		if (m_usWorkersCount > 0)
		{
			foreach (RplId workerRplId : m_usWorkerRplIds)
			{
				RplComponent workerRplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
				IEntity usWorker = workerRplComp.GetEntity();
				if (!usWorker) continue;

				SCR_CharacterControllerComponent ccc = SCR_CharacterControllerComponent.Cast(usWorker.FindComponent(SCR_CharacterControllerComponent));
				if (ccc.IsUnconscious()) continue;

				if (m_baseComponent.usWIPStructureRplIds.IsEmpty())
				{
					stopBuildingAction(usWorker);
					ccc.SetStanceChange(1);
					continue;
				} else {
					array<IEntity> wipStructures = {};
					foreach (RplId wipStructureRplId : m_baseComponent.usWIPStructureRplIds)
					{
						RplComponent wipStructureRplComp = RplComponent.Cast(Replication.FindItem(wipStructureRplId));
						IEntity wipStructure = wipStructureRplComp.GetEntity();
						if (wipStructure) wipStructures.Insert(wipStructure);
					}

					IEntity closestWipStructure = SCR_CTI_GetClosestEntity.GetClosestEntity(usWorker, wipStructures);
					int distance = vector.Distance(usWorker.GetOrigin(), closestWipStructure.GetOrigin());

					switch (true)
					{
						case (distance <= SCR_CTI_Constants.WORKERSERVICERANGE && distance > SCR_CTI_Constants.WORKERBUILDRANGE):
						{
							Print("CTI :: Distance > 250m, Not in BuildRange!");
							
							stopBuildingAction(usWorker);
							ccc.SetStanceChange(1);

							IEntity child = closestWipStructure.GetChildren();
							while (child)
							{
								SCR_AIWaypoint waypoint = SCR_AIWaypoint.Cast(child);
								if (waypoint)
								{
									waypoint.SetCompletionRadius(25);

									AIControlComponent AIController = AIControlComponent.Cast(usWorker.FindComponent(AIControlComponent));
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

							takeBuildingToolToHand(usWorker);
							
							SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(closestWipStructure.FindComponent(SCR_CTI_StructureCompletionComponent));
							if (scc.getCompletionValue() < 100)
							{
								startBuildingAction(usWorker);

								PrintFormat("CTI :: Completion: %1", scc.getCompletionValue());
								scc.setCompletionValue(scc.getCompletionValue() + 5);
								Replication.BumpMe();
							} else {
								stopBuildingAction(usWorker);
								ccc.SetStanceChange(1);

								SCR_CTI_FinishWipStructure finisher = new SCR_CTI_FinishWipStructure();
								finisher.finishWipStructure(closestWipStructure);
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

		if (!m_rplComponent.IsProxy()) GetGame().GetCallqueue().CallLater(workersLoop, 10 * 1000, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateWorkersComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(ent);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateWorkersComponent()
	{
		if (m_ussrWorkerRplIds) m_ussrWorkerRplIds.Clear();
		m_ussrWorkerRplIds = null;
		if (m_usWorkerRplIds) m_usWorkerRplIds.Clear();
		m_usWorkerRplIds = null;
	}
};