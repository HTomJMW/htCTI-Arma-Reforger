[EntityEditorProps(category: "GameScripted/CTI", description: "CTI USSR Units")]
class SCR_CTI_UnitsUSSR
{
	// USSR units
	FactionKey factionKey = "USSR";
	ref array<ref SCR_CTI_UnitData> g_USSR_Units = new array<ref SCR_CTI_UnitData>;

	private ref array<ResourceName> resname		= {}; // ResourceName
	private ref array<string>		picture		= {}; // Picture
	private ref array<string>		name		= {}; // Name
	private ref array<int>			price		= {}; // Price
	private ref array<int>			buildtime	= {}; // Build Time
	private ref array<int>			uplevel		= {}; // Upgrade Level
	private ref array<string>		factory		= {}; // Factory
	private ref array<string>		script		= {}; // Script

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_UnitData unitData;
		for (int i = 0; i < g_USSR_Units.Count(); i++)
		{
			unitData = g_USSR_Units[i];
			if (unitData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Equipment box
		resname.Insert(SCR_CTI_Constants.USSR_BOX);
		picture.Insert("");
		name.Insert("Equipment Box");
		price.Insert(500);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Flag");
		script.Insert("");

		// Soldiers
		resname.Insert(SCR_CTI_Constants.USSR_WORKER);
		picture.Insert("");
		name.Insert("Worker");
		price.Insert(SCR_CTI_Constants.WORKERPRICE);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("MHQ");
		script.Insert("");

		resname.Insert("{98EB9CDD85B8C92C}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Unarmed.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(75);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{5436629450D8387A}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_SL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(120);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{AB9726163EC1BD81}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Medic.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{DCB41B3746FDD1BE}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Rifleman.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{23ADBBC31B6A3DC6}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_AR.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(150);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{96C784C502AC37DA}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_MG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(150);
		buildtime.Insert(10);
		uplevel.Insert(2);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{1C78331E156A3D65}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_AT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(2);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{976AC400219898FA}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Sharpshooter.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(3);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{8E0FE664CE7D1CA9}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_GL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(120);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{612F43A4D5AE765F}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_RTO.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{E9AEEF2D9E41321B}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_AMG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(110);
		buildtime.Insert(10);
		uplevel.Insert(2);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{631158F6898738A4}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_AAT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(110);
		buildtime.Insert(10);
		uplevel.Insert(2);
		factory.Insert("Barracks");
		script.Insert("");

		// Vehicles
		resname.Insert("{16A674FE31B0921C}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469_uncovered.et");
		picture.Insert("");
		name.Insert("UAZ-469 Off-road - Open Top"); // missing open top name
		price.Insert(700);
		buildtime.Insert(20);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert(SCR_CTI_Constants.USSR_UAZ);
		picture.Insert("");
		name.Insert("");
		price.Insert(750);
		buildtime.Insert(20);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{0B4DEA8078B78A9B}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469_PKM.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(900);
		buildtime.Insert(30);
		uplevel.Insert(1);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{43C4AF1EEBD001CE}Prefabs/Vehicles/Wheeled/UAZ452/UAZ452_ambulance.et");
		picture.Insert("");
		name.Insert("UAZ-452A Ambulance [Mobile Respawn]");
		price.Insert(2000);
		buildtime.Insert(25);
		uplevel.Insert(1);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{16C1F16C9B053801}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1200);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert(SCR_CTI_Constants.USSR_TRUCK);
		picture.Insert("");
		name.Insert("");
		price.Insert(1300);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{A5647958579A4149}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_repair.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Repair Depot");
		script.Insert("");

		resname.Insert("{3336BE330C4F355B}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_ammo.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Ammo Depot");
		script.Insert("");

		resname.Insert("{4C81D7ED8F8C0D87}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_tanker.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Repair Depot");
		script.Insert("");

		resname.Insert(SCR_CTI_Constants.USSR_MHQ);
		picture.Insert("");
		name.Insert("");
		price.Insert(2000); // For reward need use other price, its only for service menu
		buildtime.Insert(60);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");

		resname.Insert(SCR_CTI_Constants.USSR_BTR70);
		picture.Insert("");
		name.Insert("");
		price.Insert(2500);
		buildtime.Insert(45);
		uplevel.Insert(0);
		factory.Insert("Heavy Factory");
		script.Insert("");
		
		// Air
		resname.Insert("{DF5CCB7C0FF049F4}Prefabs/Vehicles/Helicopters/Mi8MT/Mi8MT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(8000);
		buildtime.Insert(60);
		uplevel.Insert(0);
		factory.Insert("Air Factory");
		script.Insert("");
	}
	
	//------------------------------------------------------------------------------------------------
	private void setDisplayNames()
	{
		for (int i = 0; i < resname.Count(); i++)
		{
			if (name[i] == "")
			{
				Resource resource = Resource.Load(resname[i]);
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

                BaseContainer meshComponent = null;
                for (int c = components.Count() - 1; c >= 0; c--)
                {
                    meshComponent = components.Get(c);
                    if (meshComponent.GetClassName() == "SCR_EditableCharacterComponent" || meshComponent.GetClassName() == "SCR_EditableVehicleComponent")
						break;
        
                    meshComponent = null;
                }
                if (meshComponent)
                {
					BaseContainer infoContainer = meshComponent.GetObject("m_UIInfo");
					string displayName;
					infoContainer.Get("Name", displayName);
					displayName = WidgetManager.Translate(displayName);
					
					name[i] = displayName;
                }
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	private void setUnits()
	{
		SCR_CTI_UnitData store;
		for (int i = 0; i < resname.Count(); i++)
		{
			store = new SCR_CTI_UnitData;
			store.setData(resname[i], picture[i], name[i], price[i], buildtime[i], uplevel[i], factory[i], script[i]);
			
			g_USSR_Units.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UnitsUSSR()
	{
		fillUp();
		setDisplayNames();
		setUnits();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UnitsUSSR()
	{
		if (g_USSR_Units) g_USSR_Units.Clear();
		g_USSR_Units = null;
		
		if (resname) resname.Clear();
		resname = null;
		if (picture) picture.Clear();
		picture = null;
		if (name) name.Clear();
		name = null;
		if (price) price.Clear();
		price = null;
		if (buildtime) buildtime.Clear();
		buildtime = null;
		if (uplevel) uplevel.Clear();
		uplevel = null;
		if (factory) factory.Clear();
		factory = null;
		if (script) script.Clear();
		script = null;
	}
};