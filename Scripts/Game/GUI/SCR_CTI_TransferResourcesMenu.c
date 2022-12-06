class SCR_CTI_TransferResourcesMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;
	protected SCR_GroupsManagerComponent groupManComp;
	
	protected ref array<SCR_AIGroup> sideGroups;
	protected int groupCount;
	
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
		groupManComp = SCR_GroupsManagerComponent.Cast(gameMode.FindComponent(SCR_GroupsManagerComponent));
		
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

		// handler
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		m_sliderEventHandler = new SCR_CTI_TransferMenuSliderHandler();
		
		m_slider.AddHandler(m_sliderEventHandler);

		m_back.SetColor(Color.Orange);
		m_back.AddHandler(m_buttonEventHandler);

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_buttonEventHandler);
		
		m_transfer.SetColor(Color.Orange);
		m_transfer.AddHandler(m_buttonEventHandler);
		
		SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
		m_yourresources.SetText("Your Resources: " + cdc.getFunds().ToString() + "$");
		
		sideGroups = groupManComp.GetPlayableGroupsByFaction(playerFaction);
		groupCount = sideGroups.Count();
		
		for (int i = 0; i < sideGroups.Count(); i++)
		{
			m_listboxcomp.AddItem(sideGroups[i].GetCustomName() + " " + GetGame().GetPlayerManager().GetPlayerName(sideGroups[i].GetLeaderID()), sideGroups[i]);
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
			// if groups changed just reload menu (temporary)
			sideGroups = groupManComp.GetPlayableGroupsByFaction(playerFaction);
			if (sideGroups.Count() != groupCount)
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_TransferResourcesMenu);
			}
			
			SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));

			m_yourresources.SetText("Your Resources: " + cdc.getFunds().ToString() + "$");
				
			m_slider.SetMax(cdc.getFunds());
				
			string ebox = m_editbox.GetText();
			ask = ebox.ToInt();
			if (ask > cdc.getFunds())
			{
				ask = cdc.getFunds();
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
				AIGroup selectedgroup = AIGroup.Cast(m_listboxcomp.GetItemData(m_listboxcomp.GetSelectedItem())); Print(selectedgroup);
				int selectedId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(selectedgroup.GetLeaderAgent().GetControlledEntity()); Print(selectedId);

				PlayerController pcSelected = GetGame().GetPlayerManager().GetPlayerController(selectedId);
				SCR_CTI_ClientDataComponent cdcSelected = SCR_CTI_ClientDataComponent.Cast(pcSelected.FindComponent(SCR_CTI_ClientDataComponent));
				
				m_playerresources.SetText("Player Resources: " + cdcSelected.getFunds().ToString() + "$");
			}
	
			m_timeDelta = 0;
		}
	}
};