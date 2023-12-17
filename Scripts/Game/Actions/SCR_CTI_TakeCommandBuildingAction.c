[EntityEditorProps(category: "GameScripted/CTI", description: "Take Command on building - User Action")]
class SCR_CTI_TakeCommandBuildingAction : ScriptedUserAction
{
	protected IEntity m_building;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_building = SCR_EntityHelper.GetMainParent(pOwnerEntity, true);
		m_rplComponent = RplComponent.Cast(m_building.FindComponent(RplComponent));
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
		
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		gameMode.bumpMeServer();
		
		PrintFormat("CTI :: %2 commandship taken by Player %1", GetGame().GetPlayerManager().GetPlayerName(playerId), affComp.GetAffiliatedFaction().GetFactionKey());
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
	override bool CanBeShownScript(IEntity user)
	{
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(user);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		FactionAffiliationComponent playerFactionAffComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));

		if (m_gameMode.getCommanderId(playerFactionAffComp.GetAffiliatedFaction().GetFactionKey()) != -2) return false; // check no comm

		IEntity door = m_rplComponent.GetEntity(); // no initialized m_building here
		IEntity mainBuilding = SCR_EntityHelper.GetMainParent(door, true);

		SCR_CTI_BuildingCustomVariablesComponent m_customVarComp = SCR_CTI_BuildingCustomVariablesComponent.Cast(mainBuilding.FindComponent(SCR_CTI_BuildingCustomVariablesComponent));

		if (playerFactionAffComp.GetAffiliatedFaction().GetFactionKey() != m_customVarComp.getFactionKey()) return false; // check side
		if (m_gameMode.getCommanderId(playerFactionAffComp.GetAffiliatedFaction().GetFactionKey()) == playerId) return false; // check player is comm (after side check)

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Take Command";

		return true;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_TakeCommandBuildingAction()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_TakeCommandBuildingAction()
	{
	}
};