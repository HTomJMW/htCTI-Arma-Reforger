[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup Building markers.")]
class SCR_CTI_BuildingMapDescriptorComponentClass : SCR_MapDescriptorComponentClass
{
};

class SCR_CTI_BuildingMapDescriptorComponent : SCR_MapDescriptorComponent
{
	protected ResourceName m_resname;
	protected IEntity m_owner;
	
	[RplProp(onRplName: "createStructureMarker", condition: RplCondition.Custom, customConditionName: "RpcConditionMethod")]
	protected FactionKey m_fk;
	
	//------------------------------------------------------------------------------------------------
	bool RpcConditionMethod()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	void init(FactionKey fk)
	{
		m_fk = fk;
		
		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	protected void createStructureMarker()
	{
		FactionAffiliationComponent faffcomp = FactionAffiliationComponent.Cast(m_owner.FindComponent(FactionAffiliationComponent));
		Faction faction = faffcomp.GetAffiliatedFaction();
		int factionIndex = GetGame().GetFactionManager().GetFactionIndex(faction);
		Color color = Color.Black; // faction.GetFactionColor();
		string name = "Building";

		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());

		SCR_CTI_FactoryData facData;
		if (faction.GetFactionKey() == "USSR")
		{
			int size = gameMode.FactoriesUSSR.g_USSR_Factories.Count();
			for (int i = 0; i < size; i++)
			{
				facData = gameMode.FactoriesUSSR.g_USSR_Factories[i];
				if (facData.getResname() == m_resname)
				{
					name = facData.getName();
					break;
				}
			}
		} else {
			int size = gameMode.FactoriesUS.g_US_Factories.Count();
			for (int i = 0; i < size; i++)
			{
				facData = gameMode.FactoriesUS.g_US_Factories[i];
				if (facData.getResname() == m_resname)
				{
					name = facData.getName();
					break;
				}
			}
		}
		
		MapItem mapitem = Item();
		
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
	/*void markAsDestroyed(bool value)
	{
		Color color;
		if (value)
		{
			color = Color.Black;
		} else {
			color = m_textcolor;
		}
		
		MapItem item = Item();
		MapDescriptorProps props = item.GetProps();
			props.SetTextColor(color);
		
		item.SetProps(props);
	}*/

	//------------------------------------------------------------------------------------------------
	void OnMapOpen()
	{
		//if (!SCR_PlayerController.GetLocalControlledEntity()) return;
		
		//SCR_DamageManagerComponent dmc = SCR_DamageManagerComponent.Cast(m_owner.FindComponent(SCR_DamageManagerComponent));
		//if (dmc && dmc.IsDestroyed()) markAsDestroyed(true); else markAsDestroyed(false);
	}

	//------------------------------------------------------------------------------------------------
	void OnMapClose()
	{
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BuildingMapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_resname = ent.GetPrefabData().GetPrefabName();
		m_owner = ent;

		//SCR_MapEntity.GetOnMapOpen().Insert(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Insert(OnMapClose);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildingMapDescriptorComponent()
	{
		//SCR_MapEntity.GetOnMapOpen().Remove(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Remove(OnMapClose);
	}
};