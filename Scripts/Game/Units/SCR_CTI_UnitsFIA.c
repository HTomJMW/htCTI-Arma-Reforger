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

	//------------------------------------------------------------------------------------------------
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

	//------------------------------------------------------------------------------------------------
	void fillUp()
	{
		// Equipment box
		res.Insert("{7F1A910F6EA32A82}Prefabs/Systems/Arsenal/AmmoBoxes/FIA/AmmoBoxArsenal_Equipment_FIA.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(500);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		// Soldiers
		res.Insert("{854C04F0EA2129CC}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Unarmed.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(75);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{677B515F119222C2}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_SL.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(120);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{84B40583F4D1B7A3}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Rifleman.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(100);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{58E47E5A4D599432}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_MG.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(150);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{D25BC9815A9F9E8D}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_AT.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(200);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{CE33AB22F61F3365}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Sharpshooter.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(200);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{BF1E43FF39AA526B}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_Scout.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(100);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{23D81C023DBF85AC}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_RTO.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(100);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{FE65E8C60C751352}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_PL.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(100);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{75FC25863194612A}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_AMG.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(110);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
		
		res.Insert("{FF43925D26526B95}Prefabs/Characters/Factions/INDFOR/FIA/Character_FIA_AAT.et");
		pic.Insert("");
		name.Insert("");
		pri.Insert(110);
		bt.Insert(10);
		ul.Insert(0);
		fac.Insert("");
		scr.Insert("");
	}

	//------------------------------------------------------------------------------------------------
	void init()
	{
		fillUp();
		setDisplayNames();
		setUnits();
	}

	//------------------------------------------------------------------------------------------------
	void setDisplayNames()
	{
		for (int i = 0; i < res.Count(); i++)
		{
			//todo get display names from uiinfo - EntityInfo better maybe?
		}
	}

	//------------------------------------------------------------------------------------------------
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