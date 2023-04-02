class SCR_CTI_GearMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected Faction playerFaction;
	protected FactionAffiliationComponent affiliationComp;

	protected BaseLoadoutManagerComponent blmc;
	protected SCR_InventoryStorageManagerComponent ismc;
	protected SCR_CharacterInventoryStorageComponent cisc;
	protected SCR_EquipmentStorageComponent esc;
	protected SCR_TourniquetStorageComponent tsc;

	protected ref array<Managed> cwscArray = {};
	protected ref array<Managed> cgscArray = {};
	
	protected Widget m_wRoot;

	protected ButtonWidget m_buy;
	protected ButtonWidget m_exit;
	
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
	
	protected IEntity m_newPrimaryWeapon1Ent = null;
	protected IEntity m_newPrimaryWeapon2Ent = null;
	protected IEntity m_newSecondaryWeaponEnt = null;
	protected IEntity m_newGrenadeEnt = null;
	protected IEntity m_newThrowableEnt = null;
	
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
	
	protected ResourceName m_newHelmetResName;
	protected ResourceName m_newUpperitemResName;
	protected ResourceName m_newJacketResName;
	protected ResourceName m_newVestResName;
	protected ResourceName m_newBackpackResName;
	protected ResourceName m_newTrousersResName;
	protected ResourceName m_newBootsResName;
	protected ResourceName m_newBottomItemResName;
	protected ResourceName m_newItemResName;
	
	protected IEntity m_jacketItems[itemSlots];
	protected IEntity m_vestItems[itemSlots];
	protected IEntity m_backpackItems[itemSlots];
	protected IEntity m_trousersItems[itemSlots];
	
	protected IEntity m_oldJacketItems[itemSlots];
	protected IEntity m_oldVestItems[itemSlots];
	protected IEntity m_oldBackpackItems[itemSlots];
	protected IEntity m_oldTrousersItems[itemSlots];
	
	protected IEntity m_newJacketItems[itemSlots];
	protected IEntity m_newVestItems[itemSlots];
	protected IEntity m_newBackpackItems[itemSlots];
	protected IEntity m_newTrousersItems[itemSlots];

	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;

	protected ref SCR_CTI_GearMenuButtonHandler m_gearButtonHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		playerFaction = affiliationComp.GetAffiliatedFaction();

		blmc = BaseLoadoutManagerComponent.Cast(pc.GetControlledEntity().FindComponent(BaseLoadoutManagerComponent));
		ismc = SCR_InventoryStorageManagerComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_InventoryStorageManagerComponent));
		cisc = SCR_CharacterInventoryStorageComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_CharacterInventoryStorageComponent)); // 2 child
		esc = SCR_EquipmentStorageComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_EquipmentStorageComponent));
		tsc = SCR_TourniquetStorageComponent.Cast(pc.GetControlledEntity().FindComponent(SCR_TourniquetStorageComponent));
		
		pc.GetControlledEntity().FindComponents(CharacterWeaponSlotComponent, cwscArray);
		pc.GetControlledEntity().FindComponents(CharacterGrenadeSlotComponent, cgscArray);
		
		m_wRoot = GetRootWidget();
		
		m_preViewManager = GetGame().GetItemPreviewManager();
		
		// handler
		m_gearButtonHandler = new SCR_CTI_GearMenuButtonHandler();

		m_buy = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Buy"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));

		m_buy.SetColor(Color.Orange);
		m_buy.AddHandler(m_gearButtonHandler);
		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_gearButtonHandler);
		
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

		FactionKey fk = playerFaction.GetFactionKey();
		SCR_CTI_GearData gearData;
		switch (fk)
		{
			case "USSR":
			{
				for (int i = 0; i < gameMode.GearUSSR.g_USSR_Gear.Count(); i++)
				{
					gearData = gameMode.GearUSSR.g_USSR_Gear[i];
					m_listboxcomp.AddItem(gearData.getPrice().ToString() + "$ " + gearData.getName(), gearData);
				}
				break;
			}
			
			case "US":
			{
				for (int i = 0; i < gameMode.GearUS.g_US_Gear.Count(); i++)
				{
					gearData = gameMode.GearUS.g_US_Gear[i];
					m_listboxcomp.AddItem(gearData.getPrice().ToString() + "$ " + gearData.getName(), gearData);
				}
				break;
			}		
		}

		// character weapon slots
		foreach(Managed managed : cwscArray)
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
		foreach(Managed managed : cgscArray)
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
		m_helmetEnt = blmc.GetClothByArea(LoadoutHeadCoverArea);
		if (m_helmetEnt)
		{
			m_iconHelmet.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_helmet, m_helmetEnt);
			m_helmet.SetResolutionScale(1, 1);
		}
		
		m_upperitemEnt = blmc.GetClothByArea(LoadoutGooglesArea);
		if (m_upperitemEnt)
		{
			m_iconUpperitem.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_upperitem, m_upperitemEnt);
			m_upperitem.SetResolutionScale(1, 1);
		}
		
		m_backpackEnt = blmc.GetClothByArea(LoadoutBackpackArea);
		if (m_backpackEnt)
		{
			m_iconBackpack.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_backpack, m_backpackEnt);
			m_backpack.SetResolutionScale(1, 1);
		}
		
		m_jacketEnt = blmc.GetClothByArea(LoadoutJacketArea);
		if (m_jacketEnt)
		{
			m_iconJacket.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_jacket, m_jacketEnt);
			m_jacket.SetResolutionScale(1, 1);
		}
		
		m_vestEnt = blmc.GetClothByArea(LoadoutVestArea);
		if (m_vestEnt)
		{
			m_iconVest.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_vest, m_vestEnt);
			m_vest.SetResolutionScale(1, 1);
		}
		
		m_trousersEnt = blmc.GetClothByArea(LoadoutPantsArea);
		if (m_trousersEnt)
		{
			m_iconTrousers.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_trousers, m_trousersEnt);
			m_trousers.SetResolutionScale(1, 1);
		}
		
		m_bootsEnt = blmc.GetClothByArea(LoadoutBootsArea);
		if (m_bootsEnt)
		{
			m_iconBoots.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_boots, m_bootsEnt);
			m_boots.SetResolutionScale(1, 1);
		}

		// ESC slot 0 is watch, slot 1 is binocular
		InventoryStorageSlot iss_0 = esc.GetSlot(0);
		m_bottomItemEnt = iss_0.GetAttachedEntity();
		if (m_bottomItemEnt)
		{
			m_iconBottomitem.SetVisible(false);
			m_preViewManager.SetPreviewItem(m_bottomitem, m_bottomItemEnt);
			m_bottomitem.SetResolutionScale(1, 1);
		}

		InventoryStorageSlot iss_1 = esc.GetSlot(1);
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
			BaseInventoryStorageComponent bisc = cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			bisc.GetAll(items);
			
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
			BaseInventoryStorageComponent bisc = cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			bisc.GetAll(items);

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
			BaseInventoryStorageComponent bisc = cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			bisc.GetAll(items);

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
			BaseInventoryStorageComponent bisc = cisc.GetStorageFromLoadoutSlot(loadoutAreaType);
			array<IEntity> items = {};
			bisc.GetAll(items);

			for(int i = 0; i < items.Count(); i++)
			{
				m_trousersTexts[i].SetVisible(false);
				m_preViewManager.SetPreviewItem(m_trousersPreViews[i], items[i]);
				m_trousersPreViews[i].SetResolutionScale(1, 1);
				
				m_trousersItems[i] = items[i];
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void removeItem(Widget w)
	{
		switch(w.GetName())
		{
			case "PreViewHelmet":
			{
				m_oldHelmetEnt = m_helmetEnt;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconHelmet.SetVisible(true);
				
				break;
			}
			case "PreViewUpperItem":
			{
				m_oldUpperitemEnt = m_upperitemEnt;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconUpperitem.SetVisible(true);
				
				break;
			}
			case "PreViewBackPack":
			{
				m_oldBackpackEnt = m_backpackEnt;
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
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconBoots.SetVisible(true);
				
				break;
			}
			case "PreViewBottomItem":
			{
				m_oldBottomItemEnt = m_bottomItemEnt;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconBottomitem.SetVisible(true);
				
				break;
			}
			case "PreViewItem":
			{
				m_oldItemEnt = m_itemEnt;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_iconItem.SetVisible(true);
				
				break;
			}
			case "PreViewPrimary1":
			{
				m_oldPrimaryWeapon1Ent = m_primaryWeapon1Ent;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_primary1Text.SetVisible(true);
				
				break;
			}
			case "PreViewPrimary2":
			{
				m_oldPrimaryWeapon2Ent = m_primaryWeapon2Ent;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_primary2Text.SetVisible(true);
				
				break;
			}
			case "PreViewSecondary":
			{
				m_secondaryWeaponEnt = m_secondaryWeaponEnt;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_secondaryText.SetVisible(true);
				
				break;
			}
			case "PreViewGrenade1":
			{
				m_oldGrenadeEnt = m_grenadeEnt;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_grenade1Text.SetVisible(true);
				
				break;
			}
			case "PreViewGrenade2":
			{
				m_oldThrowableEnt = m_throwableEnt;
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_grenade2Text.SetVisible(true);
				
				break;
			}
			case "ItemPVT0":
			{
				m_oldTrousersItems[0] = m_trousersItems[0];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVT1":
			{
				m_oldTrousersItems[1] = m_trousersItems[1];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVT2":
			{
				m_oldTrousersItems[2] = m_trousersItems[2];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVT3":
			{
				m_oldTrousersItems[3] = m_trousersItems[3];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVT4":
			{
				m_oldTrousersItems[4] = m_trousersItems[4];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVT5":
			{
				m_oldTrousersItems[5] = m_trousersItems[5];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVT6":
			{
				m_oldTrousersItems[6] = m_trousersItems[6];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVT7":
			{
				m_oldTrousersItems[7] = m_trousersItems[7];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVT8":
			{
				m_oldTrousersItems[8] = m_trousersItems[8];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVT9":
			{
				m_oldTrousersItems[9] = m_trousersItems[9];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVT10":
			{
				m_oldTrousersItems[10] = m_trousersItems[10];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_trousersTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVT11":
			{
				m_oldTrousersItems[11] = m_trousersItems[11];
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
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVJ1":
			{
				m_oldJacketItems[1] = m_jacketItems[1];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVJ2":
			{
				m_oldJacketItems[2] = m_jacketItems[2];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVJ3":
			{
				m_oldJacketItems[3] = m_jacketItems[3];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVJ4":
			{
				m_oldJacketItems[4] = m_jacketItems[4];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVJ5":
			{
				m_oldJacketItems[5] = m_jacketItems[5];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVJ6":
			{
				m_oldJacketItems[6] = m_jacketItems[6];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVJ7":
			{
				m_oldJacketItems[7] = m_jacketItems[7];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVJ8":
			{
				m_oldJacketItems[8] = m_jacketItems[8];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVJ9":
			{
				m_oldJacketItems[9] = m_jacketItems[9];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVJ10":
			{
				m_oldJacketItems[10] = m_jacketItems[10];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVJ11":
			{
				m_oldJacketItems[11] = m_jacketItems[11];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_jacketTexts[11].SetVisible(true);
				
				break;
			}
			case "ItemPVB0":
			{
				m_oldBackpackItems[0] = m_backpackItems[0];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVB1":
			{
				m_oldBackpackItems[1] = m_backpackItems[1];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVB2":
			{
				m_oldBackpackItems[2] = m_backpackItems[2];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVB3":
			{
				m_oldBackpackItems[3] = m_backpackItems[3];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVB4":
			{
				m_oldBackpackItems[4] = m_backpackItems[4];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVB5":
			{
				m_oldBackpackItems[5] = m_backpackItems[5];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVB6":
			{
				m_oldBackpackItems[6] = m_backpackItems[6];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVB7":
			{
				m_oldBackpackItems[7] = m_backpackItems[7];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVB8":
			{
				m_oldBackpackItems[8] = m_backpackItems[8];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVB9":
			{
				m_oldBackpackItems[9] = m_backpackItems[9];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVB10":
			{
				m_oldBackpackItems[10] = m_backpackItems[10];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVB11":
			{
				m_oldBackpackItems[11] = m_backpackItems[11];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_backpackTexts[11].SetVisible(true);
				
				break;
			}
			case "ItemPVV0":
			{
				m_oldVestItems[0] = m_vestItems[0];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[0].SetVisible(true);
				
				break;
			}
			case "ItemPVV1":
			{
				m_oldVestItems[1] = m_vestItems[1];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[1].SetVisible(true);
				
				break;
			}
			case "ItemPVV2":
			{
				m_oldVestItems[2] = m_vestItems[2];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[2].SetVisible(true);
				
				break;
			}
			case "ItemPVV3":
			{
				m_oldVestItems[3] = m_vestItems[3];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[3].SetVisible(true);
				
				break;
			}
			case "ItemPVV4":
			{
				m_oldVestItems[4] = m_vestItems[4];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[4].SetVisible(true);
				
				break;
			}
			case "ItemPVV5":
			{
				m_oldVestItems[5] = m_vestItems[5];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[5].SetVisible(true);
				
				break;
			}
			case "ItemPVV6":
			{
				m_oldVestItems[6] = m_vestItems[6];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[6].SetVisible(true);
				
				break;
			}
			case "ItemPVV7":
			{
				m_oldVestItems[7] = m_vestItems[7];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[7].SetVisible(true);
				
				break;
			}
			case "ItemPVV8":
			{
				m_oldVestItems[8] = m_vestItems[8];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[8].SetVisible(true);
				
				break;
			}
			case "ItemPVV9":
			{
				m_oldVestItems[9] = m_vestItems[9];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[9].SetVisible(true);
				
				break;
			}
			case "ItemPVV10":
			{
				m_oldVestItems[10] = m_vestItems[10];
				m_preViewManager.SetPreviewItem(ItemPreviewWidget.Cast(w), null);
				m_vestTexts[10].SetVisible(true);
				
				break;
			}
			case "ItemPVV11":
			{
				m_oldVestItems[11] = m_vestItems[11];
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
				Resource resource = Resource.Load(gearData.getResname());
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "BaseLoadoutClothComponent")
						break;
        
                    meshComponent = null;
                }
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
		}
	}
	
	//------------------------------------------------------------------------------------------------
	void clean()
	{
		if (m_oldHelmetEnt && !m_newHelmetResName) ismc.AskServerToDeleteEntity(m_helmetEnt);
		if (m_oldUpperitemEnt && !m_newUpperitemResName) ismc.AskServerToDeleteEntity(m_upperitemEnt);
		if (m_oldBackpackEnt && !m_newBackpackResName) ismc.AskServerToDeleteEntity(m_backpackEnt);
		if (m_oldJacketEnt && !m_newJacketResName) ismc.AskServerToDeleteEntity(m_jacketEnt);
		if (m_oldVestEnt && !m_newVestResName) ismc.AskServerToDeleteEntity(m_vestEnt);
		if (m_oldTrousersEnt && !m_newTrousersResName) ismc.AskServerToDeleteEntity(m_trousersEnt);
		if (m_oldBootsEnt && !m_newBootsResName) ismc.AskServerToDeleteEntity(m_bootsEnt);
		if (m_oldBottomItemEnt && !m_newBottomItemResName) ismc.AskServerToDeleteEntity(m_bottomItemEnt);
		if (m_oldItemEnt && !m_newItemResName) ismc.AskServerToDeleteEntity(m_itemEnt);
		
		if (m_oldPrimaryWeapon1Ent && !m_newPrimaryWeapon1Ent) ismc.AskServerToDeleteEntity(m_primaryWeapon1Ent);
		if (m_oldPrimaryWeapon2Ent && !m_newPrimaryWeapon2Ent) ismc.AskServerToDeleteEntity(m_primaryWeapon2Ent);
		if (m_oldSecondaryWeaponEnt && !m_newSecondaryWeaponEnt) ismc.AskServerToDeleteEntity(m_secondaryWeaponEnt);
		if (m_oldGrenadeEnt && !m_newGrenadeEnt) ismc.AskServerToDeleteEntity(m_grenadeEnt);
		if (m_oldThrowableEnt && !m_newThrowableEnt) ismc.AskServerToDeleteEntity(m_throwableEnt);
		
		for(int i = 0; i < itemSlots; i++)
		{
			if (m_jacketEnt && m_oldJacketItems[i] && !m_newJacketItems[i]) ismc.AskServerToDeleteEntity(m_jacketItems[i]);
			if (m_vestEnt && m_oldVestItems[i] && !m_newVestItems[i]) ismc.AskServerToDeleteEntity(m_vestItems[i]);
			if (m_backpackEnt && m_oldBackpackItems[i] && !m_newBackpackItems[i]) ismc.AskServerToDeleteEntity(m_backpackItems[i]);
			if (m_trousersEnt && m_oldTrousersItems[i] && !m_newTrousersItems[i]) ismc.AskServerToDeleteEntity(m_trousersItems[i]);
		}
		
		if (m_newHelmetResName && m_helmetEnt && m_helmetEnt.GetPrefabData().GetPrefabName() != m_newHelmetResName)
		{
			ismc.TryDeleteItem(m_helmetEnt); // bug, need unwear after delete, TrySpawnPrefabToStorage not working on client without this
			blmc.Unwear(m_helmetEnt);
		}
		
		if (m_newUpperitemResName && m_upperitemEnt && m_upperitemEnt.GetPrefabData().GetPrefabName() != m_newUpperitemResName)
		{
			ismc.TryDeleteItem(m_upperitemEnt);
			blmc.Unwear(m_upperitemEnt);
		}
		
		if (m_newBackpackResName && m_backpackEnt && m_backpackEnt.GetPrefabData().GetPrefabName() != m_newBackpackResName)
		{
			ismc.TryDeleteItem(m_backpackEnt);
			blmc.Unwear(m_backpackEnt);
		}
		
		if (m_newJacketResName && m_jacketEnt && m_jacketEnt.GetPrefabData().GetPrefabName() != m_newJacketResName)
		{
			ismc.TryDeleteItem(m_jacketEnt);
			blmc.Unwear(m_jacketEnt);
		}
		
		if (m_newVestResName && m_vestEnt && m_vestEnt.GetPrefabData().GetPrefabName() != m_newVestResName)
		{
			ismc.TryDeleteItem(m_vestEnt);
			blmc.Unwear(m_vestEnt);
		}
		
		if (m_newTrousersResName && m_trousersEnt && m_trousersEnt.GetPrefabData().GetPrefabName() != m_newTrousersResName)
		{
			ismc.TryDeleteItem(m_trousersEnt);
			blmc.Unwear(m_trousersEnt);
		}
		
		if (m_newBootsResName && m_bootsEnt && m_bootsEnt.GetPrefabData().GetPrefabName() != m_newBootsResName)
		{
			ismc.TryDeleteItem(m_bootsEnt);
			blmc.Unwear(m_bootsEnt);
		}
		
		if (m_newBottomItemResName && m_bottomItemEnt && m_bottomItemEnt.GetPrefabData().GetPrefabName() != m_newBottomItemResName)
		{
			ismc.TryDeleteItem(m_bottomItemEnt);
			blmc.Unwear(m_bottomItemEnt);
		}
		
		if (m_newItemResName && m_itemEnt && m_itemEnt.GetPrefabData().GetPrefabName() != m_newItemResName)
		{
			ismc.TryDeleteItem(m_itemEnt);
			blmc.Unwear(m_itemEnt);
		}
	}

	//------------------------------------------------------------------------------------------------
	void buy()
	{
		if (m_newHelmetResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newHelmetResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newUpperitemResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newUpperitemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newBackpackResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newBackpackResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newJacketResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newJacketResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newVestResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newVestResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newTrousersResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newTrousersResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newBootsResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newBootsResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newBottomItemResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newBottomItemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}
		
		if (m_newItemResName)
		{
			ismc.TrySpawnPrefabToStorage(m_newItemResName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
		}

		gameMode.saveLoadout();

		// temporary until no update methods
		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();
	}
	
	//------------------------------------------------------------------------------------------------
	protected void delayed(IEntity ent, ResourceName resName)
	{
		InventoryStorageManagerComponent manager = InventoryStorageManagerComponent.Cast(ent.FindComponent(InventoryStorageManagerComponent));
		manager.TrySpawnPrefabToStorage(resName, null, -1, EStoragePurpose.PURPOSE_LOADOUT_PROXY, null);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuOpen()
	{
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		m_oldPrimaryWeapon1Ent = null;
		m_oldPrimaryWeapon2Ent = null;
		m_oldSecondaryWeaponEnt = null;
		m_oldGrenadeEnt = null;
		m_oldThrowableEnt = null;
	
		m_newPrimaryWeapon1Ent = null;
		m_newPrimaryWeapon2Ent = null;
		m_newSecondaryWeaponEnt = null;
		m_newGrenadeEnt = null;
		m_newThrowableEnt = null;
	
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
	
			m_newJacketItems[i] = null;
			m_newVestItems[i] = null;
			m_newBackpackItems[i] = null;
			m_newTrousersItems[i] = null;
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
	}
};