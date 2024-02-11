// CTI modded AI danger reaction for unarmed Workers
[BaseContainerProps()]
modded class SCR_AIDangerReaction_WeaponFired : SCR_AIDangerReaction
{
	override bool PerformReaction(notnull SCR_AIUtilityComponent utility, notnull SCR_AIThreatSystem threatSystem, AIDangerEvent dangerEvent)
	{
		IEntity shooter = dangerEvent.GetObject();
		
		if (!shooter)
			return false;
		
		// Get root entity of shooter, in case it is turret in vehicle hierarchy
		shooter = shooter.GetRootParent();
		
		SCR_ChimeraAIAgent agent = SCR_ChimeraAIAgent.Cast(utility.GetOwner());
		if (!agent || !agent.IsEnemy(shooter))
			return false;
		
		vector min, max;
		shooter.GetBounds(min, max);
		vector lookPosition = shooter.GetOrigin() + (min + max) * 0.5;
		vector myOrigin = utility.m_OwnerEntity.GetOrigin();
		
		float distance = vector.Distance(lookPosition, utility.GetOrigin());
		
		threatSystem.ThreatShotFired(distance, dangerEvent.GetCount());

		// Look at shooting position. Even though we add an observe behavior, we can't guarantee that
		// some other behavior doesn't override observe behavior, in which case we might want to look at shooter in parallel.
		utility.m_LookAction.LookAt(lookPosition, utility.m_LookAction.PRIO_DANGER_EVENT, 3.0);

		// Skip gunshot investigate reaction for CTI Workers
		if (utility.m_OwnerEntity.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.USSR_WORKER || utility.m_OwnerEntity.GetPrefabData().GetPrefabName() == SCR_CTI_Constants.US_WORKER)
			return false;

		// Notify our group
		// ! Only if we are a leader
		AIGroup myGroup = AIGroup.Cast(utility.GetOwner().GetParentGroup());
		if (myGroup && myGroup.GetLeaderAgent() == agent)
			NotifyGroup(myGroup, shooter, lookPosition);
		
		// Ignore if we have selected a target
		// Ignore if target is too far
		if (utility.m_CombatComponent.GetCurrentTarget() != null ||
			distance > AI_WEAPONFIRED_REACTION_DISTANCE)
			return false;
		
		// Check if we must dismount the turret
		vector turretDismountCheckPosition = lookPosition;
		bool mustDismountTurret = utility.m_CombatComponent.DismountTurretCondition(turretDismountCheckPosition, true);
		if (mustDismountTurret)
		{
			utility.m_CombatComponent.TryAddDismountTurretActions(turretDismountCheckPosition);
		}
		
		// Stare at gunshot origin
		bool addObserveBehavior = false;
		SCR_AIMoveAndInvestigateBehavior investigateBehavior = SCR_AIMoveAndInvestigateBehavior.Cast(utility.FindActionOfType(SCR_AIMoveAndInvestigateBehavior));
		SCR_AIObserveUnknownFireBehavior oldObserveBehavior = SCR_AIObserveUnknownFireBehavior.Cast(utility.FindActionOfType(SCR_AIObserveUnknownFireBehavior));
		if (investigateBehavior && investigateBehavior.GetActionState() == EAIActionState.RUNNING)
		{
			if (SCR_AIObserveUnknownFireBehavior.IsNewPositionMoreRelevant(myOrigin, investigateBehavior.m_vPosition.m_Value, lookPosition))
				addObserveBehavior = true;
		}
		else if (oldObserveBehavior)
		{
			if (SCR_AIObserveUnknownFireBehavior.IsNewPositionMoreRelevant(myOrigin, oldObserveBehavior.m_vPosition.m_Value, lookPosition))
				addObserveBehavior = true;
		}
		else if (!oldObserveBehavior)
			addObserveBehavior = true;
			
		if (addObserveBehavior)
		{
			// !!! It's important that priority of this is higher than priority of move and investigate,
			// !!! So first we look at gunshot origin, then investigate it
			SCR_AIObservePositionBehavior observeBehavior = new SCR_AIObserveUnknownFireBehavior(utility, null,	posWorld: lookPosition);
			utility.AddAction(observeBehavior);
		}
		
		return true;
	}
};
