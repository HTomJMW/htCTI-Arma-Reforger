[EntityEditorProps(category: "GameScripted/CTI", description: "Purchase Vehicle User Action")]
class SCR_CTI_PurchaseVehicleAction : ScriptedUserAction
{
	protected IEntity m_owner;
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected ResourceName m_resNameUaz = "{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et";
	protected ResourceName m_resNameJeep = "{F649585ABB3706C4}Prefabs/Vehicles/Wheeled/M151A2/M151A2.et";

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
			Print("RPL component missing! (SCR_CTI_PurchaseVehicleAction)");
			return;
		}

		RplId destructibleID = rplComp.Id();
		if (!destructibleID.IsValid())
		{
			Print("RplId not valid! (SCR_CTI_PurchaseVehicleAction)");
			return;
		}
		
		Resource resource;
		int unitIndex;
		SCR_CTI_UnitData unitData;
		int price;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			resource = Resource.Load(m_resNameUaz);
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUaz);
			unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			price = unitData.getPrice();
		} else {
			resource = Resource.Load(m_resNameJeep);
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameJeep);
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

		GetGame().SpawnEntityPrefab(resource, m_owner.GetWorld(), params);
		
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);

		PlayerController pc = GetGame().GetPlayerManager().GetPlayerController(playerId);
		SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
		
		cdc.changeFunds(-price);
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		PlayerController playerController = GetGame().GetPlayerController();
		int playerId = playerController.GetPlayerId();
		
		SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(playerController.FindComponent(SCR_CTI_ClientDataComponent));
		
		int funds = cdc.getFunds();

		int unitIndex;
		SCR_CTI_UnitData unitData;
		int unitPrice;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUaz);
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
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameJeep);
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
		outName = ("Purchase Light Vehicle");
		
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