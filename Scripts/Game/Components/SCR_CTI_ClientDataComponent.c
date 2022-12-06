[EntityEditorProps(category: "GameScripted/CTI", description: "Store Client Datas. Should be attached to PlayerController.")]
class SCR_CTI_ClientDataComponent : ScriptComponent
{
	protected SCR_PlayerController m_PlayerController;
	
	protected int m_playerId = -1;
	protected bool m_isCommander = false;
	protected int m_funds;
	
	//------------------------------------------------------------------------------------------------
	int getPlayerId()
	{
		return m_playerId;
	}

	//------------------------------------------------------------------------------------------------
	void setPlayerId(int id)
	{
		m_playerId = id;
	}

	//------------------------------------------------------------------------------------------------
	string getPlayerName()
	{
		return GetGame().GetPlayerManager().GetPlayerName(m_playerId);
	}
	
	//------------------------------------------------------------------------------------------------
	bool isCommander()
	{
		return m_isCommander;
	}

	//------------------------------------------------------------------------------------------------
	void setCommander(bool value)
	{
		m_isCommander = value;
	}
	
	//------------------------------------------------------------------------------------------------
	int getFunds()
	{
		return m_funds;
	}

	//------------------------------------------------------------------------------------------------
	void changeFunds(int value)
	{
		m_funds += (value);
		if (m_funds < 0) m_funds = 0;
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_PlayerController = SCR_PlayerController.Cast(PlayerController.Cast(owner));
		
		if (!m_PlayerController)
		{
			Print("SCR_CTI_ClientDataComponent must be attached to PlayerController!", LogLevel.ERROR);
			return;
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		
		SetEventMask(owner, EntityEvent.INIT);
		owner.SetFlags(EntityFlags.ACTIVE, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_ClientDataComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_ClientDataComponent()
	{
	}
};

class SCR_CTI_ClientDataComponentClass: ScriptComponentClass
{
};