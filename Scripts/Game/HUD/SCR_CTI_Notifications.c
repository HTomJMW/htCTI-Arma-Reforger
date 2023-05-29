modded enum ENotification
{
	CTI_NOTIF_COMMANDER_ASSIGNED, // Player and Faction Notification (Param1: PlayerID)
	CTI_NOTIF_COMMANDER_LEFT, // Player Notification
	CTI_NOTIF_TOWN_PRIORITY_CHANGED, // Notification display data
	CTI_NOTIF_TOWN_CAPTURED, // Town Notification (Param1: Town index)
	CTI_NOTIF_TOWN_LOST, // Town Notification (Param1: Town index)
	CTI_NOTIF_MHQ_DESTROYED, // Notification display data
	CTI_NOTIF_MHQ_REPAIRED, // Notification display data
	CTI_NOTIF_FACTORY_CONSTRUCTED // Factory Notification (Param1: Factory index, Param2: Faction index, Param3: X, Param4: Y, Param5: Z coords)
};