class SCR_CTI_RandomDir
{
	//------------------------------------------------------------------------------------------------
	static vector getRandomDir()
	{
		RandomGenerator randomGen = new RandomGenerator();
		
		vector vec;
		vec[0] = randomGen.RandFloatXY(-1, 1);
		vec[1] = 0.0;
		vec[2] = randomGen.RandFloatXY(-1, 1);

		return vec;
	}
};