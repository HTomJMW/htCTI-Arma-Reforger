class SCR_CTI_TakeCommandAction : SCR_VehicleActionBase
{
	protected CarControllerComponent m_pCarController;
	protected FactionAffiliationComponent m_vehAffiliationComp;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected ResourceName USSR_mhq = "{1BABF6B33DA0AEB6}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_command.et";
	protected ResourceName US_mhq = "{36BDCC88B17B3BFA}Prefabs/Vehicles/Wheeled/M923A1/M923A1_command.et";

	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_pCarController = CarControllerComponent.Cast(pOwnerEntity.FindComponent(CarControllerComponent));
		m_vehAffiliationComp = FactionAffiliationComponent.Cast(pOwnerEntity.FindComponent(FactionAffiliationComponent));
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}
	
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	void PerformScriptedContinuousAction(IEntity pOwnerEntity, IEntity pUserEntity, float timeSlice)
	{
	}
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		FactionAffiliationComponent affComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_gameMode.setCommanderId(affComp.GetAffiliatedFaction().GetFactionKey(), playerId);
		
		int sizeCDA = m_gameMode.ClientDataArray.Count();
		SCR_CTI_ClientData clientData;
		for (int i = 0; i < sizeCDA; i++)
		{
			if (m_gameMode.ClientDataArray[i].getPlayerId() == playerId)
			{
				clientData = m_gameMode.ClientDataArray[i];
				break;
			}
		}
		
		if (clientData)
		{
			clientData.setCommander(true);
		}
	}
	
	//! Method called from scripted interaction handler when an action is started (progress bar appeared)
	//! \param pUserEntity The entity that started performing this action
	override void OnActionStart(IEntity pUserEntity)
	{
	}

	//! Action canceled
	//! \param pUserEntity The entity that started performing this action
	override void OnActionCanceled(IEntity pOwnerEntity, IEntity pUserEntity)
	{
	}

	override bool CanBeShownScript(IEntity user)
	{
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(user);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		FactionAffiliationComponent affComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		IEntity veh = m_pCarController.GetOwner();
		ResourceName res = veh.GetPrefabData().GetPrefabName();
		
		if (m_gameMode.getCommanderId(affComp.GetAffiliatedFaction().GetFactionKey()) != -2) return false; // check no comm
		if (affComp.GetAffiliatedFaction().GetFactionKey() == "USSR" && res != USSR_mhq) return false; // check hq in user side
		if (affComp.GetAffiliatedFaction().GetFactionKey() == "US" && res != US_mhq) return false; // check hq in user side
		if (m_gameMode.getCommanderId(affComp.GetAffiliatedFaction().GetFactionKey()) == playerId) return false; // check player is comm (after side check)
		
		return true;
	}

	override bool GetState()
	{
	}

	override void SetState(bool enable)
	{
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = "Take Command";

		return true;
	}
};