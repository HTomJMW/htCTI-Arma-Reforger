class SCR_CTI_BaseManagementMenu : ChimeraMenuBase
{
	protected SCR_CTI_GameMode m_gameMode;
	protected PlayerController m_pc;
	protected int m_playerId;
	protected FactionKey m_factionKey;
	protected FactionAffiliationComponent m_affiliationComp;
	protected SCR_CTI_UpdateWorkersComponent m_updateWorkersComp;
	protected SCR_CTI_BaseComponent m_baseComp;
	
	protected float m_timeDelta = 1;
	protected const float TIMESTEP = 0.2;
	
	protected Widget m_wRoot;
	
	protected ButtonWidget m_disband;
	protected ButtonWidget m_demolish;
	protected ButtonWidget m_back;
	protected ButtonWidget m_exit;

	protected OverlayWidget m_listbox;
	protected SCR_ListBoxComponent m_listboxcomp;

	protected ref SCR_CTI_CommonButtonHandler m_commonButtonHandler;
	protected ref SCR_CTI_BaseManagementMenuButtonHandler m_buttonEventHandler;

	//------------------------------------------------------------------------------------------------
	override void OnMenuInit()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_pc = GetGame().GetPlayerController();
		m_playerId = m_pc.GetPlayerId();
		m_affiliationComp = FactionAffiliationComponent.Cast(m_pc.GetControlledEntity().FindComponent(FactionAffiliationComponent));
		m_factionKey = m_affiliationComp.GetAffiliatedFaction().GetFactionKey();
		m_updateWorkersComp = SCR_CTI_UpdateWorkersComponent.Cast(m_gameMode.FindComponent(SCR_CTI_UpdateWorkersComponent));
		m_baseComp = SCR_CTI_BaseComponent.Cast(m_gameMode.FindComponent(SCR_CTI_BaseComponent));
		
		m_wRoot = GetRootWidget();

		// buttons
		m_demolish = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Demolish"));
		m_disband = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Disband"));
		m_back = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Back"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		// listbox
		m_listbox = OverlayWidget.Cast(m_wRoot.FindAnyWidget("ListBox"));
		m_listboxcomp = SCR_ListBoxComponent.Cast(m_listbox.FindHandler(SCR_ListBoxComponent));

		SCR_CTI_FactoryData factoryData;
		int index;
		switch (m_factionKey)
		{
			case "USSR":
			{
				foreach (RplId workerRplId : m_updateWorkersComp.m_ussrWorkerRplIds)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
					IEntity worker = rplComp.GetEntity();
					
					int gridX, gridZ;
					SCR_MapEntity.GetGridPos(worker.GetOrigin(), gridX, gridZ);
					
					m_listboxcomp.AddItem("Worker Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), worker.GetOrigin())) + "m", rplComp);
				}

				foreach (RplId ussrWIPStructureRplId : m_baseComp.ussrWIPStructureRplIds)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(ussrWIPStructureRplId));
					IEntity wipStructure = rplComp.GetEntity();
					
					index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(wipStructure.GetPrefabData().GetPrefabName());
					factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];

					int gridX, gridZ;
					SCR_MapEntity.GetGridPos(wipStructure.GetOrigin(), gridX, gridZ);
					
					m_listboxcomp.AddItem(factoryData.getName() + " - Work In Progress... Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), wipStructure.GetOrigin())) + "m", rplComp);
				}
					
				foreach (RplId ussrStructureRplId : m_baseComp.ussrStructureRplIds)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(ussrStructureRplId));
					IEntity structure = rplComp.GetEntity();
					
					index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(structure.GetPrefabData().GetPrefabName());
					factoryData = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];
					
					int gridX, gridZ;
					SCR_MapEntity.GetGridPos(structure.GetOrigin(), gridX, gridZ);
						
					m_listboxcomp.AddItem(factoryData.getName() + " Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), structure.GetOrigin())) + "m", rplComp);
				}

				break;
			}
			case "US":
			{
				foreach (RplId workerRplId : m_updateWorkersComp.m_usWorkerRplIds)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(workerRplId));
					IEntity worker = rplComp.GetEntity();

					int gridX, gridZ;
					SCR_MapEntity.GetGridPos(worker.GetOrigin(), gridX, gridZ);
					
					m_listboxcomp.AddItem("Worker Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), worker.GetOrigin())) + "m", rplComp);
				}

				foreach (RplId usWIPStructureRplId : m_baseComp.usWIPStructureRplIds)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(usWIPStructureRplId));
					IEntity wipStructure = rplComp.GetEntity();
					
					index = m_gameMode.FactoriesUS.findIndexFromResourcename(wipStructure.GetPrefabData().GetPrefabName());
					factoryData = m_gameMode.FactoriesUS.g_US_Factories[index];

					int gridX, gridZ;
					SCR_MapEntity.GetGridPos(wipStructure.GetOrigin(), gridX, gridZ);
					
					m_listboxcomp.AddItem(factoryData.getName() + " - Work In Progress... Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), wipStructure.GetOrigin())) + "m", rplComp);
				}

				foreach (RplId usStructureRplId : m_baseComp.usStructureRplIds)
				{
					RplComponent rplComp = RplComponent.Cast(Replication.FindItem(usStructureRplId));
					IEntity structure = rplComp.GetEntity();

					index = m_gameMode.FactoriesUS.findIndexFromResourcename(structure.GetPrefabData().GetPrefabName());
					factoryData = m_gameMode.FactoriesUS.g_US_Factories[index];

					int gridX, gridZ;
					SCR_MapEntity.GetGridPos(structure.GetOrigin(), gridX, gridZ);
					
					m_listboxcomp.AddItem(factoryData.getName() + " Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), structure.GetOrigin())) + "m", rplComp);
				}

				break;
			}
		}

		// handlers
		m_commonButtonHandler = new SCR_CTI_CommonButtonHandler();
		m_buttonEventHandler = new SCR_CTI_BaseManagementMenuButtonHandler();
		
		m_demolish.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_demolish.AddHandler(m_buttonEventHandler);
		
		m_disband.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_disband.AddHandler(m_buttonEventHandler);

		m_back.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_back.AddHandler(m_commonButtonHandler);

		m_exit.SetColor(SCR_CTI_Constants.CTI_ORANGE);
		m_exit.AddHandler(m_commonButtonHandler);
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
		GetGame().GetInputManager().AddActionListener("MenuBack", EActionTrigger.DOWN, back);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuClose()
	{
		GetGame().GetInputManager().RemoveActionListener("MenuBack", EActionTrigger.DOWN, back);
	}

	//------------------------------------------------------------------------------------------------
	protected void back()
	{
		auto menuManager = GetGame().GetMenuManager();
		menuManager.CloseAllMenus();

		GetGame().GetMenuManager().OpenMenu(ChimeraMenuPreset.CTI_GUI_MainMenu);
	}

	//------------------------------------------------------------------------------------------------
	override void OnMenuUpdate(float tDelta)
	{
		m_timeDelta += tDelta;
		if (m_timeDelta > TIMESTEP)
		{
			switch (m_factionKey)
			{
				case "USSR":
				{
					// Remove first
					int listboxItemCount = m_listboxcomp.GetItemCount();
					for (int i = 0; i < listboxItemCount; i++)
					{
						RplComponent rplComp = RplComponent.Cast(m_listboxcomp.GetItemData(i));
						RplId rplid = rplComp.Id();
						bool isWorker = false;
						if (rplComp.GetEntity().Type() == SCR_ChimeraCharacter) isWorker = true;
						
						if (isWorker && !m_updateWorkersComp.m_ussrWorkerRplIds.Contains(rplid))
						{
							m_listboxcomp.RemoveItem(i);
							break;
						}
						
						if (!isWorker && !(m_baseComp.ussrWIPStructureRplIds.Contains(rplid) || m_baseComp.ussrStructureRplIds.Contains(rplid)))
						{
							m_listboxcomp.RemoveItem(i);
							break;
						}
					}
					
					// When WIP finished
					listboxItemCount = m_listboxcomp.GetItemCount();
					array<RplId> listboxRplIds = {};
					for (int j = 0; j < listboxItemCount; j++)
					{
						RplComponent rplComp = RplComponent.Cast(m_listboxcomp.GetItemData(j));
						listboxRplIds.Insert(rplComp.Id());
					}
					
					foreach (RplId ussrStructureRplId : m_baseComp.ussrStructureRplIds)
					{
						if (!listboxRplIds.Contains(ussrStructureRplId))
						{
							RplComponent rplComp = RplComponent.Cast(Replication.FindItem(ussrStructureRplId));
							IEntity structure = rplComp.GetEntity();

							int index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(structure.GetPrefabData().GetPrefabName());
							SCR_CTI_FactoryData factdata = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];

							int gridX, gridZ;
							SCR_MapEntity.GetGridPos(structure.GetOrigin(), gridX, gridZ);
							
							m_listboxcomp.AddItem(factdata.getName() + " Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), structure.GetOrigin())) + "m", rplComp);
						}
					}
					
					// TODO if again goes WIP...

					break;
				}
				case "US":
				{
					// Remove first
					int listboxItemCount = m_listboxcomp.GetItemCount();
					for (int i = 0; i < listboxItemCount; i++)
					{
						RplComponent rplComp = RplComponent.Cast(m_listboxcomp.GetItemData(i));
						RplId rplid = rplComp.Id();
						bool isWorker = false;
						if (rplComp.GetEntity().Type() == SCR_ChimeraCharacter) isWorker = true;
						
						if (isWorker && !m_updateWorkersComp.m_usWorkerRplIds.Contains(rplid))
						{
							m_listboxcomp.RemoveItem(i);
							break;
						}
						
						if (!isWorker && !(m_baseComp.usWIPStructureRplIds.Contains(rplid) || m_baseComp.usStructureRplIds.Contains(rplid)))
						{
							m_listboxcomp.RemoveItem(i);
							break;
						}
					}
					
					// When WIP finished
					listboxItemCount = m_listboxcomp.GetItemCount();
					array<RplId> listboxRplIds = {};
					for (int j = 0; j < listboxItemCount; j++)
					{
						RplComponent rplComp = RplComponent.Cast(m_listboxcomp.GetItemData(j));
						listboxRplIds.Insert(rplComp.Id());
					}
					
					foreach (RplId usStructureRplId : m_baseComp.usStructureRplIds)
					{
						if (!listboxRplIds.Contains(usStructureRplId))
						{
							RplComponent rplComp = RplComponent.Cast(Replication.FindItem(usStructureRplId));
							IEntity structure = rplComp.GetEntity();

							int index = m_gameMode.FactoriesUSSR.findIndexFromResourcename(structure.GetPrefabData().GetPrefabName());
							SCR_CTI_FactoryData factdata = m_gameMode.FactoriesUSSR.g_USSR_Factories[index];

							int gridX, gridZ;
							SCR_MapEntity.GetGridPos(structure.GetOrigin(), gridX, gridZ);
							
							m_listboxcomp.AddItem(factdata.getName() + " Grid[" + gridX.ToString() + " " + gridZ.ToString() + "] Distance: " + Math.Round(vector.Distance(m_pc.GetControlledEntity().GetOrigin(), structure.GetOrigin())) + "m", rplComp);
						}
					}
					
					// TODO if again goes WIP...
					
					break;
				}
			}

			m_timeDelta = 0;
		}
	}
};