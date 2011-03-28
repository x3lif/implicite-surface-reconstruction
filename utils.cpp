#include <math.h>
#include <QVector3D>
#include <QDebug>
double Distance3D (const QVector3D& a, const QVector3D& b)
{
	double x,y,z;
	x=a.x()-b.x();x=x*x;
	y=a.y()-b.y();y=y*y;
	z=a.z()-b.z();z=z*z;

	/*QVector3D lTemp = a - b;
	lTemp = lTemp * lTemp;

	if( lTemp.length() == sqrt(x+y+z) ) {
		qWarning()<<"Distance3D Eureka";
	} else {
		qWarning()<< lTemp.length() << sqrt(x+y+z);
	}*/
	return (sqrt(x+y+z));
}

double Distance3D_Square (const QVector3D& a, const QVector3D& b)
{
	double x,y,z;
	x=a.x()-b.x();x=x*x;
	y=a.y()-b.y();y=y*y;
	z=a.z()-b.z();z=z*z;
	return (x+y+z);
}

double Manhattan_Distance3D (const QVector3D& a, const QVector3D& b)
{
	double x,y,z;
	x=fabs(a.x()-b.x());
	y=fabs(a.y()-b.y());
	z=fabs(a.z()-b.z());
	return (x+y+z);
}
/*
CPoint_3D Middle(CPoint_3D a, CPoint_3D b)
{
	CPoint_3D m;
	m.Put_x((a.Get_x()+b.Get_x())/2);
	m.Put_y((a.Get_y()+b.Get_y())/2);
	m.Put_z((a.Get_z()+b.Get_z())/2);
	return m;
}

CPoint_3D Normal3D(CPoint_3D a, CPoint_3D b)
{
	CPoint_3D n;
	n.Put_x(a.Get_y()*b.Get_z()-b.Get_y()*a.Get_z());
	n.Put_y(a.Get_z()*b.Get_x()-b.Get_z()*a.Get_x());
	n.Put_z(a.Get_x()*b.Get_y()-b.Get_x()*a.Get_y());
	return n;
}

double Dot_Product_3D(CPoint_3D a, CPoint_3D b)
{
	return (a.Get_x()*b.Get_x()+a.Get_y()*b.Get_y()+a.Get_z()*b.Get_z());
}
*/
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
/*
void Find_New_Center(CPoint_3D &c,CPoint_3D M,CPoint_3D N)
{
	CPoint_3D C;
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
	
	return(0);
}

double dEuclidianx(CPoint_3D p,CPoint_3D c)
{
	return((c.Get_x()-p.Get_x())/Distance3D(p,c));
}

double dEuclidiany(CPoint_3D p,CPoint_3D c)
{
	return((c.Get_y()-p.Get_y())/Distance3D(p,c));
}

double dEuclidianz(CPoint_3D p,CPoint_3D c)
{
	return((c.Get_z()-p.Get_z())/Distance3D(p,c));
}
double AngleXY(CBlob* blob){
	CPoint_3D p1=blob->Get_Segment_A(),p2=blob->Get_Segment_B();double angle=0.;
	p1.Put_z(0.);p2.Put_z(0.);
	double l = Distance3D(p1,p2);
	if(l>0.){
	angle=acos((p1.Get_x()-p2.Get_x())/l);
	if( p2.Get_y()-p1.Get_y() <0 )
		angle=-angle;
	}
	return (angle);
}
double AngleXZ(CBlob* blob){
	CPoint_3D p1=blob->Get_Segment_A(),p2=blob->Get_Segment_B();double angle=0.;
	p1.Put_y(0.);p2.Put_y(0.);
	double l = Distance3D(p1,p2);
	if(l>0.){
		angle=acos((p1.Get_x()-p2.Get_x())/l);
		if(p2.Get_z()-p1.Get_z()<0)
			angle=-angle;
	}
	return angle;
}
double AngleYZ(CBlob* blob){
	CPoint_3D p1=blob->Get_Segment_A(),p2=blob->Get_Segment_B();double angle=0.;
	p1.Put_x(0.);p2.Put_x(0.);
	double l = Distance3D(p1,p2);
	if(l>0.){
	angle=acos((p1.Get_y()-p2.Get_y())/l);
	}
	return angle;
}
double absolut(double nombre){
	return (nombre>0.)?nombre:-nombre;
}
*/
