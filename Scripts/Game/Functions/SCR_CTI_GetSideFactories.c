class SCR_CTI_GetSideFactories
{
	//------------------------------------------------------------------------------------------------
	static array<IEntity> GetSideFactories(FactionKey factionkey)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		IEntity ent = null;
		switch (factionkey)
		{
			case "USSR":
			{
				for (int i = 0; i < baseComp.ussrStructureRplIds.Count(); i++)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(baseComp.ussrStructureRplIds[i]));
					ent = rplComp.GetEntity();
					list.Insert(ent);
				}
				break;
			}
			case "US":
			{
				for (int i = 0; i < baseComp.usStructureRplIds.Count(); i++)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(baseComp.usStructureRplIds[i]));
					ent = rplComp.GetEntity();
					list.Insert(ent);
				}
				break;
			}
		}

		return list;
	}

	//------------------------------------------------------------------------------------------------
	// Factory Types equal to Factory Names
	static array<IEntity> GetSideFactoriesByType(FactionKey factionkey, string factorytype)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		IEntity ent = null;
		SCR_CTI_FactoryData factoryData;
		int index = -1;
		switch (factionkey)
		{
			case "USSR":
			{
				for (int i = 0; i < baseComp.ussrStructureRplIds.Count(); i++)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(baseComp.ussrStructureRplIds[i]));
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
				for (int i = 0; i < baseComp.usStructureRplIds.Count(); i++)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(baseComp.usStructureRplIds[i]));
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

		return list;
	}
};