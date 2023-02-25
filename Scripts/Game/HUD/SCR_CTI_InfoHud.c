class SCR_CTI_InfoHud : SCR_InfoDisplayExtended
{
	protected RichTextWidget m_Line1;
	protected RichTextWidget m_Line2;
	protected RichTextWidget m_Line3;
	protected RichTextWidget m_Line4;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 1;
	
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_UpgradeComponent m_upComp;
	protected PlayerController m_pc;
	protected IEntity m_ent;
	protected DamageManagerComponent m_dmc;
	protected BaseStaminaComponent m_bsc;
	protected SCR_InventoryStorageManagerComponent m_ismc;
	
	protected ResourceName m_ussr_radio1 = "{E1A5D4B878AA8980}Prefabs/Items/Equipment/Radios/Radio_R148.et"; // start radio
	protected ResourceName m_ussr_radio2 = "{54C68E438DD34265}Prefabs/Items/Equipment/Radios/Radio_R107M.et";
	protected ResourceName m_us_radio1 = "{73950FBA2D7DB5C5}Prefabs/Items/Equipment/Radios/Radio_ANPRC68.et"; // start radio
	protected ResourceName m_us_radio2 = "{9B6B61BB3FE3DFB0}Prefabs/Items/Equipment/Radios/Radio_ANPRC77.et";

	//------------------------------------------------------------------------------------------------
	protected void CreateHud(IEntity owner)
	{
		m_Line1 = RichTextWidget.Cast(m_wRoot.FindAnyWidget("HudLine1"));
		m_Line2 = RichTextWidget.Cast(m_wRoot.FindAnyWidget("HudLine2"));
		m_Line3 = RichTextWidget.Cast(m_wRoot.FindAnyWidget("HudLine3"));
		m_Line4 = RichTextWidget.Cast(m_wRoot.FindAnyWidget("HudLine4"));
	}

	//------------------------------------------------------------------------------------------------
	protected void DestroyHud()
	{		
		if (!m_wRoot)
			return;		

		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
		
		m_wRoot = null;		
	}

	//------------------------------------------------------------------------------------------------
	override event void DisplayUpdate(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
		{
			if (!m_wRoot)
				return;	
			
			bool menuOpen = GetGame().GetMenuManager().IsAnyMenuOpen();
			m_wRoot.SetVisible(!menuOpen);

			m_ent = m_pc.GetControlledEntity();
			
			m_dmc = DamageManagerComponent.Cast(m_ent.FindComponent(DamageManagerComponent));
			int hp = m_dmc.GetHealth();
			
			m_bsc = BaseStaminaComponent.Cast(m_ent.FindComponent(BaseStaminaComponent));
			int st = m_bsc.GetStamina() * 100;
			
			FactionAffiliationComponent side = FactionAffiliationComponent.Cast(m_ent.FindComponent(FactionAffiliationComponent));

			m_ismc = SCR_InventoryStorageManagerComponent.Cast(m_ent.FindComponent(SCR_InventoryStorageManagerComponent));
			SCR_PrefabNamePredicate predicate = new SCR_PrefabNamePredicate();
			array<IEntity> radios = {};
			switch (side.GetAffiliatedFaction().GetFactionKey())
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

			SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(m_gameMode.FindComponent(SCR_CTI_BaseComponent));
			FactionKey sidekey = side.GetAffiliatedFaction().GetFactionKey();
			int baseCount = 0;
			int commanderId = -2;
			string upgrade = string.Format("<color rgba='255,0,0,255'>No Upgrade Running</color>");
			SCR_CTI_UpgradeData upgradedata;
			if (sidekey == "USSR")
			{
				baseCount = baseComp.getBaseCount(sidekey);
				
				commanderId = m_gameMode.getCommanderId(sidekey);
				
				for (int j = 0; j < m_gameMode.Upgrades.g_Upgrades.Count(); j++)
				{
					upgradedata = m_gameMode.Upgrades.g_Upgrades[j];
					if (m_upComp.getUpgradeStatus(sidekey, j) == UpgradeStatus.RUNNING)
					{
						upgrade = "Running Upgrade: " + upgradedata.getName() + " :: " + Math.Round(m_upComp.getRemainingTime(sidekey)).ToString() + "s";
						break;
					}
				}
			} else {
				baseCount = baseComp.getBaseCount(sidekey);
				
				commanderId = m_gameMode.getCommanderId(sidekey);

				for (int j = 0; j < m_gameMode.Upgrades.g_Upgrades.Count(); j++)
				{
					upgradedata = m_gameMode.Upgrades.g_Upgrades[j];
					if (m_upComp.getUpgradeStatus(sidekey, j) == UpgradeStatus.RUNNING)
					{
						upgrade = "Running Upgrade: " + upgradedata.getName() + " :: " + Math.Round(m_upComp.getRemainingTime(sidekey)).ToString() + "s";
						break;
					}
				}
			}
			string comm = "None";
			if (commanderId != -2) comm = GetGame().GetPlayerManager().GetPlayerName(commanderId);
			
			int playerId = m_pc.GetPlayerId();
			
			SCR_CTI_ClientData clientData = m_gameMode.getClientData(playerId); // TODO put to init

			int funds = 0;
			if (clientData)
			{
				if (clientData.isCommander())
				{
					funds = m_gameMode.getCommanderFunds(sidekey);
				} else {
					funds = clientData.getFunds();
				}
			}

			string rad = "None";
			if (!radios.IsEmpty()) rad = "Live";

			string health;
			switch (true)
			{
				case (hp < 75 && hp > 25): health = string.Format("<color rgba='255,255,0,255'>%1</color>", hp.ToString()); break;
				case (hp < 25): health = string.Format("<color rgba='255,0,0,255'>%1</color>", hp.ToString()); break;
				default: health = string.Format("<color rgba='0,255,0,255'>%1</color>", hp.ToString()); break;
			}

			string stamina;
			switch (true)
			{
				case (st < 75 && st > 25): stamina = string.Format("<color rgba='255,255,0,255'>%1</color>", st.ToString()); break;
				case (st < 25): stamina = string.Format("<color rgba='255,0,0,255'>%1</color>", st.ToString()); break;
				default: stamina = string.Format("<color rgba='0,0,255,255'>%1</color>", st.ToString()); break;
			}
			
			string priority = "None";
			if (m_gameMode.getPriority(sidekey) != "") priority = m_gameMode.getPriority(sidekey);
				
			m_Line1.SetText("Radio: " + rad + " || Funds: " + funds.ToString() + "$ || HP: " + health + " || STA: " + stamina);
			m_Line2.SetText("Current Com: " + comm + " || Bases: " + baseCount.ToString() + "/" + SCR_CTI_Constants.MAXBASES.ToString()); 
			m_Line3.SetText(upgrade);
			m_Line4.SetText("Priority Town: " + priority);

			m_timeDelta = 0;
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool DisplayStartDrawInit(IEntity owner)
	{
		if (m_LayoutPath == "") m_LayoutPath = "{959E824DECAF27D7}UI/layouts/InfoHud.layout";
		
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_upComp = SCR_CTI_UpgradeComponent.Cast(m_gameMode.FindComponent(SCR_CTI_UpgradeComponent));
		
		m_pc = GetGame().GetPlayerController();
		
		m_timeDelta = 0;

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayStartDraw(IEntity owner)
	{
		if (!m_wRoot)
		{
			return;
		}

		CreateHud(owner);
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayInit(IEntity owner)
	{
		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
	}

	//------------------------------------------------------------------------------------------------
	override void DisplayStopDraw(IEntity owner)
	{
		DestroyHud();
	}
};