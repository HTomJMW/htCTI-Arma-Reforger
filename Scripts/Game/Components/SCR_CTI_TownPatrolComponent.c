[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Town Patrol")]
class SCR_CTI_TownPatrolComponentClass : ScriptComponentClass
{
};

class SCR_CTI_TownPatrolComponent : ScriptComponent
{
	protected SCR_CTI_Town m_town;
	protected RplComponent m_RplComponent;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 60;
	
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
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_town = SCR_CTI_Town.Cast(owner);
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		m_timeDelta = 0;
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				if (m_town.isActive())
				{
					updateWayPoints();
				}
				m_timeDelta = 0;
			}
	}

	//------------------------------------------------------------------------------------------------
	override void OnDelete(IEntity owner)
	{
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_TownPatrolComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_TownPatrolComponent()
	{
		waypoints.Clear();
		waypoints = null;
	}
};