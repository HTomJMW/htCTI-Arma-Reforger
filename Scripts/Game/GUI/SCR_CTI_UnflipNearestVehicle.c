class SCR_CTI_UnflipNearestVehicle
{
	protected IEntity playerEntity;
	protected ref array<IEntity> vehicles = {};
	
	void init()
	{
		PlayerController pc = GetGame().GetPlayerController();
		playerEntity = pc.GetControlledEntity();
	}
	
	protected IEntity findNearest()
	{
		vector mat[4];
		playerEntity.GetTransform(mat);

		vector center = mat[3];
		float radius = 10.0;

		GetGame().GetWorld().QueryEntitiesBySphere(center, radius, GetEntity, FilterEntities, EQueryEntitiesFlags.DYNAMIC);
		
		IEntity nearest = null;
		float distance = radius;
		
		foreach (IEntity veh : vehicles)
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
	
	protected bool GetEntity(IEntity ent)
	{
		vehicles.Insert(ent);

		return true;
	}
	
	protected bool FilterEntities(IEntity ent) 
	{
		if (ent.FindComponent(SCR_VehicleDamageManagerComponent))
			return true;

		return false;
	}
	
	void unflip()
	{
		IEntity nearest = findNearest();
		if (nearest)
		{
			Physics physics = nearest.GetPhysics();
		
			vector vel = physics.GetVelocity();
			if (vel == "0 0 0")		
			{
				//vector origin = nearest.GetOrigin();
				//origin[1] = origin[1] + 0.5;
				//nearest.SetOrigin(origin);
			
				physics.SetVelocity("0 4 0");
			
				vector angles = nearest.GetAngles();
				if (angles[0] > 70 || angles[0] < -70) angles[0] = 0;
				if (angles[2] > 70 || angles[2] < -70) angles[2] = 0;
				nearest.SetAngles(angles);
			}
		}
	}
	
	void SCR_CTI_UnflipNearestVehicle()
	{
	}
	
	void ~SCR_CTI_UnflipNearestVehicle()
	{
	}
};