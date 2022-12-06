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
			case "Exit":
			{
				auto menuManager = GetGame().GetMenuManager();
				menuManager.CloseAllMenus();
				break;
			}
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