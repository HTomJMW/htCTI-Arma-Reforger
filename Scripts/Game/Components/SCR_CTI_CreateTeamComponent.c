[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Spawn AI groups")]
class SCR_CTI_CreateTeamComponentClass : ScriptComponentClass
{
};

void ScriptInvoker_OnSpawnerEmptyDelegate();
typedef func ScriptInvoker_OnSpawnerEmptyDelegate;
typedef ScriptInvokerBase<ScriptInvoker_OnSpawnerEmptyDelegate> ScriptInvoker_OnSpawnerEmpty;

class SCR_CTI_CreateTeamComponent : ScriptComponent
{
	protected RplComponent m_RplComponent;
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected ResourceName m_FIA_FireTeam = "{5BEA04939D148B1D}Prefabs/Groups/INDFOR/Group_FIA_FireTeam.et";
	protected ResourceName m_FIA_MGTeam = "{22F33D3EC8F281AB}Prefabs/Groups/INDFOR/Group_FIA_MachineGunTeam.et";
	protected ResourceName m_FIA_MedicalSection = "{581106FA58919E89}Prefabs/Groups/INDFOR/Group_FIA_MedicalSection.et";
	protected ResourceName m_FIA_PlatoonHQ = "{EE92725E9B949C3D}Prefabs/Groups/INDFOR/Group_FIA_PlatoonHQ.et";
	protected ResourceName m_FIA_ReconTeam = "{2E9C920C3ACA2C6F}Prefabs/Groups/INDFOR/Group_FIA_ReconTeam.et";
	protected ResourceName m_FIA_RifleSquad = "{CE41AF625D05D0F0}Prefabs/Groups/INDFOR/Group_FIA_RifleSquad.et";
	protected ResourceName m_FIA_SniperTeam = "{6307F42403E9B8A4}Prefabs/Groups/INDFOR/Group_FIA_SharpshooterTeam.et";
	protected ResourceName m_FIA_ATTeam = "{2CC26054775FBA2C}Prefabs/Groups/INDFOR/Group_FIA_Team_AT.et";

	protected ResourceName m_USSR_FireGroup = "{30ED11AA4F0D41E5}Prefabs/Groups/OPFOR/Group_USSR_FireGroup.et";
	protected ResourceName m_USSR_LightFireTeam = "{657590C1EC9E27D3}Prefabs/Groups/OPFOR/Group_USSR_LightFireTeam.et";
	protected ResourceName m_USSR_MGTeam = "{A2F75E45C66B1C0A}Prefabs/Groups/OPFOR/Group_USSR_MachineGunTeam.et";
	protected ResourceName m_USSR_ManeuverGroup = "{1A5F0D93609DA5DA}Prefabs/Groups/OPFOR/Group_USSR_ManeuverGroup.et";
	protected ResourceName m_USSR_MedicalSection = "{D815658156080328}Prefabs/Groups/OPFOR/Group_USSR_MedicalSection.et";
	protected ResourceName m_USSR_RifleSquad = "{E552DABF3636C2AD}Prefabs/Groups/OPFOR/Group_USSR_RifleSquad.et";
	protected ResourceName m_USSR_SentryTeam = "{CB58D90EA14430AD}Prefabs/Groups/OPFOR/Group_USSR_SentryTeam.et";
	protected ResourceName m_USSR_GLTeam = "{43C7A28EEB660FF8}Prefabs/Groups/OPFOR/Group_USSR_Team_GL.et";
	protected ResourceName m_USSR_ATTeam = "{96BAB56E6558788E}Prefabs/Groups/OPFOR/Group_USSR_Team_AT.et";
	protected ResourceName m_USSR_SuppressTeam = "{1C0502B5729E7231}Prefabs/Groups/OPFOR/Group_USSR_Team_Suppress.et";

	protected ResourceName m_US_FireTeam = "{84E5BBAB25EA23E5}Prefabs/Groups/BLUFOR/Group_US_FireTeam.et";
	protected ResourceName m_US_LightFireTeam = "{FCF7F5DC4F83955C}Prefabs/Groups/BLUFOR/Group_US_LightFireTeam.et";
	protected ResourceName m_US_MGTeam = "{958039B857396B7B}Prefabs/Groups/BLUFOR/Group_US_MachineGunTeam.et";
	protected ResourceName m_US_MedicalSection = "{EF62027CC75A7459}Prefabs/Groups/BLUFOR/Group_US_MedicalSection.et";
	protected ResourceName m_US_RifleSquad = "{DDF3799FA1387848}Prefabs/Groups/BLUFOR/Group_US_RifleSquad.et";
	protected ResourceName m_US_SentryTeam = "{3BF36BDEEB33AEC9}Prefabs/Groups/BLUFOR/Group_US_SentryTeam.et";
	protected ResourceName m_US_SniperTeam = "{D807C7047E818488}Prefabs/Groups/BLUFOR/Group_US_SniperTeam.et";
	protected ResourceName m_US_GLTeam = "{DE747BC9217D383C}Prefabs/Groups/BLUFOR/Group_US_Team_GL.et";
	protected ResourceName m_US_ATTeam = "{FAEA8B9E1252F56E}Prefabs/Groups/BLUFOR/Group_US_Team_LAT.et";
	protected ResourceName m_US_SuppressTeam = "{81B6DBF2B88545F5}Prefabs/Groups/BLUFOR/Group_US_Team_Suppress.et";

	protected AIAgent m_AIAgent;
	
	[Attribute("", UIWidgets.EditBox, "Group spawn position.", params: "inf inf 0 0 purposeCoords spaceWorld")]
	protected vector m_SpawnPos;
	[Attribute("", UIWidgets.EditBox, "Group spawn direction. (only yaw used)", params: "inf inf 0 0 purposeAngles spaceWorld")]
	protected vector m_SpawnDir;

	protected ref ScriptInvoker_OnSpawnerEmpty m_OnEmptyInvoker = new ScriptInvoker_OnSpawnerEmpty();
	
	//------------------------------------------------------------------------------------------------
	vector defaultCoords()
	{
		SCR_BaseTriggerEntity parent = SCR_BaseTriggerEntity.Cast(GetOwner());
		SCR_CTI_Town grandParent = SCR_CTI_Town.Cast(parent.GetParent());
		vector coords = grandParent.getFlagPos();
		
		return coords;
	}

	//------------------------------------------------------------------------------------------------
	AIAgent GetAgent()
	{
		return m_AIAgent;
	}

	//------------------------------------------------------------------------------------------------
	ScriptInvoker_OnSpawnerEmpty GetOnEmptyInvoker()
	{
		return m_OnEmptyInvoker;
	}

	//------------------------------------------------------------------------------------------------
	vector GetSpawnPos()
	{
		if (m_SpawnPos == "0 0 0")
		{
			Print("AI Spawn position is not set! Flag's position will be default");
			return defaultCoords();
		}
		
		return m_SpawnPos;
	}

	//------------------------------------------------------------------------------------------------
	vector GetSpawnDir()
	{
		return Vector(0.0, m_SpawnDir[1], 0.0);
	}

	//------------------------------------------------------------------------------------------------
	void GetSpawnTransform(out vector transformMatrix[4])
	{
		vector rotation = GetSpawnDir();
		vector yawPitchRoll = Vector(rotation[1], rotation[0], rotation[2]);
		Math3D.AnglesToMatrix(rotation, transformMatrix);		
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, GetSpawnPos(), 3);
		transformMatrix[3] = emptyPos;
	}

	//------------------------------------------------------------------------------------------------
	bool DoSpawn(ResourceName aiAgentPrefab, array<string> wayPoints = null)
	{
		if (!VerifyRplComponentPresent())
		{			
			Print("RPL Component missing!");
			return false;
		}
		
		Resource agentPrefab = Resource.Load(aiAgentPrefab);
		if (!agentPrefab)
		{
			Print("AgentPrefab load failed!");
			return false;
		}
		
		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.TransformMode = ETransformMode.WORLD;		
		GetSpawnTransform(spawnParams.Transform);
		
		IEntity spawnedEntity = GetGame().SpawnEntityPrefab(agentPrefab, GetOwner().GetWorld(), spawnParams);
		if (!spawnedEntity)
		{
			Print("Spawn Failed!");
			return false;
		}

		AIAgent agent = AIAgent.Cast(spawnedEntity);
		if (!agent)
		{
			Print("AI Agent type fail!");
			RplComponent.DeleteRplEntity(spawnedEntity, false);
			return false;
		}
		
		m_AIAgent = agent;

		SCR_AIGroup aiGroup = SCR_AIGroup.Cast(agent);
		
		//Set AI Skill
		SCR_AIConfigComponent aiConfigComponent = SCR_AIConfigComponent.Cast(aiGroup.FindComponent(SCR_AIConfigComponent));
		aiConfigComponent.m_Skill = m_gameMode.AISKILL;
		
		if (aiGroup)
		{
			aiGroup.GetOnEmpty().Insert(OnEmpty);
			m_town.m_groups.Insert(aiGroup);
		}
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected event void OnEmpty()
	{
		m_OnEmptyInvoker.Invoke();
	}

	//------------------------------------------------------------------------------------------------
#ifdef WORKBENCH
	protected override void _WB_AfterWorldUpdate(IEntity owner, float timeSlice)
	{
		super._WB_AfterWorldUpdate(owner, timeSlice);
		
		vector spawnPosition = GetSpawnPos();
		Shape shape = Shape.CreateSphere(COLOR_YELLOW, ShapeFlags.ONCE | ShapeFlags.NOOUTLINE, spawnPosition, 0.3);
		Shape arrow = Shape.CreateArrow(GetOwner().GetOrigin(), spawnPosition, 0.1, COLOR_YELLOW, ShapeFlags.ONCE);
	}
#endif

	//------------------------------------------------------------------------------------------------
	protected bool VerifyRplComponentPresent()
	{
		if (!m_RplComponent)
		{
			Print("RPL Component missing!");
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------------------
	void OnTriggerActivate()
	{
		if (m_RplComponent.IsProxy()) return; // run only on server side
		
		m_town.m_groups.Clear();	

		PrintFormat("CTI :: Town %1 - %2 AIs spawning", m_town.getTownName(), m_town.getFactionKey());

		int rnd = Math.RandomIntInclusive(0,5);
		switch (m_town.getFactionKey())
		{
			case "FIA":
				DoSpawn(m_FIA_FireTeam);
				switch (rnd)
				{
					case 0: DoSpawn(m_FIA_MGTeam);
							break;
					case 1:	DoSpawn(m_FIA_SniperTeam);
							break;
					case 2:	DoSpawn(m_FIA_ATTeam);
							break;
					case 3:	DoSpawn(m_FIA_MedicalSection);
							break;
					case 4:	DoSpawn(m_FIA_ReconTeam);
							break;
					case 5:	DoSpawn(m_FIA_ATTeam);
							break;
				}
				break;
			case "USSR":
				DoSpawn(m_USSR_FireGroup);
				switch (rnd)
				{
					case 0: DoSpawn(m_USSR_MGTeam);
							break;
					case 1:	DoSpawn(m_USSR_GLTeam);
							break;
					case 2:	DoSpawn(m_USSR_ATTeam);
							break;
					case 3:	DoSpawn(m_USSR_MedicalSection);
							break;
					case 4:	DoSpawn(m_USSR_ManeuverGroup);
							break;
					case 5:	DoSpawn(m_USSR_ATTeam);
							break;
				}
				break;
			case "US":
				DoSpawn(m_US_FireTeam);
				switch (rnd)
				{
					case 0: DoSpawn(m_US_MGTeam);
							break;
					case 1:	DoSpawn(m_US_GLTeam);
							break;
					case 2:	DoSpawn(m_US_ATTeam);
							break;
					case 3:	DoSpawn(m_US_MedicalSection);
							break;
					case 4:	DoSpawn(m_US_SniperTeam);
							break;
					case 5:	DoSpawn(m_US_ATTeam);
							break;
				}
				break;
			}
		PrintFormat("CTI :: Town %1 - Spawned groups: %2", m_town.getTownName(), m_town.m_groups);
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_RplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		if (!VerifyRplComponentPresent())
			return;

		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		SCR_CTI_ActivationArea parent = SCR_CTI_ActivationArea.Cast(owner);
		if (!parent)
		{
			Print("Must be SCR_CTI_ActivationArea component!");
			return;
		}
		
		m_town = SCR_CTI_Town.Cast(GetOwner().GetParent());
		m_town.m_groups.Clear();
		
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	override void OnDelete(IEntity owner)
	{
		SCR_AIGroup aiGroup = SCR_AIGroup.Cast(GetAgent());
		if (aiGroup) {aiGroup.GetOnEmpty().Remove(OnEmpty);}
	}

	//------------------------------------------------------------------------------------------------	
	void SCR_CTI_CreateTeamComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_CreateTeamComponent()
	{
	}
};