[EntityEditorProps(category: "GameScripted/CTI", description: "Player resources. Should be attached to PlayerController.")]
class SCR_CTI_ClientPocketComponent : ScriptComponent
{
	protected SCR_PlayerController m_PlayerController;
	protected RplComponent m_RplComponent;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected int m_funds;

	//------------------------------------------------------------------------------------------------
	protected bool IsProxy()
	{
		return (m_RplComponent && m_RplComponent.IsProxy());
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
			Print("SCR_CTI_ClientPocketComponent must be attached to PlayerController!", LogLevel.ERROR);
			return;
		}
		
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		
		m_funds = m_gameMode.STARTFUNDS;
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
		owner.SetFlags(EntityFlags.ACTIVE, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_ClientPocketComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_ClientPocketComponent()
	{
	}
};

class SCR_CTI_ClientPocketComponentClass: ScriptComponentClass
{
};