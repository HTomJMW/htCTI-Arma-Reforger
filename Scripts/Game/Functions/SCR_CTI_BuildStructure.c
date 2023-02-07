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
			// create marker and get name from factories list
			SCR_MapDescriptorComponent mdc =  SCR_MapDescriptorComponent.Cast(structure.FindComponent(SCR_MapDescriptorComponent));
			createStructureMarker(mdc, factionkey, resourcename);
			
			// set faction of building
			FactionAffiliationComponent faffcomp = FactionAffiliationComponent.Cast(structure.FindComponent(FactionAffiliationComponent));
			faffcomp.SetAffiliatedFactionByKey(factionkey);
			
			// store structure IDs for searching
			m_baseComp.addStuctureId(factionkey, structure.GetID());
		} else {
			PrintFormat("CTI :: Side %1 reached Base limit", factionkey);
		}
		
		// create spawn point
		ResourceName resname = "{987991DCED3DC197}PrefabsEditable/SpawnPoints/E_SpawnPoint.et";
		Resource res = Resource.Load(resname);
		IEntity sp = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), params);
		SCR_SpawnPoint spawn = SCR_SpawnPoint.Cast(sp);
		spawn.SetFactionKey(factionkey);
		
		// todo money things
	}

	//------------------------------------------------------------------------------------------------
	protected void createStructureMarker(SCR_MapDescriptorComponent mdc, FactionKey factionkey, ResourceName resourcename)
	{
		FactionManager fm = GetGame().GetFactionManager();
		Faction faction = fm.GetFactionByKey(factionkey);
		int factionIndex = fm.GetFactionIndex(faction);
		Color color = Color.Black; // faction.GetFactionColor();
		string name = "Building";
		
		SCR_CTI_FactoryData facData;
		if (factionkey == "USSR")
		{
			int size = m_gameMode.FactoriesUSSR.g_USSR_Factories.Count();
			for (int i = 0; i < size; i++)
			{
				facData = m_gameMode.FactoriesUSSR.g_USSR_Factories[i];
				if (facData.getResname() == resourcename)
				{
					name = facData.getName();
					break;
				}
			}
		} else {
			int size = m_gameMode.FactoriesUS.g_US_Factories.Count();
			for (int i = 0; i < size; i++)
			{
				facData = m_gameMode.FactoriesUS.g_US_Factories[i];
				if (facData.getResname() == resourcename)
				{
					name = facData.getName();
					break;
				}
			}
		}
		
		MapItem mapitem = mdc.Item();
		
		mapitem.SetDisplayName(name);
		mapitem.SetBaseType(EMapDescriptorType.MDT_UNIT);
		mapitem.SetFactionIndex(factionIndex);
		
		MapDescriptorProps props = mapitem.GetProps();
			props.SetDetail(96);
			//props.SetIconSize(2, 1, 2);
			props.SetTextSize(16, 8, 32);
			props.SetTextColor(color);
			color.SetA(0.8);
			props.SetFrontColor(color);
			props.SetTextVisible(true);
			props.SetIconVisible(false);
			props.Activate(true);
		
		mapitem.SetProps(props);
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