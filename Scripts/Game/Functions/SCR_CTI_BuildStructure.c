class SCR_CTI_BuildStructure
{
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_BaseComponent m_baseComp;

	//------------------------------------------------------------------------------------------------
	void build(FactionKey factionkey, ResourceName resourcename, vector mat[4])
	{
		if (m_baseComp.getBaseCount(factionkey) >= m_gameMode.MAXBASES) return;
		
		Resource resource = Resource.Load(resourcename);
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform = mat;

		GetGame().SpawnEntityPrefab(resource, GetGame().GetWorld(), params);
		
		setBaseArea(factionkey, mat[3]);
		
		// todo add structure to base
	}
	
	//------------------------------------------------------------------------------------------------
	protected void setBaseArea(FactionKey factionkey, vector mat)
	{
		int basecount;
		switch (factionkey)
		{
			case "USSR":
			{
				basecount = m_baseComp.getBaseCount(factionkey);
				if (basecount < 1)
				{
					m_baseComp.addBase(factionkey, mat, basecount);
				} else {
					float distance;
					for (int i = 0; i < basecount; i++)
					{
						distance = m_baseComp.getAreaDistances(mat,m_baseComp.getBase(factionkey, i).getBasePos());
						if (distance > m_gameMode.BASERADIUS * 2)
						{
							m_baseComp.addBase(factionkey, mat, basecount);
							break;
						}
					}
				}
				break;
			}
			case "US":
			{
				basecount = m_baseComp.getBaseCount(factionkey);
				if (basecount < 1)
				{
					m_baseComp.addBase(factionkey, mat, basecount);
				} else {
					float distance;
					for (int i = 0; i < basecount; i++)
					{
						distance = m_baseComp.getAreaDistances(mat, m_baseComp.getBase(factionkey, i).getBasePos());
						if (distance > m_gameMode.BASERADIUS * 2)
						{
							m_baseComp.addBase(factionkey, mat, basecount);
							break;
						}
					}
				}
				break;
			}
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