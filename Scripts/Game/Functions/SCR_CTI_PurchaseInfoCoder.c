class SCR_CTI_PurchaseInfoCoder
{
	//------------------------------------------------------------------------------------------------
	CTI_PurchaseInfos enCode(bool driver, bool gunner, bool commander, bool crew, bool locked)
	{
		CTI_PurchaseInfos infos;
		
		switch (true)
		{
			case (driver == false && gunner == false && commander == false && crew == false && locked == false):	infos = CTI_PurchaseInfos.EMPTY_OPEN; break;
			case (driver == false && gunner == false && commander == false && crew == false && locked == true):		infos = CTI_PurchaseInfos.EMPTY_LOCKED; break;

			case (driver == true && gunner == false && commander == false && crew == false && locked == false):		infos = CTI_PurchaseInfos.DRIVER_OPEN; break;
			case (driver == true && gunner == false && commander == false && crew == false && locked == true):		infos = CTI_PurchaseInfos.DRIVER_LOCKED; break;

			case (driver == false && gunner == true && commander == false && crew == false && locked == false):		infos = CTI_PurchaseInfos.GUNNER_OPEN; break;
			case (driver == false && gunner == true && commander == false && crew == false && locked == true):		infos = CTI_PurchaseInfos.GUNNER_LOCKED; break;

			case (driver == false && gunner == false && commander == true && crew == false && locked == false):		infos = CTI_PurchaseInfos.COMMANDER_OPEN; break;
			case (driver == false && gunner == false && commander == true && crew == false && locked == true):		infos = CTI_PurchaseInfos.COMMANDER_LOCKED; break;

			case (driver == false && gunner == false && commander == false && crew == true && locked == false):		infos = CTI_PurchaseInfos.CREW_OPEN; break;
			case (driver == false && gunner == false && commander == false && crew == true && locked == true):		infos = CTI_PurchaseInfos.CREW_LOCKED; break;

			case (driver == true && gunner == true && commander == false && crew == false && locked == false):		infos = CTI_PurchaseInfos.DRIVER_GUNNER_OPEN; break;
			case (driver == true && gunner == true && commander == false && crew == false && locked == true):		infos = CTI_PurchaseInfos.DRIVER_GUNNER_LOCKED; break;

			case (driver == true && gunner == false && commander == true && crew == false && locked == false):		infos = CTI_PurchaseInfos.DRIVER_COMMANDER_OPEN; break;
			case (driver == true && gunner == false && commander == true && crew == false && locked == true):		infos = CTI_PurchaseInfos.DRIVER_COMMANDER_LOCKED; break;

			case (driver == true && gunner == false && commander == false && crew == true && locked == false):		infos = CTI_PurchaseInfos.DRIVER_CREW_OPEN; break;
			case (driver == true && gunner == false && commander == false && crew == true && locked == true):		infos = CTI_PurchaseInfos.DRIVER_CREW_LOCED; break;

			case (driver == true && gunner == true && commander == true && crew == false && locked == false):		infos = CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_OPEN; break;
			case (driver == true && gunner == true && commander == true && crew == false && locked == true):		infos = CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_LOCKED; break;

			case (driver == true && gunner == true && commander == true && crew == true && locked == false):		infos = CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_CREW_OPEN; break;
			case (driver == true && gunner == true && commander == true && crew == true && locked == true):			infos = CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_CREW_LOCKED; break;

			case (driver == true && gunner == true && commander == false && crew == true && locked == false):		infos = CTI_PurchaseInfos.DRIVER_GUNNER_CREW_OPEN; break;
			case (driver == true && gunner == true && commander == false && crew == true && locked == true):		infos = CTI_PurchaseInfos.DRIVER_GUNNER_CREW_LOCKED; break;

			case (driver == true && gunner == false && commander == true && crew == true && locked == false):		infos = CTI_PurchaseInfos.DRIVER_COMMANDER_CREW_OPEN; break;
			case (driver == true && gunner == false && commander == true && crew == true && locked == true):		infos = CTI_PurchaseInfos.DRIVER_COMMANDER_CREW_LOCKED; break;

			case (driver == false && gunner == true && commander == true && crew == false && locked == false):		infos = CTI_PurchaseInfos.GUNNER_COMMANDER_OPEN; break;
			case (driver == false && gunner == true && commander == true && crew == false && locked == true):		infos = CTI_PurchaseInfos.GUNNER_COMMANDER_LOCKED; break;

			case (driver == false && gunner == true && commander == false && crew == true && locked == false):		infos = CTI_PurchaseInfos.GUNNER_CREW_OPEN; break;
			case (driver == false && gunner == true && commander == false && crew == true && locked == true):		infos = CTI_PurchaseInfos.GUNNER_CREW_LOCKED; break;

			case (driver == false && gunner == true && commander == true && crew == true && locked == false):		infos = CTI_PurchaseInfos.GUNNER_COMMANDER_CREW_OPEN; break;
			case (driver == false && gunner == true && commander == true && crew == true && locked == true):		infos = CTI_PurchaseInfos.GUNNER_COMMANDER_CREW_LOCKED; break;

			case (driver == false && gunner == false && commander == true && crew == true && locked == false):		infos = CTI_PurchaseInfos.COMMANDER_CREW_OPEN; break;
			case (driver == false && gunner == false && commander == true && crew == true && locked == true):		infos = CTI_PurchaseInfos.COMMANDER_CREW_LOCKED; break;

			default:																								infos = CTI_PurchaseInfos.EMPTY_OPEN; break;
		}
		
		return infos;
	}

	//------------------------------------------------------------------------------------------------
	void deCode(out bool driver, out bool gunner, out bool commander, out bool crew, out bool locked, CTI_PurchaseInfos infos)
	{	
		switch (infos)
		{
			case (CTI_PurchaseInfos.EMPTY_OPEN):							driver = false; gunner = false; commander = false; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.EMPTY_LOCKED):							driver = false; gunner = false; commander = false; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_OPEN):							driver = true; gunner = false; commander = false; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_LOCKED):							driver = true; gunner = false; commander = false; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.GUNNER_OPEN):							driver = false; gunner = true; commander = false; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.GUNNER_LOCKED):							driver = false; gunner = true; commander = false; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.COMMANDER_OPEN):						driver = false; gunner = false; commander = true; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.COMMANDER_LOCKED):						driver = false; gunner = false; commander = true; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.CREW_OPEN):								driver = false; gunner = false; commander = false; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.CREW_LOCKED):							driver = false; gunner = false; commander = false; crew = true; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_GUNNER_OPEN):					driver = true; gunner = true; commander = false; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_GUNNER_LOCKED):					driver = true; gunner = true; commander = false; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_COMMANDER_OPEN):					driver = true; gunner = false; commander = true; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_COMMANDER_LOCKED):				driver = true; gunner = false; commander = true; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_CREW_OPEN):						driver = true; gunner = false; commander = false; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_CREW_LOCED):						driver = true; gunner = false; commander = false; crew = true; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_OPEN):			driver = true; gunner = true; commander = true; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_LOCKED):		driver = true; gunner = true; commander = true; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_CREW_OPEN):		driver = true; gunner = true; commander = true; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_GUNNER_COMMANDER_CREW_LOCKED):	driver = true; gunner = true; commander = true; crew = true; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_GUNNER_CREW_OPEN):				driver = true; gunner = true; commander = false; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_GUNNER_CREW_LOCKED):				driver = true; gunner = true; commander = false; crew = true; locked = true; break;

			case (CTI_PurchaseInfos.DRIVER_COMMANDER_CREW_OPEN):			driver = true; gunner = false; commander = true; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.DRIVER_COMMANDER_CREW_LOCKED):			driver = true; gunner = false; commander = true; crew = true; locked = true; break;

			case (CTI_PurchaseInfos.GUNNER_COMMANDER_OPEN):					driver = false; gunner = true; commander = true; crew = false; locked = false; break;
			case (CTI_PurchaseInfos.GUNNER_COMMANDER_LOCKED):				driver = false; gunner = true; commander = true; crew = false; locked = true; break;

			case (CTI_PurchaseInfos.GUNNER_CREW_OPEN):						driver = false; gunner = true; commander = false; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.GUNNER_CREW_LOCKED):					driver = false; gunner = true; commander = false; crew = true; locked = true; break;

			case (CTI_PurchaseInfos.GUNNER_COMMANDER_CREW_OPEN):			driver = false; gunner = true; commander = true; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.GUNNER_COMMANDER_CREW_LOCKED):			driver = false; gunner = true; commander = true; crew = true; locked = true; break;

			case (CTI_PurchaseInfos.COMMANDER_CREW_OPEN):					driver = false; gunner = false; commander = true; crew = true; locked = false; break;
			case (CTI_PurchaseInfos.COMMANDER_CREW_LOCKED):					driver = false; gunner = false; commander = true; crew = true; locked = true; break;
		}
	}
};