class SCR_CTI_UnflipNearestVehicle
{
	protected IEntity playerEntity;
	protected ref array<IEntity> vehicles = {};
	protected SCR_CTI_GameMode gameMode;
	
	void init()
	{
		PlayerController pc = GetGame().GetPlayerController();
		playerEntity = pc.GetControlledEntity();
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
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
			PlayerController pc = GetGame().GetPlayerController();
			SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
			RplComponent rplComp = RplComponent.Cast(nearest.FindComponent(RplComponent));
			RplId rplId = rplComp.Id();
			netComp.unflipNearestVehicleServer(rplId);
		}
	}
	
	void SCR_CTI_UnflipNearestVehicle()
	{
	}
	
	void ~SCR_CTI_UnflipNearestVehicle()
	{
	}
};