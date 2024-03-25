[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Service functions")]
class SCR_CTI_ServiceComponentClass : ScriptComponentClass
{
};

class SCR_CTI_ServiceComponent : ScriptComponent
{
	//------------------------------------------------------------------------------------------------
	void delayedRepair(int playerId, RplId rplid)
	{
		// TODO check rep near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		SCR_CTI_VehicleCustomVariablesComponent vcvc = SCR_CTI_VehicleCustomVariablesComponent.Cast(ent.FindComponent(SCR_CTI_VehicleCustomVariablesComponent));

		if (vcvc && vcvc.getSupportVehicleType() == CTI_SupportVehicleTypes.MHQ && vehicleDamageManager.IsDestroyed())
		{
			FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
			SCR_CTI_RepairMHQ.repairMHQ(faffComp.GetDefaultAffiliatedFaction().GetFactionKey());
			return;
		}

		if (!vehicleDamageManager.IsDestroyed()) vehicleDamageManager.FullHeal();

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle</color> repaired!", "Information", 5);
	}
	
	//------------------------------------------------------------------------------------------------
	void delayedRearm(int playerId, RplId rplid)
	{
		// TODO check ammo near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(ent.FindComponent(SCR_BaseCompartmentManagerComponent));

			array<BaseCompartmentSlot> outCompartments = {};
			bcmc.GetCompartments(outCompartments);

			foreach (BaseCompartmentSlot slot : outCompartments)
			{
				if (slot.Type() == TurretCompartmentSlot)
				{
					TurretControllerComponent tcc = TurretControllerComponent.Cast(slot.GetController());
					BaseWeaponManagerComponent bwmc = tcc.GetWeaponManager();

					array<IEntity> outWeapons = {};
					bwmc.GetWeaponsList(outWeapons);

					if (outWeapons.IsEmpty()) return;

					foreach (IEntity weapon : outWeapons)
					{
						WeaponComponent wc = WeaponComponent.Cast(weapon.FindComponent(WeaponComponent));
						BaseMagazineComponent bmc = wc.GetCurrentMagazine();

						bmc.SetAmmoCount(bmc.GetMaxAmmoCount());
					}
				}
			}
		}

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle</color> rearmed!", "Information", 5);
	}

	//------------------------------------------------------------------------------------------------
	void delayedRefuel(int playerId, RplId rplid)
	{
		// TODO check fuel near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			FuelManagerComponent fuelManagerComp = FuelManagerComponent.Cast(ent.FindComponent(FuelManagerComponent));
			array<BaseFuelNode> outNodes = {};
			fuelManagerComp.GetFuelNodesList(outNodes);

			foreach (BaseFuelNode node : outNodes)
			{
				node.SetFuel(node.GetMaxFuel());
			}
		}

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle</color> refuelled!", "Information", 5);
	}

	//------------------------------------------------------------------------------------------------
	void delayedHeal(int playerId, RplId rplid)
	{
		// TODO rep near
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity ent = rplComp.GetEntity();
		if (!ent) return;

		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (!vehicleDamageManager.IsDestroyed())
		{
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(ent.FindComponent(SCR_BaseCompartmentManagerComponent));
			array<IEntity> occupants = {};
			bcmc.GetOccupants(occupants);

			foreach (IEntity crew : occupants)
			{
				if (!crew) break;
				SCR_CharacterDamageManagerComponent cdmc = SCR_CharacterDamageManagerComponent.Cast(crew.FindComponent(SCR_CharacterDamageManagerComponent));
				if (!cdmc.IsDestroyed()) cdmc.FullHeal();
			}
		}

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.SendHint(playerId, "<color rgba='255,210,115,255'>Vehicle crew</color> healed!", "Information", 5);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_ServiceComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_ServiceComponent()
	{
	}	
};