class SCR_CTI_TerrainIsFlat
{
	//------------------------------------------------------------------------------------------------
	static bool isFlat(vector center, float radius, float maxDifference = 0.25)
	{
		float height = center[1];

		// step 1
		float checkPoint = center[0] + radius;
		float checkPointHeight = GetGame().GetWorld().GetSurfaceY(checkPoint, center[2]);
		
		if (checkPointHeight > height + maxDifference || checkPointHeight < height - maxDifference) return false;

		// step 2
		checkPoint = center[0] - radius;
		checkPointHeight = GetGame().GetWorld().GetSurfaceY(checkPoint, center[2]);
		
		if (checkPointHeight > height + maxDifference || checkPointHeight < height - maxDifference) return false;

		// step 3
		checkPoint = center[2] + radius;
		checkPointHeight = GetGame().GetWorld().GetSurfaceY(center[0], checkPoint);
		
		if (checkPointHeight > height + maxDifference || checkPointHeight < height - maxDifference) return false;
		
		// step 4
		checkPoint = center[2] - radius;
		checkPointHeight = GetGame().GetWorld().GetSurfaceY(center[0], checkPoint);
		
		if (checkPointHeight > height + maxDifference || checkPointHeight < height - maxDifference) return false;

		return true;
	}
};