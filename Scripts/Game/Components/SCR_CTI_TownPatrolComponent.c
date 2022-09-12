[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Town Patrol")]
class SCR_CTI_TownPatrolComponentClass : ScriptComponentClass
{
};

class SCR_CTI_TownPatrolComponent : ScriptComponent
{
	protected SCR_CTI_Town m_town;
	protected RplComponent m_RplComponent;
	
	ref array<AIWaypoint> waypoints = {};
	
	protected void addWayPoint()
	{
		
	}
	
	override void OnPostInit(IEntity owner)
	{
	}

	override void EOnInit(IEntity owner)
	{
		m_town = SCR_CTI_Town.Cast(owner);
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
	}
	
	override void OnDelete(IEntity owner)
	{
	}
	
	void SCR_CTI_TownPatrolComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}
	
	void ~SCR_CTI_TownPatrolComponent()
	{
	}
};