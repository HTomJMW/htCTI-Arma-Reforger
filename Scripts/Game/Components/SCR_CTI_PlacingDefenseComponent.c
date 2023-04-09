[EntityEditorProps(category: "GameScripted/CTI", description: "Defense placing")]
class SCR_CTI_PlacingDefenseComponentClass: ScriptComponentClass
{
};

class SCR_CTI_PlacingDefenseComponent : ScriptComponent
{
	protected PlayerController m_PlayerController;
	protected RplComponent m_RplComponent;
	protected FactionKey m_fk;
	
	protected ResourceName m_resName;

	protected SCR_BasePreviewEntity m_defense = null;

	protected vector finalMat[4];
	
	protected bool m_startPlacing = false;
	
	protected float m_dist;
	protected float m_placement;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.02;
	
	protected ResourceName m_material = "{58F07022C12D0CF5}Assets/Editor/PlacingPreview/Preview.emat";
	protected ResourceName m_materialRed = "{F34CA01A59FDBED4}Assets/Editor/PlacingPreview/PreviewRed.emat";
	
	protected bool m_blocked = false;
	protected float m_radius;
	protected float m_maxDifference;
	
	protected ref TraceOBB m_paramOBB = new TraceOBB();
	
	protected vector m_boundmins;
	protected vector m_boundmaxs;

	//------------------------------------------------------------------------------------------------
	bool getStartPlacing()
	{
		return m_startPlacing;
	}

	//------------------------------------------------------------------------------------------------
	void createDefPreview(ResourceName resName, float distance, float placement, bool startPlacing)
	{
		m_resName = resName;
		m_dist = distance;
		m_placement = placement;

		vector mat[4];
		vector dir;
		
		IEntity m_player = m_PlayerController.GetControlledEntity();
		
		FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(m_PlayerController.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_fk = faffComp.GetAffiliatedFaction().GetFactionKey();
		
		m_player.GetTransform(mat);
		dir = m_player.GetWorldTransformAxis(2);

		vector angles = Math3D.MatrixToAngles(mat);
		angles[0] = angles[0] + placement;
		Math3D.AnglesToMatrix(angles, mat);

		mat[3] = mat[3] + (dir * m_dist);
		mat[3][1] = GetGame().GetWorld().GetSurfaceY(mat[3][0], mat[3][2]);

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;
		
		Resource resource = Resource.Load(resName);

		m_defense = SCR_PrefabPreviewEntity.SpawnPreviewFromPrefab(resource, "SCR_PrefabPreviewEntity", GetGame().GetWorld(), params, m_material);

		if (m_defense)
		{
			PrintFormat("CTI :: Created Def preview: %1", m_defense);

			m_defense.GetPreviewBounds(m_boundmins, m_boundmaxs);
			m_radius = (vector.DistanceXZ(m_boundmins, m_boundmaxs)) * 0.5;
			m_maxDifference = m_radius * 0.075;
			
			Math3D.MatrixIdentity3(m_paramOBB.Mat);
			m_paramOBB.Flags = TraceFlags.ENTS;
			m_paramOBB.Exclude = m_defense;
			m_paramOBB.LayerMask = EPhysicsLayerPresets.Projectile;
			m_paramOBB.Mins = m_boundmins;
			m_paramOBB.Maxs = m_boundmaxs;
	
			m_startPlacing = startPlacing;
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void updatePreiew()
	{
		vector mat[4];
		vector dir;
		
		IEntity m_player = m_PlayerController.GetControlledEntity();
		if (!m_player)
		{
			cancelBuilding();
			return;
		}
		m_player.GetTransform(mat);
		dir = m_player.GetWorldTransformAxis(2);

		vector angles = Math3D.MatrixToAngles(mat);
		angles[0] = angles[0] + m_placement;
		Math3D.AnglesToMatrix(angles, mat);

		mat[3] = mat[3] + (dir * m_dist);
		mat[3][1] = GetGame().GetWorld().GetSurfaceY(mat[3][0], mat[3][2]);

		SCR_CTI_HierarchyTransform.SetHierarchyTransform(m_defense, mat);

		m_paramOBB.Mat[0] = mat[0];
		m_paramOBB.Mat[1] = mat[1];
		m_paramOBB.Mat[2] = mat[2];
		m_paramOBB.Start = mat[3] + "0 0.05 0";
		
		GetGame().GetWorld().TracePosition(m_paramOBB, null);
		
		bool mhqInRange = false;
		IEntity mhq = SCR_CTI_GetSideMHQ.GetSideMHQ(m_fk);
		if (mhq)
		{
			SCR_VehicleDamageManagerComponent vdmc = SCR_VehicleDamageManagerComponent.Cast(mhq.FindComponent(SCR_VehicleDamageManagerComponent));
			float dist = vector.Distance(mhq.GetOrigin(), m_player.GetOrigin());
			if (dist <= SCR_CTI_Constants.BUILDRANGE && !vdmc.IsDestroyed()) mhqInRange = true;
		}

		if (!SCR_CTI_TerrainIsFlat.isFlat(mat[3], m_radius, m_maxDifference) || mat[3][1] < 0 || m_paramOBB.TraceEnt || !mhqInRange)
		{
			SCR_Global.SetMaterial(m_defense, m_materialRed);
			m_blocked = true;
		} else {
			SCR_Global.SetMaterial(m_defense, m_material);
			m_blocked = false;
		}

		m_defense.Update();

		finalMat = mat;
	}

	//------------------------------------------------------------------------------------------------
	void performBuilding()
	{
		if (m_blocked) return;

		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();

		m_startPlacing = false;

		SCR_EntityHelper.DeleteEntityAndChildren(m_defense);

		SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(m_PlayerController.FindComponent(SCR_CTI_NetWorkComponent));
		netComp.buildDefenseServer(m_resName, finalMat, m_PlayerController.GetPlayerId());
	}

	//------------------------------------------------------------------------------------------------
	void cancelBuilding()
	{
		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();
		
		m_startPlacing = false;
		
		if (m_defense) SCR_EntityHelper.DeleteEntityAndChildren(m_defense);
	}

	//------------------------------------------------------------------------------------------------
	protected bool IsProxy()
	{
		return (m_RplComponent && m_RplComponent.IsProxy());
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_PlayerController = PlayerController.Cast(owner);
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		SetEventMask(owner, EntityEvent.INIT | EntityEvent.FIXEDFRAME);
		owner.SetFlags(EntityFlags.ACTIVE, true);
		
		m_timeDelta = 0;
	}
	
	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		if ((m_startPlacing && IsProxy()) || (m_startPlacing && m_RplComponent.IsMaster()))
		{
			m_timeDelta += timeSlice;
			if (m_timeDelta > TIMESTEP)
			{
				updatePreiew();
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_PlacingDefenseComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_PlacingDefenseComponent()
	{
	}
};