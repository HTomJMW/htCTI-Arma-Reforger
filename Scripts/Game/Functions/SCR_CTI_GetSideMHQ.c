class SCR_CTI_GetSideMHQ
{
	//------------------------------------------------------------------------------------------------
	static IEntity GetSideMHQ(FactionKey factionkey)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		IEntity mhq = null;

		switch (factionkey)
		{
			case "USSR":
			{
				mhq = GetGame().GetWorld().FindEntityByName(gameMode.USSRMHQNAME);
				break;
			}
			case "US":
			{
				mhq = GetGame().GetWorld().FindEntityByName(gameMode.USMHQNAME);
				break;
			}
		}
		
		return mhq;
	}
};