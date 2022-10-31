[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Base handler")]
class SCR_CTI_BaseComponentClass : ScriptComponentClass
{
};

class SCR_CTI_BaseComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	//protected float m_timeDelta;
	//protected const float TIMESTEP = 5;
	
	ref array<SCR_CTI_Base> ussrBases = {};
	ref array<SCR_CTI_Base> usBases = {};

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetOwner());
	}

	//------------------------------------------------------------------------------------------------
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
				}
				break;
			}
		}
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