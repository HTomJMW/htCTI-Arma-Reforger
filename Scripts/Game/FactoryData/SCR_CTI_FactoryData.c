[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Factory Data Structure")]
class SCR_CTI_FactoryData
{
	protected ResourceName res;	// Resource name
	protected string name;		// Display name
	protected int pri;			// Price
	protected int bt;			// Build time
	protected int dis;			// Distance
	protected int pla;			// Placement degree
	protected string scr;		// Script

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newres, string newname, int newpri, int newbt, int newdis, int newpla, string newscr)
	{
		res = newres;
		name = newname;
		pri = newpri;
		bt = newbt;
		dis = newdis;
		pla = newpla;
		scr = newscr;
	}

	//------------------------------------------------------------------------------------------------
	ResourceName getRes()
	{
		return res;
	}

	//------------------------------------------------------------------------------------------------
	string getName()
	{
		return name;
	}

	//------------------------------------------------------------------------------------------------
	int getPri()
	{
		return pri;
	}

	//------------------------------------------------------------------------------------------------
	int getBt()
	{
		return bt;
	}

	//------------------------------------------------------------------------------------------------
	int getDis()
	{
		return dis;
	}

	//------------------------------------------------------------------------------------------------
	int getPla()
	{
		return pla;
	}

	//------------------------------------------------------------------------------------------------
	string getScr()
	{
		return scr;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_FactoryData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_FactoryData()
	{
	}
};