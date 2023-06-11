[EntityEditorProps(category: "GameScripted/CTI", description: "Lock and Unlock Vehicle User Action")]
class SCR_CTI_LockAndUnlockVehicleAction : ScriptedUserAction
{
	protected IEntity m_vehicle;
	protected SCR_VehicleSpawnProtectionComponent m_vehSpawnProtectionComp;
	protected SCR_BaseCompartmentManagerComponent m_baseCompoartmentManagerComp;
	protected SCR_BaseLockComponent m_baseLockComp;
	protected RplComponent m_rplComponent;

	//------------------------------------------------------------------------------------------------
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_vehicle = IEntity.Cast(pOwnerEntity);
		m_vehSpawnProtectionComp = SCR_VehicleSpawnProtectionComponent.Cast(pOwnerEntity.FindComponent(SCR_VehicleSpawnProtectionComponent));
		m_baseCompoartmentManagerComp = SCR_BaseCompartmentManagerComponent.Cast(pOwnerEntity.FindComponent(SCR_BaseCompartmentManagerComponent));
		m_baseLockComp = SCR_BaseLockComponent.Cast(pOwnerEntity.FindComponent(SCR_BaseLockComponent));
		m_rplComponent = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{
		if (m_rplComponent && m_rplComponent.IsProxy()) return;

		int userId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(pUserEntity);
		if (m_vehSpawnProtectionComp && m_vehSpawnProtectionComp.GetVehicleOwner() == userId)
		{
			if (m_baseLockComp)
			{
				if (m_baseLockComp.vehicleIsLocked())
				{
					m_baseLockComp.lockVehicle(false);
				} else {
					m_baseLockComp.lockVehicle(true);
				}
			}
		} 
	}

	//------------------------------------------------------------------------------------------------
	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBePerformedScript(IEntity user)
	{
		array<IEntity> occupants = {};
		m_baseCompoartmentManagerComp.GetOccupants(occupants);

		// TODO Check AI or Player
		if (!occupants.IsEmpty())
		{
			SetCannotPerformReason("Vehicle occupied!");
			return false;
		}

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool CanBeShownScript(IEntity user)
	{
		// TODO Commander open all vehicles	
		int userId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(user);
		int ownerId = m_vehSpawnProtectionComp.GetVehicleOwner();
		if (m_vehSpawnProtectionComp.GetVehicleOwner() != userId) return false;

		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool GetActionNameScript(out string outName)
	{
		outName = "";

		if (m_baseLockComp)
		{
			if (m_baseLockComp.vehicleIsLocked())
			{
				outName = "UnLock Vehicle";
			} else {
				outName = "Lock Vehicle";
			}
		}
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_LockAndUnlockVehicleAction()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_LockAndUnlockVehicleAction()
	{
	}
};