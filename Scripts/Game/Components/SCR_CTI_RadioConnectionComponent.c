[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Radio Connection")]
class SCR_CTI_RadioConnectionComponentClass : ScriptComponentClass
{
};

class SCR_CTI_RadioConnectionComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	
	//------------------------------------------------------------------------------------------------
	void SCR_CTI_RadioConnectionComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_RadioConnectionComponent()
	{
	}
};