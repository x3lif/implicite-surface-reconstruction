/* note de Guillaume PERADON à l'éventuel courageux qui voudrait reprendre le code source
 * j'ai essayé de reprendre le code du mieux que j'ai pu, mais certaines fonctions ont été crées
 * et jamais appelées comme le calcul du gradient et du hessien, ce travail fonctionne mais ne respecte 
 * pas le travail de la thèse qui est fournie avec le programme,

 * les différents types de blobs sont : 1/ surfacique, 2/ intérieurs, 3/ profonds, pour les parties de code que j'ai rajouté j'ai utilisé le type énuméré afin de faciliter la lecture du code
 * j'ai rajouté les fonctionnalités pour les blobs cylindriques, voir mon rapport de projet.
 */

//#include <iostream>
//#include <fstream>
//using namespace std;
#ifndef __BLOB_H__
#define __BLOB_H__

#define MAX_POINT 20000
#include "voxel.h"
#include "octree.h"
#include <QVector3D>
#include <QColor>
#include <QDebug>
#include "utils.h"
#include <GLBatch.h>
#include <GLTriangleBatch.h>
#include <GLFrame.h>

/*typedef struct Tree
{
	CInterval node[3];
	Tree *left;
	Tree *right;
} Tree;*/

enum {
    Generique = 0,
	Spherique,
	Cylindrique
};

enum {
	Surface=1,
	Interieur=2,
	Profond=3
};

class CBlob
{
public:
	CBlob(void);
	virtual ~CBlob(void);

        // méthodes virtuelles pures
        virtual void        Blob_Info(void) const =0;
        virtual const QVector3D&   getCenter(void) const =0;
        virtual double      getRadius(void) const =0;
        virtual double      getInfParam(void) const =0;
        virtual int         getTypeReconstruction(void) const =0;
        virtual const QColor&     getColor(void) const =0;
        virtual double      computeDistance(const QVector3D&) const =0;
        virtual void        computeBounds(double&, double&, double&, double&, double&, double &) const =0;
        virtual double      computeVal(const QVector3D& pPoint) const =0;
        virtual double      computeVal(double) const =0;
        virtual void        drawInfluence() const = 0;
        virtual void        drawThreshold() const = 0;
        //virtual QVector3D   computeGradient(QVector3D) const =0;
//	virtual CBlob & operator = (const CBlob & b);

//	virtual	char Relative_Position(CInterval_3D)=0;
//	virtual bool IsEmpty(CInterval_3D inter)=0;
//       virtual	bool IsInside(QVector3D)=0;
//	virtual CInterval Compute_Val(CInterval [3])=0;//fonction jamais appelée
//	virtual CInterval_3D Compute_Gradient(CInterval_3D)=0; // fonction jamais appelée
//	virtual long double** Compute_Hessien(CPoint_3D)=0; // fonction jamais appelée
	//----------------- Ajoutées par Guillaume PERADON -------------------//
        virtual int type(); //Permet de faire un affichage différent pour les différents type de blobs qui héritent de cette classe
        virtual const QVector3D& getSegmentA() const =0;
        virtual const QVector3D& getSegmentB()const =0;
        virtual CBlob* clone() const =0;
    GLTriangleBatch mInfluenceBatch;
    GLTriangleBatch mThresholdBatch;
    GLFrame         mFrame;
};

class CBlob_Spherical:public CBlob
{
protected:
        QVector3D mCenter;
        double mRadius,mInfParam, mThreshold;
        int mTypeFunction;
        int mTypeReconstruction;	// Pour identifier les blobs de la construction
        //double Color[4];
        QColor mColor;
public:
	CBlob_Spherical(void);
        //CBlob_Spherical(CPoint_3D,double,double,int,double[4]);
        CBlob_Spherical(QVector3D pCenter, double pRadius, double pInfParam, int pTypeFunction, QColor pColor);
	~CBlob_Spherical(void);

        CBlob_Spherical* clone() const;

