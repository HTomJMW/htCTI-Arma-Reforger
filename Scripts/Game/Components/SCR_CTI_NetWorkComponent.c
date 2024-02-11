[EntityEditorProps(category: "GameScripted/CTI", description: "Handles client - server communication. Should be attached to PlayerController.")]
class SCR_CTI_NetWorkComponentClass: ScriptComponentClass
{
};

class SCR_CTI_NetWorkComponent : ScriptComponent
{
	protected SCR_PlayerController m_PlayerController;
	protected RplComponent m_RplComponent;

	//------------------------------------------------------------------------------------------------
	protected bool IsProxy()
	{
		return (m_RplComponent && m_RplComponent.IsProxy());
	}

	//------------------------------------------------------------------------------------------------
	void unflipNearestVehicleServer(RplId vehRplId)
	{
		Rpc(RpcAsk_UnflipNearestVehicle, vehRplId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_UnflipNearestVehicle(RplId vehRplId)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(vehRplId));
		IEntity vehicle = rplComp.GetEntity();
		VehicleWheeledSimulation_SA simulation = VehicleWheeledSimulation_SA.Cast(vehicle.FindComponent(VehicleWheeledSimulation_SA));

		if (Math.AbsFloat(simulation.GetSpeedKmh()) < 5)
		{
			CarControllerComponent_SA carController = CarControllerComponent_SA.Cast(vehicle.FindComponent(CarControllerComponent_SA));
			if (carController) carController.SetPersistentHandBrake(true);
			
			Physics physics = vehicle.GetPhysics();
			physics.SetVelocity("0 4 0");

			vector angles = vehicle.GetAngles();
			if (angles[0] > 70 || angles[0] < -70) angles[0] = 0;
			if (angles[2] > 70 || angles[2] < -70) angles[2] = 0;
			vehicle.SetAngles(angles);
		}
	}

