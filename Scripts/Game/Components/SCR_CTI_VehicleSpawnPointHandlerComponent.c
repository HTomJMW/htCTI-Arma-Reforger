[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Vehicle Spawn Point Handler.")]
class SCR_CTI_VehicleSpawnPointHandlerComponentClass : ScriptComponentClass
{
};

class SCR_CTI_VehicleSpawnPointHandlerComponent : ScriptComponent
{
	protected RplComponent m_rplComponent;
	
	//------------------------------------------------------------------------------------------------
	protected void OnDestroyed(IEntity ent)
	{
		SlotManagerComponent slotManager = SlotManagerComponent.Cast(ent.FindComponent(SlotManagerComponent));
		if (slotManager)
		{
			array<EntitySlotInfo> slots = {};
			slotManager.GetSlotInfos(slots);

			foreach (EntitySlotInfo slot : slots)
			{
				SCR_SpawnPoint spawnPoint = SCR_SpawnPoint.Cast(slot.GetAttachedEntity());
				if (spawnPoint)
				{
					SCR_EntityHelper.DeleteEntityAndChildren(spawnPoint);
					break;
				} else {
					continue;
				}
			}
		}

		if (ent.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.USSR_MHQ || ent.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.US_MHQ)
		{
			ChimeraWorld world = ent.GetWorld();
			GarbageManager garbagemanager = world.GetGarbageManager();
	
			garbagemanager.Insert(ent);
			garbagemanager.Withdraw(ent); // Maybe OnDestroyed have more instances, so possible need make delayed ask too

			SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
			FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
			
			gameMode.sendFactionNotifP(faffComp.GetDefaultAffiliatedFaction().GetFactionKey(), ENotification.CTI_NOTIF_MHQ_DESTROYED);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected override void OnPostInit(IEntity owner)
	{
		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		if (m_rplComponent.IsProxy()) return;
		
		EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(owner.FindComponent(EventHandlerManagerComponent));
		if (ehManager)
		{
			ehManager.RegisterScriptHandler("OnDestroyed", this, OnDestroyed);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected override void OnDelete(IEntity owner)
	{
		if (m_rplComponent.IsProxy()) return;

		EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(owner.FindComponent(EventHandlerManagerComponent));
		if (ehManager)
		{
			ehManager.RemoveScriptHandler("OnDestroyed", this, OnDestroyed);
		}
	}
};