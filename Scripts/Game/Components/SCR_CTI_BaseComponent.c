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
	
	ref array<SCR_CTI_Base> ussrBases = {};
	ref array<SCR_CTI_Base> usBases = {};

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetOwner());
	}

	//------------------------------------------------------------------------------------------------
	// Only on server
	void addBase(FactionKey factionkey, vector position, int baseId)
	{
		switch (factionkey)
		{
			case "USSR":
			{
				if (ussrBases.Count() < m_gameMode.MAXBASES)
				{
					SCR_CTI_Base base = new SCR_CTI_Base();
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
					SCR_CTI_Base base = new SCR_CTI_Base();
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
	void markBase(FactionKey sidekey, int baseId)
	{
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
	}
};