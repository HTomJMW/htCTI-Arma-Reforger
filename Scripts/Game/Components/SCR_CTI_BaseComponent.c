[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Base handler")]
class SCR_CTI_BaseComponentClass : ScriptComponentClass
{
};

class SCR_CTI_BaseComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	//protected float m_timeDelta;
	//protected const float TIMESTEP = 5;

	[RplProp()]
	protected int ussrBaseCount = 0;
	[RplProp()]
	protected int usBaseCount = 0;

	protected ref array<ref SCR_CTI_Base> ussrBases = {};
	protected ref array<ref SCR_CTI_Base> usBases = {};
	
	[RplProp()]
	protected ref array<ref EntityID> ussrStructureIDs = {};
	[RplProp()]
	protected ref array<ref EntityID> usStructureIDs = {};

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetOwner());
	}

	//------------------------------------------------------------------------------------------------
	// Only on server
	void addBase(FactionKey factionkey, vector position, int baseId)
	{
		SCR_CTI_Base base = new SCR_CTI_Base();
		switch (factionkey)
		{
			case "USSR":
			{
				if (ussrBases.Count() < m_gameMode.MAXBASES)
				{
					base.setBaseFactionKey(factionkey);
					base.setBaseId(baseId);
					base.setBasePos(position);
					
					ussrBases.Insert(base);
					ussrBaseCount = ussrBases.Count();
				}
				break;
			}
			case "US":
			{
				if (usBases.Count() < m_gameMode.MAXBASES)
				{
					base.setBaseFactionKey(factionkey);
					base.setBaseId(baseId);
					base.setBasePos(position);
					
					usBases.Insert(base);
					usBaseCount = usBases.Count();
				}
				break;
			}
		}
		Replication.BumpMe();
		createBaseMarker(position, factionkey);
	}

	//------------------------------------------------------------------------------------------------
	protected void createBaseMarker(vector position, FactionKey factionkey)
	{
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		params.Transform[3] = position;
		
		ResourceName resname;
		if (factionkey == "USSR")
		{
			resname = "{D6EE5AB2287665DB}Prefabs/Markers/CTI_BaseMarkerUSSR.et";
		} else {
			resname = "{F1601BFC409D50E7}Prefabs/Markers/CTI_BaseMarkerUS.et";
		}
		Resource res = Resource.Load(resname);
		
		GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), params);
	}

	//------------------------------------------------------------------------------------------------
	protected void createStructureMarker(vector position, FactionKey factionkey, IEntity structure)
	{
		// TODO
	}

	//------------------------------------------------------------------------------------------------
	int getBaseCount(FactionKey factionkey)
	{
		int result = 0;
		switch (factionkey)
		{
			case "USSR":
			{
				result = ussrBaseCount;
				break;
			}
			case "US":
			{
				result = usBaseCount;
				break;
			}
		}
		
		return result;
	}
	
	//------------------------------------------------------------------------------------------------
	float getAreaDistances(vector base1, vector base2)
	{
		float dist= -1;
		dist = vector.DistanceXZ(base1, base2);

		return dist;
	}

	//------------------------------------------------------------------------------------------------
	// maybe need basecount check for baseid/index
	SCR_CTI_Base getBase(FactionKey factionkey, int baseId)
	{
		SCR_CTI_Base base;
		switch (factionkey)
		{
			case "USSR":
			{
				base = ussrBases[baseId];
				break;
			}
			case "US":
			{
				base = usBases[baseId];
				break;
			}
		}
		
		return base;
	}

	//------------------------------------------------------------------------------------------------
	void addStuctureId(FactionKey factionkey, EntityID id)
	{
		switch (factionkey)
		{
			case "USSR":
			{
				ussrStructureIDs.Insert(id);
				break;
			}
			case "US":
			{
				usStructureIDs.Insert(id);
				break;
			}
		}
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref EntityID> getUSSRStructureIdArray()
	{
		return ussrStructureIDs;
	}
	
	//------------------------------------------------------------------------------------------------
	array<ref EntityID> getUSStructureIdArray()
	{
		return usStructureIDs;
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		//m_timeDelta += timeSlice;
		/*if (m_timeDelta > TIMESTEP)
		{
			Print("SERVER 5s LOOP");
			
			m_timeDelta = 0;
		}*/
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BaseComponent()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BaseComponent()
	{
		ussrBases.Clear();
		ussrBases = null;
		usBases.Clear();
		usBases = null;
		ussrStructureIDs.Clear();
		ussrStructureIDs = null;
		usStructureIDs.Clear();
		usStructureIDs = null;
	}
};