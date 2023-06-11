[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI MHQ Lock.")]
class SCR_CTI_MHQLockComponentClass : SCR_BaseLockComponentClass
{
};

class SCR_CTI_MHQLockComponent : SCR_BaseLockComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_VehicleSpawnProtectionComponent m_vehSpawnProtection;
	protected SCR_VehicleFactionAffiliationComponent m_vehFactionAffComp;
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		ClearEventMask(owner, EntityEvent.INIT);

		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);

		m_vehFactionAffComp = SCR_VehicleFactionAffiliationComponent.Cast(owner.FindComponent(SCR_VehicleFactionAffiliationComponent));
		m_vehSpawnProtection = SCR_VehicleSpawnProtectionComponent.Cast(owner.FindComponent(SCR_VehicleSpawnProtectionComponent));
		m_vehSpawnProtection.SetVehicleOwner(-2);
		m_vehSpawnProtection.SetProtectionTime(0); // unlimited protection time
	}
	
	//------------------------------------------------------------------------------------------------
	override LocalizedString GetCannotPerformReason(IEntity user)
	{
		return "Only for Commander!";
	}
	
	//------------------------------------------------------------------------------------------------
	override bool IsLocked(IEntity user, BaseCompartmentSlot compartmentSlot)
	{
		if (super.IsLocked(user, compartmentSlot))
			return true;

		SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(user);
		Faction characterFaction = character.GetFaction();
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(user);
		if (playerId != m_gameMode.getCommanderId(characterFaction.GetFactionKey()) /*&& compartmentSlot.Type() == PilotCompartmentSlot*/)
		{
			return true;
		}
		
		return false;
	}
};