class SCR_CTI_FactoryProduction
{
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	void build(ResourceName resourcename, FactionKey factionkey, EntityID groupID, RplId factRplId, vector mat[4], int playerId, int buildTime, CTI_PurchaseInfos purchaseInfo)
	{
		SCR_CTI_PurchaseInfoCoder infoCoder = new SCR_CTI_PurchaseInfoCoder();
		bool driver, gunner, commander, crew, locked;
		infoCoder.deCode(driver, gunner, commander, crew, locked, purchaseInfo);
		PrintFormat("%1, %2, %3, %4, %5", driver.ToString(), gunner.ToString(), commander.ToString(), crew.ToString(), locked.ToString());
		//TODO Man vehicle if need

		RplComponent factRplComp = RplComponent.Cast(Replication.FindItem(factRplId));
		IEntity factory = factRplComp.GetEntity();

		IEntity entity = null;

		Resource resource = Resource.Load(resourcename);

		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;

		entity = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		
		if (entity)
		{
			PrintFormat("CTI :: Entity spawned: %1, Pos: %2 (GRID: %3)", entity, entity.GetOrigin(), SCR_MapEntity.GetGridPos(entity.GetOrigin()));
			
			// TODO temporary -> 180deg turn
			vector angles = entity.GetAngles();
			angles[1] = angles[1] + 180;
			entity.SetAngles(angles);

			AIControlComponent AgentControlComponent = AIControlComponent.Cast(entity.FindComponent(AIControlComponent));
			AIAgent agent = null;
			if (AgentControlComponent)
			{
				AgentControlComponent.ActivateAI();
				agent = AgentControlComponent.GetControlAIAgent();
			}
			
			AIGroup group = AIGroup.Cast(GetGame().GetWorld().FindEntityByID(groupID));
			if (agent && group) group.AddAgent(agent);
			
			SCR_CTI_UnitData unitData;
			int index = -1;
			switch (factionkey)
			{
				case "USSR":
				{
					index = m_gameMode.UnitsUSSR.findIndexFromResourcename(resourcename);
					unitData = m_gameMode.UnitsUSSR.g_USSR_Units[index];
					break;
				}
				case "US":
				{
					index = m_gameMode.UnitsUS.findIndexFromResourcename(resourcename);
					unitData = m_gameMode.UnitsUS.g_US_Units[index];
					break;
				}
			}
			int cost = unitData.getPrice();
			
			SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId);
			if (clientData)
			{
				if (clientData.isCommander())
				{
					m_gameMode.changeCommanderFunds(factionkey, -cost);
				} else {
					clientData.changeFunds(-cost);
					m_gameMode.bumpMeServer();
				}
			}
			
			m_gameMode.SendHint(playerId, "Your <color rgba='255,210,115,255'>" + unitData.getName() + "</color> has arrived from the <color rgba='255,210,115,255'>" + unitData.getFactory() + "</color> at grid <color rgba='255,210,115,255'>[" + SCR_MapEntity.GetGridPos(mat[3]) + "]</color>.", "Information", 15);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_FactoryProduction()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_FactoryProduction()
	{
	}
};