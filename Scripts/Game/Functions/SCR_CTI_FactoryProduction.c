class SCR_CTI_FactoryProduction
{
	protected SCR_CTI_GameMode m_gameMode;

	//------------------------------------------------------------------------------------------------
	void build(ResourceName resourcename, FactionKey factionkey, EntityID groupID, vector mat[4])
	{
		IEntity ent = null;
		
		Resource resource = Resource.Load(resourcename);
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;
		
		ent = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		PrintFormat("CTI :: Entity spawned: %1", ent);
		
		AIControlComponent AgentControlComponent = AIControlComponent.Cast(ent.FindComponent(AIControlComponent));
		AIAgent agent = null;
		if (AgentControlComponent)
		{
			agent = AgentControlComponent.GetControlAIAgent();
		}
		
		AIGroup group = AIGroup.Cast(GetGame().GetWorld().FindEntityByID(groupID));
		if (agent && group) group.AddAgent(agent);
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