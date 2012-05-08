#ifndef __UTILS_H__
#define __UTILS_H__

#include <QVector3D>

class CBlob;

double Distance3D (const QVector3D& a, const QVector3D& b);
double Distance3D_Square (const QVector3D& a, const QVector3D& b);
double Manhattan_Distance3D (const QVector3D& a, const QVector3D& b);
int Find_Square_Power (int n);
QVector3D Middle(QVector3D a, QVector3D b);
QVector3D Normal3D(QVector3D a, QVector3D b);
double Dot_Product_3D(QVector3D a, QVector3D b);

void Find_New_Center(QVector3D&,QVector3D&,QVector3D&);
double Muraki(double r, double R);
double Wywill(double r, double R);
double dMuraki(double r, double R);
double dWywill(double r, double R);
double dEuclidianx(QVector3D,QVector3D);
double dEuclidiany(QVector3D,QVector3D);
double dEuclidianz(QVector3D,QVector3D);
double AngleXY(CBlob*);
double AngleXZ(CBlob*);
double AngleYZ(CBlob*);
double absolut(double);

void Draw_Sphere (float r,int parallele,int meridien);

#endif /* __UTILS_H__ */

