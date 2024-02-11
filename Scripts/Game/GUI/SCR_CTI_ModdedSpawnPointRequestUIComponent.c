modded class SCR_SpawnPointRequestUIComponent : SCR_DeployRequestUIBaseComponent
{
	override void ShowAvailableSpawnPoints(Faction faction)
	{
		if (!faction)
			return;

		ClearSpawnPoints();

		PlayerController pc = GetGame().GetPlayerController();
		SCR_CTI_DeathPositionComponent dpc = SCR_CTI_DeathPositionComponent.Cast(pc.FindComponent(SCR_CTI_DeathPositionComponent));

		array<SCR_SpawnPoint> infos = SCR_SpawnPoint.getSpawnPointsForCTIPlayer(faction, dpc.getDeathPosition());
		
		if (infos.IsEmpty())
		{
			SetSpawnPoint(RplId.Invalid());
			return;
		}

		foreach (SCR_SpawnPoint info : infos)
		{
			info.ShowSpawnPointDescriptors(true, faction);

			auto mapDescriptor = SCR_MapDescriptorComponent.Cast(info.FindComponent(SCR_MapDescriptorComponent));
			if (mapDescriptor)
			{
				 MapItem mapItem = mapDescriptor.Item();

				mapItem.SetBaseType(EMapDescriptorType.MDT_ICON);
				mapItem.SetImageDef("USSR_Base_Small_Select");

				MapDescriptorProps props = mapItem.GetProps();
					props.SetDetail(96);
					props.SetIconSize(32, 0.25, 0.25);
					props.SetFrontColor(Color.Yellow);
					props.SetIconVisible(true);
					props.Activate(true);

				mapItem.SetProps(props);
			}

			AddSpawnPoint(info);
		}
	}
};