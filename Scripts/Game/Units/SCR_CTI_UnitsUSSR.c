[EntityEditorProps(category: "GameScripted/CTI", description: "CTI USSR Units")]
class SCR_CTI_UnitsUSSR
{
	// USSR units
	FactionKey factionKey = "USSR";
	ref array<ref SCR_CTI_UnitData> g_USSR_Units = new array<ref SCR_CTI_UnitData>;

	private ref array<ResourceName> res  =  {};	// ResourceName
	private ref array<string>		pic	 =  {};	// Picture
	private ref array<string>		name =  {};	// Name
	private ref array<int>			pri  =  {};	// Price
	private ref array<int>			bt   =  {};	// Build Time
	private ref array<int>			ul   =  {};	// Upgrade Level
	private ref array<string>		fac  =  {};	// Factory
	private ref array<string>		scr  =  {};	// Script
	
	int findIndexFromResourcename(ResourceName resName)
	{
		SCR_CTI_UnitData unitData;
		for (int i = 0; i < g_USSR_Units.Count(); i++)
		{
			unitData = g_USSR_Units[i];
			if (unitData.getRes() == resName) return i;
		}
		
		return -1;
	}
	
	void fillUp()
	{
		// Soldiers
		res.Insert("NONE");
		pic.Insert("");
		name.Insert("");
		pri.Insert(200);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		// Vehicles
		res.Insert("{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(700);
		bt.Insert(20);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{16C1F16C9B053801}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1200);
		bt.Insert(30);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{D9B91FAB817A6033}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_transport_covered.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1300);
		bt.Insert(30);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{4C81D7ED8F8C0D87}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_tanker.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(1500);
		bt.Insert(30);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{1BABF6B33DA0AEB6}Prefabs/Vehicles/Wheeled/Ural4320/Ural4320_command.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(20000);
		bt.Insert(60);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{C012BB3488BEA0C2}Prefabs/Vehicles/Wheeled/BTR70/BTR70.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(2500);
		bt.Insert(45);
		ul.Insert(1);
		fac.Insert("");
		scr.Insert("");
	}
	
	void init()
	{
		fillUp();
		setUnits();
	}

	void setUnits()
	{
		SCR_CTI_UnitData store;
		for (int i = 0; i < res.Count(); i++)
		{
			store = new SCR_CTI_UnitData;
			store.setData(res[i], pic[i], name[i], pri[i], bt[i], ul[i], fac[i], scr[i]);
			
			g_USSR_Units.Insert(store);
		}
	}
};