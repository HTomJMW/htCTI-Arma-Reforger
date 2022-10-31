[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Unit Data Structure")]
class SCR_CTI_UnitData
{
	protected ResourceName res; // Resource name
	protected string pic;		// Picture name
	protected string name;		// Display name
	protected int pri;			// Price
	protected int bt;			// Build time
	protected int ul;			// Upgrade level
	protected string fac;		// Factory
	protected string scr;		// Script

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newres, string newpic, string newname, int newpri, int newbt, int newul, string newfac, string newscr)
	{
		res = newres;
		pic = newpic;
		name = newname;
		pri = newpri;
		bt = newbt;
		ul = newul;
		fac = newfac;
		scr = newscr;
	}

	//------------------------------------------------------------------------------------------------
	ResourceName getRes()
	{
		return res;
	}

	//------------------------------------------------------------------------------------------------
	string getPic()
	{
		return pic;
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
	int getUl()
	{
		return ul;
	}

	//------------------------------------------------------------------------------------------------
	string getFac()
	{
		return fac;
	}

	//------------------------------------------------------------------------------------------------
	string getScr()
	{
		return scr;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UnitData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UnitData()
	{
	}
};