[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Factory Spawn")]
class SCR_CTI_FactorySpawnComponentClass : ScriptComponentClass
{
};

class SCR_CTI_FactorySpawnComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	
	[Attribute("", UIWidgets.EditBox, "Spawn position.", params: "inf inf 0 0 purposeCoords spaceWorld")]
	protected vector m_SpawnPos;
	[Attribute("", UIWidgets.EditBox, "Spawn direction. (only yaw used)", params: "inf inf 0 0 purposeAngles spaceWorld")]
	protected vector m_SpawnDir;

	//------------------------------------------------------------------------------------------------
	vector GetSpawnPos()
	{	
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
		transformMatrix[3] = m_SpawnPos;
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
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		SCR_DestructibleBuildingEntity parent = SCR_DestructibleBuildingEntity.Cast(owner);
		if (!parent)
		{
			Print("Must be SCR_DestructibleBuildingEntity component!");
			return;
		}
		
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	override void OnDelete(IEntity owner)
	{
	}

	//------------------------------------------------------------------------------------------------	
	void SCR_CTI_FactorySpawnComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_FactorySpawnComponent()
	{
	}
};