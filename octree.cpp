#include "octree.h"
#include "cloud.h"
#include "utils.h"

// -------------------
// Classe COctree_Node
// -------------------

COctree_Node::COctree_Node(void)
{	
	int i;
	State=4;Level=0;Father=NULL;
	Voxel.Put_Vertex(0,0,0,0);
	Voxel.Put_Vertex(1,1,0,0);
	Voxel.Put_Vertex(2,1,0,1);
	Voxel.Put_Vertex(3,0,0,1);
	Voxel.Put_Vertex(4,0,1,0);
	Voxel.Put_Vertex(5,1,1,0);
	Voxel.Put_Vertex(6,1,1,1);
	Voxel.Put_Vertex(7,0,1,1);
	for (i=0;i<8;i++)
		Sons[i]=NULL;
}

COctree_Node::~COctree_Node(void)
{}

COctree_Node::COctree_Node(COctree_Node * F, CVoxel_8 V,unsigned char S,unsigned char L)
{	
	int i;
	Father=F;State=S;Voxel=V;Level=L;IsLeaf=false;
	for (i=0;i<8;i++)
		Sons[i]=NULL;
}

unsigned char COctree_Node::Get_State(void)
{	return State;}

unsigned char COctree_Node::Get_Level(void)
{	return Level;}

COctree_Node * COctree_Node::Get_From_Type(unsigned char Type)
{
	if (Type==State)
		return this;
	else
		return NULL;
}

COctree_Node * COctree_Node::Get_Father(void)
{	return Father;}

void COctree_Node::Put_State(unsigned char S)
{	State=S;}

COctree_Node * COctree_Node::Get_Son(unsigned char Son_Number)
{
	if (Sons[Son_Number]!=NULL)
		return Sons[Son_Number];
	else
		return NULL;
}

void COctree_Node::Put_Level(unsigned char L)
{Level=L;}

CVoxel_8 COctree_Node::Get_Voxel(void)
{return Voxel;}

void COctree_Node::Compute_Octree_Cloud(QVector<QVector3D>& cloud,unsigned char Lmax)
{
	if (Level<=Lmax)
	{
		int i,nbpmax;
                QVector3D p;
		double px,py,pz;
		bool point_in=false,point2_in=false;

                nbpmax=cloud.size();
		for (i=0;i<nbpmax;i++)
		{
                        p=cloud[i];
                        px=p.x();py=p.y();pz=p.z();
                        if ((px>=Voxel.Get_Vertex(0).x())&&(px<=Voxel.Get_Vertex(1).x()))
                                if ((py>=Voxel.Get_Vertex(0).y())&&(py<=Voxel.Get_Vertex(4).y()))
                                        if ((pz>=Voxel.Get_Vertex(0).z())&&(pz<=Voxel.Get_Vertex(3).z()))
					{
						if (point_in==false)
							point_in=true;	// 1 point dans le voxel
						else
							point2_in=true; // 2 points dans le voxel
					}
			if (point2_in)
				i=nbpmax;
		}
		if (point_in)
		{
			State=1;
			if (point2_in)
			{
				if (Level<Lmax)
				{
					IsLeaf=false;
					CVoxel_8 V;
                                        QVector3D Vx(1,0,0),Vy(0,1,0),Vz(0,0,1);
					double vlength;

					// Longueur des voxels fils
                                        vlength=((Voxel.Get_Vertex(1).x()-Voxel.Get_Vertex(0).x())/2);

					// Voxel fils 0 en x min, y min , zmin
					V.Put_Vertex(0,Voxel.Get_Vertex(0));
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[0]=new COctree_Node(this,V,4,Level+1);
					Sons[0]->Compute_Octree_Cloud(cloud,Lmax);

					// Voxel fils 1 en x max, y min , zmin
					V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[1]=new COctree_Node(this,V,4,Level+1);
					Sons[1]->Compute_Octree_Cloud(cloud,Lmax);

					// Voxel fils 2 en x max, y min , zmax
					V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vx*vlength+Vz*vlength);
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[2]=new COctree_Node(this,V,4,Level+1);
					Sons[2]->Compute_Octree_Cloud(cloud,Lmax);

					// Voxel fils 3 en x min, y min , zmax
					V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[3]=new COctree_Node(this,V,4,Level+1);
					Sons[3]->Compute_Octree_Cloud(cloud,Lmax);

					// Voxel fils 0 en x min, y max , zmin
					V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[4]=new COctree_Node(this,V,4,Level+1);
					Sons[4]->Compute_Octree_Cloud(cloud,Lmax);

					// Voxel fils 1 en x max, y max , zmin
					V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength+Vx*vlength);
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[5]=new COctree_Node(this,V,4,Level+1);
					Sons[5]->Compute_Octree_Cloud(cloud,Lmax);

					// Voxel fils 2 en x max, y max , zmax
					V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength+Vx*vlength+Vz*vlength);
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[6]=new COctree_Node(this,V,4,Level+1);
					Sons[6]->Compute_Octree_Cloud(cloud,Lmax);

					// Voxel fils 3 en x min, y max , zmax
					V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength+Vz*vlength);
					V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
					V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
					V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
					V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
					V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
					V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
					V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
					Sons[7]=new COctree_Node(this,V,4,Level+1);
					Sons[7]->Compute_Octree_Cloud(cloud,Lmax);
				}
				else
					IsLeaf=true;
			}
			else
				IsLeaf=true;
		}
		else 
		{
			State=3;IsLeaf=true;
		}
	}
}

