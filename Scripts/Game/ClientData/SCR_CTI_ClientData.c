[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Client Data")]
class SCR_CTI_ClientData
{
	private int m_playerId = -1;
	private Faction m_playerFaction;
	private bool m_isCommander = false;

	//------------------------------------------------------------------------------------------------
	int getPlayerId()
	{
		return m_playerId;
	}

	//------------------------------------------------------------------------------------------------
	void setPlayerId(int id)
	{
		m_playerId = id;
	}

	//------------------------------------------------------------------------------------------------
	Faction getFaction()
	{
		return m_playerFaction;
	}
	
	//------------------------------------------------------------------------------------------------
	void setFaction(Faction faction)
	{
		m_playerFaction = faction;
	}

	//------------------------------------------------------------------------------------------------
	string getPlayerName()
	{
		return GetGame().GetPlayerManager().GetPlayerName(m_playerId);
	}

	//------------------------------------------------------------------------------------------------
	bool isCommander()
	{
		return m_isCommander;
	}

	//------------------------------------------------------------------------------------------------
	void setCommander(bool value)
	{
		m_isCommander = value;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_ClientData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_ClientData()
	{
		//m_savedGear.Clear();
		//m_savedGear = null;
	}
};