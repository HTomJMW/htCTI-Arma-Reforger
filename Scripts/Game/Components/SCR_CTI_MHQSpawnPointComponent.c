[EntityEditorProps(category: "GameScripted/CTI", description: "MHQ Spawn Point.", color: "0 0 255 255")]
class SCR_CTI_MHQSpawnPointComponentClass: ScriptGameComponentClass
{
};

class SCR_CTI_MHQSpawnPointComponent : ScriptGameComponent
{
	protected IEntity m_vehicleEnt;
	protected SCR_VehicleFactionAffiliationComponent m_vehfacaffcomp;
	protected SCR_VehicleDamageManagerComponent m_vehdamagecomp;
	protected SCR_SpawnPoint m_sp;
	protected FactionKey m_fk;
	
	bool m_enabled = false;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 1;

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_vehicleEnt = GetOwner();
		BaseWorld world = GetGame().GetWorld();
		SCR_SpawnPoint spNorth = SCR_SpawnPoint.Cast(world.FindEntityByName("SpawnPointNorth"));
		SCR_SpawnPoint spSouth = SCR_SpawnPoint.Cast(world.FindEntityByName("SpawnPointSouth"));
		
		m_vehfacaffcomp = SCR_VehicleFactionAffiliationComponent.Cast(m_vehicleEnt.FindComponent(SCR_VehicleFactionAffiliationComponent));
		m_fk = m_vehfacaffcomp.GetDefaultAffiliatedFaction().GetFactionKey();
		
		if (spNorth.GetFactionKey() == m_fk)
		{
			m_sp = spNorth;
		} else {
			m_sp = spSouth;
		}
		
		m_vehdamagecomp = SCR_VehicleDamageManagerComponent.Cast(m_vehicleEnt.FindComponent(SCR_VehicleDamageManagerComponent));
		
		SetEventMask(GetOwner(), EntityEvent.FIXEDFRAME);
		m_timeDelta = 0;
		m_enabled = true;
	}
	
	//------------------------------------------------------------------------------------------------
	protected void Update()
	{
		vector pos = m_vehicleEnt.GetOrigin();
		m_sp.SetOrigin(pos);
		
		if (m_vehdamagecomp.IsDestroyed())
		{
			m_sp.SetFactionKey("FIA"); //Deactivate() not working
		} else {
			m_sp.SetFactionKey(m_fk);
		}

		m_timeDelta = 0;
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP && m_enabled) Update();
	}
};
