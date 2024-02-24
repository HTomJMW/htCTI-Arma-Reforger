[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup flag markers.")]
class SCR_CTI_FlagMapDescriptorComponentClass : SCR_MapDescriptorComponentClass
{
};

class SCR_CTI_FlagMapDescriptorComponent : SCR_MapDescriptorComponent
{
	protected MapItem m_item;

	//------------------------------------------------------------------------------------------------
	void createMarker()
	{
		Color orig = Color.Black;
		orig.SetA(0.8);
		
		m_item = Item();

		m_item.SetDisplayName("");
		m_item.SetBaseType(EMapDescriptorType.MDT_ICON);
		m_item.SetImageDef("CTI_FLAG");
		m_item.SetPriority(3);

		MapDescriptorProps props = m_item.GetProps();
			props.SetDetail(96);
			props.SetIconSize(128, 0.1, 0.4);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(Color.Black);
			props.SetFrontColor(orig);
			props.SetTextVisible(false);
			props.SetIconVisible(true);
			props.Activate(true);
		
		m_item.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_FlagMapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		GetGame().GetCallqueue().CallLater(createMarker, 2000, false);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_FlagMapDescriptorComponent()
	{
	}
};