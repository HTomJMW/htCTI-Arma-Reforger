[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Build Queue.")]
class SCR_CTI_BuildQueueComponentClass : ScriptComponentClass
{
};

class SCR_CTI_BuildQueueComponent : ScriptComponent
{
	protected SCR_CTI_GameMode m_gameMode;

	ref array<ref SCR_CTI_BuildData> g_BuildQueue = new array<ref SCR_CTI_BuildData>;
	
	//------------------------------------------------------------------------------------------------
	void addRequest(ResourceName resourcename, FactionKey factionkey, EntityID groupID, RplId factRplId, vector mat[4], int playerId, int buildTime, CTI_PurchaseInfos purchaseInfo)
	{
		SCR_CTI_BuildData buildData = new SCR_CTI_BuildData;
		buildData.setData(resourcename, factionkey, groupID, factRplId, mat, playerId, buildTime, purchaseInfo);
		int index = g_BuildQueue.Insert(buildData);

		GetGame().GetCallqueue().CallLater(executeRequest, buildTime * 1000, false, index);
		
		m_gameMode.SendHint(playerId, "Your <color rgba='255,210,115,255'>Unit</color> is being built! (" + buildTime.ToString() + "s)", "Information", 15);
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
		
		g_BuildQueue.Remove(index);
	}
	
	//------------------------------------------------------------------------------------------------
	void removeRequest()
	{
	}
	
	//------------------------------------------------------------------------------------------------
	void executeBuild()
	{
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BuildQueueComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gameMode = SCR_CTI_GameMode.Cast(ent);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildQueueComponent()
	{
		if (g_BuildQueue) g_BuildQueue.Clear();
		g_BuildQueue = null;
	}	
};