[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Town Patrol")]
class SCR_CTI_TownPatrolComponentClass : ScriptComponentClass
{
};

class SCR_CTI_TownPatrolComponent : ScriptComponent
{
	protected SCR_CTI_Town m_town;
	protected RplComponent m_RplComponent;
	
	protected float m_timeDelta = 30; // first waypoint need faster
	protected const float TIMESTEP = 45;
	
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
		vector rndpos = randomgen.GenerateRandomPointInRadius(50, 75, mat[3], true);

		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		params.Transform = mat;

		IEntity wpEntity = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), params);
		AIWaypoint wp = AIWaypoint.Cast(wpEntity);
		wp.SetCompletionRadius(5);
		wp.SetCompletionType(EAIWaypointCompletionType.Any);
		
		waypoints.Insert(wp);
		
		//PrintFormat("Town pos: %1, WP pos: %2", m_town.getFlagPos(), mat[3]);
	}

	//------------------------------------------------------------------------------------------------
	protected void updateWayPoints()
	{
		if (waypoints.Count() < 5)
		{
			createWayPoint();
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		if (m_town.isActive() && !m_RplComponent.IsProxy())
		{
			m_timeDelta += timeSlice;
			if (m_timeDelta > TIMESTEP)
			{
				updateWayPoints();

				m_timeDelta = 0;
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_TownPatrolComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_town = SCR_CTI_Town.Cast(ent);

		m_timeDelta = 30;
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_TownPatrolComponent()
	{
		waypoints.Clear();
		waypoints = null;
	}
};