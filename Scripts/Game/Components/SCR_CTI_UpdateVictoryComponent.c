[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Victory")]
class SCR_CTI_UpdateVictoryComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateVictoryComponent : ScriptComponent
{
	protected float m_timeDelta;
	protected const float TIMESTEP = 60;
	
	protected int m_ussrIndex;
	protected int m_usIndex;
	protected FactionManager m_factionmanager;
	protected SCR_CTI_GameMode m_gamemode;
	
	protected IEntity m_ussrMHQ = null;
	protected IEntity m_usMHQ = null;

	//------------------------------------------------------------------------------------------------
	void update()
	{
		if (m_gamemode.IsRunning())
		{
			if (!m_ussrMHQ) m_ussrMHQ = GetGame().GetWorld().FindEntityByName(m_gamemode.USSRMHQNAME);
			if (!m_usMHQ) m_usMHQ = GetGame().GetWorld().FindEntityByName(m_gamemode.USMHQNAME);
			
			SCR_VehicleDamageManagerComponent vdmcUSSR = SCR_VehicleDamageManagerComponent.Cast(m_ussrMHQ.FindComponent(SCR_VehicleDamageManagerComponent));
			SCR_VehicleDamageManagerComponent vdmcUS = SCR_VehicleDamageManagerComponent.Cast(m_usMHQ.FindComponent(SCR_VehicleDamageManagerComponent));
			
			bool ussrMHQdown = vdmcUSSR.IsDestroyed();
			bool usMHQdown = vdmcUS.IsDestroyed();
			
			SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(m_gamemode.FindComponent(SCR_CTI_BaseComponent));
			// NO DRAW?
			if (baseComp.getBaseCount("USSR") == 0 && ussrMHQdown) m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(SCR_GameModeEndData.ENDREASON_EDITOR_FACTION_VICTORY, -1, m_usIndex));
			if (baseComp.getBaseCount("US") == 0 && usMHQdown) m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(SCR_GameModeEndData.ENDREASON_EDITOR_FACTION_VICTORY, -1, m_ussrIndex));
			
			if (m_gamemode.ECOWIN)
			{
				float ussr = 0.0;
				float us = 0.0;
	
				for (int i = 0; i < m_gamemode.CTI_Towns.Count(); i++)
				{
					SCR_CTI_Town town = m_gamemode.CTI_Towns[i];
					if (town.getFactionKey() == "USSR") ussr++;
					if (town.getFactionKey() == "US") us++;
				}

				if (ussr >= (m_gamemode.CTI_Towns.Count() * (m_gamemode.WINRATE / 100)))
				{
					m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(SCR_GameModeEndData.ENDREASON_EDITOR_FACTION_VICTORY, -1, m_ussrIndex));
				}
				
				if (us >= (m_gamemode.CTI_Towns.Count() * (m_gamemode.WINRATE / 100)))
				{
					m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(SCR_GameModeEndData.ENDREASON_EDITOR_FACTION_VICTORY, -1, m_usIndex));
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_factionmanager = GetGame().GetFactionManager();
		m_ussrIndex = m_factionmanager.GetFactionIndex(m_factionmanager.GetFactionByKey("USSR"));
		m_usIndex = m_factionmanager.GetFactionIndex(m_factionmanager.GetFactionByKey("US"));
		m_gamemode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		
		m_timeDelta = 0;
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				update();
				m_timeDelta = 0;
			}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateVictoryComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateVictoryComponent()
	{
	}	
};