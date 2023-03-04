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
		VehicleWheeledSimulation simulation = VehicleWheeledSimulation.Cast(vehicle.FindComponent(VehicleWheeledSimulation));
		
		if (Math.AbsFloat(simulation.GetSpeedKmh()) < 5)
		{
			Physics physics = vehicle.GetPhysics();
			physics.SetVelocity("0 4 0");

			vector angles = vehicle.GetAngles();
			if (angles[0] > 70 || angles[0] < -70) angles[0] = 0;
			if (angles[2] > 70 || angles[2] < -70) angles[2] = 0;
			vehicle.SetAngles(angles);
		}
	}

	//------------------------------------------------------------------------------------------------
	void StartUpgradeServer(FactionKey fk, int selected)
	{
		Rpc(RpcAsk_StartUpgrade, fk, selected);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_StartUpgrade(FactionKey fk, int selected)
	{
		SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_CTI_UpgradeComponent));
		upgradeComp.runUpgrade(fk, selected);
	}

	//------------------------------------------------------------------------------------------------
	void StopUpgradeServer(FactionKey fk)
	{
		Rpc(RpcAsk_StopUpgrade, fk);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_StopUpgrade(FactionKey fk)
	{
		SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_CTI_UpgradeComponent));
		upgradeComp.stopUpgrade(fk);
	}

	//------------------------------------------------------------------------------------------------
	void setCommanderIdRpl(FactionKey fk, int playerId)
	{
		Rpc(RpcAsk_SetCommanderId, fk, playerId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_SetCommanderId(FactionKey fk, int playerId)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		gameMode.setCommanderId(fk, playerId);
	}

	//------------------------------------------------------------------------------------------------
	void clearCommanderIdRpl(FactionKey fk)
	{
		Rpc(RpcAsk_ClearCommanderId, fk);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_ClearCommanderId(FactionKey fk)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		gameMode.clearCommanderId(fk);
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
			SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
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
		SCR_CTI_BuildStructure BuildStructure = new SCR_CTI_BuildStructure;
		BuildStructure.build(factionkey, resourcename, mat);
	}
	
	//------------------------------------------------------------------------------------------------
	void factoryProductionServer(ResourceName resourcename, FactionKey factionkey, EntityID groupID, vector mat[4], int playerId)
	{
		Rpc(RpcAsk_FactoryProductionServer, resourcename, factionkey, groupID, mat, playerId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_FactoryProductionServer(ResourceName resourcename, FactionKey factionkey, EntityID groupID, vector mat[4], int playerId)
	{
		SCR_CTI_FactoryProduction FactoryProduction = new SCR_CTI_FactoryProduction;
		FactoryProduction.build(resourcename, factionkey, groupID, mat, playerId);
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
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		SCR_CTI_ClientData clientData = gameMode.getClientData(playerId);
		if (clientData) clientData.changeFunds(value);
		gameMode.bumpMeServer();
	}
	
	//------------------------------------------------------------------------------------------------
	void changeCommanderFundsServer(FactionKey fk, int value)
	{
		Rpc(RpcAsk_changeCommanderFundsServer, fk, value);
	}
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_changeCommanderFundsServer(FactionKey fk, int value)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		gameMode.changeCommanderFunds(fk, value);
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
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
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

		arsenalManager.SetPlayerArsenalLoadout(playerId, GameEntity.Cast(ent));
	}
	
	//------------------------------------------------------------------------------------------------
	void repairVehicleServer(RplId rplid)
	{
		Rpc(RpcAsk_RepairVehicleServer, rplid);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_RepairVehicleServer(RplId rplid)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed()) vehicleDamageManager.FullHeal();
	}

	//------------------------------------------------------------------------------------------------
	void refuelVehicleServer(RplId rplid)
	{
		Rpc(RpcAsk_RefuelVehicleServer, rplid);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_RefuelVehicleServer(RplId rplid)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;
		
		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			FuelManagerComponent fuelManagerComp = FuelManagerComponent.Cast(ent.FindComponent(FuelManagerComponent));
			array<BaseFuelNode> outNodes = {};
			fuelManagerComp.GetFuelNodesList(outNodes);
			
			foreach(BaseFuelNode node : outNodes)
			{
				node.SetFuel(node.GetMaxFuel());
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	void rearmVehicleServer(RplId rplid)
	{
		Rpc(RpcAsk_RearmVehicleServer, rplid);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_RearmVehicleServer(RplId rplid)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;
		
		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(ent.FindComponent(SCR_BaseCompartmentManagerComponent));
			
			array<BaseCompartmentSlot> outCompartments = {};
			bcmc.GetCompartments(outCompartments);
					
			foreach(BaseCompartmentSlot slot : outCompartments)
			{
				if (slot.Type() == TurretCompartmentSlot)
				{
					TurretControllerComponent tcc = TurretControllerComponent.Cast(slot.GetController());
					BaseWeaponManagerComponent bwmc = tcc.GetWeaponManager();

					array<IEntity> outWeapons = {};
					bwmc.GetWeaponsList(outWeapons);
					
					if (outWeapons.IsEmpty()) return;

					foreach(IEntity weapon : outWeapons)
					{
						WeaponComponent wc = WeaponComponent.Cast(weapon.FindComponent(WeaponComponent));
						BaseMagazineComponent bmc = wc.GetCurrentMagazine();

						bmc.SetAmmoCount(bmc.GetMaxAmmoCount());
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	void healVehicleCrewServer(RplId rplid)
	{
		Rpc(RpcAsk_HealVehicleCrewServer, rplid);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_HealVehicleCrewServer(RplId rplid)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;
		
		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(ent.FindComponent(SCR_BaseCompartmentManagerComponent));
			array<IEntity> occupants = {};
			bcmc.GetOccupants(occupants);
			
			foreach(IEntity crew : occupants)
			{
				SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(crew.FindComponent(SCR_CharacterDamageManagerComponent));
				cdmc.FullHeal();
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_PlayerController = SCR_PlayerController.Cast(PlayerController.Cast(owner));
		
		if (!m_PlayerController)
		{
			Print("SCR_CTI_NetworkComponent must be attached to PlayerController!", LogLevel.ERROR);
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