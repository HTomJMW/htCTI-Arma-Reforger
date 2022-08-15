[EntityEditorProps(category: "GameScripted/CTI", description: "User Action")]
class SCR_CTI_PurchaseAIAction : ScriptedUserAction
{
	protected IEntity m_owner;
	protected SCR_CTI_Town m_town;
	protected FactionAffiliationComponent m_userAffiliationComponent;
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_ClientData m_clientData;
	
	protected ResourceName m_resNameUSSRsoldier = "{DCB41B3746FDD1BE}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Rifleman.et";
	protected ResourceName m_resNameUSsoldier = "{26A9756790131354}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Rifleman.et";
	
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_owner = pOwnerEntity;
		m_town = SCR_CTI_Town.Cast(pOwnerEntity);
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}
	
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
		if (m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			resource = Resource.Load(m_resNameUSSRsoldier);
			int unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUSSRsoldier);
			SCR_CTI_UnitData unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			price = unitData.getPri();
		} else {
			resource = Resource.Load(m_resNameUSsoldier);
			int unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameUSsoldier);
			SCR_CTI_UnitData unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
			price = unitData.getPri();
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
		
		//SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		//SCR_AIGroup group = gmc.GetPlayerGroup(m_clientData.getPlayerId());
		//group.AddAIEntityToGroup(spawnedAI, -1); // UnitID not used in v0.9.5.109

		AIControlComponent control = AIControlComponent.Cast(spawnedAI.FindComponent(AIControlComponent));
		AIAgent agent = control.GetControlAIAgent();

		ResourceName wpRes = "{93291E72AC23930F}Prefabs/AI/Waypoints/AIWaypoint_Defend.et";
		Resource res = Resource.Load(wpRes);
		IEntity wpEntity = GetGame().SpawnEntityPrefab(res, m_owner.GetWorld());
		SCR_AIWaypoint wp = SCR_AIWaypoint.Cast(wpEntity);
		wp.SetCompletionRadius(1);
		wp.SetCompletionType(EAIWaypointCompletionType.Any);
		
		vector rndwppos = randomgen.GenerateRandomPointInRadius(12, 30, mat[3], true);
		vector emptywppos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptywppos, rndwppos, 10);
		mat[3] = emptywppos;
		wp.SetTransform(mat);
		
		//AIGroup grp = AIGroup.Cast(GetGame().SpawnEntity(AIGroup, m_owner.GetWorld()));
		//PrintFormat("GROUP: %1", grp);
		//grp.AddAgent(agent);
		//grp.AddWaypoint(wp);
		
		agent.AddWaypoint(wp);
		
		SCR_AIConfigComponent aiConfigComponent = SCR_AIConfigComponent.Cast(agent.FindComponent(SCR_AIConfigComponent));
		aiConfigComponent.m_Skill = 0.75;
		
		m_clientData.changeFunds(-price);
	}

	override bool HasLocalEffectOnlyScript()
	{
		return true;
	}

	override bool CanBePerformedScript(IEntity user)
	{
		PlayerController playerController = GetGame().GetPlayerController();
		int playerId = playerController.GetPlayerId();
		
		int sizeCDA = m_gameMode.ClientDataArray.Count();
		for (int i = 0; i < sizeCDA; i++)
		{
			if (m_gameMode.ClientDataArray[i].getPlayerId() == playerId)
			{
				m_clientData = m_gameMode.ClientDataArray[i];
				break;
			}
		}
		
		if (m_clientData)
			{
				int funds = m_clientData.getFunds();
				
				if (m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
				{
					int unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUSSRsoldier);
					SCR_CTI_UnitData unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
					int unitPrice = unitData.getPri();
					if (funds > unitPrice)
					{
						return true;
					} else {
						SetCannotPerformReason("Insufficent funds!");
						return false;
					}
				} else {
					int unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameUSsoldier);
					SCR_CTI_UnitData unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
					int unitPrice = unitData.getPri();
					if (funds > unitPrice)
					{
						return true;
					} else {
						SetCannotPerformReason("Insufficent funds!");
						return false;
					}
				}
			}
		
		//todo player group size check

		return true;
	}

	override bool CanBeShownScript(IEntity user)
	{
		if (!m_userAffiliationComponent) m_userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		if (m_town.getFactionKey() != m_userAffiliationComponent.GetAffiliatedFaction().GetFactionKey()) return false;
		
		return true;
	}

	override bool GetActionNameScript(out string outName)
	{
		ActionNameParams[0] = "PARAM1";
		ActionNameParams[1] = "PARAM2";
					
		outName = ("Purchase AI");
		
		return true;
	}
	
	void SCR_CTI_PurchaseAIAction()
	{
	}

	void ~SCR_CTI_PurchaseAIAction()
	{
	}
};