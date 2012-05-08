#ifndef __VOXEL_H__
#define __VOXEL_H__

#include <QVector3D>
#include <QVector>

class Cloud;

struct Dot_List
{	
	int Dot_Num;
	Dot_List *Next;
};

struct Vox_List
{	
	int Vox_Coord [3];
	Vox_List *Next;
};


class CVoxel_8
{
protected:
	QVector3D Vertex[8];

        Dot_List *First,*Last;
public:
	QVector<float> mVertexArrayList;
	CVoxel_8(void);
	QVector3D Get_Vertex(int) const;
	void Put_Vertex(int,QVector3D);
	void Put_Vertex(int,double,double,double);	
	void Set_Voxel(QVector3D,QVector3D,QVector3D,QVector3D,QVector3D,QVector3D,QVector3D,QVector3D);
	void Voxel_Info(void);
	CVoxel_8 &operator = (const CVoxel_8 &V);
	void Draw(void);
	void Draw_Lines(void);
	void arrayList();
friend class CVoxel_Tab;
friend class CList_BLob;
};

class CVoxel_Tab
{
protected:
	CVoxel_8 ***Voxels;
	CVoxel_8 BBox;
	unsigned char ***States;
	int Dimx,Dimy,Dimz;
	double Vlength;
	Vox_List *FDV,*FNV,*FSV;
	Vox_List *LDV,*LNV,*LSV;


public:
	CVoxel_Tab(void);
	CVoxel_Tab(int,int,int);
	void Init_Voxels(CVoxel_8);
	int Get_Dimx(void);
	int Get_Dimy(void);
	int Get_Dimz(void);
	double Get_Vlength(void);
	CVoxel_8 Get_BBox(void);
	CVoxel_8 Get_Voxel(int,int,int);
	unsigned char Get_State(int,int,int);
	unsigned char*** Get_States();
	void Draw_Bounding_Box(void);
	void Draw_All(void);
	void Draw_All_Lines(void);
	void Draw_State(unsigned char);
	//void Create_Square_Enum(QVector<QVector3D>&);
	void Create_Square_Enum(Cloud*);
	void Find_Boundary_Voxels(Cloud*);
	void Find_InOut_Voxels(void);
	void Find_Deep_Voxels(void);
	void Find_Nearest_State_Voxel(int &,int &,int &,QVector3D,unsigned char);
	bool Is_In_Neighbourhood_State_Voxel(int,int,int,unsigned char);
	bool Is_In_26_Neighbourhood(int,int,int,int,int,int);
	void Clear_Voxel_Tab(void);
friend class CList_BLob;
};


#endif /* __VOXEL_H__ */

