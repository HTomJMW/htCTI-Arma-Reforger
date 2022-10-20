[ComponentEditorProps(category: "GameScripted/CTI", description: "Run CTI Upgrades")]
class SCR_CTI_UpgradeComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpgradeComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected float m_timeDelta;
	protected const float TIMESTEP = 5;
	protected float ussr_remainingtime;
	protected float us_remainingtime;
	protected int ussr_upgradeindex;
	protected int us_upgradeindex;
	
	void init()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetOwner());
		ussr_remainingtime = 0;
		us_remainingtime = 0;
		ussr_upgradeindex = -1;
		us_upgradeindex = -1;
	}
	
	void runUpgrade(FactionKey factionKey, int upgradeindex)
	{
		SCR_CTI_UpgradeData upgradeData;
		switch (factionKey)
		{
			case "USSR":
			{
				upgradeData = m_gameMode.UpgradesUSSR.g_Upgrades[upgradeindex];
				if (upgradeindex != -1 && upgradeData.getStatus() == UpgradeStatus.NONE)
				{
					upgradeData.setStatus(UpgradeStatus.RUNNING);
					ussr_remainingtime = upgradeData.getTime();
					ussr_upgradeindex = upgradeindex;
				}
				break;
			}
			case "US":
			{
				upgradeData = m_gameMode.UpgradesUS.g_Upgrades[upgradeindex];
				if (upgradeindex != -1 && upgradeData.getStatus() == UpgradeStatus.NONE)
				{
					upgradeData.setStatus(UpgradeStatus.RUNNING);
					us_remainingtime = upgradeData.getTime();
					us_upgradeindex = upgradeindex;
				}
				break;
			}
		}
	}

	protected void finish(FactionKey factionkey, int upgradeindex)
	{
		if (upgradeindex != -1)
		{
			SCR_CTI_UpgradeData dta;
			switch (factionkey)
			{
			case "USSR":
				{
					dta = m_gameMode.UpgradesUSSR.g_Upgrades[upgradeindex];
					ussr_upgradeindex = -1;
					break;
				}
				case "US":
				{
					dta = m_gameMode.UpgradesUS.g_Upgrades[upgradeindex];
					us_upgradeindex = -1;
					break;
				}
			}
			dta.setStatus(UpgradeStatus.FINISHED);
		}
	}
			
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		//m_timeDelta += timeSlice;
		if (ussr_remainingtime > 0)
		{
			ussr_remainingtime -= timeSlice;
		} else {
			ussr_remainingtime = 0;
			finish("USSR", ussr_upgradeindex);
		}
		if (us_remainingtime > 0)
		{
			us_remainingtime -= timeSlice;
		} else {
			us_remainingtime = 0;
			finish("US", us_upgradeindex);
		}
		/*if (m_timeDelta > TIMESTEP)
		{
			Print("SERVER 5s LOOP");
			
			m_timeDelta = 0;
		}*/
	}
	
	float getRemainingTime(FactionKey fk)
	{
		float time = -1;
		if (fk == "USSR")
		{
			time = ussr_remainingtime;
		} else {
			time = us_remainingtime;
		} 
		
		return time;
	}
	
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	void SCR_CTI_UpgradeComponent()
	{
	}
		
	void ~SCR_CTI_UpgradeComponent()
	{
	}
};