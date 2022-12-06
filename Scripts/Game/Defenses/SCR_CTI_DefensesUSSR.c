[EntityEditorProps(category: "GameScripted/CTI", description: "CTI USSR Defenses")]
class SCR_CTI_DefensesUSSR
{
	// USSR defs
	FactionKey factionKey = "USSR";
	ref array<ref SCR_CTI_DefenseData> g_USSR_Defenses = new array<ref SCR_CTI_DefenseData>;

	private ref array<ResourceName> resname		= {}; // ResourceName
	private ref array<string>		name		= {}; // Name
	private ref array<int>			price		= {}; // Price
	private ref array<int>			buildtime   = {}; // Build Time
	private ref array<int>	 		distance	= {}; // Distance
	private ref array<int>			placement	= {}; // Placement
	private ref array<string>		script		= {}; // Script

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_DefenseData defData;
		for (int i = 0; i < g_USSR_Defenses.Count(); i++)
		{
			defData = g_USSR_Defenses[i];
			if (defData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Defenses
		resname.Insert("{723870DBB19D30B0}Prefabs/Weapons/Tripods/Tripod_6T5_PKM.et");
		name.Insert("PKM - Tripod");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{B90CA0BEF3CC1D19}Prefabs/Structures/Military/CamoNets/Soviet/CamoNet_Medium_Soviet.et");
		name.Insert("Camo Net - Medium");
		price.Insert(500);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{FBCE1861B987EA68}Prefabs/Structures/Military/Houses/GuardTower_01/GuardTower_01.et");
		name.Insert("Guard Tower");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(10);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{80DF3BD810D032AF}Prefabs/Structures/Industrial/Towers/LightTower_01/LightTower_01.et");
		name.Insert("Light Tower");
		price.Insert(700);
		buildtime.Insert(10);
		distance.Insert(10);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{4E331E7D8DAD1EAD}Prefabs/Structures/Military/Camps/TentUSSR_01/TentUSSR_01.et");
		name.Insert("Tent");
		price.Insert(500);
		buildtime.Insert(10);
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{DA1B42FB9AEC02BE}Prefabs/Structures/Military/Fortifications/Dragontooth_01/Dragontooth_01_V3.et");
		name.Insert("Dragon Tooth");
		price.Insert(500);
		buildtime.Insert(10);
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");
	}

	//------------------------------------------------------------------------------------------------
	private void setDefenses()
	{
		SCR_CTI_DefenseData store;
		for (int i = 0; i < resname.Count(); i++)
		{
			store = new SCR_CTI_DefenseData;
			store.setData(resname[i], name[i], price[i], buildtime[i], distance[i], placement[i], script[i]);
			
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