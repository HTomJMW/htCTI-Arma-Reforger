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
	
	[RplProp(onRplName: "OnStructureAdded", condition: RplCondition.Custom, customConditionName: "RpcConditionMethod")]
	protected ref array<RplId> ussrStructureRplIds = {};
	[RplProp(onRplName: "OnStructureAdded", condition: RplCondition.Custom, customConditionName: "RpcConditionMethod")]
	protected ref array<RplId> usStructureRplIds = {};

	//------------------------------------------------------------------------------------------------
	bool RpcConditionMethod()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	// Proxys
	void OnStructureAdded()
	{
		GetGame().GetCallqueue().CallLater(delayedCall, 1000, false);
	}

	//------------------------------------------------------------------------------------------------
	protected void delayedCall()
	{
		RplComponent rplComp;
		IEntity struct;

		int last = ussrStructureRplIds.Count();
		if (last > 0)
		{
			last = last - 1;
			rplComp = RplComponent.Cast(Replication.FindItem(ussrStructureRplIds[last]));
			struct = rplComp.GetEntity();
			struct.Update();
		}

		last = usStructureRplIds.Count();
		if (last > 0)
		{
			last = last - 1;
			rplComp = RplComponent.Cast(Replication.FindItem(usStructureRplIds[last]));
			struct = rplComp.GetEntity();
			struct.Update();
		}
	}

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
				if (ussrBases.Count() < SCR_CTI_Constants.MAXBASES)
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
				if (usBases.Count() < SCR_CTI_Constants.MAXBASES)
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
		
		ResourceName resname = "{D6EE5AB2287665DB}Prefabs/Markers/CTI_BaseMarker.et";
		Resource res = Resource.Load(resname);
		
		IEntity marker = GetGame().SpawnEntityPrefab(res, GetGame().GetWorld(), params);

		if (marker)
		{
			SCR_CTI_BaseMarker baseMarker = SCR_CTI_BaseMarker.Cast(marker);
			baseMarker.setOwnerFaction(factionkey);
		}
	}

	//------------------------------------------------------------------------------------------------
	int getBaseCount(FactionKey factionkey)
	{
		int result;

		switch (factionkey)
		{
			case "USSR": result = ussrBaseCount; break;
			case "US": result = usBaseCount; break;
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
			case "USSR": base = ussrBases[baseId]; break;
			case "US": base = usBases[baseId]; break;
		}
		
		return base;
	}

	//------------------------------------------------------------------------------------------------
	void addStuctureRplId(FactionKey factionkey, RplId rplid)
	{
		switch (factionkey)
		{
			case "USSR": ussrStructureRplIds.Insert(rplid); break;
			case "US": usStructureRplIds.Insert(rplid); break;
		}

		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	array<RplId> getUSSRStructureRplIdArray()
	{
		return ussrStructureRplIds;
	}
	
	//------------------------------------------------------------------------------------------------
	array<RplId> getUSStructureRplIdArray()
	{
		return usStructureRplIds;
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		//m_timeDelta += timeSlice;
		/*if (m_timeDelta > TIMESTEP)
		{
			//TODO
			
			m_timeDelta = 0;
		}*/
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		//SetEventMask(owner, EntityEvent.FIXEDFRAME);
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
		ussrStructureRplIds.Clear();
		ussrStructureRplIds = null;
		usStructureRplIds.Clear();
		usStructureRplIds = null;
	}
};