        const QVector3D& getCenter(void)const;
        double getRadius(void) const;
        double getInfParam(void) const;
        double getThreshold(void) const;
        int getTypeFunction(void) const;
        int getTypeReconstruction(void) const;
        const QColor& getColor(void) const;
        void setCenter(QVector3D);
        void setRadius(double);
        void setInfParam(double);
        void setThreshold(double);
        void setTypeFunction(int);
        void setTypeReconstruction(int);
        void setColor(/*float [4]*/ const QColor& pNewColor);
        CBlob_Spherical& operator = (const CBlob_Spherical & b);
        void Blob_Info(void) const;
        double computeDistance(const QVector3D&) const;
        void computeBounds(double &,double &,double &,double &,double &,double &) const;
        double computeVal( const QVector3D& pPoint) const;
        double computeVal(double) const;
        void drawInfluence() const;
        void drawThreshold() const;
        //CPoint_3D Compute_Gradient(CPoint_3D);
        //CPoint_3D Compute_Gradient_Muraki(CPoint_3D);
        //char relativePosition(CInterval_3D);
        //bool isEmpty(CInterval_3D);
        bool isInside(const QVector3D&) const;
        //CInterval Compute_Val_Muraki(CInterval [3]);
        //CInterval Compute_Val(CInterval [3]);
        //CInterval_3D Compute_Gradient(CInterval_3D);
        //long double** Compute_Hessien(CPoint_3D);
	//--------------------Ajoutées par Guillaume PERADON---------------//
        int type() const;
        const QVector3D& getSegmentA() const;
        const QVector3D& getSegmentB() const;
protected:
        void drawSpherical(int Parallels, int Meridians, float pRadius) const;
};
/*
class CBlob_Cylindric:public CBlob
{
protected:
	CPoint_3D Segment_A,Segment_B;
	double Ray,Inf_Param;
	int Type_Function;
	int Type_Reconstruction;
	double Color[4];
public:
	CBlob_Cylindric(void);
	CBlob_Cylindric(CPoint_3D,CPoint_3D,double,double,int,double[4]);
	~CBlob_Cylindric(void);
	CPoint_3D Get_Segment_A(void);
	CPoint_3D Get_Segment_B(void);
	double Get_Ray(void);
	double Get_Inf_Param(void);
	int Get_Type_Function(void);
	int Get_Type_Reconstruction(void);
	double *Get_Color(void);
	void Put_Segment_A(CPoint_3D);
	void Put_Segment_B(CPoint_3D);
	void Put_Ray(double);
	void Put_Inf_Param(double);
	void Put_Type_Function(int);
	void Put_Type_Reconstruction(int);
	void Put_Color(float [4]);
	CBlob_Cylindric & operator = (const CBlob_Cylindric & b);
	void Blob_Info(void);
	double Compute_Dist(CPoint_3D);
	void Compute_Bounds(double &,double &,double &,double &,double &,double &);
	double Compute_Val(CPoint_3D);
	double Compute_Val(double);
	CPoint_3D Compute_Gradient(CPoint_3D);

	char Relative_Position(CInterval_3D);
	bool IsEmpty(CInterval_3D);
	bool IsInside(CPoint_3D);
	CInterval Compute_Val(CInterval [3]);//A FAire
	CInterval_3D Compute_Gradient(CInterval_3D);// A FAire
	long double** Compute_Hessien(CPoint_3D);// A Faire
	virtual CPoint_3D Get_Center(void);
	//-------------------------------- Ajouté par Guillaume PERADON ---------------//
	int Get_Type_Of_Blob();
	CBlob_Cylindric* CBlob_Cylindric::clone();
	CInterval Compute_Val_Muraki(CInterval [3]);
};

class CBlob_Rectangle:public CBlob
{
protected:
	CPoint_3D Segment_A,Segment_B,Segment_C,Segment_D;
	double Ray,Inf_Param;
	int Type_Function;
	double Color[4];
public:
	CBlob_Rectangle(void);
	CBlob_Rectangle(CPoint_3D,CPoint_3D,CPoint_3D,CPoint_3D,double,double,int,double[4]);
	~CBlob_Rectangle(void);
	double Get_Ray(void);
	double Get_Inf_Param(void);
	int Get_Type_Function(void);
	double *Get_Color(void);
	void Put_Segment_A(CPoint_3D);
	void Put_Segment_B(CPoint_3D);
	void Put_Ray(double);
	void Put_Inf_Param(double);
	void Put_Type_Function(int);
	void Put_Color(float [4]);
	CBlob_Rectangle & operator = (const CBlob_Rectangle & b);
	void Blob_Info(void);
	double Compute_Dist(CPoint_3D);
};

class CBlob_Linked
{
protected:
	CBlob *Blob;
	CBlob_Linked *Prec,*Next;
public:
	CBlob_Linked(void);
	CBlob_Linked(CBlob_Linked *Precedent,CBlob_Linked *Next);
	~CBlob_Linked(void);
	CBlob_Linked * Get_Prec(void);
	CBlob_Linked * Get_Next(void);
	int Get_Type_Of_Blob();
	//Rajout
	void Set_Next(CBlob_Linked*);
	void Set_Prec(CBlob_Linked*);
	CBlob_Linked* clone();
friend class CList_BLob;
}; */

