[EntityEditorProps(category: "GameScripted/CTI", description: "CTI US Units")]
class SCR_CTI_UnitsUS
{
	// US units
	FactionKey factionKey = "US";
	ref array<ref SCR_CTI_UnitData> g_US_Units = new array<ref SCR_CTI_UnitData>;

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
		for (int i = 0; i < g_US_Units.Count(); i++)
		{
			unitData = g_US_Units[i];
			if (unitData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Equipment box
		resname.Insert("{0FC1D6E9B592F75D}Prefabs/Systems/Arsenal/AmmoBoxes/US/AmmoBoxArsenal_Equipment_US.et");
		picture.Insert("");
		name.Insert("Equipment Box");
		price.Insert(500);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Flag");
		script.Insert("");

		// Soldiers
		resname.Insert("{2F912ED6E399FF47}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Unarmed.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(75);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{E45F1E163F5CA080}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_SL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(120);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{E398E44759DA1A43}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_TL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(120);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{C9E4FEAF5AAC8D8C}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Medic.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{26A9756790131354}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Rifleman.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{5B1996C05B1E51A4}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_AR.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(150);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{1623EA3AEFACA0E4}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_MG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(150);
		buildtime.Insert(10);
		uplevel.Insert(2);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{27BF1FF235DD6036}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_LAT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(2);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{0F6689B491641155}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Sniper.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(3);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{84029128FA6F6BB9}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_GL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(120);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{3726077BE60962FF}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_RTO.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(1);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{1CA3D30464EE4674}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Spotter.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(3);
		factory.Insert("Barracks");
		script.Insert("");

		resname.Insert("{6058AB54781A0C52}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_AMG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(110);
		buildtime.Insert(10);
		uplevel.Insert(2);
		factory.Insert("Barracks");
		script.Insert("");

		// Vehicles
		resname.Insert("{F649585ABB3706C4}Prefabs/Vehicles/Wheeled/M151A2/M151A2.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(700);
		buildtime.Insert(20);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{47D94E1193A88497}Prefabs/Vehicles/Wheeled/M151A2/M151A2_transport.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(750);
		buildtime.Insert(20);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{F6B23D17D5067C11}Prefabs/Vehicles/Wheeled/M151A2/M151A2_M2HB.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(900);
		buildtime.Insert(30);
		uplevel.Insert(1);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{F1FBD0972FA5FE09}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1200);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{81FDAD5EB644CC3D}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport_covered.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1300);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{9E8B0E825C072CE5}Prefabs/Vehicles/Wheeled/M923A1/M923A1_medical.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(2500);
		buildtime.Insert(30);
		uplevel.Insert(1);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{A042ACE5C2B13206}Prefabs/Vehicles/Wheeled/M923A1/M923A1_repair.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Repair Depot");
		script.Insert("");

		resname.Insert("{92264FF932676C13}Prefabs/Vehicles/Wheeled/M923A1/M923A1_ammo.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Ammo Depot");
		script.Insert("");

		resname.Insert("{2116A4AEE7457A54}Prefabs/Vehicles/Wheeled/M923A1/M923A1_fuel.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(30);
		uplevel.Insert(0);
		factory.Insert("Repair Depot");
		script.Insert("");

		resname.Insert("{36BDCC88B17B3BFA}Prefabs/Vehicles/Wheeled/M923A1/M923A1_command.et"); // MHQ
		picture.Insert("");
		name.Insert("");
		price.Insert(20000);
		buildtime.Insert(60);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");

		resname.Insert("{B55C6990A6A9411B}Prefabs/Vehicles/Wheeled/M998/M998_covered.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1000);
		buildtime.Insert(45);
		uplevel.Insert(0);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{4A71F755A4513227}Prefabs/Vehicles/Wheeled/M998/M1025.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1000);
		buildtime.Insert(45);
		uplevel.Insert(1);
		factory.Insert("Light Factory");
		script.Insert("");

		resname.Insert("{3EA6F47D95867114}Prefabs/Vehicles/Wheeled/M998/M1025_armed_M2HB.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(1500);
		buildtime.Insert(45);
		uplevel.Insert(1);
		factory.Insert("Light Factory");
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
			
			g_US_Units.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UnitsUS()
	{
		fillUp();
		setDisplayNames();
		setUnits();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UnitsUS()
	{
		if (!g_US_Units) return;
		g_US_Units.Clear();
		g_US_Units = null;
	}
};