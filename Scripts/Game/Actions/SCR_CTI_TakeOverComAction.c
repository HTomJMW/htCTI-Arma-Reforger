[EntityEditorProps(category: "GameScripted/CTI", description: "User Action")]
class SCR_CTI_TakeOverComAction : ScriptedUserAction
{
	protected IEntity m_owner;
	protected FactionAffiliationComponent m_userAffiliationComponent;
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_ClientData m_clientData;

	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_owner = pOwnerEntity;
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{	
		RplComponent rplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
		if (!rplComp)	
		{	
			Print("RPL component missing! (SCR_CTI_TakeOverComAction)");
			return;
		}

		RplId destructibleID = rplComp.Id();
		if (!destructibleID.IsValid())
		{
			Print("RplId not valid! (SCR_CTI_TakeOverComAction)");
			return;
		}
		
		//todo
	}

	override bool HasLocalEffectOnlyScript()
	{
		return true;
	}

	override bool CanBePerformedScript(IEntity user)
	{
		PlayerController playerController = GetGame().GetPlayerController();
		int playerId = playerController.GetPlayerId();
		
		int sizeCDA = m_gameMode.ClientDataArray.Count();
		for (int i = 0; i < sizeCDA; i++)
		{
			if (m_gameMode.ClientDataArray[i].getPlayerId() == playerId)
			{
				m_clientData = m_gameMode.ClientDataArray[i];
				break;
			}
		}
		
		if (m_clientData)
			{
				int funds = m_clientData.getFunds();
				
				if (m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
				{
					// todo
				} else {
					// todo
				}
			}

		return true;
	}

	override bool CanBeShownScript(IEntity user)
	{
		if (!m_userAffiliationComponent) m_userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		
		return true;
	}

	override bool GetActionNameScript(out string outName)
	{
		ActionNameParams[0] = "PARAM1";
		ActionNameParams[1] = "PARAM2";
					
		outName = ("Take Command");
		
		return true;
	}
	
	void SCR_CTI_TakeOverComAction()
	{
	}

	void ~SCR_CTI_TakeOverComAction()
	{
	}
};