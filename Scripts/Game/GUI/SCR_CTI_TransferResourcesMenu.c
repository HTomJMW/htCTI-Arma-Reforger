class SCR_CTI_TransferResourcesMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected SCR_CTI_ClientData clientData;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;
	protected PlayerManager pm;
	
	protected ref array<int> players = {};
	protected int playerCount;

	protected float m_timeDelta;
	protected const float TIMESTEP = 0.3;
	
	protected Widget m_wRoot;
	
	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;
	
	protected EditBoxWidget m_editbox;
	
	protected int ask = 0;
	
	protected SliderWidget m_slider;
	
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	protected ButtonWidget m_transfer;
	
	protected TextWidget m_playerresources;
	protected TextWidget m_yourresources;
	
	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;
	protected ref SCR_CTI_TransferMenuSliderHandler m_sliderEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		playerFaction = affiliationComp.GetAffiliatedFaction();
		pm = GetGame().GetPlayerManager();
		
		m_wRoot = GetRootWidget();
		
		// listbox
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));
		
		// editbox
		m_editbox = EditBoxWidget.Cast(m_wRoot.FindAnyWidget("EditBox"));
		
		// slider
		m_slider = SliderWidget.Cast(m_wRoot.FindAnyWidget("Slider"));
		
		// buttons
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		m_transfer = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Transfer"));
		
		// textwidgets
		m_playerresources = TextWidget.Cast(m_wRoot.FindAnyWidget("PlayerResources"));
		m_yourresources = TextWidget.Cast(m_wRoot.FindAnyWidget("YourResources"));

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		m_sliderEventHandler = new SCR_CTI_TransferMenuSliderHandler();
		
		m_slider.AddHandler(m_sliderEventHandler);

		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);
		
		m_transfer.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_transfer.AddHandler(m_buttonEventHandler);
		
		clientData = gameMode.getClientData(playerId);

		int funds = 0;
		if (clientData) funds = clientData.getFunds();
		
		m_yourresources.SetText("Your Resources: " + funds.ToString() + "$");
		
		pm.GetPlayers(players);
		playerCount = players.Count();
		for (int i = 0; i < playerCount; i++)
		{
			IEntity playerEnt = pm.GetPlayerControlledEntity(players[i]);
			FactionAffiliationComponent affcomp = FactionAffiliationComponent.Cast(playerEnt.FindComponent(FactionAffiliationComponent));

			if (affcomp.GetAffiliatedFaction() == playerFaction)
			{
				RplComponent rplComp = RplComponent.Cast(playerEnt.FindComponent(RplComponent));
				
				m_listboxcomp.AddItem(pm.GetPlayerName(players[i]), rplComp);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			// if playerlist changed just reload menu (temporary)
			pm.GetPlayers(players);
			if (players.Count() != playerCount)
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_TransferResourcesMenu);
			}

			int funds = 0;
			if (clientData) funds = clientData.getFunds();

			m_yourresources.SetText("Your Resources: " + funds.ToString() + "$");
				
			m_slider.SetMax(funds);
				
			string ebox = m_editbox.GetText();
			ask = ebox.ToInt();
			if (ask > funds)
			{
				ask = funds;
				m_editbox.SetText(ask.ToString());
			}
			if (ask < 0)
			{
				ask = 0;
				m_editbox.SetText(ask.ToString());
			}
				
			m_slider.SetCurrent(ask);
			
			if (m_listboxcomp.GetSelectedItem() != -1)
			{
				RplComponent rplCompReceiver = RplComponent.Cast(m_listboxcomp.GetItemData(m_listboxcomp.GetSelectedItem()));
				RplId rplid = rplCompReceiver.Id();
				int receiverId = GetGame().GetPlayerManager().GetPlayerIdFromEntityRplId(rplid);
				PlayerController pcrec = PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(receiverId));
				
				SCR_CTI_ClientData receiverClientData = gameMode.getClientData(receiverId);
				
				m_playerresources.SetText("Player Resources: " + receiverClientData.getFunds().ToString() + "$");
			}

			m_timeDelta = 0;
		}
	}
};