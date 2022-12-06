[EntityEditorProps(category: "GameScripted/CTI", description: "CTI USSR Factories")]
class SCR_CTI_FactoriesUSSR
{
	// USSR factorys
	FactionKey factionKey = "USSR";
	ref array<ref SCR_CTI_FactoryData> g_USSR_Factories = new array<ref SCR_CTI_FactoryData>;

	private ref array<ResourceName> resname		= {}; // ResourceName
	private ref array<string>		name		= {}; // Name
	private ref array<int>			price		= {}; // Price
	private ref array<int>			buildtime	= {}; // Build Time
	private ref array<int>	 		distance	= {}; // Distance
	private ref array<int>			placement	= {}; // Placement
	private ref array<string>		script		= {}; // Script

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_FactoryData factoryData;
		for (int i = 0; i < g_USSR_Factories.Count(); i++)
		{
			factoryData = g_USSR_Factories[i];
			if (factoryData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Buildings
		resname.Insert("{51F233A0BA73532A}Prefabs/Structures/Industrial/Houses/Office_E_01/Office_E_01.et");
		name.Insert("Control Center");
		price.Insert(2000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{56073EA03FCF2043}Prefabs/Structures/Military/Houses/Barracks_01/Barracks_01_military_white.et");
		name.Insert("Barracks");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(25);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{80A5B37A1472B084}Prefabs/Structures/Industrial/Garages/Garage_E_02/Garage_E_02.et");
		name.Insert("Light Factory");
		price.Insert(2000);
		buildtime.Insert(10);
		distance.Insert(20);
		placement.Insert(180);
		script.Insert("");

		resname.Insert("{4A862A8A65503FFC}Prefabs/Structures/Military/Houses/GarageMilitary_E_01/GarageMilitary_E_01_V2.et");
		name.Insert("Heavy Factory");
		price.Insert(4000);
		buildtime.Insert(10);
		distance.Insert(20);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{9CEC8BB63429FF28}Prefabs/Structures/Airport/ControlTower_01.et");
		name.Insert("Air Factory");
		price.Insert(8000);
		buildtime.Insert(10);
		distance.Insert(20);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{7E2380494811A5FB}Prefabs/Structures/Infrastructure/Towers/TransmitterTower_01/TransmitterTower_01_medium.et");
		name.Insert("Radar Tower");
		price.Insert(2000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{E8C14F26268A4D6D}Prefabs/Structures/Services/Fire/FireStation_E_01/FireStation_E_01.et");
		name.Insert("Repair Depot");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{BBCEDBF2C4E3E896}Prefabs/Structures/Industrial/Houses/Warehouse_01/Warehouse_01_Office.et");
		name.Insert("Ammo Depot");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{05446F713779A94D}Prefabs/Structures/Military/Houses/GuardHouse_02/GuardHouse_02.et");
		name.Insert("Naval");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(0);
		script.Insert("");
	}

	//------------------------------------------------------------------------------------------------
	private void setFactories()
	{
		SCR_CTI_FactoryData store;
		for (int i = 0; i < resname.Count(); i++)
		{
			store = new SCR_CTI_FactoryData;
			store.setData(resname[i], name[i], price[i], buildtime[i], distance[i], placement[i], script[i]);
			
			g_USSR_Factories.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_FactoriesUSSR()
	{
		fillUp();
		setFactories();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_FactoriesUSSR()
	{
		g_USSR_Factories.Clear();
		g_USSR_Factories = null;
	}
};