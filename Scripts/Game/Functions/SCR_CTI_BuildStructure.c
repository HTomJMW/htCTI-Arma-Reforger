class SCR_CTI_BuildStructure
{
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_BaseComponent m_baseComp;

	//------------------------------------------------------------------------------------------------
	void build(FactionKey factionkey, ResourceName resourcename, vector mat[4])
	{
		Resource resource = Resource.Load(resourcename);
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;

		IEntity structure = null;
		int basecount = m_baseComp.getBaseCount(factionkey);
		switch (factionkey)
		{
			case "USSR":
			{
				// Step 1:
				// if no base yet
				if (basecount < 1)
				{
					m_baseComp.addBase(factionkey, mat[3], basecount);
					structure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
					m_baseComp.getBase(factionkey, basecount).addStructure(structure);
					break;
				}

				// Step 2: 
				// if pos inside base area (base area unions not handled, add structure to first possible base)
				bool inside = false;
				for (int i = 0; i < basecount; i++)
				{
					if (!inside)
					{
						float distance = m_baseComp.getAreaDistances(mat[3], m_baseComp.getBase(factionkey, i).getBasePos());
		
						if (distance <= SCR_CTI_Constants.BASERADIUS)
						{
							structure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
							m_baseComp.getBase(factionkey, i).addStructure(structure);
							inside = true;
						}
					}
				}
				if (inside) break;

				// Step 3:
				// if pos not inside base area and max base count reached
				if (basecount >= SCR_CTI_Constants.MAXBASES) break;
				
				// Step 4:
				// not first and not inside other area so make new base
				m_baseComp.addBase(factionkey, mat[3], basecount);
				structure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
				m_baseComp.getBase(factionkey, basecount).addStructure(structure);

				break;
			}
			case "US":
			{
				// Step 1:
				// if no base yet
				if (basecount < 1)
				{
					m_baseComp.addBase(factionkey, mat[3], basecount);
					structure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
					m_baseComp.getBase(factionkey, basecount).addStructure(structure);
					break;
				}

				// Step 2: 
				// if pos inside base area (base area unions not handled, add structure to first possible base)
				bool inside = false;
				for (int i = 0; i < basecount; i++)
				{
					if (!inside)
					{
						float distance = m_baseComp.getAreaDistances(mat[3], m_baseComp.getBase(factionkey, i).getBasePos());
		
						if (distance <= SCR_CTI_Constants.BASERADIUS)
						{
							structure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
							m_baseComp.getBase(factionkey, i).addStructure(structure);
							inside = true;
						}
					}
				}
				if (inside) break;

				// Step 3:
				// if pos not inside base area and max base count reached
				if (basecount >= SCR_CTI_Constants.MAXBASES) break;
				
				// Step 4:
				// not first and not inside other area so make new base
				m_baseComp.addBase(factionkey, mat[3], basecount);
				structure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
				m_baseComp.getBase(factionkey, basecount).addStructure(structure);

				break;
			}
		}

		if (structure)
		{
			structure.Update();
			
			// set faction of building
			FactionAffiliationComponent faffcomp = FactionAffiliationComponent.Cast(structure.FindComponent(FactionAffiliationComponent));
			faffcomp.SetAffiliatedFactionByKey(factionkey);
			
			// set marker of building
			SCR_CTI_BuildingMapDescriptorComponent bmdc = SCR_CTI_BuildingMapDescriptorComponent.Cast(structure.FindComponent(SCR_CTI_BuildingMapDescriptorComponent));
			bmdc.init(factionkey);
			
			// store structure IDs for searching
			RplComponent rplComp = RplComponent.Cast(structure.FindComponent(RplComponent));
			RplId rplid = rplComp.Id();
			m_baseComp.addStuctureRplId(factionkey, rplid);
			
			// create spawn point
			ResourceName resname = "{987991DCED3DC197}PrefabsEditable/SpawnPoints/E_SpawnPoint.et";
			Resource res = Resource.Load(resname);
			IEntity sp = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), params);
			SCR_SpawnPoint spawn = SCR_SpawnPoint.Cast(sp);
			spawn.SetFactionKey(factionkey);
			
			// pay the cost
			SCR_CTI_FactoryData factoryData;
			int index = -1;
			switch (factionkey)
			{
				case "USSR":
				{
					index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(resourcename);
					factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];
					break;
				}
				case "US":
				{
					index = m_gameMode.FactoriesUS.findIndexFromResourcename(resourcename);
					factoryData = m_gameMode.FactoriesUS.g_US_Factories[index];
					break;
				}
			}
			int cost = factoryData.getPrice();
			m_gameMode.changeCommanderFunds(factionkey, -cost);
		} else {
			PrintFormat("CTI :: Side %1 reached Base limit", factionkey);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BuildStructure()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_baseComp = SCR_CTI_BaseComponent.Cast(m_gameMode.FindComponent(SCR_CTI_BaseComponent));
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildStructure()
	{
	}
};