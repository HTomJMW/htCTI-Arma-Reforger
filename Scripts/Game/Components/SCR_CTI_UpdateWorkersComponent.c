[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Workers")]
class SCR_CTI_UpdateWorkersComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateWorkersComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

	ref array<IEntity> m_ussrWorkers = {};
	ref array<IEntity> m_usWorkers = {};

	[RplProp()]
	protected int m_ussrWorkersCount = 0;
	[RplProp()]
	protected int m_usWorkersCount = 0;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 30;
	
	//------------------------------------------------------------------------------------------------
	//server only
	void addWorker(FactionKey factionkey)
	{
		if (m_rplComponent.IsProxy()) return;

		IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(factionkey);
		vector mat[4];
		mhq.GetTransform(mat);
		
		RandomGenerator randomgen = new RandomGenerator();
		vector rndpos = randomgen.GenerateRandomPointInRadius(4, 8, mat[3], true);
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		ResourceName workerResName;
		switch (factionkey)
		{
			case "USSR": workerResName = SCR_CTI_Constants.USSR_WORKER; break;
			case "US": workerResName = SCR_CTI_Constants.US_WORKER; break;
		}

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;

		IEntity worker = GetGame().SpawnEntityPrefab(Resource.Load(workerResName), GetGame().GetWorld(), params);

		if (worker)
		{
			switch (factionkey)
			{
				case "USSR": m_ussrWorkers.Insert(worker); m_ussrWorkersCount++; break;
				case "US": m_usWorkers.Insert(worker); m_usWorkersCount++; break;
			}
			
			EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(worker.FindComponent(EventHandlerManagerComponent));
			if (ehManager)
			{
				ehManager.RegisterScriptHandler("OnDestroyed", this, OnDestroyed);
			}

			m_gameMode.changeCommanderFunds(factionkey, -SCR_CTI_Constants.WORKERPRICE);
			
			Replication.BumpMe();
		}
	}

	//------------------------------------------------------------------------------------------------
	int getWorkersCount(FactionKey factionkey)
	{
		int workersCount = 0;

		switch (factionkey)
		{
			case "USSR":
			{
				workersCount = m_ussrWorkersCount;
				break;
			}
			case "US":
			{
				workersCount = m_usWorkersCount;
				break;
			}
		}
		
		return workersCount;
	}

	//------------------------------------------------------------------------------------------------
	protected void OnDestroyed(IEntity ent)
	{
		if (m_rplComponent.IsProxy()) return;
		
		FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		switch (faffComp.GetDefaultAffiliatedFaction().GetFactionKey())
		{
			case "USSR": m_ussrWorkersCount--; break;
			case "US": m_usWorkersCount--; break;
		}
		
		Replication.BumpMe();
		
		EventHandlerManagerComponent ehManager = EventHandlerManagerComponent.Cast(ent.FindComponent(EventHandlerManagerComponent));
		if (ehManager)
		{
			ehManager.RemoveScriptHandler("OnDestroyed", this, OnDestroyed);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{	
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
		{
			//TODO
	
			m_timeDelta = 0;
		}
		
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_rplComponent = RplComponent.Cast(m_gameMode.FindComponent(RplComponent));

		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateWorkersComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(ent);

		m_timeDelta = 0;
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateWorkersComponent()
	{
		m_ussrWorkers.Clear();
		m_ussrWorkers = null;
		m_usWorkers.Clear();
		m_usWorkers = null;
	}
};