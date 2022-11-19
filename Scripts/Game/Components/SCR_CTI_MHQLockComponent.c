[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI MHQ Lock.")]
class SCR_CTI_MHQLockComponentClass : SCR_BaseLockComponentClass
{
};

class SCR_CTI_MHQLockComponent : SCR_BaseLockComponent
{
	protected SCR_CTI_GameMode gameMode;
	protected SCR_VehicleSpawnProtectionComponent vehSpawnProtection;
	protected SCR_VehicleFactionAffiliationComponent vehFactionAffComp;
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
		ClearEventMask(owner, EntityEvent.INIT);
		
		gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);

		vehFactionAffComp = SCR_VehicleFactionAffiliationComponent.Cast(owner.FindComponent(SCR_VehicleFactionAffiliationComponent));
		vehSpawnProtection = SCR_VehicleSpawnProtectionComponent.Cast(owner.FindComponent(SCR_VehicleSpawnProtectionComponent));
		vehSpawnProtection.SetVehicleOwner(-2);
		vehSpawnProtection.SetProtectionTime(0); // unlimited protection time
	}
	
	//------------------------------------------------------------------------------------------------
	override LocalizedString GetCannotPerformReason(IEntity user)
	{
		return "Only for Commander";
	}
	
	//------------------------------------------------------------------------------------------------
	override bool IsLocked(IEntity user, BaseCompartmentSlot compartmentSlot)
	{
		if (super.IsLocked(user, compartmentSlot))
			return true;

		SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(user);
		Faction characterFaction = character.GetFaction();
		int playerId = GetGame().GetPlayerManager().GetPlayerIdFromControlledEntity(user);
		if (playerId != gameMode.getCommanderId(characterFaction.GetFactionKey()))
		{
			return true;
		}
		
		return false;
	}
};