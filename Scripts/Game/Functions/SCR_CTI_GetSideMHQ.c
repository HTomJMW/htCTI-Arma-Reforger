class SCR_CTI_GetSideMHQ
{
	//------------------------------------------------------------------------------------------------
	static IEntity GetSideMHQ(FactionKey factionkey)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		IEntity	mhq = IEntity.Cast(Replication.FindItem(gameMode.getMHQrplId(factionkey)));

		return mhq;
	}
};