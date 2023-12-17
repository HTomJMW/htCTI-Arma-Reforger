modded class SCR_SpawnPointRequestUIComponent : SCR_DeployRequestUIBaseComponent
{
	override void ShowAvailableSpawnPoints(Faction faction)
	{
		if (!faction)
			return;

		ClearSpawnPoints();

		PlayerController pc = GetGame().GetPlayerController();
		SCR_CTI_DeathPositionComponent dpc = SCR_CTI_DeathPositionComponent.Cast(pc.FindComponent(SCR_CTI_DeathPositionComponent));

		array<SCR_SpawnPoint> infos = SCR_SpawnPoint.getSpawnPointsForCTIPlayer(faction, dpc.getDeathPosition());
		
		if (infos.IsEmpty())
		{
			SetSpawnPoint(RplId.Invalid());
			return;
		}

		foreach (SCR_SpawnPoint info : infos)
		{
			AddSpawnPoint(info);
		}
	}
};