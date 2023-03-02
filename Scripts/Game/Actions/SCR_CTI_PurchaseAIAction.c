[EntityEditorProps(category: "GameScripted/CTI", description: "Pruchase AI User Action")]
class SCR_CTI_PurchaseAIAction : ScriptedUserAction
{
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;

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
		int unitIndex;
		SCR_CTI_UnitData unitData;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			resource = Resource.Load(SCR_CTI_Constants.USSR_SOLDIER);
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_SOLDIER);
			unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			price = unitData.getPrice();
		} else {
			resource = Resource.Load(SCR_CTI_Constants.US_SOLDIER);
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_SOLDIER);
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

		IEntity spawnedAI = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);

		AIControlComponent control = AIControlComponent.Cast(spawnedAI.FindComponent(AIControlComponent));
		control.ActivateAI();
		
		AIAgent agent = control.GetControlAIAgent();

		ResourceName wpRes = "{93291E72AC23930F}Prefabs/AI/Waypoints/AIWaypoint_Defend.et";
		Resource res = Resource.Load(wpRes);
		IEntity wpEntity = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), params);
		
		vector rndwppos = randomgen.GenerateRandomPointInRadius(12, 30, mat[3], true);
		vector emptywppos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptywppos, rndwppos, 10);
		mat[3] = emptywppos;
		
		SCR_AIWaypoint wp = SCR_AIWaypoint.Cast(wpEntity);
		wp.SetTransform(mat);
		wp.SetCompletionRadius(1);
		wp.SetCompletionType(EAIWaypointCompletionType.Any);
		
		agent.AddWaypoint(wp); // not working atm, maybe need agent group

		SCR_AIConfigComponent aiConfigComponent = SCR_AIConfigComponent.Cast(agent.FindComponent(SCR_AIConfigComponent));
		aiConfigComponent.m_Skill = SCR_CTI_Constants.AISKILL;

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
		
		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		SCR_AIGroup playerGroup = gmc.GetPlayerGroup(playerId);
		playerGroup.AddAgent(agent);

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

		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		SCR_AIGroup playerGroup = gmc.GetPlayerGroup(playerId);
			
		if (playerGroup.GetAgentsCount() >= SCR_CTI_Constants.PLAYERGROUPSIZE)
		{
			SetCannotPerformReason("Group limit reached!");
			return false;
		}

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
			unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_SOLDIER);
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
			unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_SOLDIER);
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
		outName = "Purchase AI";
		
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