[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Gear Data Structure")]
class SCR_CTI_GearData
{
	protected ResourceName resname;	// Resource name
	protected string name;			// Display name
	protected string category;		// Category
	protected int uplevel;			// Upgrade level
	protected int price;			// Price

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newresname, string newname, string newcategory, int newuplevel, int newprice)
	{
		resname = newresname;
		name = newname;
		category = newcategory;
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
	string getCategory()
	{
		return category;
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