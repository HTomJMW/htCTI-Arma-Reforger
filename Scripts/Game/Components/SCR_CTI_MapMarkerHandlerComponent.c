[EntityEditorProps(category: "GameScripted/CTI", description: "Handles Map Markers.")]
class SCR_CTI_MapMarkerHandlerComponentClass: ScriptComponentClass
{
};

class SCR_CTI_MapMarkerHandlerComponent : ScriptComponent
{
	protected SCR_PlayerController m_playerController;
	protected SCR_MapEntity m_mapEntity;
	protected RplComponent m_rplComponent;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected float m_zoomValue;

	//------------------------------------------------------------------------------------------------
	protected bool IsProxy()
	{
		return (m_rplComponent && m_rplComponent.IsProxy());
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_playerController = SCR_PlayerController.Cast(PlayerController.Cast(owner));
		
		if (!m_playerController)
		{
			Print("CTI :: SCR_CTI_MapMarkerHandlerComponent must be attached to PlayerController!", LogLevel.ERROR);
			return;
		}
		
		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
		owner.SetFlags(EntityFlags.ACTIVE, true);
		
		m_mapEntity = SCR_MapEntity.GetMapInstance();

		m_mapEntity.GetOnMapOpen().Insert(OnPlayerMapOpen);
		m_mapEntity.GetOnMapZoom().Insert(OnPlayerMapZoom);
		m_mapEntity.GetOnMapClose().Insert(OnPlayerMapClose);
	}
	
	//------------------------------------------------------------------------------------------------
	protected void OnPlayerMapOpen()
	{
		m_zoomValue = m_mapEntity.GetCurrentZoom();
	}

	//------------------------------------------------------------------------------------------------
	protected void OnPlayerMapZoom()
	{
		float currentZoom = m_mapEntity.GetCurrentZoom(); // 0.0-20.0 ZOOM
		PrintFormat("MAP :: CurrentZoom: %1", currentZoom);

		foreach (SCR_CTI_Town town : m_gameMode.CTI_Towns)
		{
			SCR_CTI_TownMapDescriptorComponent townMDC = SCR_CTI_TownMapDescriptorComponent.Cast(town.FindComponent(SCR_CTI_TownMapDescriptorComponent));
			MapItem item = townMDC.Item();
			if (item)
			{
				MapDescriptorProps props = item.GetProps();
					props.SetIconSize(512, -currentZoom, -currentZoom);
					//props.SetTextSize(32, 16, 64);
			
				item.SetProps(props);
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void OnPlayerMapClose()
	{
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_MapMarkerHandlerComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_MapMarkerHandlerComponent()
	{
		m_mapEntity.GetOnMapOpen().Remove(OnPlayerMapOpen);
		m_mapEntity.GetOnMapZoom().Remove(OnPlayerMapZoom);
		m_mapEntity.GetOnMapClose().Remove(OnPlayerMapClose);
	}
};