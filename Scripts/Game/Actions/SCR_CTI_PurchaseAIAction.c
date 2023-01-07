[EntityEditorProps(category: "GameScripted/CTI", description: "Pruchase AI User Action")]
class SCR_CTI_PurchaseAIAction : ScriptedUserAction
{
	protected IEntity m_owner;
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected ResourceName m_resNameUSSRsoldier = "{DCB41B3746FDD1BE}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Rifleman.et";
	protected ResourceName m_resNameUSsoldier = "{26A9756790131354}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Rifleman.et";

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
		int unitIndex;
		SCR_CTI_UnitData unitData;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			resource = Resource.Load(m_resNameUSSRsoldier);
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUSSRsoldier);
			unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			price = unitData.getPrice();
		} else {
			resource = Resource.Load(m_resNameUSsoldier);
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameUSsoldier);
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

		IEntity spawnedAI = GetGame().SpawnEntityPrefab(resource, m_owner.GetWorld(), params);

		AIControlComponent control = AIControlComponent.Cast(spawnedAI.FindComponent(AIControlComponent));
		control.ActivateAI();
		
		AIAgent agent = control.GetControlAIAgent();

		ResourceName wpRes = "{93291E72AC23930F}Prefabs/AI/Waypoints/AIWaypoint_Defend.et";
		Resource res = Resource.Load(wpRes);
		IEntity wpEntity = GetGame().SpawnEntityPrefab(res, m_owner.GetWorld(), params);
		
		vector rndwppos = randomgen.GenerateRandomPointInRadius(12, 30, mat[3], true);
		vector emptywppos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptywppos, rndwppos, 10);
		mat[3] = emptywppos;
		
		SCR_AIWaypoint wp = SCR_AIWaypoint.Cast(wpEntity);
		wp.SetTransform(mat);
		wp.SetCompletionRadius(1);
		wp.SetCompletionType(EAIWaypointCompletionType.Any);

		agent.AddWaypoint(wp); // todo ... not working atm
		
		SCR_AIConfigComponent aiConfigComponent = SCR_AIConfigComponent.Cast(agent.FindComponent(SCR_AIConfigComponent));
		aiConfigComponent.m_Skill = m_gameMode.AISKILL;

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
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUSSRsoldier);
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
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameUSsoldier);
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
		
		//todo player group size check

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
		outName = ("Purchase AI");
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_PurchaseAIAction()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_PurchaseAIAction()
	{
	}
};