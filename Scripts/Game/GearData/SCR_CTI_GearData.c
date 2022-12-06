[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Gear Data Structure")]
class SCR_CTI_GearData
{
	protected ResourceName resname;	// Resource name
	protected string name;			// Display name
	protected int uplevel;			// Upgrade level
	protected int price;			// Price

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newresname, string newname, int newuplevel, int newprice)
	{
		resname = newresname;
		name = newname;
		uplevel = newuplevel;
		price = newprice;
	}

	//------------------------------------------------------------------------------------------------
	ResourceName getResname()
	{
		return resname;
	}

	//------------------------------------------------------------------------------------------------
	string getName()
	{
		return name;
	}
	
	//------------------------------------------------------------------------------------------------
	int getUplevel()
	{
		return uplevel;
	}

	//------------------------------------------------------------------------------------------------
	int getPrice()
	{
		return price;
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