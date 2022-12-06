class SCR_CTI_PurchaseMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode gameMode;
	protected PlayerController pc;
	protected int playerId;
	protected FactionKey factionKey;
	protected FactionAffiliationComponent affiliationComp;
	
	protected string currentSelectedFactoryTypeIcon = "None";
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 0.2;
	
	protected Widget m_wRoot;
	
	protected RichTextWidget m_cost;
	protected RichTextWidget m_resources;
	
	protected ButtonWidget m_buttoninf;
	protected ButtonWidget m_buttonlight;
	protected ButtonWidget m_buttonheavy;
	protected ButtonWidget m_buttonair;
	protected ButtonWidget m_buttonrep;
	protected ButtonWidget m_buttonammo;
	protected ButtonWidget m_buttonnaval;
	protected ButtonWidget m_buttonflag;
	
	protected ButtonWidget m_driver;
	protected ButtonWidget m_gunner;
	protected ButtonWidget m_commander;
	protected ButtonWidget m_crew;
	protected ButtonWidget m_lock;
	protected ButtonWidget m_unlock;
	
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;
	
	protected ButtonWidget m_purchase;
	protected ButtonWidget m_cancelqueue;
	protected ButtonWidget m_buyindsalvager;

	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;
	
	protected XComboBoxWidget m_comboteam;
	protected XComboBoxWidget m_combofactory;
	
	protected ref array<IEntity> m_sortedfactories = {};
	
	protected SCR_AIGroup m_playergroup;

	protected ref SCR_CTI_ButtonHandler m_buttonEventHandler;
	protected ref SCR_CTI_IconButtonHandler m_iconbuttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		pc = GetGame().GetPlayerController();
		playerId = pc.GetPlayerId();
		affiliationComp = FactionAffiliationComponent.Cast(pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		factionKey = affiliationComp.GetAffiliatedFaction().GetFactionKey();
		
		m_wRoot = GetRootWidget();
		
		m_cost = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Cost"));
		m_resources = RichTextWidget.Cast(m_wRoot.FindAnyWidget("Resources"));
		
		// buttons
		m_buttoninf = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonInf"));
		m_buttonlight = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonLight"));
		m_buttonheavy = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonHeavy"));
		m_buttonair = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonAir"));
		m_buttonrep = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonRep"));
		m_buttonammo = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonAmmo"));
		m_buttonnaval = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonNaval"));
		m_buttonflag = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonFlag"));
		
		m_driver = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonDriver"));
		m_gunner = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonGunner"));
		m_commander = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonCommander"));
		m_crew = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonCrew"));
		m_lock = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonLock"));
		m_unlock = ButtonWidget.Cast(m_wRoot.FindAnyWidget("ButtonUnlock"));
		
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		m_purchase = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Purchase"));
		m_cancelqueue = ButtonWidget.Cast(m_wRoot.FindAnyWidget("CancelQueue"));
		m_buyindsalvager = ButtonWidget.Cast(m_wRoot.FindAnyWidget("BuyIndependentSalvager"));
		
		// listbox
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));
		
		// xcombobox
		m_comboteam = XComboBoxWidget.Cast(m_wRoot.FindAnyWidget("XComboBoxTeam"));
		m_combofactory = XComboBoxWidget.Cast(m_wRoot.FindAnyWidget("XComboBoxFactory"));

		// handler
		m_buttonEventHandler = new SCR_CTI_ButtonHandler();
		m_iconbuttonEventHandler = new SCR_CTI_IconButtonHandler();
		
		m_buttoninf.AddHandler(m_iconbuttonEventHandler);
		m_buttonlight.AddHandler(m_iconbuttonEventHandler);
		m_buttonheavy.AddHandler(m_iconbuttonEventHandler);
		m_buttonair.AddHandler(m_iconbuttonEventHandler);
		m_buttonrep.AddHandler(m_iconbuttonEventHandler);
		m_buttonammo.AddHandler(m_iconbuttonEventHandler);
		m_buttonnaval.AddHandler(m_iconbuttonEventHandler);
		m_buttonflag.AddHandler(m_iconbuttonEventHandler);

		m_driver.AddHandler(m_iconbuttonEventHandler);
		m_gunner.AddHandler(m_iconbuttonEventHandler);
		m_commander.AddHandler(m_iconbuttonEventHandler);
		m_crew.AddHandler(m_iconbuttonEventHandler);
		m_lock.AddHandler(m_iconbuttonEventHandler);
		m_unlock.AddHandler(m_iconbuttonEventHandler);

		m_back.SetColor(Color.Orange);
		m_back.AddHandler(m_buttonEventHandler);

		m_exit.SetColor(Color.Orange);
		m_exit.AddHandler(m_buttonEventHandler);
		
		m_purchase.SetColor(Color.Orange);
		m_purchase.AddHandler(m_buttonEventHandler);
		
		//m_cancelqueue.SetColor(Color.Orange);
		//m_cancelqueue.AddHandler(m_buttonEventHandler);
		//m_buyindsalvager.SetColor(Color.Orange);
		//m_buyindsalvager.AddHandler(m_buttonEventHandler);
		
		SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
		m_resources.SetText("Resources: " + cdc.getFunds().ToString() + "$");

		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		m_playergroup = gmc.GetPlayerGroup(playerId);
		m_comboteam.AddItem("Group " + m_playergroup.GetGroupID().ToString() + " " + m_playergroup.GetCustomName());
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
			SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
			m_resources.SetText("Resources: " + cdc.getFunds().ToString() + "$");

			// if factory type selection changed
			if (currentSelectedFactoryTypeIcon != m_iconbuttonEventHandler.getSelectedFactoryTypeIcon())
			{
				m_listboxcomp.SetAllItemsSelected(false);
				m_combofactory.ClearAll();
				m_sortedfactories.Clear();
				
				// listbox update
				SCR_CTI_UnitData unitData;
				int removeIndex = -1;
				switch (factionKey)
				{
					case "USSR":
					{
						for (int i = 0; i < gameMode.UnitsUSSR.g_USSR_Units.Count(); i++)
						{
							unitData = gameMode.UnitsUSSR.g_USSR_Units[i];
							if (unitData.getFac() == m_iconbuttonEventHandler.getSelectedFactoryTypeIcon())
							{
								m_listboxcomp.AddItem(unitData.getName(), unitData);
							} else {
								removeIndex = m_listboxcomp.FindItemWithData(unitData);
								if (removeIndex > -1) m_listboxcomp.RemoveItem(removeIndex);
							}
						}
						break;
					}
					case "US":
					{
						for (int i = 0; i < gameMode.UnitsUS.g_US_Units.Count(); i++)
						{
							unitData = gameMode.UnitsUS.g_US_Units[i];
							if (unitData.getFac() == m_iconbuttonEventHandler.getSelectedFactoryTypeIcon())
							{
								m_listboxcomp.AddItem(unitData.getName(), unitData);
							} else {
								removeIndex = m_listboxcomp.FindItemWithData(unitData);
								if (removeIndex > -1) m_listboxcomp.RemoveItem(removeIndex);
							}
						}
						break;
					}		
				}

				// xcombobox update
				SCR_CTI_FactoryData factoryData;
				array<IEntity> unsortedfactories = SCR_CTI_GetSideFactories.GetSideFactoriesByType(factionKey, m_iconbuttonEventHandler.getSelectedFactoryTypeIcon());
				if (unsortedfactories)
				{
					m_sortedfactories = SCR_CTI_SortByDistance.SortByDistance(pc.GetControlledEntity(), unsortedfactories);
					unsortedfactories.Clear();
					unsortedfactories = null;
					for (int i = 0; i < m_sortedfactories.Count(); i++)
					{
						int index = -1;
						switch (factionKey)
						{
							case "USSR":
							{
								index = gameMode.FactoriesUSSR.findIndexFromResourcename(m_sortedfactories[i].GetPrefabData().GetPrefabName());
								factoryData = gameMode.FactoriesUSSR.g_USSR_Factories[index];
								break;
							}
							case "US":
							{
								index = gameMode.FactoriesUS.findIndexFromResourcename(m_sortedfactories[i].GetPrefabData().GetPrefabName());
								factoryData = gameMode.FactoriesUS.g_US_Factories[index];
								break;
							}
						}
						if (index > -1)
						{
							float distance = vector.Distance(pc.GetControlledEntity().GetOrigin(), m_sortedfactories[i].GetOrigin());
							m_combofactory.AddItem(string.Format(factoryData.getName() + " - " + (Math.Round(distance)).ToString() + "m - Grid [" + SCR_MapEntity.GetGridPos(m_sortedfactories[i].GetOrigin(), 2, 4, ",") + "]"));
						}
					}
				}

				m_cost.SetText("Cost:");
				currentSelectedFactoryTypeIcon = m_iconbuttonEventHandler.getSelectedFactoryTypeIcon();
			} else {
				int selectedId = m_listboxcomp.GetSelectedItem();
				if (m_listboxcomp.GetItemCount() > 0 && selectedId > -1 && m_listboxcomp.GetElementComponent(selectedId) && m_listboxcomp.IsItemSelected(selectedId))
				{
					SCR_CTI_UnitData unitData = SCR_CTI_UnitData.Cast(m_listboxcomp.GetItemData(selectedId));
					m_cost.SetText("Cost: " + unitData.getPri() + "$");
				} else {
					m_cost.SetText("Cost:");
				}
			}
			
			m_timeDelta = 0;
		}
	}
	
	//------------------------------------------------------------------------------------------------
	array<IEntity> getSortedFactoriesForCombobox()
	{
		return m_sortedfactories;
	}
	
	//------------------------------------------------------------------------------------------------
	AIGroup getGroupforCombobox()
	{
		return m_playergroup;
	}
};