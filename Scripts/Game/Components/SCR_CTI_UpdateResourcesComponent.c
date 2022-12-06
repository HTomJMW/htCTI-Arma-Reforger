[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Update Resources")]
class SCR_CTI_UpdateResourcesComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpdateResourcesComponent : ScriptComponent
{
	protected float m_timeDelta;
	protected const float TIMESTEP = 45; // economy cycle
	protected const float BASEINCOME = 10;

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_timeDelta = 0;
	}

	//------------------------------------------------------------------------------------------------
	protected void update()
	{
		PlayerManager pm = GetGame().GetPlayerManager();
		
		array<int> players = {};
		pm.GetPlayers(players);
		
		foreach (int playerId : players)
		{
			PlayerController pc = GetGame().GetPlayerController();
			SCR_CTI_ClientDataComponent cdc = SCR_CTI_ClientDataComponent.Cast(pc.FindComponent(SCR_CTI_ClientDataComponent));
			
			cdc.changeFunds(BASEINCOME);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				update();
				m_timeDelta = 0;
			}
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