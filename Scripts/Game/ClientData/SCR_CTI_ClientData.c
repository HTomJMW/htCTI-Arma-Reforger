[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Client Data")]
class SCR_CTI_ClientData
{
	private int m_playerId = -1;
	private bool m_isCommander = false;
	private int m_funds;
	
	//ref array<ResourceName> m_savedGear = {};

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

	//------------------------------------------------------------------------------------------------
	/*void getLoadout(int playerId)
	{
		SCR_ArsenalManagerComponent amc = SCR_ArsenalManagerComponent.Cast(GetGame().GetGameMode().FindComponent(SCR_ArsenalManagerComponent));
		
		amc.SetPlayerArsenalLoadout(playerId, GetGame().GetPlayerManager().GetPlayerControlledEntity(playerId));
		
		string jsonCharacter;
		amc.GetPlayerArsenalLoadout(playerId, jsonCharacter);
		Print(jsonCharacter);
	}*/

	//------------------------------------------------------------------------------------------------
	/*void saveLastGear(IEntity player)
	{
		SCR_InventoryStorageManagerComponent ismc = SCR_InventoryStorageManagerComponent.Cast(player.FindComponent(SCR_InventoryStorageManagerComponent));

		array<IEntity> outitems = {};
		ismc.GetItems(outitems);
		
		foreach (IEntity item : outitems)
		{
			ResourceName rn = item.GetPrefabData().GetPrefabName();
			m_savedGear.Insert(rn);
		}
		
		PrintFormat("Player: %1, Items: %2", getPlayerName(), m_savedGear);
	}*/

	//------------------------------------------------------------------------------------------------
	/*void loadGear(IEntity controlledEntity)
	{
		if (m_savedGear.Count() < 1) return;
		
		SCR_InventoryStorageManagerComponent ismc = SCR_InventoryStorageManagerComponent.Cast(controlledEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		
		array<IEntity> outitems = {};
		ismc.GetItems(outitems);
		
		foreach (IEntity item : outitems)
		{
			bool trydel = ismc.TryDeleteItem(item); PrintFormat("ITEM: %1, TRYDEL: %2", item.GetPrefabData().GetPrefabName(), trydel.ToString());
		}
		
		for (int i = 0; i < m_savedGear.Count(); i++)
		{
			Resource res = Resource.Load(m_savedGear[i]);
			IEntity ent = GetGame().SpawnEntityPrefab(res);
			ismc.TryInsertItem(ent);
		}
	}*/

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