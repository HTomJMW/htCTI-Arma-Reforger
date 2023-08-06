[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Repair Truck")]
class SCR_CTI_UpdateRepairTruckComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateRepairTruckComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_BaseComponent m_baseComp;
	protected IEntity m_vehicle;
	protected VehicleWheeledSimulation_SA m_simulation;
	protected RplComponent m_rplComp;
	protected SCR_BaseCompartmentManagerComponent m_bcmComp;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 20;

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		if (m_rplComp.IsProxy()) return;
		
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
		{
			if (Math.AbsFloat(m_simulation.GetSpeedKmh()) > 5) return;
			
			array<IEntity> occupants = {};
			m_bcmComp.GetOccupants(occupants);

			if (!occupants.IsEmpty())
			{
				FactionKey occupantFactionKey;
				foreach (IEntity ent : occupants)
				{
					FactionAffiliationComponent occupantFaffComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
					occupantFactionKey = occupantFaffComp.GetAffiliatedFaction().GetFactionKey();
					if (occupantFactionKey) break;
				}
	
				switch (occupantFactionKey)
				{
					case "USSR":
					{
						array<RplId> wipRplIds = m_baseComp.ussrWIPStructureRplIds;
						
						foreach (RplId id : wipRplIds)
						{
							if (!id) break;
							
							RplComponent wipStructRplComp = RplComponent.Cast(Replication.FindItem(id));
							IEntity wipStruct = wipStructRplComp.GetEntity();
							
							float distance = vector.Distance(wipStruct.GetOrigin(), m_vehicle.GetOrigin());
							if (distance <= SCR_CTI_Constants.SERVICERANGE)
							{
								PrintFormat("Repair Truck - WIP structure Dist: %1", distance);
								SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(wipStruct.FindComponent(SCR_CTI_StructureCompletionComponent));

								if (scc.getCompletionValue() < 100)
								{
									scc.setCompletionValue(scc.getCompletionValue() + 10);
									m_gameMode.bumpMeServer();

									if (scc.getCompletionValue() >= 100)
									{
										finishBuilding("USSR", wipStruct, id);
									} else {
										PrintFormat("Completion value: %1", scc.getCompletionValue());
									}
								} else {
									finishBuilding("USSR", wipStruct, id);
								}
							}
						}
						
						break;
					}
					case "US":
					{
						array<RplId> wipRplIds = m_baseComp.usWIPStructureRplIds;
						
						foreach (RplId id : wipRplIds)
						{
							if (!id) break;
							
							RplComponent wipStructRplComp = RplComponent.Cast(Replication.FindItem(id));
							IEntity wipStruct = wipStructRplComp.GetEntity();
							
							float distance = vector.Distance(wipStruct.GetOrigin(), m_vehicle.GetOrigin());
							if (distance <= SCR_CTI_Constants.SERVICERANGE)
							{
								PrintFormat("Repair Truck - WIP structure Dist: %1", distance);
								SCR_CTI_StructureCompletionComponent scc = SCR_CTI_StructureCompletionComponent.Cast(wipStruct.FindComponent(SCR_CTI_StructureCompletionComponent));

								if (scc.getCompletionValue() < 100)
								{
									scc.setCompletionValue(scc.getCompletionValue() + 10);
									m_gameMode.bumpMeServer();

									if (scc.getCompletionValue() >= 100)
									{
										finishBuilding("US", wipStruct, id);
									} else {
										PrintFormat("Completion value: %1", scc.getCompletionValue());
									}
								} else {
									finishBuilding("US", wipStruct, id);
								}
							}
						}
						
						break;
					}			
				}
			}

			m_timeDelta = 0;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected void finishBuilding(FactionKey factionkey, IEntity wipStruct, RplId id)
	{
		vector mat[4];
		wipStruct.GetTransform(mat);

		int index = -1;
		SCR_CTI_FactoryData factoryData;
		switch (factionkey)
		{
			case "USSR":
			{
				index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(wipStruct.GetPrefabData().GetPrefabName());
				factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];
				
				break;
			}
			case "US":
			{
				index = m_gameMode.FactoriesUS.findIndexFromResourcename(wipStruct.GetPrefabData().GetPrefabName());
				factoryData = m_gameMode.FactoriesUS.g_US_Factories[index];

				break;
			}	
		}
							
		SCR_EntityHelper.DeleteEntityAndChildren(wipStruct);
		m_baseComp.removeWIPStructureRplId(factionkey, id);

		SCR_CTI_BuildStructure buildstructure = new SCR_CTI_BuildStructure();
		buildstructure.build(factionkey, factoryData.getResName(), mat);

		Print("CTI :: Construction Complete!");
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_vehicle = GetOwner();
		m_simulation = VehicleWheeledSimulation_SA.Cast(m_vehicle.FindComponent(VehicleWheeledSimulation_SA));
		m_rplComp = RplComponent.Cast(m_vehicle.FindComponent(RplComponent));
		m_bcmComp = SCR_BaseCompartmentManagerComponent.Cast(m_vehicle.FindComponent(SCR_BaseCompartmentManagerComponent));

		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateRepairTruckComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_baseComp = SCR_CTI_BaseComponent.Cast(m_gameMode.FindComponent(SCR_CTI_BaseComponent));

		m_timeDelta = 0;
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateRepairTruckComponent()
	{
	}	
};