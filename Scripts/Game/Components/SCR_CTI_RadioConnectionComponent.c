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

	//------------------------------------------------------------------------------------------------
	bool hasRadio()
	{
		SCR_PrefabNamePredicate predicate = new SCR_PrefabNamePredicate();
		
		array<IEntity> radios = {};
		switch (m_factionAffComp.GetAffiliatedFaction().GetFactionKey())
		{
			case "USSR":
			{
				predicate.prefabName = SCR_CTI_Constants.USSR_RADIO1;
				m_ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_ANY);
				if (radios.IsEmpty())
					{
						predicate.prefabName = SCR_CTI_Constants.USSR_RADIO2;
						m_ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_ANY);
					}
				break;
			}
			case "US":
			{
				predicate.prefabName = SCR_CTI_Constants.US_RADIO1;
				m_ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_ANY);
				if (radios.IsEmpty())
					{
						predicate.prefabName = SCR_CTI_Constants.US_RADIO2;
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
		m_mapitem.SetPriority(3);
		
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
		super.OnPostInit(owner);

		// disabled on dedicated server with playercontroller check
		if (m_pc)
		{
			m_mapDescComp = SCR_MapDescriptorComponent.Cast(owner.FindComponent(SCR_MapDescriptorComponent));
			m_ismc = SCR_InventoryStorageManagerComponent.Cast(owner.FindComponent(SCR_InventoryStorageManagerComponent));
			m_factionAffComp = FactionAffiliationComponent.Cast(owner.FindComponent(FactionAffiliationComponent));
			m_dmc = DamageManagerComponent.Cast(owner.FindComponent(DamageManagerComponent));
	
			GetGame().GetCallqueue().CallLater(initMapDescriptor, 3000);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_RadioConnectionComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_player = SCR_ChimeraCharacter.Cast(ent);
		m_pc = GetGame().GetPlayerController();

		if (m_pc) SCR_MapEntity.GetOnMapOpen().Insert(OnMapOpen);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_RadioConnectionComponent()
	{
		if (m_pc) SCR_MapEntity.GetOnMapOpen().Remove(OnMapOpen);
	}
};