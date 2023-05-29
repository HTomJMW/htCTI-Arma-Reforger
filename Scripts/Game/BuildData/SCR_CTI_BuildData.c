[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Build Data")]
class SCR_CTI_BuildData
{
	protected ResourceName m_resourceName;		// Resource name
	protected FactionKey m_factionKey;			// Facton key
	protected EntityID m_groupId;				// Requester groupId
	protected RplId m_factoryRplId;				// Factory RplId
	protected vector m_mat[4];					// Early spawn area
	protected int m_playerId;					// Requester PlayerId
	protected int m_buildTime;					// Needed build time
	protected CTI_PurchaseInfos m_purchaseInfo;	// Purchase infos
	protected int m_requestTime;				// Request time

	//------------------------------------------------------------------------------------------------
	void setData(ResourceName newResourceName, FactionKey newFactionKey, EntityID newGroupId, RplId newFactoryRplId, vector newMat[4], int newPlayerId, int newBuildTime, CTI_PurchaseInfos newPurchaseInfo)
	{
		m_resourceName = newResourceName;
		m_factionKey = newFactionKey;
		m_groupId = newGroupId;
		m_factoryRplId = newFactoryRplId;
		m_mat = newMat;
		m_playerId = newPlayerId;
		m_buildTime = newBuildTime;
		m_purchaseInfo = newPurchaseInfo;

		//TODO put to constructor
		SCR_CTI_GameMode gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_requestTime = gameMode.GetElapsedTime();
	}
	
	//------------------------------------------------------------------------------------------------
	void findBuildDataBy()
	{
		// TODO request time use for ID
	}
	
	//------------------------------------------------------------------------------------------------
	void getData(out ResourceName resourceName, out FactionKey factionKey, out EntityID groupId, out RplId factoryRplId, out vector mat[4], out int playerId, out int buildTime, out CTI_PurchaseInfos purchaseInfo, out int requestTime)
	{
		resourceName = m_resourceName;
		factionKey = m_factionKey;
		groupId = m_groupId;
		factoryRplId = m_factoryRplId;
		mat = m_mat;
		playerId = m_playerId;
		buildTime = m_buildTime;
		purchaseInfo = m_purchaseInfo;
		requestTime = m_requestTime;
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_BuildData()
	{
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_BuildData()
	{
	}
};