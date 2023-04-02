[EntityEditorProps(category: "GameScripted/CTI", description: "Structure placing")]
class SCR_CTI_PlacingStructureComponentClass: ScriptComponentClass
{
};

class SCR_CTI_PlacingStructureComponent : ScriptComponent
{
	protected PlayerController m_PlayerController;
	protected RplComponent m_RplComponent;
	
	protected FactionKey m_fk;
	protected ResourceName m_resName;

	protected SCR_BasePreviewEntity m_structure = null;
	
	protected vector finalMat[4];
	
	protected bool m_startPlacing = false;
	
	protected float m_dist;
	protected int m_placement;
	
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
	void createStructurePreview(FactionKey fk, ResourceName resName, float distance, int placement, bool startPlacing)
	{
		m_fk = fk;
		m_resName = resName;
		m_dist = distance;
		m_placement = placement;
		
		vector mat[4];
		vector dir;
		
		IEntity m_player = m_PlayerController.GetControlledEntity();
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

		m_structure = SCR_PrefabPreviewEntity.SpawnPreviewFromPrefab(resource, "SCR_PrefabPreviewEntity", GetGame().GetWorld(), params, m_material);

		if (m_structure)
		{
			PrintFormat("CTI :: Created Structure preview: %1", m_structure);

			m_structure.GetPreviewBounds(m_boundmins, m_boundmaxs);
			m_radius = (vector.DistanceXZ(m_boundmins, m_boundmaxs)) * 0.5;
			m_maxDifference = m_radius * 0.15;
			
			Math3D.MatrixIdentity3(m_paramOBB.Mat);
			m_paramOBB.Flags = TraceFlags.ENTS;
			m_paramOBB.Exclude = m_structure;
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

		SCR_CTI_HierarchyTransform.SetHierarchyTransform(m_structure, mat);
		
		m_paramOBB.Mat[0] = mat[0];
		m_paramOBB.Mat[1] = mat[1];
		m_paramOBB.Mat[2] = mat[2];
		m_paramOBB.Start = mat[3] + "0 0.05 0";
		
		GetGame().GetWorld().TracePosition(m_paramOBB, null);

		if (!SCR_CTI_TerrainIsFlat.isFlat(mat[3], m_radius, m_maxDifference) || mat[3][1] < 0 || m_paramOBB.TraceEnt)
		{
			SCR_Global.SetMaterial(m_structure, m_materialRed);
			m_blocked = true;
		} else {
			SCR_Global.SetMaterial(m_structure, m_material);
			m_blocked = false;
		}
		
		m_structure.Update();

		finalMat = mat;
	}
	
	//------------------------------------------------------------------------------------------------
	void performBuilding()
	{
		if (m_blocked) return;

		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();

		m_startPlacing = false;
		
		SCR_EntityHelper.DeleteEntityAndChildren(m_structure);
		
		SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(m_PlayerController.FindComponent(SCR_CTI_NetWorkComponent));
		netComp.buildStructureServer(m_fk, m_resName, finalMat);
	}

	//------------------------------------------------------------------------------------------------
	void cancelBuilding()
	{
		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();
		
		m_startPlacing = false;

		if (m_structure) SCR_EntityHelper.DeleteEntityAndChildren(m_structure);
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
	void SCR_CTI_PlacingStructureComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_PlacingStructureComponent()
	{
	}
};