[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Gear Data Structure")]
class SCR_CTI_GearData
{
	protected ResourceName res;	// Resource name
	protected string name;		// Display name
	protected int ul;			// Upgrade level
	protected int pri;			// Price

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newres, string newname, int newul, int newpri)
	{
		res = newres;
		name = newname;
		ul = newul;
		pri = newpri;
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
	int getUl()
	{
		return ul;
	}

	//------------------------------------------------------------------------------------------------
	int getPri()
	{
		return pri;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_GearData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GearData()
	{
	}
};