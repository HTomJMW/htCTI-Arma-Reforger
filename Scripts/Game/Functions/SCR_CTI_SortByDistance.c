class SCR_CTI_SortByDistance
{
	static array<IEntity> SortByDistance(notnull IEntity object, notnull array<IEntity> source)
	{
		array<IEntity> sorted = {};

		for (int i = source.Count() - 1; i >= 0; i--)
		{
			IEntity closest = null;
			closest = SCR_CTI_GetClosestEntity.GetClosestEntity(object, source);
			if (closest)
			{
				sorted.Insert(closest);
				source.Remove(source.Find(closest));
			}
		}

		return sorted;
	}
};