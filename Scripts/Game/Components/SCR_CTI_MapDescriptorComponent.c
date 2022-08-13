[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup town markers.")]
class SCR_CTI_MapDescriptorComponentClass: MapDescriptorComponentClass
{
};

class SCR_CTI_MapDescriptorComponent: MapDescriptorComponent
{
	protected MapItem item;
	protected SCR_CTI_Town owner;
	
	void init()
	{
		item = Item();
		owner = SCR_CTI_Town.Cast(item.Entity());
		item.SetDisplayName(owner.getTownName());
		item.SetBaseType(85); // task marker
		
		MapDescriptorProps props = item.GetProps();
			props.SetIconSize(50, 20, 50);
			props.SetTextSize(50, 20, 50);
			props.SetTextColor(Color(0, 0, 0, 1));
			props.SetFrontColor(Color(0, 0, 0, 1));
		item.SetProps(props);
	}
	
	void SCR_CTI_MapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	void ~SCR_CTI_MapDescriptorComponent()
	{
	}
};