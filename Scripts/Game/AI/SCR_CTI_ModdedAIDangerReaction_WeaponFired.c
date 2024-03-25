// CTI modded AI danger reaction for unarmed Workers
modded class SCR_AIDangerReaction_WeaponFired : SCR_AIDangerReaction
{
	override bool PerformReaction(notnull SCR_AIUtilityComponent utility, notnull SCR_AIThreatSystem threatSystem, AIDangerEvent dangerEvent)
	{
		// Skip gunshot investigate reaction for CTI Workers
		if (utility.m_OwnerEntity.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.USSR_WORKER || utility.m_OwnerEntity.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.US_WORKER)
			return false;
		
		return super.PerformReaction(utility, threatSystem, dangerEvent);
	}
};