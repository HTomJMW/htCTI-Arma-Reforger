class SCR_CTI_InfoHud : SCR_InfoDisplayExtended
{
	protected RichTextWidget Line1;
	protected RichTextWidget Line2;
	protected RichTextWidget Line3;
	
	protected float m_timeDelta;
	protected const float timeStep = 1;
	
	SCR_CTI_GameMode gameMode;
	SCR_CTI_UpgradeComponent upComp;
	PlayerController pc;
	IEntity ent;
	DamageManagerComponent dmc;

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
		if (m_timeDelta > timeStep)
		{
			if (!m_wRoot)
				return;	
			
			bool menuOpen = GetGame().GetMenuManager().IsAnyMenuOpen();
			m_wRoot.SetVisible(!menuOpen);
			
			pc = GetGame().GetPlayerController();
			ent = pc.GetControlledEntity();
			dmc = DamageManagerComponent.Cast(ent.FindComponent(DamageManagerComponent));
	
			int hp = dmc.GetHealth();
			
			FactionAffiliationComponent side = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
			SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(gameMode.FindComponent(SCR_CTI_BaseComponent));
			FactionKey sidekey = side.GetAffiliatedFaction().GetFactionKey();
			int baseCount = 0;
			int commanderId = -2;
			string upgrade = string.Format("<color rgba='255,0,0,255'>No Upgrade Running</color>");
			SCR_CTI_UpgradeData upgradedata;
			if (sidekey == "USSR")
			{
				baseCount = baseComp.ussrBases.Count();
				
				commanderId = gameMode.getCommanderId(sidekey);
				
				for (int j = 0; j < gameMode.UpgradesUSSR.g_Upgrades.Count(); j++)
				{
					upgradedata = gameMode.UpgradesUSSR.g_Upgrades[j];
					if (upComp.getUpgradeStatus(sidekey, j) == UpgradeStatus.RUNNING)
					{
						upgrade = "Running Upgrade: " + upgradedata.getName() + " :: " + Math.Round(upComp.getRemainingTime(sidekey)).ToString() + "s";
						break;
					}
				}
			} else {
				baseCount = baseComp.usBases.Count();
				
				commanderId = gameMode.getCommanderId(sidekey);

				for (int j = 0; j < gameMode.UpgradesUS.g_Upgrades.Count(); j++)
				{
					upgradedata = gameMode.UpgradesUSSR.g_Upgrades[j];
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
			
			int sizeCDA = gameMode.ClientDataArray.Count();
			SCR_CTI_ClientData clientData;
			for (int i = 0; i < sizeCDA; i++)
			{
				if (gameMode.ClientDataArray[i].getPlayerId() == playerId)
				{
					clientData = gameMode.ClientDataArray[i];
					break;
				}
			}
			
			if (clientData)
			{
				int funds = clientData.getFunds();

				string health;
				switch (true)
				{
					case (hp < 75 && hp > 25): health = string.Format("<color rgba='255,255,0,255'>%1</color>", hp.ToString()); break;
					case (hp < 25): health = string.Format("<color rgba='255,0,0,255'>%1</color>", hp.ToString()); break;
					default: health = string.Format("<color rgba='0,255,0,255'>%1</color>", hp.ToString()); break;
				}
				Line1.SetText("Radio: [R] || Funds: " + funds.ToString() + "$ || HP: " + health + " || STA: [-]");
			}
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