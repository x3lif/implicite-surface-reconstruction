#include "voxel.h"
#include "utils.h"
#include "cloud.h"
#include "renderer.h"
#include <QDebug>

// --------------
// class CVoxel_8
// --------------

int FastVoxelization = 0;

CVoxel_8::CVoxel_8(void)
{First=Last=NULL;}

QVector3D CVoxel_8::Get_Vertex(int i) const
{return Vertex[i];}

void CVoxel_8::Put_Vertex(int i,QVector3D p)
{
	Vertex[i]=p;
	//arrayList();
	// erase vertexArray in order to generate it at the next draw
	mVertexArrayList.clear();
}

void CVoxel_8::Put_Vertex(int i,double x,double y, double z)
{
	QVector3D lNewVertex(x,y,z);
	Vertex[i] = lNewVertex;
	//Vertex[i].Put_x(x);Vertex[i].Put_y(y);Vertex[i].Put_z(z);
	//arrayList();
	// erase vertexArray in order to generate it at the next draw
	mVertexArrayList.clear();
}

void CVoxel_8::Voxel_Info(void)
{
	int i;

	for(i=0;i<8;i++)
	{
		//qWarning()<<"Sommet "<<i<<":";
		//Vertex[i].Point_Info();
		qWarning()<<"Point "<<i<<": "<<Vertex[i].x()<<" "<<Vertex[i].y()<<" "<<Vertex[i].z();
		//printf("\n");
	}
}

void CVoxel_8::Set_Voxel(	QVector3D V0,QVector3D V1,QVector3D V2,QVector3D V3,
							QVector3D V4,QVector3D V5,QVector3D V6,QVector3D V7)
{
	Vertex[0]=V0;
	Vertex[1]=V1;
	Vertex[2]=V2;
	Vertex[3]=V3;
	Vertex[4]=V4;
	Vertex[5]=V5;
	Vertex[6]=V6;
	Vertex[7]=V7;

	// erase vertexArray in order to generate it at the next draw
	mVertexArrayList.clear();
}

CVoxel_8 &CVoxel_8::operator = (const CVoxel_8 &V)
{	
	int i;

	for(i=0;i<8;i++)
		Vertex[i]=V.Get_Vertex(i);
	return *this;
}

void CVoxel_8::arrayList() {
	mVertexArrayList.clear();
	mVertexArrayList<<Vertex[0].x()<<Vertex[0].y()<<Vertex[0].z();
	mVertexArrayList<<Vertex[4].x()<<Vertex[4].y()<<Vertex[4].z();
	mVertexArrayList<<Vertex[5].x()<<Vertex[5].y()<<Vertex[5].z();
	mVertexArrayList<<Vertex[1].x()<<Vertex[1].y()<<Vertex[1].z();

	mVertexArrayList<<Vertex[6].x()<<Vertex[6].y()<<Vertex[6].z();
	mVertexArrayList<<Vertex[2].x()<<Vertex[2].y()<<Vertex[2].z();
	mVertexArrayList<<Vertex[1].x()<<Vertex[1].y()<<Vertex[1].z();
	mVertexArrayList<<Vertex[5].x()<<Vertex[5].y()<<Vertex[5].z();

	mVertexArrayList<<Vertex[5].x()<<Vertex[5].y()<<Vertex[5].z();
	mVertexArrayList<<Vertex[4].x()<<Vertex[4].y()<<Vertex[4].z();
	mVertexArrayList<<Vertex[7].x()<<Vertex[7].y()<<Vertex[7].z();
	mVertexArrayList<<Vertex[6].x()<<Vertex[6].y()<<Vertex[6].z();

	mVertexArrayList<<Vertex[0].x()<<Vertex[0].y()<<Vertex[0].z();
	mVertexArrayList<<Vertex[3].x()<<Vertex[3].y()<<Vertex[3].z();
	mVertexArrayList<<Vertex[7].x()<<Vertex[7].y()<<Vertex[7].z();
	mVertexArrayList<<Vertex[4].x()<<Vertex[4].y()<<Vertex[4].z();

	mVertexArrayList<<Vertex[0].x()<<Vertex[0].y()<<Vertex[0].z();
	mVertexArrayList<<Vertex[1].x()<<Vertex[1].y()<<Vertex[1].z();
	mVertexArrayList<<Vertex[2].x()<<Vertex[2].y()<<Vertex[2].z();
	mVertexArrayList<<Vertex[3].x()<<Vertex[3].y()<<Vertex[3].z();

	mVertexArrayList<<Vertex[6].x()<<Vertex[6].y()<<Vertex[6].z();
	mVertexArrayList<<Vertex[7].x()<<Vertex[7].y()<<Vertex[7].z();
	mVertexArrayList<<Vertex[3].x()<<Vertex[3].y()<<Vertex[3].z();
	mVertexArrayList<<Vertex[2].x()<<Vertex[2].y()<<Vertex[2].z();
}

