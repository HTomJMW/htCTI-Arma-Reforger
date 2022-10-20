[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Set weather and time accelerations.")]
class SCR_CTI_WeatherAndTimeComponentClass : ScriptComponentClass
{
};

class SCR_CTI_WeatherAndTimeComponent : ScriptComponent
{
	protected TimeAndWeatherManagerEntity m_manager;
	protected float m_lenghtofday = 24 * 60 * 60;
	protected float m_daytimeduration = m_lenghtofday / 1;
	protected float m_nightduration = m_lenghtofday / 4; //Night 4x faster than Daytime
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 60;
	
	protected void setStartTime()
	{
		if (!m_manager) return;
		
		m_manager.SetDate(1985, 06, 01, true);
		
		int random_hour = Math.RandomIntInclusive(8, 16);
		m_manager.SetHoursMinutesSeconds(random_hour, 0, 0, true);
		
		PrintFormat("CTI :: Time: %1h", m_manager.GetTime().m_iHours);
	}
	
	protected void timeAcceleration()
	{
		float time = m_manager.GetTimeOfTheDay();
		
		if (m_manager.IsNightHour(time))
		{
			m_manager.SetDayDuration(m_nightduration);
		} else {
			m_manager.SetDayDuration(m_daytimeduration);
		}
	}
	
	protected void setFog()
	{
		//Fog not included yet, fog entity need
	}
	
	protected void setWeather()
	{
	}
	
	protected void setRain()
	{
	}

	void init()
	{
		m_manager = GetGame().GetTimeAndWeatherManager();
		
		setStartTime();
		
		m_timeDelta = 0;
	}
	
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}
	
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				timeAcceleration();
				m_timeDelta = 0;
			}
	}

	void SCR_CTI_WeatherAndTimeComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}
		
	void ~SCR_CTI_WeatherAndTimeComponent()
	{
	}	
};