[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Factory Build Queue.")]
class SCR_CTI_BuildQueueComponentClass : ScriptComponentClass
{
};

class SCR_CTI_BuildQueueComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;
	protected int m_finishTime;

	ref array<ref SCR_CTI_BuildData> g_BuildQueue = new array<ref SCR_CTI_BuildData>;
	
	//------------------------------------------------------------------------------------------------
	void addRequest(ResourceName resourcename, FactionKey factionkey, EntityID groupID, RplId factRplId, vector mat[4], int playerId, int buildTime, CTI_PurchaseInfos purchaseInfo)
	{
		int index = -1;
		index = g_BuildQueue.Find(null);

		SCR_CTI_BuildData buildData = new SCR_CTI_BuildData;
		buildData.setData(resourcename, factionkey, groupID, factRplId, mat, playerId, buildTime, purchaseInfo);

		if (index > -1)
		{
			g_BuildQueue.Set(index, buildData);
		} else {
			index = g_BuildQueue.Insert(buildData);
		}

		int currentTime = m_gameMode.GetElapsedTime();
		int delay;
		if (m_finishTime - currentTime > 0)
		{
			delay = (m_finishTime - currentTime) + buildTime;
		} else {
			delay = buildTime;
		}
		m_finishTime = currentTime + delay;
	
		GetGame().GetCallqueue().CallLater(executeRequest, delay * 1000, false, index);

		m_gameMode.SendHint(playerId, "Your <color rgba='255,210,115,255'>Unit</color> added to build queue!", "Information", 5);
		
		int last = g_BuildQueue.Count() - 1;
		if (!g_BuildQueue[last]) g_BuildQueue.Remove(last);
	}

	protected void executeRequest(int index)
	{
		ResourceName resourcename;
		FactionKey factionkey;
		EntityID groupID;
		RplId factRplId;
		vector mat[4];
		int playerId;
		int buildTime;
		CTI_PurchaseInfos purchaseInfo;
		int requestTime;
		SCR_CTI_BuildData buildData = g_BuildQueue.Get(index);
		buildData.getData(resourcename, factionkey, groupID, factRplId, mat, playerId, buildTime, purchaseInfo, requestTime);
		
		SCR_CTI_FactoryProduction FactoryProduction = new SCR_CTI_FactoryProduction;
		FactoryProduction.build(resourcename, factionkey, groupID, factRplId, mat, playerId, buildTime, purchaseInfo);
		
		g_BuildQueue[index] = null;
	}
	
	//------------------------------------------------------------------------------------------------
	void removeRequest()
	{
		// TODO
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BuildQueueComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildQueueComponent()
	{
		if (g_BuildQueue) g_BuildQueue.Clear();
		g_BuildQueue = null;
	}	
};