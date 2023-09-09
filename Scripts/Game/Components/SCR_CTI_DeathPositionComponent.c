[EntityEditorProps(category: "GameScripted/CTI", description: "Last death position component. Should be attached to PlayerController.")]
class SCR_CTI_DeathPositionComponentClass: ScriptComponentClass
{
};

class SCR_CTI_DeathPositionComponent : ScriptComponent
{
	protected SCR_PlayerController m_PlayerController;
	protected RplComponent m_RplComponent;
	
	protected vector m_deathPosition;
	
	//------------------------------------------------------------------------------------------------
	vector getDeathPosition()
	{
		return m_deathPosition;
	}

	//------------------------------------------------------------------------------------------------
	protected bool IsProxy()
	{
		return (m_RplComponent && m_RplComponent.IsProxy());
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_PlayerController = SCR_PlayerController.Cast(PlayerController.Cast(owner));
		
		if (!m_PlayerController)
		{
			Print("CTI :: SCR_CTI_DeathPositionComponent must be attached to PlayerController!", LogLevel.ERROR);
			return;
		} else {
			m_PlayerController.m_OnDestroyed.Insert(OnCharacterDestroyed);
		}
		
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
	}
	
	//------------------------------------------------------------------------------------------------
	protected void OnCharacterDestroyed()
	{
		m_deathPosition = m_PlayerController.GetControlledEntity().GetOrigin();
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
		owner.SetFlags(EntityFlags.ACTIVE, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_DeathPositionComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_DeathPositionComponent()
	{
		if (m_PlayerController) m_PlayerController.m_OnDestroyed.Remove(OnCharacterDestroyed);
	}
};