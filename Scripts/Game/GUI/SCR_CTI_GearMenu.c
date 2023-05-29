class SCR_CTI_GearMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected int m_playerId;
	protected Faction m_playerFaction;
	protected FactionAffiliationComponent m_affiliationComp;

	//protected BaseLoadoutManagerComponent m_blmc; //disabled on update
	protected SCR_InventoryStorageManagerComponent m_ismc;
	protected SCR_CharacterInventoryStorageComponent m_cisc;
	protected EquipedWeaponStorageComponent m_ewsc;
	protected EquipedLoadoutStorageComponent m_elsc;
	protected SCR_EquipmentStorageComponent m_esc;
	protected SCR_TourniquetStorageComponent m_tsc;
	protected SCR_CharacterControllerComponent m_ccc;

	protected ref array<Managed> m_cwscArray = {};
	protected ref array<Managed> m_cgscArray = {};
	
	protected Widget m_wRoot;

	protected ButtonWidget m_buy;
	protected ButtonWidget m_exit;
	
	protected ButtonWidget m_rifles;
	protected ButtonWidget m_launchers;
	protected ButtonWidget m_pistols;
	protected ButtonWidget m_accessories;
	protected ButtonWidget m_ammos;
	protected ButtonWidget m_items;
	protected ButtonWidget m_uniforms;
	protected ButtonWidget m_templates;
	
	protected ImageWidget m_riflesImg;
	protected ImageWidget m_launchersImg;
	protected ImageWidget m_pistolsImg;
	protected ImageWidget m_accessoriesImg;
	protected ImageWidget m_ammosImg;
	protected ImageWidget m_itemsImg;
	protected ImageWidget m_uniformsImg;
	protected ImageWidget m_templatesImg;
	
	protected RichTextWidget m_totalWeight;
	protected RichTextWidget m_totalCost;
	
	protected ItemPreviewManagerEntity m_preViewManager;
	
	protected ItemPreviewWidget m_primary1;
	protected ItemPreviewWidget m_primary2;
	protected ItemPreviewWidget m_secondary;
	protected ItemPreviewWidget m_grenade1;
	protected ItemPreviewWidget m_grenade2;

	protected RichTextWidget m_primary1Text;
	protected RichTextWidget m_primary2Text;
	protected RichTextWidget m_secondaryText;
	protected RichTextWidget m_grenade1Text;
	protected RichTextWidget m_grenade2Text;

	protected ItemPreviewWidget m_helmet;
	protected ItemPreviewWidget m_upperitem;
	protected ItemPreviewWidget m_backpack;
	protected ItemPreviewWidget m_jacket;
	protected ItemPreviewWidget m_vest;
	protected ItemPreviewWidget m_trousers;
	protected ItemPreviewWidget m_boots;
	protected ItemPreviewWidget m_bottomitem;
	protected ItemPreviewWidget m_item;

	protected ImageWidget m_iconHelmet;
	protected ImageWidget m_iconUpperitem;
	protected ImageWidget m_iconBackpack;
	protected ImageWidget m_iconJacket;
	protected ImageWidget m_iconVest;
	protected ImageWidget m_iconTrousers;
	protected ImageWidget m_iconBoots;
	protected ImageWidget m_iconBottomitem;
	protected ImageWidget m_iconItem;

	protected const int itemSlots = 12;
	protected bool uniqueRun = true;

	protected ref ItemPreviewWidget m_jacketPreViews[itemSlots];
	protected ref ItemPreviewWidget m_backpackPreViews[itemSlots];
	protected ref ItemPreviewWidget m_vestPreViews[itemSlots];
	protected ref ItemPreviewWidget m_trousersPreViews[itemSlots];

	protected ref RichTextWidget m_jacketTexts[itemSlots];
	protected ref RichTextWidget m_backpackTexts[itemSlots];
	protected ref RichTextWidget m_vestTexts[itemSlots];
	protected ref RichTextWidget m_trousersTexts[itemSlots];
	
	protected IEntity m_oldPrimaryWeapon1Ent = null;
	protected IEntity m_oldPrimaryWeapon2Ent = null;
	protected IEntity m_oldSecondaryWeaponEnt = null;
	protected IEntity m_oldGrenadeEnt = null;
	protected IEntity m_oldThrowableEnt = null;
	
	protected ResourceName m_newPrimaryWeapon1ResName;
	protected ResourceName m_newPrimaryWeapon2ResName;
	protected ResourceName m_newSecondaryWeaponResName;
	protected ResourceName m_newGrenadeResName;
	protected ResourceName m_newThrowableResName;
	
	protected IEntity m_primaryWeapon1Ent = null;
	protected IEntity m_primaryWeapon2Ent = null;
	protected IEntity m_secondaryWeaponEnt = null;
	protected IEntity m_grenadeEnt = null;
	protected IEntity m_throwableEnt = null;

	protected IEntity m_helmetEnt = null;
	protected IEntity m_upperitemEnt = null;
	protected IEntity m_jacketEnt = null;
	protected IEntity m_vestEnt = null;
	protected IEntity m_backpackEnt = null;
	protected IEntity m_trousersEnt = null;
	protected IEntity m_bootsEnt = null;
	protected IEntity m_bottomItemEnt = null;
	protected IEntity m_itemEnt = null;
	
	protected IEntity m_oldHelmetEnt = null;
	protected IEntity m_oldUpperitemEnt = null;
	protected IEntity m_oldJacketEnt = null;
	protected IEntity m_oldVestEnt = null;
	protected IEntity m_oldBackpackEnt = null;
	protected IEntity m_oldTrousersEnt = null;
	protected IEntity m_oldBootsEnt = null;
	protected IEntity m_oldBottomItemEnt = null;
	protected IEntity m_oldItemEnt = null;
	
	protected IEntity m_newJacketEnt = null;
	protected IEntity m_newVestEnt = null;
	protected IEntity m_newBackpackEnt = null;
	protected IEntity m_newTrousersEnt = null;
	
	protected ResourceName m_newHelmetResName;
	protected ResourceName m_newUpperitemResName;
	protected ResourceName m_newJacketResName;
	protected ResourceName m_newVestResName;
	protected ResourceName m_newBackpackResName;
	protected ResourceName m_newTrousersResName;
	protected ResourceName m_newBootsResName;
	protected ResourceName m_newBottomItemResName;
	protected ResourceName m_newItemResName;
	
	protected BaseInventoryStorageComponent m_jacketStorage = null;
	protected BaseInventoryStorageComponent m_backpackStorage = null;
	protected BaseInventoryStorageComponent m_vestStorage = null;
	protected BaseInventoryStorageComponent m_trousersStorage = null;

	protected IEntity m_jacketItems[itemSlots];
	protected IEntity m_vestItems[itemSlots];
	protected IEntity m_backpackItems[itemSlots];
	protected IEntity m_trousersItems[itemSlots];
	
	protected IEntity m_oldJacketItems[itemSlots];
	protected IEntity m_oldVestItems[itemSlots];
	protected IEntity m_oldBackpackItems[itemSlots];
	protected IEntity m_oldTrousersItems[itemSlots];
	
	protected ResourceName m_newJacketItemsResName[itemSlots];
	protected ResourceName m_newVestItemsResName[itemSlots];
	protected ResourceName m_newBackpackItemsResName[itemSlots];
	protected ResourceName m_newTrousersItemsResName[itemSlots];

	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;

	protected ref SCR_CTI_GearMenuButtonHandler m_gearButtonHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_affiliationComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_playerFaction = m_affiliationComp.GetAffiliatedFaction();

		//m_blmc = BaseLoadoutManagerComponent.Cast(m_pc.GetControlledEntity().FindComponent(BaseLoadoutManagerComponent));
		m_ismc = SCR_InventoryStorageManagerComponent.Cast(m_pc.GetControlledEntity().FindComponent(SCR_InventoryStorageManagerComponent));
		m_cisc = SCR_CharacterInventoryStorageComponent.Cast(m_pc.GetControlledEntity().FindComponent(SCR_CharacterInventoryStorageComponent)); // 2 child
		m_ewsc = EquipedWeaponStorageComponent.Cast(m_pc.GetControlledEntity().FindComponent(EquipedWeaponStorageComponent));
		m_elsc = EquipedLoadoutStorageComponent.Cast(m_pc.GetControlledEntity().FindComponent(EquipedLoadoutStorageComponent));
		m_esc = SCR_EquipmentStorageComponent.Cast(m_pc.GetControlledEntity().FindComponent(SCR_EquipmentStorageComponent));
		m_tsc = SCR_TourniquetStorageComponent.Cast(m_pc.GetControlledEntity().FindComponent(SCR_TourniquetStorageComponent));
		m_ccc = SCR_CharacterControllerComponent.Cast(m_pc.GetControlledEntity().FindComponent(SCR_CharacterControllerComponent));
		
		m_ccc.SelectWeapon(null);
		m_ismc.SetInventoryLocked(true);
		
		m_pc.GetControlledEntity().FindComponents(CharacterWeaponSlotComponent, m_cwscArray);
		m_pc.GetControlledEntity().FindComponents(CharacterGrenadeSlotComponent, m_cgscArray);
		
		m_wRoot = GetRootWidget();
		
		m_preViewManager = GetGame().GetItemPreviewManager();
		
		// handler
		m_gearButtonHandler = new SCR_CTI_GearMenuButtonHandler();

		m_buy = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Buy"));
		m_buy.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_buy.AddHandler(m_gearButtonHandler);
		
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_gearButtonHandler);

		m_rifles = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Rifles"));
		m_rifles.AddHandler(m_gearButtonHandler);
		m_launchers = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Launchers"));
		m_launchers.AddHandler(m_gearButtonHandler);
		m_pistols = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Pistols"));
		m_pistols.AddHandler(m_gearButtonHandler);
		m_accessories = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Accessories"));
		m_accessories.AddHandler(m_gearButtonHandler);
		m_ammos = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Ammos"));
		m_ammos.AddHandler(m_gearButtonHandler);
		m_items = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Items"));
		m_items.AddHandler(m_gearButtonHandler);
		m_uniforms = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Uniforms"));
		m_uniforms.AddHandler(m_gearButtonHandler);
		m_templates = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Templates"));
		m_templates.AddHandler(m_gearButtonHandler);
		m_templates.SetEnabled(false);
		m_templates.SetColor(Color.Gray);
		
		m_riflesImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("RiflesImg"));
		m_riflesImg.AddHandler(m_gearButtonHandler);
		m_launchersImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("LaunchersImg"));
		m_launchersImg.AddHandler(m_gearButtonHandler);
		m_pistolsImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("PistolsImg"));
		m_pistolsImg.AddHandler(m_gearButtonHandler);
		m_accessoriesImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("AccessoriesImg"));
		m_accessoriesImg.AddHandler(m_gearButtonHandler);
		m_ammosImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("AmmosImg"));
		m_ammosImg.AddHandler(m_gearButtonHandler);
		m_itemsImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("ItemsImg"));
		m_itemsImg.AddHandler(m_gearButtonHandler);
		m_uniformsImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("UniformsImg"));
		m_uniformsImg.AddHandler(m_gearButtonHandler);
		m_templatesImg = ImageWidget.Cast(m_wRoot.FindAnyWidget("TemplatesImg"));
		m_templatesImg.AddHandler(m_gearButtonHandler);
		m_templatesImg.SetColor(Color.White);
		
		m_totalWeight = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TotalWeight"));
		m_totalCost = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TotalCost"));
		
		m_primary1 = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewPrimary1"));
		m_primary1.AddHandler(m_gearButtonHandler);
		m_primary2 = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewPrimary2"));
		m_primary2.AddHandler(m_gearButtonHandler);
		m_secondary = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewSecondary"));
		m_secondary.AddHandler(m_gearButtonHandler);
		m_grenade1 = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewGrenade1"));
		m_grenade1.AddHandler(m_gearButtonHandler);
		m_grenade2 = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewGrenade2"));
		m_grenade2.AddHandler(m_gearButtonHandler);
		
		m_primary1Text = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TextPrimary1"));
		m_primary2Text = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TextPrimary2"));
		m_secondaryText = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TextSecondary"));
		m_grenade1Text = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TextGrenade1"));
		m_grenade2Text = RichTextWidget.Cast(m_wRoot.FindAnyWidget("TextGrenade2"));
		
		m_helmet = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewHelmet"));
		m_helmet.AddHandler(m_gearButtonHandler);
		m_upperitem = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewUpperItem"));
		m_upperitem.AddHandler(m_gearButtonHandler);
		m_backpack = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewBackPack"));
		m_backpack.AddHandler(m_gearButtonHandler);
		m_jacket = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewJacket"));
		m_jacket.AddHandler(m_gearButtonHandler);
		m_vest = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewVest"));
		m_vest.AddHandler(m_gearButtonHandler);
		m_trousers = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewTrousers"));
		m_trousers.AddHandler(m_gearButtonHandler);
		m_boots = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewBoots"));
		m_boots.AddHandler(m_gearButtonHandler);
		m_bottomitem = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewBottomItem"));
		m_bottomitem.AddHandler(m_gearButtonHandler);
		m_item = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget("PreViewItem"));
		m_item.AddHandler(m_gearButtonHandler);
		
		m_iconHelmet = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconHelmet"));
		m_iconUpperitem = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconUpperItem"));
		m_iconBackpack = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconBackPack"));
		m_iconJacket = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconJacket"));
		m_iconVest = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconVest"));
		m_iconTrousers = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconTrousers"));
		m_iconBoots = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconBoots"));
		m_iconBottomitem = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconBottomItem"));
		m_iconItem = ImageWidget.Cast(m_wRoot.FindAnyWidget("IconItem"));

		for (int i = 0; i < itemSlots; i++)
		{
			string widgetname;
			
			widgetname = "ItemPVJ" + i;
			m_jacketPreViews[i] = ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			m_jacketPreViews[i].AddHandler(m_gearButtonHandler);
			
			widgetname = "ItemPVB" + i;
			m_backpackPreViews[i] =  ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			m_backpackPreViews[i].AddHandler(m_gearButtonHandler);
			
			widgetname = "ItemPVV" + i;
			m_vestPreViews[i] =  ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			m_vestPreViews[i].AddHandler(m_gearButtonHandler);
			
			widgetname = "ItemPVT" + i;
			m_trousersPreViews[i] =  ItemPreviewWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			m_trousersPreViews[i].AddHandler(m_gearButtonHandler);
			
			widgetname = "TextJ" + i;
			m_jacketTexts[i] =  RichTextWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			
			widgetname = "TextJ" + i;
			m_jacketTexts[i] =  RichTextWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			
			widgetname = "TextB" + i;
			m_backpackTexts[i] =  RichTextWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			
			widgetname = "TextV" + i;
			m_vestTexts[i] =  RichTextWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
			
			widgetname = "TextT" + i;
			m_trousersTexts[i] =  RichTextWidget.Cast(m_wRoot.FindAnyWidget(widgetname));
		}

		// listboxes
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));

		FactionKey factionkey = m_playerFaction.GetFactionKey();
		SCR_CTI_GearData gearData;
		switch (factionkey)
		{
			case "USSR":
			{
				for (int i = 0; i < m_gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
				{
					gearData = m_gameMode.GearUSSR.g_USSR_Gear[i];
					m_listboxcomp.AddItem(gearData.getPrice().ToString() + "$ " + gearData.getName(), gearData);
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < m_gameMode.GearUS.g_US_Gear.Count(); i++)
				{
					gearData = m_gameMode.GearUS.g_US_Gear[i];
					m_listboxcomp.AddItem(gearData.getPrice().ToString() + "$ " + gearData.getName(), gearData);
				}
				break;
			}		
		}

		// character weapon slots
		foreach(Managed managed : m_cwscArray)
		{
			CharacterWeaponSlotComponent cwsc = CharacterWeaponSlotComponent.Cast(managed);

			if (cwsc.GetWeaponSlotType() == "primary" && cwsc.GetWeaponSlotIndex() == 0)
			{
				m_primaryWeapon1Ent = cwsc.GetWeaponEntity();
				if (m_primaryWeapon1Ent)
				{
					m_preViewManager.SetPreviewItem(m_primary1, m_primaryWeapon1Ent);
					m_primary1.SetResolutionScale(1, 1);

					m_primary1Text.SetVisible(false);
				}
			}
			if (cwsc.GetWeaponSlotType() == "primary" && cwsc.GetWeaponSlotIndex() == 1)
			{
				m_primaryWeapon2Ent = cwsc.GetWeaponEntity();
				if (m_primaryWeapon2Ent)
				{
					m_preViewManager.SetPreviewItem(m_primary2, m_primaryWeapon2Ent);
					m_primary2.SetResolutionScale(1, 1);			
						
					m_primary2Text.SetVisible(false);
				}
			}
			if (cwsc.GetWeaponSlotType() == "secondary" && cwsc.GetWeaponSlotIndex() == 2)
			{
				m_secondaryWeaponEnt = cwsc.GetWeaponEntity();
				if (m_secondaryWeaponEnt)
				{
					m_preViewManager.SetPreviewItem(m_secondary, m_secondaryWeaponEnt);
					m_secondary.SetResolutionScale(1, 1);
					
					m_secondaryText.SetVisible(false);
				}
			}
		}

		// character grenade slots
		foreach(Managed managed : m_cgscArray)
		{
			CharacterGrenadeSlotComponent cgsc = CharacterGrenadeSlotComponent.Cast(managed);

			if (cgsc.GetWeaponSlotType() == "grenade" && cgsc.GetWeaponSlotIndex() == 3)
			{
				m_grenadeEnt = cgsc.GetWeaponEntity();
				if (m_grenadeEnt)
				{
					m_preViewManager.SetPreviewItem(m_grenade1, m_grenadeEnt);
					m_grenade1.SetResolutionScale(1, 1);
					
					m_grenade1Text.SetVisible(false);
				}
			}
			if (cgsc.GetWeaponSlotType() == "throwable" && cgsc.GetWeaponSlotIndex() == 4)
			{
				m_throwableEnt = cgsc.GetWeaponEntity();
				if (m_throwableEnt)
				{
					m_preViewManager.SetPreviewItem(m_grenade2, m_throwableEnt);
					m_grenade2.SetResolutionScale(1, 1);
					
					m_grenade2Text.SetVisible(false);
				}
			}
		}

		// clothes
		m_helmetEnt = m_elsc.GetClothFromArea(LoadoutHeadCoverArea);
		if (m_helmetEnt)
		{
			m_iconHelmet.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_helmet, m_helmetEnt);
			m_helmet.SetResolutionScale(1, 1);
		}
		
		m_upperitemEnt = m_elsc.GetClothFromArea(LoadoutGooglesArea);
		if (m_upperitemEnt)
		{
			m_iconUpperitem.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_upperitem, m_upperitemEnt);
			m_upperitem.SetResolutionScale(1, 1);
		}
		
		m_backpackEnt = m_elsc.GetClothFromArea(LoadoutBackpackArea);
		if (m_backpackEnt)
		{
			m_iconBackpack.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_backpack, m_backpackEnt);
			m_backpack.SetResolutionScale(1, 1);
		}
		
		m_jacketEnt = m_elsc.GetClothFromArea(LoadoutJacketArea);
		if (m_jacketEnt)
		{
			m_iconJacket.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_jacket, m_jacketEnt);
			m_jacket.SetResolutionScale(1, 1);
		}
		
		m_vestEnt = m_elsc.GetClothFromArea(LoadoutVestArea);
		if (m_vestEnt)
		{
			m_iconVest.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_vest, m_vestEnt);
			m_vest.SetResolutionScale(1, 1);
		}
		
		m_trousersEnt = m_elsc.GetClothFromArea(LoadoutPantsArea);
		if (m_trousersEnt)
		{
			m_iconTrousers.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_trousers, m_trousersEnt);
			m_trousers.SetResolutionScale(1, 1);
		}
		
		m_bootsEnt = m_elsc.GetClothFromArea(LoadoutBootsArea);
		if (m_bootsEnt)
		{
			m_iconBoots.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_boots, m_bootsEnt);
			m_boots.SetResolutionScale(1, 1);
		}

		// ESC slot 0 is watch, slot 1 is binocular
		InventoryStorageSlot iss_0 = m_esc.GetSlot(0);
		m_bottomItemEnt = iss_0.GetAttachedEntity();
		if (m_bottomItemEnt)
		{
			m_iconBottomitem.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_bottomitem, m_bottomItemEnt);
			m_bottomitem.SetResolutionScale(1, 1);
		}

		InventoryStorageSlot iss_1 = m_esc.GetSlot(1);
		m_itemEnt = iss_1.GetAttachedEntity();
		if (m_itemEnt)
		{
			m_iconItem.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_item, m_itemEnt);
			m_item.SetResolutionScale(1, 1);
		}

		// items in storages
		if (m_jacketEnt)
		{
			BaseLoadoutClothComponent LoadoutCloth = BaseLoadoutClothComponent.Cast(m_jacketEnt.FindComponent(BaseLoadoutClothComponent));
			LoadoutAreaType loadoutAreaType = LoadoutCloth.GetAreaType();
			m_jacketStorage = m_cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			m_jacketStorage.GetAll(items);
			
			for(int i = 0; i < items.Count(); i++)
			{
				m_jacketTexts[i].SetVisible(false);
				m_preViewManager.SetPreviewItem(m_jacketPreViews[i], items[i]);
				m_jacketPreViews[i].SetResolutionScale(1, 1);
				
				m_jacketItems[i] = items[i];
			}
		}
		
		if (m_backpackEnt)
		{
			BaseLoadoutClothComponent LoadoutCloth = BaseLoadoutClothComponent.Cast(m_backpackEnt.FindComponent(BaseLoadoutClothComponent));
			LoadoutAreaType loadoutAreaType = LoadoutCloth.GetAreaType();
			m_backpackStorage = m_cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			m_backpackStorage.GetAll(items);

			for(int i = 0; i < items.Count(); i++)
			{
				m_backpackTexts[i].SetVisible(false);
				m_preViewManager.SetPreviewItem(m_backpackPreViews[i], items[i]);
				m_backpackPreViews[i].SetResolutionScale(1, 1);
				
				m_backpackItems[i] = items[i];
			}
		}
		
		if (m_vestEnt)
		{
			BaseLoadoutClothComponent LoadoutCloth = BaseLoadoutClothComponent.Cast(m_vestEnt.FindComponent(BaseLoadoutClothComponent));
			LoadoutAreaType loadoutAreaType = LoadoutCloth.GetAreaType();
			m_vestStorage = m_cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			m_vestStorage.GetAll(items);

			for(int i = 0; i < items.Count(); i++)
			{
				m_vestTexts[i].SetVisible(false);
				m_preViewManager.SetPreviewItem(m_vestPreViews[i], items[i]);
				m_vestPreViews[i].SetResolutionScale(1, 1);
				
				m_vestItems[i] = items[i];
			}
		}
		
		if (m_trousersEnt)
		{
			BaseLoadoutClothComponent LoadoutCloth = BaseLoadoutClothComponent.Cast(m_trousersEnt.FindComponent(BaseLoadoutClothComponent));
			LoadoutAreaType loadoutAreaType = LoadoutCloth.GetAreaType();
			m_trousersStorage = m_cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			m_trousersStorage.GetAll(items);

			for(int i = 0; i < items.Count(); i++)
			{
				m_trousersTexts[i].SetVisible(false);
				m_preViewManager.SetPreviewItem(m_trousersPreViews[i], items[i]);
				m_trousersPreViews[i].SetResolutionScale(1, 1);
				
				m_trousersItems[i] = items[i];
			}
		}
		
		// add invokers
		m_ismc.m_OnItemAddedInvoker.Insert(OnItemAdded);
		m_ismc.m_OnItemRemovedInvoker.Insert(OnItemRemoved);
	}

	//------------------------------------------------------------------------------------------------
	void removeItem(Widget w)
	{
		switch(w.GetName())
		{
			case "PreViewHelmet":
			{
				m_oldHelmetEnt = m_helmetEnt;
				m_newHelmetResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconHelmet.SetVisible(true);
				
				break;
			}
			case "PreViewUpperItem":
			{
				m_oldUpperitemEnt = m_upperitemEnt;
				m_newUpperitemResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconUpperitem.SetVisible(true);
				
				break;
			}
			case "PreViewBackPack":
			{
				m_oldBackpackEnt = m_backpackEnt;
				m_newBackpackResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconBackpack.SetVisible(true);
				
				for(int i = 0; i < itemSlots; i++)
				{
					m_preViewManager.SetPreviewItem(m_backpackPreViews[i], null);
					m_backpackTexts[i].SetVisible(true);
				}

				break;
			}
			case "PreViewJacket":
			{
				m_oldJacketEnt = m_jacketEnt;
				m_newJacketResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconJacket.SetVisible(true);
				
				for(int i = 0; i < itemSlots; i++)
				{
					m_preViewManager.SetPreviewItem(m_jacketPreViews[i], null);
					m_jacketTexts[i].SetVisible(true);
				}
				
				break;
			}
			case "PreViewVest":
			{
				m_oldVestEnt = m_vestEnt;
				m_newVestResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconVest.SetVisible(true);
				
				for(int i = 0; i < itemSlots; i++)
				{
					m_preViewManager.SetPreviewItem(m_vestPreViews[i], null);
					m_vestTexts[i].SetVisible(true);
				}
				
				break;
			}
			case "PreViewTrousers":
			{
				m_oldTrousersEnt = m_trousersEnt;
				m_newTrousersResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconTrousers.SetVisible(true);
				
				for(int i = 0; i < itemSlots; i++)
				{
					m_preViewManager.SetPreviewItem(m_trousersPreViews[i], null);
					m_trousersTexts[i].SetVisible(true);
				}
				
				break;
			}
			case "PreViewBoots":
			{
				m_oldBootsEnt = m_bootsEnt;
				m_newBootsResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconBoots.SetVisible(true);
				
				break;
			}
			case "PreViewBottomItem":
			{
				m_oldBottomItemEnt = m_bottomItemEnt;
				m_newBottomItemResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconBottomitem.SetVisible(true);
				
				break;
			}
			case "PreViewItem":
			{
				m_oldItemEnt = m_itemEnt;
				m_newItemResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconItem.SetVisible(true);
				
				break;
			}
			case "PreViewPrimary1":
			{
				m_oldPrimaryWeapon1Ent = m_primaryWeapon1Ent;
				m_newPrimaryWeapon1ResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_primary1Text.SetVisible(true);
				
				break;
			}
			case "PreViewPrimary2":
			{
				m_oldPrimaryWeapon2Ent = m_primaryWeapon2Ent;
				m_newPrimaryWeapon2ResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_primary2Text.SetVisible(true);
				
				break;
			}
			case "PreViewSecondary":
			{
				m_secondaryWeaponEnt = m_secondaryWeaponEnt;
				m_newSecondaryWeaponResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_secondaryText.SetVisible(true);
				
				break;
			}
			case "PreViewGrenade1":
			{
				m_oldGrenadeEnt = m_grenadeEnt;
				m_newGrenadeResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_grenade1Text.SetVisible(true);
				
				break;
			}
			case "PreViewGrenade2":
			{
				m_oldThrowableEnt = m_throwableEnt;
				m_newThrowableResName = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_grenade2Text.SetVisible(true);
				
				break;
			}
			case "ItemPVT0":
			{
				m_oldTrousersItems[0] = m_trousersItems[0];
				m_newTrousersItemsResName[0] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVT1":
			{
				m_oldTrousersItems[1] = m_trousersItems[1];
				m_newTrousersItemsResName[1] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVT2":
			{
				m_oldTrousersItems[2] = m_trousersItems[2];
				m_newTrousersItemsResName[2] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVT3":
			{
				m_oldTrousersItems[3] = m_trousersItems[3];
				m_newTrousersItemsResName[3] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVT4":
			{
				m_oldTrousersItems[4] = m_trousersItems[4];
				m_newTrousersItemsResName[4] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVT5":
			{
				m_oldTrousersItems[5] = m_trousersItems[5];
				m_newTrousersItemsResName[5] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVT6":
			{
				m_oldTrousersItems[6] = m_trousersItems[6];
				m_newTrousersItemsResName[6] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVT7":
			{
				m_oldTrousersItems[7] = m_trousersItems[7];
				m_newTrousersItemsResName[7] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVT8":
			{
				m_oldTrousersItems[8] = m_trousersItems[8];
				m_newTrousersItemsResName[8] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVT9":
			{
				m_oldTrousersItems[9] = m_trousersItems[9];
				m_newTrousersItemsResName[9] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVT10":
			{
				m_oldTrousersItems[10] = m_trousersItems[10];
				m_newTrousersItemsResName[10] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVT11":
			{
				m_oldTrousersItems[11] = m_trousersItems[11];
				m_newTrousersItemsResName[11] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[11].SetVisible(true);
				
				break;
			}
			case "ItemPVA0":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				// TODO test missing
				
				break;
			}
			case "ItemPVA1":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA2":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA3":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA4":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA5":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA6":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA7":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA8":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA9":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA10":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVA11":
			{
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				
				break;
			}
			case "ItemPVJ0":
			{
				m_oldJacketItems[0] = m_jacketItems[0];
				m_newJacketItemsResName[0] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVJ1":
			{
				m_oldJacketItems[1] = m_jacketItems[1];
				m_newJacketItemsResName[1] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVJ2":
			{
				m_oldJacketItems[2] = m_jacketItems[2];
				m_newJacketItemsResName[2] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVJ3":
			{
				m_oldJacketItems[3] = m_jacketItems[3];
				m_newJacketItemsResName[3] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVJ4":
			{
				m_oldJacketItems[4] = m_jacketItems[4];
				m_newJacketItemsResName[4] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVJ5":
			{
				m_oldJacketItems[5] = m_jacketItems[5];
				m_newJacketItemsResName[5] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVJ6":
			{
				m_oldJacketItems[6] = m_jacketItems[6];
				m_newJacketItemsResName[6] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVJ7":
			{
				m_oldJacketItems[7] = m_jacketItems[7];
				m_newJacketItemsResName[7] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVJ8":
			{
				m_oldJacketItems[8] = m_jacketItems[8];
				m_newJacketItemsResName[8] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVJ9":
			{
				m_oldJacketItems[9] = m_jacketItems[9];
				m_newJacketItemsResName[9] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVJ10":
			{
				m_oldJacketItems[10] = m_jacketItems[10];
				m_newJacketItemsResName[10] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVJ11":
			{
				m_oldJacketItems[11] = m_jacketItems[11];
				m_newJacketItemsResName[11] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[11].SetVisible(true);
				
				break;
			}
			case "ItemPVB0":
			{
				m_oldBackpackItems[0] = m_backpackItems[0];
				m_newBackpackItemsResName[0] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVB1":
			{
				m_oldBackpackItems[1] = m_backpackItems[1];
				m_newBackpackItemsResName[1] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVB2":
			{
				m_oldBackpackItems[2] = m_backpackItems[2];
				m_newBackpackItemsResName[2] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVB3":
			{
				m_oldBackpackItems[3] = m_backpackItems[3];
				m_newBackpackItemsResName[3] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVB4":
			{
				m_oldBackpackItems[4] = m_backpackItems[4];
				m_newBackpackItemsResName[4] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVB5":
			{
				m_oldBackpackItems[5] = m_backpackItems[5];
				m_newBackpackItemsResName[5] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVB6":
			{
				m_oldBackpackItems[6] = m_backpackItems[6];
				m_newBackpackItemsResName[6] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVB7":
			{
				m_oldBackpackItems[7] = m_backpackItems[7];
				m_newBackpackItemsResName[7] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVB8":
			{
				m_oldBackpackItems[8] = m_backpackItems[8];
				m_newBackpackItemsResName[8] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVB9":
			{
				m_oldBackpackItems[9] = m_backpackItems[9];
				m_newBackpackItemsResName[9] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVB10":
			{
				m_oldBackpackItems[10] = m_backpackItems[10];
				m_newBackpackItemsResName[10] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVB11":
			{
				m_oldBackpackItems[11] = m_backpackItems[11];
				m_newBackpackItemsResName[11] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[11].SetVisible(true);
				
				break;
			}
			case "ItemPVV0":
			{
				m_oldVestItems[0] = m_vestItems[0];
				m_newVestItemsResName[0] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVV1":
			{
				m_oldVestItems[1] = m_vestItems[1];
				m_newVestItemsResName[1] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVV2":
			{
				m_oldVestItems[2] = m_vestItems[2];
				m_newVestItemsResName[2] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVV3":
			{
				m_oldVestItems[3] = m_vestItems[3];
				m_newVestItemsResName[3] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVV4":
			{
				m_oldVestItems[4] = m_vestItems[4];
				m_newVestItemsResName[4] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVV5":
			{
				m_oldVestItems[5] = m_vestItems[5];
				m_newVestItemsResName[5] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVV6":
			{
				m_oldVestItems[6] = m_vestItems[6];
				m_newVestItemsResName[6] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVV7":
			{
				m_oldVestItems[7] = m_vestItems[7];
				m_newVestItemsResName[7] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVV8":
			{
				m_oldVestItems[8] = m_vestItems[8];
				m_newVestItemsResName[8] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVV9":
			{
				m_oldVestItems[9] = m_vestItems[9];
				m_newVestItemsResName[9] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVV10":
			{
				m_oldVestItems[10] = m_vestItems[10];
				m_newVestItemsResName[10] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVV11":
			{
				m_oldVestItems[11] = m_vestItems[11];
				m_newVestItemsResName[11] = "";
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[11].SetVisible(true);
				
				break;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void tryAddItem(Widget w, SCR_CTI_GearData gearData)
	{
		switch(w.GetName())
		{
			case "PreViewHelmet":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutHeadCoverArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconHelmet.SetVisible(false);
						m_newHelmetResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewUpperItem":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutGooglesArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconUpperitem.SetVisible(false);
						m_newUpperitemResName = gearData.getResname();
					}
				}
				
				break;
			}
			case "PreViewBackPack":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutBackpackArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconBackpack.SetVisible(false);
						m_newBackpackResName = gearData.getResname();
					}
				}
				
				break;
			}
			case "PreViewJacket":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutJacketArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconJacket.SetVisible(false);
						m_newJacketResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewVest":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutVestArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconVest.SetVisible(false);
						m_newVestResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewTrousers":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutPantsArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconTrousers.SetVisible(false);
						m_newTrousersResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewBoots":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutBootsArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconBoots.SetVisible(false);
						m_newBootsResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewBottomItem":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutWatchArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconBottomitem.SetVisible(false);
						m_newBottomItemResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewItem":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "BaseLoadoutClothComponent");
                if (meshComponent)
                {
					LoadoutAreaType lat;
					meshComponent.Get("AreaType", lat);
					if (lat.Type() == LoadoutBinocularsArea)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_iconItem.SetVisible(false);
						m_newItemResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewPrimary1":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "WeaponComponent");
                if (meshComponent)
                {
					EWeaponType weaponType;
					meshComponent.Get("WeaponType", weaponType);
					if (weaponType == 1 || weaponType == 3 || weaponType == 4 || weaponType == 5)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_primary1Text.SetVisible(false);
						m_newPrimaryWeapon1ResName = gearData.getResname();
					}
				} else {
					meshComponent = getMeshComponentByClassName(gearData.getResname(), "SCR_MineWeaponComponent");
					if (meshComponent)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_primary1Text.SetVisible(false);
						m_newPrimaryWeapon1ResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewPrimary2":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "WeaponComponent");
                if (meshComponent)
                {
					EWeaponType weaponType;
					meshComponent.Get("WeaponType", weaponType);
					if (weaponType == 1 || weaponType == 3 || weaponType == 4 || weaponType == 5)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_primary2Text.SetVisible(false);
						m_newPrimaryWeapon2ResName = gearData.getResname();
					}
				} else {
					meshComponent = getMeshComponentByClassName(gearData.getResname(), "SCR_MineWeaponComponent");
					if (meshComponent)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_primary2Text.SetVisible(false);
						m_newPrimaryWeapon2ResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewSecondary":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "WeaponComponent");
                if (meshComponent)
                {
					EWeaponType weaponType;
					meshComponent.Get("WeaponType", weaponType);
					if (weaponType == 6)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_secondaryText.SetVisible(false);
						m_newSecondaryWeaponResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewGrenade1":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "WeaponComponent");
                if (meshComponent)
                {
					EWeaponType weaponType;
					meshComponent.Get("WeaponType", weaponType);
					if (weaponType == 7 || weaponType == 8)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_grenade1Text.SetVisible(false);
						m_newGrenadeResName = gearData.getResname();
					}
				}

				break;
			}
			case "PreViewGrenade2":
			{
				BaseContainer meshComponent = getMeshComponentByClassName(gearData.getResname(), "WeaponComponent");
                if (meshComponent)
                {
					EWeaponType weaponType;
					meshComponent.Get("WeaponType", weaponType);
					if (weaponType == 7 || weaponType == 8)
					{
						m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
						m_grenade2Text.SetVisible(false);
						m_newThrowableResName = gearData.getResname();
					}
				}

				break;
			}
			case "ItemPVT0":
			{
				// TODO CHECK clothes - helmet
				
				// if no trousers in gear menu
				if (m_iconTrousers.IsVisible()) break;

				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[0].SetVisible(false);
					m_newTrousersItemsResName[0] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT1":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[1].SetVisible(false);
					m_newTrousersItemsResName[1] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT2":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[2].SetVisible(false);
					m_newTrousersItemsResName[2] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT3":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[3].SetVisible(false);
					m_newTrousersItemsResName[3] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT4":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[4].SetVisible(false);
					m_newTrousersItemsResName[4] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT5":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[5].SetVisible(false);
					m_newTrousersItemsResName[5] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT6":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[6].SetVisible(false);
					m_newTrousersItemsResName[6] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT7":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[7].SetVisible(false);
					m_newTrousersItemsResName[7] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT8":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[8].SetVisible(false);
					m_newTrousersItemsResName[8] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT9":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[9].SetVisible(false);
					m_newTrousersItemsResName[9] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT10":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[10].SetVisible(false);
					m_newTrousersItemsResName[10] = gearData.getResname();
				}

				break;
			}
			case "ItemPVT11":
			{
				if (m_iconTrousers.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_trousersTexts[11].SetVisible(false);
					m_newTrousersItemsResName[11] = gearData.getResname();
				}

				break;
			}
			case "ItemPVA0":
			{
				// TODO
				
				break;
			}
			case "ItemPVA1":
			{
				break;
			}
			case "ItemPVA2":
			{
				break;
			}
			case "ItemPVA3":
			{
				break;
			}
			case "ItemPVA4":
			{
				break;
			}
			case "ItemPVA5":
			{
				break;
			}
			case "ItemPVA6":
			{
				break;
			}
			case "ItemPVA7":
			{
				break;
			}
			case "ItemPVA8":
			{
				break;
			}
			case "ItemPVA9":
			{
				break;
			}
			case "ItemPVA10":
			{
				break;
			}
			case "ItemPVA11":
			{
				break;
			}
			case "ItemPVJ0":
			{
				if (m_iconJacket.IsVisible()) break;

				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[0].SetVisible(false);
					m_newJacketItemsResName[0] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ1":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[1].SetVisible(false);
					m_newJacketItemsResName[1] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ2":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[2].SetVisible(false);
					m_newJacketItemsResName[2] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ3":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[3].SetVisible(false);
					m_newJacketItemsResName[3] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ4":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[4].SetVisible(false);
					m_newJacketItemsResName[4] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ5":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[5].SetVisible(false);
					m_newJacketItemsResName[5] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ6":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[6].SetVisible(false);
					m_newJacketItemsResName[6] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ7":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[7].SetVisible(false);
					m_newJacketItemsResName[7] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ8":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[8].SetVisible(false);
					m_newJacketItemsResName[8] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ9":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[9].SetVisible(false);
					m_newJacketItemsResName[9] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ10":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[10].SetVisible(false);
					m_newJacketItemsResName[10] = gearData.getResname();
				}

				break;
			}
			case "ItemPVJ11":
			{
				if (m_iconJacket.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_jacketTexts[11].SetVisible(false);
					m_newJacketItemsResName[11] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB0":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[0].SetVisible(false);
					m_newBackpackItemsResName[0] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB1":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[1].SetVisible(false);
					m_newBackpackItemsResName[1] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB2":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[2].SetVisible(false);
					m_newBackpackItemsResName[2] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB3":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[3].SetVisible(false);
					m_newBackpackItemsResName[3] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB4":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[4].SetVisible(false);
					m_newBackpackItemsResName[4] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB5":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[5].SetVisible(false);
					m_newBackpackItemsResName[5] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB6":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[6].SetVisible(false);
					m_newBackpackItemsResName[6] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB7":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[7].SetVisible(false);
					m_newBackpackItemsResName[7] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB8":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[8].SetVisible(false);
					m_newBackpackItemsResName[8] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB9":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[9].SetVisible(false);
					m_newBackpackItemsResName[9] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB10":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[10].SetVisible(false);
					m_newBackpackItemsResName[10] = gearData.getResname();
				}

				break;
			}
			case "ItemPVB11":
			{
				if (m_iconBackpack.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent", "SCR_MineWeaponComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_backpackTexts[11].SetVisible(false);
					m_newBackpackItemsResName[11] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV0":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[0].SetVisible(false);
					m_newVestItemsResName[0] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV1":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[1].SetVisible(false);
					m_newVestItemsResName[1] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV2":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[2].SetVisible(false);
					m_newVestItemsResName[2] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV3":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[3].SetVisible(false);
					m_newVestItemsResName[3] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV4":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[4].SetVisible(false);
					m_newVestItemsResName[4] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV5":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[5].SetVisible(false);
					m_newVestItemsResName[5] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV6":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[6].SetVisible(false);
					m_newVestItemsResName[6] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV7":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[7].SetVisible(false);
					m_newVestItemsResName[7] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV8":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[8].SetVisible(false);
					m_newVestItemsResName[8] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV9":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[9].SetVisible(false);
					m_newVestItemsResName[9] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV10":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[10].SetVisible(false);
					m_newVestItemsResName[10] = gearData.getResname();
				}

				break;
			}
			case "ItemPVV11":
			{
				if (m_iconVest.IsVisible()) break;
				
				BaseContainer meshComponent = getMeshComponentByClassNames(gearData.getResname(), "InventoryMagazineComponent", "InventoryItemComponent");
                if (meshComponent)
                {
					m_preViewManager.SetPreviewItemFromPrefab(ItemPreviewWidget.Cast(w), gearData.getResname());
					m_vestTexts[11].SetVisible(false);
					m_newVestItemsResName[11] = gearData.getResname();
				}

				break;
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void startproc()
	{
		uniqueRun = true;
		
		// if item removed by RMB and slot empty, delete old
		if (m_oldHelmetEnt && !m_newHelmetResName) m_ismc.TryDeleteItem(m_helmetEnt);
		if (m_oldUpperitemEnt && !m_newUpperitemResName) m_ismc.TryDeleteItem(m_upperitemEnt);
		if (m_oldBackpackEnt && !m_newBackpackResName)
		{
			m_ismc.TryDeleteItem(m_backpackEnt); // need test childs deleted or not
			m_backpackStorage = null;
		}
		if (m_oldJacketEnt && !m_newJacketResName)
		{
			m_ismc.TryDeleteItem(m_jacketEnt);
			m_jacketStorage = null;
		}
		if (m_oldVestEnt && !m_newVestResName)
		{
			m_ismc.TryDeleteItem(m_vestEnt);
			m_vestStorage = null;
		}
		if (m_oldTrousersEnt && !m_newTrousersResName)
		{
			m_ismc.TryDeleteItem(m_trousersEnt);
			m_trousersStorage = null;
		}
		if (m_oldBootsEnt && !m_newBootsResName) m_ismc.TryDeleteItem(m_bootsEnt);
		if (m_oldBottomItemEnt && !m_newBottomItemResName) m_ismc.TryDeleteItem(m_bottomItemEnt);
		if (m_oldItemEnt && !m_newItemResName) m_ismc.TryDeleteItem(m_itemEnt);
		
		if (m_oldPrimaryWeapon1Ent && !m_newPrimaryWeapon1ResName) m_ismc.TryDeleteItem(m_primaryWeapon1Ent);
		if (m_oldPrimaryWeapon2Ent && !m_newPrimaryWeapon2ResName) m_ismc.TryDeleteItem(m_primaryWeapon2Ent);
		if (m_oldSecondaryWeaponEnt && !m_newSecondaryWeaponResName) m_ismc.TryDeleteItem(m_secondaryWeaponEnt);
		if (m_oldGrenadeEnt && !m_newGrenadeResName) m_ismc.TryDeleteItem(m_grenadeEnt);
		if (m_oldThrowableEnt && !m_newThrowableResName) m_ismc.TryDeleteItem(m_throwableEnt);
		
		for(int i = 0; i < itemSlots; i++)
		{
			if (m_jacketEnt && m_oldJacketItems[i] && !m_newJacketItemsResName[i]) m_ismc.TryDeleteItem(m_jacketItems[i]);
			if (m_vestEnt && m_oldVestItems[i] && !m_newVestItemsResName[i]) m_ismc.TryDeleteItem(m_vestItems[i]);
			if (m_backpackEnt && m_oldBackpackItems[i] && !m_newBackpackItemsResName[i]) m_ismc.TryDeleteItem(m_backpackItems[i]);
			if (m_trousersEnt && m_oldTrousersItems[i] && !m_newTrousersItemsResName[i]) m_ismc.TryDeleteItem(m_trousersItems[i]);
		}

		// if added new item, delete old
		if (m_newHelmetResName && m_helmetEnt && m_helmetEnt.GetPrefabData().GetPrefabName() != m_newHelmetResName)
		{
			m_ismc.TryDeleteItem(m_helmetEnt); // bug, need unwear after delete, TrySpawnPrefabToStorage not working on client without this
			//m_blmc.Unwear(m_helmetEnt);
		}
		
		if (m_newUpperitemResName && m_upperitemEnt && m_upperitemEnt.GetPrefabData().GetPrefabName() != m_newUpperitemResName)
		{
			m_ismc.TryDeleteItem(m_upperitemEnt);
			//m_blmc.Unwear(m_upperitemEnt);
		}
		
		if (m_newBackpackResName && m_backpackEnt && m_backpackEnt.GetPrefabData().GetPrefabName() != m_newBackpackResName)
		{
			m_ismc.TryDeleteItem(m_backpackEnt);
			//m_blmc.Unwear(m_backpackEnt);
		}
		
		if (m_newJacketResName && m_jacketEnt && m_jacketEnt.GetPrefabData().GetPrefabName() != m_newJacketResName)
		{
			m_ismc.TryDeleteItem(m_jacketEnt);
			//m_blmc.Unwear(m_jacketEnt);
		}
		
		if (m_newVestResName && m_vestEnt && m_vestEnt.GetPrefabData().GetPrefabName() != m_newVestResName)
		{
			m_ismc.TryDeleteItem(m_vestEnt);
			//m_blmc.Unwear(m_vestEnt);
		}
		
		if (m_newTrousersResName && m_trousersEnt && m_trousersEnt.GetPrefabData().GetPrefabName() != m_newTrousersResName)
		{
			m_ismc.TryDeleteItem(m_trousersEnt);
			//m_blmc.Unwear(m_trousersEnt);
		}
		
		if (m_newBootsResName && m_bootsEnt && m_bootsEnt.GetPrefabData().GetPrefabName() != m_newBootsResName)
		{
			m_ismc.TryDeleteItem(m_bootsEnt);
			//m_blmc.Unwear(m_bootsEnt);
		}
		
		if (m_newBottomItemResName && m_bottomItemEnt && m_bottomItemEnt.GetPrefabData().GetPrefabName() != m_newBottomItemResName)
		{
			m_ismc.TryDeleteItem(m_bottomItemEnt);
			//m_blmc.Unwear(m_bottomItemEnt);
		}
		
		if (m_newItemResName && m_itemEnt && m_itemEnt.GetPrefabData().GetPrefabName() != m_newItemResName)
		{
			m_ismc.TryDeleteItem(m_itemEnt);
			//m_blmc.Unwear(m_itemEnt);
		}
		
		if (m_newPrimaryWeapon1ResName && m_primaryWeapon1Ent && m_primaryWeapon1Ent.GetPrefabData().GetPrefabName() != m_newPrimaryWeapon1ResName)
		{		
			m_ismc.TryDeleteItem(m_primaryWeapon1Ent);
		}
		
		if (m_newPrimaryWeapon2ResName && m_primaryWeapon2Ent && m_primaryWeapon2Ent.GetPrefabData().GetPrefabName() != m_newPrimaryWeapon2ResName)
		{
			m_ismc.TryDeleteItem(m_primaryWeapon2Ent);
		}
		
		if (m_newSecondaryWeaponResName && m_secondaryWeaponEnt && m_secondaryWeaponEnt.GetPrefabData().GetPrefabName() != m_newSecondaryWeaponResName)
		{
			m_ismc.TryDeleteItem(m_secondaryWeaponEnt);
		}
		
		if (m_newGrenadeResName && m_grenadeEnt && m_grenadeEnt.GetPrefabData().GetPrefabName() != m_newGrenadeResName)
		{
			m_ismc.TryDeleteItem(m_grenadeEnt);
		}
		
		if (m_newThrowableResName && m_throwableEnt && m_throwableEnt.GetPrefabData().GetPrefabName() != m_newThrowableResName)
		{
			m_ismc.TryDeleteItem(m_throwableEnt);
		}
		
		for(int j = 0; j < itemSlots; j++)
		{
			if ((m_newJacketResName && m_jacketEnt) || !m_jacketEnt) m_ismc.TryDeleteItem(m_jacketItems[j]);
			if ((m_newVestResName && m_vestEnt) || !m_vestEnt) m_ismc.TryDeleteItem(m_vestItems[j]);
			if ((m_newBackpackResName && m_backpackEnt) || !m_backpackEnt) m_ismc.TryDeleteItem(m_backpackItems[j]);
			if ((m_newTrousersResName && m_trousersEnt) || !m_trousersEnt) m_ismc.TryDeleteItem(m_trousersItems[j]);
		}
		
		// if add to empty slot
		if (m_newHelmetResName && !m_oldHelmetEnt) m_ismc.TrySpawnPrefabToStorage(m_newHelmetResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newUpperitemResName && !m_oldUpperitemEnt) m_ismc.TrySpawnPrefabToStorage(m_newUpperitemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newBackpackResName && !m_oldBackpackEnt) m_ismc.TrySpawnPrefabToStorage(m_newBackpackResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newJacketResName && !m_oldJacketEnt) m_ismc.TrySpawnPrefabToStorage(m_newJacketResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newVestResName && !m_oldVestEnt) m_ismc.TrySpawnPrefabToStorage(m_newVestResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newTrousersResName && !m_oldTrousersEnt) m_ismc.TrySpawnPrefabToStorage(m_newTrousersResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newBootsResName && !m_oldBootsEnt) m_ismc.TrySpawnPrefabToStorage(m_newBootsResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newBottomItemResName && !m_oldBottomItemEnt) m_ismc.TrySpawnPrefabToStorage(m_newBottomItemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newItemResName && !m_oldItemEnt) m_ismc.TrySpawnPrefabToStorage(m_newItemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		if (m_newPrimaryWeapon1ResName && !m_primaryWeapon1Ent) m_ismc.TrySpawnPrefabToStorage(m_newPrimaryWeapon1ResName, m_ewsc, 0, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
		if (m_newPrimaryWeapon2ResName && !m_primaryWeapon2Ent) m_ismc.TrySpawnPrefabToStorage(m_newPrimaryWeapon2ResName, m_ewsc, 1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
		if (m_newSecondaryWeaponResName && !m_secondaryWeaponEnt) m_ismc.TrySpawnPrefabToStorage(m_newSecondaryWeaponResName, m_ewsc, -1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
		if (m_newGrenadeResName && !m_grenadeEnt) m_ismc.TrySpawnPrefabToStorage(m_newGrenadeResName, m_ewsc, -1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
		if (m_newThrowableResName && !m_throwableEnt) m_ismc.TrySpawnPrefabToStorage(m_newThrowableResName, m_ewsc, -1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
		
		for(int i = 0; i < itemSlots; i++)
		{
			if (!m_newBackpackResName && m_newBackpackItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newBackpackItemsResName[i], m_backpackStorage, i, EStoragePurpose.PURPOSE_ANY, null); // maybe need test slotid
			if (!m_newJacketResName && m_newJacketItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newJacketItemsResName[i], m_jacketStorage, i, EStoragePurpose.PURPOSE_ANY, null);
			if (!m_newVestItemsResName && m_newVestItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newVestItemsResName[i], m_vestStorage, i, EStoragePurpose.PURPOSE_ANY, null);
			if (!m_newTrousersItemsResName && m_newTrousersItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newTrousersItemsResName[i], m_trousersStorage, i, EStoragePurpose.PURPOSE_ANY, null);
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnItemRemoved(IEntity entity, BaseInventoryStorageComponent storage)
	{
		switch(entity)
		{
			case m_helmetEnt:
			{
				if (m_newHelmetResName) m_ismc.TrySpawnPrefabToStorage(m_newHelmetResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_upperitemEnt: 
			{
				if (m_newUpperitemResName) m_ismc.TrySpawnPrefabToStorage(m_newUpperitemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_backpackEnt:
			{
				if (m_newBackpackResName) m_ismc.TrySpawnPrefabToStorage(m_newBackpackResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_jacketEnt:
			{
				if (m_newJacketResName) m_ismc.TrySpawnPrefabToStorage(m_newJacketResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_vestEnt:
			{
				if (m_newVestResName) m_ismc.TrySpawnPrefabToStorage(m_newVestResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_trousersEnt:
			{
				if (m_newTrousersResName) m_ismc.TrySpawnPrefabToStorage(m_newTrousersResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_bootsEnt:
			{
				if (m_newBootsResName) m_ismc.TrySpawnPrefabToStorage(m_newBootsResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_bottomItemEnt:
			{
				if (m_newBottomItemResName) m_ismc.TrySpawnPrefabToStorage(m_newBottomItemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_itemEnt:
			{
				if (m_newItemResName) m_ismc.TrySpawnPrefabToStorage(m_newItemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
				break;
			}
			case m_primaryWeapon1Ent:
			{
				if (m_newPrimaryWeapon1ResName) m_ismc.TrySpawnPrefabToStorage(m_newPrimaryWeapon1ResName, m_ewsc, 0, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
				break;
			}
			case m_primaryWeapon2Ent:
			{
				if (m_newPrimaryWeapon2ResName) m_ismc.TrySpawnPrefabToStorage(m_newPrimaryWeapon2ResName, m_ewsc, 1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
				break;
			}
			case m_secondaryWeaponEnt:
			{
				if (m_newSecondaryWeaponResName) m_ismc.TrySpawnPrefabToStorage(m_newSecondaryWeaponResName, m_ewsc, -1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
				break;
			}
			case m_grenadeEnt:
			{
				if (m_newGrenadeResName) m_ismc.TrySpawnPrefabToStorage(m_newGrenadeResName, m_ewsc, -1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
				break;
			}
			case m_throwableEnt:
			{
				if (m_newThrowableResName) m_ismc.TrySpawnPrefabToStorage(m_newThrowableResName, m_ewsc, -1, EStoragePurpose.PURPOSE_WEAPON_PROXY, null);
				break;
			}
		}
	
		// when keep old storage but fill it with new items
		if (uniqueRun)
		{
			for(int i = 0; i < itemSlots; i++)
			{
				if (!m_newBackpackResName && m_newBackpackItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newBackpackItemsResName[i], m_backpackStorage, i, EStoragePurpose.PURPOSE_ANY, null); // maybe need test slotid
				if (!m_newJacketResName && m_newJacketItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newJacketItemsResName[i], m_jacketStorage, i, EStoragePurpose.PURPOSE_ANY, null);
				if (!m_newVestItemsResName && m_newVestItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newVestItemsResName[i], m_vestStorage, i, EStoragePurpose.PURPOSE_ANY, null);
				if (!m_newTrousersItemsResName && m_newTrousersItemsResName[i]) m_ismc.TrySpawnPrefabToStorage(m_newTrousersItemsResName[i], m_trousersStorage, i, EStoragePurpose.PURPOSE_ANY, null);
			}
			uniqueRun = false;
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnItemAdded(IEntity entity, BaseInventoryStorageComponent storage)
	{
		if (entity.GetPrefabData().GetPrefabName() == m_newBackpackResName || entity.GetPrefabData().GetPrefabName() == m_newJacketResName || entity.GetPrefabData().GetPrefabName() == m_newVestResName || entity.GetPrefabData().GetPrefabName() == m_newTrousersResName)
		{
			BaseContainer meshComponent = getMeshComponentByClassName(entity.GetPrefabData().GetPrefabName(), "BaseLoadoutClothComponent");
			if (meshComponent)
			{
				LoadoutAreaType lat;
				meshComponent.Get("AreaType", lat);
				switch(lat.Type())
				{
					case LoadoutBackpackArea:
					{
						m_newBackpackEnt = entity;
						m_backpackStorage = m_cisc.GetStorageFromLoadoutSlot(lat);
						for(int i = 0; i < itemSlots; i++)
						{
							m_ismc.TrySpawnPrefabToStorage(m_newBackpackItemsResName[i], m_backpackStorage, i, EStoragePurpose.PURPOSE_ANY, null); // maybe need test slotid
						}
						break;
					}
					case LoadoutJacketArea:
					{
						m_newJacketEnt = entity;
						m_jacketStorage = m_cisc.GetStorageFromLoadoutSlot(lat);
						for(int i = 0; i < itemSlots; i++)
						{
							m_ismc.TrySpawnPrefabToStorage(m_newJacketItemsResName[i], m_jacketStorage, i, EStoragePurpose.PURPOSE_ANY, null);
						}
						break;
					}
					case LoadoutVestArea:
					{
						m_newVestEnt = entity;
						m_vestStorage = m_cisc.GetStorageFromLoadoutSlot(lat);
						for(int i = 0; i < itemSlots; i++)
						{
							m_ismc.TrySpawnPrefabToStorage(m_newVestItemsResName[i], m_vestStorage, i, EStoragePurpose.PURPOSE_ANY, null);
						}
						break;
					}
					case LoadoutPantsArea:
					{
						m_newTrousersEnt = entity;
						m_trousersStorage = m_cisc.GetStorageFromLoadoutSlot(lat);
						for(int i = 0; i < itemSlots; i++)
						{
							m_ismc.TrySpawnPrefabToStorage(m_newTrousersItemsResName[i], m_trousersStorage, i, EStoragePurpose.PURPOSE_ANY, null);
						}
						break;
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected BaseContainer getMeshComponentByClassName(ResourceName resName, string className)
	{
		Resource resource = Resource.Load(resName);
		BaseResourceObject prefabBase = resource.GetResource();
		BaseContainer prefabSrc = prefabBase.ToBaseContainer();
		BaseContainerList components = prefabSrc.GetObjectArray("components");

		BaseContainer meshComponent = null;
		for (int c = components.Count() - 1; c >= 0; c--)
		{
			meshComponent = components.Get(c);
			if (meshComponent.GetClassName() == className)
				break;

			meshComponent = null;
		}

		return meshComponent;
	}
	
	//------------------------------------------------------------------------------------------------
	protected BaseContainer getMeshComponentByClassNames(ResourceName resName, string classNameA, string classnameB, string classnameC = "NONE")
	{
		Resource resource = Resource.Load(resName);
		BaseResourceObject prefabBase = resource.GetResource();
		BaseContainer prefabSrc = prefabBase.ToBaseContainer();
		BaseContainerList components = prefabSrc.GetObjectArray("components");

		BaseContainer meshComponent = null;
		for (int c = components.Count() - 1; c >= 0; c--)
		{
			meshComponent = components.Get(c);
			if (meshComponent.GetClassName() == classNameA || meshComponent.GetClassName() == classnameB || meshComponent.GetClassName() == classnameC)
				break;

			meshComponent = null;
		}

		return meshComponent;
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		// remove invokers
		m_ismc.m_OnItemAddedInvoker.Remove(OnItemAdded);
		m_ismc.m_OnItemRemovedInvoker.Remove(OnItemRemoved);
		
		m_ismc.SetInventoryLocked(false);
		
		m_gameMode.saveLoadout();
		
		m_oldPrimaryWeapon1Ent = null;
		m_oldPrimaryWeapon2Ent = null;
		m_oldSecondaryWeaponEnt = null;
		m_oldGrenadeEnt = null;
		m_oldThrowableEnt = null;
	
		m_newPrimaryWeapon1ResName = "";
		m_newPrimaryWeapon2ResName = "";
		m_newSecondaryWeaponResName = "";
		m_newGrenadeResName = "";
		m_newThrowableResName = "";
	
		m_primaryWeapon1Ent = null;
		m_primaryWeapon2Ent = null;
		m_secondaryWeaponEnt = null;
		m_grenadeEnt = null;
		m_throwableEnt = null;

		m_helmetEnt = null;
		m_upperitemEnt = null;
		m_jacketEnt = null;
		m_vestEnt = null;
		m_backpackEnt = null;
		m_trousersEnt = null;
		m_bootsEnt = null;
		m_bottomItemEnt = null;
		m_itemEnt = null;
		
		m_oldHelmetEnt = null;
		m_oldUpperitemEnt = null;
		m_oldJacketEnt = null;
		m_oldVestEnt = null;
		m_oldBackpackEnt = null;
		m_oldTrousersEnt = null;
		m_oldBootsEnt = null;
		m_oldBottomItemEnt = null;
		m_oldItemEnt = null;
		
		m_newHelmetResName = "";
		m_newUpperitemResName = "";
		m_newJacketResName = "";
		m_newVestResName = "";
		m_newBackpackResName = "";
		m_newTrousersResName = "";
		m_newBootsResName = "";
		m_newBottomItemResName = "";
		m_newItemResName = "";
		
		for(int i = 0; i < itemSlots; i++)
		{
			m_jacketItems[i] = null;
			m_vestItems[i] = null;
			m_backpackItems[i] = null;
			m_trousersItems[i] = null;
	
			m_oldJacketItems[i] = null;
			m_oldVestItems[i] = null;
			m_oldBackpackItems[i] = null;
			m_oldTrousersItems[i] = null;
	
			m_newJacketItemsResName[i] = "";
			m_newVestItemsResName[i] = "";
			m_newBackpackItemsResName[i] = "";
			m_newTrousersItemsResName[i] = "";
		}
		
		m_jacketStorage = null;
		m_backpackStorage = null;
		m_vestStorage = null;
		m_trousersStorage = null;
		
		m_newJacketEnt = null;
		m_newVestEnt = null;
		m_newBackpackEnt = null;
		m_newTrousersEnt = null;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		// TODO close menu when bars or med down
	}
};