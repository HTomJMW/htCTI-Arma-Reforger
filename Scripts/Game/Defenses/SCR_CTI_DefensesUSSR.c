[EntityEditorProps(category: "GameScripted/CTI", description: "CTI USSR Defenses")]
class SCR_CTI_DefensesUSSR
{
	// USSR defs
	FactionKey factionKey = "USSR";
	ref array<ref SCR_CTI_DefenseData> g_USSR_Defenses = new array<ref SCR_CTI_DefenseData>;

	private ref array<ResourceName> res  =  {};	// ResourceName
	private ref array<string>		name =  {};	// Name
	private ref array<int>			pri  =  {};	// Price
	private ref array<int>			bt   =  {};	// Build Time
	private ref array<int>	 		dis  =	{}; // Distance
	private ref array<int>			pla  =  {};	// Placement
	private ref array<string>		scr  =  {};	// Script
	
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_DefenseData defData;
		for (int i = 0; i < g_USSR_Defenses.Count(); i++)
		{
			defData = g_USSR_Defenses[i];
			if (defData.getRes() == resName) return i;
		}
		
		return -1;
	}
	
	void fillUp()
	{
		// Defenses
		res.Insert("{723870DBB19D30B0}Prefabs/Weapons/Tripods/Tripod_6T5_PKM.et");
		name.Insert("PKM - Tripod");
		pri.Insert(1000);
		bt.Insert(10);
		dis.Insert(5);
		pla.Insert(0);
		scr.Insert("");
	}
	
	void init()
	{
		fillUp();
		setDefenses();
	}

	void setDefenses()
	{
		SCR_CTI_DefenseData store;
		for (int i = 0; i < res.Count(); i++)
		{
			store = new SCR_CTI_DefenseData;
			store.setData(res[i], name[i], pri[i], bt[i], dis[i], pla[i], scr[i]);
			
			g_USSR_Defenses.Insert(store);
		}
	}
};