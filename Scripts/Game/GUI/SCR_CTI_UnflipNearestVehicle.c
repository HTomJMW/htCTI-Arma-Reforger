class SCR_CTI_UnflipNearestVehicle
{
	protected PlayerController m_pc;
	protected IEntity m_playerEntity;
	protected ref array<IEntity> m_vehicles = {};
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_pc = GetGame().GetPlayerController();
		m_playerEntity = m_pc.GetControlledEntity();
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

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
		if (ent.FindComponent(SCR_VehicleDamageManagerComponent))
			return true;

		return false;
	}

	//------------------------------------------------------------------------------------------------
	void unflip()
	{
		IEntity nearest = findNearest();

		if (nearest)
		{
			// disable unflip when vehicle is manned (its make RPL desync bug) (maybe player compartmentaccess component getout better?)
			SCR_BaseCompartmentManagerComponent bcmc = SCR_BaseCompartmentManagerComponent.Cast(nearest.FindComponent(SCR_BaseCompartmentManagerComponent));
			array<IEntity> occupants = {};
			bcmc.GetOccupants(occupants);
			if (occupants.Count() > 0) return;
			
			SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(m_pc.FindComponent(SCR_CTI_NetWorkComponent));
			RplComponent rplComp = RplComponent.Cast(nearest.FindComponent(RplComponent));
			RplId vehRplId = rplComp.Id();
			netComp.unflipNearestVehicleServer(vehRplId);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UnflipNearestVehicle()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UnflipNearestVehicle()
	{
		m_vehicles.Clear();
		m_vehicles = null;
	}
};