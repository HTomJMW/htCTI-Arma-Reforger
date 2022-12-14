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
		descriptions.Insert("Unlocks better Gear");
		levels.Insert(1);
		costs.Insert(1000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(60);
		
		labels.Insert("Gear");
		names.Insert("Gear Level 2");
		descriptions.Insert("Unlocks better Gear");
		levels.Insert(2);
		costs.Insert(2000);
		links.Insert("Gear Level 1");
		linklevels.Insert(1);
		times.Insert(120);
		
		labels.Insert("Gear");
		names.Insert("Gear Level 3");
		descriptions.Insert("Unlocks better Gear");
		levels.Insert(3);
		costs.Insert(4000);
		links.Insert("Gear Level 2");
		linklevels.Insert(2);
		times.Insert(180);
		
		labels.Insert("Barracks");
		names.Insert("Barracks Level 1");
		descriptions.Insert("Unlocks better Infantry Units");
		levels.Insert(1);
		costs.Insert(1000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(60);
		
		labels.Insert("Barracks");
		names.Insert("Barracks Level 2");
		descriptions.Insert("Unlocks better Infantry Units");
		levels.Insert(2);
		costs.Insert(2000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(120);
		
		labels.Insert("Barracks");
		names.Insert("Barracks Level 3");
		descriptions.Insert("Unlocks better Infantry Units");
		levels.Insert(3);
		costs.Insert(4000);
		links.Insert("Barracks Level 2");
		linklevels.Insert(2);
		times.Insert(180);
		
		labels.Insert("Light Factory");
		names.Insert("Light Factory level 1");
		descriptions.Insert("Unlocks better Light Vehicles");
		levels.Insert(1);
		costs.Insert(2000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(300);
		
		labels.Insert("Light Factory");
		names.Insert("Light Factory level 2");
		descriptions.Insert("Unlocks better Light Vehicles");
		levels.Insert(2);
		costs.Insert(5000);
		links.Insert("Light Factory level 1");
		linklevels.Insert(1);
		times.Insert(400);
		
		/*
		labels.Insert("Heavy Factory");
		names.Insert("Light Factory level 1");
		descriptions.Insert("Unlocks better Heavy Vehicles");
		levels.Insert(1);
		costs.Insert(8000);
		links.Insert("Light Factory level 1");
		linklevels.Insert(1);
		times.Insert(500);
		
		labels.Insert("Air Factory");
		names.Insert("Air Factory level 1");
		descriptions.Insert("Unlocks better Air Vehicles");
		levels.Insert(1);
		costs.Insert(10000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(600);
		*/
		
		labels.Insert("Radio");
		names.Insert("Radio level 1");
		descriptions.Insert("Enables radio");
		levels.Insert(1);
		costs.Insert(1000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(60);
		
		labels.Insert("Radio");
		names.Insert("Radio level 2");
		descriptions.Insert("Increase radio range");
		levels.Insert(2);
		costs.Insert(2500);
		links.Insert("Radio level 1");
		linklevels.Insert(1);
		times.Insert(120);
		
		labels.Insert("Radio");
		names.Insert("Radio level 3");
		descriptions.Insert("Increase radio range");
		levels.Insert(3);
		costs.Insert(5000);
		links.Insert("Radio level 2");
		linklevels.Insert(2);
		times.Insert(180);
		
		labels.Insert("Halo Jump");
		names.Insert("Halo Jump level 1");
		descriptions.Insert("Enables Halo Jump");
		levels.Insert(1);
		costs.Insert(5000);
		links.Insert("Barracks level 1");
		linklevels.Insert(1);
		times.Insert(300);
		
		labels.Insert("Respawn Truck");
		names.Insert("Respawn Truck level 1");
		descriptions.Insert("Increase Respawn Truck range");
		levels.Insert(1);
		costs.Insert(2000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(60);
		
		labels.Insert("Respawn Truck");
		names.Insert("Respawn Truck level 2");
		descriptions.Insert("Increase Respawn Truck range");
		levels.Insert(2);
		costs.Insert(4000);
		links.Insert("Respawn Truck level 1");
		linklevels.Insert(1);
		times.Insert(120);
		
		labels.Insert("Respawn Truck");
		names.Insert("Respawn Truck level 3");
		descriptions.Insert("Increase Respawn Truck range");
		levels.Insert(3);
		costs.Insert(6000);
		links.Insert("Respawn Truck level 2");
		linklevels.Insert(2);
		times.Insert(180);
		
		labels.Insert("Towns Occupation");
		names.Insert("Towns Occupation Level 1");
		descriptions.Insert("Enables Towns Occupation");
		levels.Insert(1);
		costs.Insert(5000);
		links.Insert("Barracks Level 1");
		linklevels.Insert(1);
		times.Insert(500);
		
		labels.Insert("Towns Occupation");
		names.Insert("Towns Occupation Level 2");
		descriptions.Insert("More Towns Occupation");
		levels.Insert(2);
		costs.Insert(10000);
		links.Insert("Towns Occupation Level 1");
		linklevels.Insert(1);
		times.Insert(500);
		
		labels.Insert("Towns Occupation");
		names.Insert("Towns Occupation Level 3");
		descriptions.Insert("More Towns Occupation");
		levels.Insert(3);
		costs.Insert(20000);
		links.Insert("Towns Occupation Level 2");
		linklevels.Insert(2);
		times.Insert(500);
		
		labels.Insert("Radar");
		names.Insert("Radar level 1");
		descriptions.Insert("Unlocks Radar");
		levels.Insert(1);
		costs.Insert(5000);
		links.Insert("None");
		linklevels.Insert(0);
		times.Insert(2000);
		
		labels.Insert("Radar");
		names.Insert("Radar level 2");
		descriptions.Insert("Increase radar range");
		levels.Insert(1);
		costs.Insert(10000);
		links.Insert("Radar level 1");
		linklevels.Insert(1);
		times.Insert(4000);
		
		labels.Insert("Satellite");
		names.Insert("Satellite Camera level 1");
		descriptions.Insert("Unlocks SatCam");
		levels.Insert(1);
		costs.Insert(100000);
		links.Insert("Radar level 2");
		linklevels.Insert(2);
		times.Insert(1000);
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