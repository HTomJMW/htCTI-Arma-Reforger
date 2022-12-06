class SCR_CTI_GetClosestEntity
{
	static IEntity GetClosestEntity(notnull IEntity entity, notnull array<IEntity> dynamicArrayOfEntities)
	{
		IEntity closest = null;
		float dist = 100000;
		
		foreach (IEntity ent : dynamicArrayOfEntities)
		{
			float distance = vector.Distance(entity.GetOrigin(), ent.GetOrigin());
			if (distance < dist)
			{
				closest = ent;
				dist = distance;
			}
		}
		
		return closest;
	}

	static IEntity GetClosestEntity(notnull IEntity entity, notnull IEntity staticArrayOfEntities[])
	{
		IEntity closest = null;
		float dist = 100000;
		
		foreach (IEntity ent : staticArrayOfEntities)
		{
			float distance = vector.Distance(entity.GetOrigin(), ent.GetOrigin());
			if (distance < dist)
			{
				closest = ent;
				dist = distance;
			}
		}
		
		return closest;
	}
};