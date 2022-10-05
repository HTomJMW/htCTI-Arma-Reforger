class SCR_CTI_InfoHud : SCR_InfoDisplayExtended
{
	protected RichTextWidget Name;
	protected RichTextWidget Health;
	protected RichTextWidget Funds;
	
	protected float m_timeDelta;
	protected const float timeStep = 0.5;
	
	SCR_CTI_GameMode gameMode;
	PlayerController pc;
	IEntity ent;
	DamageManagerComponent dmc;

	protected void CreateHud(IEntity owner)
	{
		Name = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Name"));
		Health = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Health"));
		Funds = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Funds"));
		
		Name.SetText("Player Name");
		Name.SetVisible(true);
		
		Health.SetText("Player Health");
		Health.SetVisible(true);
		
		Funds.SetText("Player Funds");
		Funds.SetVisible(true);
	}

	protected void DestroyHud()
	{		
		if (!m_wRoot)
			return;		

		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
		
		m_wRoot = null;		
	}

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
				string name = clientData.getPlayerName();
			
				Name.SetText("Player: " + name);
				switch (true)
				{
					case (hp < 75 && hp > 25): Health.SetColor(Color.Yellow); break;
					case (hp < 25): Health.SetColor(Color.Red); break;
					default: Health.SetColor(Color.Green); break;
				}
				Health.SetText("Health: " + hp.ToString());
				Funds.SetText("Funds: " + funds.ToString());
			}
			m_timeDelta = 0;
		}
	}

	override bool DisplayStartDrawInit(IEntity owner)
	{
		if (m_LayoutPath == "") m_LayoutPath = "{959E824DECAF27D7}UI/layouts/InfoHud.layout";
		
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_timeDelta = 0;

		return true;
	}

	override void DisplayStartDraw(IEntity owner)
	{
		if (!m_wRoot)
		{
			return;
		}

		CreateHud(owner);
	}
	
	override void DisplayInit(IEntity owner)
	{
		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
	}

	override void DisplayStopDraw(IEntity owner)
	{
		DestroyHud();
	}
};