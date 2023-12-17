class SCR_CTI_GetSideTowns
{
	//------------------------------------------------------------------------------------------------
	static array<IEntity> GetSideTowns(FactionKey factionkey)
	{
		array<IEntity> list = {};
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		
		foreach (SCR_CTI_Town town : gameMode.CTI_Towns)
		{
			if (town.getFactionKey() == factionkey)
			{
				list.Insert(town);
			}
		}

		return list;
	}
};