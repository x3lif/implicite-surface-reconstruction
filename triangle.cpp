#include "triangle.h"
#include <QDebug>
#include <GL/gl.h>

// ---------------
// class CTriangle
// ---------------

CTriangle::CTriangle(void)
{
    mPointsTab.resize(3);
    mNormalTab.resize(3);
    mColorTab.resize(3);
}

CTriangle::CTriangle(QVector3D V[3], QVector3D N[3], QColor C[3])
{
    for(int i=0; i<3; ++i) {
        mPointsTab << V[i];
        mNormalTab << N[i];
        mColorTab << C[i];
    }
}

CTriangle::CTriangle(QVector3D pTriangle[])
{
    for(int i=0; i<3; ++i) {
        mPointsTab<<pTriangle[i];
    }
}

CTriangle::~CTriangle(void)
{}

void CTriangle::Put_Vertex(const int pIndex, const QVector3D& pVertex)
{
    mPointsTab[pIndex] = pVertex;
}

void CTriangle::Put_Normal(const int pIndex, const QVector3D &pNormal)
{
        mNormalTab[pIndex] = pNormal;
}

void CTriangle::Put_Color(const int pIndex, const QColor &pColor )
{
        mColorTab[pIndex] = pColor;
}

void CTriangle::Put_Triangle(QVector3D pTriangle[3], QVector3D pNormale[3])
{
        for (int i=0;i<3;++i) {
            mPointsTab[i] = pTriangle[i];
            mNormalTab[i] = pNormale[i];
        }
}

void CTriangle::Put_Triangle( QVector3D V[3], QVector3D N[3], QColor C[3] )
{
        for (int i=0;i<3;++i)
	{
                mPointsTab[i] = V[i];
                mNormalTab[i] = N[i];
                mColorTab[i] = C[i];
	}
}

void CTriangle::Put_Triangle(QVector3D &V0, QVector3D &V1, QVector3D &V2, QVector3D &N0, QVector3D &N1, QVector3D &N2)
{
        mPointsTab[0] = V0;
        mPointsTab[1] = V1;
        mPointsTab[2] = V2;

        mNormalTab[0] = N0;
        mNormalTab[1] = N1;
        mNormalTab[2] = N2;
}

void CTriangle::Put_Triangle(QVector3D V[3])
{
    for(int i=0; i<3; ++i) {
        mPointsTab[i] = V[i];
    }
}

QVector3D& CTriangle::vertex(const int pIndex)
{
    return mPointsTab[pIndex];
}

QVector3D& CTriangle::normal(int pIndex)
{
    return mNormalTab[pIndex];
}

void CTriangle::Triangle_Info(void)
{
    for (int i=0;i<=2;i++)
    {
        qWarning()<<"Sommet "<<i;
        qWarning()<<"point :"<<mPointsTab[i]<< "- normale :"<<mNormalTab[i]<<"- Couleur : "<<mColorTab[i];
    }
}

void CTriangle::Draw(void)
{
    float lColor[4];
    glBegin(GL_TRIANGLES);
    glEnable(GL_COLOR_MATERIAL);
    // reseting the color
    glColor3f(1,1,1);
    // resseting tranformation
    glPushMatrix();
    for(int i=0;i<3;++i)
        {
        if(!mColorTab.isEmpty()){
            lColor[0] = mColorTab[i].redF();
            lColor[1]=mColorTab[i].greenF();
            lColor[2] = mColorTab[i].blueF();
        } else {
        lColor[0] = lColor[1] = lColor[2] = 0.5; lColor[3]=1.0;
        }

            //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lColor);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lColor);
            //glNormal3d(mNormalTab[i].x(), mNormalTab[i].y(), mNormalTab[i].z());
            glVertex3d(mPointsTab[i].x(), mPointsTab[i].y(), mPointsTab[i].z());
        }
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glEnd();
}