void COctree_Node::Compute_Octree_Voxellization(CVoxel_Tab VT,unsigned char Lmax, int i1, int i2, int j1, int j2, int k1, int k2)
{
	int i,j,k;
	bool Same=true;

	State=VT.Get_State(i1,j1,k1);
	for (i=i1;i<=i2;i++)
		for (j=j1;j<=j2;j++)
			for (k=k1;k<=k2;k++)
				if (VT.Get_State(i,j,k)!=State)
				{
					Same=false;
					State=4;
					break;
				}

	if (Same!=true)			// Tous les voxels correspondants à ce noeud de l'octree ne sont pas identiques
	{						// La subdivision doit être poursuivie
		if (Level<Lmax)		// Création des 8 noeuds fils
		{
			IsLeaf=false;	// Le noeud courant n'est donc pas une feuille
			CVoxel_8 V;
                        QVector3D Vx(1,0,0),Vy(0,1,0),Vz(0,0,1);
			double vlength;

			// Longueur des voxels fils
                        vlength=((Voxel.Get_Vertex(1).x()-Voxel.Get_Vertex(0).x())/2);

			// Voxel fils 0 en x min, y min , zmin
			V.Put_Vertex(0,Voxel.Get_Vertex(0));
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[0]=new COctree_Node(this,V,4,Level+1);
			Sons[0]->Compute_Octree_Voxellization(VT,Lmax,i1,(i1+i2)/2,j1,(j1+j2)/2,k1,(k1+k2)/2);

			// Voxel fils 1 en x max, y min , zmin
			V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[1]=new COctree_Node(this,V,4,Level+1);
			Sons[1]->Compute_Octree_Voxellization(VT,Lmax,1+(i1+i2)/2,i2,j1,(j1+j2)/2,k1,(k1+k2)/2);

			// Voxel fils 2 en x max, y min , zmax
			V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vx*vlength+Vz*vlength);
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[2]=new COctree_Node(this,V,4,Level+1);
			Sons[2]->Compute_Octree_Voxellization(VT,Lmax,1+(i1+i2)/2,i2,j1,(j1+j2)/2,1+(k1+k2)/2,k2);

			// Voxel fils 3 en x min, y min , zmax
			V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[3]=new COctree_Node(this,V,4,Level+1);
			Sons[3]->Compute_Octree_Voxellization(VT,Lmax,i1,(i1+i2)/2,j1,(j1+j2)/2,1+(k1+k2)/2,k2);

			// Voxel fils 0 en x min, y max , zmin
			V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[4]=new COctree_Node(this,V,4,Level+1);
			Sons[4]->Compute_Octree_Voxellization(VT,Lmax,i1,(i1+i2)/2,1+(j1+j2)/2,j2,k1,(k1+k2)/2);

			// Voxel fils 1 en x max, y max , zmin
			V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength+Vx*vlength);
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[5]=new COctree_Node(this,V,4,Level+1);
			Sons[5]->Compute_Octree_Voxellization(VT,Lmax,1+(i1+i2)/2,i2,1+(j1+j2)/2,j2,k1,(k1+k2)/2);

			// Voxel fils 2 en x max, y max , zmax
			V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength+Vx*vlength+Vz*vlength);
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[6]=new COctree_Node(this,V,4,Level+1);
			Sons[6]->Compute_Octree_Voxellization(VT,Lmax,1+(i1+i2)/2,i2,1+(j1+j2)/2,j2,1+(k1+k2)/2,k2);

			// Voxel fils 3 en x min, y max , zmax
			V.Put_Vertex(0,Voxel.Get_Vertex(0)+Vy*vlength+Vz*vlength);
			V.Put_Vertex(1,V.Get_Vertex(0)+Vx*vlength);
			V.Put_Vertex(2,V.Get_Vertex(1)+Vz*vlength);
			V.Put_Vertex(3,V.Get_Vertex(0)+Vz*vlength);
			V.Put_Vertex(4,V.Get_Vertex(0)+Vy*vlength);
			V.Put_Vertex(5,V.Get_Vertex(4)+Vx*vlength);
			V.Put_Vertex(6,V.Get_Vertex(5)+Vz*vlength);
			V.Put_Vertex(7,V.Get_Vertex(4)+Vz*vlength);
			Sons[7]=new COctree_Node(this,V,4,Level+1);
			Sons[7]->Compute_Octree_Voxellization(VT,Lmax,i1,(i1+i2)/2,1+(j1+j2)/2,j2,1+(k1+k2)/2,k2);
		}
		else
			IsLeaf=true;	// Feuille indéterminée
	}
	else
		IsLeaf=true; // "Grosse feuille" déterminée		

}

