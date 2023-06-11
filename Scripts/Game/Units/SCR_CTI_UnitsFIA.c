[EntityEditorProps(category: "GameScripted/CTI", description: "CTI FIA Units")]
class SCR_CTI_UnitsFIA
{
	// FIA units
	FactionKey factionKey = "FIA";
	ref array<ref SCR_CTI_UnitData> g_FIA_Units = new array<ref SCR_CTI_UnitData>;

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
		for (int i = 0; i < g_FIA_Units.Count(); i++)
		{
			unitData = g_FIA_Units[i];
			if (unitData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Equipment box
		resname.Insert("{7F1A910F6EA32A82}Prefabs/Systems/Arsenal/AmmoBoxes/FIA/AmmoBoxArsenal_Equipment_FIA.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(500);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		// Soldiers
		resname.Insert("{854C04F0EA2129CC}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Unarmed.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(75);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{677B515F119222C2}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_SL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(120);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{45A02CA25CBA9443}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Medic.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{84B40583F4D1B7A3}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Rifleman.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{58E47E5A4D599432}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_MG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(150);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{D25BC9815A9F9E8D}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_AT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{CE33AB22F61F3365}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Sharpshooter.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(200);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{BF1E43FF39AA526B}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Scout.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{23D81C023DBF85AC}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_RTO.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{FE65E8C60C751352}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_PL.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(100);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{75FC25863194612A}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_AMG.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(110);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{FF43925D26526B95}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_AAT.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(110);
		buildtime.Insert(10);
		uplevel.Insert(0);
		factory.Insert("");
		script.Insert("");
		
		resname.Insert("{B47110AA1A806556}Prefabs/Vehicles/Wheeled/BTR70/BTR70_FIA.et");
		picture.Insert("");
		name.Insert("");
		price.Insert(2500);
		buildtime.Insert(45);
		uplevel.Insert(0);
		factory.Insert("");
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
			
			g_FIA_Units.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UnitsFIA()
	{
		fillUp();
		setDisplayNames();
		setUnits();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UnitsFIA()
	{
		if (!g_FIA_Units) return;
		g_FIA_Units.Clear();
		g_FIA_Units = null;
	}
};