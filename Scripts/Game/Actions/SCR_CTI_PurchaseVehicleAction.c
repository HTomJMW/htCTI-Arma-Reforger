[EntityEditorProps(category: "GameScripted/CTI", description: "Purchase Vehicle User Action")]
class SCR_CTI_PurchaseVehicleAction : ScriptedUserAction
{
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_town = SCR_CTI_Town.Cast(pOwnerEntity);
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_rplComponent = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		Resource resource;
		int unitIndex;
		SCR_CTI_UnitData unitData;
		int price;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		switch (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey())
		{
			case "USSR":
			{
				resource = Resource.Load(SCR_CTI_Constants.USSR_UAZ);
				unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_UAZ);
				unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
				price = unitData.getPrice();
				break;
			}
			case "US":
			{
				resource = Resource.Load(SCR_CTI_Constants.US_JEEP);
				unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_JEEP);
				unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
				price = unitData.getPrice();
				break;
			}
		}

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		vector mat[4];
		m_town.GetTransform(mat); // FlagPos
		
		RandomGenerator randomgen = new RandomGenerator();
		vector rndpos = randomgen.GenerateRandomPointInRadius(3, 8, mat[3], true);
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		params.Transform = mat;

		IEntity spawnedVehicle = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		if (!spawnedVehicle) return;

		ChimeraWorld world = GetOwner().GetWorld();
		GarbageManager garbagemanager = world.GetGarbageManager();
		garbagemanager.Insert(spawnedVehicle, SCR_CTI_Constants.VEHICLECOLLECTIONTIME);
		
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);

		SCR_VehicleSpawnProtectionComponent vspc = SCR_VehicleSpawnProtectionComponent.Cast(spawnedVehicle.FindComponent(SCR_VehicleSpawnProtectionComponent));
		if (vspc) vspc.SetVehicleOwner(playerId);

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

		int gridX, gridZ;
		SCR_MapEntity.GetGridPos(mat[3], gridX, gridZ);
		m_gameMode.SendHint(playerId, "Your <color rgba='255,210,115,255'>" + "Vehicle" + "</color> has arrived at the <color rgba='255,210,115,255'>" + "Flag" + "</color> at grid <color rgba='255,210,115,255'>[" + gridX.ToString() + ", " + gridZ.ToString() + "]</color>.", "Information", 15);
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

		int funds;
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
		switch (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey())
		{
			case "USSR":
			{
				unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_UAZ);
				unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
				unitPrice = unitData.getPrice();
				if (funds >= unitPrice)
				{
					return true;
				} else {
					SetCannotPerformReason("Insufficent funds! [" + unitPrice + "$]");
					return false;
				}
				break;
			}
			case "US":
			{
				unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_JEEP);
				unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
				unitPrice = unitData.getPrice();
				if (funds >= unitPrice)
				{
					return true;
				} else {
					SetCannotPerformReason("Insufficent funds! [" + unitPrice + "$]");
					return false;
				}
				break;
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
		outName = "[Hold] Purchase Light Vehicle";
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_PurchaseVehicleAction()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_PurchaseVehicleAction()
	{
	}
};