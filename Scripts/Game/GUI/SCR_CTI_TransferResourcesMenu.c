class SCR_CTI_TransferResourcesMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected SCR_CTI_ClientData m_clientData;
	protected int m_playerId;
	protected Faction m_playerFaction;
	protected FactionAffiliationComponent m_affiliationComp;
	protected PlayerManager m_pm;
	
	protected ref array<int> m_players = {};
	protected int m_playerCount;

	protected float m_timeDelta;
	protected const float TIMESTEP = 0.3;
	
	protected Widget m_wRoot;
	
	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;
	
	protected EditBoxWidget m_editbox;
	
	protected int m_ask = 0;
	
	protected SliderWidget m_slider;
	
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	protected ButtonWidget m_transfer;
	
	protected TextWidget m_playerresources;
	protected TextWidget m_yourresources;
	
	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_TransferResourcesMenuButtonHandler m_buttonEventHandler;
	protected ref SCR_CTI_TransferResourcesMenuSliderHandler m_sliderEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_affiliationComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_playerFaction = m_affiliationComp.GetAffiliatedFaction();
		m_pm = GetGame().GetPlayerManager();
		
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
		m_buttonEventHandler = new SCR_CTI_TransferResourcesMenuButtonHandler();
		m_sliderEventHandler = new SCR_CTI_TransferResourcesMenuSliderHandler();
		
		m_slider.AddHandler(m_sliderEventHandler);

		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);
		
		m_transfer.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_transfer.AddHandler(m_buttonEventHandler);
		
		m_clientData = m_gameMode.getClientData(m_playerId);

		int funds = 0;
		if (m_clientData && m_clientData.isCommander())
		{
			funds = m_gameMode.getCommanderFunds(m_playerFaction.GetFactionKey());
		} else {
			funds = m_clientData.getFunds();
		}

		m_yourresources.SetText("Your Resources: " + funds.ToString() + "$");
		
		m_pm.GetPlayers(m_players);
		m_playerCount = m_players.Count();
		for (int i = 0; i < m_playerCount; i++)
		{
			IEntity playerEnt = m_pm.GetPlayerControlledEntity(m_players[i]);
			FactionAffiliationComponent affcomp = FactionAffiliationComponent.Cast(playerEnt.FindComponent(FactionAffiliationComponent));

			if (affcomp.GetAffiliatedFaction() == m_playerFaction)
			{
				RplComponent rplComp = RplComponent.Cast(playerEnt.FindComponent(RplComponent));
				
				m_listboxcomp.AddItem(m_pm.GetPlayerName(m_players[i]), rplComp);
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
			// if playerlist changed just reload menu (temporary) TODO
			m_pm.GetPlayers(m_players);
			if (m_players.Count() != m_playerCount)
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_TransferResourcesMenu);
			}

			int funds = 0;
			if (m_clientData && m_clientData.isCommander())
			{
				funds = m_gameMode.getCommanderFunds(m_playerFaction.GetFactionKey());
			} else {
				funds = m_clientData.getFunds();
			}

			m_yourresources.SetText("Your Resources: " + funds.ToString() + "$");
				
			m_slider.SetMax(funds);
				
			string ebox = m_editbox.GetText();
			m_ask = ebox.ToInt();
			if (m_ask > funds)
			{
				m_ask = funds;
				m_editbox.SetText(m_ask.ToString());
			}
			if (m_ask < 0)
			{
				m_ask = 0;
				m_editbox.SetText(m_ask.ToString());
			}
				
			m_slider.SetCurrent(m_ask);
			
			if (m_listboxcomp.GetSelectedItem() != -1)
			{
				RplComponent rplCompReceiver = RplComponent.Cast(m_listboxcomp.GetItemData(m_listboxcomp.GetSelectedItem()));
				RplId rplid = rplCompReceiver.Id();
				int receiverId = GetGame().GetPlayerManager().GetPlayerIdFromEntityRplId(rplid);
				PlayerController pcrec = PlayerController.Cast(GetGame().GetPlayerManager().GetPlayerController(receiverId));
				
				SCR_CTI_ClientData receiverClientData = m_gameMode.getClientData(receiverId);
				
				m_playerresources.SetText("Player Resources: " + receiverClientData.getFunds().ToString() + "$");
			}

			m_timeDelta = 0;
		}
	}
};