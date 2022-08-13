[EntityEditorProps(category: "GameScripted/CTI", description: "CTI FIA Units")]
class SCR_CTI_UnitsFIA
{
	// FIA units
	FactionKey factionKey = "FIA";
	ref array<ref SCR_CTI_UnitData> g_FIA_Units = new array<ref SCR_CTI_UnitData>;

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
		for (int i = 0; i < g_FIA_Units.Count(); i++)
		{
			unitData = g_FIA_Units[i];
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
			
			g_FIA_Units.Insert(store);
		}
	}
};