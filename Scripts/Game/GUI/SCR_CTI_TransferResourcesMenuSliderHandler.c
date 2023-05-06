class SCR_CTI_TransferResourcesMenuSliderHandler : ScriptedWidgetEventHandler
{
	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		EditBoxWidget ebw = EditBoxWidget.Cast(w.GetParent().FindAnyWidget("EditBox"));
		SliderWidget sw = SliderWidget.Cast(w);
		ebw.SetText(sw.GetCurrent().ToString());
	
		return true;
	}
};