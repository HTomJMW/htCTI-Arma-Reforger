[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Player Resources")]
class SCR_CTI_UpdateResourcesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateResourcesComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	void update()
	{
		int CDA = m_gameMode.ClientDataArray.Count();
		for (int i = 0; i < CDA; i++)
		{
			SCR_CTI_ClientData clientData = m_gameMode.ClientDataArray[i];
			if (clientData)
			{
				if (clientData.isCommander())
				{
					int factionIndex = clientData.getFactionIndex();
					m_gameMode.changeCommanderFunds(GetGame().GetFactionManager().GetFactionByIndex(factionIndex).GetFactionKey(), SCR_CTI_Constants.BASEINCOME * 5);
				} else {
					if (GetGame().GetPlayerManager().IsPlayerConnected(clientData.getPlayerId())) clientData.changeFunds(SCR_CTI_Constants.BASEINCOME);
				}
			}	
		}
		m_gameMode.bumpMeServer();
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
	
		SetEventMask(owner, EntityEvent.INIT);
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		if (!m_rplComponent.IsProxy()) GetGame().GetCallqueue().CallLater(update, 45 * 1000, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateResourcesComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(ent);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateResourcesComponent()
	{
	}	
};