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

double dWywill(double /*r*/, double /*R*/)
{
	// A FAIRE
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

/////////////////////////////////////////////////////////////////////////////////////////////////
// Make a sphere
void gltMakeSphere(GLTriangleBatch& sphereBatch, GLfloat fRadius, GLint iSlices, GLint iStacks, float posX, float posY, float posZ)
    {
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
    GLfloat ds = 1.0f / (GLfloat) iSlices;
    GLfloat dt = 1.0f / (GLfloat) iStacks;
    GLfloat t = 1.0f;
    GLfloat s = 0.0f;
    GLint i, j;     // Looping variables

    sphereBatch.BeginMesh(iSlices * iStacks * 6);
    for (i = 0; i < iStacks; i++)
        {
        GLfloat rho = (GLfloat)i * drho;
        GLfloat srho = (GLfloat)(sin(rho));
        GLfloat crho = (GLfloat)(cos(rho));
        GLfloat srhodrho = (GLfloat)(sin(rho + drho));
        GLfloat crhodrho = (GLfloat)(cos(rho + drho));

        // Many sources of OpenGL sphere drawing code uses a triangle fan
        // for the caps of the sphere. This however introduces texturing
        // artifacts at the poles on some OpenGL implementations
        s = 0.0f;
        M3DVector3f vVertex[4];
        M3DVector3f vNormal[4];
        M3DVector2f vTexture[4];

        for ( j = 0; j < iSlices; j++)
            {
            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
            GLfloat stheta = (GLfloat)(-sin(theta));
            GLfloat ctheta = (GLfloat)(cos(theta));

            GLfloat x = stheta * srho;
            GLfloat y = ctheta * srho;
            GLfloat z = crho;

            vTexture[0][0] = s;
            vTexture[0][1] = t;
            vNormal[0][0] = x;
            vNormal[0][1] = y;
            vNormal[0][2] = z;
            vVertex[0][0] = x * fRadius + posX;
            vVertex[0][1] = y * fRadius + posY;
            vVertex[0][2] = z * fRadius + posZ;

            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;

            vTexture[1][0] = s;
            vTexture[1][1] = t - dt;
            vNormal[1][0] = x;
            vNormal[1][1] = y;
            vNormal[1][2] = z;
            vVertex[1][0] = x * fRadius + posX;
            vVertex[1][1] = y * fRadius + posY;
            vVertex[1][2] = z * fRadius + posZ;


            theta = ((j+1) == iSlices) ? 0.0f : (j+1) * dtheta;
            stheta = (GLfloat)(-sin(theta));
            ctheta = (GLfloat)(cos(theta));

            x = stheta * srho;
            y = ctheta * srho;
            z = crho;

            s += ds;
            vTexture[2][0] = s;
            vTexture[2][1] = t;
            vNormal[2][0] = x;
            vNormal[2][1] = y;
            vNormal[2][2] = z;
            vVertex[2][0] = x * fRadius + posX;
            vVertex[2][1] = y * fRadius + posY;
            vVertex[2][2] = z * fRadius + posZ;

            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;

            vTexture[3][0] = s;
            vTexture[3][1] = t - dt;
            vNormal[3][0] = x;
            vNormal[3][1] = y;
            vNormal[3][2] = z;
            vVertex[3][0] = x * fRadius + posX;
            vVertex[3][1] = y * fRadius + posY;
            vVertex[3][2] = z * fRadius + posZ;

            sphereBatch.AddTriangle(vVertex, vNormal, vTexture);

            // Rearrange for next triangle
            memcpy(vVertex[0], vVertex[1], sizeof(M3DVector3f));
            memcpy(vNormal[0], vNormal[1], sizeof(M3DVector3f));
            memcpy(vTexture[0], vTexture[1], sizeof(M3DVector2f));

            memcpy(vVertex[1], vVertex[3], sizeof(M3DVector3f));
            memcpy(vNormal[1], vNormal[3], sizeof(M3DVector3f));
            memcpy(vTexture[1], vTexture[3], sizeof(M3DVector2f));

            sphereBatch.AddTriangle(vVertex, vNormal, vTexture);
            }
        t -= dt;
        }
        sphereBatch.End();
    }
