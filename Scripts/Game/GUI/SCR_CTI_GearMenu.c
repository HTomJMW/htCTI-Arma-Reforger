class SCR_CTI_GearMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;
	
	protected BaseWeaponManagerComponent bwmc;
	protected EquipedWeaponStorageComponent ewsc;
	protected SCR_GadgetManagerComponent gmc;
	protected BaseLoadoutManagerComponent blmc;
	protected SCR_InventoryStorageManagerComponent ismc;
	protected SCR_CharacterInventoryStorageComponent cisc;

	protected ref array<Managed> cwscArray = {};
	protected ref array<Managed> cgscArray = {};
	
	protected Widget m_wRoot;

	protected ButtonWidget m_buy;
	protected ButtonWidget m_exit;
	
	protected ButtonWidget m_helmet;
	protected ButtonWidget m_upperitem;
	protected ButtonWidget m_backpack;
	protected ButtonWidget m_jacket;
	protected ButtonWidget m_vest;
	protected ButtonWidget m_trousers;
	protected ButtonWidget m_boots;
	protected ButtonWidget m_bottomitem;
	protected ButtonWidget m_item;

	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_GearMenuButtonHandler m_gearButtonHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		playerFaction = affiliationComp.GetAffiliatedFaction();
		
		bwmc = BaseWeaponManagerComponent.Cast(pc.GetControlledEntity().FindComponent(BaseWeaponManagerComponent));
		ewsc = EquipedWeaponStorageComponent.Cast(pc.GetControlledEntity().FindComponent(EquipedWeaponStorageComponent));
		gmc = SCR_GadgetManagerComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_GadgetManagerComponent));
		blmc = BaseLoadoutManagerComponent.Cast(pc.GetControlledEntity().FindComponent(BaseLoadoutManagerComponent));
		ismc = SCR_InventoryStorageManagerComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_InventoryStorageManagerComponent));
		cisc = SCR_CharacterInventoryStorageComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_CharacterInventoryStorageComponent)); // 2 child
		
		pc.GetControlledEntity().FindComponents(CharacterWeaponSlotComponent, cwscArray);
		pc.GetControlledEntity().FindComponents(CharacterGrenadeSlotComponent, cgscArray);
		
		m_wRoot = GetRootWidget();

		m_buy = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Buy"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		m_helmet = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonHelmet"));
		m_upperitem = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonUpperItem"));
		m_backpack = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonBackPack"));
		m_jacket = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonJacket"));
		m_vest = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonVest"));
		m_trousers = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonTrousers"));
		m_boots = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonBoots"));
		m_bottomitem = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonBottomItem"));
		m_item = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonItem"));

		// listboxes
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_gearButtonHandler = new SCR_CTI_GearMenuButtonHandler();

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_commonButtonHandler);

		FactionKey fk = playerFaction.GetFactionKey();
		SCR_CTI_GearData gearData;
		switch (fk)
		{
			case "USSR":
			{
				for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
				{
					gearData = gameMode.GearUSSR.g_USSR_Gear[i];
					m_listboxcomp.AddItem(gearData.getPrice().ToString() + "$ " + gearData.getName());
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
				{
					gearData = gameMode.GearUS.g_US_Gear[i];
					m_listboxcomp.AddItem(gearData.getPrice().ToString() + "$ " + gearData.getName());
				}
				break;
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
	}
};