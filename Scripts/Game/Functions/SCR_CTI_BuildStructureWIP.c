class SCR_CTI_BuildStructureWIP
{
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_BaseComponent m_baseComp;

	//------------------------------------------------------------------------------------------------
	void build(FactionKey factionkey, ResourceName resourcename, vector mat[4])
	{
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;
		
		IEntity wipStructure = null;
		Resource resource;
		SCR_CTI_FactoryData factoryData;
		int index = -1;

		int basecount = m_baseComp.getBaseCount(factionkey);
		switch (factionkey)
		{
			case "USSR":
			{
				index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(resourcename);
				factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];
				resource = Resource.Load(factoryData.getWIPName());
				
				// Step 1: If no base yet
				if (basecount < 1)
				{
					m_baseComp.addBase(factionkey, mat[3], basecount);
					wipStructure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
					wipStructure.Update();

					break;
				}

				// Step 2: If pos inside base area (base area unions not handled, add structure to first possible base)
				bool inside = false;
				for (int i = 0; i < basecount; i++)
				{
					if (!inside)
					{
						float distance = m_baseComp.getAreaDistances(mat[3], m_baseComp.getBase(factionkey, i).getBasePos());

						if (distance <= SCR_CTI_Constants.BASERADIUS)
						{
							wipStructure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
							wipStructure.Update();
							inside = true;
						}
					}
				}
				if (inside) break;

				// Step 3: If pos not inside base area and max base count reached
				if (basecount >= SCR_CTI_Constants.MAXBASES) break;

				// Step 4: Not first and not inside other area so make new base
				m_baseComp.addBase(factionkey, mat[3], basecount);
				wipStructure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
				wipStructure.Update();

				break;
			}
			case "US":
			{
				index = m_gameMode.FactoriesUS.findIndexFromResourcename(resourcename);
				factoryData = m_gameMode.FactoriesUS.g_US_Factories[index];
				resource = Resource.Load(factoryData.getWIPName());

				// Step 1: If no base yet
				if (basecount < 1)
				{
					m_baseComp.addBase(factionkey, mat[3], basecount);
					wipStructure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
					wipStructure.Update();

					break;
				}

				// Step 2: If pos inside base area (base area unions not handled, add structure to first possible base)
				bool inside = false;
				for (int i = 0; i < basecount; i++)
				{
					if (!inside)
					{
						float distance = m_baseComp.getAreaDistances(mat[3], m_baseComp.getBase(factionkey, i).getBasePos());

						if (distance <= SCR_CTI_Constants.BASERADIUS)
						{
							wipStructure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
							wipStructure.Update();
							inside = true;
						}
					}
				}
				if (inside) break;

				// Step 3: If pos not inside base area and max base count reached
				if (basecount >= SCR_CTI_Constants.MAXBASES) break;

				// Step 4: Not first and not inside other area so make new base
				m_baseComp.addBase(factionkey, mat[3], basecount);
				wipStructure = GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
				wipStructure.Update();

				break;
			}
		}

		if (wipStructure)
		{
			// Set faction of building
			FactionAffiliationComponent faffcomp = FactionAffiliationComponent.Cast(wipStructure.FindComponent(FactionAffiliationComponent));
			faffcomp.SetAffiliatedFactionByKey(factionkey);

			// Store wip structure IDs for searching
			RplComponent rplComp = RplComponent.Cast(wipStructure.FindComponent(RplComponent));
			RplId rplid = rplComp.Id();
			m_baseComp.addWIPStuctureRplId(factionkey, rplid);

			// Pay the cost
			int cost = factoryData.getPrice();
			m_gameMode.changeCommanderFunds(factionkey, -cost);

			// Parts SnapToGround
			BaseWorld world = GetGame().GetWorld();
			IEntity child = wipStructure.GetChildren();
			while (child)
			{
				vector orig = child.GetOrigin();
				float y = SCR_TerrainHelper.GetTerrainY(orig, world);
				if (orig[1] < y + 2)
				{
					orig[1] = y;
					child.SetOrigin(orig);
					child.Update();
				}

				child = child.GetSibling();
			}
		} else {
			PrintFormat("CTI :: Side %1 reached Base limit", factionkey);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BuildStructureWIP()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_baseComp = SCR_CTI_BaseComponent.Cast(m_gameMode.FindComponent(SCR_CTI_BaseComponent));
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildStructureWIP()
	{
	}
};