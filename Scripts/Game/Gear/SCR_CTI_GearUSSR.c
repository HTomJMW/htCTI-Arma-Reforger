[EntityEditorProps(category: "GameScripted/CTI", description: "CTI USSR Gear")]
class SCR_CTI_GearUSSR
{
	// USSR gear
	FactionKey factionKey = "USSR";
	ref array<ref SCR_CTI_GearData> g_USSR_Gear = new array<ref SCR_CTI_GearData>;

	private ref array<ResourceName> resname = {}; // ResourceName
	private ref array<string>		name	= {}; // DisplayName
	private ref array<int>			uplevel = {}; // UpgradeLevel
	private ref array<int>			price	= {}; // Price

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_GearData gearData;
		for (int i = 0; i < g_USSR_Gear.Count(); i++)
		{
			gearData = g_USSR_Gear[i];
			if (gearData.getResname() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	private void fillUp()
	{
		// Gear
		// Medicine
		resname.Insert("{C3F1FA1E2EC2B345}Prefabs/Items/Medicine/FieldDressing_USSR_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		// Radios
		resname.Insert("{E1A5D4B878AA8980}Prefabs/Items/Equipment/Radios/Radio_R148.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{54C68E438DD34265}Prefabs/Items/Equipment/Radios/Radio_R107M.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(300);
		
		// Flashlight
		resname.Insert("{575EA58E67448C2A}Prefabs/Items/Equipment/Flashlights/Flashlight_Soviet_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		// Watch
		resname.Insert("{6FD6C96121905202}Prefabs/Items/Equipment/Watches/Watch_Vostok.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		// Compass
		resname.Insert("{7CEF68E2BC68CE71}Prefabs/Items/Equipment/Compass/Compass_Adrianov.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		// Bino
		resname.Insert("{F2539FA5706E51E4}Prefabs/Items/Equipment/Binoculars/Binoculars_B12.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(150);
		
		// Backpack
		resname.Insert("{6A39B5843B3F36DA}Prefabs/Items/Equipment/Backpacks/Backpack_RPG_Assistant.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		resname.Insert("{0D39750E5695B9D8}Prefabs/Items/Equipment/Backpacks/Backpack_RPG_Gunner.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		resname.Insert("{3DE0155EC9767B98}Prefabs/Items/Equipment/Backpacks/Backpack_Veshmeshok.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{41A9C55B61F375F0}Prefabs/Items/Equipment/Backpacks/Backpack_Kolobok.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		// Bayonet
		resname.Insert("{C7534F7A79EA3331}Prefabs/Weapons/Attachments/Bayonets/Bayonet_6Kh4.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(50);
		
		// Rifles
		resname.Insert("{FA5C25BF66A53DCF}Prefabs/Weapons/Rifles/AK74/Rifle_AK74.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(200);
		
		resname.Insert("{63E8322E2ADD4AA7}Prefabs/Weapons/Rifles/AK74/Rifle_AK74_GP25.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(300);
		
		resname.Insert("{3EB02CDAD5F23C82}Prefabs/Weapons/Rifles/SVD/Rifle_SVD.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(300);
		
		resname.Insert("{6415B7923DE28C1B}Prefabs/Weapons/Rifles/SVD/Rifle_SVD_PSO.et");
		name.Insert("");
		uplevel.Insert(2);
		price.Insert(400);
		
		// Machineguns
		resname.Insert("{A7AF84C6C58BA3E8}Prefabs/Weapons/MachineGuns/RPK74/MG_RPK74.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(500);
		
		resname.Insert("{A89BC9D55FFB4CD8}Prefabs/Weapons/MachineGuns/PKM/MG_PKM.et");
		name.Insert("");
		uplevel.Insert(2);
		price.Insert(700);
		
		// Handgun
		resname.Insert("{C0F7DD85A86B2900}Prefabs/Weapons/Handguns/PM/Handgun_PM.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(100);
		
		// Grenades
		resname.Insert("{645C73791ECA1698}Prefabs/Weapons/Grenades/Grenade_RGD5.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{77EAE5E07DC4678A}Prefabs/Weapons/Grenades/Smoke_RDG2.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);

		// Launcher
		resname.Insert("{7A82FE978603F137}Prefabs/Weapons/Launchers/RPG7/Launcher_RPG7.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(450);
		
		// Mags
		resname.Insert("{8B853CDD11BA916E}Prefabs/Weapons/Magazines/Magazine_9x18_PM_8rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(10);
		
		resname.Insert("{BBB50A815A2F916B}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{0A84AA5A3884176F}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Last_5Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{E5912E45754CD421}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{BC74DAC891D48540}Prefabs/Weapons/Magazines/Magazine_545x39_RPK_45rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		resname.Insert("{D78C667F59829717}Prefabs/Weapons/Magazines/Magazine_545x39_RPK_45rnd_4Ball_1Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		resname.Insert("{5897D01F41DB5D2D}Prefabs/Weapons/Magazines/Magazine_545x39_RPK_45rnd_Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(30);
		
		resname.Insert("{9CCB46C6EE632C1A}Prefabs/Weapons/Magazines/Magazine_762x54_SVD_10rnd_Sniper.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{1C260E65B7F290BA}Prefabs/Weapons/Magazines/Box_762x54_PK_250rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{D8421F6E70B2FB4F}Prefabs/Weapons/Magazines/Box_762x54_PK_250rnd_4Ball_1Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{B386EEE8AED8E386}Prefabs/Weapons/Magazines/Box_762x54_PK_250rnd_Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{A6737DA00653A39C}Prefabs/Weapons/Magazines/Box_762x54_PK_100rnd_Ball.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{E5E9C5897CF47F44}Prefabs/Weapons/Magazines/Box_762x54_PK_100rnd_4Ball_1Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		resname.Insert("{BEEA49E27174B224}Prefabs/Weapons/Magazines/Box_762x54_PK_100rnd_Tracer.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(40);
		
		// Rocket
		resname.Insert("{32E12D322E107F1C}Prefabs/Weapons/Ammo/Ammo_Rocket_PG7VM.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(100);
		
		// GL ammo
		resname.Insert("{262F0D09C4130826}Prefabs/Weapons/Ammo/Ammo_Grenade_HE_VOG25.et");
		name.Insert("");
		uplevel.Insert(1);
		price.Insert(50);
		
		// Boot
		resname.Insert("{C7923961D7235D70}Prefabs/Characters/Footwear/CombatBoots_Soviet_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		// Helmet and hat
		resname.Insert("{2B29B7E1C6BD1048}Prefabs/Characters/HeadGear/Hat_M88_01/Hat_M88_01_v1.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{793EEE2C133176F9}Prefabs/Characters/HeadGear/Hat_Panama_Soviet/Hat_Panama_Soviet_01_v1.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
		
		resname.Insert("{A7E6D7ECD5F684D7}Prefabs/Characters/HeadGear/Helmet_SSh68_01/Helmet_SSh68_01.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{66196D85AB93D2BE}Prefabs/Characters/HeadGear/Helmet_SSh68_01/Helmet_SSh68_01_camo.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{D4028ED16DEE99EE}Prefabs/Characters/HeadGear/Helmet_SSh68_01/Helmet_SSh68_01_camonet.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		resname.Insert("{3D74845B9D0867B0}Prefabs/Characters/HeadGear/Helmet_SSh68_01/Helmet_SSh68_01_cover.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		// Uniform
		resname.Insert("{9F546CCA2582D16F}Prefabs/Characters/Uniforms/Jacket_M88.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(50);
		
		// Vests
		resname.Insert("{9713FE6DDCC9510D}Prefabs/Characters/Vests/Vest_Lifchik/Vest_Lifchik.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(10);
		
		resname.Insert("{ED5574EA7F63B457}Prefabs/Characters/Vests/Vest_Type56/Vest_Type56.et");
		name.Insert("");
		uplevel.Insert(0);
		price.Insert(20);
	}

	//------------------------------------------------------------------------------------------------
	private void setGear()
	{
		SCR_CTI_GearData store;
		for (int i = 0; i < resname.Count(); i++)
		{
			store = new SCR_CTI_GearData;
			store.setData(resname[i], name[i], uplevel[i], price[i]);
			
			g_USSR_Gear.Insert(store);
		}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_GearUSSR()
	{
		fillUp();
		setGear();
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_GearUSSR()
	{
		g_USSR_Gear.Clear();
		g_USSR_Gear = null;
	}
};