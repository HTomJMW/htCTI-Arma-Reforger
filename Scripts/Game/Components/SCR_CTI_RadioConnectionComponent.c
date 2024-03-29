[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Radio Connection")]
class SCR_CTI_RadioConnectionComponentClass : ScriptComponentClass
{
};

class SCR_CTI_RadioConnectionComponent : ScriptComponent
{
	protected PlayerController m_pc;
	protected SCR_InventoryStorageManagerComponent m_ismc;
	protected FactionAffiliationComponent m_factionAffComp;
	protected bool m_radioOn = true;
	
	//------------------------------------------------------------------------------------------------
	bool radioIsOn()
	{
		return m_radioOn;
	}
	
	//------------------------------------------------------------------------------------------------
	void setRadioOn(bool value)
	{
		m_radioOn = value;
	}

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
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		// disabled on dedicated server with playercontroller check
		if (m_pc)
		{
			m_ismc = SCR_InventoryStorageManagerComponent.Cast(owner.FindComponent(SCR_InventoryStorageManagerComponent));
			m_factionAffComp = FactionAffiliationComponent.Cast(owner.FindComponent(FactionAffiliationComponent));
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_RadioConnectionComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_pc = GetGame().GetPlayerController();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_RadioConnectionComponent()
	{
	}
};