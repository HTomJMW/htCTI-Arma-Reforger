[EntityEditorProps(category: "GameScripted/CTI", description: "User Action")]
class SCR_CTI_PurchaseVehicleAction : ScriptedUserAction
{
	protected IEntity m_owner;
	protected SCR_CTI_Town m_town;
	protected SCR_CTI_GameMode m_gameMode;
	protected SCR_CTI_ClientData m_clientData;
	
	protected ResourceName m_resNameUaz = "{259EE7B78C51B624}Prefabs/Vehicles/Wheeled/UAZ469/UAZ469.et";
	protected ResourceName m_resNameJeep = "{F649585ABB3706C4}Prefabs/Vehicles/Wheeled/M151A2/M151A2.et";
	
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		m_owner = pOwnerEntity;
		m_town = SCR_CTI_Town.Cast(pOwnerEntity);
		m_gameMode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
	}
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity) 
	{	
		RplComponent rplComp = RplComponent.Cast(pOwnerEntity.FindComponent(RplComponent));
		if (!rplComp)	
		{	
			Print("RPL component missing! (SCR_CTI_PurchaseVehicleAction)");
			return;
		}

		RplId destructibleID = rplComp.Id();
		if (!destructibleID.IsValid())
		{
			Print("RplId not valid! (SCR_CTI_PurchaseVehicleAction)");
			return;
		}
		
		Resource resource;
		int price;
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(pUserEntity.FindComponent(FactionAffiliationComponent));
		if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
		{
			resource = Resource.Load(m_resNameUaz);
			int unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUaz);
			SCR_CTI_UnitData unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
			price = unitData.getPri();
		} else {
			resource = Resource.Load(m_resNameJeep);
			int unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameJeep);
			SCR_CTI_UnitData unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
			price = unitData.getPri();
		}
			
		EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		vector mat[4];
		m_owner.GetTransform(mat); // flagpos
		
		RandomGenerator randomgen = new RandomGenerator();
		vector rndpos = randomgen.GenerateRandomPointInRadius(3, 8, mat[3], true);
		vector emptyPos;
		SCR_WorldTools.FindEmptyTerrainPosition(emptyPos, rndpos, 6);
		mat[3] = emptyPos;

		params.Transform = mat;

		GetGame().SpawnEntityPrefab(resource, m_owner.GetWorld(), params);
		
		m_clientData.changeFunds(-price);
	}

	override bool HasLocalEffectOnlyScript()
	{
		return false;
	}

	override bool CanBePerformedScript(IEntity user)
	{
		PlayerController playerController = GetGame().GetPlayerController();
		int playerId = playerController.GetPlayerId();
		
		int sizeCDA = m_gameMode.ClientDataArray.Count();
		for (int i = 0; i < sizeCDA; i++)
		{
			if (m_gameMode.ClientDataArray[i].getPlayerId() == playerId)
			{
				m_clientData = m_gameMode.ClientDataArray[i];
				break;
			}
		}
		
		if (m_clientData)
			{
				int funds = m_clientData.getFunds();
			
				FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
				if (userAffiliationComponent.GetAffiliatedFaction().GetFactionKey() == "USSR")
				{
					int unitIndex = m_gameMode.UnitsUSSR.findIndexFromResourcename(m_resNameUaz);
					SCR_CTI_UnitData unitData = m_gameMode.UnitsUSSR.g_USSR_Units[unitIndex];
					int unitPrice = unitData.getPri();
					if (funds > unitPrice)
					{
						return true;
					} else {
						SetCannotPerformReason("Insufficent funds!");
						return false;
					}
				} else {
					int unitIndex = m_gameMode.UnitsUS.findIndexFromResourcename(m_resNameJeep);
					SCR_CTI_UnitData unitData = m_gameMode.UnitsUS.g_US_Units[unitIndex];
					int unitPrice = unitData.getPri();
					if (funds > unitPrice)
					{
						return true;
					} else {
						SetCannotPerformReason("Insufficent funds!");
						return false;
					}
				}
			}

		return true;
	}

	override bool CanBeShownScript(IEntity user)
	{
		FactionAffiliationComponent userAffiliationComponent = FactionAffiliationComponent.Cast(user.FindComponent(FactionAffiliationComponent));
		if (m_town.getFactionKey() != userAffiliationComponent.GetAffiliatedFaction().GetFactionKey()) return false;
		
		return true;
	}

	override bool GetActionNameScript(out string outName)
	{
		ActionNameParams[0] = "PARAM1";
		ActionNameParams[1] = "PARAM2";
					
		outName = ("Purchase Light Vehicle");
		
		return true;
	}
	
	void SCR_CTI_PurchaseVehicleAction()
	{
	}

	void ~SCR_CTI_PurchaseVehicleAction()
	{
	}
};