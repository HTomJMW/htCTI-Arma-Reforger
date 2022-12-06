class SCR_CTI_GetSideFactories
{
	static array<IEntity> GetSideFactories(FactionKey factionkey)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		IEntity ent = null;
		array<ref EntityID> structureIdArray = {};
		switch (factionkey)
		{
			case "USSR":
			{
				structureIdArray = baseComp.getUSSRStructureIdArray();
				break;
			}
			case "US":
			{
				structureIdArray = baseComp.getUSStructureIdArray();
				break;
			}
		}
		
		for (int i = 0; i < structureIdArray.Count(); i++)
		{
			ent = GetGame().GetWorld().FindEntityByID(structureIdArray[i]);
			list.Insert(ent);
		}
		
		if (list.Count() < 1) return null;

		return list;
	}
	
	static array<IEntity> GetSideFactoriesByType(FactionKey factionkey, string factorytype)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		IEntity ent = null;
		SCR_CTI_FactoryData factoryData;
		array<ref EntityID> structureIdArray = {};
		int index = -1;
		switch (factionkey)
		{
			case "USSR":
			{
				structureIdArray = baseComp.getUSSRStructureIdArray();
				for (int i = 0; i < structureIdArray.Count(); i++)
				{
					ent = GetGame().GetWorld().FindEntityByID(structureIdArray[i]);
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
				structureIdArray = baseComp.getUSStructureIdArray();
				for (int i = 0; i < structureIdArray.Count(); i++)
				{
					ent = GetGame().GetWorld().FindEntityByID(structureIdArray[i]);
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