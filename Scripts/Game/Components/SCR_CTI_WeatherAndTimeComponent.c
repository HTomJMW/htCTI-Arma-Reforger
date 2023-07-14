[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Set weather and time accelerations.")]
class SCR_CTI_WeatherAndTimeComponentClass : ScriptComponentClass
{
};

class SCR_CTI_WeatherAndTimeComponent : ScriptComponent
{
	protected TimeAndWeatherManagerEntity m_manager;
	protected float m_lenghtofday = 24 * 60 * 60;
	protected float m_daytimeduration = m_lenghtofday / 1;
	protected float m_nightduration = m_lenghtofday / 6; //Night 6x faster than Daytime
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 60;

	//------------------------------------------------------------------------------------------------
	void randomStartTime()
	{
		if (!m_manager) return;

		m_manager.SetDate(1985, 06, 01, true);

		RandomGenerator randomgen = new RandomGenerator();
		int h, m, s;
		System.GetHourMinuteSecond(h, m, s);
		randomgen.SetSeed(s * 100000);

		int random_hour = randomgen.RandIntInclusive(6, 18);
		m_manager.SetHoursMinutesSeconds(random_hour, 0, 0, true);
		
		PrintFormat("CTI :: Time: %1h", m_manager.GetTime().m_iHours);
	}
	
	//------------------------------------------------------------------------------------------------
	void randomWeather()
	{
		if (!m_manager) return;

		array<ref WeatherState> weatherStates = {};
		m_manager.GetWeatherStatesList(weatherStates);
			
		if (!weatherStates.IsEmpty())
		{
			int statesCount = weatherStates.Count();
			for (int i = 0; i < statesCount; i++)
			{
				if (weatherStates[i].GetStateName() == "Clear") {weatherStates.Insert(weatherStates[i]); weatherStates.Insert(weatherStates[i]);}
				if (weatherStates[i].GetStateName() == "Cloudy") weatherStates.Insert(weatherStates[i]);
			}

			Math.Randomize(-1);
			m_manager.ForceWeatherTo(false, weatherStates.GetRandomElement().GetStateName());
		}
	}

	//------------------------------------------------------------------------------------------------
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

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		m_timeDelta += timeSlice;
		if (m_timeDelta > TIMESTEP)
			{
				timeAcceleration();
				m_timeDelta = 0;
			}
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_WeatherAndTimeComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_manager = GetGame().GetTimeAndWeatherManager();
		
		m_timeDelta = 0;
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_WeatherAndTimeComponent()
	{
	}	
};