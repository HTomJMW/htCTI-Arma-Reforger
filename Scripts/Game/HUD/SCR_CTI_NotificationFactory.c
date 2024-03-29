[BaseContainerProps(), SCR_BaseContainerCustomTitleEnum(ENotification, "m_NotificationKey")]
class SCR_CTI_NotificationFactory : SCR_NotificationDisplayData
{
	override string GetText(SCR_NotificationData data)
	{		
		int factoryIndex, factionIndex, x, y, z;
		data.GetParams(factoryIndex, factionIndex, x, y, z);

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		SCR_CTI_FactoryData factoryData;
		switch (factionIndex)
		{
			case 1: factoryData = gameMode.FactoriesUS.g_US_Factories[factoryIndex]; break; // US
			case 2: factoryData = gameMode.FactoriesUSSR.g_USSR_Factories[factoryIndex]; break; // USSR
		}

		string factoryName = factoryData.getName();

		vector position;
		position[0] = x;
		position[1] = y;
		position[2] = z;

		int gridX, gridZ;
		SCR_MapEntity.GetGridPos(position, gridX, gridZ);
		string gridPos = gridX.ToString() + ", " + gridZ.ToString();

		data.SetNotificationTextEntries(factoryName, gridPos);
		return super.GetText(data);
	}
};