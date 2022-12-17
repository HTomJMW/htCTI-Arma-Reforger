[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Player Resources")]
class SCR_CTI_UpdateResourcesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateResourcesComponent : ScriptComponent
{
	protected PlayerController m_playerController;
	protected SCR_CTI_ClientPocketComponent m_clientPocketComp;
	protected SCR_CTI_GameMode m_gameMode;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 45; // economy cycle

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				m_clientPocketComp.changeFunds(m_gameMode.BASEINCOME); // update
				m_timeDelta = 0;
			}
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_playerController = PlayerController.Cast(owner);
		m_clientPocketComp = SCR_CTI_ClientPocketComponent.Cast(m_playerController.FindComponent(SCR_CTI_ClientPocketComponent));
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		
		m_timeDelta = 0;
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