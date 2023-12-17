[EntityEditorProps(category: "GameScripted/CTI", description: "CTI FIA Gear")]
class SCR_CTI_GearFIA
{
	// FIA gear
	FactionKey factionKey = "FIA";
	ref array<ref SCR_CTI_GearData> g_FIA_Gear = new array<ref SCR_CTI_GearData>;

	private ref array<ResourceName> resname		= {}; // ResourceName
	private ref array<string>		name		= {}; // DisplayName
	private ref array<string>		category	= {}; // Category
	private ref array<int>			uplevel		= {}; // UpgradeLevel
	private ref array<int>			price		= {}; // Price

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_GearData gearData;
		for (int i = 0; i < g_FIA_Gear.Count(); i++)
		{
			gearData = g_FIA_Gear[i];
			if (gearData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// FIA gear - Used only on resistance side, exclude common things
		// Backpacks
		resname.Insert("{FDA7B6630DB87991}Prefabs/Items/Equipment/Backpacks/Backpack_M70_Swiss.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(150);
		
		// Attachments
		resname.Insert("{2F4BBE174AFAF5E0}Prefabs/Weapons/Attachments/Stocks/Stock_VZ58/Stock_VZ58_fixed.et");
		name.Insert("VZS8 Fixed Stock"); // Can't get name from container, need extend...
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{AD045AFAFFC1AB6E}Prefabs/Weapons/Attachments/Stocks/Stock_VZ58/Stock_VZ58_folding.et");
		name.Insert("VZS8 Folding Stock"); // Can't get name from container, need extend...
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		// Rifles
		resname.Insert("{9C948630078D154D}Prefabs/Weapons/Rifles/VZ58/Rifle_VZ58P.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{443CEFF17E040B11}Prefabs/Weapons/Rifles/VZ58/Rifle_VZ58V.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(200);

		// Mags
		resname.Insert("{48720FC416263FC1}Prefabs/Weapons/Magazines/Vz58/Magazine_762x39_Vz58_30rnd_Ball.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{A827B610B7CD4158}Prefabs/Weapons/Magazines/Vz58/Magazine_762x39_Vz58_30rnd_Last_5Tracer.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{FAFA0D71E75CEBE2}Prefabs/Weapons/Magazines/Vz58/Magazine_762x39_Vz58_30rnd_Tracer.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(20);

		// Helmet and hat
		resname.Insert("{B02281435AED8274}Prefabs/Characters/HeadGear/Hat_M70_01/Hat_M70_01.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(20);

		// Uniform
		resname.Insert("{BBA08EC4EC40FA94}Prefabs/Characters/Uniforms/Jacket_M70.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{06BC3F18B47799AE}Prefabs/Characters/Uniforms/Pants_M70.et");
		name.Insert("");
		category.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
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
                    if (meshComponent.GetClassName() == "WeaponComponent" || meshComponent.GetClassName() == "InventoryItemComponent" || meshComponent.GetClassName() == "InventoryMagazineComponent" || meshComponent.GetClassName() == "SCR_UniversalInventoryStorageComponent" || meshComponent.GetClassName() == "ClothNodeStorageComponent" || meshComponent.GetClassName() == "SCR_MineInventoryItemComponent")
						break;
        
                    meshComponent = null;
                }
				
				if (meshComponent)
				{
					switch (meshComponent.GetClassName())
					{
						case "WeaponComponent":
						{
							BaseContainer infoContainer = meshComponent.GetObject("UIInfo");
							string displayName;
							infoContainer.Get("Name", displayName);
							displayName = WidgetManager.Translate(displayName);
						
							name[i] = displayName;
							
							break;
						}
						case "InventoryItemComponent":
						{
							BaseContainer infoContainer = meshComponent.GetObject("Attributes");
							infoContainer = infoContainer.GetObject("ItemDisplayName");
							string displayName;
							infoContainer.Get("Name", displayName);
							displayName = WidgetManager.Translate(displayName);
						
							name[i] = displayName;
							
							break;
						}
						case "InventoryMagazineComponent":
						{
							BaseContainer infoContainer = meshComponent.GetObject("Attributes");
							infoContainer = infoContainer.GetObject("ItemDisplayName");
							string displayName;
							infoContainer.Get("Name", displayName);
							displayName = WidgetManager.Translate(displayName);
						
							name[i] = displayName;
							
							break;
						}
						case "SCR_UniversalInventoryStorageComponent":
						{
							BaseContainer infoContainer = meshComponent.GetObject("Attributes");
							infoContainer = infoContainer.GetObject("ItemDisplayName");
							string displayName;
							infoContainer.Get("Name", displayName);
							displayName = WidgetManager.Translate(displayName);
						
							name[i] = displayName;
							
							break;
						}
						case "ClothNodeStorageComponent":
						{
							BaseContainer infoContainer = meshComponent.GetObject("Attributes");
							infoContainer = infoContainer.GetObject("ItemDisplayName");
							string displayName;
							infoContainer.Get("Name", displayName);
							displayName = WidgetManager.Translate(displayName);
						
							name[i] = displayName;
							
							break;
						}
						case "SCR_MineInventoryItemComponent":
						{
							BaseContainer infoContainer = meshComponent.GetObject("Attributes");
							infoContainer = infoContainer.GetObject("ItemDisplayName");
							string displayName;
							infoContainer.Get("Name", displayName);
							displayName = WidgetManager.Translate(displayName);

							name[i] = displayName;

							break;
						}
					}
				}
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	private void setCategories()
	{
		for (int i = 0; i < resname.Count(); i++)
		{
			if (category[i] == "")
			{
				Resource resource = Resource.Load(resname[i]);
                BaseResourceObject prefabBase = resource.GetResource();
                BaseContainer prefabSrc = prefabBase.ToBaseContainer();
                BaseContainerList components = prefabSrc.GetObjectArray("components");

				array<string> componentNames = {};
				for(int j = 0; j < components.Count(); j++)
				{
					string className = components[j].GetClassName();
					componentNames.Insert(className);
				}
				
				if (componentNames.Contains("BaseLoadoutClothComponent") && !(componentNames.Contains("SCR_BinocularsComponent") || componentNames.Contains("SCR_WristwatchComponent")))
				{
					category[i] = "Uniform";
				}
				
				if (componentNames.Contains("MagazineComponent"))
				{
					category[i] = "Ammo";
				}
				
				if (componentNames.Contains("SCR_ConsumableItemComponent") || componentNames.Contains("SCR_FlashlightComponent") || componentNames.Contains("SCR_BinocularsComponent") || componentNames.Contains("SCR_WristwatchComponent") || componentNames.Contains("SCR_CompassComponent") || (componentNames.Contains("BaseRadioComponent") && !componentNames.Contains("BaseLoadoutClothComponent")))
				{
					category[i] = "Item";
				}
				
				if (componentNames.Contains("WeaponComponent"))
				{
					BaseContainer meshComponent = null;
					int index = componentNames.Find("WeaponComponent");
					meshComponent = components.Get(index);
					
					EWeaponType weaponType;
					meshComponent.Get("WeaponType", weaponType);
					
					switch(weaponType)
					{
						case 1: category[i] = "Rifle"; break;
						case 3: category[i] = "Rifle"; break;
						case 5: category[i] = "Rifle"; break;
						
						case 4: category[i] = "Launcher"; break;
						
						case 6: category[i] = "Pistol"; break;
						
						case 7: category[i] = "Ammo"; break;
						case 8: category[i] = "Ammo"; break;
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	private void setGear()
	{
		SCR_CTI_GearData store;
		for (int i = 0; i < resname.Count(); i++)
		{
			store = new SCR_CTI_GearData;
			store.setData(resname[i], name[i], category[i], uplevel[i], price[i]);
			
			g_FIA_Gear.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_GearFIA()
	{
		fillUp();
		setDisplayNames();
		setCategories();
		setGear();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GearFIA()
	{
		if (g_FIA_Gear) g_FIA_Gear.Clear();
		g_FIA_Gear = null;
		
		if (resname) resname.Clear();
		resname = null;
		if (name) name.Clear();
		name = null;
		if (category) category.Clear();
		category = null;
		if (uplevel) uplevel.Clear();
		uplevel = null;
		if (price) price.Clear();
		price = null;
	}
};