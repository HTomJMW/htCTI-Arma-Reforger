class SCR_CTI_PurchaseMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected SCR_CTI_ClientData m_clientData;
	protected int m_playerId;
	protected FactionKey m_factionKey;
	protected FactionAffiliationComponent m_affiliationComp;
	protected SCR_CTI_UpgradeComponent m_upgradeComp;
	
	protected string currentSelectedFactoryTypeIcon = "None";
	
	protected float m_timeDelta = 1;
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

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_PurchaseMenuButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_affiliationComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_factionKey = m_affiliationComp.GetAffiliatedFaction().GetFactionKey();
		m_upgradeComp = SCR_CTI_UpgradeComponent.Cast(m_gameMode.FindComponent(SCR_CTI_UpgradeComponent));
		
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

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_PurchaseMenuButtonHandler();
		
		m_buttoninf.AddHandler(m_buttonEventHandler);
		m_buttonlight.AddHandler(m_buttonEventHandler);
		m_buttonheavy.AddHandler(m_buttonEventHandler);
		m_buttonair.AddHandler(m_buttonEventHandler);
		m_buttonrep.AddHandler(m_buttonEventHandler);
		m_buttonammo.AddHandler(m_buttonEventHandler);
		m_buttonnaval.AddHandler(m_buttonEventHandler);
		m_buttonflag.SetColor(Color.Gray);
		m_buttonflag.SetEnabled(false);
		//m_buttonflag.AddHandler(m_buttonEventHandler);

		//m_driver.SetEnabled(false);
		m_driver.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_driver.AddHandler(m_buttonEventHandler);
		//m_gunner.SetEnabled(false);
		m_gunner.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_gunner.AddHandler(m_buttonEventHandler);
		//m_commander.SetEnabled(false);
		m_commander.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_commander.AddHandler(m_buttonEventHandler);
		//m_crew.SetEnabled(false);
		m_crew.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_crew.AddHandler(m_buttonEventHandler);
		//m_lock.SetEnabled(false);
		m_lock.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_lock.AddHandler(m_buttonEventHandler);
		
		// Unlock default picked
		//m_unlock.SetEnabled(false);
		m_unlock.SetColor(Color.White);
		ImageWidget children = ImageWidget.Cast(m_unlock.GetChildren());
		children.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_unlock.AddHandler(m_buttonEventHandler);

		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);
		
		m_purchase.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_purchase.AddHandler(m_buttonEventHandler);

		m_cancelqueue.SetColor(Color.Gray);
		m_cancelqueue.SetEnabled(false);
		//m_cancelqueue.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_cancelqueue.AddHandler(m_buttonEventHandler);
		m_buyindsalvager.SetColor(Color.Gray);
		m_buyindsalvager.SetEnabled(false);
		//m_buyindsalvager.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		//m_buyindsalvager.AddHandler(m_buttonEventHandler);
		
		m_clientData = m_gameMode.getClientData(m_playerId);

		int funds = 0;
		if (m_clientData)
		{
			if (m_clientData.isCommander())
			{
				funds = m_gameMode.getCommanderFunds(m_factionKey);
			} else {
				funds = m_clientData.getFunds();
			}
		}
		
		m_resources.SetText("Resources: " + funds.ToString() + "$");

		// TODO only commander can buy units for other groups
		SCR_GroupsManagerComponent gmc = SCR_GroupsManagerComponent.GetInstance();
		m_playergroup = gmc.GetPlayerGroup(m_playerId);
		m_comboteam.AddItem("Group " + m_playergroup.GetGroupID().ToString() + " " + m_playergroup.GetCustomName());
	}
	
	//------------------------------------------------------------------------------------------------
	protected void listboxClear()
	{
		for (int i = m_listboxcomp.GetItemCount() - 1; i >= 0; i--)
		{
			m_listboxcomp.RemoveItem(i);
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
			int funds = 0;
			if (m_clientData)
			{
				if (m_clientData.isCommander())
				{
					funds = m_gameMode.getCommanderFunds(m_factionKey);
				} else {
					funds = m_clientData.getFunds();
				}
			}

			m_resources.SetText("Resources: " + funds.ToString() + "$");
			
			array<IEntity> barracks = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Barracks");
			array<IEntity> lfs = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Light Factory");
			array<IEntity> hfs = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Heavy Factory");
			array<IEntity> afs = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Air Factory");
			array<IEntity> rds = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Repair Depot");
			array<IEntity> ads = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Ammo Depot");
			array<IEntity> navals = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, "Naval");
			
			if (barracks.IsEmpty())
			{
				if (m_buttoninf.IsEnabled())
				{
					if (m_buttoninf.GetColor() == Color.White) listboxClear(); // if is selected when lost factory - need test this later
					m_buttoninf.SetColor(Color.Gray);
					m_buttoninf.SetEnabled(false);
				}
			} else {
				if (!m_buttoninf.IsEnabled())
				{
					m_buttoninf.SetColor(SCR_CTI_Constants.CTI_ORANGE);
					m_buttoninf.SetEnabled(true);
				}
			}
			if (lfs.IsEmpty())
			{
				if (m_buttonlight.IsEnabled())
				{
					if (m_buttonlight.GetColor() == Color.White) listboxClear();
					m_buttonlight.SetColor(Color.Gray);
					m_buttonlight.SetEnabled(false);
				}
			} else {
				if (!m_buttonlight.IsEnabled())
				{
					m_buttonlight.SetColor(SCR_CTI_Constants.CTI_ORANGE);
					m_buttonlight.SetEnabled(true);
				}
			}
			if (hfs.IsEmpty())
			{
				if (m_buttonheavy.IsEnabled())
				{
					if (m_buttonheavy.GetColor() == Color.White) listboxClear();
					m_buttonheavy.SetColor(Color.Gray);
					m_buttonheavy.SetEnabled(false);
				}
			} else {
				if (!m_buttonheavy.IsEnabled())
				{
					m_buttonheavy.SetColor(SCR_CTI_Constants.CTI_ORANGE);
					m_buttonheavy.SetEnabled(true);
				}
			}
			if (afs.IsEmpty())
			{
				if (m_buttonair.IsEnabled())
				{
					if (m_buttonair.GetColor() == Color.White) listboxClear();
					m_buttonair.SetColor(Color.Gray);
					m_buttonair.SetEnabled(false);
				}
			} else {
				if (!m_buttonair.IsEnabled())
				{
					m_buttonair.SetColor(SCR_CTI_Constants.CTI_ORANGE);
					m_buttonair.SetEnabled(true);
				}
			}
			if (rds.IsEmpty())
			{
				if (m_buttonrep.IsEnabled())
				{
					if (m_buttonrep.GetColor() == Color.White) listboxClear();
					m_buttonrep.SetColor(Color.Gray);
					m_buttonrep.SetEnabled(false);
				}
			} else {
				if (!m_buttonrep.IsEnabled())
				{
					m_buttonrep.SetColor(SCR_CTI_Constants.CTI_ORANGE);
					m_buttonrep.SetEnabled(true);
				}
			}
			if (ads.IsEmpty())
			{
				if (m_buttonammo.IsEnabled())
				{
					if (m_buttonammo.GetColor() == Color.White) listboxClear();
					m_buttonammo.SetColor(Color.Gray);
					m_buttonammo.SetEnabled(false);
				}
			} else {
				if (!m_buttonammo.IsEnabled())
				{
					m_buttonammo.SetColor(SCR_CTI_Constants.CTI_ORANGE);
					m_buttonammo.SetEnabled(true);
				}
			}
			if (navals.IsEmpty())
			{
				if (m_buttonnaval.IsEnabled())
				{
					if (m_buttonnaval.GetColor() == Color.White) listboxClear();
					m_buttonnaval.SetColor(Color.Gray);
					m_buttonnaval.SetEnabled(false);
				}
			} else {
				if (!m_buttonnaval.IsEnabled())
				{
					m_buttonnaval.SetColor(SCR_CTI_Constants.CTI_ORANGE);
					m_buttonnaval.SetEnabled(true);
				}
			}

			// If factory type selection changed
			if (currentSelectedFactoryTypeIcon != m_buttonEventHandler.getSelectedFactoryTypeIcon())
			{
				m_listboxcomp.SetAllItemsSelected(false);
				m_combofactory.ClearAll();
				m_sortedfactories.Clear();
				
				// listbox update
				SCR_CTI_UnitData unitData;
				SCR_CTI_UpgradeData upgradeData;
				array<int> upgradeIndexes = {};
				int removeIndex = -1;
				switch (m_factionKey)
				{
					case "USSR":
					{
						for (int i = 0; i < m_gameMode.UnitsUSSR.g_USSR_Units.Count(); i++)
						{
							unitData = m_gameMode.UnitsUSSR.g_USSR_Units[i];
							upgradeIndexes = m_gameMode.Upgrades.findIndexesByLabel(m_buttonEventHandler.getSelectedFactoryTypeIcon());
							int upLevel = 0;
							foreach (int index : upgradeIndexes)
							{
								upgradeData = m_gameMode.Upgrades.g_Upgrades[index];
								if (m_upgradeComp.getUpgradeStatus(m_factionKey, index) == UpgradeStatus.FINISHED)
								{
									int level = upgradeData.getLevel();
									if (level > upLevel) upLevel = level;
								}
							}
							if (unitData.getFactory() == m_buttonEventHandler.getSelectedFactoryTypeIcon() && unitData.getUplevel() <= upLevel)
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
						for (int i = 0; i < m_gameMode.UnitsUS.g_US_Units.Count(); i++)
						{
							unitData = m_gameMode.UnitsUS.g_US_Units[i];
							upgradeIndexes = m_gameMode.Upgrades.findIndexesByLabel(m_buttonEventHandler.getSelectedFactoryTypeIcon());
							int upLevel = 0;
							foreach (int index : upgradeIndexes)
							{
								upgradeData = m_gameMode.Upgrades.g_Upgrades[index];
								if (m_upgradeComp.getUpgradeStatus(m_factionKey, index) == UpgradeStatus.FINISHED)
								{
									int level = upgradeData.getLevel();
									if (level > upLevel) upLevel = level;
								}
							}
							if (unitData.getFactory() == m_buttonEventHandler.getSelectedFactoryTypeIcon() && unitData.getUplevel() <= upLevel)
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
				array<IEntity> unsortedfactories = SCR_CTI_GetSideFactories.GetSideFactoriesByType(m_factionKey, m_buttonEventHandler.getSelectedFactoryTypeIcon());
				if (!unsortedfactories.IsEmpty())
				{
					m_sortedfactories = SCR_CTI_SortByDistance.SortByDistance(m_pc.GetControlledEntity(), unsortedfactories);
					unsortedfactories.Clear();
					unsortedfactories = null;
					for (int i = 0; i < m_sortedfactories.Count(); i++)
					{
						int index = -1;
						switch (m_factionKey)
						{
							case "USSR":
							{
								index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(m_sortedfactories[i].GetPrefabData().GetPrefabName());
								factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];
								break;
							}
							case "US":
							{
								index = m_gameMode.FactoriesUS.findIndexFromResourcename(m_sortedfactories[i].GetPrefabData().GetPrefabName());
								factoryData = m_gameMode.FactoriesUS.g_US_Factories[index];
								break;
							}
						}
						if (index > -1)
						{
							float distance = vector.Distance(m_pc.GetControlledEntity().GetOrigin(), m_sortedfactories[i].GetOrigin());
							m_combofactory.AddItem(string.Format(factoryData.getName() + " - " + (Math.Round(distance)).ToString() + "m - Grid [" + SCR_MapEntity.GetGridPos(m_sortedfactories[i].GetOrigin(), 2, 4, ",") + "]"));
						}
					}
				}

				m_cost.SetText("Cost:");
				currentSelectedFactoryTypeIcon = m_buttonEventHandler.getSelectedFactoryTypeIcon();
			} else {
				int selectedId = m_listboxcomp.GetSelectedItem();
				if (m_listboxcomp.GetItemCount() > 0 && selectedId > -1 && m_listboxcomp.GetElementComponent(selectedId) && m_listboxcomp.IsItemSelected(selectedId))
				{
					SCR_CTI_UnitData unitData = SCR_CTI_UnitData.Cast(m_listboxcomp.GetItemData(selectedId));
					m_cost.SetText("Cost: " + unitData.getPrice() + "$");
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