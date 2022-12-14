[EntityEditorProps(category: "GameScripted/CTI", description: "CTI US Gear")]
class SCR_CTI_GearUS
{
	// US gear
	FactionKey factionKey = "US";
	ref array<ref SCR_CTI_GearData> g_US_Gear = new array<ref SCR_CTI_GearData>;

	private ref array<ResourceName> resname = {}; // ResourceName
	private ref array<string>		name	= {}; // DisplayName
	private ref array<int>			uplevel	= {}; // UpgradeLevel
	private ref array<int>			price	= {}; // Price

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_GearData gearData;
		for (int i = 0; i < g_US_Gear.Count(); i++)
		{
			gearData = g_US_Gear[i];
			if (gearData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Gear
		// Medicine
		resname.Insert("{A81F501D3EF6F38E}Prefabs/Items/Medicine/FieldDressing_US_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		// Radios
		resname.Insert("{73950FBA2D7DB5C5}Prefabs/Items/Equipment/Radios/Radio_ANPRC68.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{9B6B61BB3FE3DFB0}Prefabs/Items/Equipment/Radios/Radio_ANPRC77.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(300);
		
		// Flashlight
		resname.Insert("{3A421547BC29F679}Prefabs/Items/Equipment/Flashlights/Flashlight_MX991.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		// Watch
		resname.Insert("{78ED4FEF62BBA728}Prefabs/Items/Equipment/Watches/Watch_SandY184A.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		// Compass
		resname.Insert("{61D4F80E49BF9B12}Prefabs/Items/Equipment/Compass/Compass_SY183.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);

		// Bino
		resname.Insert("{0CF54B9A85D8E0D4}Prefabs/Items/Equipment/Binoculars/Binoculars_M22.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(150);
		
		// Backpack
		resname.Insert("{06B68C58B72EAAC6}Prefabs/Items/Equipment/Backpacks/Backpack_ALICE_Medium.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{5C5C6EE05EE2FF1A}Prefabs/Items/Equipment/Backpacks/Backpack_ALICE_Medium_assembled.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{841162A79157C494}Prefabs/Items/Equipment/Backpacks/Backpack_ALICE_Medium_frame.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);

		// Bayonet
		resname.Insert("{A4AF9C38A4179880}Prefabs/Weapons/Attachments/Bayonets/Bayonet_M9.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(50);
		
		// Rifles
		resname.Insert("{3E413771E1834D2F}Prefabs/Weapons/Rifles/M16/Rifle_M16A2.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{5A987A8A13763769}Prefabs/Weapons/Rifles/M16/Rifle_M16A2_M203.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(300);
		
		resname.Insert("{B31929F65F0D0279}Prefabs/Weapons/Rifles/M14/Rifle_M21.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(300);
		
		resname.Insert("{81EB948E6414BD6F}Prefabs/Weapons/Rifles/M14/Rifle_M21_ARTII.et");
		name.Insert("");
		uplevel.Insert(2);
		price.Insert(400);
		
		// Machineguns
		resname.Insert("{D2B48DEBEF38D7D7}Prefabs/Weapons/MachineGuns/M249/MG_M249.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(500);
		
		resname.Insert("{D182DCDD72BF7E34}Prefabs/Weapons/MachineGuns/M60/MG_M60.et");
		name.Insert("");
		uplevel.Insert(2);
		price.Insert(700);

		// Handgun
		resname.Insert("{1353C6EAD1DCFE43}Prefabs/Weapons/Handguns/M9/Handgun_M9.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		// Grenades
		resname.Insert("{E8F00BF730225B00}Prefabs/Weapons/Grenades/Grenade_M67.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{9DB69176CEF0EE97}Prefabs/Weapons/Grenades/Smoke_ANM8HC.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);

		// Launcher
		resname.Insert("{9C5C20FB0E01E64F}Prefabs/Weapons/Launchers/M72/Launcher_M72A3.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(450);
		
		// Mags
		resname.Insert("{9C05543A503DB80E}Prefabs/Weapons/Magazines/Magazine_9x19_M9_15rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(10);
		
		resname.Insert("{2EBF60EF24B108FC}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{D8F2CA92583B23D3}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Last_5Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);

		resname.Insert("{A9A385FE1F7BF4BD}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{627255315038152A}Prefabs/Weapons/Magazines/Magazine_762x51_M14_20rnd_SpecialBall.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{982F5BA41A3738CF}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{4D2C1E8F3A81F894}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_4Ball_1Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{AD8AB93729348C3E}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{75632A0CA07D3817}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_AP.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{AAF51CFA75A9CF8B}Prefabs/Weapons/Magazines/Box_762x51_M60_100rnd_4AP_1Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{4FCBBDF274FD2157}Prefabs/Weapons/Magazines/Box_556x45_M249_200rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		resname.Insert("{06D722FC2666EB83}Prefabs/Weapons/Magazines/Box_556x45_M249_200rnd_4Ball_1Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		resname.Insert("{4EEDDB27C023B8B9}Prefabs/Weapons/Magazines/Box_556x45_M249_200rnd_Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		// Rocket
		resname.Insert("{79FA751EEBE25DDE}Prefabs/Weapons/Ammo/Ammo_Rocket_M72A3.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(100);
		
		// GL ammo
		resname.Insert("{5375FA7CB1F68573}Prefabs/Weapons/Ammo/Ammo_Grenade_HE_M406.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(50);
		
		// Boot
		resname.Insert("{DAAFD15478BDE1C3}Prefabs/Characters/Footwear/CombatBoots_US_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		// Helmet and hat
		resname.Insert("{E12126CDE731EED5}Prefabs/Characters/HeadGear/Hat_Boonie_US_01/Hat_Boonie_US_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{B74A4FF0DD8BB116}Prefabs/Characters/HeadGear/Helmet_PASGT_01/Helmet_PASGT_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{FE5C49069C2499D9}Prefabs/Characters/HeadGear/Helmet_PASGT_01/Helmet_PASGT_01_cover.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{E685A8D337D36204}Prefabs/Characters/HeadGear/Helmet_PASGT_01/Helmet_PASGT_01_cover_w_goggles.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{03C1F3DB6BB9796A}Prefabs/Characters/HeadGear/Helmet_PASGT_01/Helmet_PASGT_01_cover_w_scrim.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		// Uniform
		resname.Insert("{C7861F11D5334C0E}Prefabs/Characters/Uniforms/Jacket_US_BDU.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		// Vests
		resname.Insert("{0BC230E08CEA02B6}Prefabs/Characters/Vests/Vest_ALICE/Vest_ALICE_belt.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(10);
		
		resname.Insert("{4B57C11AA5161760}Prefabs/Characters/Vests/Vest_PASGT/Vest_PASGT.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
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
                    if (meshComponent.GetClassName() == "WeaponComponent" || meshComponent.GetClassName() == "InventoryItemComponent")
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
			store.setData(resname[i], name[i], uplevel[i], price[i]);
			
			g_US_Gear.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_GearUS()
	{
		fillUp();
		setDisplayNames();
		setGear();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GearUS()
	{
		g_US_Gear.Clear();
		g_US_Gear = null;
	}
};