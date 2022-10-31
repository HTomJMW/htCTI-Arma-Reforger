[EntityEditorProps(category: "GameScripted/CTI", description: "Handles client - server communication. Should be attached to PlayerController.")]
class SCR_CTI_NetWorkComponent : ScriptComponent
{
	protected SCR_PlayerController m_PlayerController;
	protected RplComponent m_RplComponent;
	protected SCR_PopUpNotification popUpNotif;

	//------------------------------------------------------------------------------------------------
	protected bool IsProxy()
	{
		return (m_RplComponent && m_RplComponent.IsProxy());
	}

	//------------------------------------------------------------------------------------------------
	void SendHint(int playerId, string message = "", string messageTitle = "", int hintTime = 5.0)
    {
        RpcAsk_RecieveHint(playerId, message, messageTitle, hintTime);
        Rpc(RpcAsk_RecieveHint, playerId, message, messageTitle, hintTime);
    }
   
	//------------------------------------------------------------------------------------------------
    [RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
    protected void RpcAsk_RecieveHint(int playerId, string message, string messageTitle, int hintTime)
    {
        int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
        if(playerId != localPlayerId) return;
        
        SCR_HintManagerComponent.ShowCustomHint(message, messageTitle, hintTime);
    }

	//------------------------------------------------------------------------------------------------
	void SendPopUpNotif(int playerId, string message = "", float duration = 5.0, float fade = 0.5, string message2 = "", int prio = -1)
	{
		RpcAsk_RecievePopUpNotif(playerId, message, duration, fade, message2, prio);
        Rpc(RpcAsk_RecievePopUpNotif, playerId, message, duration, fade, message2, prio);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
    protected void RpcAsk_RecievePopUpNotif(int playerId, string message, float duration, float fade, string message2, int prio)
    {
        int localPlayerId = GetGame().GetPlayerController().GetPlayerId();
        if(playerId != localPlayerId) return;

		popUpNotif.PopupMsg(message, duration, fade, message2);
    }

	//------------------------------------------------------------------------------------------------
	void unflipNearestVehicleServer(RplId rplId)
	{
		Rpc(RpcAsk_UnflipNearestVehicle, rplId);
		Rpc(RpcDo_UnflipNearestVehicle, rplId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_UnflipNearestVehicle(RplId rplId)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplId));
		IEntity vehicle = rplComp.GetEntity();
		
		RplIdentity rplIdentity = m_PlayerController.GetRplIdentity();
		rplComp.GiveExt(rplIdentity, true);

		Physics physics = vehicle.GetPhysics();
		
		vector vel = physics.GetVelocity();
		if (vel == "0 0 0")
		{
			physics.SetVelocity("0 4 0");

			vector angles = vehicle.GetAngles();
			if (angles[0] > 70 || angles[0] < -70) angles[0] = 0;
			if (angles[2] > 70 || angles[2] < -70) angles[2] = 0;
			vehicle.SetAngles(angles);
		}
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void RpcDo_UnflipNearestVehicle(RplId rplId)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplId));
		IEntity vehicle = rplComp.GetEntity();
		
		RplIdentity rplIdentity = m_PlayerController.GetRplIdentity();
		rplComp.GiveExt(rplIdentity, true);

		Physics physics = vehicle.GetPhysics();
		
		vector vel = physics.GetVelocity();
		if (vel == "0 0 0")
		{
			physics.SetVelocity("0 4 0");

			vector angles = vehicle.GetAngles();
			if (angles[0] > 70 || angles[0] < -70) angles[0] = 0;
			if (angles[2] > 70 || angles[2] < -70) angles[2] = 0;
			vehicle.SetAngles(angles);
		}
	}

	//------------------------------------------------------------------------------------------------
	void StartUpgradeServer(FactionKey fk, int selected)
	{
		Rpc(RpcAsk_StartUpgrade, fk, selected);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_StartUpgrade(FactionKey fk, int selected)
	{
		SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_CTI_UpgradeComponent));
		upgradeComp.runUpgrade(fk, selected);
	}

	//------------------------------------------------------------------------------------------------
	void StopUpgradeServer(FactionKey fk)
	{
		Rpc(RpcAsk_StopUpgrade, fk);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_StopUpgrade(FactionKey fk)
	{
		SCR_CTI_UpgradeComponent upgradeComp = SCR_CTI_UpgradeComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_CTI_UpgradeComponent));
		upgradeComp.stopUpgrade(fk);
	}

	//------------------------------------------------------------------------------------------------
	void setCommanderIdRpl(FactionKey fk, int playerId)
	{
		Rpc(RpcAsk_SetCommanderId, fk, playerId);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_SetCommanderId(FactionKey fk, int playerId)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		gameMode.setCommanderId(fk, playerId);
	}

	//------------------------------------------------------------------------------------------------
	void clearCommanderIdRpl(FactionKey fk)
	{
		Rpc(RpcAsk_ClearCommanderId, fk);
	}

	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_ClearCommanderId(FactionKey fk)
	{
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		gameMode.clearCommanderId(fk);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_PlayerController = SCR_PlayerController.Cast(PlayerController.Cast(owner));
		
		if (!m_PlayerController)
		{
			Print("SCR_CTI_NetworkComponent must be attached to PlayerController!", LogLevel.ERROR);
			return;
		}
		
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		popUpNotif = SCR_PopUpNotification.GetInstance();
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
		owner.SetFlags(EntityFlags.ACTIVE, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_NetWorkComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_NetWorkComponent()
	{
	}
};

class SCR_CTI_NetWorkComponentClass: ScriptComponentClass
{
};