void COctree_Node::Draw_Box(unsigned char type)
{
	switch (type)
	{
	case 1:		
		break;
	default:
		break;
	}		
		Voxel.Draw();
}

void COctree_Node::Get_Leaves_Recursive(CList_Octree_Node &L_ON)
{
	
	if (IsLeaf)
		L_ON.Add_Octree_Node(*this);
	else
	{
		int i;
		for (i=0;i<8;i++)
			Sons[i]->Get_Leaves_Recursive(L_ON);
	}
	
}

void COctree_Node::Delete_If_Empty_Sons(void)
{
	int i;

	for (i=0;i<8;i++)
		if (Sons[i]!=NULL)
			Sons[i]->Delete_If_Empty_Sons();
	this->~COctree_Node();
}

// -------------------------
// class CListed_Octree_Node
// -------------------------

CListed_Octree_Node::CListed_Octree_Node(void)
{Next=NULL;}

CListed_Octree_Node::~CListed_Octree_Node(void)
{}

CListed_Octree_Node * CListed_Octree_Node::Get_Next(void)
{return Next;}

void CListed_Octree_Node::Put_Next(CListed_Octree_Node *N)
{Next=N;}

// -----------------------
// class CList_Octree_Node
// -----------------------
CList_Octree_Node::CList_Octree_Node(void)
{
First=Last=NULL;NBN=0;
}

int CList_Octree_Node::Get_NBN(void)
{
return NBN;
}

