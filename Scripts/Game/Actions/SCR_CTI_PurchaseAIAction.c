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
		m_gameMode = SCR_CTI_GameMode.GetInstance();
		m_rplComponent = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		
		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		SCR_AIGroup playersGroup = gmc.GetPlayerGroup(playerId);

		if (playersGroup.GetAgentsCount() >= SCR_CTI_Constants.PLAYERGROUPSIZE)
		{
			m_gameMode.SendHint(playerId, "Your Group is full!", "Information", 15);
			return;
		}
		
		Resource resource;
		int price;
		int unitIndex;
		SCR_CTI_UnitData unitData;
		
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		switch (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey())
		{
			case "USSR":
			{
				resource = Resource.Load(SCR_CTI_Constants.USSR_SOLDIER);
				unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_SOLDIER);
				unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
				price = unitData.getPrice();
				break;
			}
			case "US":
			{
				resource = Resource.Load(SCR_CTI_Constants.US_SOLDIER);
				unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_SOLDIER);
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

		IEntity spawnedAI = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		if (!spawnedAI) return;

		AIControlComponent control = AIControlComponent.Cast(spawnedAI.FindComponent(AIControlComponent));
		control.ActivateAI();

		AIAgent agent = control.GetControlAIAgent();

		SCR_AIConfigComponent aiConfigComponent = SCR_AIConfigComponent.Cast(agent.FindComponent(SCR_AIConfigComponent));
		aiConfigComponent.m_Skill = SCR_CTI_Constants.AISKILL; // ai combat component - skill test?

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

		playersGroup.AddAgent(agent);

		m_gameMode.bumpMeServer();
		
		int gridX, gridZ;
		SCR_MapEntity.GetGridPos(mat[3], gridX, gridZ);
		m_gameMode.SendHint(playerId, "Your <color rgba='255,210,115,255'>" + "Rifleman" + "</color> has arrived at the <color rgba='255,210,115,255'>" + "Flag" + "</color> at grid <color rgba='255,210,115,255'>[" + gridX.ToString() + ", " + gridZ.ToString() + "]</color>.", "Information", 15);
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		PlayerController pc = GetGame().GetPlayerController();
		int playerId = pc.GetPlayerId();
		SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId);

		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		SCR_AIGroup playersGroup = gmc.GetPlayerGroup(playerId);
		
		if (playersGroup.GetAgentsCount() >= SCR_CTI_Constants.PLAYERGROUPSIZE) // working only on server atm, slave group needed
		{
			SetCannotPerformReason("Group limit reached!");
			return false;
		}

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
				unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(SCR_CTI_Constants.USSR_SOLDIER);
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
				unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(SCR_CTI_Constants.US_SOLDIER);
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
		outName = "[Hold] Purchase AI";
		
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