class SCR_CTI_FinishWipStructure
{
	void finishWipStructure(IEntity wipStructure)
	{
		vector mat[4];
		wipStructure.GetTransform(mat);

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.GetInstance();
		FactionAffiliationComponent faffComp = FactionAffiliationComponent.Cast(wipStructure.FindComponent(FactionAffiliationComponent));
		FactionKey factionkey = faffComp.GetAffiliatedFaction().GetFactionKey();
		SCR_CTI_FactoryData factoryData;
		switch (factionkey)
		{
			case "USSR":
			{
				int index = gameMode.FactoriesUSSR.findIndexFromResourcename(wipStructure.GetPrefabData().GetPrefabName());
				factoryData = gameMode.FactoriesUSSR.g_USSR_Factories[index];
				break;
			}
			case "US":
			{
				int index = gameMode.FactoriesUS.findIndexFromResourcename(wipStructure.GetPrefabData().GetPrefabName());
				factoryData = gameMode.FactoriesUS.g_US_Factories[index];
				break;
			}
		}
		
		SCR_CTI_BaseComponent baseComponent = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
		RplComponent rplComponent = RplComponent.Cast(wipStructure.FindComponent(RplComponent));

		SCR_EntityHelper.DeleteEntityAndChildren(wipStructure);
		baseComponent.removeWIPStructureRplId(factionkey, rplComponent.Id());
		
		SCR_CTI_BuildStructure buildstructure = new SCR_CTI_BuildStructure();
		buildstructure.build(factionkey, factoryData.getResName(), mat);
		Print("CTI :: Construction Complete!");
	}
};