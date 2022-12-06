[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Upgrade Data Structure")]
class SCR_CTI_UpgradeData
{
	protected string label;		// Label
	protected string name;		// Name
	protected string desc;		// Description
	protected int level;		// Level
	protected int cost;			// Cost
	protected string link;		// Link
	protected int linklevel;	// Link Level
	protected int time;			// Time

	//------------------------------------------------------------------------------------------------
	void setData(string newlabel, string newname, string newdesc, int newlevel, int newcost, string newlink, int newlinklevel, int newtime)
	{
		label = newlabel;
		name = newname;
		desc = newdesc;
		level = newlevel;
		cost = newcost;
		link = newlink;
		linklevel = newlinklevel;
		time = newtime;
	}

	//------------------------------------------------------------------------------------------------
	string getLabel()
	{
		return label;
	}

	//------------------------------------------------------------------------------------------------
	string getName()
	{
		return name;
	}

	//------------------------------------------------------------------------------------------------
	string getDesc()
	{
		return desc;
	}

	//------------------------------------------------------------------------------------------------
	int getLevel()
	{
		return level;
	}

	//------------------------------------------------------------------------------------------------
	int getCost()
	{
		return cost;
	}

	//------------------------------------------------------------------------------------------------
	string getLink()
	{
		return link;
	}

	//------------------------------------------------------------------------------------------------
	int getLinkLevel()
	{
		return linklevel;
	}

	//------------------------------------------------------------------------------------------------
	int getTime()
	{
		return time;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpgradeData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpgradeData()
	{
	}
};