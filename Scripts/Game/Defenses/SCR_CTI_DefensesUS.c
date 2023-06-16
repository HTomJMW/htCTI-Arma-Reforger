[EntityEditorProps(category: "GameScripted/CTI", description: "CTI US Defenses")]
class SCR_CTI_DefensesUS
{
	// US defs
	FactionKey factionKey = "US";
	ref array<ref SCR_CTI_DefenseData> g_US_Defenses = new array<ref SCR_CTI_DefenseData>;

	private ref array<ResourceName> resname		= {}; // ResourceName
	private ref array<string>		name		= {}; // Name
	private ref array<int>			price		= {}; // Price
	private ref array<string>		category	= {}; // Category
	private ref array<int>			distance	= {}; // Distance
	private ref array<int>			placement	= {}; // Placement
	private ref array<string>		script		= {}; // Script

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_DefenseData defData;
		for (int i = 0; i < g_US_Defenses.Count(); i++)
		{
			defData = g_US_Defenses[i];
			if (defData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Defenses
		resname.Insert("{83A5D83A4BFC12FF}Prefabs/Weapons/Tripods/CTI_Tripod_M122_MG_M60.et");
		name.Insert("M60 - Tripod");
		price.Insert(1000);
		category.Insert("");
		distance.Insert(5);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{37E774931ECF96FB}Prefabs/Structures/Military/CamoNets/US/CTI_CamoNet_Medium_US.et");
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
		
		resname.Insert("{E5C9F16617D4297B}Prefabs/Structures/Military/Camps/Canvas_Covers/US/CTI_CanvasCover_Large_US.et");
		name.Insert("Canvas Cover");
		price.Insert(300);
		category.Insert("");
		distance.Insert(8);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{479EB44290C671F1}Prefabs/Structures/Military/Camps/TentUS_01/CTI_TentUS_01_Assembled.et");
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
		
		resname.Insert("{C32638BCE50E6212}Prefabs/Items/Demining/MineFlags/CTI_MineFlag_US.et");
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
			
			g_US_Defenses.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_DefensesUS()
	{
		fillUp();
		setDefenses();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_DefensesUS()
	{
		if (!g_US_Defenses) return;
		g_US_Defenses.Clear();
		g_US_Defenses = null;
	}
};