void CList_Octree_Node::Add_Octree_Node(COctree_Node O_N)
{
	if (NBN==0)
	{
		First=new CListed_Octree_Node;
		Last=First;
		First->State=O_N.State;First->Level=O_N.Level;First->Father=O_N.Father;
		First->Voxel=O_N.Voxel;
		int i; for (i=0;i<8;i++) First->Sons[i]=O_N.Sons[i];
		First->IsLeaf=O_N.IsLeaf;
		First->Next=NULL;
		NBN=1;
	}
	else
	{
		Last->Next=new CListed_Octree_Node;
		Last=Last->Next;
		Last->State=O_N.State;Last->Level=O_N.Level;Last->Father=O_N.Father;
		Last->Voxel=O_N.Voxel;
		int i; for (i=0;i<8;i++) Last->Sons[i]=O_N.Sons[i];
		Last->IsLeaf=O_N.IsLeaf;
		Last->Next=NULL;
		NBN++;
	}
}

void CList_Octree_Node::Draw(unsigned char S)
{
	CListed_Octree_Node *Current;

	float frose[4]={0.807,0.462,0.670,0.0};
        //float frouge[4]={1.0,0.0,0.0,0.0};
	float fvert[4]={0.0,1.0,0.0,1.0};
	float fbleu[4]={0.14,0.21,0.6,0.0};
	float fjaune[4]={1.0,1.0,0.0,0.0};
        //float fjaunevert[4]={0.7,1.0,0.0,0.0};

	switch (S)
	{
		case 0:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,fjaune);
		break;
		case 1:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,fvert);
		break;
		case 2:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,fbleu);
		break;
		case 3:
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,frose);
		break;
	}
	Current=First;
	do
	{
		if (Current->State==S)
			Current->Voxel.Draw();
		Current=Current->Next;
	} 
	while (Current->Next!=NULL);
	if (Current->State==S)
			Current->Voxel.Draw();
}

void CList_Octree_Node::Delete_List(void)
{
	CListed_Octree_Node *Current;

	Current=First;
	do
	{	if (Current->Next!=NULL)
			Current=Current->Next;
		delete First;
		First=Current;
	} 
	while (Current!=Last);

	delete First;

	First=Last=NULL;NBN=0;
}

// --------------
// Classe COctree
// --------------

COctree::COctree(void)
{Root=NULL;Level=0;}

COctree::COctree(CVoxel_8 V)
{Root=new COctree_Node(NULL,V,4,0);Level=0;}

COctree_Node * COctree::Get_root(void)
{
	if (Root!=NULL)
		return Root;
	else return
		NULL;
}

void COctree::Compute_Octree_Cloud(QVector<QVector3D>& cloud,unsigned char Lmax)
{
	if (Root!=NULL)
	{
		Root->Compute_Octree_Cloud(cloud,Lmax);
	}
	else
        {
                Root=new COctree_Node(NULL,Cloud(cloud).boundingBox(),4,0);
		Level=Lmax;
		Root->Compute_Octree_Cloud(cloud,Level);
	}
}

void COctree::Find_List_Leaves(CList_Octree_Node &L_ON)
{
	if (Root!=NULL)
		Root->Get_Leaves_Recursive(L_ON);	
	else
		printf("Arbre octal Vide !!!\n");
}

void COctree::Create_From_Voxellization(CVoxel_Tab VT)
{
	if (Level==0)
	{
		Root=new COctree_Node(NULL,VT.Get_BBox(),4,0);
		Level=Find_Square_Power(VT.Get_Dimx());
		Root->Compute_Octree_Voxellization(VT,Level,0,VT.Get_Dimx()-1,0,VT.Get_Dimy()-1,0,VT.Get_Dimz()-1);

	}
}

void COctree::Draw_Boxes(unsigned char)
{
	if (Root!=NULL)
	{
		

	}

}

void COctree::Clear_Octree(void)
{
	Root->Delete_If_Empty_Sons();
	Root=NULL;Level=0;
}





