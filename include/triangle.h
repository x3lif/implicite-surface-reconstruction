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

#endif /* __TRIANGLE_H__ */

