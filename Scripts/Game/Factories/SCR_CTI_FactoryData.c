[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Factory Data Structure")]
class SCR_CTI_FactoryData
{
	protected ResourceName m_resname;	// Resource name
	protected ResourceName m_wipname;	// WIP resource name
	protected string m_name;			// Display name
	protected int m_price;				// Price
	protected int m_buildtime;			// Build time
	protected int m_distance;			// Distance
	protected int m_placement;			// Placement degree
	protected string m_script;			// Script

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newresname, ResourceName newwipname, string newname, int newprice, int newbuildtime, int newdistance, int newplacement, string newscript)
	{
		m_resname = newresname;
		m_wipname = newwipname;
		m_name = newname;
		m_price = newprice;
		m_buildtime = newbuildtime;
		m_distance = newdistance;
		m_placement = newplacement;
		m_script = newscript;
	}

	//------------------------------------------------------------------------------------------------
	ResourceName getResName()
	{
		return m_resname;
	}

	//------------------------------------------------------------------------------------------------
	ResourceName getWIPName()
	{
		return m_wipname;
	}

	//------------------------------------------------------------------------------------------------
	string getName()
	{
		return m_name;
	}

	//------------------------------------------------------------------------------------------------
	int getPrice()
	{
		return m_price;
	}

	//------------------------------------------------------------------------------------------------
	int getBuildtime()
	{
		return m_buildtime;
	}

	//------------------------------------------------------------------------------------------------
	int getDistance()
	{
		return m_distance;
	}

	//------------------------------------------------------------------------------------------------
	int getPlacement()
	{
		return m_placement;
	}

	//------------------------------------------------------------------------------------------------
	string getScript()
	{
		return m_script;
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