	//------------------------------------------------------------------------------------------------
	void StartUpgradeServer(FactionKey factionkey, int selected)
	{
		Rpc(RpcAsk_StartUpgrade, factionkey, selected);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_StartUpgrade(FactionKey factionkey, int selected)
	{
		SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_CTI_UpgradeComponent));
		upgradeComp.runUpgrade(factionkey, selected);
	}

	//------------------------------------------------------------------------------------------------
	void StopUpgradeServer(FactionKey factionkey)
	{
		Rpc(RpcAsk_StopUpgrade, factionkey);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_StopUpgrade(FactionKey factionkey)
	{
		SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_CTI_UpgradeComponent));
		upgradeComp.stopUpgrade(factionkey);
	}

	//------------------------------------------------------------------------------------------------
	void setCommanderIdRpl(FactionKey factionkey, int playerId)
	{
		Rpc(RpcAsk_SetCommanderId, factionkey, playerId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_SetCommanderId(FactionKey factionkey, int playerId)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.setCommanderId(factionkey, playerId);
	}

	//------------------------------------------------------------------------------------------------
	void clearCommanderIdRpl(FactionKey factionkey)
	{
		Rpc(RpcAsk_ClearCommanderId, factionkey);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_ClearCommanderId(FactionKey factionkey)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.clearCommanderId(factionkey);
	}

	//------------------------------------------------------------------------------------------------
	void updateClientDataCommanderServer(int playerId)
	{
		Rpc(RpcAsk_UpdateClientDataCommanderServer, playerId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_UpdateClientDataCommanderServer(int playerId)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
		if (clientData)
		{
			clientData.setCommander(false);
			gameMode.bumpMeServer();
		}
	}

	//------------------------------------------------------------------------------------------------
	void buildDefenseServer(ResourceName resourcename, vector mat[4], int playerId)
	{
		Rpc(RpcAsk_BuildDefenseServer, resourcename, mat, playerId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_BuildDefenseServer(ResourceName resourcename, vector mat[4], int playerId)
	{
		Resource resource = Resource.Load(resourcename);
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;

		IEntity defense = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		
		if (defense)
		{
			SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
			SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
			if (clientData)
			{
				int factionIndex = clientData.getFactionIndex();
				FactionKey factionkey = GetGame().GetFactionManager().GetFactionByIndex(factionIndex).GetFactionKey();
				
				SCR_CTI_DefenseData defenseData;
					int index = -1;
					switch (factionkey)
					{
						case "USSR":
						{
							index = gameMode.DefensesUSSR.findIndexFromResourcename(resourcename);
							defenseData = gameMode.DefensesUSSR.g_USSR_Defenses[index];
							break;
						}
						case "US":
						{
							index = gameMode.DefensesUS.findIndexFromResourcename(resourcename);
							defenseData = gameMode.DefensesUS.g_US_Defenses[index];
							break;
						}
					}
					int cost = defenseData.getPrice();

				if (clientData.isCommander())
				{
					gameMode.changeCommanderFunds(factionkey, -cost);
				} else {
					clientData.changeFunds(-cost);
					gameMode.bumpMeServer();
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	void buildStructureServer(FactionKey factionkey, ResourceName resourcename, vector mat[4])
	{
		Rpc(RpcAsk_BuildStructureServer, factionkey, resourcename, mat);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_BuildStructureServer(FactionKey factionkey, ResourceName resourcename, vector mat[4])
	{
		SCR_CTI_BuildStructureWIP builder = new SCR_CTI_BuildStructureWIP;
		builder.build(factionkey, resourcename, mat);
	}

	//------------------------------------------------------------------------------------------------
	void addBuildRequestServer(ResourceName resourcename, FactionKey factionkey, EntityID groupID, RplId factRplId, vector mat[4], int playerId, int buildTime, CTI_PurchaseInfos purchaseInfo)
	{
		Rpc(RpcAsk_AddBuildRequestServer, resourcename, factionkey, groupID, factRplId, mat, playerId, buildTime, purchaseInfo);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_AddBuildRequestServer(ResourceName resourcename, FactionKey factionkey, EntityID groupID, RplId factRplId, vector mat[4], int playerId, int buildTime, CTI_PurchaseInfos purchaseInfo)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(factRplId));
		IEntity factory = rplComp.GetEntity();
		SCR_CTI_BuildQueueComponent bqcomp = SCR_CTI_BuildQueueComponent.Cast(factory.FindComponent(SCR_CTI_BuildQueueComponent));
		bqcomp.addRequest(resourcename, factionkey, groupID, factRplId, mat, playerId, buildTime, purchaseInfo);
	}

	//------------------------------------------------------------------------------------------------
	void changeFundsServer(int playerId, int value)
	{
		Rpc(RpcAsk_changeFundsServer, playerId, value);
	}
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_changeFundsServer(int playerId, int value)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
		if (clientData) clientData.changeFunds(value);
		gameMode.bumpMeServer();
	}
	
	//------------------------------------------------------------------------------------------------
	void changeCommanderFundsServer(FactionKey factionkey, int value)
	{
		Rpc(RpcAsk_changeCommanderFundsServer, factionkey, value);
	}
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_changeCommanderFundsServer(FactionKey factionkey, int value)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.changeCommanderFunds(factionkey, value);
	}
	
	//------------------------------------------------------------------------------------------------
	void setPriorityServer(FactionKey factionkey, string townName)
	{
		Rpc(RpcAsk_setPriorityServer, factionkey, townName);
	}
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_setPriorityServer(FactionKey factionkey, string townName)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.setPriority(factionkey, townName);
	}

	//------------------------------------------------------------------------------------------------
	void savePlayerLoadout(int playerId, RplId rplid)
	{
		Rpc(RpcAsk_savePlayerLoadoutServer, playerId, rplid);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_savePlayerLoadoutServer(int playerId, RplId rplid)
	{
		SCR_ArsenalManagerComponent arsenalManager;
		SCR_ArsenalManagerComponent.GetArsenalManager(arsenalManager);
		
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();

		arsenalManager.SetPlayerArsenalLoadout(playerId, GameEntity.Cast(ent), null);
	}
	
	//------------------------------------------------------------------------------------------------
	void repairVehicleServer(int playerId, RplId rplid, int delay)
	{
		Rpc(RpcAsk_RepairVehicleServer, playerId, rplid, delay);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_RepairVehicleServer(int playerId, RplId rplid, int delay)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		GetGame().GetCallqueue().CallLater(gameMode.delayedRepair, delay * 1000, false, playerId, rplid);
	}

	//------------------------------------------------------------------------------------------------
	void rearmVehicleServer(int playerId, RplId rplid, int delay)
	{
		Rpc(RpcAsk_RearmVehicleServer, playerId, rplid, delay);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_RearmVehicleServer(int playerId, RplId rplid, int delay)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		GetGame().GetCallqueue().CallLater(gameMode.delayedRearm, delay * 1000, false, playerId, rplid);
	}

	//------------------------------------------------------------------------------------------------
	void refuelVehicleServer(int playerId, RplId rplid, int delay)
	{
		Rpc(RpcAsk_RefuelVehicleServer, playerId, rplid, delay);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_RefuelVehicleServer(int playerId, RplId rplid, int delay)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		GetGame().GetCallqueue().CallLater(gameMode.delayedRefuel, delay * 1000, false, playerId, rplid);
	}

	//------------------------------------------------------------------------------------------------
	void healVehicleCrewServer(int playerId, RplId rplid, int delay)
	{
		Rpc(RpcAsk_HealVehicleCrewServer, playerId, rplid, delay);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_HealVehicleCrewServer(int playerId, RplId rplid, int delay)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		GetGame().GetCallqueue().CallLater(gameMode.delayedHeal, delay * 1000, false, playerId, rplid);
	}

	//------------------------------------------------------------------------------------------------
	void addWorkerServer(FactionKey factionkey)
	{
		Rpc(RpcAsk_addWorkerServer, factionkey);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_addWorkerServer(FactionKey factionkey)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_UpdateWorkersComponent uwc = SCR_CTI_UpdateWorkersComponent.Cast(gameMode.FindComponent(SCR_CTI_UpdateWorkersComponent));
		if (uwc) uwc.addWorker(factionkey);
	}
	
	//------------------------------------------------------------------------------------------------
	void disbandWorkerServer(FactionKey factionkey, RplId rplid)
	{
		Rpc(RpcAsk_disbandWorkerServer, factionkey, rplid);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_disbandWorkerServer(FactionKey factionkey, RplId rplid)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_UpdateWorkersComponent uwc = SCR_CTI_UpdateWorkersComponent.Cast(gameMode.FindComponent(SCR_CTI_UpdateWorkersComponent));
		if (uwc) uwc.disbandWorker(factionkey, rplid);
	}
	
	//------------------------------------------------------------------------------------------------
	void deleteObjectServer(FactionKey factionkey, RplId rplid)
	{
		Rpc(RpcAsk_deleteObjectServer, factionkey, rplid);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_deleteObjectServer(FactionKey factionkey, RplId rplid)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		if (baseComp) baseComp.deleteObject(factionkey, rplid);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_PlayerController = SCR_PlayerController.Cast(PlayerController.Cast(owner));
		
		if (!m_PlayerController)
		{
			Print("CTI :: SCR_CTI_NetworkComponent must be attached to PlayerController!", LogLevel.ERROR);
			return;
		}
		
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
		owner.SetFlags(EntityFlags.ACTIVE, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_NetWorkComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_NetWorkComponent()
	{
	}
};