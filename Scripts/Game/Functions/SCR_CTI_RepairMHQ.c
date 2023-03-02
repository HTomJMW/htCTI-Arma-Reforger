class SCR_CTI_RepairMHQ
{
	//Server only
	//------------------------------------------------------------------------------------------------
	static void repairMHQ(FactionKey factionkey)
	{
		IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(factionkey);
		SCR_VehicleDamageManagerComponent vehicleDamageManager = SCR_VehicleDamageManagerComponent.Cast(mhq.FindComponent(SCR_VehicleDamageManagerComponent));

		if (vehicleDamageManager.IsDestroyed())
		{
			vector mat[4];
			mhq.GetWorldTransform(mat);
			
			RplComponent.DeleteRplEntity(mhq, false);
			
			ResourceName resname;
			switch(factionkey)
			{
				case "USSR": resname = SCR_CTI_Constants.USSR_MHQ; break;
				case "US": resname = SCR_CTI_Constants.US_MHQ; break;
			} 
		
			Resource res = Resource.Load(resname);
			
			EntitySpawnParams spawnParams = new EntitySpawnParams();
			spawnParams.TransformMode = ETransformMode.WORLD;
			spawnParams.Transform = mat;		
		
			IEntity spawnedEntity = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), spawnParams);
			
			RplId rplId = Replication.FindId(spawnedEntity);
			SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
			gameMode.setMHQrplId(factionkey, rplId);
			
			// TODO check garbage collector
			// TODO send notif
		}
	}
};