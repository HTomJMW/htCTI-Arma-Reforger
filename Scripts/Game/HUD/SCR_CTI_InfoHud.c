class SCR_CTI_InfoHud : SCR_InfoDisplayExtended
{
	protected RichTextWidget Line1;
	protected RichTextWidget Line2;
	protected RichTextWidget Line3;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 1;
	
	protected SCR_CTI_GameMode gameMode;
	protected SCR_CTI_UpgradeComponent upComp;
	protected PlayerController pc;
	protected IEntity ent;
	protected DamageManagerComponent dmc;
	protected BaseStaminaComponent bsc;
	protected SCR_InventoryStorageManagerComponent ismc;
	
	protected ResourceName m_ussr_radio1 = "{E1A5D4B878AA8980}Prefabs/Items/Equipment/Radios/Radio_R148.et"; // start radio
	protected ResourceName m_ussr_radio2 = "{54C68E438DD34265}Prefabs/Items/Equipment/Radios/Radio_R107M.et";
	protected ResourceName m_us_radio1 = "{73950FBA2D7DB5C5}Prefabs/Items/Equipment/Radios/Radio_ANPRC68.et"; // start radio
	protected ResourceName m_us_radio2 = "{9B6B61BB3FE3DFB0}Prefabs/Items/Equipment/Radios/Radio_ANPRC77.et";

	//------------------------------------------------------------------------------------------------
	protected void CreateHud(IEntity owner)
	{
		Line1 = RichTextWidget.Cast(m_wRoot.FindAnyWidget("HudLine1"));
		Line2 = RichTextWidget.Cast(m_wRoot.FindAnyWidget("HudLine2"));
		Line3 = RichTextWidget.Cast(m_wRoot.FindAnyWidget("HudLine3"));
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
			
			pc = GetGame().GetPlayerController();
			ent = pc.GetControlledEntity();

			dmc = DamageManagerComponent.Cast(ent.FindComponent(DamageManagerComponent));
			int hp = dmc.GetHealth();
			
			bsc = BaseStaminaComponent.Cast(ent.FindComponent(BaseStaminaComponent));
			int st = bsc.GetStamina() * 100;
			
			FactionAffiliationComponent side = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));

			ismc = SCR_InventoryStorageManagerComponent.Cast(ent.FindComponent(SCR_InventoryStorageManagerComponent));
			SCR_PrefabNamePredicate predicate = new SCR_PrefabNamePredicate();
			array<IEntity> radios = {};
			switch (side.GetAffiliatedFaction().GetFactionKey())
			{
				case "USSR":
				{
					predicate.prefabName = m_ussr_radio1;
					ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_GADGET_PROXY);
					if (radios.IsEmpty())
						{
							predicate.prefabName = m_ussr_radio2;
							ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_GADGET_PROXY);
						}
					break;
				}
				case "US":
				{
					predicate.prefabName = m_us_radio1;
					ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_GADGET_PROXY);
					if (radios.IsEmpty())
						{
							predicate.prefabName = m_us_radio2;
							ismc.FindItems(radios, predicate, EStoragePurpose.PURPOSE_GADGET_PROXY);
						}
					break;
				}
			}

			SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
			FactionKey sidekey = side.GetAffiliatedFaction().GetFactionKey();
			int baseCount = 0;
			int commanderId = -2;
			string upgrade = string.Format("<color rgba='255,0,0,255'>No Upgrade Running</color>");
			SCR_CTI_UpgradeData upgradedata;
			if (sidekey == "USSR")
			{
				baseCount = baseComp.getBaseCount(sidekey);
				
				commanderId = gameMode.getCommanderId(sidekey);
				
				for (int j = 0; j < gameMode.Upgrades.g_Upgrades.Count(); j++)
				{
					upgradedata = gameMode.Upgrades.g_Upgrades[j];
					if (upComp.getUpgradeStatus(sidekey, j) == UpgradeStatus.RUNNING)
					{
						upgrade = "Running Upgrade: " + upgradedata.getName() + " :: " + Math.Round(upComp.getRemainingTime(sidekey)).ToString() + "s";
						break;
					}
				}
			} else {
				baseCount = baseComp.getBaseCount(sidekey);
				
				commanderId = gameMode.getCommanderId(sidekey);

				for (int j = 0; j < gameMode.Upgrades.g_Upgrades.Count(); j++)
				{
					upgradedata = gameMode.Upgrades.g_Upgrades[j];
					if (upComp.getUpgradeStatus(sidekey, j) == UpgradeStatus.RUNNING)
					{
						upgrade = "Running Upgrade: " + upgradedata.getName() + " :: " + Math.Round(upComp.getRemainingTime(sidekey)).ToString() + "s";
						break;
					}
				}
			}
			string comm = "None";
			if (commanderId != -2) comm = GetGame().GetPlayerManager().GetPlayerName(commanderId);
			
			int playerId = pc.GetPlayerId();
			
			SCR_CTI_ClientData clientData = gameMode.getClientData(playerId); // TODO put to init

			int funds = 0;
			if (clientData) funds = clientData.getFunds();
			
			string rad = "None";
			if (radios.IsEmpty()) rad = "Live";

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
				
			Line1.SetText("Radio: " + rad + " || Funds: " + funds.ToString() + "$ || HP: " + health + " || STA: " + stamina);
			Line2.SetText("Current Com: " + comm + " || Bases: " + baseCount.ToString() + "/" + gameMode.MAXBASES.ToString()); 
			Line3.SetText(upgrade);
			m_timeDelta = 0;
		}
	}

	//------------------------------------------------------------------------------------------------
	override bool DisplayStartDrawInit(IEntity owner)
	{
		if (m_LayoutPath == "") m_LayoutPath = "{959E824DECAF27D7}UI/layouts/InfoHud.layout";
		
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		upComp = SCR_CTI_UpgradeComponent.Cast(gameMode.FindComponent(SCR_CTI_UpgradeComponent));
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