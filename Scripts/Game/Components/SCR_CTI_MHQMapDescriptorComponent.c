[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup MHQ markers.")]
class SCR_CTI_MHQMapDescriptorComponentClass : SCR_MapDescriptorComponentClass
{
};

class SCR_CTI_MHQMapDescriptorComponent : SCR_MapDescriptorComponent
{
	protected SCR_CTI_GameMode gamemode;
	protected ResourceName resname;
	
	//------------------------------------------------------------------------------------------------
	void init()
	{
		Color textcolor = Color.Black;
		if (resname == gamemode.USSRMHQ)
		{
			textcolor = Color.Red;
		} else {
			textcolor = Color.Blue;
		}

		MapItem mapitem = Item();

		MapDescriptorProps props = mapitem.GetProps();
			props.SetDetail(96);
			props.SetIconSize(16, 1, 2);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(textcolor);
			props.SetTextBold();
			props.SetTextVisible(true);
			props.SetIconVisible(false);
			props.Activate(true);
		
		mapitem.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	void OnMapOpen()
	{
		if (!SCR_PlayerController.GetLocalControlledEntity()) return;

		Print("- MAP OPEN -");
	}

	//------------------------------------------------------------------------------------------------
	void OnMapClose()
	{
		Print("- MAP CLOSE -");
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_MHQMapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{	
		gamemode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		resname = ent.GetPrefabData().GetPrefabName();
		
		// Call init function after 5s (wait until object ready for use)
		GetGame().GetCallqueue().CallLater(init, 5000);
		
		//SCR_MapEntity.GetOnMapOpen().Insert(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Insert(OnMapClose);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_MHQMapDescriptorComponent()
	{
		//SCR_MapEntity.GetOnMapOpen().Remove(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Remove(OnMapClose);
	}
};