class CList_BLob
{
public:
    /*
	CBlob_Linked *First,*Last;
	int Nb_Blobs;
	double Threshold;
	long double xmin,ymin,zmin,xmax,ymax,zmax;
	CVoxel_8 Bounded_Box;

	CInterval_3D criticalIntervals[MAX_POINT];
	int criticalIntervalIndex;
	CPoint_3D criticalPoints[MAX_POINT];
	int criticalPointIndex;
    */
protected:
        /** Qt Version */
        QVector<CBlob*> mBlobList;
        double mThreshold;
        long double mXMin,mYMin,mZMin,mXMax,mYMax,mZMax;
        CVoxel_8 mBoundedBox;

public:
	CList_BLob(void);
	double Get_Threshold(void);
	CVoxel_8 Get_Bounded_Box(void);
	int Get_Nb_Blobs(void);
	void Set_Threshold(double);
        long double getXMin(void);
        long double getYMin(void);
        long double getZMin(void);
        long double getXMax(void);
        long double getYMax(void);
        long double getZMax(void);
        int size();
        void Add_Blob(CBlob *);
        void List_Info(void);
        CBlob* Nearest_Blob(QVector3D pPoint);
        void drawBlobsThreshold(int) const ;
        void drawBlobsInfluence(int) const ;

        void readVoxellization(QVector<QVector3D> pCloud, CVoxel_Tab* pVT, double pThresold = 0.15);
//	void Read_Octree_Inner_Leaves(CTab_Point_3D,CList_Octree_Node, double);
        void readOctreeInnerLeaves(QVector<QVector3D>&, CList_Octree_Node, double);

        //void Add_Boundary_Blobs(CTab_Point_3D,CVoxel_Tab);
        //void addBoundaryBlobs(QVector<QVector3D>&, CVoxel_Tab);
        //void Add_Boundary_Blobs_From_Voxels(CTab_Point_3D,CVoxel_Tab);
        void addBoundaryBlobsFromVoxels(QVector<QVector3D> pCloudPoint, CVoxel_Tab* pVoxelTab);
        //void Read_File(char *);
        //void Save_To_Povray(char *);
        double Compute_Val(const QVector3D& pPoint) const;
        /*
        CPoint_3D Compute_Gradient(QVector3D);
        void Compute_Color(QVector3D p,float c[4]); // TODO replace c[4] by QColor?

        void Compute_Vertex(CVertex_3D &,double &);
	void Compute_Gradient_and_Color_on_Surface(CVertex_3D &Vertex);
	void Clear_Blobs_List(void);

	int Get_Critical_Interval_Nb(void);
	int Get_Critical_Point_Nb(void);
	void Display_Critical_Intervals(void);
	void Display_Critical_Points(void);
	char Relative_Position(CInterval_3D);
	bool IsEmpty(CInterval_3D inter, long double precision);
	CInterval Compute_Val(CInterval inter[3]);
	CInterval_3D Compute_Gradient(CInterval_3D inter);
	long double** Compute_Hessien(CPoint_3D point);
	void Compute_Critical_Points(CTree_Interval_3D , long double precision);
	void Compute_Critical_Points(CNode_Interval_3D *, long double precision);
	void Interval_To_Point(void);
	void Refine_Critical_Points(double precision);
	void Fill_Gaps(double precision);
	//-------------------- Ajouté par Guillaume PERADON ---------------------//
	void Get_All_Types_Of_Blob();
	CBlob* Nearest_Y_Blob(CPoint_3D* Point,int type);//Permet de trouver le blob le plus proche ( en Y ) d'un point donné; fonction utilisée par pour créer les blobs cylindriques d'intérieur proche
	CPoint_3D* Extremum_Y_Spherical_Blob(CPoint_3D*,int);// retourne les blobs les plus extrêmes en Y d'un point donné en paramètre
	CPoint_3D* Extremum_Y_Spherical_Blob(CPoint_3D*,int,float);//retourne les blobs les plus extremes dans le cas ou il y a des discontinuités
	CPoint_3D* Extremum_X_Spherical_Blob(CPoint_3D*,int);// retourne les blobs les plus extrêmes en Y d'un point donné en paramètre
	CPoint_3D* Extremum_X_Spherical_Blob(CPoint_3D*,int,float);
	CPoint_3D* Extremum_Z_Spherical_Blob(CPoint_3D*,int);// retourne les blobs les plus extrêmes en Y d'un point donné en paramètre
	CPoint_3D* Extremum_Z_Spherical_Blob(CPoint_3D*,int,float);
	void Spherical_To_Cylindric(int);//permet de passer tous les blobs sphériques d'un type donné en blobs cylindrique
	void Dealloc(CBlob_Linked*);
	int Delete_All_BetweenY(CPoint_3D*,int,int);
	int Delete_All_BetweenX(CPoint_3D*,int,int);
	int Delete_All_BetweenZ(CPoint_3D*,int,int);
        CBlob_Linked* Nearest_Dif_LinkedBlob(CPoint_3D);*/
};

#endif /* __BLOB_H__ */

