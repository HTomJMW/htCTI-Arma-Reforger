enum UpgradeStatus
{
	NONE,
	RUNNING,
	FINISHED
};

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
	protected UpgradeStatus status;

	void setData(string newlabel, string newname, string newdesc, int newlevel, int newcost, string newlink, int newlinklevel, int newtime, UpgradeStatus newstatus)
	{
		label = newlabel;
		name = newname;
		desc = newdesc;
		level = newlevel;
		cost = newcost;
		link = newlink;
		linklevel = newlinklevel;
		time = newtime;
		status = newstatus;
	}

	string getLabel()
	{
		return label;
	}
	
	string getName()
	{
		return name;
	}
	
	string getDesc()
	{
		return desc;
	}

	int getLevel()
	{
		return level;
	}
	
	int getCost()
	{
		return cost;
	}
	
	string getLink()
	{
		return link;
	}
	
	int getLinkLevel()
	{
		return linklevel;
	}

	int getTime()
	{
		return time;
	}
	
	UpgradeStatus getStatus()
	{
		return status;
	}
	
	void setStatus(UpgradeStatus newStatus)
	{
		status = newStatus;
	}

	void SCR_CTI_UpgradeData()
	{
	}
		
	void ~SCR_CTI_UpgradeData()
	{
	}
};

[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Upgrades")]
class SCR_CTI_Upgrades
{
	ref array<ref SCR_CTI_UpgradeData> g_Upgrades = new array<ref SCR_CTI_UpgradeData>;

	private ref array<string>			labels	     = {}; // Label
	private ref array<string>			names		 = {}; // Name
	private ref array<string>			descriptions = {}; // Description
	private ref array<int>				levels		 = {}; // Level
	private ref array<int>				costs		 = {}; // Cost
	private ref array<string> 			links		 = {}; // Dependence
	private ref array<int> 				linklevels	 = {}; // Dependence level 
	private ref array<int> 				times		 = {}; // Time
	private ref array<UpgradeStatus>	statuses	 = {}; // Status

	int findIndexFromName(string name)
	{
		SCR_CTI_UpgradeData upgradeData;
		for (int i = 0; i < g_Upgrades.Count(); i++)
		{
			upgradeData = g_Upgrades[i];
			if (upgradeData.getName() == name) return i;
		}
		
		return -1;
	}
		
	void fillUp()
	{
		// Upgrades
		labels.Insert("Barracks");
		names.Insert("Barracks Level 1");
		descriptions.Insert("Unlock better Infantry Units");
		levels.Insert(1);
		costs.Insert(1000);
		links.Insert("");
		linklevels.Insert(0);
		times.Insert(60);
		statuses.Insert(UpgradeStatus.NONE);
		
		labels.Insert("Barracks");
		names.Insert("Barracks Level 2");
		descriptions.Insert("Unlock better Infantry Units");
		levels.Insert(2);
		costs.Insert(2000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(120);
		statuses.Insert(UpgradeStatus.NONE);
		
		labels.Insert("Light Factory");
		names.Insert("Light Factory level 1");
		descriptions.Insert("Unlock better Light Vehicles");
		levels.Insert(1);
		costs.Insert(2000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(300);
		statuses.Insert(UpgradeStatus.NONE);
		
		labels.Insert("Towns Occupation");
		names.Insert("Towns Occupation Level 1");
		descriptions.Insert("Enable Towns Occupation");
		levels.Insert(1);
		costs.Insert(5000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(500);
		statuses.Insert(UpgradeStatus.NONE);
	}
	
	void init()
	{
		fillUp();
		setUpgrades();
	}

	protected void setUpgrades()
	{
		SCR_CTI_UpgradeData store;
		for (int i = 0; i < labels.Count(); i++)
		{
			store = new SCR_CTI_UpgradeData;
			store.setData(labels[i], names[i], descriptions[i], levels[i], costs[i], links[i], linklevels[i], times[i], statuses[i]);
			
			g_Upgrades.Insert(store);
		}
	}
};