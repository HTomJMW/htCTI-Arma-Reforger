class SCR_CTI_TakeCommandAction : SCR_VehicleActionBase
{
	protected CarControllerComponent m_pCarController;
	protected FactionAffiliationComponent m_vehAffiliationComp;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_pCarController = CarControllerComponent.Cast(pOwnerEntity.FindComponent(CarControllerComponent));
		m_vehAffiliationComp = FactionAffiliationComponent.Cast(pOwnerEntity.FindComponent(FactionAffiliationComponent));
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_rplComponent = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		FactionAffiliationComponent affComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
		netComp.setCommanderIdRpl(affComp.GetAffiliatedFaction().GetFactionKey(), playerId);

		SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId);
		if (clientData) clientData.setCommander(true);
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		gameMode.bumpMeServer();
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(user);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		FactionAffiliationComponent affComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		IEntity veh = m_pCarController.GetOwner();
		ResourceName res = veh.GetPrefabData().GetPrefabName();
		VehicleWheeledSimulation simulation = VehicleWheeledSimulation.Cast(veh.FindComponent(VehicleWheeledSimulation));
		
		if (Math.AbsFloat(simulation.GetSpeedKmh()) > 5) return false; // check vehicle speed less then 5
		if (m_gameMode.getCommanderId(affComp.GetAffiliatedFaction().GetFactionKey()) != -2) return false; // check no comm
		if (affComp.GetAffiliatedFaction().GetFactionKey() == "USSR" && res != SCR_CTI_Constants.USSR_MHQ) return false; // check hq in user side
		if (affComp.GetAffiliatedFaction().GetFactionKey() == "US" && res != SCR_CTI_Constants.US_MHQ) return false; // check hq in user side
		if (m_gameMode.getCommanderId(affComp.GetAffiliatedFaction().GetFactionKey()) == playerId) return false; // check player is comm (after side check)

		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Take Command";

		return true;
	}
};