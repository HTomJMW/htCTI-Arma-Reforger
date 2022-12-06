[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Unit Data Structure")]
class SCR_CTI_UnitData
{
	protected ResourceName resname; // Resource name
	protected string picture;		// Picture name
	protected string name;			// Display name
	protected int price;			// Price
	protected int buildtime;		// Build time
	protected int uplevel;			// Upgrade level
	protected string factory;		// Factory
	protected string script;		// Script

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newresname, string newpicture, string newname, int newprice, int newbuildtime, int newuplevel, string newfactory, string newscript)
	{
		resname = newresname;
		picture = newpicture;
		name = newname;
		price = newprice;
		buildtime = newbuildtime;
		uplevel = newuplevel;
		factory = newfactory;
		script = newscript;
	}

	//------------------------------------------------------------------------------------------------
	ResourceName getResname()
	{
		return resname;
	}

	//------------------------------------------------------------------------------------------------
	string getPicture()
	{
		return picture;
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
	int getBuildtime()
	{
		return buildtime;
	}

	//------------------------------------------------------------------------------------------------
	int getUplevel()
	{
		return uplevel;
	}

	//------------------------------------------------------------------------------------------------
	string getFactory()
	{
		return factory;
	}

	//------------------------------------------------------------------------------------------------
	string getScript()
	{
		return script;
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