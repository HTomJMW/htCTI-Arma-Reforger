[EntityEditorProps(category: "GameScripted/CTI", description: "CTI US Units")]
class SCR_CTI_UnitsUS
{
	// US units
	FactionKey factionKey = "US";
	ref array<ref SCR_CTI_UnitData> g_US_Units = new array<ref SCR_CTI_UnitData>;

	private ref array<ResourceName> res  =  {};	// ResourceName
	private ref array<string>		pic	 =  {};	// Picture
	private ref array<string>		name =  {};	// Name
	private ref array<int>			pri  =  {};	// Price
	private ref array<int>			bt   =  {};	// Build Time
	private ref array<int>			ul   =  {};	// Upgrade Level
	private ref array<string>		fac  =  {};	// Factory
	private ref array<string>		scr  =  {};	// Script

	//------------------------------------------------------------------------------------------------
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_UnitData unitData;
		for (int i = 0; i < g_US_Units.Count(); i++)
		{
			unitData = g_US_Units[i];
			if (unitData.getRes() == resName) return i;
		}
		
		return -1;
	}

	//------------------------------------------------------------------------------------------------
	void fillUp()
	{
		// Equipment box
		res.Insert("{0FC1D6E9B592F75D}Prefabs/Systems/Arsenal/AmmoBoxes/US/AmmoBoxArsenal_Equipment_US.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(500);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		// Soldiers
		res.Insert("{2F912ED6E399FF47}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Unarmed.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(75);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{E45F1E163F5CA080}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_SL.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(120);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{E398E44759DA1A43}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_TL.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(120);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{26A9756790131354}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Rifleman.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(100);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{5B1996C05B1E51A4}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_AR.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(150);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{1623EA3AEFACA0E4}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_MG.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(150);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{27BF1FF235DD6036}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_LAT.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(200);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{0F6689B491641155}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Sniper.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(200);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{84029128FA6F6BB9}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_GL.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(120);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{3726077BE60962FF}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_RTO.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(100);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{1CA3D30464EE4674}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_Spotter.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(100);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{6058AB54781A0C52}Prefabs/Characters/Factions/BLUFOR/US_Army/Character_US_AMG.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(110);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		// Vehicles
		res.Insert("{F649585ABB3706C4}Prefabs/Vehicles/Wheeled/M151A2/M151A2.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(700);
		bt.Insert(20);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{47D94E1193A88497}Prefabs/Vehicles/Wheeled/M151A2/M151A2_transport.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(750);
		bt.Insert(20);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{F6B23D17D5067C11}Prefabs/Vehicles/Wheeled/M151A2/M151A2_M2HB.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(900);
		bt.Insert(30);
		ul.Insert(1);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{F1FBD0972FA5FE09}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1200);
		bt.Insert(30);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{81FDAD5EB644CC3D}Prefabs/Vehicles/Wheeled/M923A1/M923A1_transport_covered.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1300);
		bt.Insert(30);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{2BE1F8B9299B67C1}Prefabs/Vehicles/Wheeled/M923A1/M923A1_tanker.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1500);
		bt.Insert(30);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{36BDCC88B17B3BFA}Prefabs/Vehicles/Wheeled/M923A1/M923A1_command.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(20000);
		bt.Insert(60);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{4A71F755A4513227}Prefabs/Vehicles/Wheeled/M998/M1025.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1000);
		bt.Insert(45);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{3EA6F47D95867114}Prefabs/Vehicles/Wheeled/M998/M1025_armed_M2HB.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1500);
		bt.Insert(45);
		ul.Insert(1);
		fac.Insert("");
		scr.Insert("");
	}

	//------------------------------------------------------------------------------------------------
	void init()
	{
		fillUp();
		setUnits();
	}

	//------------------------------------------------------------------------------------------------
	void setUnits()
	{
		SCR_CTI_UnitData store;
		for (int i = 0; i < res.Count(); i++)
		{
			store = new SCR_CTI_UnitData;
			store.setData(res[i], pic[i], name[i], pri[i], bt[i], ul[i], fac[i], scr[i]);
			
			g_US_Units.Insert(store);
		}
	}
};