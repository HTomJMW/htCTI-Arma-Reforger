[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Upgrade Data Structure")]
class SCR_CTI_UpgradeData
{
	protected string label;
	protected string name;
	protected string desc;
	protected int level;
	protected int cost;
	protected string link;
	protected int linklevel;
	protected int time;

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