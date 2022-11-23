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

	//------------------------------------------------------------------------------------------------
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

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Upgrades
		labels.Insert("Gear");
		names.Insert("Gear Level 1");
		descriptions.Insert("Unlock better Gear");
		levels.Insert(1);
		costs.Insert(1000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(60);
		
		labels.Insert("Gear");
		names.Insert("Gear Level 2");
		descriptions.Insert("Unlock better Gear");
		levels.Insert(2);
		costs.Insert(2000);
		links.Insert("None");
		linklevels.Insert(1);
		times.Insert(120);
		
		labels.Insert("Barracks");
		names.Insert("Barracks Level 1");
		descriptions.Insert("Unlock better Infantry Units");
		levels.Insert(1);
		costs.Insert(1000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(60);
		
		labels.Insert("Barracks");
		names.Insert("Barracks Level 2");
		descriptions.Insert("Unlock better Infantry Units");
		levels.Insert(2);
		costs.Insert(2000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(120);
		
		labels.Insert("Light Factory");
		names.Insert("Light Factory level 1");
		descriptions.Insert("Unlock better Light Vehicles");
		levels.Insert(1);
		costs.Insert(2000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(300);
		
		labels.Insert("Towns Occupation");
		names.Insert("Towns Occupation Level 1");
		descriptions.Insert("Enable Towns Occupation");
		levels.Insert(1);
		costs.Insert(5000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(500);
	}

	//------------------------------------------------------------------------------------------------
	private void setUpgrades()
	{
		SCR_CTI_UpgradeData store;
		for (int i = 0; i < labels.Count(); i++)
		{
			store = new SCR_CTI_UpgradeData;
			store.setData(labels[i], names[i], descriptions[i], levels[i], costs[i], links[i], linklevels[i], times[i]);
			
			g_Upgrades.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_Upgrades()
	{
		fillUp();
		setUpgrades();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_Upgrades()
	{
		g_Upgrades.Clear();
		g_Upgrades = null;
	}
};