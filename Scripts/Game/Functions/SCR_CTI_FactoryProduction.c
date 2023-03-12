class SCR_CTI_FactoryProduction
{
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	void build(ResourceName resourcename, FactionKey factionkey, EntityID groupID, vector mat[4], int playerId)
	{
		IEntity entity = null;

		Resource resource = Resource.Load(resourcename);
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;
		
		entity = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		
		if (entity)
		{
			PrintFormat("CTI :: Entity spawned: %1", entity);

			AIControlComponent AgentControlComponent = AIControlComponent.Cast(entity.FindComponent(AIControlComponent));
			AIAgent agent = null;
			if (AgentControlComponent)
			{
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