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
	protected int ussrBaseCount = 0; // Maybe not need anymore... basemarkerid.count can do this.
	[RplProp()]
	protected int usBaseCount = 0;
	[RplProp()]
	ref array<RplId> ussrBaseMarkerRplIds = {};
	[RplProp()]
	ref array<RplId> usBaseMarkerRplIds = {};

	ref array<ref SCR_CTI_Base> ussrBases = {};
	ref array<ref SCR_CTI_Base> usBases = {};
	
	[RplProp(onRplName: "OnStructureAdded", condition: RplCondition.Custom, customConditionName: "RpcConditionMethod")]
	ref array<RplId> ussrStructureRplIds = {};
	[RplProp(onRplName: "OnStructureAdded", condition: RplCondition.Custom, customConditionName: "RpcConditionMethod")]
	ref array<RplId> usStructureRplIds = {};
	
	[RplProp(onRplName: "OnStructureAdded", condition: RplCondition.Custom, customConditionName: "RpcConditionMethod")]
	ref array<RplId> ussrWIPStructureRplIds = {};
	[RplProp(onRplName: "OnStructureAdded", condition: RplCondition.Custom, customConditionName: "RpcConditionMethod")]
	ref array<RplId> usWIPStructureRplIds = {};

	//------------------------------------------------------------------------------------------------
	bool RpcConditionMethod()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	// Proxys
	void OnStructureAdded()
	{
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
			
			RplComponent rplComp = RplComponent.Cast(baseMarker.FindComponent(RplComponent));
			if (rplComp)
			{
				RplId rplid = rplComp.Id();
				switch (factionkey)
				{
					case "USSR":ussrBaseMarkerRplIds.Insert(rplid); break;
					case "US": usBaseMarkerRplIds.Insert(rplid); break;
				}
				
				Replication.BumpMe();
			}
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
	void addWIPStuctureRplId(FactionKey factionkey, RplId rplid)
	{
		switch (factionkey)
		{
			case "USSR": ussrWIPStructureRplIds.Insert(rplid); break;
			case "US": usWIPStructureRplIds.Insert(rplid); break;
		}

		Replication.BumpMe();
	}
	
	void removeWIPStructureRplId(FactionKey factionkey, RplId rplid)
	{
		switch (factionkey)
		{
			case "USSR": ussrWIPStructureRplIds.RemoveItem(rplid); break;
			case "US": usWIPStructureRplIds.RemoveItem(rplid); break;
		}

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	// Only on server
	void deleteObject(FactionKey factionkey, RplId rplid)
	{
		RplComponent rplComp = RplComponent.Cast(Replication.FindItem(rplid));
		IEntity object = rplComp.GetEntity();
		
		switch (factionkey)
		{
			case "USSR":
			{
				if (ussrWIPStructureRplIds.Contains(rplid))
				{
					ussrWIPStructureRplIds.RemoveItem(rplid);
					break;
				}
				
				if (ussrStructureRplIds.Contains(rplid))
				{
					ussrStructureRplIds.RemoveItem(rplid);
					break;
				}
			}
			case "US":
			{
				if (usWIPStructureRplIds.Contains(rplid))
				{
					usWIPStructureRplIds.RemoveItem(rplid);
					break;
				}
				
				if (usStructureRplIds.Contains(rplid))
				{
					usStructureRplIds.RemoveItem(rplid);
					break;
				}
			}
		}
		
		Replication.BumpMe();
		
		SCR_EntityHelper.DeleteEntityAndChildren(object);
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
	void ~SCR_CTI_BaseComponent()
	{
		if (ussrBases) ussrBases.Clear();
		ussrBases = null;
		if (usBases) usBases.Clear();
		usBases = null;
		if (ussrStructureRplIds) ussrStructureRplIds.Clear();
		ussrStructureRplIds = null;
		if (usStructureRplIds) usStructureRplIds.Clear();
		usStructureRplIds = null;
		if (ussrWIPStructureRplIds) ussrWIPStructureRplIds.Clear();
		ussrWIPStructureRplIds = null;
		if (usWIPStructureRplIds) usWIPStructureRplIds.Clear();
		usWIPStructureRplIds = null;
	}
};