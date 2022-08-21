[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup town markers.")]
class SCR_CTI_MapDescriptorComponentClass : SCR_MapDescriptorComponentClass
{
};

class SCR_CTI_MapDescriptorComponent : SCR_MapDescriptorComponent
{
	protected MapItem item;
	protected SCR_CTI_Town owner;
	
	protected Widget widget;
	protected string marker = "Flag";

	void init()
	{
		item = Item();
		owner = SCR_CTI_Town.Cast(item.Entity());
		
		item.SetDisplayName(owner.getTownName());
		item.SetBaseType(EMapDescriptorType.MDT_ICON);
		
		MapDescriptorProps props = item.GetProps();
			item.SetImageDef(marker);
			props.SetDetail(96);
			props.SetIconSize(32, 1, 4);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(Color.Black);
			props.SetFrontColor(Color.Green);
			props.SetTextVisible(true);
			props.SetIconVisible(true);
			props.Activate(true);
		
		item.SetProps(props);
		
		//WorkspaceWidget workspace = GetGame().GetWorkspace();
		//ResourceName layout = "{6B2B7AC257269983}UI/layouts/MapIcon.layout";

		//widget = workspace.CreateWidgets(layout);
		//ImageWidget iwg = ImageWidget.Cast(widget.FindAnyWidget("Image"));

		//ResourceName imageset = "{3EA91214A3CABFCC}UI/Imagesets/MapIcons.imageset";
		
		//iwg.LoadImageFromSet(0, imageset, "Flag");
		//iwg.SetImage(0);
		
		//widget.SetVisible(true);
	}
	
	void changeMarker()
	{
		MapDescriptorProps props = item.GetProps();
		
		Color color;
		switch (owner.getFactionKey())
			{
				case "USSR": color = color.Red; break;
				case "US": color = color.Blue; break;
				case "FIA": color = color.Green; break;
			}
		props.SetFrontColor(color);
	}

	void OnMapOpen()
	{
		if (!SCR_PlayerController.GetLocalControlledEntity()) return;

		Print("- MAP OPEN -");
	}
	
	void OnMapClose()
	{
		Print("- MAP CLOSE -");
	}

	void SCR_CTI_MapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		//SCR_MapEntity.GetOnMapOpen().Insert(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Insert(OnMapClose);
	}

	void ~SCR_CTI_MapDescriptorComponent()
	{
		//SCR_MapEntity.GetOnMapOpen().Remove(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Remove(OnMapClose);
	}
};