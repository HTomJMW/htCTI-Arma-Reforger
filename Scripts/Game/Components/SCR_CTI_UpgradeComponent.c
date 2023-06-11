enum UpgradeStatus
{
	NONE,
	RUNNING,
	FINISHED
};

[ComponentEditorProps(category: "GameScripted/CTI", description: "Run CTI Upgrades")]
class SCR_CTI_UpgradeComponentClass : ScriptComponentClass
{
};

class SCR_CTI_UpgradeComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected RplComponent m_rplComponent;
	
	protected float m_timeDelta;
	protected const float TIMESTEP = 5;

	[RplProp()]
	protected int ussrRunningUpgradeIndex = -1;
	[RplProp()]
	protected int usRunningUpgradeIndex = -1;
	[RplProp()]
	protected float ussrRemainingUpgradeTime = 0;
	[RplProp()]
	protected float usRemainingUpgradeTime = 0;
	[RplProp()]
	ref array<UpgradeStatus> ussrUpgradeStatuses = {};
	[RplProp()]
	ref array<UpgradeStatus> usUpgradeStatuses = {};

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetOwner());
		m_rplComponent = RplComponent.Cast(m_gameMode.FindComponent(RplComponent));
		initUpdateStatuses();
	}

	//------------------------------------------------------------------------------------------------
	protected void initUpdateStatuses()
	{
		for (int i = 0; i < m_gameMode.Upgrades.g_Upgrades.Count(); i++)
		{
			ussrUpgradeStatuses.Insert(UpgradeStatus.NONE);
			usUpgradeStatuses.Insert(UpgradeStatus.NONE);
		}
	}

	//------------------------------------------------------------------------------------------------
	// Only on server
	void runUpgrade(FactionKey factionkey, int upgradeindex)
	{
		SCR_CTI_UpgradeData upgradeData = m_gameMode.Upgrades.g_Upgrades[upgradeindex];
		switch (factionkey)
		{
			case "USSR":
			{
				if (upgradeindex != -1 && ussrUpgradeStatuses[upgradeindex] == UpgradeStatus.NONE)
				{
					ussrUpgradeStatuses[upgradeindex] = UpgradeStatus.RUNNING;
					ussrRemainingUpgradeTime = upgradeData.getTime();
					ussrRunningUpgradeIndex = upgradeindex;
				}
				break;
			}
			case "US":
			{
				if (upgradeindex != -1 && usUpgradeStatuses[upgradeindex] == UpgradeStatus.NONE)
				{
					usUpgradeStatuses[upgradeindex] = UpgradeStatus.RUNNING;
					usRemainingUpgradeTime = upgradeData.getTime();
					usRunningUpgradeIndex = upgradeindex;
				}
				break;
			}
		}

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	// Only on Server
	void stopUpgrade(FactionKey factionkey)
	{
		switch (factionkey)
		{
			case "USSR":
			{
				for (int i = 0; i < ussrUpgradeStatuses.Count(); i++)
				{
					if (ussrUpgradeStatuses[i] == UpgradeStatus.RUNNING)
					{
						ussrRunningUpgradeIndex = -1;
						ussrUpgradeStatuses[i] = UpgradeStatus.NONE;
						ussrRemainingUpgradeTime = 0;
						break;
					}
				}
				break;
			}
			case "US":
			{
				for (int i = 0; i < ussrUpgradeStatuses.Count(); i++)
				{
					if (usUpgradeStatuses[i] == UpgradeStatus.RUNNING)
					{
						usRunningUpgradeIndex = -1;
						usUpgradeStatuses[i] = UpgradeStatus.NONE;
						usRemainingUpgradeTime = 0;
						break;
					}
				}
				break;
			}
		}

		Replication.BumpMe();
	}

	//------------------------------------------------------------------------------------------------
	protected void finish(FactionKey factionkey, int upgradeindex)
	{
		if (upgradeindex != -1)
		{
			switch (factionkey)
			{
			case "USSR":
				{
					ussrUpgradeStatuses[upgradeindex] = UpgradeStatus.FINISHED;
					ussrRunningUpgradeIndex = -1;
					break;
				}
				case "US":
				{
					usUpgradeStatuses[upgradeindex] = UpgradeStatus.FINISHED;
					ussrRunningUpgradeIndex = -1;
					break;
				}
			}

			Replication.BumpMe();
		}
	}

	//------------------------------------------------------------------------------------------------
	override void EOnFixedFrame(IEntity owner, float timeSlice)
	{
		if (!m_rplComponent.IsProxy())
		{
			m_timeDelta += timeSlice;
			if (m_timeDelta > TIMESTEP)
			{
				if (ussrRunningUpgradeIndex != -1)
				{
					if (ussrRemainingUpgradeTime > 0)
					{
						ussrRemainingUpgradeTime -= m_timeDelta;
						if (ussrRemainingUpgradeTime <= 0)
						{
							ussrRemainingUpgradeTime = 0;
							finish("USSR", ussrRunningUpgradeIndex);
						}
					} else {
						ussrRemainingUpgradeTime = 0;
						finish("USSR", ussrRunningUpgradeIndex);
					}
				}
				if (usRunningUpgradeIndex != -1)
				{
					if (usRemainingUpgradeTime > 0)
					{
						usRemainingUpgradeTime -= m_timeDelta;
						if (usRemainingUpgradeTime <= 0)
						{
							ussrRemainingUpgradeTime = 0;
							finish("US", usRunningUpgradeIndex);
						}
					} else {
						usRemainingUpgradeTime = 0;
						finish("US", usRunningUpgradeIndex);
					}
				}
				if (ussrRunningUpgradeIndex != -1 || usRunningUpgradeIndex != -1)
				{
					Replication.BumpMe(); // refresh upgrades to proxys
				}
				
				m_timeDelta = 0;
			}
		}
	}

	//------------------------------------------------------------------------------------------------
	int getRunningUpgradeIndex(FactionKey factionkey)
	{
		int index = -1;

		switch (factionkey)
		{
			case "USSR": index = ussrRunningUpgradeIndex; break;
			case "US": index = usRunningUpgradeIndex; break;
		}

		return index;
	}

	//------------------------------------------------------------------------------------------------
	float getRemainingTime(FactionKey factionkey)
	{
		float time = -1;

		switch (factionkey)
		{
			case "USSR": time = ussrRemainingUpgradeTime; break;
			case "US": time = usRemainingUpgradeTime; break;
		}

		return time;
	}

	//------------------------------------------------------------------------------------------------
	UpgradeStatus getUpgradeStatus(FactionKey factionkey, int upgradeindex)
	{
		UpgradeStatus status = UpgradeStatus.NONE;
		
		switch (factionkey)
		{
			case "USSR": status = ussrUpgradeStatuses[upgradeindex]; break;
			case "US": status = usUpgradeStatuses[upgradeindex]; break;
		}
		
		return status;
	}

	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.FIXEDFRAME);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_UpgradeComponent()
	{
		if (ussrUpgradeStatuses) ussrUpgradeStatuses.Clear();
		ussrUpgradeStatuses = null;
		if (usUpgradeStatuses) usUpgradeStatuses.Clear();
		usUpgradeStatuses = null;
	}
};