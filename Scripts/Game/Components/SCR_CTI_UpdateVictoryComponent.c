[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Victory")]
class SCR_CTI_UpdateVictoryComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateVictoryComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gamemode;

	//------------------------------------------------------------------------------------------------
	void update()
	{
		if (m_gamemode.IsRunning())
		{
			FactionManager factionmanager = GetGame().GetFactionManager();
			int ussrIndex = factionmanager.GetFactionIndex(factionmanager.GetFactionByKey("USSR"));
			int usIndex = factionmanager.GetFactionIndex(factionmanager.GetFactionByKey("US"));
			
			IEntity m_ussrMHQ = SCR_CTI_GetSideMHQ.GetSideMHQ("USSR");
			IEntity m_usMHQ = SCR_CTI_GetSideMHQ.GetSideMHQ("US");
			
			SCR_VehicleDamageManagerComponent vdmcUSSR = SCR_VehicleDamageManagerComponent.Cast(m_ussrMHQ.FindComponent(SCR_VehicleDamageManagerComponent));
			SCR_VehicleDamageManagerComponent vdmcUS = SCR_VehicleDamageManagerComponent.Cast(m_usMHQ.FindComponent(SCR_VehicleDamageManagerComponent));
			
			bool ussrMHQdown = false;
			if (vdmcUSSR) ussrMHQdown = vdmcUSSR.IsDestroyed();
			bool usMHQdown = false;
			if (vdmcUS) usMHQdown = vdmcUS.IsDestroyed();

			SCR_CTI_BaseComponent baseComp = SCR_CTI_BaseComponent.Cast(m_gamemode.FindComponent(SCR_CTI_BaseComponent));
			// NO DRAW? need add draw for rarely case
			if (baseComp.getBaseCount("USSR") == 0 && ussrMHQdown) m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(EGameOverTypes.ENDREASON_SCORELIMIT, -1, usIndex));
			if (baseComp.getBaseCount("US") == 0 && usMHQdown) m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(EGameOverTypes.ENDREASON_SCORELIMIT, -1, ussrIndex));

			if (SCR_CTI_Constants.ECOWIN)
			{
				float ussr = 0.0;
				float us = 0.0;

				for (int i = 0; i < m_gamemode.CTI_Towns.Count(); i++)
				{
					SCR_CTI_Town town = m_gamemode.CTI_Towns[i];
					if (town.getFactionKey() == "USSR") ussr++;
					if (town.getFactionKey() == "US") us++;
				}

				if (ussr >= (m_gamemode.CTI_Towns.Count() * (SCR_CTI_Constants.WINRATE / 100)))
				{
					m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(EGameOverTypes.ENDREASON_SCORELIMIT, -1, ussrIndex));
				}

				if (us >= (m_gamemode.CTI_Towns.Count() * (SCR_CTI_Constants.WINRATE / 100)))
				{
					m_gamemode.EndGameMode(SCR_GameModeEndData.CreateSimple(EGameOverTypes.ENDREASON_SCORELIMIT, -1, usIndex));
				}
			}

			// Temporary GM FIX for MHQ Lifetime problem (GETIN event enables GM)
			ChimeraWorld world = m_ussrMHQ.GetWorld();
			GarbageManager garbagemanager = world.GetGarbageManager();
			
			garbagemanager.Withdraw(m_ussrMHQ);
			garbagemanager.Withdraw(m_usMHQ);
			
			//PrintFormat("CTI :: DEBUG :: USSR mhq lifetime: %1s", garbagemanager.GetRemainingLifetime(m_ussrMHQ));
			//PrintFormat("CTI :: DEBUG :: US mhq lifetime: %1s", garbagemanager.GetRemainingLifetime(m_usMHQ));
		}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{	
		GetGame().GetCallqueue().CallLater(update, 60 * 1000, true);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateVictoryComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gamemode = SCR_CTI_GameMode.Cast(ent);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateVictoryComponent()
	{
	}	
};