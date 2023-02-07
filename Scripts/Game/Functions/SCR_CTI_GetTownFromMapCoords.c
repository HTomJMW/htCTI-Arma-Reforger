class SCR_CTI_GetTownFromMapCoords
{
	//------------------------------------------------------------------------------------------------
	static SCR_CTI_Town GetTownFromMapCoords(vector worldPos, notnull array<SCR_CTI_Town> towns)
	{
		SCR_CTI_Town closest = null;
		float dist = 100000;
		
		foreach (SCR_CTI_Town town : towns)
		{
			float distance = vector.Distance(worldPos, town.GetOrigin());
			if (distance < dist)
			{
				closest = town;
				dist = distance;
			}
		}
		
		return closest;
	}
};