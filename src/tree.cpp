#include "main.h"

void CNode_Interval_3D::Set_Node(long double xbi,long double xbs,long double ybi,long double ybs,long double zbi,long double zbs)
{
	Node.Set(xbi,xbs,ybi,ybs,zbi,zbs);
}

CNode <CInterval_3D>* CTree_Interval_3D::Get_Root(void)
{
	return Root;
}

CNode <CInterval_3D> CTree_Interval_3D::Get_Root_Value(void)
{
	return *Root;
}

void CTree_Interval_3D::Set_Root (CNode <CInterval_3D>* INode)
{
	if (Root==NULL)
		Root=new CNode <CInterval_3D>;
	Root=INode;
}

void CTree_Interval_3D::Set_Root (CNode <CInterval_3D> INode)
{
	if (Root==NULL)
		Root=new CNode <CInterval_3D>;
	*Root=INode;
}

void CTree_Interval_3D::Set_Root (long double xbi,long double xbs,long double ybi,long double ybs,long double zbi,long double zbs)
{
	if (Root==NULL)
		Root=new CNode <CInterval_3D>;
	static_cast<CNode_Interval_3D *>(Root)->Set_Node(xbi,xbs,ybi,ybs,zbi,zbs);
	

}