[EntityEditorProps(category: "GameScripted/CTI", description: "Open Gear Menu User Action")]
class SCR_CTI_GearMenuAction : ScriptedUserAction
{
	protected SCR_DestructibleBuildingEntity m_building;
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_building = SCR_DestructibleBuildingEntity.Cast(pOwnerEntity.GetParent().GetParent());
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();
		GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_GearMenu);
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		FactionAffiliationComponent buildingAffiliationComponent = FactionAffiliationComponent.Cast(m_building.FindComponent(FactionAffiliationComponent));
		if (buildingAffiliationComponent.GetAffiliatedFaction() != userAffiliationComponent.GetAffiliatedFaction()) return false;
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{			
		outName = "Open Gear menu";
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_GearMenuAction()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GearMenuAction()
	{
	}
};