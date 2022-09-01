modded enum ChimeraMenuPreset
{
	CTI_GUI_BuildMenu
};

class SCR_CTI_BuildMenu : ChimeraMenuBase
{
	protected Widget m_wRoot;
	protected WindowWidget m_window;
	protected TextWidget m_resources;
	protected TextWidget m_workers;
	protected ButtonWidget m_addworker;
	protected ButtonWidget m_buildstructure;
	protected ButtonWidget m_undostructure;
	protected ButtonWidget m_defautomanning;
	protected ButtonWidget m_autoalignwalls;
	protected ButtonWidget m_builddefense;
	protected ButtonWidget m_undodefense;
	protected ButtonWidget m_exit;
	
	override void OnMenuInit()
	{
		m_wRoot = GetRootWidget();
		m_window = WindowWidget.Cast(m_wRoot.FindAnyWidget("Window"));
		m_resources = TextWidget.Cast(m_wRoot.FindAnyWidget("Resources"));
		m_workers = TextWidget.Cast(m_wRoot.FindAnyWidget("Workers"));
		m_addworker = ButtonWidget.Cast(m_wRoot.FindAnyWidget("AddWorker"));
		m_buildstructure = ButtonWidget.Cast(m_wRoot.FindAnyWidget("BuildStructure"));
		m_undostructure = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UndoStructure"));
		m_defautomanning = ButtonWidget.Cast(m_wRoot.FindAnyWidget("DefAutoManning"));
		m_autoalignwalls = ButtonWidget.Cast(m_wRoot.FindAnyWidget("AutoAlignWalls"));
		m_builddefense = ButtonWidget.Cast(m_wRoot.FindAnyWidget("BuildDefense"));
		m_undodefense = ButtonWidget.Cast(m_wRoot.FindAnyWidget("UndoDefense"));
		m_exit = ButtonWidget.Cast(m_wRoot.FindAnyWidget("Exit"));
		
		//m_window.SetVisible(true);
		m_resources.SetText("Resources: ");
		//m_resources.SetVisible(true);
		m_workers.SetText("Workers: ");
		m_addworker.SetColor(Color.Orange);
		m_buildstructure.SetColor(Color.Orange);
		m_undostructure.SetColor(Color.Orange);
		m_defautomanning.SetColor(Color.Orange);
		m_autoalignwalls.SetColor(Color.Orange);
		m_builddefense.SetColor(Color.Orange);
		m_undodefense.SetColor(Color.Orange);
		m_exit.SetColor(Color.Red);
	}
	
	override void OnMenuOpen()
	{
		Print("!!!! BUILD MENU !!!!");
	}
};