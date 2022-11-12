class SCR_CTI_TakeCommandAction : SCR_VehicleActionBase
{
	protected CarControllerComponent m_pCarController;
	protected FactionAffiliationComponent m_vehAffiliationComp;
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_pCarController = CarControllerComponent.Cast(pOwnerEntity.FindComponent(CarControllerComponent));
		m_vehAffiliationComp = FactionAffiliationComponent.Cast(pOwnerEntity.FindComponent(FactionAffiliationComponent));
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	void PerformScriptedContinuousAction(IEntity pOwnerEntity, IEntity pUserEntity, float timeSlice)
	{
	}

	//------------------------------------------------------------------------------------------------
	// PerformAction part running on server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		FactionAffiliationComponent affComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
		netComp.setCommanderIdRpl(affComp.GetAffiliatedFaction().GetFactionKey(), playerId);
		
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
			
			SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
			if (affComp.GetAffiliatedFaction().GetFactionKey() == "USSR")
			{
				clientData.changeFunds(gameMode.getCommanderFunds("USSR"));
			} else {
				clientData.changeFunds(gameMode.getCommanderFunds("US"));
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	//! Method called from scripted interaction handler when an action is started (progress bar appeared)
	//! \param pUserEntity The entity that started performing this action
	override void OnActionStart(IEntity pUserEntity)
	{
	}

	//------------------------------------------------------------------------------------------------
	//! Action canceled
	//! \param pUserEntity The entity that started performing this action
	override void OnActionCanceled(IEntity pOwnerEntity, IEntity pUserEntity)
	{
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
		if (affComp.GetAffiliatedFaction().GetFactionKey() == "USSR" && res != m_gameMode.USSRMHQ) return false; // check hq in user side
		if (affComp.GetAffiliatedFaction().GetFactionKey() == "US" && res != m_gameMode.USMHQ) return false; // check hq in user side
		if (m_gameMode.getCommanderId(affComp.GetAffiliatedFaction().GetFactionKey()) == playerId) return false; // check player is comm (after side check)
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool GetState()
	{
	}

	//------------------------------------------------------------------------------------------------
	override void SetState(bool enable)
	{
	}
	
	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "Take Command";

		return true;
	}
};