void CVoxel_8::Draw(void)
{
	if(mVertexArrayList.size() == 0)	arrayList();

	// TODO : Use Array Lists
	glColor3f(0.0,0.0,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mVertexArrayList.data());
		glDrawArrays(GL_QUADS, 0, 4);
		glDrawArrays(GL_QUADS, 4, 4);
		glDrawArrays(GL_QUADS, 8, 4);
		glDrawArrays(GL_QUADS, 12, 4);
		glDrawArrays(GL_QUADS, 16, 4);
		glDrawArrays(GL_QUADS, 20, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CVoxel_8::Draw_Lines(void)
{
	if(mVertexArrayList.size() == 0)	arrayList();

	glColor3f(0.0,0.0,1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, mVertexArrayList.data());
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		glDrawArrays(GL_LINE_LOOP, 4, 4);
		glDrawArrays(GL_LINE_LOOP, 8, 4);
		glDrawArrays(GL_LINE_LOOP, 12, 4);
		glDrawArrays(GL_LINE_LOOP, 16, 4);
		glDrawArrays(GL_LINE_LOOP, 20, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor3f(1.0,1.0,1.0);
}

// ----------------
// class CVoxel_Tab
// ----------------

CVoxel_Tab::CVoxel_Tab(void)
{Voxels=NULL;States=NULL;Dimx=Dimy=Dimz=0;FSV=LSV=NULL;}

CVoxel_Tab::CVoxel_Tab(int x_Dim,int y_Dim,int z_Dim)
{
//	int i,j;
	Dimx=x_Dim;Dimy=y_Dim;Dimz=z_Dim;
	/*Voxels=new CVoxel_8** [Dimx];
	for (i=0;i<Dimx;i++)
	{
		Voxels[i]=new CVoxel_8* [Dimy];
		for (j=0;j<Dimy;j++)
			Voxels[i][j]=new CVoxel_8 [Dimz];
	}

	States=new unsigned char**[Dimx];
	for (i=0;i<Dimx;i++)
	{
		States[i]=new unsigned char* [Dimy];
		for (j=0;j<Dimy;j++)
			States[i][j]=new unsigned char [Dimz];
	}*/
	// Construction du QVector de voxels
	QVector<QVector<QVector< CVoxel_8> > > Voxels(Dimx);
	for(int i=0;i<Dimx;i++){
		Voxels[i].resize(Dimy);
		for(int j=0;j<Dimy;j++){
			Voxels[i][j].resize(Dimz);
		}
	}
	qWarning()<<"vox s"<<Voxels.size()<<" "<<Voxels[Dimx-1].size()<<" "<<Voxels[Dimx-1][Dimy-1].size();
	//Construction du tableau d'états
	QVector<QVector<QVector< unsigned char> > > States(Dimx);
	for(int i=0;i<Dimx;i++){
		States[i].resize(Dimy);
		for(int j=0;j<Dimy;j++){
			States[i][j].resize(Dimz);
		}
	}

	qWarning()<<"states s"<<States.size()<<" "<<States[Dimx-1].size()<<" "<<States[Dimx-1][Dimy-1].size();
}

void CVoxel_Tab::Init_Voxels(CVoxel_8 B_Box)
{
	if ((Dimx!=0)&&(Dimy!=0)&&(Dimz!=0))
	{
		int i,j,k;
		QVector3D Vx(1,0,0),Vy(0,1,0),Vz(0,0,1);
		double xlength,ylength,zlength;
		xlength=(B_Box.Get_Vertex(1).x()-B_Box.Get_Vertex(0).x())/Dimx;
		ylength=(B_Box.Get_Vertex(3).y()-B_Box.Get_Vertex(0).y())/Dimy;
		zlength=(B_Box.Get_Vertex(4).y()-B_Box.Get_Vertex(0).y())/Dimz;
		for (i=0;i<Dimx;i++)
			for (j=0;j<Dimy;j++)
				for (k=0;k<Dimx;k++)
				{
					Voxels[i][j][k].Put_Vertex(0,Vx*i*xlength+Vy*j*ylength+Vz*k*zlength);
					Voxels[i][j][k].Put_Vertex(1,Voxels[i][j][k].Get_Vertex(0)+Vx*xlength);
					Voxels[i][j][k].Put_Vertex(2,Voxels[i][j][k].Get_Vertex(1)+Vz*zlength);
					Voxels[i][j][k].Put_Vertex(3,Voxels[i][j][k].Get_Vertex(0)+Vz*zlength);
					Voxels[i][j][k].Put_Vertex(4,Voxels[i][j][k].Get_Vertex(0)+Vy*ylength);
					Voxels[i][j][k].Put_Vertex(5,Voxels[i][j][k].Get_Vertex(4)+Vx*xlength);
					Voxels[i][j][k].Put_Vertex(6,Voxels[i][j][k].Get_Vertex(5)+Vz*zlength);
					Voxels[i][j][k].Put_Vertex(7,Voxels[i][j][k].Get_Vertex(4)+Vz*zlength);
				}
		for (i=0;i<Dimx;i++)
			for (j=0;j<Dimy;j++)
				for (k=0;k<Dimx;k++)
					States[i][j][k]=4;
	}
}

int CVoxel_Tab::Get_Dimx(void)
{
	return Dimx;
}

int CVoxel_Tab::Get_Dimy(void)
{
	return Dimy;
}

int CVoxel_Tab::Get_Dimz(void)
{
	return Dimz;
}

double CVoxel_Tab::Get_Vlength(void)
{
	return Vlength;
}

CVoxel_8 CVoxel_Tab::Get_BBox(void)
{
	return BBox;
}

CVoxel_8 CVoxel_Tab::Get_Voxel(int i,int j,int k)
{
	return Voxels[i][j][k];
}

unsigned char CVoxel_Tab::Get_State(int i,int j,int k)
{
	return States[i][j][k];
}

unsigned char*** CVoxel_Tab::Get_States() {
	return States;
}

void CVoxel_Tab::Draw_Bounding_Box(void)
{
	BBox.Draw_Lines();
}

void CVoxel_Tab::Draw_All(void)
{
	int i,j,k;

	for (i=0;i<Dimx;i++)
		for (j=0;j<Dimy;j++)
			for (k=0;k<Dimz;k++)
				Voxels[i][j][k].Draw();
}

void CVoxel_Tab::Draw_All_Lines(void)
{
	int i,j,k;

	for (i=0;i<Dimx;i++)
		for (j=0;j<Dimy;j++)
			for (k=0;k<Dimz;k++)
				Voxels[i][j][k].Draw_Lines();
}

void CVoxel_Tab::Draw_State(unsigned char s)
{
	int i,j,k;
        //TODO : optimiser en parcourant uniquement la list voulue.
	for (i=0;i<Dimx;i++)
		for (j=0;j<Dimy;j++)
			for (k=0;k<Dimz;k++)
				if (States[i][j][k]==s)
					Voxels[i][j][k].Draw_Lines();
}

void CVoxel_Tab::Create_Square_Enum(Cloud* pCloud) {
	if(pCloud == NULL)	return;

	QVector<QVector3D> pPoints = pCloud->getPoints();
	int i,j,k;	
	float ** Distances_Tab;
	float Distance_min=100000 , Distance_max=-100000;
	QVector3D a,b;
	int Pow2 [13]={0,2,4,8,16,32,64,128,256,512,1024,2048,4096};
	int NBPTS = pPoints.size();
        int im=0,jm=0,jmin=0;

	float * Distances_min;
	float Distemp;
	int * Distances_min_i;

	if (FastVoxelization==1)
	{
		qWarning()<<"mode fast voxelisation";
		Distances_min = new float [NBPTS];
		Distances_min_i = new int [NBPTS];
		for(i=0;i<NBPTS;i++) // A optimiser
		{	
			Distances_min[i]=100000;
			a=pPoints[i];
			for(j=0;j<NBPTS;j++) 
			{
				if (j!=i)
				{
					b=pPoints[j];
					Distemp=Manhattan_Distance3D(a,b);
					if (Distemp<Distances_min[i])
					{
						Distances_min[i]=Distemp;
						Distances_min_i[i]=j;
					}
				}
			}
		}
		for (i=0;i<NBPTS;i++)
			if (Distances_min[i]>Distance_max)
			{
				Distance_max=Distances_min[i];
				im=i;
			}
		Distance_max=Distance3D( pPoints[im], pPoints[Distances_min_i[im]] );
		delete [] Distances_min;
		delete [] Distances_min_i;
	}
	else
	{
		printf("mode slow voxelisation\n");
		Distances_Tab = new float * [NBPTS-1];
		for(i=0;i<NBPTS-1;i++) 
		{	
			Distances_Tab [i] = new float [NBPTS-(i+1)];
			a=pPoints[i];
			for(j=i+1;j<NBPTS;j++) 
			{				
					b=pPoints[j];
					Distances_Tab [i][j-(i+1)]=Distance3D(a,b);
			}
		}
	
		for (k=0;k<NBPTS;k++)
		{
			Distance_min=100000;
			for (j=0;j<NBPTS-(k+1);j++){
				if (Distances_Tab [k][j]<Distance_min)
				{
					Distance_min=Distances_Tab [k][j];
					jmin=j+k+1;
				}
			}
			for (i=0;i<k;i++){
				if (Distances_Tab [i][k-1-i]<Distance_min)
				{
					Distance_min=Distances_Tab [i][k-1-i];
					jmin=i;
				}
			}
			if (Distance_min>Distance_max)
			{
				Distance_max=Distance_min;
				im=k,jm=jmin;
			}		
		}
		Distance_max=Distance3D(pPoints[im],pPoints[jm]);
		for(i=0;i<NBPTS-1;i++)
			delete [] Distances_Tab [i];
		delete [] Distances_Tab;		
	}

	Vlength=2.0*(Distance_max);
	qWarning()<<"Taille des voxels ideale : %.5f\n"<<Vlength;

	int Dim=Dimx;

	if (Dim==0) // Dimx=Dimy=Dimz == Dimx
	{
		double tx,ty,tz,tmax;		
		
		BBox=pCloud->boundingBox();
		tx=BBox.Get_Vertex(1).x()-BBox.Get_Vertex(0).x();
		ty=BBox.Get_Vertex(4).y()-BBox.Get_Vertex(0).y();
		tz=BBox.Get_Vertex(3).z()-BBox.Get_Vertex(0).z();
		tmax=qMax(tx,qMax(ty,tz));
		printf("Longueur maximale de la boite engloibante = %.5f\n",tmax);

		Dim=(int)(tmax/Vlength);
		qWarning()<<"Dimension de la voxellisation determinee par la taille des voxels : %d\n"<<Dim;

		for (i=0;i<13;i++)
			if (Dim<Pow2[i])
			{
				Dim=Pow2[i];	// on prend la puisance de 2 superieure
				break;
			}
		qWarning()<<"Dimension de la voxellisation ajustee en puissance de 2 : %d\n"<<Dim;

		Dimx=Dimy=Dimz=Dim;

		Voxels=new CVoxel_8** [Dimx];
		for (i=0;i<Dimx;i++)
		{
			Voxels[i]=new CVoxel_8* [Dimy];
			for (j=0;j<Dimy;j++)
				Voxels[i][j]=new CVoxel_8 [Dimz];
		}

		States=new unsigned char**[Dimx];
		for (i=0;i<Dimx;i++)
		{
			States[i]=new unsigned char* [Dimy];
			for (j=0;j<Dimy;j++)
				States[i][j]=new unsigned char [Dimz];
		}

		QVector3D Gc;
		Gc.setX((BBox.Get_Vertex(1).x()+BBox.Get_Vertex(0).x())/2);
		Gc.setY((BBox.Get_Vertex(4).y()+BBox.Get_Vertex(0).y())/2);
		Gc.setZ((BBox.Get_Vertex(3).z()+BBox.Get_Vertex(0).z())/2);

		QVector3D Vx(Dim*Vlength/2,0,0),Vy(0,Dim*Vlength/2,0),Vz(0,0,Dim*Vlength/2);
		
		BBox.Put_Vertex(0,Gc-Vx-Vy-Vz);
		BBox.Put_Vertex(1,Gc+Vx-Vy-Vz);
		BBox.Put_Vertex(2,Gc+Vx-Vy+Vz);
		BBox.Put_Vertex(3,Gc-Vx-Vy+Vz);
		BBox.Put_Vertex(4,Gc-Vx+Vy-Vz);
		BBox.Put_Vertex(5,Gc+Vx+Vy-Vz);
		BBox.Put_Vertex(6,Gc+Vx+Vy+Vz);
		BBox.Put_Vertex(7,Gc-Vx+Vy+Vz);

		QVector3D VX(Vlength,0,0),VY(0,Vlength,0),VZ(0,0,Vlength),PO;
		int k;

		PO=BBox.Get_Vertex(0);
		for (i=0;i<Dimx;i++)
			for (j=0;j<Dimy;j++)
				for (k=0;k<Dimx;k++)
				{
					Voxels[i][j][k].Put_Vertex(0,PO+VX*i+VY*j+VZ*k);
					Voxels[i][j][k].Put_Vertex(1,PO+VX*(i+1)+VY*j+VZ*k);
					Voxels[i][j][k].Put_Vertex(2,PO+VX*(i+1)+VY*j+VZ*(k+1));
					Voxels[i][j][k].Put_Vertex(3,PO+VX*i+VY*j+VZ*(k+1));
					Voxels[i][j][k].Put_Vertex(4,PO+VX*i+VY*(j+1)+VZ*k);
					Voxels[i][j][k].Put_Vertex(5,PO+VX*(i+1)+VY*(j+1)+VZ*k);
					Voxels[i][j][k].Put_Vertex(6,PO+VX*(i+1)+VY*(j+1)+VZ*(k+1));
					Voxels[i][j][k].Put_Vertex(7,PO+VX*i+VY*(j+1)+VZ*(k+1));
				}
		for (i=0;i<Dimx;i++)
			for (j=0;j<Dimy;j++)
				for (k=0;k<Dimx;k++)
					States[i][j][k]=4;

	}
}

void CVoxel_Tab::Find_Boundary_Voxels(Cloud* pCloud)
{
	QVector<QVector3D> pPoints(pCloud->getPoints());
	int i,j,k,l;
	int i1,i2,j1,j2,k1,k2;
	QVector3D point;
	double px,py,pz;
	for (l=0;l<pPoints.size();l++)
	{
		i1=i2=j1=j2=k1=k2=-1;
		point=pPoints[l];
		px=point.x();py=point.y();pz=point.z();

		for (i=1;i<Dimx;i++) {
			if (px<=Voxels[i][0][0].Get_Vertex(0).x())
			{
				i1=i-1;
				if (px==Voxels[i][0][0].Get_Vertex(0).x())
					i2=i;
				break;
			}
		}

		if (i1==-1)
			if (px>Voxels[Dimx-1][0][0].Get_Vertex(0).x()&&px<=Voxels[Dimx-1][0][0].Get_Vertex(6).x())
				i1=Dimx-1;
		
		for (j=1;j<Dimy;j++) {
			if (py<=Voxels[0][j][0].Get_Vertex(0).y())
			{
				j1=j-1;
				if (py==Voxels[0][j][0].Get_Vertex(0).y())
					j2=j;
				break;
			}
		}

		if (j1==-1)
			if (py>Voxels[0][Dimy-1][0].Get_Vertex(0).y()&&py<=Voxels[0][Dimy-1][0].Get_Vertex(6).y())
				j1=Dimy-1;

		for (k=1;k<Dimz;k++) {
			if (pz<=Voxels[0][0][k].Get_Vertex(0).z())
			{
				k1=k-1;
				if (pz==Voxels[0][0][k].Get_Vertex(0).z())
					k2=k;
				break;
			}
		}

		if (k1==-1)
			if (pz>Voxels[0][0][Dimz-1].Get_Vertex(0).z()&&pz<=Voxels[0][0][Dimz-1].Get_Vertex(6).z())
				k1=Dimz-1;

		if ((i1!=-1)&&(j1!=-1)&&(k1!=-1))
		{

			States[i1][j1][k1]=1;

			// INSCRIPTION DU VOXEL DANS LA LISTE DES VOXELS SURFACE
			if (FSV==NULL)
			{
				FSV=new Vox_List;
				FSV->Vox_Coord[0]=i1;FSV->Vox_Coord[1]=j1;FSV->Vox_Coord[2]=k1;
				LSV=FSV;LSV->Next=NULL;
			}
			else
			{
				LSV->Next=new Vox_List;
				LSV=LSV->Next;
				LSV->Vox_Coord[0]=i1;LSV->Vox_Coord[1]=j1;LSV->Vox_Coord[2]=k1;LSV->Next=NULL;
			}
			if (Voxels[i1][j1][k1].First==NULL)
			{
				Voxels[i1][j1][k1].First=new Dot_List;
				Voxels[i1][j1][k1].First->Dot_Num=l;
				Voxels[i1][j1][k1].First->Next=NULL;
				Voxels[i1][j1][k1].Last=Voxels[i1][j1][k1].First;
			}
			else
			{
				Voxels[i1][j1][k1].Last->Next=new Dot_List;
				Voxels[i1][j1][k1].Last=Voxels[i1][j1][k1].Last->Next;
				Voxels[i1][j1][k1].Last->Dot_Num=l;
				Voxels[i1][j1][k1].Last->Next=NULL;
			}
			if (i2!=-1)
			{
				States[i2][j1][k1]=1;

				LSV->Next=new Vox_List;
				LSV=LSV->Next;
				LSV->Vox_Coord[0]=i2;LSV->Vox_Coord[1]=j1;LSV->Vox_Coord[2]=k1;LSV->Next=NULL;

				if (Voxels[i2][j1][k1].First==NULL)
				{
					Voxels[i2][j1][k1].First=new Dot_List;
					Voxels[i2][j1][k1].First->Dot_Num=l;
					Voxels[i2][j1][k1].First->Next=NULL;
					Voxels[i2][j1][k1].Last=Voxels[i2][j1][k1].First;
				}
				else
				{
					Voxels[i2][j1][k1].Last->Next=new Dot_List;
					Voxels[i2][j1][k1].Last=Voxels[i2][j1][k1].Last->Next;
					Voxels[i2][j1][k1].Last->Dot_Num=l;
					Voxels[i2][j1][k1].Last->Next=NULL;
				}
				if (j2!=-1)
				{
					States[i1][j2][k1]=1;

					LSV->Next=new Vox_List;
					LSV=LSV->Next;
					LSV->Vox_Coord[0]=i1;LSV->Vox_Coord[1]=j2;LSV->Vox_Coord[2]=k1;LSV->Next=NULL;

					if (Voxels[i1][j2][k1].First==NULL)
					{
						Voxels[i1][j2][k1].First=new Dot_List;
						Voxels[i1][j2][k1].First->Dot_Num=l;
						Voxels[i1][j2][k1].First->Next=NULL;
						Voxels[i1][j2][k1].Last=Voxels[i1][j2][k1].First;
					}
					else
					{
						Voxels[i1][j2][k1].Last->Next=new Dot_List;
						Voxels[i1][j2][k1].Last=Voxels[i1][j2][k1].Last->Next;
						Voxels[i1][j2][k1].Last->Dot_Num=l;
						Voxels[i1][j2][k1].Last->Next=NULL;
					}
					
					States[i2][j2][k1]=1;

					LSV->Next=new Vox_List;
					LSV=LSV->Next;
					LSV->Vox_Coord[0]=i2;LSV->Vox_Coord[1]=j2;LSV->Vox_Coord[2]=k1;LSV->Next=NULL;

					if (Voxels[i2][j2][k1].First==NULL)
					{
						Voxels[i2][j2][k1].First=new Dot_List;
						Voxels[i2][j2][k1].First->Dot_Num=l;
						Voxels[i2][j2][k1].First->Next=NULL;
						Voxels[i2][j2][k1].Last=Voxels[i2][j2][k1].First;
					}
					else
					{
						Voxels[i2][j2][k1].Last->Next=new Dot_List;
						Voxels[i2][j2][k1].Last=Voxels[i2][j2][k1].Last->Next;
						Voxels[i2][j2][k1].Last->Dot_Num=l;
						Voxels[i2][j2][k1].Last->Next=NULL;
					}
					if (k2!=-1)
					{
						States[i1][j1][k2]=1;

						LSV->Next=new Vox_List;
						LSV=LSV->Next;
						LSV->Vox_Coord[0]=i1;LSV->Vox_Coord[1]=j1;LSV->Vox_Coord[2]=k2;LSV->Next=NULL;

						if (Voxels[i1][j1][k2].First==NULL)
						{
							Voxels[i1][j1][k2].First=new Dot_List;
							Voxels[i1][j1][k2].First->Dot_Num=l;
							Voxels[i1][j1][k2].First->Next=NULL;
							Voxels[i1][j1][k2].Last=Voxels[i1][j1][k2].First;
						}
						else
						{
							Voxels[i1][j1][k2].Last->Next=new Dot_List;
							Voxels[i1][j1][k2].Last=Voxels[i1][j1][k2].Last->Next;
							Voxels[i1][j1][k2].Last->Dot_Num=l;
							Voxels[i1][j1][k2].Last->Next=NULL;
						}
						States[i2][j1][k2]=1;

						LSV->Next=new Vox_List;
						LSV=LSV->Next;
						LSV->Vox_Coord[0]=i2;LSV->Vox_Coord[1]=j1;LSV->Vox_Coord[2]=k2;LSV->Next=NULL;

						if (Voxels[i2][j1][k2].First==NULL)
						{
							Voxels[i2][j1][k2].First=new Dot_List;
							Voxels[i2][j1][k2].First->Dot_Num=l;
							Voxels[i2][j1][k2].First->Next=NULL;
							Voxels[i2][j1][k2].Last=Voxels[i2][j1][k2].First;
						}
						else
						{
							Voxels[i2][j1][k2].Last->Next=new Dot_List;
							Voxels[i2][j1][k2].Last=Voxels[i2][j1][k2].Last->Next;
							Voxels[i2][j1][k2].Last->Dot_Num=l;
							Voxels[i2][j1][k2].Last->Next=NULL;
						}
						States[i1][j2][k2]=1;

						LSV->Next=new Vox_List;
						LSV=LSV->Next;
						LSV->Vox_Coord[0]=i1;LSV->Vox_Coord[1]=j2;LSV->Vox_Coord[2]=k2;LSV->Next=NULL;

						if (Voxels[i1][j2][k2].First==NULL)
						{
							Voxels[i1][j2][k2].First=new Dot_List;
							Voxels[i1][j2][k2].First->Dot_Num=l;
							Voxels[i1][j2][k2].First->Next=NULL;
							Voxels[i1][j2][k2].Last=Voxels[i1][j2][k2].First;
						}
						else
						{
							Voxels[i1][j2][k2].Last->Next=new Dot_List;
							Voxels[i1][j2][k2].Last=Voxels[i1][j2][k2].Last->Next;
							Voxels[i1][j2][k2].Last->Dot_Num=l;
							Voxels[i1][j2][k2].Last->Next=NULL;
						}
						States[i2][j2][k2]=1;

						LSV->Next=new Vox_List;
						LSV=LSV->Next;
						LSV->Vox_Coord[0]=i2;LSV->Vox_Coord[1]=j2;LSV->Vox_Coord[2]=k2;LSV->Next=NULL;

						if (Voxels[i2][j2][k2].First==NULL)
						{
							Voxels[i2][j2][k2].First=new Dot_List;
							Voxels[i2][j2][k2].First->Dot_Num=l;
							Voxels[i2][j2][k2].First->Next=NULL;
							Voxels[i2][j2][k2].Last=Voxels[i2][j2][k2].First;
						}
						else
						{
							Voxels[i2][j2][k2].Last->Next=new Dot_List;
							Voxels[i2][j2][k2].Last=Voxels[i2][j2][k2].Last->Next;
							Voxels[i2][j2][k2].Last->Dot_Num=l;
							Voxels[i2][j2][k2].Last->Next=NULL;
						}
					}
				}

			}
		}
		else {
			qWarning()<<"Point x="<<px<<" y="<<py<<"z="<<pz<<\
					"hors de la voxellisation ! i1="<<i1<<"j1="<<j1<<"k1="<<k1;
		}
	}
}

void CVoxel_Tab::Find_InOut_Voxels(void)
{
	int i,j,k;

	// Marquage des voxels aux bords de la boite englobante
	for (i=0;i<Dimx;i++)
		for (j=0;j<Dimy;j++)
		{
			if (States[i][j][0]==4)
				States[i][j][0]=0;
			if (States[i][j][Dimz-1]==4)
				States[i][j][Dimz-1]=0;
		}
	for (i=0;i<Dimx;i++)
		for (k=0;k<Dimz;k++)
		{
			if (States[i][0][k]==4)
				States[i][0][k]=0;
			if (States[i][Dimy-1][k]==4)
				States[i][Dimy-1][k]=0;
		}
	for (j=0;j<Dimy;j++)
		for (k=0;k<Dimz;k++)
		{
			if (States[0][j][k]==4)
				States[0][j][k]=0;
			if (States[Dimx-1][j][k]==4)
				States[Dimx-1][j][k]=0;
		}

	// Propagation des voxels exterieurs
	for (i=1;i<Dimx;i++)
		for (j=1;j<Dimy;j++)
			for (k=1;k<Dimz;k++)
				if ((States[i][j][k]==4)
					&&((States[i-1][j][k]==0)||(States[i][j-1][k]==0)||(States[i][j][k-1]==0)))
					States[i][j][k]=0;
	for (i=Dimx-2;i>=1;i--)
		for (j=1;j<Dimy;j++)
			for (k=1;k<Dimz;k++)
				if ((States[i][j][k]==4)
					&&((States[i+1][j][k]==0)||(States[i][j-1][k]==0)||(States[i][j][k-1]==0)))
					States[i][j][k]=0;
	for (i=Dimx-2;i>=1;i--)
		for (j=1;j<Dimy;j++)
			for (k=Dimz-2;k>=1;k--)
				if ((States[i][j][k]==4)
					&&((States[i+1][j][k]==0)||(States[i][j-1][k]==0)||(States[i][j][k+1]==0)))
					States[i][j][k]=0;
	for (i=0;i<Dimx;i++)
		for (j=0;j<Dimy;j++)
			for (k=Dimz-2;k>=1;k--)
				if ((States[i][j][k]==4)
					&&((States[i-1][j][k]==0)||(States[i][j-1][k]==0)||(States[i][j][k+1]==0)))
					States[i][j][k]=0;
	for (i=1;i<Dimx;i++)
		for (j=Dimy-2;j>=1;j--)
			for (k=1;k<Dimz;k++)
				if ((States[i][j][k]==4)
					&&((States[i-1][j][k]==0)||(States[i][j+1][k]==0)||(States[i][j][k-1]==0)))
					States[i][j][k]=0;
	for (i=Dimx-2;i>=1;i--)
		for (j=Dimy-2;j>=1;j--)
			for (k=1;k<Dimz;k++)
				if ((States[i][j][k]==4)
					&&((States[i+1][j][k]==0)||(States[i][j+1][k]==0)||(States[i][j][k-1]==0)))
					States[i][j][k]=0;
	for (i=Dimx-2;i>=1;i--)
		for (j=Dimy-2;j>=1;j--)
			for (k=Dimz-2;k>=1;k--)
				if ((States[i][j][k]==4)
					&&((States[i+1][j][k]==0)||(States[i][j+1][k]==0)||(States[i][j][k+1]==0)))
					States[i][j][k]=0;
	for (i=0;i<Dimx;i++)
		for (j=Dimy-2;j>=1;j--)
			for (k=Dimz-2;k>=1;k--)
				if ((States[i][j][k]==4)
					&&((States[i-1][j][k]==0)||(States[i][j+1][k]==0)||(States[i][j][k+1]==0)))
					States[i][j][k]=0;

	// Obtention des voxels interieurs par complement
	for (i=1;i<Dimx;i++)
		for (j=1;j<Dimy;j++)
			for (k=1;k<Dimz;k++)
				if (States[i][j][k]==4)
					States[i][j][k]=3;
}

void CVoxel_Tab::Find_Deep_Voxels(void)
{

	int i,j,k,l,m,n;

	bool vnear=false;

	for (i=1;i<Dimx;i++)
		for (j=1;j<Dimy;j++)
			for (k=1;k<Dimz;k++)
				if (States[i][j][k]==3)
				{
					for (l=-1;l<=1;l++)
						for (m=-1;m<=1;m++)
							for (n=-1;n<=1;n++)
								if (States[i+l][j+m][k+n]==1)
								{
									vnear=true;
									break;
								}
					if (vnear==true)
					{
						States[i][j][k]=2;
						if (FNV==NULL)
							{
								FNV=new Vox_List;
								FNV->Vox_Coord[0]=i;FNV->Vox_Coord[1]=j;FNV->Vox_Coord[2]=k;
								LNV=FNV;LNV->Next=NULL;
							}
							else
							{
								LNV->Next=new Vox_List;
								LNV=LNV->Next;
								LNV->Vox_Coord[0]=i;LNV->Vox_Coord[1]=j;LNV->Vox_Coord[2]=k;
								LNV->Next=NULL;
							}
						vnear=false;
					}
					else
					{
						if (FDV==NULL)
							{
								FDV=new Vox_List;
								FDV->Vox_Coord[0]=i;FDV->Vox_Coord[1]=j;FDV->Vox_Coord[2]=k;
								LDV=FDV;
								LDV->Next=NULL;
							}
							else
							{
								LDV->Next=new Vox_List;
								LDV=LDV->Next;
								LDV->Vox_Coord[0]=i;LDV->Vox_Coord[1]=j;LDV->Vox_Coord[2]=k;
								LDV->Next=NULL;
							}
					}
				}
}

void CVoxel_Tab::Find_Nearest_State_Voxel(int &ip,int &jp,int &kp,QVector3D p,unsigned char s)
{
	int i,j,k;
	double dist=100000,distemp;
        Vox_List *Current = NULL;


	ip=-1;jp=-1;kp=-1;
	
	switch (s)
	{
	case 1:
		Current=FSV;
		break;
	case 2:
		Current=FNV;
		break;
	case 3:
		Current=FDV;
		break;
	}

	if (Current!=NULL)
	{
		do
		{
			i=Current->Vox_Coord[0];j=Current->Vox_Coord[1];k=Current->Vox_Coord[2];
			distemp=Distance3D_Square(p,(Get_Voxel(i,j,k).Get_Vertex(0)+Get_Voxel(i,j,k).Get_Vertex(6))*0.5);
			if (distemp<dist)
			{
				dist=distemp;
				ip=i,jp=j,kp=k;
			}
			Current=Current->Next;
		}
		while (Current!=NULL);
	}

}

bool CVoxel_Tab::Is_In_Neighbourhood_State_Voxel(int iv,int jv,int kv,unsigned char s)
{
	bool voxel_found=false;
	int i,j,k,imin,jmin,kmin,imax,jmax,kmax;

	if (iv==0) imin=0; else imin=iv-1;
	if (jv==0) jmin=0; else jmin=jv-1;
	if (kv==0) kmin=0; else kmin=kv-1;
	if (iv==Dimx-1) imax=Dimx-1; else imax=iv+1;
	if (jv==Dimy-1) jmax=Dimy-1; else jmax=jv+1;
	if (kv==Dimz-1) kmax=Dimz-1; else kmax=kv+1;

	for (i=imin;i<=imax;i++)
		for (j=jmin;j<=jmax;j++)
			for (k=kmin;k<=kmax;k++)
				if ((i!=iv)&&(j!=jv)&&(k!=kv))
					if (States[i][j][k]==s)
					{
						voxel_found=true;
						break;
					}
	return voxel_found;
}

void CVoxel_Tab::Clear_Voxel_Tab(void)
{

	int i,j;

	for (i=0;i<Dimx;i++)
		for (j=0;j<Dimy;j++)
			delete [] Voxels[i][j];
	
	for (i=0;i<Dimx;i++)
		delete [] Voxels[i];
	


	for (i=0;i<Dimx;i++)
		for (j=0;j<Dimy;j++)
			delete [] States[i][j];
	
	for (i=0;i<Dimx;i++)
		delete [] States[i];

	Vlength=0;Dimx=Dimy=Dimz=0;
	FDV=FNV=FSV=LDV=LNV=LSV=NULL;
	QVector3D O(0.0,0.0,0.0);
	BBox.Set_Voxel(O,O,O,O,O,O,O,O);

}

bool CVoxel_Tab::Is_In_26_Neighbourhood(int i_vox1,int j_vox1,int k_vox1,int i_vox2,int j_vox2,int k_vox2)
{

	if ((i_vox2>=i_vox1-1)&&(i_vox2<=i_vox1+1)&&(j_vox2<=j_vox1+1)&&(j_vox2>=j_vox1-1)&&(k_vox2<=k_vox1+1)&&(k_vox2>=k_vox1-1))
		return true;
	return false;
}
