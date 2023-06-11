[EntityEditorProps(category: "GameScripted/CTI", description: "CTI - Modded SCR_BaseLockComponent.")]
modded class SCR_BaseLockComponentClass : ScriptComponentClass
{
};

//------------------------------------------------------------------------------------------------
modded class SCR_BaseLockComponent : ScriptComponent
{
	[RplProp()]
	protected bool m_isLocked = false;

	private SCR_VehicleSpawnProtectionComponent m_pVehicleSpawnProtection

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		m_pVehicleSpawnProtection = SCR_VehicleSpawnProtectionComponent.Cast(owner.FindComponent(SCR_VehicleSpawnProtectionComponent));
		ClearEventMask(owner, EntityEvent.INIT);
	}
	
	//------------------------------------------------------------------------------------------------
	bool vehicleIsLocked()
	{
		return m_isLocked;
	}
	
	//------------------------------------------------------------------------------------------------
	void lockVehicle(bool lock)
	{
		m_isLocked = lock;
		
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	override LocalizedString GetCannotPerformReason(IEntity user)
	{
		return "Vehicle Locked!";
	}

	//------------------------------------------------------------------------------------------------
	override bool IsLocked(IEntity user, BaseCompartmentSlot compartmentSlot)
	{
		if (!user || !compartmentSlot)
			return false;

		if (m_pVehicleSpawnProtection && m_pVehicleSpawnProtection.GetVehicleOwner() == -1) return false;
	
		if (m_isLocked) return true;
		
		return false;
	}
};