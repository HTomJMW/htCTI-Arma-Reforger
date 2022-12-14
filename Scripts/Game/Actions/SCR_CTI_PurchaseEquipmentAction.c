[EntityEditorProps(category: "GameScripted/CTI", description: "Purchase Equipment User Action")]
class SCR_CTI_PurchaseEquipmentAction : ScriptedUserAction
{
	protected IEntity m_owner;
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected ResourceName m_resNameUSSRbox = "{B728C4AE0E6EB1E8}Prefabs/Systems/Arsenal/AmmoBoxes/USSR/AmmoBoxArsenal_Equipment_USSR.et";
	protected ResourceName m_resNameUSbox = "{0FC1D6E9B592F75D}Prefabs/Systems/Arsenal/AmmoBoxes/US/AmmoBoxArsenal_Equipment_US.et";
	
	protected ref array<IEntity> m_items = {};

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_owner = pOwnerEntity;
		m_town = SCR_CTI_Town.Cast(pOwnerEntity);
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	// PerformAction part running on server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{	
		RplComponent rplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
		if (!rplComp)	
		{	
			Print("RPL component missing! (SCR_CTI_PurchaseAIAction)");
			return;
		}

		RplId destructibleID = rplComp.Id();
		if (!destructibleID.IsValid())
		{
			Print("RplId not valid! (SCR_CTI_PurchaseAIAction)");
			return;
		}

		Resource resource;
		int price;
		SCR_CTI_UnitData unitData;
		int unitIndex;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			resource = Resource.Load(m_resNameUSSRbox);
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUSSRbox);
			unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			price = unitData.getPrice();
		} else {
			resource = Resource.Load(m_resNameUSbox);
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameUSbox);
			unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
			price = unitData.getPrice();
		}
			
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		vector mat[4];
		m_owner.GetTransform(mat); // flagpos
		
		RandomGenerator randomgen = new RandomGenerator();
		vector rndpos = randomgen.GenerateRandomPointInRadius(3, 8, mat[3], true);
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		params.Transform = mat;

		IEntity spawnedBox = GetGame().SpawnEntityPrefab(resource, m_owner.GetWorld(), params);
		setEquipment(userAffiliationComponent);
		insertItems(spawnedBox);
		
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId);
		
		if (clientData)
		{
			clientData.changeFunds(-price);
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
		if (clientData) funds = clientData.getFunds();
		
		int unitIndex;
		SCR_CTI_UnitData unitData;
		int unitPrice;
				
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUSSRbox);
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
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameUSbox);
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
		outName = ("Purchase Equipment");
		
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
				IEntity item = GetGame().SpawnEntityPrefab(res, m_owner.GetWorld());
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
				ResourceName ussr_bandage = "{C3F1FA1E2EC2B345}Prefabs/Items/Medicine/FieldDressing_USSR_01.et";
				ResourceName ussr_ak_mag = "{0A84AA5A3884176F}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Last_5Tracer.et";
				ResourceName ussr_rpg7 = "{7A82FE978603F137}Prefabs/Weapons/Launchers/RPG7/Launcher_RPG7.et";
				ResourceName ussr_rpg_ammo = "{32E12D322E107F1C}Prefabs/Weapons/Ammo/Ammo_Rocket_PG7VM.et";
				ResourceName ussr_grenade = "{645C73791ECA1698}Prefabs/Weapons/Grenades/Grenade_RGD5.et";

				map<ResourceName, int> itemMapUSSR = new map<ResourceName, int>();
				itemMapUSSR.Set(ussr_bandage, 5);
				itemMapUSSR.Set(ussr_ak_mag, 10);
				itemMapUSSR.Set(ussr_rpg7, 2);
				itemMapUSSR.Set(ussr_rpg_ammo, 4);
				itemMapUSSR.Set(ussr_grenade, 4);
			
				addItemsPrefab(itemMapUSSR);

				break;
			}
			case "US":
			{
				ResourceName us_bandage = "{A81F501D3EF6F38E}Prefabs/Items/Medicine/FieldDressing_US_01.et";
				ResourceName us_m16_mag = "{D8F2CA92583B23D3}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Last_5Tracer.et";
				ResourceName us_m72 = "{9C5C20FB0E01E64F}Prefabs/Weapons/Launchers/M72/Launcher_M72A3.et";
				ResourceName us_m72_ammo = "{79FA751EEBE25DDE}Prefabs/Weapons/Ammo/Ammo_Rocket_M72A3.et";
				ResourceName us_grenade = "{E8F00BF730225B00}Prefabs/Weapons/Grenades/Grenade_M67.et";

				map<ResourceName, int> itemMapUS = new map<ResourceName, int>();
				itemMapUS.Set(us_bandage, 5);
				itemMapUS.Set(us_m16_mag, 10);
				itemMapUS.Set(us_m72, 2);
				itemMapUS.Set(us_m72_ammo, 4);
				itemMapUS.Set(us_grenade, 4);
			
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