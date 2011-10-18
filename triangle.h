#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <QVector3D>
#include <QVector>
#include <QColor>


class CTriangle
{
protected:
        QVector<QVector3D> mPointsTab;
        QVector<QVector3D> mNormalTab;
        QVector<QColor>    mColorTab;
public:
	CTriangle(void);
        CTriangle(QVector3D pTriangle[3], QVector3D pNormale[3], QColor pColor[3] );
        CTriangle(QVector3D pTriangle[3]);
	virtual ~CTriangle(void);
        void Put_Vertex(const int pIndex, const QVector3D& pVertex);
        void Put_Normal(const int pIndex, const QVector3D& pNormal);
        void Put_Color(const int pIndex, const QColor& pColors);
        void Put_Triangle(QVector3D pTriangle[3], QVector3D pNormale[3]);
        void Put_Triangle(QVector3D V[3], QVector3D N[3], QColor C[3]);
        void Put_Triangle(QVector3D& V0, QVector3D& V1, QVector3D& V2, QVector3D& N0, QVector3D& N1, QVector3D& N2);
        void Put_Triangle(QVector3D V[3]);
        QVector3D& vertex(const int pIndex);
        QVector3D& normal(int pIndex);
	void Triangle_Info(void);
	void Draw(void);
};

/*class CTriangle_Linked:public CTriangle
{
protected:
	CTriangle_Linked *Prec,*Next;
public:
	CTriangle_Linked(void);
	~CTriangle_Linked(void);
	CTriangle_Linked * Get_Prec(void);
	CTriangle_Linked * Get_Next(void);
friend class Clist_Triangle;
};

class Clist_Triangle
{
protected:
	CTriangle_Linked *First,*Last;
	int Nb_Triangles;
	CVoxel_8 BB;
public:
	Clist_Triangle(void);
	void Clear_Clist_Triangle(void);
	int Get_Nb_Triangles(void);
	CVoxel_8 Get_BB(void);
	void Add_Triangle(CPoint_3D[3],CPoint_3D[3]);
	void Add_Triangle(CPoint_3D[3],CPoint_3D[3],float [3][4]);
	void Add_Triangle(CVertex_3D[3]);
	void Add_Triangle(CVertex_3D,CVertex_3D,CVertex_3D);
	void List_Info(void);
	void Draw(void);
};
*/

#endif /* __TRIANGLE_H__ */

