[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Radio Connection")]
class SCR_CTI_RadioConnectionComponentClass : ScriptComponentClass
{
};

class SCR_CTI_RadioConnectionComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected SCR_ChimeraCharacter m_player;
	protected SCR_MapDescriptorComponent m_mapDescComp;
	protected SCR_InventoryStorageManagerComponent m_ismc;
	protected FactionAffiliationComponent m_factionAffComp;
	protected DamageManagerComponent m_dmc;
	protected MapItem m_mapitem;
	
	protected ResourceName m_ussr_radio1 = "{E1A5D4B878AA8980}Prefabs/Items/Equipment/Radios/Radio_R148.et"; // start radio
	protected ResourceName m_ussr_radio2 = "{54C68E438DD34265}Prefabs/Items/Equipment/Radios/Radio_R107M.et";
	protected ResourceName m_us_radio1 = "{73950FBA2D7DB5C5}Prefabs/Items/Equipment/Radios/Radio_ANPRC68.et"; // start radio
	protected ResourceName m_us_radio2 = "{9B6B61BB3FE3DFB0}Prefabs/Items/Equipment/Radios/Radio_ANPRC77.et";
	
	//------------------------------------------------------------------------------------------------
	bool hasRadio()
	{
		SCR_PrefabNamePredicate predicate = new SCR_PrefabNamePredicate();
		
		array<IEntity> radios = {};
		switch (m_factionAffComp.GetAffiliatedFaction().GetFactionKey())
		{
			case "USSR":
			{
				predicate.prefabName = m_ussr_radio1;
				m_ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_ANY);
				if (radios.IsEmpty())
					{
						predicate.prefabName = m_ussr_radio2;
						m_ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_ANY);
					}
				break;
			}
			case "US":
			{
				predicate.prefabName = m_us_radio1;
				m_ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_ANY);
				if (radios.IsEmpty())
					{
						predicate.prefabName = m_us_radio2;
						m_ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_ANY);
					}
				break;
			}
		}
		if (!radios.IsEmpty()) return true;

		return false;
	}
	
	//------------------------------------------------------------------------------------------------
	void initMapDescriptor()
	{
		Color color = Color.Black;
		switch (m_factionAffComp.GetAffiliatedFaction().GetFactionKey())
		{
			case "USSR": color = Color.Red; break;
			case "US": color = Color.Blue; break;
			//case "FIA": color = Color.Green; break;
		}

		m_mapitem = m_mapDescComp.Item();
		
		m_mapitem.SetDisplayName(GetGame().GetPlayerManager().GetPlayerName(m_pc.GetPlayerId()));
		m_mapitem.SetBaseType(EMapDescriptorType.MDT_NAME_GENERIC);
		m_mapitem.SetImageDef("Unit");
		
		MapDescriptorProps props = m_mapitem.GetProps();
			props.SetDetail(96);
			props.SetIconSize(0.125, 0.05, 0.125);
			props.SetTextSize(32, 8, 32);
			props.SetTextColor(Color.Black);
			props.SetFrontColor(color);
			props.SetTextVisible(false);
			props.SetIconVisible(false);
			props.Activate(true);
		
		m_mapitem.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	void OnMapOpen()
	{
		if (!SCR_PlayerController.GetLocalControlledEntity()) return;

		if (m_mapitem && m_dmc)
		{
			MapDescriptorProps props = m_mapitem.GetProps();
	
			if (hasRadio() && !m_dmc.IsDestroyed())
			{
					props.SetTextVisible(true);
					props.SetIconVisible(true);
			} else {
					props.SetTextVisible(false);
					props.SetIconVisible(false);
			}
			
			m_mapitem.SetProps(props);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_mapDescComp = SCR_MapDescriptorComponent.Cast(owner.FindComponent(SCR_MapDescriptorComponent));
		m_ismc = SCR_InventoryStorageManagerComponent.Cast(owner.FindComponent(SCR_InventoryStorageManagerComponent));
		m_factionAffComp = FactionAffiliationComponent.Cast(owner.FindComponent(FactionAffiliationComponent));
		m_dmc = DamageManagerComponent.Cast(owner.FindComponent(DamageManagerComponent));
		
		GetGame().GetCallqueue().CallLater(initMapDescriptor, 3000);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_RadioConnectionComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_player = SCR_ChimeraCharacter.Cast(ent);
		m_pc = GetGame().GetPlayerController();

		SCR_MapEntity.GetOnMapOpen().Insert(OnMapOpen);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_RadioConnectionComponent()
	{
		SCR_MapEntity.GetOnMapOpen().Remove(OnMapOpen);
	}
};