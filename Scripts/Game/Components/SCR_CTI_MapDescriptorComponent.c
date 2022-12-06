[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup town markers.")]
class SCR_CTI_MapDescriptorComponentClass : SCR_MapDescriptorComponentClass
{
};

class SCR_CTI_MapDescriptorComponent : SCR_MapDescriptorComponent
{
	protected MapItem m_item;
	protected SCR_CTI_Town m_owner;
	protected string m_marker = "Flag";

	//------------------------------------------------------------------------------------------------
	void init()
	{
		m_item = Item();
		m_owner = SCR_CTI_Town.Cast(m_item.Entity());
		
		m_item.SetDisplayName(m_owner.getTownName() + "\n" + m_owner.getTownValue().ToString());
		m_item.SetBaseType(EMapDescriptorType.MDT_ICON);
		
		MapDescriptorProps props = m_item.GetProps();
			m_item.SetImageDef(m_marker);
			props.SetDetail(96);
			props.SetIconSize(32, 1, 4);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(Color.Black);
			Color orig = Color.Green;
			orig.SetA(0.8);
			props.SetFrontColor(orig);
			props.SetTextVisible(true);
			props.SetIconVisible(true);
			props.Activate(true);
		
		m_item.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	void changeMarker()
	{
		MapDescriptorProps props = m_item.GetProps();
		
		Color color;
		switch (m_owner.getFactionKey())
			{
				case "USSR": color = color.Red; break;
				case "US": color = color.Blue; break;
				case "FIA": color = color.Green; break;
			}
		color.SetA(0.8);
		props.SetFrontColor(color);
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
	void SCR_CTI_MapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		//SCR_MapEntity.GetOnMapOpen().Insert(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Insert(OnMapClose);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_MapDescriptorComponent()
	{
		//SCR_MapEntity.GetOnMapOpen().Remove(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Remove(OnMapClose);
	}
};