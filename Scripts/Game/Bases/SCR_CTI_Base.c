[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Base")]
class SCR_CTI_Base
{
	protected FactionKey m_baseSide;
	protected int m_baseId;
	protected vector m_basePos;
	protected bool m_destroyed = false;
	
	ref array<IEntity> structures = {};

	//------------------------------------------------------------------------------------------------
	FactionKey getBaseFactionKey()
	{
		return m_baseSide;
	}

	//------------------------------------------------------------------------------------------------
	void setBaseFactionKey(FactionKey key)
	{
		m_baseSide = key;
	}

	//------------------------------------------------------------------------------------------------
	int getBaseId()
	{
		return m_baseId;
	}

	//------------------------------------------------------------------------------------------------
	void setBaseId(int value)
	{
		m_baseId = value;	
	}

	//------------------------------------------------------------------------------------------------
	vector getBasePos()
	{
		return m_basePos;
	}

	//------------------------------------------------------------------------------------------------
	void setBasePos(vector pos)
	{
		m_basePos = pos;
	}

	//------------------------------------------------------------------------------------------------
	bool isDestroyed()
	{
		return m_destroyed;
	}

	//------------------------------------------------------------------------------------------------
	void setDestroyed(bool value)
	{
		m_destroyed = value;
	}
	
	//------------------------------------------------------------------------------------------------
	void addStructure(IEntity structure)
	{
		structures.Insert(structure);
		// todo make marker
	}

	//------------------------------------------------------------------------------------------------
	void destroyStructure(IEntity structure)
	{
		// todo remove
		// todo remove marker
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_Base()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_Base()
	{
		structures.Clear();
		structures = null;
	}
};