[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Constants")]
class SCR_CTI_Constants
{
	// Global constants
	static const int VEHICLECOLLECTIONTIME = 3600;
	static const int ITEMCOLLECTIONTIME = 3600;
	static const int PLAYERGROUPSIZE = 8;
	static const int MAXBASES = 2;
	static const int BASERADIUS = 100;
	static const int BUILDRANGE = 100;
	static const int SERVICERANGE = 70;
	static const int WORKERSLIMIT = 10;
	static const int WORKERPRICE = 300;
	static const bool ECOWIN = true;
	static const int WINRATE = 75;
	static const int CAPTURERANGE = 75;
	static const int ACTIVATIONRANGE = 500;
	static const int ACTIVATIONRANGEAIR = 50;
	static const int INACTIVATIONTIME = 180;
	static const int RECAPTUREDELAY = 180;
	static const int STARTFUNDS = 2400;
	static const int STARTCOMMFUNDS = 7500;
	static const int MHQREPAIRCOST = 20000;
	static const int BASEINCOME = 50;
	static const float AISKILL = 0.75;
	static const int MAXVD = 4000;
	static const int MINVD = 2500;
	static const int MAXTG = 150;
	static const int MINTG = 80;
	
	// Colors
	static const ref Color CTI_ORANGE = new Color(1.000000, 0.456336, 0.000000, 1.000000);
	
	// General ResouceNames
	static const ResourceName USSR_WORKER = "{98EB9CDD85B8C92C}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Unarmed.et";
	static const ResourceName US_WORKER = "{2F912ED6E399FF47}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Unarmed.et";
	static const ResourceName USSR_MHQ = "{1BABF6B33DA0AEB6}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_command.et";
	static const ResourceName US_MHQ = "{36BDCC88B17B3BFA}Prefabs/Vehicles/Wheeled/M923A1/M923A1_command.et";
	static const ResourceName USSR_BOX = "{B728C4AE0E6EB1E8}Prefabs/Systems/Arsenal/AmmoBoxes/USSR/AmmoBoxArsenal_Equipment_USSR.et";
	static const ResourceName US_BOX = "{0FC1D6E9B592F75D}Prefabs/Systems/Arsenal/AmmoBoxes/US/AmmoBoxArsenal_Equipment_US.et";
	static const ResourceName USSR_SOLDIER = "{DCB41B3746FDD1BE}Prefabs/Characters/Factions/OPFOR/USSR_Army/Character_USSR_Rifleman.et";
	static const ResourceName US_SOLDIER = "{26A9756790131354}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Rifleman.et";
	static const ResourceName USSR_UAZ = "{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et";
	static const ResourceName US_JEEP = "{47D94E1193A88497}Prefabs/Vehicles/Wheeled/M151A2/M151A2_transport.et";
	
	// Radios
	static const ResourceName USSR_RADIO1 = "{E1A5D4B878AA8980}Prefabs/Items/Equipment/Radios/Radio_R148.et"; // start equipment
	static const ResourceName USSR_RADIO2 = "{54C68E438DD34265}Prefabs/Items/Equipment/Radios/Radio_R107M.et";
	static const ResourceName US_RADIO1 = "{73950FBA2D7DB5C5}Prefabs/Items/Equipment/Radios/Radio_ANPRC68.et"; // start equipment
	static const ResourceName US_RADIO2 = "{9B6B61BB3FE3DFB0}Prefabs/Items/Equipment/Radios/Radio_ANPRC77.et";

	// USSR equipment
	static const ResourceName USSR_BANDAGE = "{C3F1FA1E2EC2B345}Prefabs/Items/Medicine/FieldDressing_USSR_01.et";
	static const ResourceName USSR_AK_MAG = "{0A84AA5A3884176F}Prefabs/Weapons/Magazines/Magazine_545x39_AK_30rnd_Last_5Tracer.et";
	static const ResourceName USSR_RPG7 = "{7A82FE978603F137}Prefabs/Weapons/Launchers/RPG7/Launcher_RPG7.et";
	static const ResourceName USSR_RPG7_AMMO = "{32E12D322E107F1C}Prefabs/Weapons/Ammo/Ammo_Rocket_PG7VM.et";
	static const ResourceName USSR_GRENADE = "{645C73791ECA1698}Prefabs/Weapons/Grenades/Grenade_RGD5.et";
	static const ResourceName USSR_PM = "{C0F7DD85A86B2900}Prefabs/Weapons/Handguns/PM/Handgun_PM.et";
	static const ResourceName USSR_PM_MAG = "{8B853CDD11BA916E}Prefabs/Weapons/Magazines/Magazine_9x18_PM_8rnd_Ball.et";

	// US equipment	
	static const ResourceName US_BANDAGE = "{A81F501D3EF6F38E}Prefabs/Items/Medicine/FieldDressing_US_01.et";
	static const ResourceName US_M16_MAG = "{D8F2CA92583B23D3}Prefabs/Weapons/Magazines/Magazine_556x45_STANAG_30rnd_Last_5Tracer.et";
	static const ResourceName US_M72 = "{9C5C20FB0E01E64F}Prefabs/Weapons/Launchers/M72/Launcher_M72A3.et";
	static const ResourceName US_GRENADE = "{E8F00BF730225B00}Prefabs/Weapons/Grenades/Grenade_M67.et";
	static const ResourceName US_M9 = "{1353C6EAD1DCFE43}Prefabs/Weapons/Handguns/M9/Handgun_M9.et";
	static const ResourceName US_M9_MAG = "{9C05543A503DB80E}Prefabs/Weapons/Magazines/Magazine_9x19_M9_15rnd_Ball.et";
	
	// Town Units
	static const ResourceName FIA_FireTeam = "{5BEA04939D148B1D}Prefabs/Groups/INDFOR/Group_FIA_FireTeam.et";
	static const ResourceName FIA_MGTeam = "{22F33D3EC8F281AB}Prefabs/Groups/INDFOR/Group_FIA_MachineGunTeam.et";
	static const ResourceName FIA_MedicalSection = "{581106FA58919E89}Prefabs/Groups/INDFOR/Group_FIA_MedicalSection.et";
	static const ResourceName FIA_PlatoonHQ = "{EE92725E9B949C3D}Prefabs/Groups/INDFOR/Group_FIA_PlatoonHQ.et";
	static const ResourceName FIA_ReconTeam = "{2E9C920C3ACA2C6F}Prefabs/Groups/INDFOR/Group_FIA_ReconTeam.et";
	static const ResourceName FIA_RifleSquad = "{CE41AF625D05D0F0}Prefabs/Groups/INDFOR/Group_FIA_RifleSquad.et";
	static const ResourceName FIA_SniperTeam = "{6307F42403E9B8A4}Prefabs/Groups/INDFOR/Group_FIA_SharpshooterTeam.et";
	static const ResourceName FIA_ATTeam = "{2CC26054775FBA2C}Prefabs/Groups/INDFOR/Group_FIA_Team_AT.et";

	static const ResourceName USSR_FireGroup = "{30ED11AA4F0D41E5}Prefabs/Groups/OPFOR/Group_USSR_FireGroup.et";
	static const ResourceName USSR_LightFireTeam = "{657590C1EC9E27D3}Prefabs/Groups/OPFOR/Group_USSR_LightFireTeam.et";
	static const ResourceName USSR_MGTeam = "{A2F75E45C66B1C0A}Prefabs/Groups/OPFOR/Group_USSR_MachineGunTeam.et";
	static const ResourceName USSR_ManeuverGroup = "{1A5F0D93609DA5DA}Prefabs/Groups/OPFOR/Group_USSR_ManeuverGroup.et";
	static const ResourceName USSR_MedicalSection = "{D815658156080328}Prefabs/Groups/OPFOR/Group_USSR_MedicalSection.et";
	static const ResourceName USSR_RifleSquad = "{E552DABF3636C2AD}Prefabs/Groups/OPFOR/Group_USSR_RifleSquad.et";
	static const ResourceName USSR_SentryTeam = "{CB58D90EA14430AD}Prefabs/Groups/OPFOR/Group_USSR_SentryTeam.et";
	static const ResourceName USSR_GLTeam = "{43C7A28EEB660FF8}Prefabs/Groups/OPFOR/Group_USSR_Team_GL.et";
	static const ResourceName USSR_ATTeam = "{96BAB56E6558788E}Prefabs/Groups/OPFOR/Group_USSR_Team_AT.et";
	static const ResourceName USSR_SuppressTeam = "{1C0502B5729E7231}Prefabs/Groups/OPFOR/Group_USSR_Team_Suppress.et";
	
	static const ResourceName USSR_BTR70 = "{C012BB3488BEA0C2}Prefabs/Vehicles/Wheeled/BTR70/BTR70.et";

	static const ResourceName US_FireTeam = "{84E5BBAB25EA23E5}Prefabs/Groups/BLUFOR/Group_US_FireTeam.et";
	static const ResourceName US_LightFireTeam = "{FCF7F5DC4F83955C}Prefabs/Groups/BLUFOR/Group_US_LightFireTeam.et";
	static const ResourceName US_MGTeam = "{958039B857396B7B}Prefabs/Groups/BLUFOR/Group_US_MachineGunTeam.et";
	static const ResourceName US_MedicalSection = "{EF62027CC75A7459}Prefabs/Groups/BLUFOR/Group_US_MedicalSection.et";
	static const ResourceName US_RifleSquad = "{DDF3799FA1387848}Prefabs/Groups/BLUFOR/Group_US_RifleSquad.et";
	static const ResourceName US_SentryTeam = "{3BF36BDEEB33AEC9}Prefabs/Groups/BLUFOR/Group_US_SentryTeam.et";
	static const ResourceName US_SniperTeam = "{D807C7047E818488}Prefabs/Groups/BLUFOR/Group_US_SniperTeam.et";
	static const ResourceName US_GLTeam = "{DE747BC9217D383C}Prefabs/Groups/BLUFOR/Group_US_Team_GL.et";
	static const ResourceName US_ATTeam = "{FAEA8B9E1252F56E}Prefabs/Groups/BLUFOR/Group_US_Team_LAT.et";
	static const ResourceName US_SuppressTeam = "{81B6DBF2B88545F5}Prefabs/Groups/BLUFOR/Group_US_Team_Suppress.et";
	
	static const ResourceName US_M1025_M2 = "{3EA6F47D95867114}Prefabs/Vehicles/Wheeled/M998/M1025_armed_M2HB.et";
};