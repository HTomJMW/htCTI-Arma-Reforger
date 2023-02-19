class SCR_CTI_GetSideFactories
{
	//------------------------------------------------------------------------------------------------
	static array<IEntity> GetSideFactories(FactionKey factionkey)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		IEntity ent = null;
		array<RplId> structureRplIdArray = {};
		switch (factionkey)
		{
			case "USSR":
			{
				structureRplIdArray = baseComp.getUSSRStructureRplIdArray();
				break;
			}
			case "US":
			{
				structureRplIdArray = baseComp.getUSStructureRplIdArray();
				break;
			}
		}
		
		for (int i = 0; i < structureRplIdArray.Count(); i++)
		{
			ent = GetGame().GetWorld().FindEntityByID(structureRplIdArray[i]);
			list.Insert(ent);
		}
		
		if (list.Count() < 1) return null;

		return list;
	}

	//------------------------------------------------------------------------------------------------
	static array<IEntity> GetSideFactoriesByType(FactionKey factionkey, string factorytype)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		IEntity ent = null;
		SCR_CTI_FactoryData factoryData;
		array<RplId> structureRplIdArray = {};
		int index = -1;
		switch (factionkey)
		{
			case "USSR":
			{
				structureRplIdArray = baseComp.getUSSRStructureRplIdArray();
				for (int i = 0; i < structureRplIdArray.Count(); i++)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(structureRplIdArray[i]));
					ent = rplComp.GetEntity();
					index = gameMode.FactoriesUSSR.findIndexFromResourcename(ent.GetPrefabData().GetPrefabName());
					if (index > -1)
					{
						factoryData = gameMode.FactoriesUSSR.g_USSR_Factories[index];
						if (factoryData.getName() == factorytype) list.Insert(ent);
					}
				}
				break;
			}
			case "US":
			{
				structureRplIdArray = baseComp.getUSStructureRplIdArray();
				for (int i = 0; i < structureRplIdArray.Count(); i++)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(structureRplIdArray[i]));
					ent = rplComp.GetEntity();
					index = gameMode.FactoriesUS.findIndexFromResourcename(ent.GetPrefabData().GetPrefabName());
					if (index > -1)
					{
						factoryData = gameMode.FactoriesUS.g_US_Factories[index];
						if (factoryData.getName() == factorytype) list.Insert(ent);
					}
				}
				break;
			}
		}
		
		if (list.Count() < 1) return null;

		return list;
	}
};