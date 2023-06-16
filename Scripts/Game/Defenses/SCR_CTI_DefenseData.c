[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Defense Data Structure")]
class SCR_CTI_DefenseData
{
	protected ResourceName resname;	// Resource name
	protected string name;			// Display name
	protected int price;			// Price
	protected string category;		// Category
	protected int distance;			// Distance
	protected int placement;		// Placement
	protected string script;		// Script

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newresname, string newname, int newprice, string newcategory, int newdistance, int newplacement, string newscript)
	{
		resname = newresname;
		name = newname;
		price = newprice;
		category = newcategory;
		distance = newdistance;
		placement = newplacement;
		script = newscript;
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
	int getPrice()
	{
		return price;
	}

	//------------------------------------------------------------------------------------------------
	int getCategory()
	{
		return category;
	}

	//------------------------------------------------------------------------------------------------
	int getDistance()
	{
		return distance;
	}

	//------------------------------------------------------------------------------------------------
	int getPlacement()
	{
		return placement;
	}

	//------------------------------------------------------------------------------------------------
	string getScript()
	{
		return script;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_DefenseData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_DefenseData()
	{
	}
};