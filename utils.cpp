#include <math.h>
//#include <GL/freeglut.h>
#include <QVector3D>
#include <QDebug>
#include "blob.h"

double Distance3D (const QVector3D& a, const QVector3D& b)
{
    float ax=a.x(),ay=a.y(),az=a.z(),bx=b.x(),by=b.y(),bz=b.z();
    return sqrt((ax-bx)*(ax-bx) + (ay-by)*(ay-by) + (az-bz)*(az-bz));
    return (a-b).length();
}

double Distance3D_Square (const QVector3D& a, const QVector3D& b)
{
    return (a-b).lengthSquared();
}

double Manhattan_Distance3D (const QVector3D& a, const QVector3D& b)
{
	double x,y,z;
        x=qAbs(a.x()-b.x());
        y=qAbs(a.y()-b.y());
        z=qAbs(a.z()-b.z());
	return (x+y+z);
}

/*QVector3D Middle(QVector3D a, QVector3D b)
{
        QVector3D m;
        m.setX((a.x()+b.x())/2);
        m.setY((a.y()+b.y())/2);
        m.setZ((a.z()+b.z())/2);
	return m;
}

QVector3D Normal3D(QVector3D a, QVector3D b)
{
        QVector3D n;
        n.setX(a.y()*b.z()-b.y()*a.z());
        n.setY(a.z()*b.x()-b.z()*a.x());
        n.setZ(a.x()*b.y()-b.x()*a.y());
	return n;
}

double Dot_Product_3D(QVector3D a, QVector3D b)
{
        return (a.x()*b.x()+a.y()*b.y()+a.z()*b.z());
}*/

int Find_Square_Power (int n)
{
	int p=0;

	do
	{
		if ((n%2)==0)
		{
			n=n/2;
			p++;
		}
		else n=0;
	}
	while (n>1);

	if (n==1)
		return p;
	else return 0;
}

void Find_New_Center(QVector3D &c,QVector3D& M,QVector3D& N)
{
        QVector3D C;
	double t;
	for (t=0;t<=1;t=t+0.001)
	{
		C=c*(1-t)+M*t;
		if (Distance3D(C,N)>=Distance3D(C,M))
			break;
	
	}
	c=C;
}

double Muraki(double r, double R)
{
	double val;

	if (r<=R)
	{
                val=r/R;val=val*val;
		val=1-val;
		val=val*val;
		return(val);
	}
	else
		return(0);
}

double Wywill(double r, double R)
{
	double d2,r2,d4,r4,d6,r6;
	
	if (r<=R)
	{	//ai (-4r6/9Ri6 + 17r4/9Ri4 - 22r2/9Ri2)
		d2=r*r;r2=R*R;d4=d2*d2;r4=r2*r2;d6=d4*d2;r6=r4*r2;
		return(((-4*d6)/(9*r6)+(17*d4)/(9*r4)-(22*d2)/(9*r2)+1));
	}
	else
		return(0);
}

double dMuraki(double r, double R)
{
	double r2,R2,R4;

	r2=r*r;R2=R*R;R4=R2*R2;
	
	return(4*r*(r2/R4-1/R2));
}

double dWywill(double r, double R)
{
	// A FAIRE
        r = 0;
        R = 0;
	return(0);
}

double dEuclidianx(QVector3D p,QVector3D c)
{
        return((c.x()-p.x())/Distance3D(p,c));
}

double dEuclidiany(QVector3D p,QVector3D c)
{
        return((c.y()-p.y())/Distance3D(p,c));
}

double dEuclidianz(QVector3D p,QVector3D c)
{
        return((c.z()-p.z())/Distance3D(p,c));
}

double AngleXY(CBlob* blob){
        QVector3D p1=blob->getSegmentA(),p2=blob->getSegmentB();double angle=0.;
        p1.setZ(0.);p2.setZ(0.);
	double l = Distance3D(p1,p2);
	if(l>0.){
        angle=acos((p1.x()-p2.x())/l);
        if( p2.y()-p1.y() <0 )
		angle=-angle;
	}
	return (angle);
}
double AngleXZ(CBlob* blob){
        QVector3D p1=blob->getSegmentA(),p2=blob->getSegmentB();double angle=0.;
        p1.setY(0.);p2.setY(0.);
	double l = Distance3D(p1,p2);
	if(l>0.){
                angle=acos((p1.x()-p2.x())/l);
                if(p2.z()-p1.z()<0)
			angle=-angle;
	}
	return angle;
}
double AngleYZ(CBlob* blob){
        QVector3D p1=blob->getSegmentA(),p2=blob->getSegmentB();double angle=0.;
        p1.setX(0.);p2.setX(0.);
	double l = Distance3D(p1,p2);
	if(l>0.){
            angle=acos((p1.y()-p2.y())/l);
	}
	return angle;
}
double absolut(double nombre){
	return (nombre>0.)?nombre:-nombre;
}

void Draw_Sphere (float r,int parallele,int meridien)
{
int i,j;
double theta,phi;

        /* Initialisation de l'angle */
        theta=((M_PI/2)-(M_PI/parallele));
        // Dessin des bandes parallèles
        glBegin(GL_QUAD_STRIP);
                for (i=1;i<=parallele-2;i++)
                {
                        phi=0;
                        for (j=0;j<=meridien;j++)
                        {
                                glNormal3f(sin(phi)*cos(theta),sin(theta),cos(phi)*cos(theta));
                                glVertex4f(r*sin(phi)*cos(theta),r*sin(theta),r*cos(phi)*cos(theta),1.0);
                                theta=theta-(M_PI/parallele);
                                glNormal3f(sin(phi)*cos(theta),sin(theta),cos(phi)*cos(theta));
                                glVertex4f(r*sin(phi)*cos(theta),r*sin(theta),r*cos(phi)*cos(theta),1.0);
                                theta=theta+(M_PI/parallele);
                                phi=phi+(2*M_PI/meridien);
                        }
                        theta=theta-(M_PI/parallele);
                };
        glEnd();

        // Dessin de la calotte inférieur
        theta=((-M_PI)/2)-(M_PI/parallele);
        phi=0;
        if ( (meridien % 2) == 1) phi=M_PI/meridien;
                glBegin(GL_TRIANGLE_FAN);
                        glNormal3f(0.0,-1.0,0.0);
                        glVertex3f(0.0,-r,0.0);
                        for (i=0; i<=meridien; i++)
                        {
                                glNormal3f(sin(phi)*cos(theta),sin(theta),cos(phi)*cos(theta));
                                glVertex4f(r*sin(phi)*cos(theta),r*sin(theta),r*cos(phi)*cos(theta),1.0);
                                phi=phi-(2*M_PI/meridien);
                        };
                glEnd();

        // Dessin de la calotte supérieur
        theta=((M_PI)/2)-(M_PI/parallele);
        phi=0;
        glBegin(GL_TRIANGLE_FAN);
                glNormal3f(0.0,1.0,0.0);
                glVertex3f(0.0,r,0.0);
                for (i=0; i<=meridien; i++)
                {
                        glNormal3f(sin(phi)*cos(theta),sin(theta),cos(phi)*cos(theta));
                        glVertex4f(r*sin(phi)*cos(theta),r*sin(theta),r*cos(phi)*cos(theta),1.0);
                        phi=phi+(2*M_PI/meridien);
                }
        glEnd();

}
