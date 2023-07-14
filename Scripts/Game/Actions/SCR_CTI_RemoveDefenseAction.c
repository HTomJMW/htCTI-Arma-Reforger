[EntityEditorProps(category: "GameScripted/CTI", description: "Remove Defense - User Action")]
class SCR_CTI_RemoveDefenseAction : ScriptedUserAction
{
	protected IEntity m_defense;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_defense = SCR_EntityHelper.GetMainParent(pOwnerEntity, true);
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_rplComponent = RplComponent.Cast(m_defense.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		SCR_EntityHelper.DeleteEntityAndChildren(m_defense);
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
		
		// TODO check: already in use (ladder or towers)
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "[Hold] Remove Defense";

		return true;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_RemoveDefenseAction()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_RemoveDefenseAction()
	{
	}
};