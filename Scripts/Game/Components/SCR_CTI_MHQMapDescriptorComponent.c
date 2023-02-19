[ComponentEditorProps(category: "GameScripted/CTI", description: "CTI Setup MHQ markers.")]
class SCR_CTI_MHQMapDescriptorComponentClass : SCR_MapDescriptorComponentClass
{
};

class SCR_CTI_MHQMapDescriptorComponent : SCR_MapDescriptorComponent
{
	protected SCR_CTI_GameMode m_gamemode;
	protected ResourceName m_resname;
	protected IEntity m_owner;
	protected MapItem m_mapitem;
	protected Color m_textcolor = Color.Black;
	
	//------------------------------------------------------------------------------------------------
	void init()
	{
		if (m_resname == SCR_CTI_Constants.USSRMHQ)
		{
			m_textcolor = Color.Red;
		} else {
			m_textcolor = Color.Blue;
		}

		m_mapitem = Item();

		MapDescriptorProps props = m_mapitem.GetProps();
			props.SetDetail(96);
			props.SetIconSize(16, 1, 2);
			props.SetTextSize(32, 16, 64);
			props.SetTextColor(m_textcolor);
			props.SetTextBold();
			props.SetTextVisible(true);
			props.SetIconVisible(false);
			props.Activate(true);
		
		m_mapitem.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	void markAsDestroyed(bool value)
	{
		Color color;
		if (value)
		{
			color = Color.Black;
		} else {
			color = m_textcolor;
		}
		
		MapItem item = Item();
		MapDescriptorProps props = item.GetProps();
			props.SetTextColor(color);
		
		item.SetProps(props);
	}

	//------------------------------------------------------------------------------------------------
	void OnMapOpen()
	{
		if (!SCR_PlayerController.GetLocalControlledEntity()) return;
		
		SCR_DamageManagerComponent dmc = SCR_DamageManagerComponent.Cast(m_owner.FindComponent(SCR_DamageManagerComponent));
		if (dmc && dmc.IsDestroyed()) markAsDestroyed(true); else markAsDestroyed(false);
	}

	//------------------------------------------------------------------------------------------------
	void OnMapClose()
	{
	}

	//------------------------------------------------------------------------------------------------
	void SCR_CTI_MHQMapDescriptorComponent(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
		m_gamemode = SCR_CTI_GameMode.Cast(GetGame().GetGameMode());
		m_resname = ent.GetPrefabData().GetPrefabName();
		m_owner = ent;
		
		// Call init function after 3s (wait until object ready for use)
		GetGame().GetCallqueue().CallLater(init, 3000);

		SCR_MapEntity.GetOnMapOpen().Insert(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Insert(OnMapClose);
	}

	//------------------------------------------------------------------------------------------------
	void ~SCR_CTI_MHQMapDescriptorComponent()
	{
		SCR_MapEntity.GetOnMapOpen().Remove(OnMapOpen);
		//SCR_MapEntity.GetOnMapClose().Remove(OnMapClose);
	}
};