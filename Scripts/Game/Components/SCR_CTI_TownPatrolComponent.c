[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Town Patrol")]
class SCR_CTI_TownPatrolComponentClass : ScriptComponentClass
{
};

class SCR_CTI_TownPatrolComponent : ScriptComponent
{
	protected SCR_CTI_Town m_town;
	protected RplComponent m_RplComponent;
	
	ref array<AIWaypoint> waypoints = {};

	//------------------------------------------------------------------------------------------------
	protected void createWayPoint()
	{
		ResourceName wpRes = "{22A875E30470BD4F}Prefabs/AI/Waypoints/AIWaypoint_Patrol.et";
		Resource res = Resource.Load(wpRes);
		
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		vector mat[4];
		m_town.GetTransform(mat);

		RandomGenerator randomgen = new RandomGenerator();
		vector rndpos = randomgen.GenerateRandomPointInRadius(25, 75, mat[3], true);

		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		params.Transform = mat;

		IEntity wpEntity = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), params);
		AIWaypoint wp = AIWaypoint.Cast(wpEntity);
		wp.SetCompletionRadius(5);
		wp.SetCompletionType(EAIWaypointCompletionType.Any);
		
		waypoints.Insert(wp);
		//PrintFormat("CTI :: Town name: %1, Town pos: %2, WP pos: %3", m_town.getTownName(), m_town.getFlagPos(), mat[3]);
	}

	//------------------------------------------------------------------------------------------------
	protected void updateWayPoints()
	{
		if (waypoints.Count() < 4 && m_town.isActive())
		{
			createWayPoint();
			createWayPoint();
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		
		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		
		if (!m_RplComponent.IsProxy())
		{
			GetGame().GetCallqueue().CallLater(updateWayPoints, 45 * 1000, true);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_TownPatrolComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_town = SCR_CTI_Town.Cast(ent);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_TownPatrolComponent()
	{
		if (!waypoints) return;
		waypoints.Clear();
		waypoints = null;
	}
};