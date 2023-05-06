[BaseContainerProps(), SCR_BaseContainerCustomTitleEnum(ENotification, "m_NotificationKey")]
class SCR_CTI_NotificationTown : SCR_NotificationDisplayData
{
	override string GetText(SCR_NotificationData data)
	{		
		int townIndex;
		data.GetParams(townIndex);

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		string townName = gameMode.CTI_Towns[townIndex].getTownName();

		data.SetNotificationTextEntries(townName);
		return super.GetText(data);
	}
};