[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Client Data")]
class SCR_CTI_ClientData
{
	private int m_playerId = -1;
	private Faction m_playerFaction;
	private int m_factionIndex = 0;
	private bool m_isCommander = false;
	private int m_funds = 0;

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
	int getFactionIndex()
	{
		return m_factionIndex;
	}
	
	//------------------------------------------------------------------------------------------------
	void setFactionIndex(int index)
	{
		m_factionIndex = index;
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
	int getFunds()
	{
		return m_funds;
	}
	
	//------------------------------------------------------------------------------------------------
	void changeFunds(int value)
	{
		m_funds += (value);
		if (m_funds < 0) m_funds = 0;
	}
	
	//################################################################################################
	//! Codec methods
	//------------------------------------------------------------------------------------------------
	static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet) 
	{
		snapshot.Serialize(packet, 16);
	}
	
	//------------------------------------------------------------------------------------------------
	static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot) 
	{
		return snapshot.Serialize(packet, 16);
	}
	
	//------------------------------------------------------------------------------------------------
	static bool SnapCompare(SSnapSerializerBase lhs, SSnapSerializerBase rhs, ScriptCtx ctx) 
	{	
		return lhs.CompareSnapshots(rhs, 16);
	}
	
	//------------------------------------------------------------------------------------------------
	static bool PropCompare(SCR_CTI_ClientData prop, SSnapSerializerBase snapshot, ScriptCtx ctx) 
	{
		return snapshot.Compare(prop.m_playerId, 4)
			&& snapshot.Compare(prop.m_factionIndex, 4)
			&& snapshot.Compare(prop.m_isCommander, 1)
			&& snapshot.Compare(prop.m_funds, 4);
	}
	
	//------------------------------------------------------------------------------------------------
	static bool Extract(SCR_CTI_ClientData prop, ScriptCtx ctx, SSnapSerializerBase snapshot) 
	{		
		snapshot.SerializeBytes(prop.m_playerId, 4);
		snapshot.SerializeBytes(prop.m_factionIndex, 4);
		snapshot.SerializeBytes(prop.m_isCommander, 1);
		snapshot.SerializeBytes(prop.m_funds, 4);
		
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, SCR_CTI_ClientData prop) 
	{
		snapshot.SerializeBytes(prop.m_playerId, 4);
		snapshot.SerializeBytes(prop.m_factionIndex, 4);
		snapshot.SerializeBytes(prop.m_isCommander, 1);
		snapshot.SerializeBytes(prop.m_funds, 4);
		
		return true;
	}
	//################################################################################################

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_ClientData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_ClientData()
	{
	}
};