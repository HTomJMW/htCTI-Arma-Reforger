[EntityEditorProps(category: "GameScripted/CTI", description: "CTI US Factories")]
class SCR_CTI_FactoriesUS
{
	// US factorys
	FactionKey factionKey = "US";
	ref array<ref SCR_CTI_FactoryData> g_US_Factories = new array<ref SCR_CTI_FactoryData>;

	private ref array<ResourceName> resname		= {}; // ResourceName
	private ref array<ResourceName> wipname		= {}; // WIP ResourceMame
	private ref array<string>		name		= {}; // Name
	private ref array<int>			price		= {}; // Price
	private ref array<int>			buildtime	= {}; // Build Time
	private ref array<int>			distance	= {}; // Distance
	private ref array<int>			placement	= {}; // Placement
	private ref array<string>		script		= {}; // Script

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_FactoryData factoryData;
		for (int i = 0; i < g_US_Factories.Count(); i++)
		{
			factoryData = g_US_Factories[i];
			if (factoryData.getResName() == resName || factoryData.getWIPName() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Buildings
		resname.Insert("{531C9448A4765D2C}Prefabs/Structures/Industrial/Houses/Office_E_01/CTI_Office_E_01.et");
		wipname.Insert("{456DCCA35C04C8C1}Prefabs/Structures/Industrial/Houses/Office_E_01/CTI_Office_E_01_WIP.et");
		name.Insert("Control Center");
		price.Insert(2000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{8614313A0B9A7D00}Prefabs/Structures/Military/Houses/Barracks_01/CTI_Barracks_01_military_white.et");
		wipname.Insert("{2877A7B2761573F3}Prefabs/Structures/Military/Houses/Barracks_01/CTI_Barracks_01_military_white_WIP.et");
		name.Insert("Barracks");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(25);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{B96C2C9025525F99}Prefabs/Structures/Industrial/Garages/Garage_E_02/CTI_Garage_E_02.et");
		wipname.Insert("{02402124C6749AE3}Prefabs/Structures/Industrial/Garages/Garage_E_02/CTI_Garage_E_02_WIP.et");
		name.Insert("Light Factory");
		price.Insert(2000);
		buildtime.Insert(10);
		distance.Insert(20);
		placement.Insert(180);
		script.Insert("");

		resname.Insert("{A23910B70FA0AE18}Prefabs/Structures/Military/Houses/GarageMilitary_E_01/CTI_GarageMilitary_E_01_V2.et");
		wipname.Insert("{319A8382D916124D}Prefabs/Structures/Military/Houses/GarageMilitary_E_01/CTI_GarageMilitary_E_01_V2_WIP.et");
		name.Insert("Heavy Factory");
		price.Insert(4000);
		buildtime.Insert(10);
		distance.Insert(20);
		placement.Insert(180);
		script.Insert("");
		
		/*resname.Insert("{B26CC368BE2940F1}Prefabs/Structures/Airport/CTI_ControlTower_01.et");
		wipname.Insert("{008116AA975DA252}Prefabs/Structures/Airport/CTI_ControlTower_01_WIP.et");
		name.Insert("Air Factory");
		price.Insert(8000);
		buildtime.Insert(10);
		distance.Insert(20);
		placement.Insert(180);
		script.Insert("");*/
		
		resname.Insert("{629CD40ABAEA6CF9}Prefabs/Structures/Infrastructure/Towers/TransmitterTower_01/CTI_TransmitterTower_01_medium.et");
		wipname.Insert("{D693709149EC77D3}Prefabs/Structures/Infrastructure/Towers/TransmitterTower_01/CTI_TransmitterTower_01_medium_WIP.et");
		name.Insert("Radar Tower");
		price.Insert(2000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(0);
		script.Insert("");
		
		resname.Insert("{706F5D7B89075C8E}Prefabs/Structures/Services/Fire/FireStation_E_01/CTI_FireStation_E_01_white.et");
		wipname.Insert("{96FFA1A00062A85A}Prefabs/Structures/Services/Fire/FireStation_E_01/CTI_FireStation_E_01_white_WIP.et");
		name.Insert("Repair Depot");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(180);
		script.Insert("");
		
		resname.Insert("{9F0ADF73AD4259AE}Prefabs/Structures/Industrial/Houses/Warehouse_01/CTI_Warehouse_01_Office.et");
		wipname.Insert("{025FA95714B6F641}Prefabs/Structures/Industrial/Houses/Warehouse_01/CTI_Warehouse_01_Office_WIP.et");
		name.Insert("Ammo Depot");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(180);
		script.Insert("");
		
		/*resname.Insert("{0148FBB09395D786}Prefabs/Structures/Military/Houses/GuardHouse_02/CTI_GuardHouse_02.et");
		wipname.Insert("{7685EDFEB663C136}Prefabs/Structures/Military/Houses/GuardHouse_02/CTI_GuardHouse_02_WIP.et");
		name.Insert("Naval");
		price.Insert(1000);
		buildtime.Insert(10);
		distance.Insert(15);
		placement.Insert(0);
		script.Insert("");*/
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
		for (int i = 0; i < resname.Count(); i++)
		{
			store = new SCR_CTI_FactoryData;
			store.setData(resname[i], wipname[i], name[i], price[i], buildtime[i], distance[i], placement[i], script[i]);
			
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
		if (!g_US_Factories) return;
		g_US_Factories.Clear();
		g_US_Factories = null;
	}
};