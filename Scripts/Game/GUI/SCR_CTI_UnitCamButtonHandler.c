class SCR_CTI_UnitCamButtonHandler : ScriptedWidgetEventHandler
{
	//------------------------------------------------------------------------------------------------
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		w.SetColor(Color.White);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		w.SetColor(Color.Orange);
		
		return true;
	}

	//------------------------------------------------------------------------------------------------
	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		switch (w.GetName())
		{
			case "IronSight":
			{
				break;
			}
			case "Internal":
			{
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();
				SCR_CharacterCameraHandlerComponent cchc = SCR_CharacterCameraHandlerComponent.Cast(player.FindComponent(SCR_CharacterCameraHandlerComponent));
				cchc.SetThirdPerson(false);
				
				break;
			}
			case "External":
			{
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();
				SCR_CharacterCameraHandlerComponent cchc = SCR_CharacterCameraHandlerComponent.Cast(player.FindComponent(SCR_CharacterCameraHandlerComponent));
				cchc.SetThirdPerson(true);

				break;
			}
			case "Unflip":
			{
				// todo check team members
				PlayerController pc = GetGame().GetPlayerController();
				IEntity player = pc.GetControlledEntity();
				SCR_CompartmentAccessComponent cac = SCR_CompartmentAccessComponent.Cast(player.FindComponent(SCR_CompartmentAccessComponent));
				IEntity vehicle = cac.GetVehicle();
				if (vehicle)
				{
					RplComponent vehRplComp = RplComponent.Cast(vehicle.FindComponent(RplComponent));
					RplId rplid = vehRplComp.Id();

					SCR_CTI_NetWorkComponent netComp = SCR_CTI_NetWorkComponent.Cast(pc.FindComponent(SCR_CTI_NetWorkComponent));
					netComp.unflipNearestVehicleServer(rplid);
				}
				
				break;
			}
			case "Disband":
			{
				
				
				break;
			}
			case "Info":
			{
				
				
				break;
			}
			case "NormalNV":
			{
				
				
				break;
			}
			case "Satellite":
			{
				
				
				break;
			}
		}
		
		return true;
	}
};