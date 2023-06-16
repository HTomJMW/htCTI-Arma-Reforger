[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Upgrade Data Structure")]
class SCR_CTI_UpgradeData
{
	protected string label;		// Label
	protected string name;		// Name
	protected string desc;		// Description
	protected int level;		// Level
	protected string history;	// History
	protected int cost;			// Cost
	protected string link;		// Link
	protected string link2;		// Link
	protected int time;			// Time

	//------------------------------------------------------------------------------------------------
	void setData(string newlabel, string newname, string newdesc, int newlevel, string newhistory, int newcost, string newlink, string newlink2, int newtime)
	{
		label = newlabel;
		name = newname;
		desc = newdesc;
		level = newlevel;
		history = newhistory;
		cost = newcost;
		link = newlink;
		link2 = newlink2;
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
	string getHistrory()
	{
		return history;
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
	string getLink2()
	{
		return link2;
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