#ifndef __MC_H__
#define __MC_H__

#include "voxel.h"
#include "blob.h"
#include "triangle.h"
#include <QList>

QVector3D VertexInterp(double isolevel,QVector3D p1,QVector3D p2,double valp1,double valp2);

//CVertex_3D VertexInterp(double isolevel,CVertex_3D v1,CVertex_3D v2,double valp1,double valp2);

class CIntersections
{
protected:
        QVector3D* x;
        QVector3D* y;
        QVector3D* z;
public:
	CIntersections(void);
        QVector3D* Get_x(void);
        QVector3D* Get_y(void);
        QVector3D* Get_z(void);
        void Set_x(QVector3D pX);
        void Set_y(QVector3D pY);
        void Set_z(QVector3D pZ);
        /*void Set_x_Point(QVector3D);
        void Set_y_Point(QVector3D);
        void Set_z_Point(QVector3D);*/

        //void Set_x(double,double,double);
        //void Set_y(double,double,double);
        //void Set_z(double,double,double);
friend class CMarching_Grid;
};

class CMarching_Grid
{
protected:
        QVector3D *** mVerticesTab;
        CIntersections ***Segment_Intersection;
        CVoxel_8 mGlobalBox, mBoundedBox;
        double *** mValTab;
        int mDimension;
        double mCellLength;
public:
	CMarching_Grid(void);
	CMarching_Grid(int);
	void Allocate(void);
	void DeAllocate(void);
	void Init_Boxes(CVoxel_8);
	void Init_Grid(void);
        int dimension(void);
        void setDimension(int);
        CVoxel_8 boundingBox(void);
        CVoxel_8 globalBox(void);
	void Compute_Vertex(double,double,double,double);
	void Compute_Vertex(double,double,double,double,double,double);
        void Compute_Val(const CList_BLob& );
	void Vertex_Info(void);
	void Val_Info(void);
	void Grid_Info(void);
	void Draw_Vertex_In(CList_BLob);
	void Draw_Vertex(void);
        //int Polygonise(QVector3D s0,QVector3D s1,QVector3D s2,QVector3D s3,QVector3D s4,QVector3D s5,QVector3D s6,QVector3D s7,
        //				CList_BLob,Clist_Triangle &,double v0,double v1,double v2,double v3,double v4,double v5,double v6,double v7);
        void computeTriangles(CList_BLob &,QList<CTriangle>& pList);
	//void Compute_Triangles_Tetrahedrons(implicit,MarchingGrid);
	
};

#endif /* __MC_H__ */

