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

	//------------------------------------------------------------------------------------------------
	void update()
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
								scc.setCompletionValue(scc.getCompletionValue() + 15);
								m_gameMode.bumpMeServer();

								if (scc.getCompletionValue() >= 100)
								{
									SCR_CTI_FinishWipStructure finisher = new SCR_CTI_FinishWipStructure();
									finisher.finishWipStructure(wipStruct);
								} else {
									PrintFormat("Completion value: %1", scc.getCompletionValue());
								}
							} else {
								SCR_CTI_FinishWipStructure finisher = new SCR_CTI_FinishWipStructure();
								finisher.finishWipStructure(wipStruct);
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
								scc.setCompletionValue(scc.getCompletionValue() + 15);
								m_gameMode.bumpMeServer();

								if (scc.getCompletionValue() >= 100)
								{
									SCR_CTI_FinishWipStructure finisher = new SCR_CTI_FinishWipStructure();
									finisher.finishWipStructure(wipStruct);
								} else {
									PrintFormat("Completion value: %1", scc.getCompletionValue());
								}
							} else {
								SCR_CTI_FinishWipStructure finisher = new SCR_CTI_FinishWipStructure();
								finisher.finishWipStructure(wipStruct);
							}
						}
					}

					break;
				}			
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_vehicle = GetOwner();
		m_simulation = VehicleWheeledSimulation_SA.Cast(m_vehicle.FindComponent(VehicleWheeledSimulation_SA));
		m_rplComp = RplComponent.Cast(m_vehicle.FindComponent(RplComponent));
		m_bcmComp = SCR_BaseCompartmentManagerComponent.Cast(m_vehicle.FindComponent(SCR_BaseCompartmentManagerComponent));

		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		if (!m_rplComp.IsProxy())
		{
			GetGame().GetCallqueue().CallLater(update, 20 * 1000, true);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateRepairTruckComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_baseComp = SCR_CTI_BaseComponent.Cast(m_gameMode.FindComponent(SCR_CTI_BaseComponent));
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateRepairTruckComponent()
	{
	}	
};