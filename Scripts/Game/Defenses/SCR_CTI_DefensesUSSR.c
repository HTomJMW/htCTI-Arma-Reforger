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

	//------------------------------------------------------------------------------------------------
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

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Defenses
		res.Insert("{723870DBB19D30B0}Prefabs/Weapons/Tripods/Tripod_6T5_PKM.et");
		name.Insert("PKM - Tripod");
		pri.Insert(1000);
		bt.Insert(10);
		dis.Insert(5);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{B90CA0BEF3CC1D19}Prefabs/Structures/Military/CamoNets/Soviet/CamoNet_Medium_Soviet.et");
		name.Insert("Camo Net - Medium");
		pri.Insert(500);
		bt.Insert(10);
		dis.Insert(15);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{FBCE1861B987EA68}Prefabs/Structures/Military/Houses/GuardTower_01/GuardTower_01.et");
		name.Insert("Guard Tower");
		pri.Insert(1000);
		bt.Insert(10);
		dis.Insert(10);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{80DF3BD810D032AF}Prefabs/Structures/Industrial/Towers/LightTower_01/LightTower_01.et");
		name.Insert("Light Tower");
		pri.Insert(700);
		bt.Insert(10);
		dis.Insert(10);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{4E331E7D8DAD1EAD}Prefabs/Structures/Military/Camps/TentUSSR_01/TentUSSR_01.et");
		name.Insert("Tent");
		pri.Insert(500);
		bt.Insert(10);
		dis.Insert(5);
		pla.Insert(0);
		scr.Insert("");
		
		res.Insert("{DA1B42FB9AEC02BE}Prefabs/Structures/Military/Fortifications/Dragontooth_01/Dragontooth_01_V3.et");
		name.Insert("Dragon Tooth");
		pri.Insert(500);
		bt.Insert(10);
		dis.Insert(5);
		pla.Insert(0);
		scr.Insert("");
	}

	//------------------------------------------------------------------------------------------------
	private void setDefenses()
	{
		SCR_CTI_DefenseData store;
		for (int i = 0; i < res.Count(); i++)
		{
			store = new SCR_CTI_DefenseData;
			store.setData(res[i], name[i], pri[i], bt[i], dis[i], pla[i], scr[i]);
			
			g_USSR_Defenses.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_DefensesUSSR()
	{
		fillUp();
		setDefenses();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_DefensesUSSR()
	{
		g_USSR_Defenses.Clear();
		g_USSR_Defenses = null;
	}
};