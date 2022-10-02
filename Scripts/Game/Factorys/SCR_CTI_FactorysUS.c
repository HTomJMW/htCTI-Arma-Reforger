[EntityEditorProps(category: "GameScripted/CTI", description: "CTI US Factorys")]
class SCR_CTI_FactorysUS
{
	// US factorys
	FactionKey factionKey = "US";
	ref array<ref SCR_CTI_FactoryData> g_US_Factorys = new array<ref SCR_CTI_FactoryData>;

	private ref array<ResourceName> res  =  {};	// ResourceName
	private ref array<string>		name =  {};	// Name
	private ref array<int>			pri  =  {};	// Price
	private ref array<int>			bt   =  {};	// Build Time
	private ref array<int>			dis  =	{}; // Distance
	private ref array<int>			pla  =  {};	// Placement
	private ref array<string>		scr  =  {};	// Script
	
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_FactoryData factoryData;
		for (int i = 0; i < g_US_Factorys.Count(); i++)
		{
			factoryData = g_US_Factorys[i];
			if (factoryData.getRes() == resName) return i;
		}
		
		return -1;
	}
	
	void fillUp()
	{
		// Buildings
		res.Insert("{3F91DEEC9C78E473}Prefabs/Structures/Military/Houses/GuardHouse_01.et");
		name.Insert("Control Center");
		pri.Insert(0);
		bt.Insert(10);
		dis.Insert(10);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{88044D117268E628}Prefabs/Structures/Military/Houses/Barracks_01_military_yellow.et");
		name.Insert("Barracks");
		pri.Insert(0);
		bt.Insert(10);
		dis.Insert(10);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{80A5B37A1472B084}Prefabs/Structures/Industrial/Garages/Garage_E_02.et");
		name.Insert("Light Factory");
		pri.Insert(0);
		bt.Insert(10);
		dis.Insert(10);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{F16324CB8CB07C00}Prefabs/Structures/Military/Houses/GarageMilitary_E_01.et");
		name.Insert("Heavy Factory");
		pri.Insert(0);
		bt.Insert(10);
		dis.Insert(10);
		pla.Insert(0);
		scr.Insert("");
	}
	
	void init()
	{
		fillUp();
		setFactorys();
	}

	void setFactorys()
	{
		SCR_CTI_FactoryData store;
		for (int i = 0; i < res.Count(); i++)
		{
			store = new SCR_CTI_FactoryData;
			store.setData(res[i], name[i], pri[i], bt[i], dis[i], pla[i], scr[i]);
			
			g_US_Factorys.Insert(store);
		}
	}
};