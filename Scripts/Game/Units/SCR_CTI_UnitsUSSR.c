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
		resname.Insert("{B728C4AE0E6EB1E8}Prefabs/Systems/Arsenal/AmmoBoxes/USSR/AmmoBoxArsenal_Equipment_USSR.et");
		picture.Insert("");
		name.Insert("Equipment Box");
		price.Insert(500);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Flag");
		script.Insert("");
		
		// Soldiers
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
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{AB9726163EC1BD81}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Medic.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
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
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{96C784C502AC37DA}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_MG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(150);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{1C78331E156A3D65}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_AT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{976AC400219898FA}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Sharpshooter.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{8E0FE664CE7D1CA9}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_GL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(120);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{612F43A4D5AE765F}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_RTO.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{E9AEEF2D9E41321B}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_AMG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(110);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		resname.Insert("{631158F6898738A4}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_AAT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(110);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");
		
		// Vehicles
		resname.Insert("{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(700);
		buildtime.Insert(20);
		uplevel.Insert(0);
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
		
		resname.Insert("{D9B91FAB817A6033}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport_covered.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1300);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");
		
		resname.Insert("{4C81D7ED8F8C0D87}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_tanker.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Repair Depot");
		script.Insert("");
		
		resname.Insert("{1BABF6B33DA0AEB6}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_command.et"); // MHQ
		picture.Insert("");
		name.Insert("");
		price.Insert(20000);
		buildtime.Insert(60);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{C012BB3488BEA0C2}Prefabs/Vehicles/Wheeled/BTR70/BTR70.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(2500);
		buildtime.Insert(45);
		uplevel.Insert(1);
		factory.Insert("Heavy Factory");
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
		g_USSR_Units.Clear();
		g_USSR_Units = null;
	}
};