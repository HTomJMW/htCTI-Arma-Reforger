[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Player Resources")]
class SCR_CTI_UpdateResourcesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateResourcesComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 45; // economy cycle

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				int CDA = m_gameMode.ClientDataArray.Count();
				for (int i = 0; i < CDA; i++)
				{
					SCR_CTI_ClientData clientData = m_gameMode.ClientDataArray[i];
					if (clientData) clientData.changeFunds(m_gameMode.BASEINCOME);	
				}
			
				m_gameMode.bumpMeServer();

				m_timeDelta = 0;
			}
	}

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		
		m_timeDelta = 0;
	}
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_UpdateResourcesComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpdateResourcesComponent()
	{
	}	
};