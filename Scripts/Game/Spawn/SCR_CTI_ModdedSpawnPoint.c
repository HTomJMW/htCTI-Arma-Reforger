[EntityEditorProps(category: "GameScripted/CTI", description: "CTI - Modded Spawn point entity", visible: false)]
modded class SCR_SpawnPointClass : SCR_PositionClass
{
}

//------------------------------------------------------------------------------------------------
modded class SCR_SpawnPoint : SCR_Position
{
	[RplProp(onRplName: "OnDisplayNameChangedClient", condition: RplCondition.Custom, customConditionName: "RpcCondition")]
	string m_displayName = "SpawnPoint";

	//------------------------------------------------------------------------------------------------
	void setDisplayName(string name)
	{
		m_displayName = name;
		setUIInfo(m_displayName);

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	protected void setUIInfo(LocalizedString name)
	{
		SCR_UIInfo m_uiInfo = SCR_UIInfo.CreateInfo(name);
		m_Info = m_uiInfo;
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);

		m_bShowInDeployMapOnly = true;

		setUIInfo(m_displayName);
	}

	//------------------------------------------------------------------------------------------------
	protected bool RpcCondition()
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected void OnDisplayNameChangedClient()
	{
		setUIInfo(m_displayName);
	}

	//------------------------------------------------------------------------------------------------
	static array<SCR_SpawnPoint> getSpawnPointsForCTIPlayer(Faction faction, vector deathPos)
	{
		FactionKey factionKey = faction.GetFactionKey();

		array<SCR_SpawnPoint> playerSpawnPoints = new array<SCR_SpawnPoint>();

		array<IEntity> friendlyTowns = SCR_CTI_GetSideTowns.GetSideTowns(faction.GetFactionKey());
		IEntity closestFriendlyTown = null;
		if (!friendlyTowns.IsEmpty())
		{
			closestFriendlyTown = SCR_CTI_GetClosestEntity.GetClosestEntityToVector(deathPos, friendlyTowns);
		}

		array<SCR_SpawnPoint> spawnPoints = GetSpawnPoints();
		foreach (SCR_SpawnPoint spawnPoint : spawnPoints)
		{
			if (factionKey && spawnPoint && spawnPoint.GetFactionKey() == factionKey)
			{
				IEntity parent = spawnPoint.GetParent();

				if (!deathPos)
				{
					if (parent)
					{
						if (SCR_CTI_GetSideMHQ.GetSideMHQ(factionKey) == parent) playerSpawnPoints.Insert(spawnPoint);
					} else {
						string spName = spawnPoint.GetSpawnPointName();

						if (spName.Contains("Town") || spName.Contains("SpawnPoint"))
						{
							continue;
						} else {
							playerSpawnPoints.Insert(spawnPoint);
						}
					}
				} else {
					if (parent)
					{
						if (SCR_CTI_GetSideMHQ.GetSideMHQ(factionKey) == parent)
						{
							playerSpawnPoints.Insert(spawnPoint);
						} else {
							int range = 300;

							SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());

							int resp1index = gameMode.Upgrades.findIndexByName("Respawn Truck level 1");
							int resp2index = gameMode.Upgrades.findIndexByName("Respawn Truck level 2");
							int resp3index = gameMode.Upgrades.findIndexByName("Respawn Truck level 3");

							SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(gameMode.FindComponent(SCR_CTI_UpgradeComponent));

							switch (true)
							{
								case (upgradeComp.getUpgradeStatus(faction.GetFactionKey(), resp3index) == UpgradeStatus.FINISHED):
								{
									range = 2000;
									break;
								}
								case (upgradeComp.getUpgradeStatus(faction.GetFactionKey(), resp2index) == UpgradeStatus.FINISHED):
								{
									range = 1000;
									break;
								}
								case (upgradeComp.getUpgradeStatus(faction.GetFactionKey(), resp1index) == UpgradeStatus.FINISHED):
								{
									range = 500;
									break;
								}
							}

							float distance = vector.Distance(deathPos, parent.GetOrigin());

							if (distance <= range) playerSpawnPoints.Insert(spawnPoint);
						}
					} else {
						string spName = spawnPoint.GetSpawnPointName();

						if (closestFriendlyTown && spName.Contains("Town"))
						{
							SCR_CTI_Town town = SCR_CTI_Town.Cast(closestFriendlyTown);
							if (spName.Contains(town.getTownName())) playerSpawnPoints.Insert(spawnPoint);
						}
						
						if (!spName.Contains("Town") && !spName.Contains("SpawnPoint"))
						{
							playerSpawnPoints.Insert(spawnPoint);
						}
					}
				}
			}
		}

		return playerSpawnPoints;
	}
}
