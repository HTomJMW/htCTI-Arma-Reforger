[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Spawn Mines")]
class SCR_CTI_CreateMinesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_CreateMinesComponent : ScriptComponent
{
	protected RplComponent m_RplComponent;
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected ResourceName m_resATmine = "{D6EF54367CECE1D9}Prefabs/Weapons/Explosives/Mine_TM62M/Mine_TM62M.et";
	protected ResourceName m_ussrATmine = "{D6EF54367CECE1D9}Prefabs/Weapons/Explosives/Mine_TM62M/Mine_TM62M.et";
	protected ResourceName m_usATmine = "{49FFE8F373F55960}Prefabs/Weapons/Explosives/Mine_M15AT/Mine_M15AT.et";

	protected ResourceName m_APmine = ""; // TODO pavements

	protected ref array<IEntity> m_roads = {};

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
	// server only
	void OnTriggerActivate()
	{
		if (m_RplComponent.IsProxy()) return;
		
		vector center = m_town.GetOrigin();
		float radius = 200.0;
		
		GetGame().GetWorld().QueryEntitiesBySphere(center, radius, GetRoadEntity, FilterEntities, EQueryEntitiesFlags.STATIC);
		
		array<int> possibleQuantity = {0, 0, 0, 2, 4, 5};
		int quantity = possibleQuantity.GetRandomElement();
		
		PrintFormat("CTI :: Mines number: %1", quantity);
		
		for (int i = 0; i < quantity; i++)
		{
			GetGame().GetCallqueue().CallLater(spawnMine, (i + 1) * 500, false);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void findRoadPosition(out vector transformMatrix[4])
	{
		IEntity randomRoad = m_roads.GetRandomElement();
		randomRoad.GetTransform(transformMatrix);
		transformMatrix[3] = transformMatrix[3] + (SCR_CTI_RandomDir.getRandomDir() * 1.25);
		transformMatrix[3][1] = GetGame().GetWorld().GetSurfaceY(transformMatrix[3][0], transformMatrix[3][2]);
		m_roads.RemoveItem(randomRoad);
	}
	
	//------------------------------------------------------------------------------------------------
	protected bool GetRoadEntity(IEntity ent)
	{
		m_roads.Insert(ent);

		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected bool FilterEntities(IEntity ent)
	{
		// Temporary until can't get Road segments
		if (ent.Type() == SCR_SiteSlotEntity/* || ent.Type() == DecalEntity*/)
		{
			//PrintFormat("CTI :: FILTER :: ENT: %1, RESNAME: %2, TYPE: %3", ent, ent.GetPrefabData().GetPrefabName(), ent.Type());
			return true;
		}

		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	void spawnMine()
	{
		ResourceName m_ATmine = m_resATmine;
		
		switch (m_town.getFactionKey())
		{
			case "USSR": m_ATmine = m_ussrATmine; break;
			case "US": m_ATmine = m_usATmine; break;
		}
		
		Resource minePrefab = Resource.Load(m_ATmine);

		EntitySpawnParams spawnParams = new EntitySpawnParams();
		spawnParams.TransformMode = ETransformMode.WORLD;
		
		vector mat[4];

		if (m_roads.IsEmpty())
		{
			return;
		} else {
			findRoadPosition(mat);
		}

		spawnParams.Transform = mat;
		
		IEntity spawnedMine = GetGame().SpawnEntityPrefab(minePrefab, GetOwner().GetWorld(), spawnParams);
		
		m_town.m_townMines.Insert(spawnedMine);
		
		PrintFormat("CTI :: Mine Spawned at: %1", mat[3]);
		
		SCR_PressureTriggerComponent mineTriggerComponent = SCR_PressureTriggerComponent.Cast(spawnedMine.FindComponent(SCR_PressureTriggerComponent));
		mineTriggerComponent.ActivateTrigger();
		
		// TODO reveal mine for faction
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
		m_gameMode = SCR_CTI_GameMode.GetInstance();
	}
	
	//------------------------------------------------------------------------------------------------	
	void SCR_CTI_CreateMinesComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_CreateMinesComponent()
	{
		if (m_roads) m_roads.Clear();
		m_roads = null;
	}
};