[EntityEditorProps(category: "GameScripted/CTI", description: "Purchase Equipment User Action")]
class SCR_CTI_PurchaseEquipmentAction : ScriptedUserAction
{
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;
	
	protected ref array<IEntity> m_items = {};

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_town = SCR_CTI_Town.Cast(pOwnerEntity);
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_rplComponent = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		Resource resource;
		int price;
		SCR_CTI_UnitData unitData;
		int unitIndex;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			resource = Resource.Load(SCR_CTI_Constants.USSR_BOX);
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_BOX);
			unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			price = unitData.getPrice();
		} else {
			resource = Resource.Load(SCR_CTI_Constants.US_BOX);
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_BOX);
			unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
			price = unitData.getPrice();
		}
			
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		vector mat[4];
		m_town.GetTransform(mat); // flagpos
		
		RandomGenerator randomgen = new RandomGenerator();
		vector rndpos = randomgen.GenerateRandomPointInRadius(3, 8, mat[3], true);
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		params.Transform = mat;

		IEntity spawnedBox = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		setEquipment(userAffiliationComponent);
		insertItems(spawnedBox);
		
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId);
		
		if (clientData)
		{
			if (clientData.isCommander())
			{
				m_gameMode.changeCommanderFunds(userAffiliationComponent.GetAffiliatedFaction().GetFactionKey(), -price);
			} else {
				clientData.changeFunds(-price);
			}
		}

		m_gameMode.bumpMeServer();
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		int playerId = GetGame().GetPlayerController().GetPlayerId();
		SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId);		
		
		int funds = 0;
		if (clientData)
		{
			if (clientData.isCommander())
			{
				int factionIndex = clientData.getFactionIndex();
				funds = m_gameMode.getCommanderFunds(GetGame().GetFactionManager().GetFactionByIndex(factionIndex).GetFactionKey());
			} else {
				funds = clientData.getFunds();
			}
		}
		
		int unitIndex;
		SCR_CTI_UnitData unitData;
		int unitPrice;
				
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_BOX);
			unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			unitPrice = unitData.getPrice();
			if (funds > unitPrice)
			{
				return true;
			} else {
				SetCannotPerformReason("Insufficent funds!");
				return false;
			}
		} else {
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_BOX);
			unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
			unitPrice = unitData.getPrice();
			if (funds > unitPrice)
			{
				return true;
			} else {
				SetCannotPerformReason("Insufficent funds!");
				return false;
			}
		}

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		if (m_town.getFactionKey() != userAffiliationComponent.GetAffiliatedFaction().GetFactionKey()) return false;
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "Purchase Equipment";
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	protected void addItemsPrefab(map<ResourceName, int> prefabMap)
	{
		foreach (ResourceName prefab, int piece : prefabMap)
		{
			Resource res = Resource.Load(prefab);
			for (int i = 0; i < piece; i++)
			{
				IEntity item = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld());
				m_items.Insert(item);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void insertItems(IEntity box)
	{
		InventoryStorageManagerComponent ismc = InventoryStorageManagerComponent.Cast(box.FindComponent(InventoryStorageManagerComponent));
		
		foreach (IEntity item : m_items)
		{
			ismc.TryInsertItem(item);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void setEquipment(FactionAffiliationComponent userAffiliationComponent)
	{
		switch (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey())
		{
			case "USSR":
			{
				map<ResourceName, int> itemMapUSSR = new map<ResourceName, int>();
				itemMapUSSR.Set(SCR_CTI_Constants.USSR_BANDAGE, 5);
				itemMapUSSR.Set(SCR_CTI_Constants.USSR_AK_MAG, 10);
				itemMapUSSR.Set(SCR_CTI_Constants.USSR_RPG7, 2);
				itemMapUSSR.Set(SCR_CTI_Constants.USSR_RPG7_AMMO, 4);
				itemMapUSSR.Set(SCR_CTI_Constants.USSR_GRENADE, 4);
				itemMapUSSR.Set(SCR_CTI_Constants.USSR_PM, 1);
				itemMapUSSR.Set(SCR_CTI_Constants.USSR_PM_MAG, 4);
			
				addItemsPrefab(itemMapUSSR);

				break;
			}
			case "US":
			{
				map<ResourceName, int> itemMapUS = new map<ResourceName, int>();
				itemMapUS.Set(SCR_CTI_Constants.US_BANDAGE, 5);
				itemMapUS.Set(SCR_CTI_Constants.US_M16_MAG, 10);
				itemMapUS.Set(SCR_CTI_Constants.US_M72, 6);
				itemMapUS.Set(SCR_CTI_Constants.US_GRENADE, 4);
				itemMapUS.Set(SCR_CTI_Constants.US_M9, 1);
				itemMapUS.Set(SCR_CTI_Constants.US_M9_MAG, 4);
			
				addItemsPrefab(itemMapUS);

				break;
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_PurchaseEquipmentAction()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_PurchaseEquipmentAction()
	{
		m_items.Clear();
		m_items = null;
	}
};