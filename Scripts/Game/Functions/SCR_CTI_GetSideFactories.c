class SCR_CTI_GetSideFactories
{
	static array<IEntity> GetSideFactories(FactionKey factionkey)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		IEntity ent = null;
		switch (factionkey)
		{
			case "USSR":
			{
				array<ref EntityID> ussrArr = baseComp.getUSSRStructureIdArray();
				for (int i = 0; i < ussrArr.Count(); i++)
				{
					ent = GetGame().GetWorld().FindEntityByID(ussrArr[i]);
					list.Insert(ent);
				}
				break;
			}
			case "US":
			{
				array<ref EntityID> usArr = baseComp.getUSStructureIdArray();
				for (int i = 0; i < usArr.Count(); i++)
				{
					ent = GetGame().GetWorld().FindEntityByID(usArr[i]);
					list.Insert(ent);
				}
				break;
			}
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
		switch (factionkey)
		{
			case "USSR":
			{
				array<ref EntityID> ussrArr = baseComp.getUSSRStructureIdArray();
				for (int i = 0; i < ussrArr.Count(); i++)
				{
					ent = GetGame().GetWorld().FindEntityByID(ussrArr[i]);
					int index = gameMode.FactoriesUSSR.findIndexFromResourcename(ent.GetPrefabData().GetPrefabName());
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
				array<ref EntityID> usArr = baseComp.getUSStructureIdArray();
				for (int i = 0; i < usArr.Count(); i++)
				{
					ent = GetGame().GetWorld().FindEntityByID(usArr[i]);
					int index = gameMode.FactoriesUS.findIndexFromResourcename(ent.GetPrefabData().GetPrefabName());
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