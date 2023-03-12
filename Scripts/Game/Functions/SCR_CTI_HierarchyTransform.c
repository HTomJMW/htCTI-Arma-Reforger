class SCR_CTI_HierarchyTransform
{
	//------------------------------------------------------------------------------------------------
	//SCR_EntityHelper's function without dynamic physics test
	static void SetHierarchyTransform(notnull IEntity ent, vector newTransform[4])
	{
		vector oldTransform[4];
		ent.GetTransform(oldTransform);
		ent.SetTransform(newTransform);

		IEntity child = ent.GetChildren();
		while (child)
		{
			SetHierarchyChildTransform(child, oldTransform, newTransform, true);
			child = child.GetSibling();
		}
	}

	//------------------------------------------------------------------------------------------------
	protected static void SetHierarchyChildTransform(notnull IEntity ent, vector oldTransform[4], vector newTransform[4], bool recursive = true)
	{
		vector mat[4];
		ent.GetTransform(mat);

		vector diffMat[4];
		Math3D.MatrixInvMultiply4(oldTransform, mat, diffMat);
		Math3D.MatrixMultiply4(newTransform, diffMat, mat);

		ent.SetTransform(mat);

		IEntity child = ent.GetChildren();
		while (child)
		{
			SetHierarchyChildTransform(child, oldTransform, newTransform, recursive);
			child = child.GetSibling();
		}
	}
};