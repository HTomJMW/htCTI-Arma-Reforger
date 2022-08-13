[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Set weather and time accelerations.")]
class SCR_CTI_WeatherAndTimeComponentClass : ScriptComponentClass
{
};

class SCR_CTI_WeatherAndTimeComponent : ScriptComponent
{
	protected TimeAndWeatherManagerEntity manager;
	protected float lenghtofday = 24 * 60 * 60;
	protected float daytimeduration = lenghtofday / 1;
	protected float nightduration = lenghtofday / 4;
	
	protected float m_timeDelta;
	protected const float timeStep = 60;
	
	void setStartTime()
	{
		if (!manager) return;
		
		manager.SetDate(1985, 06, 01, true);
		
		int random_hour = Math.RandomIntInclusive(8, 16);
		manager.SetHoursMinutesSeconds(random_hour, 0, 0, true);
	}
	
	void timeAcceleration()
	{
		float time = manager.GetTimeOfTheDay();
		
		//Night 4x faster than Daytime
		if (manager.IsNightHour(time))
		{
			manager.SetDayDuration(nightduration);
		} else {
			manager.SetDayDuration(daytimeduration);
		}
	}
	
	void setFog()
	{
		//Fog not included yet, fog entity need
	}
	
	void setWeather()
	{
	}
		
	void init()
	{
		manager = GetGame().GetTimeAndWeatherManager();
		
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
		if (m_timeDelta > timeStep)
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