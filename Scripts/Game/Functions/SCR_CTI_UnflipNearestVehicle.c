class SCR_CTI_UnflipNearestVehicle
{
	protected PlayerController m_pc;
	protected IEntity m_playerEntity;
	protected ref array<IEntity> m_vehicles = {};
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	protected IEntity findNearest()
	{
		vector mat[4];
		m_playerEntity.GetTransform(mat);

		vector center = mat[3];
		float radius = 10.0;

		GetGame().GetWorld().QueryEntitiesBySphere(center, radius, GetEntity, FilterEntities, EQueryEntitiesFlags.DYNAMIC);
		
		IEntity nearest = null;
		float distance = radius;
		
		foreach (IEntity veh : m_vehicles)
		{
			vector vmat[4];
			veh.GetTransform(vmat);
			float dist = vector.Distance(center, vmat[3]);
			if (dist < distance)
			{
				nearest = veh;
				distance = dist;
			}
		}

		return nearest;
	}

	//------------------------------------------------------------------------------------------------
	protected bool GetEntity(IEntity ent)
	{
		m_vehicles.Insert(ent);

		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected bool FilterEntities(IEntity ent)
	{
		SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(ent.FindComponent(SCR_VehicleDamageManagerComponent));
		if (vdmc && !vdmc.IsDestroyed()) return true;

		return false;
	}

	//------------------------------------------------------------------------------------------------
	void unflip()
	{
		IEntity nearest = findNearest();

		if (nearest)
		{
			// disable unflip when vehicle is manned (maybe player compartmentaccess component getout better?)
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(nearest.FindComponent(SCR_BaseCompartmentManagerComponent));
			array<IEntity> occupants = {};
			bcmc.GetOccupants(occupants);
			//if (occupants.Count() > 0) return; // Disabled until wait ai commanding. Unflip disabled only if player inside vehicle.
			foreach (IEntity crew : occupants)
			{
				if (SCR_EntityHelper.IsPlayer(crew))
				{
					SCR_HintManagerComponent.ShowCustomHint("Unflip not allowed, player in vehicle!", "Information", 5);
					return;
				}
			}

			//vector pos = nearest.GetOrigin();
			//float y = GetGame().GetWorld().GetSurfaceY(pos[0], pos[2]);
			//if (y + 2.5 < pos[1]) return;

			Physics physics = nearest.GetPhysics();
			vector velocity = physics.GetVelocity();
			if (Math.AbsFloat(velocity[1]) > 0.1) return;

			SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(m_pc.FindComponent(SCR_CTI_NetWorkComponent));
			RplComponent rplComp = RplComponent.Cast(nearest.FindComponent(RplComponent));
			RplId vehRplId = rplComp.Id();

			netComp.unflipNearestVehicleServer(vehRplId);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UnflipNearestVehicle()
	{
		m_pc = GetGame().GetPlayerController();
		m_playerEntity = m_pc.GetControlledEntity();
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UnflipNearestVehicle()
	{
		if (!m_vehicles) return;
		m_vehicles.Clear();
		m_vehicles = null;
	}
};