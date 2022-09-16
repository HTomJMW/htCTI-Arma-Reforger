[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Client Data")]
class SCR_CTI_ClientData
{
	private int m_playerId = -1;
	//private Faction m_playerFaction;
	private bool m_isCommander = false;
	private int m_funds = 2400;

	int getPlayerId()
	{
		return m_playerId;
	}
	
	void setPlayerId(int id)
	{
		m_playerId = id;
	}
	
	string getPlayerName()
	{
		return GetGame().GetPlayerManager().GetPlayerName(m_playerId);
	}
	
	bool isCommander()
	{
		return m_isCommander;
	}
	
	//Faction getPlayerFaction()
	//{
	//	return m_playerFaction;
	//}
	
	//void setPlayerFaction(Faction faction)
	//{
	//	m_playerFaction = faction;
	//}
	
	//void setPlayerFactionByKey(FactionKey key)
	//{
	//	m_playerFaction = GetGame().GetFactionManager().GetFactionByKey(key);	
	//}
	
	int getFunds()
	{
		return m_funds;
	}
	
	void changeFunds(int value)
	{
		m_funds += (value);
		if (m_funds < 0) m_funds = 0;
	}
	
	void SCR_CTI_ClientData()
	{
	}
		
	void ~SCR_CTI_ClientData()
	{
	}
};