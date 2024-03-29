[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup town markers.")]
class SCR_CTI_TownMapDescriptorComponentClass : SCR_MapDescriptorComponentClass
{
};

class SCR_CTI_TownMapDescriptorComponent : SCR_MapDescriptorComponent
{
	protected MapItem m_item;
	protected SCR_CTI_Town m_owner;

	//------------------------------------------------------------------------------------------------
	void createMarker(FactionKey factionkey)
	{
		Color orig = Color.Green;
		switch (factionkey)
		{
			case "USSR": orig = Color.Red; break;
			case "US": orig = Color.Blue; break;
			case "FIA": orig = Color.Green; break;
		}
		orig.SetA(0.7);
		
		m_item = Item();

		m_item.SetDisplayName(/*m_owner.getTownName() + "\n" + */m_owner.getTownValue().ToString());
		m_item.SetBaseType(EMapDescriptorType.MDT_ICON);
		m_item.SetImageDef("CTI_TOWN");
		m_item.SetPriority(5);

		MapDescriptorProps props = m_item.GetProps();
			props.SetDetail(96);
			props.SetIconSize(256, 1, 1);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(Color.Black);
			props.SetFrontColor(orig);
			props.SetTextVisible(true);
			props.SetIconVisible(true);
			props.Activate(true);
		
		m_item.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	void changeMarker(FactionKey factionkey)
	{
		MapDescriptorProps props = m_item.GetProps();
		
		Color color;
		switch (factionkey)
			{
				case "USSR": color = color.Red; break;
				case "US": color = color.Blue; break;
				case "FIA": color = color.Green; break;
			}
		color.SetA(0.7);
		props.SetFrontColor(color);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_TownMapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_owner = SCR_CTI_Town.Cast(ent);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_TownMapDescriptorComponent()
	{
	}
};