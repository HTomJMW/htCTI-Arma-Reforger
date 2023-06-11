[EntityEditorProps(category: "GameScripted/CTI", description: "CTI - Modded SCR_VehicleSpawnProtectionComponent.")]
modded class SCR_VehicleSpawnProtectionComponentClass : ScriptComponentClass
{
};

//------------------------------------------------------------------------------------------------
modded class SCR_VehicleSpawnProtectionComponent : SCR_BaseLockComponent
{
	const int NO_OWNER = -1;
	const int NO_TIME_LIMIT = 0;
	
	[RplProp()]
	private int m_iVehicleOwnerID = NO_OWNER;
	
	protected int m_iTimeOfProtection;
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{			
		ClearEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	private void ModdedReleaseProtection()
	{
		RemoveEventHandlers();
		m_iVehicleOwnerID = NO_OWNER;

		Replication.BumpMe();
		
		GetGame().GetCallqueue().Remove(ModdedReleaseProtection);
	}
	
	//------------------------------------------------------------------------------------------------
	override void SetProtectionTime(int protectionTime)
	{
		if (protectionTime != NO_TIME_LIMIT)
		{
			m_iTimeOfProtection = protectionTime;
			GetGame().GetCallqueue().CallLater(ModdedReleaseProtection, m_iTimeOfProtection * 1000, false);
		}		
	}
	
	//------------------------------------------------------------------------------------------------
	override void SetVehicleOwner(int playerID)
	{
		IEntity playerEnt = GetGame().GetPlayerManager().GetPlayerControlledEntity(playerID);
		if (!playerEnt)
			return;
		
		SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		if (gameMode)
			gameMode.GetOnPlayerDisconnected().Insert(OnPlayerDisconected);

		// Set owner of this vehicle
		m_iVehicleOwnerID = playerID;
	
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPlayerDisconected(int playerID)
	{
		if (playerID == m_iVehicleOwnerID)
			ModdedReleaseProtection();
	}

	//------------------------------------------------------------------------------------------------
	override LocalizedString GetReasonText(IEntity user)
	{
		if (!user)
			return string.Empty;

		return "Vehicle Locked!";
	}
	
	//------------------------------------------------------------------------------------------------
	override void RemoveEventHandlers()
	{
		SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		if (gameMode)
			gameMode.GetOnPlayerDisconnected().Remove(OnPlayerDisconected);
	}
};
