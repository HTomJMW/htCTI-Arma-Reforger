[EntityEditorProps(category: "GameScripted/CTI", description: "CTI Defense Data Structure")]
class SCR_CTI_DefenseData
{
	protected ResourceName res;
	protected string name;
	protected int pri;
	protected int bt;
	protected int dis;
	protected int pla;
	protected string scr;
	
	void setData(ResourceName newres, string newname, int newpri, int newbt, int newdis, int newpla, string newscr)
	{
		res = newres;
		name = newname;
		pri = newpri;
		bt = newbt;
		dis = newdis;
		pla = newpla;
		scr = newscr;
	}
	
	ResourceName getRes()
	{
		return res;
	}

	string getName()
	{
		return name;
	}
	
	int getPri()
	{
		return pri;
	}
	
	int getBt()
	{
		return bt;
	}
	
	int getDis()
	{
		return dis;
	}
	
	int getPla()
	{
		return pla;
	}
	
	string getScr()
	{
		return scr;
	}
	
	void SCR_CTI_DefenseData()
	{
	}
		
	void ~SCR_CTI_DefenseData()
	{
	}
};