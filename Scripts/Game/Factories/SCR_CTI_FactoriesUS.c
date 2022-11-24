[EntityEditorProps(category: "GameScripted/CTI", description: "CTI US Factories")]
class SCR_CTI_FactoriesUS
{
	// US factorys
	FactionKey factionKey = "US";
	ref array<ref SCR_CTI_FactoryData> g_US_Factories = new array<ref SCR_CTI_FactoryData>;

	private ref array<ResourceName> res  =  {};	// ResourceName
	private ref array<string>		name =  {};	// Name
	private ref array<int>			pri  =  {};	// Price
	private ref array<int>			bt   =  {};	// Build Time
	private ref array<int>			dis  =	{}; // Distance
	private ref array<int>			pla  =  {};	// Placement
	private ref array<string>		scr  =  {};	// Script

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_FactoryData factoryData;
		for (int i = 0; i < g_US_Factories.Count(); i++)
		{
			factoryData = g_US_Factories[i];
			if (factoryData.getRes() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Buildings
		res.Insert("{51F233A0BA73532A}Prefabs/Structures/Industrial/Houses/Office_E_01/Office_E_01.et");
		name.Insert("Control Center");
		pri.Insert(2000);
		bt.Insert(10);
		dis.Insert(15);
		pla.Insert(180);
		scr.Insert("");
		
		res.Insert("{56073EA03FCF2043}Prefabs/Structures/Military/Houses/Barracks_01/Barracks_01_military_white.et");
		name.Insert("Barracks");
		pri.Insert(1000);
		bt.Insert(10);
		dis.Insert(25);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{80A5B37A1472B084}Prefabs/Structures/Industrial/Garages/Garage_E_02/Garage_E_02.et");
		name.Insert("Light Factory");
		pri.Insert(2000);
		bt.Insert(10);
		dis.Insert(20);
		pla.Insert(180);
		scr.Insert("");

		res.Insert("{4A862A8A65503FFC}Prefabs/Structures/Military/Houses/GarageMilitary_E_01/GarageMilitary_E_01_V2.et");
		name.Insert("Heavy Factory");
		pri.Insert(4000);
		bt.Insert(10);
		dis.Insert(20);
		pla.Insert(180);
		scr.Insert("");
		
		res.Insert("{9CEC8BB63429FF28}Prefabs/Structures/Airport/ControlTower_01.et");
		name.Insert("Air Factory");
		pri.Insert(8000);
		bt.Insert(10);
		dis.Insert(20);
		pla.Insert(180);
		scr.Insert("");
		
		res.Insert("{7E2380494811A5FB}Prefabs/Structures/Infrastructure/Towers/TransmitterTower_01/TransmitterTower_01_medium.et");
		name.Insert("Radar Tower");
		pri.Insert(2000);
		bt.Insert(10);
		dis.Insert(15);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{E8C14F26268A4D6D}Prefabs/Structures/Services/Fire/FireStation_E_01/FireStation_E_01.et");
		name.Insert("Repair Depot");
		pri.Insert(1000);
		bt.Insert(10);
		dis.Insert(15);
		pla.Insert(180);
		scr.Insert("");
		
		res.Insert("{BBCEDBF2C4E3E896}Prefabs/Structures/Industrial/Houses/Warehouse_01/Warehouse_01_Office.et");
		name.Insert("Ammo Depot");
		pri.Insert(1000);
		bt.Insert(10);
		dis.Insert(15);
		pla.Insert(180);
		scr.Insert("");
		
		res.Insert("{05446F713779A94D}Prefabs/Structures/Military/Houses/GuardHouse_02/GuardHouse_02.et");
		name.Insert("Naval");
		pri.Insert(1000);
		bt.Insert(10);
		dis.Insert(15);
		pla.Insert(0);
		scr.Insert("");
	}

	//------------------------------------------------------------------------------------------------
	void init()
	{
		fillUp();
		setFactories();
	}

	//------------------------------------------------------------------------------------------------
	private void setFactories()
	{
		SCR_CTI_FactoryData store;
		for (int i = 0; i < res.Count(); i++)
		{
			store = new SCR_CTI_FactoryData;
			store.setData(res[i], name[i], pri[i], bt[i], dis[i], pla[i], scr[i]);
			
			g_US_Factories.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_FactoriesUS()
	{
		fillUp();
		setFactories();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_FactoriesUS()
	{
		g_US_Factories.Clear();
		g_US_Factories = null;
	}
};