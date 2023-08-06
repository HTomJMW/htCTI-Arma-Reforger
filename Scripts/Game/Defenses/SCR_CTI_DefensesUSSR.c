[EntityEditorProps(category: "GameScripted/CTI", description: "CTI USSR Defenses")]
class SCR_CTI_DefensesUSSR
{
	// USSR defs
	FactionKey factionKey = "USSR";
	ref array<ref SCR_CTI_DefenseData> g_USSR_Defenses = new array<ref SCR_CTI_DefenseData>;

	private ref array<ResourceName> resname		= {}; // ResourceName
	private ref array<string>		name		= {}; // Name
	private ref array<int>			price		= {}; // Price
	private ref array<string>		category	= {}; // Category
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
		resname.Insert("{74D4D08878ACBD99}Prefabs/Weapons/Tripods/CTI_Tripod_6T5_PKM.et");
		name.Insert("PKM - Tripod");
		price.Insert(1000);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{2A4E7F1BA362AEAF}Prefabs/Structures/Military/CamoNets/Soviet/CTI_CamoNet_Medium_Soviet.et");
		name.Insert("Camo Net - Medium");
		price.Insert(500);
		category.Insert("");
		distance.Insert(12);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{F41D3F71C486575C}Prefabs/Structures/Military/Houses/GuardTower_01/CTI_GuardTower_01.et");
		name.Insert("Guard Tower");
		price.Insert(1000);
		category.Insert("");
		distance.Insert(10);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{9D538521251CD0CA}Prefabs/Structures/Industrial/Towers/LightTower_01/CTI_LightTower_01.et");
		name.Insert("Light Tower");
		price.Insert(700);
		category.Insert("");
		distance.Insert(10);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{6AF8C94550B05D1A}Prefabs/Structures/Military/Camps/Canvas_Covers/Soviet/CTI_CanvasCover_Large_Soviet.et");
		name.Insert("Canvas Cover");
		price.Insert(300);
		category.Insert("");
		distance.Insert(8);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{5C826F3B6807C726}Prefabs/Structures/Military/Camps/TentUSSR_01/CTI_TentUSSR_01.et");
		name.Insert("Tent");
		price.Insert(500);
		category.Insert("");
		distance.Insert(8);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{BEB48B461EA778F0}Prefabs/Structures/Walls/BarbedWire/BarbedTape_01/CTI_BarbedTape_01_Long.et");
		name.Insert("Barbed Wire");
		price.Insert(300);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(90);
		script.Insert("");
		
		resname.Insert("{3CBE18859ECD6B26}Prefabs/Structures/Military/Fortifications/Dragontooth_01/CTI_Dragontooth_01_V3.et");
		name.Insert("Dragon Tooth");
		price.Insert(500);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");

		// Bugged placing (90deg)
		/*resname.Insert("{DB2FACBA51080419}Prefabs/Compositions/Misc/SubCompositions/CTI_Sandbag_Camo_long_high_USSR.et");
		name.Insert("Sandbags - Camo");
		price.Insert(400);
		category.Insert("");
		distance.Insert(6);
		placement.Insert(0);
		script.Insert("");*/
		
		resname.Insert("{AF1C52A95899283B}Prefabs/Compositions/Misc/SubCompositions/CTI_Barricade_Logs_01.et");
		name.Insert("Barricade");
		price.Insert(500);
		category.Insert("");
		distance.Insert(7);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{9B8809719E076CBD}Prefabs/Structures/Walls/Concrete/ConcreteWall_01/CTI_ConcreteWall_01_camo_6m_B.et");
		name.Insert("Concrate Wall");
		price.Insert(500);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{2E31F50BD0685D63}Prefabs/Structures/Airport/LightRunway_01/CTI_LightRunway_01_white.et");
		name.Insert("Runway Light");
		price.Insert(200);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{1B1209BA807B60D2}Prefabs/Structures/Infrastructure/Lamps/LampStreet_E_02/CTI_LampStreet_E_02_single.et");
		name.Insert("Lamp Post");
		price.Insert(200);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{7FF02943FB7CDCE4}Prefabs/Structures/Infrastructure/Lamps/LampStreet_E_02/CTI_LampStreet_E_02_doubleStraight.et");
		name.Insert("Dual Lamp Post");
		price.Insert(200);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(90);
		script.Insert("");
		
		resname.Insert("{950DF64892A0B707}Prefabs/Items/Demining/MineFlags/CTI_MineFlag_USSR.et");
		name.Insert("Mine Flag");
		price.Insert(50);
		category.Insert("");
		distance.Insert(4);
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
			store.setData(resname[i], name[i], price[i], category[i], distance[i], placement[i], script[i]);
			
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
		if (!g_USSR_Defenses) return;
		g_USSR_Defenses.Clear();
		g_USSR_Defenses = null;
	}
};