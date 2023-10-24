class SCR_CTI_Helper
{
	//------------------------------------------------------------------------------------------------
	static IEntity GetCursorTarget()
	{
		IEntity cursorTarget = null;
		CameraManager cameraManager = GetGame().GetCameraManager();
		CameraBase current = cameraManager.CurrentCamera();
		cursorTarget = current.GetCursorTarget();

		return cursorTarget;
	}
};