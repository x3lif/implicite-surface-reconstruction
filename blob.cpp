#include "blob.h"
#include <math.h>

extern GLfloat rx, ry, rz;
extern GLfloat tx, ty, tz;

//constructeur
CBlob::CBlob(void)
{}

//Destructeur
CBlob::~CBlob(void)
{}
  
//retourne le type de blob
int CBlob::type(){
	return Generique;
}


// ---------------------
// class CBlob_Spherical
// ---------------------
//constructeur
CBlob_Spherical::CBlob_Spherical(void)
{	
        mCenter.setX(0);mCenter.setY(0);mCenter.setZ(0);
        mRadius=1.0;mInfParam=1.0;mTypeFunction=1;
        mColor.setRedF(0.50);mColor.setGreenF(0.40);mColor.setBlue(0.70);mColor.setAlphaF(1.0);
}

//Constructeur
CBlob_Spherical::CBlob_Spherical(QVector3D pCenter, double pRadius, double pInfParam, int pTypeFunction, QColor pColor)
{
    mCenter = pCenter;
    mRadius = pRadius;
    mInfParam = pInfParam;
    mTypeFunction = pTypeFunction;
    mColor = pColor;
    /*	Center=c;Ray=r;Inf_Param=i;Type_Function=t;
	Color[0]=col[0];Color[1]=col[1];Color[2]=col[2];Color[3]=col[3];
        */
}

//destructeur
CBlob_Spherical::~CBlob_Spherical(void)
{}

//retourne le centre du blob
const QVector3D& CBlob_Spherical::getCenter(void) const
{
        return mCenter;
}

//retourne le rayon
double CBlob_Spherical::getRadius(void) const
{
        return mRadius;
}

//retourne la valeur infParam
double CBlob_Spherical::getInfParam(void) const
{
        return mInfParam;
}

double CBlob_Spherical::getThreshold() const {
    return mThreshold;
}

//retourne le type de fonction utilisé pour la création du blob
int CBlob_Spherical::getTypeFunction() const
{
        return mTypeFunction;
}

// retourne le type de recontruction
int CBlob_Spherical::getTypeReconstruction(void) const
{ 
        return mTypeReconstruction;
}

//retourne la culeur du blob
const QColor& CBlob_Spherical::getColor(void) const
{
        return mColor;
}

//position du centre du blob
void CBlob_Spherical::setCenter(QVector3D c)
{
        mCenter=c;
}

//rayon du bob
void CBlob_Spherical::setRadius(double r)
{
    mRadius=r;
}

void CBlob_Spherical::setInfParam(double i)
{
        mInfParam=i;
}

void CBlob_Spherical::setThreshold(double t) {
    mThreshold = t;
}

//fonction pour creation du blob
void CBlob_Spherical::setTypeFunction(int t)
{
        mTypeFunction=t;
}

// fonction pour la reconstruction
void CBlob_Spherical::setTypeReconstruction(int t)
{
        mTypeReconstruction=t;
}

//fonctio pour regler la couleur
void CBlob_Spherical::setColor(const QColor& pNewColor)
{
    mColor = pNewColor;
}

//opérateur d'égalité
CBlob_Spherical& CBlob_Spherical::operator = (const CBlob_Spherical & b)
{
        mCenter=b.getCenter();
        mRadius=b.getRadius();mInfParam=b.getInfParam();mTypeFunction=b.getTypeFunction();
        //Color[0]=b.Color[0];Color[1]=b.Color[1];Color[2]=b.Color[2];Color[3]=b.Color[3];
        mColor = b.getColor();

        return *this;
}

//affiche les infos du blob
void CBlob_Spherical::Blob_Info(void) const
{
        qWarning()<<"Centre : "<<mCenter;
        qWarning()<<"Rayon : "<<mRadius <<"- Influence : "<<mInfParam;
        /*switch (mTypeFunction)
	{
	case 1:
		printf("Type de fonction : Muraki\n");
	break;
	case 2:
		printf("Type de fonction : Wywill\n");
	break;
        }*/
        //printf("Couleur : %.3f %.3f %.3f %.3f\n",Color[0],Color[1],Color[2],Color[3]);
        qWarning()<<"Couleur :"<<mColor;
}

//calcul de la distance par rapport au 
double CBlob_Spherical::computeDistance(QVector3D pt) const
{
/*	double d,xc,yc,zc;

	xc=pt.Get_x()-Center.Get_x();xc=xc*xc;
	yc=pt.Get_y()-Center.Get_y();yc=yc*yc;
	zc=pt.Get_z()-Center.Get_z();zc=zc*zc;
	d=xc+yc+zc;d=sqrt(d);

	return d;
        */
        return Distance3D(mCenter, pt);
}

//calcul la boite englobante
void CBlob_Spherical::computeBounds(double &xmin,double &ymin,double &zmin,double &xmax,double &ymax,double &zmax) const
{
        xmin=mCenter.x()-mRadius*mInfParam;
        ymin=mCenter.y()-mRadius*mInfParam;
        zmin=mCenter.z()-mRadius*mInfParam;
        xmax=mCenter.x()+mRadius*mInfParam;
        ymax=mCenter.y()+mRadius*mInfParam;
        zmax=mCenter.z()+mRadius*mInfParam;
}

//calcul de la valeur de la fonction au point pt
double CBlob_Spherical::computeVal(QVector3D pt) const
{	
        double d,val;
        d=computeDistance(pt);
        switch (mTypeFunction)
	{
		case 1 :
		{
                        val=Muraki(d,mRadius);
			break;
		}

		case 2 :
		{
                        val=Wywill(d,mRadius);
			break;
		}

		default:
		{
			printf("Mauvais type de fonction pour le calcul !\n");
			val=0.0;
			break;
		}
	}
	return (val);
        // TODO : call camputeVal(d) ????
}

//calcul la valeur au rayon r
double CBlob_Spherical::computeVal(double r) const
{	
	double val;

        switch (mTypeFunction)
	{
		case 1 :
                val=Muraki(r,mRadius);
		break;

		case 2 :
                val=Wywill(r,mRadius);
		break;

		default:
		printf("Mauvais type de fonction pour le calcul !\n");
		val = 0.0;
		break;
	}
	return (val);
}
void CBlob_Spherical::drawInfluence() const {
    drawSpherical( 15, 15, mRadius );
}

void CBlob_Spherical::drawThreshold() const {
    float lRadius = mRadius*(sqrt(1-sqrt(mThreshold)));
    drawSpherical( 15, 15, lRadius );
}

//dessine le blob sphérique
void CBlob_Spherical::drawSpherical(int p, int m, float pRadius) const
{
    float lColor[4];
    float lDiffuse[4] = {0.2f,0.2f,0.2f,1.0f};
    lColor[0] = (float)mColor.redF(); lColor[1] = (float)mColor.greenF(); lColor[2] = (float)mColor.blueF(); lColor[3] = mColor.alphaF();
    glDisable(GL_COLOR_MATERIAL);
    glPushMatrix();
        glTranslated(mCenter.x(),mCenter.y(),mCenter.z());
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lColor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lDiffuse);
        glutSolidSphere(pRadius, p, m);
    glPopMatrix();
}

/*//calcul le gradient au point p
CPoint_3D CBlob_Spherical::Compute_Gradient(CPoint_3D p)
{ 
	double dMdr;
	CPoint_3D temp;

	dMdr=dMuraki(Distance3D(p,Center),Ray);
		
	temp.Put_x(dEuclidianx(p,Center)*dMdr);
	temp.Put_y(dEuclidiany(p,Center)*dMdr);
	temp.Put_z(dEuclidianz(p,Center)*dMdr);

	return(temp);
}

//calcul le gradient pour la fonction de murakami
CPoint_3D CBlob_Spherical::Compute_Gradient_Muraki(CPoint_3D p)
{

	double r,r2,R2,R4,val;
	CPoint_3D temp;

	r=Distance3D(p,Center);
	r2=r*r;
	R2=Ray*Ray;
	R4=R2*R2;
	val=r2/R4-1/R2;

	temp.Put_x((Center.Get_x()-p.Get_x())*val);
	temp.Put_y((Center.Get_y()-p.Get_y())*val);
	temp.Put_z((Center.Get_z()-p.Get_z())*val);

	return(temp);
}

//calcul la position par rapport à l'intervalle donné
char CBlob_Spherical::Relative_Position(CInterval_3D inter)
{
	char res=0;
	long double MinD,MaxD;
	CPoint_3D MinP,MaxP;

	MinD=inter.Distance_Min(Center);
	MaxD=inter.Distance_Max(Center);

	if (MinD>=Ray*Inf_Param)
		res=-1;
	else 
		if (MaxD<Ray*Inf_Param)
			res=1;
		else
			res=0;

	return res;
}

//permet de savoir si un blob est contenu dans un intervalle donné
bool CBlob_Spherical::isEmpty(CInterval_3D inter)
{
    qWarning()<<"CBlob_Spherical"<<__func__<<"return always false while this have been tested ";
    return false;

	CInterval_3D InterNewCoord;
	CPoint_3D Nearest;
	bool res;

	// Changement de repere pour l'intervalle => Origine devient centre du blob
	InterNewCoord.Set(inter.Get_X()-Center.Get_x(),inter.Get_Y()-Center.Get_y(),inter.Get_Z()-Center.Get_z());

	if (0<InterNewCoord.Get_X().Get_Bi())
		Nearest.Put_x(InterNewCoord.Get_X().Get_Bi());
	else {
		if (0<=InterNewCoord.Get_X().Get_Bs())
			Nearest.Put_x(0);
		else 
			Nearest.Put_x(InterNewCoord.Get_X().Get_Bs());
	}

	if (0<InterNewCoord.Get_Y().Get_Bi())
		Nearest.Put_y(InterNewCoord.Get_Y().Get_Bi());
	else {
		if (0<=InterNewCoord.Get_Y().Get_Bs())
			Nearest.Put_y(0);
		else 
			Nearest.Put_y(InterNewCoord.Get_Y().Get_Bs());
	}

	if (0<InterNewCoord.Get_Z().Get_Bi())
		Nearest.Put_z(InterNewCoord.Get_Z().Get_Bi());
	else {
		if (0<=InterNewCoord.Get_Z().Get_Bs())
			Nearest.Put_z(0);
		else 
			Nearest.Put_z(InterNewCoord.Get_Z().Get_Bs());
	}

	if (sqrt(Nearest.Get_x()*Nearest.Get_x()+Nearest.Get_y()*Nearest.Get_y()+Nearest.Get_z()*Nearest.Get_z())<Ray*Inf_Param)
		res=false;
	else{
		res=true;
	}

	return res;
}*/
 
//permet de savoir si un point est à l'interieur du blob
bool CBlob_Spherical::isInside(const QVector3D& pPoint) const
{
        return ((Distance3D(mCenter,pPoint)<=mRadius)?true:false);
}

/* TODO  : see if these methods are used
//permet de calculer les valeurs de murakami sur l'interval en paramètre
CInterval CBlob_Spherical::Compute_Val_Muraki(CInterval inter[3])
{
	double xc, yc, zc;
	CInterval x, y, z, r;
	CInterval res;
	
	x = inter[0];
	y = inter[1];
	z = inter[2];
	xc = Center.Get_x();
	yc = Center.Get_y();
	zc = Center.Get_z();

	r = sqrt(sqr(x-xc)+sqr(y-yc)+sqr(z-zc));
	
	if (Ray&r)
		res = sqr(1-sqr(r/Ray));	
	else
		res = CInterval(0.0, 0.0);
	
	return res;
}

//retourne les valeurs de l'interval
CInterval CBlob_Spherical::Compute_Val(CInterval inter[3])
{
	return Compute_Val_Muraki(inter);
}


//calcul le gradient pour l'interval placé en paramètre
CInterval_3D CBlob_Spherical::Compute_Gradient(CInterval_3D inter)
{
	long double xc, yc, zc;
	CInterval x, y, z, r, add1, add2, mult1;
	CInterval_3D res;
 
	x = inter.Get_X();y = inter.Get_Y();z = inter.Get_Z();
	xc = (long double)Center.Get_x();yc = (long double)Center.Get_y();zc = (long double)Center.Get_z();

	r = sqr(x-xc)+sqr(y-yc)+sqr(z-zc);

	if (r>=Ray)
		inter.Set(0,0,0,0,0,0);
	else
	{
		add1 = 4.0/(Ray*Ray*Ray*Ray);
		add2 = 4.0/(Ray*Ray);
		mult1 = (add1*r)-add2;
		res.Set((xc-x)*mult1,(yc-y)*mult1,(zc-z)*mult1);	
		res.Display();
	}
	return res;
}



// Calcul du Hessien en un point donné 
long double** CBlob_Spherical::Compute_Hessien(CPoint_3D p)
{
	long double** res;
	double xc, yc, zc;
	double x,  y,  z;
	double r;
	double u1, u2, u3;
	double vx, vy, vz, v;

	res = new long double*[3];

	for(int i=0; i<3; i++)
		res[i] = new long double[3];

	xc = Center.Get_x();
	yc = Center.Get_y();
	zc = Center.Get_z();

	x  = p.Get_x();
	y  = p.Get_y();
	z  = p.Get_z();

	r  = Distance3D(p,Center);

	u1 = xc-x;
	u2 = yc-y;
	u3 = zc-z;

	vx = (8.0*(x-xc))/(Ray*Ray*Ray*Ray);
	vy = (8.0*(y-yc))/(Ray*Ray*Ray*Ray);
	vz = (8.0*(z-zc))/(Ray*Ray*Ray*Ray);

	v  = ((4.0*r*r)/(Ray*Ray*Ray*Ray)) - (4.0/(Ray*Ray));

	res[0][0] = (u1*vx)-v;
	res[0][1] = (u1*vy);
	res[0][2] = (u1*vz);

	res[1][0] = (u2*vx);
	res[1][1] = (u2*vy)-v;
	res[1][2] = (u2*vz);

	res[2][0] = (u3*vx);
	res[2][1] = (u3*vy);
	res[2][2] = (u3*vz)-v;

	return res;
}*/

// retourne le type de blob
int CBlob_Spherical::type(void) const
{
	return Spherique;
}

//retourne le segment A
const QVector3D& CBlob_Spherical::getSegmentA() const
{
        return mCenter;
}

//retourne le segment B
const QVector3D& CBlob_Spherical::getSegmentB() const
{
        return mCenter;
}

//permet de cloner un blob
CBlob_Spherical* CBlob_Spherical::clone() const
{
        CBlob_Spherical *lNewBlob = new CBlob_Spherical(mCenter, mRadius, mInfParam, mTypeReconstruction, mColor);
        // TODO : useless method?
        lNewBlob->setTypeReconstruction(mTypeReconstruction);
        return lNewBlob;
}

/*
// ---------------------
// class CBlob_Cylindric
// ---------------------
//constructeur
CBlob_Cylindric::CBlob_Cylindric(void)
{
}

//constructeur
CBlob_Cylindric::CBlob_Cylindric(CPoint_3D a,CPoint_3D b,double r,double i,int t,double c[4])
{
	Segment_A=a;Segment_B=b;
	Ray=r;Inf_Param=i;
	Type_Function=t;
	Color[0]=c[0];Color[1]=c[1];Color[2]=c[2];Color[3]=c[3];
}

//destrcuteur
CBlob_Cylindric::~CBlob_Cylindric(void)
{}

//permet d'obtenir le rayon
double CBlob_Cylindric::Get_Ray(void)
{
	return Ray;
}

//permet d'obtenir la valeur de seuil
double CBlob_Cylindric::Get_Inf_Param(void)
{
	return Inf_Param;
}

//permet d'obtenir le type de fonctio utlisé pour la reconstruction
int CBlob_Cylindric::Get_Type_Function(void)
{
	return Type_Function;
}

//permet de savoir quelle reconstruction on utilise
int CBlob_Cylindric::Get_Type_Reconstruction(void)
{
	return Type_Reconstruction;
}

//retourne la couleur du blob
double *CBlob_Cylindric::Get_Color(void)
{
	return Color;
}

//regle le segment A du blob
void CBlob_Cylindric::Put_Segment_A(CPoint_3D a)
{
	Segment_A=a;
}

//regle le segment B du blob
void CBlob_Cylindric::Put_Segment_B(CPoint_3D b)
{
	Segment_B=b;
}

//regle de rayon du blob
void CBlob_Cylindric::Put_Ray(double r)
{
	Ray=r;
}

//regle la valeur de seuil
void CBlob_Cylindric::Put_Inf_Param(double i)
{
	Inf_Param=i;
}

//règle le type de fonction utilisé pour calculer le blob
void CBlob_Cylindric::Put_Type_Function(int t)
{
	Type_Function=t;
}

//regle le type de reconstruction
void CBlob_Cylindric::Put_Type_Reconstruction(int t)
{
	Type_Reconstruction=t;
}

//regle la couleur du blob
void CBlob_Cylindric::Put_Color(float col[4])
{
	Color[0]=col[0];
	Color[1]=col[1];
	Color[2]=col[2];
	Color[3]=col[3];
}

//Operateur d'égalité
CBlob_Cylindric& CBlob_Cylindric::operator = (const CBlob_Cylindric & b)
{
	Segment_A=b.Segment_A;Segment_B=b.Segment_B;
	Ray=b.Ray;Inf_Param=b.Inf_Param;Type_Function=b.Type_Function;
	Color[0]=b.Color[0];Color[1]=b.Color[1];Color[2]=b.Color[2];Color[3]=b.Color[3];
	return *this;
}

//affiche les infos du blob
void CBlob_Cylindric::Blob_Info(void)
{
	printf("Segment A : %.6f %.6f %.6f B : %.6f %.6f %.6f\n",Segment_A.Get_x(),Segment_A.Get_y(),Segment_A.Get_z(),Segment_B.Get_x(),Segment_B.Get_y(),Segment_B.Get_z());
	printf("Rayon : %.6f - Influence : %.6f\n",Ray,Inf_Param);
	switch (Type_Function)
	{
	case 1:
		printf("Type de fonction : Muraki\n");
	break;
	case 2:
		printf("Type de fonction : Wywill\n");
	break;
	}
	printf("Couleur : %.3f %.3f %.3f %.3f\n",Color[0],Color[1],Color[2],Color[3]);
}

//calcul la distance du blob par rapport au point M
double CBlob_Cylindric::Compute_Dist(CPoint_3D M)
{
	double t,d;
	
	CPoint_3D AB=Segment_B-Segment_A,AM=M-Segment_A,O(0,0,0);

	d=Distance3D(O,AB);
	t=Dot_Product_3D(AB,AM)/(d*d);
	if (t>1)
		return(Distance3D(M,Segment_B));
	if (t<0)
		return(Distance3D(M,Segment_A));
	CPoint_3D N=Segment_A+AB*t;
	d=Distance3D(M,N);
	return d;
}

//calcule la boite englobante du blob
void CBlob_Cylindric::Compute_Bounds(double &xmin,double &ymin,double &zmin,double &xmax,double &ymax,double &zmax)
{
	xmin=MIN(Segment_A.Get_x()-Ray*Inf_Param,Segment_B.Get_x()-Ray*Inf_Param);
	ymin=MIN(Segment_A.Get_y()-Ray*Inf_Param,Segment_B.Get_y()-Ray*Inf_Param);
	zmin=MIN(Segment_A.Get_z()-Ray*Inf_Param,Segment_B.Get_z()-Ray*Inf_Param);
	xmax=MAX(Segment_A.Get_x()+Ray*Inf_Param,Segment_B.Get_x()+Ray*Inf_Param);
	ymax=MAX(Segment_A.Get_y()+Ray*Inf_Param,Segment_B.Get_y()+Ray*Inf_Param);
	zmax=MAX(Segment_A.Get_z()+Ray*Inf_Param,Segment_B.Get_z()+Ray*Inf_Param);
}

//calcule la valeur de la fonction au point pt
double CBlob_Cylindric::Compute_Val(CPoint_3D pt)
{	
	double d,val;
	
	d=Compute_Dist(pt);
	switch (Type_Function)
	{
		case 1 :
		val=Muraki(d,Ray);
		break;
		case 2 :
		val=Wywill(d,Ray);
		break;

		default:
		printf("Mauvais type de fonction pour le calcul !\n");
		val=0.0;
		break;
	}
	return (val);
}

//calcule la valeur au rayon r
double CBlob_Cylindric::Compute_Val(double r)
{	
	double val;

	switch (Type_Function)
	{
		case 1 :
		val=Muraki(r,Ray);
		break;

		case 2 :
		val=Wywill(r,Ray);
		break;

		default:
		printf("Mauvais type de fonction pour le calcul !\n");
		val = 0.0;
		break;
	}
	return (val);
}

//retourne le centre du blob
CPoint_3D CBlob_Cylindric::Get_Center(void)
{
	return((Segment_A+Segment_B)*0.5);
}

//calcule le gradient du blob
CPoint_3D CBlob_Cylindric::Compute_Gradient(CPoint_3D p)
{ 
	CPoint_3D temp;
	double t,d;
	
	CPoint_3D AB=Segment_B-Segment_A,AM=p-Segment_A,O(0,0,0);
	//Modification lors de l'application sur blobs cylindriques
	// modification à partir du code pour les blobs sphériques ;)
	double r,r2,R2,R4,val;

	r=this->Compute_Dist(p);
	r2=r*r;
	R2=this->Get_Ray()*this->Get_Ray();
	R4=R2*R2;
	val=r2/R4-1/R2;
	d=Distance3D(O,AB);
	t=Dot_Product_3D(AB,AM)/(d*d);
	if (t>1){
		temp.Put_x( (this->Get_Segment_B().Get_x()-p.Get_x()) *val);
		temp.Put_y((this->Get_Segment_B().Get_y()-p.Get_y())*val);
		temp.Put_z((this->Get_Segment_B().Get_z()-p.Get_z())*val);

		return temp;
	}		
	else{
		if (t<0){
			temp.Put_x((this->Get_Segment_B().Get_x()-p.Get_x())*val);
			temp.Put_y((this->Get_Segment_B().Get_y()-p.Get_y())*val);
			temp.Put_z((this->Get_Segment_B().Get_z()-p.Get_z())*val);
			return temp;
		}
	}
	CPoint_3D N=Segment_A+AB*t;
	temp.Put_x((N.Get_x()-p.Get_x())*val);
	temp.Put_y((N.Get_y()-p.Get_y())*val);
	temp.Put_z((N.Get_z()-p.Get_z())*val);
	return(temp);
}
//calcule la position relative par rapport à l'intervalle inter
char CBlob_Cylindric::Relative_Position(CInterval_3D inter)
{
	// Attention l'algo est une simple bidouille pas sur que ca fonctionne correctement
	char res=0;
	long double MinDA,MaxDA,MinDB,MaxDB,MinD,MaxD;
	CPoint_3D MinP,MaxP;
	MinDA = inter.Distance_Min(Segment_A);
	MinDB = inter.Distance_Min(Segment_B);

	MaxDA = inter.Distance_Max(Segment_A);
	MaxDB = inter.Distance_Max(Segment_B);

	MinD = (MinDA<=MinDB)?MinDA:MinDB;
	MaxD = (MaxDA>=MaxDB)?MaxDA:MaxDB;

	if(MinD>Ray*Inf_Param)
		res=-1;
	else{
		if(MaxD<Ray*Inf_Param)
			res=1;
		else{
			res=0;
		}
	}
	return res;
}

//permet de savoir si un blob est vide ou non
bool CBlob_Cylindric::IsEmpty(CInterval_3D inter)
{
	//CInterval_3D InterNewCoord;
	CPoint_3D Nearest;
	bool res;
	float minx = min(Segment_A.Get_x(),Segment_B.Get_x()),maxx=max(Segment_A.Get_x(),Segment_B.Get_x());
	float miny = min(Segment_A.Get_y(),Segment_B.Get_y()),maxy=max(Segment_A.Get_y(),Segment_B.Get_y());
	float minz = min(Segment_A.Get_z(),Segment_B.Get_z()),maxz=max(Segment_A.Get_z(),Segment_B.Get_z());

	if (0<inter.Get_X().Get_Bi()-minx)
		Nearest.Put_x(inter.Get_X().Get_Bi()-minx);
	else {
		if (0<=inter.Get_X().Get_Bs()-maxx)
			Nearest.Put_x(0);
		else 
			Nearest.Put_x(inter.Get_X().Get_Bs()-maxx);
	}

	if (0<inter.Get_Y().Get_Bi()-miny)
		Nearest.Put_y(inter.Get_Y().Get_Bi()-miny);
	else {
		if (0<=inter.Get_Y().Get_Bs()-maxy)
			Nearest.Put_y(0);
		else 
			Nearest.Put_y(inter.Get_Y().Get_Bs()-maxy);
	}

	if (0<inter.Get_Z().Get_Bi()-minz)
		Nearest.Put_z(inter.Get_Z().Get_Bi()-minz);
	else {
		if (0<=inter.Get_Z().Get_Bs()-maxz)
			Nearest.Put_z(0);
		else 
			Nearest.Put_z(inter.Get_Z().Get_Bs()-maxz);
	}

	if (sqrt(Nearest.Get_x()*Nearest.Get_x()+Nearest.Get_y()*Nearest.Get_y()+Nearest.Get_z()*Nearest.Get_z())<Ray*Inf_Param)
		res=false;
	else{
		res=true;
	}

	return res;
}

//permet de savoir si le point est contenu dans le blob
bool CBlob_Cylindric::IsInside(CPoint_3D p)
{
	this->Compute_Dist(p);
	return((this->Compute_Dist(p)<=Ray)?true:false);
}

//calcul les valeurs de la fonction de murakami surl'intervalle placé en param.
CInterval CBlob_Cylindric::Compute_Val(CInterval inter[3])
{
	return Compute_Val_Muraki(inter);
}
CInterval_3D CBlob_Cylindric::Compute_Gradient(CInterval_3D inter)
{
	// A FAIRE

	// Guillaume PERADON -> lorsque j'ai récupéré ce programme j'ai remarqué que 
	// Vincent n'a jamais appelé dans son programme l'étude des points critique sur la liste de blobs
	// il est donc inutile d'implémenter cette méthode.... Eh oui mode fénéant on ^^



	return inter;
}

//calcul du hessien
long double** CBlob_Cylindric::Compute_Hessien(CPoint_3D p)
{
	// Note : d'un point de vue numérique une dérivée s'apparente à un calcul ede limite en 0
	// on fait donc varier un tout petit peu notre point, recalcule la valeur de la fonction explicite ( murakami )
	// et on a notre valeur de dérivée ( pour le hession on calcule ca plusieurs fois ^^

	//Point = (fx,fy,fz)
	//f'({x,y,y}) = lim h->0 = f({x,y,z}+h)-f({x,y,z}) / h

long double** res;
	double xc, yc, zc;
	double x,  y,  z;
	double r;
	double u1, u2, u3;
	double vx, vy, vz, v;

	res = new long double*[3];

	for(int i=0; i<3; i++)
		res[i] = new long double[3];


	//calcul de la position relativement au squelette du blob
	CPoint_3D AB=Segment_B-Segment_A,AM=p-Segment_A,O(0,0,0);
	CPoint_3D N;
	double d=Distance3D(O,AB);
	double t=Dot_Product_3D(AB,AM)/(d*d);
	if (t>1)
		N=Segment_B;
	else{
		if (t<0)
			N=Segment_A;
		else
			N=Segment_A+AB*t;
	}

	xc = N.Get_x();
	yc = N.Get_y();
	zc = N.Get_z();

	x  = p.Get_x();
	y  = p.Get_y();
	z  = p.Get_z();

	r  = Distance3D(p,N);

	u1 = xc-x;
	u2 = yc-y;
	u3 = zc-z;

	vx = (8.0*(x-xc))/(Ray*Ray*Ray*Ray);
	vy = (8.0*(y-yc))/(Ray*Ray*Ray*Ray);
	vz = (8.0*(z-zc))/(Ray*Ray*Ray*Ray);

	v  = ((4.0*r*r)/(Ray*Ray*Ray*Ray)) - (4.0/(Ray*Ray));

	res[0][0] = (u1*vx)-v;
	res[0][1] = (u1*vy);
	res[0][2] = (u1*vz);

	res[1][0] = (u2*vx);
	res[1][1] = (u2*vy)-v;
	res[1][2] = (u2*vz);

	res[2][0] = (u3*vx);
	res[2][1] = (u3*vy);
	res[2][2] = (u3*vz)-v;

	return res;
}

//retourne le type du blob courant
int CBlob_Cylindric::Get_Type_Of_Blob(void)
{
	return Cylindrique;
}

//retourne le segmentA
CPoint_3D CBlob_Cylindric::Get_Segment_A()
{
	return Segment_A;
}

//retourne le segment B du blob
CPoint_3D CBlob_Cylindric::Get_Segment_B()
{
	return Segment_B;
}

//fonction de clonage du blob cylindrique
CBlob_Cylindric* CBlob_Cylindric::clone()
{
	CBlob_Cylindric *nouveau = new CBlob_Cylindric(Segment_A,Segment_B,Ray,Inf_Param,Type_Reconstruction,Color);
	nouveau->Put_Type_Reconstruction(Type_Reconstruction);
	return nouveau;
}

//calcul des valeurs de muraki sur un intervalle 3D
CInterval CBlob_Cylindric::Compute_Val_Muraki(CInterval inter[3])
{
	//double xc, yc, zc;
	CInterval x, y, z, r,*xc,*yc,*zc;
	CInterval res;
	
	x = inter[0];
	y = inter[1];
	z = inter[2];

	xc = new CInterval(Segment_A.Get_x(),Segment_B.Get_x());
	yc = new CInterval(Segment_A.Get_y(),Segment_B.Get_y());
	zc = new CInterval(Segment_A.Get_z(),Segment_B.Get_z());

	r = sqrt(sqr(x-*xc)+sqr(y-*yc)+sqr(z-*zc));
	if (Ray&r)
		res = sqr(1-sqr(r/Ray));	
	else
		res = CInterval(0.0, 0.0);
	return res;
}

// ------------------
// class CBlob_Square
// ------------------

CBlob_Rectangle::CBlob_Rectangle(void)
{}

CBlob_Rectangle::CBlob_Rectangle(CPoint_3D A,CPoint_3D B,CPoint_3D C,CPoint_3D D,double r,double i,int t,double c[4])
{
	Segment_A=A;Segment_B=B;Segment_C=C;Segment_D=D;
	Ray=r;Inf_Param=i;
	Type_Function=t;
	Color[0]=c[0];Color[1]=c[1];Color[2]=c[2];Color[3]=c[3];
}

CBlob_Rectangle::~CBlob_Rectangle(void)
{}

double CBlob_Rectangle::Get_Ray(void)
{	return Ray;}

double CBlob_Rectangle::Get_Inf_Param(void)
{	return Inf_Param;}

int CBlob_Rectangle::Get_Type_Function(void)
{ return Type_Function;}

double *CBlob_Rectangle::Get_Color(void)
{	return Color;}

void CBlob_Rectangle::Put_Segment_A(CPoint_3D a)
{	Segment_A=a;}

void CBlob_Rectangle::Put_Segment_B(CPoint_3D b)
{	Segment_B=b;}

void CBlob_Rectangle::Put_Ray(double r)
{	Ray=r;}

void CBlob_Rectangle::Put_Inf_Param(double i)
{	Inf_Param=i;}

void CBlob_Rectangle::Put_Type_Function(int t)
{	Type_Function=t;}

void CBlob_Rectangle::Put_Color(float col[4])
{	Color[0]=col[0];Color[1]=col[1];Color[2]=col[2];Color[3]=col[3];}

CBlob_Rectangle & CBlob_Rectangle::operator = (const CBlob_Rectangle & b)
{
	Segment_A=b.Segment_A;Segment_B=b.Segment_B;Segment_C=b.Segment_C;Segment_D=b.Segment_D;
	Ray=b.Ray;Inf_Param=b.Inf_Param;Type_Function=b.Type_Function;
	Color[0]=b.Color[0];Color[1]=b.Color[1];Color[2]=b.Color[2];Color[3]=b.Color[3];
	return *this;
}

void CBlob_Rectangle::Blob_Info(void)
{
	printf("Sommet A : %.6f %.6f %.6f - Sommet B : %.6f %.6f %.6f\n",Segment_A.Get_x(),Segment_A.Get_y(),Segment_A.Get_z(),Segment_B.Get_x(),Segment_B.Get_y(),Segment_B.Get_z());
	printf("Sommet C : %.6f %.6f %.6f - Sommet D : %.6f %.6f %.6f\n",Segment_C.Get_x(),Segment_C.Get_y(),Segment_C.Get_z(),Segment_D.Get_x(),Segment_D.Get_y(),Segment_D.Get_z());
	printf("Rayon : %.6f - Influence : %.6f\n",Ray,Inf_Param);
	switch (Type_Function)
	{
	case 1:
		printf("Type de fonction : Muraki\n");
	break;
	case 2:
		printf("Type de fonction : Wywill\n");
	break;
	}
	printf("Couleur : %.3f %.3f %.3f %.3f\n",Color[0],Color[1],Color[2],Color[3]);
}

double CBlob_Rectangle::Compute_Dist(CPoint_3D p)
{

return(3);
}


// ------------------
// class CBlob_Linked
// ------------------

CBlob_Linked::CBlob_Linked(void)
{Prec=Next=NULL;}

CBlob_Linked::CBlob_Linked(CBlob_Linked *p,CBlob_Linked *n)
{Prec=p;Next=n;}

CBlob_Linked::~CBlob_Linked(void)
{delete Blob;}

CBlob_Linked * CBlob_Linked::Get_Prec(void)
{return Prec;}

CBlob_Linked * CBlob_Linked::Get_Next(void)
{return Next;}
int CBlob_Linked::Get_Type_Of_Blob(){
	return Blob->Get_Type_Of_Blob(); 
}
void CBlob_Linked::Set_Next(CBlob_Linked* suivant){
	Next = suivant;
}
void CBlob_Linked::Set_Prec(CBlob_Linked* prec){
	Prec=prec;
}
CBlob_Linked* CBlob_Linked::clone(){
	CBlob_Linked* nouveau = new CBlob_Linked(this->Get_Prec(), this->Get_Next());
	nouveau->Blob=this->Blob->clone();
	return nouveau;
}
*/
// ----------------
// class CList_BLob
// ----------------

CList_BLob::CList_BLob(void)
{
    //	First=Last=NULL;Nb_Blobs=0;
        mXMin=mYMin=mZMin=1000000;
        mXMax=mYMax=mZMax=-100000;
        mThreshold = 0;
//	criticalIntervalIndex=0;
//	criticalPointIndex=0;
}

double CList_BLob::Get_Threshold(void)
{return mThreshold;}

long double CList_BLob::getXMin(void)
{
    return mXMin;
}
long double CList_BLob::getYMin(void)
{
    return mYMin;
}
long double CList_BLob::getZMin(void)
{
    return mZMin;
}
long double CList_BLob::getXMax(void)
{
    return mXMax;
}
long double CList_BLob::getYMax(void)
{
    return mYMax;
}
long double CList_BLob::getZMax(void)
{
    return mZMax;
}
CVoxel_8 CList_BLob::Get_Bounded_Box(void)
{
    return mBoundedBox;
}
int CList_BLob::size() {
    return mBlobList.size();
}

//int CList_BLob::Get_Nb_Blobs(void)
//{return Nb_Blobs;}

void CList_BLob::Set_Threshold(double T)
{
        mThreshold=T;
}

void CList_BLob::Add_Blob(CBlob *B)
{
    if( B == NULL ) return;

	double x_min,y_min,z_min,x_max,y_max,z_max;
	x_min=y_min=z_min=100000;
	x_max=y_max=z_max=-100000;
    /*	if (Nb_Blobs>0)
	{
		Last->Next=new CBlob_Linked;
		Last->Next->Prec=Last;
		Last=Last->Next;
		Last->Next=NULL;
		Last->Blob=B;
		Last->Blob->Compute_Bounds(x_min,y_min,z_min,x_max,y_max,z_max);
		if (x_min<xmin) xmin=x_min;
		if (y_min<ymin) ymin=y_min;
		if (z_min<zmin) zmin=z_min;
		if (x_max>xmax) xmax=x_max;
		if (y_max>ymax) ymax=y_max;
		if (z_max>zmax) zmax=z_max;
		Nb_Blobs++;
	}
	else
	{
		First=new CBlob_Linked;
		First->Prec=First->Next=NULL;
		Last=First;
		First->Blob=B;		
		First->Blob->Compute_Bounds(x_min,y_min,z_min,x_max,y_max,z_max);
		if (x_min<xmin) xmin=x_min;
		if (y_min<ymin) ymin=y_min;
		if (z_min<zmin) zmin=z_min;
		if (x_max>xmax) xmax=x_max;
		if (y_max>ymax) ymax=y_max;
		if (z_max>zmax) zmax=z_max;
		Nb_Blobs++;
	}
        */
        /** New Code **/
        mBlobList.append(B);
        mBlobList.last()->computeBounds(x_min, y_min, z_min, x_max, y_max, z_max);
        if (x_min<mXMin) mXMin=x_min;
        if (y_min<mYMin) mYMin=y_min;
        if (z_min<mZMin) mZMin=z_min;
        if (x_max>mXMax) mXMax=x_max;
        if (y_max>mYMax) mYMax=y_max;
        if (z_max>mZMax) mZMax=z_max;
        /** End new code **/

        mBoundedBox.Put_Vertex(0,mXMin,mYMin,mZMin);
        mBoundedBox.Put_Vertex(1,mXMax,mYMin,mZMin);
        mBoundedBox.Put_Vertex(2,mXMax,mYMin,mZMax);
        mBoundedBox.Put_Vertex(3,mXMin,mYMin,mZMax);
        mBoundedBox.Put_Vertex(4,mXMin,mYMax,mZMin);
        mBoundedBox.Put_Vertex(5,mXMax,mYMax,mZMin);
        mBoundedBox.Put_Vertex(6,mXMax,mYMax,mZMax);
        mBoundedBox.Put_Vertex(7,mXMin,mYMax,mZMax);
}

void CList_BLob::List_Info(void)
{
        /* Old Code
        int i=0;

        CBlob_Linked *Current=First;
	printf("Affichage des %d blobs :\n\n",Nb_Blobs);

	while (i<Nb_Blobs)
	{
		printf("Blob %d :\n",i+1);
		Current->Blob->Blob_Info();
		printf("\n");
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else break;
		i++;
	}
	printf("Boite englobante :\n");
	Bounded_Box.Voxel_Info();

        */

        /** New code */
        int lCount = 0;
        qWarning()<<"Affichage de "<<mBlobList.size()<<" blobs :";
        QListIterator<CBlob*> lIte(mBlobList);
        while(lIte.hasNext()) {
            ++lCount;
            CBlob_Spherical* lTemp = dynamic_cast<CBlob_Spherical*>(lIte.next());
            qWarning()<<"Blob "<<lCount<<lTemp->getThreshold();
            lTemp->Blob_Info();
        }
        qWarning()<<"Boite englobante";
        mBoundedBox.Voxel_Info();
}

CBlob* CList_BLob::Nearest_Blob(QVector3D p)
{
        /* Old Code
        int i=1;
	double distance=1000000,dist;

	CBlob_Linked *Current=First,*Temp;
	
	while (i<=Nb_Blobs)
	{
		
		dist=Current->Blob->Compute_Dist(p);
		if (dist<distance)
		{
			distance=dist;Temp=Current;
		}

		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else 
			break;
		i++;
	}
	return Temp->Blob;
        */
    CBlob* lClosestBlob = mBlobList.first();
    double lDist = 1000000000;
    QListIterator<CBlob*> lIte(mBlobList);
    while(lIte.hasNext()) {
        CBlob* lTemp = lIte.next();
        double lTempDist = lTemp->computeDistance(p);
        if( lTempDist < lDist) {
            lClosestBlob = lTemp;
            lDist = lTempDist;
        }
    }
    return lClosestBlob;
}


void CList_BLob::drawBlobsThreshold(int pBlobType) const
{

    QListIterator<CBlob*> lIte(mBlobList);
    while(lIte.hasNext()) {
        CBlob* lTemp = lIte.next();
        if( lTemp->getTypeReconstruction() == pBlobType ) {
            lTemp->drawThreshold();
        }
    }
    /*
	int i=1;
	CBlob_Linked *Current=First;
	
	float Material_Color[3];

	while (i<=Nb_Blobs)
	{
		if (Current->Blob->Get_Type_Reconstruction()==Blob_type && Current->Blob->Get_Type_Reconstruction()!=4)
		{
			glPushMatrix();
			glTranslated(Current->Blob->Get_Center().Get_x(),Current->Blob->Get_Center().Get_y(),Current->Blob->Get_Center().Get_z());
			Material_Color[0]=(float) Current->Blob->Get_Color()[0];
			Material_Color[1]=(float) Current->Blob->Get_Color()[1];
			Material_Color[2]=(float) Current->Blob->Get_Color()[2];
			if(Current->Blob->Get_Color()[0]!=bleu[0] && Current->Blob->Get_Color()[1]!=bleu[1] && Current->Blob->Get_Color()[2]!=bleu[2])
			{
				if(Current->Blob->Get_Type_Reconstruction()==Interieur){
					printf("erreur....\n");
				}
			}
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,Material_Color);
			switch( Current->Get_Type_Of_Blob() ){
				case Spherique:
					glutSolidSphere(Current->Blob->Get_Ray(),15,15);
					break;
				case Cylindrique :
					float angleZ=0.,angleY=0.,angleX=0.;
					glEnable(GL_CULL_FACE);
					glPushMatrix();
                                        glDisable(GL_CULL_FACE);
					float longueur = Distance3D(Current->Blob->Get_Segment_A() ,Current->Blob->Get_Segment_B());
					if(Current->Blob->Get_Segment_A().Get_x()==Current->Blob->Get_Segment_B().Get_x() && Current->Blob->Get_Segment_A().Get_z()==Current->Blob->Get_Segment_B().Get_z())
					{
						glutSolidCylinder(Current->Blob->Get_Ray(),longueur,15,15);
					}
					else{
						if(Current->Blob->Get_Segment_A().Get_y()==Current->Blob->Get_Segment_B().Get_y() && Current->Blob->Get_Segment_A().Get_z()==Current->Blob->Get_Segment_B().Get_z())
						{
							glRotatef(90,0,0,1);
							glutSolidCylinder(Current->Blob->Get_Ray(),longueur,15,15);
						}
						else{
							if(Current->Blob->Get_Segment_A().Get_x()==Current->Blob->Get_Segment_B().Get_x() && Current->Blob->Get_Segment_A().Get_y()==Current->Blob->Get_Segment_B().Get_y())
							{
								glRotatef(90,1,0,0);
							}
							else{
								angleZ=AngleXY(Current->Blob)-M_PI/2;
								angleY=AngleXZ(Current->Blob)-M_PI/2;
								glRotatef(angleZ*180./M_PI,0,0,1);
								glRotatef(angleY*180./M_PI,01,0,0);
							}
						}
					}
					glutSolidCylinder(Current->Blob->Get_Ray(),longueur,15,15);
					glPopMatrix();

					break;
			}
			glPopMatrix();
		}
		if(Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else{
			break;
		}
		i++;
        }*/
}

void CList_BLob::drawBlobsInfluence(int pBlobType) const
{
    QListIterator<CBlob*> lIte(mBlobList);
    while(lIte.hasNext()) {
        CBlob* lTemp = lIte.next();
        if( lTemp->getTypeReconstruction() == pBlobType ) {
            lTemp->drawInfluence();
        }
    }
        /*int i=1;
	CBlob_Linked *Current=First;
	
	float Material_Color[3];

	while (i<=Nb_Blobs)
	{
		if (Current->Blob->Get_Type_Reconstruction()==Blob_type)
		{
			glPushMatrix();
			glTranslated(Current->Blob->Get_Center().Get_x(),Current->Blob->Get_Center().Get_y(),Current->Blob->Get_Center().Get_z());
			Material_Color[0]=(float) Current->Blob->Get_Color()[0];
			Material_Color[1]=(float) Current->Blob->Get_Color()[1];
			Material_Color[2]=(float) Current->Blob->Get_Color()[2];
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,Material_Color);
			switch( Current->Get_Type_Of_Blob() ){
				case Spherique:
					glutSolidSphere(Current->Blob->Get_Ray()*sqrt(1-sqrt(Threshold)),15,15);
					break;
				//case Cylindrique :
				//	glPushMatrix();
				//	glDisable(GL_CULL_FACE);
				//	glutSolidCylinder(Current->Blob->Get_Ray()*sqrt(1-sqrt(Threshold)),Distance3D(Current->Blob->Get_Segment_A() ,Current->Blob->Get_Segment_B()),15,15);
				//	glPopMatrix();
				//	glEnable(GL_CULL_FACE);
				//	break;
				case Cylindrique :
					float angleZ=0.,angleY=0.,angleX=0.;
					glEnable(GL_CULL_FACE);
					glPushMatrix();
					glDisable(GL_CULL_FACE);
					float longueur = Distance3D(Current->Blob->Get_Segment_A() ,Current->Blob->Get_Segment_B());
					if(Current->Blob->Get_Segment_A().Get_x()==Current->Blob->Get_Segment_B().Get_x() && Current->Blob->Get_Segment_A().Get_z()==Current->Blob->Get_Segment_B().Get_z())
					{
						//glutSolidCylinder(Current->Blob->Get_Ray(),longueur,15,15);
					}
					else{
						if(Current->Blob->Get_Segment_A().Get_y()==Current->Blob->Get_Segment_B().Get_y() && Current->Blob->Get_Segment_A().Get_z()==Current->Blob->Get_Segment_B().Get_z())
						{
							glRotatef(90,0,0,1);
						}
						else{
							if(Current->Blob->Get_Segment_A().Get_x()==Current->Blob->Get_Segment_B().Get_x() && Current->Blob->Get_Segment_A().Get_y()==Current->Blob->Get_Segment_B().Get_y())
							{
								glRotatef(90,1,0,0);
								
							}
							else{
								
								angleZ=AngleXY(Current->Blob)-M_PI/2;
								angleY=AngleXZ(Current->Blob)-M_PI/2;
								glRotatef(angleZ*180./M_PI,0,0,1);
								glRotatef(angleY*180./M_PI,01,0,0);
							}
						}
					}
					glutSolidCylinder(Current->Blob->Get_Ray()*sqrt(1-sqrt(Threshold)),longueur,15,15);
					glPopMatrix();

					break;
			}
			glPopMatrix();
		}

		Current=Current->Get_Next();
		i++;
        }*/
}

void CList_BLob::readVoxellization(QVector<QVector3D> pPointTab,CVoxel_Tab* pVoxelTab, double pThreshold)
{
    if(pVoxelTab == NULL)   return;

    Q_UNUSED(pPointTab);

        double Vlength = pVoxelTab->Get_Vlength(),r = 0,p = 0;
        QVector3D lCenter;
        Vlength=pVoxelTab->Get_Vlength();

        // browsing the Voxel Tab
        for(int i=0;i<pVoxelTab->Get_Dimx();++i)
                for(int j=0;j<pVoxelTab->Get_Dimy();++j)
                        for(int k=0;k<pVoxelTab->Get_Dimz();++k)
                        {
                            /** New Code */
                            int lVoxelState = pVoxelTab->Get_State(i,j,k);
                            if( (lVoxelState == 2) || (lVoxelState == 3))
                            {
                                QColor lColor;
                                CBlob_Spherical *BS = NULL;

                                lCenter.setX((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).x()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(1).x())/2);
                                lCenter.setY((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).y()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(4).y())/2);
                                lCenter.setZ((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).z()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(3).z())/2);
                                r = qAbs( lCenter.x() - pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).x() );

                                // specific information following the type of blob to create
                                switch(lVoxelState)
                                {
                                    case 2 : {
                                        lColor = QColor(0,0,255);
                                        p = 1.5;
                                        break;
                                    }
                                    case 3 : {
                                        lColor = QColor(255,0,255);
                                        r += Vlength;
                                        p = 1.0;
                                        break;
                                    }
                                }

                                // Creating blob and adding it to the list
                                BS=new CBlob_Spherical(lCenter,r,p,1,lColor);
                                BS->setTypeReconstruction( lVoxelState );
                                BS->setThreshold(pThreshold);
                                Add_Blob(BS);
                            }

                        }
                                /* Old code */
                                /*if (pVoxelTab->Get_State(i,j,k)==3) // voxels deep
				{
					CBlob_Spherical *BS;
                                        // TODO store de voxel into local variable to avoid multiple calls?
                                        lCenter.setX((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).x()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(1).x())/2);
                                        lCenter.setY((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).y()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(4).y())/2);
                                        lCenter.setZ((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).z()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(3).z())/2);
                                        //r=Vlength*2;p=1.5;
                                        r = Vlength + qAbs( lCenter.x() - pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).x() );
                                        p = 1.0;

                                        BS=new CBlob_Spherical(lCenter,r,p,1,QColor(255,0,255));
                                        BS->setTypeReconstruction(3);
                                        BS->setThreshold(pThreshold);
					Add_Blob(BS);
				}
				else 
                                        if (pVoxelTab->Get_State(i,j,k)==2) // voxels in
					{
                                                CBlob_Spherical *BS;
                                                lCenter.setX((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).x()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(1).x())/2);
                                                lCenter.setY((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).y()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(4).y())/2);
                                                lCenter.setZ((pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).z()+pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(3).z())/2);
                                                //r=Vlength*2;p=1.5;
                                                r = qAbs( (lCenter.x() - pVoxelTab->Get_Voxel(i,j,k).Get_Vertex(0).x()) );
                                                p = pThreshold;
                                                BS=new CBlob_Spherical(lCenter,r,p,1,QColor(0,0,255));
                                                BS->setTypeReconstruction(2);
                                                BS->setThreshold(pThreshold);
                                                Add_Blob(BS);
					}
                            */

        // TODO check if this code is usefull....
        /*QVector3D v0(mXMin,mYMin,mZMin),v1(mXMax,mYMin,mZMin),v2(mXMax,mYMin,mZMax),v3(mXMin,mYMin,mZMax),
                          v4(mXMin,mYMax,mZMin),v5(mXMax,mYMax,mZMin),v6(mXMax,mYMax,mZMax),v7(mXMin,mYMax,mZMax);
        mBoundedBox.Put_Vertex(0,v0);
        mBoundedBox.Put_Vertex(1,v1);
        mBoundedBox.Put_Vertex(2,v2);
        mBoundedBox.Put_Vertex(3,v3);
        mBoundedBox.Put_Vertex(4,v4);
        mBoundedBox.Put_Vertex(5,v5);
        mBoundedBox.Put_Vertex(6,v6);
        mBoundedBox.Put_Vertex(7,v7);
        mThreshold=0.001;
        */
}


void CList_BLob::readOctreeInnerLeaves(QVector<QVector3D>& pCloud,CList_Octree_Node LON, double Voxel_Length)
{
 /*   Q_UNUSED(pCloud);
    CListed_Octree_Node *Current=LON.First;
	double r1,r2,p;
        QVector3D lCenter;
	
	do
	{	
		if (Current->Get_State()==2)
		{
			CBlob_Spherical *BS;
                        lCenter.setX((Current->Get_Voxel().Get_Vertex(0).x()+Current->Get_Voxel().Get_Vertex(6).x())/2);
                        lCenter.setY((Current->Get_Voxel().Get_Vertex(0).y()+Current->Get_Voxel().Get_Vertex(6).y())/2);
                        lCenter.setZ((Current->Get_Voxel().Get_Vertex(0).z()+Current->Get_Voxel().Get_Vertex(6).z())/2);
			//r1=((Current->Get_Voxel().Get_Vertex(6).Get_x()-Current->Get_Voxel().Get_Vertex(0).Get_x())/2)/sqrt(1-Threshold);
                        r1=((Current->Get_Voxel().Get_Vertex(6).x()-Current->Get_Voxel().Get_Vertex(0).x())/2);
			p=1;
                        BS=new CBlob_Spherical(lCenter,r1,p,1,bleu);
			BS->Put_Type_Reconstruction(2);
			Add_Blob(BS);
		}
	
		if (Current->Get_State()==3)
		{
			CBlob_Spherical *BS;
			
			c.Put_x((Current->Get_Voxel().Get_Vertex(0).Get_x()+Current->Get_Voxel().Get_Vertex(6).Get_x())/2);
			c.Put_y((Current->Get_Voxel().Get_Vertex(0).Get_y()+Current->Get_Voxel().Get_Vertex(6).Get_y())/2);
			c.Put_z((Current->Get_Voxel().Get_Vertex(0).Get_z()+Current->Get_Voxel().Get_Vertex(6).Get_z())/2);
			//r2=(Voxel_Length+(Current->Get_Voxel().Get_Vertex(6).Get_x()-Current->Get_Voxel().Get_Vertex(0).Get_x())/2)/sqrt(1-Threshold);
			r2=(Voxel_Length+(Current->Get_Voxel().Get_Vertex(6).Get_x()-Current->Get_Voxel().Get_Vertex(0).Get_x())/2);
			p=1;
			BS=new CBlob_Spherical(c,r2,p,1,rose);
			BS->Put_Type_Reconstruction(3);
			Add_Blob(BS);
		}

		Current=Current->Next;
	}
	while (Current!=NULL);
	
        /*CPoint_3D v0(xmin,ymin,zmin),v1(xmax,ymin,zmin),v2(xmax,ymin,zmax),v3(xmin,ymin,zmax),
			  v4(xmin,ymax,zmin),v5(xmax,ymax,zmin),v6(xmax,ymax,zmax),v7(xmin,ymax,zmax);
	Bounded_Box.Put_Vertex(0,v0);
	Bounded_Box.Put_Vertex(1,v1);
	Bounded_Box.Put_Vertex(2,v2);
	Bounded_Box.Put_Vertex(3,v3);
	Bounded_Box.Put_Vertex(4,v4);
	Bounded_Box.Put_Vertex(5,v5);
	Bounded_Box.Put_Vertex(6,v6);
        Bounded_Box.Put_Vertex(7,v7);*/
}


void CList_BLob::addBoundaryBlobsFromVoxels(QVector<QVector3D> Cloud,CVoxel_Tab* VT)
{
    //return if no datas are set
    if( Cloud.size() == 0 || VT == NULL )   return;

	int i,j,k;
	int iv,jv,kv;
        double r,p=1;
        QVector3D lVp,lCenter;
	Dot_List *current,*current2;
        unsigned char Points_Done[Cloud.size()];
        memset(Points_Done, 0, Cloud.size()*sizeof(char));

        /*for (i=0;i<Cloud.size();i++)
		Points_Done[i]=0;
        */

	// Parcours des voxels contours
	Vox_List *CurrentV;
        CurrentV=VT->FSV;
	
	if (CurrentV!=NULL)
	{
		do
		{
                    // récupération des coordonnées dans le tableau de voxels
			i=CurrentV->Vox_Coord[0];j=CurrentV->Vox_Coord[1];k=CurrentV->Vox_Coord[2];
			
                        // Si le voxel à la position [i,j,k] à un de ces voisins qui est un voxel intérieur
                        if (VT->Is_In_Neighbourhood_State_Voxel(i,j,k,2)==true)
			{						
                                current=VT->Get_Voxel(i,j,k).First;
				do
				{
                                        // Si le point n'a pas été traité
					if (Points_Done[current->Dot_Num]==0)
                                        {
                                            int iv2,jv2,kv2;
                                                // On cherche les voxels inner et deep les plus proche
                                                VT->Find_Nearest_State_Voxel(iv,jv,kv,Cloud[current->Dot_Num],3);
                                                VT->Find_Nearest_State_Voxel(iv2,jv2,kv2,Cloud[current->Dot_Num],2);

						if ((iv==-1)&&(jv==-1)&&(kv==-1))
                                                        lVp=(VT->Get_Voxel(iv2,jv2,kv2).Get_Vertex(0)+VT->Get_Voxel(iv2,jv2,kv2).Get_Vertex(6))*0.5;
						else 
                                                        if (VT->Is_In_26_Neighbourhood(iv,jv,kv,iv2,jv2,kv2)==true)
                                                                lVp=(VT->Get_Voxel(iv,jv,kv).Get_Vertex(0)+VT->Get_Voxel(iv,jv,kv).Get_Vertex(6))*0.5;
							else
                                                                lVp=(VT->Get_Voxel(iv2,jv2,kv2).Get_Vertex(0)+VT->Get_Voxel(iv2,jv2,kv2).Get_Vertex(6))*0.5;
						
                                                lCenter=(lVp+Cloud[current->Dot_Num])*0.5;
                                                r=Distance3D(lCenter,Cloud[current->Dot_Num])/sqrt(1-sqrt(mThreshold));p=1;
						//r=Distance3D(c,Cloud.Get_Point(current->Dot_Num));p=1;						
						int l,m,n,imin,jmin,kmin,imax,jmax,kmax;

						if (i==0) imin=0; else imin=i-1;
						if (j==0) jmin=0; else jmin=j-1;
						if (k==0) kmin=0; else kmin=k-1;
                                                if (i==VT->Get_Dimx()-1) imax=VT->Get_Dimx()-1; else imax=i+1;
                                                if (j==VT->Get_Dimy()-1) jmax=VT->Get_Dimy()-1; else jmax=j+1;
                                                if (k==VT->Get_Dimz()-1) kmax=VT->Get_Dimz()-1; else kmax=k+1;

						for (l=imin;l<=imax;l++)
							for (m=jmin;m<=jmax;m++)
								for (n=kmin;n<=kmax;n++)
								{											
                                                                        if (VT->Get_State(l,m,n)==1)
									{
                                                                                current2=VT->Get_Voxel(l,m,n).First;
										do
										{
											if (current2!=current)
											{
                                                                                                if (Distance3D(lCenter,Cloud[current2->Dot_Num]) < r)
												{
                                                                                                        Find_New_Center(lCenter,Cloud[current->Dot_Num],Cloud[current2->Dot_Num]);
                                                                                                        r=Distance3D(lCenter,Cloud[current->Dot_Num])/sqrt(1-sqrt(mThreshold));p=1;
													//r=Distance3D(c,Cloud.Get_Point(current2->Dot_Num));p=1;
												}
											}
												current2=current2->Next;
										}
										while(current2!=NULL);
									}
								}
						Points_Done[current->Dot_Num]=1;
                                                // creating a new surface blob
						CBlob_Spherical *BS;
                                                p=1;
                                                BS=new CBlob_Spherical(lCenter,r,p,1,QColor(0,255,0));
						Add_Blob(BS);
                                                BS->setTypeReconstruction(1);
                                                BS->setThreshold(mThreshold);
						Points_Done[current->Dot_Num]=1;
					}
					current=current->Next;														
				}
				while(current!=NULL);
						
			}
			// Si le voxel contour n'a pas de voxels interieurs dans son 26 voisinage :
			else
			{
                                current=VT->Get_Voxel(i,j,k).First;
				do
				{
					if (Points_Done[current->Dot_Num]==0)
					{
                                                VT->Find_Nearest_State_Voxel(iv,jv,kv,Cloud[current->Dot_Num],2);
                                                lVp=(VT->Get_Voxel(i,j,k).Get_Vertex(0)+VT->Get_Voxel(i,j,k).Get_Vertex(6))*0.5;
                                                lCenter=(lVp+Cloud[current->Dot_Num])*0.5;
                                                r=Distance3D(lCenter,Cloud[current->Dot_Num])/sqrt(1-sqrt(mThreshold));p=1;
						//r=Distance3D(c,Cloud.Get_Point(current->Dot_Num));p=1;

						int l,m,n,imin,jmin,kmin,imax,jmax,kmax;

						if (i==0) imin=0; else imin=i-1;
						if (j==0) jmin=0; else jmin=j-1;
						if (k==0) kmin=0; else kmin=k-1;
                                                if (i==VT->Get_Dimx()-1) imax=VT->Get_Dimx()-1; else imax=i+1;
                                                if (j==VT->Get_Dimy()-1) jmax=VT->Get_Dimy()-1; else jmax=j+1;
                                                if (k==VT->Get_Dimz()-1) kmax=VT->Get_Dimz()-1; else kmax=k+1;

                                                for (l=imin;l<=imax;l++) {
                                                        for (m=jmin;m<=jmax;m++) {
								for (n=kmin;n<=kmax;n++)
								{
                                                                        if (VT->Get_State(l,m,n)==1)
									{						
                                                                                current2=VT->Get_Voxel(l,m,n).First;
										do
										{
											if (current2!=current)
											{
                                                                                                if (Distance3D(lCenter,Cloud[current2->Dot_Num]) < r)
												{
                                                                                                        Find_New_Center(lCenter,Cloud[current->Dot_Num],Cloud[current2->Dot_Num]);
                                                                                                        r=Distance3D(lCenter,Cloud[current->Dot_Num])/sqrt(1-sqrt(mThreshold));p=1;
												}
											}
											current2=current2->Next;
										}
										while(current2!=NULL);
									}
                                                                }
                                            }   }

						CBlob_Spherical *BS;
                                                BS=new CBlob_Spherical(lCenter,r,p,1,QColor(0,255,0));
                                                BS->setTypeReconstruction(1);
                                                BS->setThreshold(mThreshold);
						Add_Blob(BS);
						Points_Done[current->Dot_Num]=1;
					}
					current=current->Next;				
				}
				while(current!=NULL);
			}
			CurrentV=CurrentV->Next;
		}
		while (CurrentV!=NULL);
	}

        // TODO : check if this code is usefull
        /*QVector3D v0(mXMin,mYMin,mZMin),v1(mXMax,mYMin,mZMin),v2(mXMax,mYMin,mZMax),v3(mXMin,mYMin,mZMax),
                          v4(mXMin,mYMax,mZMin),v5(mXMax,mYMax,mZMin),v6(mXMax,mYMax,mZMax),v7(mXMin,mYMax,mZMax);
        mBoundedBox.Put_Vertex(0,v0);
        mBoundedBox.Put_Vertex(1,v1);
        mBoundedBox.Put_Vertex(2,v2);
        mBoundedBox.Put_Vertex(3,v3);
        mBoundedBox.Put_Vertex(4,v4);
        mBoundedBox.Put_Vertex(5,v5);
        mBoundedBox.Put_Vertex(6,v6);
        mBoundedBox.Put_Vertex(7,v7);*/

}

/*
void CList_BLob::Add_Boundary_Blobs(CTab_Point_3D Cloud,CVoxel_Tab VT)
{

	int i,j,iv,jv,kv;
	double r,p;
	CPoint_3D c;

	for (i=0;i<Cloud.Get_NBT_PTS();i++)
	{
		VT.Find_Nearest_State_Voxel(iv,jv,kv,Cloud.Get_Point(i),3);
		if ((iv==-1)&&(jv==-1)&&(kv==-1))
			VT.Find_Nearest_State_Voxel(iv,jv,kv,Cloud.Get_Point(i),2);
				
		c=(VT.Get_Voxel(iv,jv,kv).Get_Vertex(0)+VT.Get_Voxel(iv,jv,kv).Get_Vertex(6))*0.5;
		c=(c+Cloud.Get_Point(i))*0.5;
		r=Distance3D(c,Cloud.Get_Point(i));
	
		for (j=0;j<Cloud.Get_NBT_PTS();j++)
		{
			if (j!=i)
			{
				if (Distance3D(c,Cloud.Get_Point(j))<r)
				{
					Find_New_Center(c,Cloud.Get_Point(i),Cloud.Get_Point(j));
					r=Distance3D(c,Cloud.Get_Point(j));
				}

			}
		}
		r=r/sqrt(1-sqrt(Threshold));p=1;
		CBlob_Spherical *BS;
		BS=new CBlob_Spherical(c,r,p,1,vert);
		BS->Put_Type_Reconstruction(1);
		Add_Blob(BS);


	}


	CPoint_3D v0(xmin,ymin,zmin),v1(xmax,ymin,zmin),v2(xmax,ymin,zmax),v3(xmin,ymin,zmax),
			  v4(xmin,ymax,zmin),v5(xmax,ymax,zmin),v6(xmax,ymax,zmax),v7(xmin,ymax,zmax);
	Bounded_Box.Put_Vertex(0,v0);
	Bounded_Box.Put_Vertex(1,v1);
	Bounded_Box.Put_Vertex(2,v2);
	Bounded_Box.Put_Vertex(3,v3);
	Bounded_Box.Put_Vertex(4,v4);
	Bounded_Box.Put_Vertex(5,v5);
	Bounded_Box.Put_Vertex(6,v6);
	Bounded_Box.Put_Vertex(7,v7);
}

void CList_BLob::Read_File(char *fabsolu)
{
	FILE *fp;
	
	int i,t,type_blob;
	double x1,y1,z1,x2,y2,z2,r,p,coul[4];

	fp=fopen(fabsolu,"r");
	if (fp==NULL)
		printf("Impossible d'ouvrir le fichier");
	else
	{
		int NB;
		

		fscanf(fp,"%d",&NB);
		printf("Nombre de Blobs : %d\n\n",NB);
		i=0;
		while (i<NB)
		{
			fscanf(fp,"%d",&type_blob);
			if (type_blob==1)
			{
				CBlob_Spherical *BS;
				fscanf(fp,"%lf %lf %lf",&x1,&y1,&z1);
				CPoint_3D c(x1,y1,z1);
				fscanf(fp,"%lf",&r);
				fscanf(fp,"%lf",&p);
				fscanf(fp,"%d",&t);
				fscanf(fp,"%lf %lf %lf %lf",&coul[0],&coul[1],&coul[2],&coul[3]);
				
				BS=new CBlob_Spherical(c,r,p,t,coul);
				BS->Blob_Info();
				printf("\n");
				Add_Blob(BS);
			}
			else 
				if (type_blob==2)
				{
					CBlob_Cylindric *BC;
					fscanf(fp,"%lf %lf %lf",&x1,&y1,&z1);
					CPoint_3D a(x1,y1,z1);
					fscanf(fp,"%lf %lf %lf",&x2,&y2,&z2);
					CPoint_3D b(x2,y2,z2);
					fscanf(fp,"%lf",&r);
					fscanf(fp,"%lf",&p);
					fscanf(fp,"%d",&t);
					fscanf(fp,"%lf %lf %lf %lf",&coul[0],&coul[1],&coul[2],&coul[3]);
					
					BC=new CBlob_Cylindric(a,b,r,p,t,coul);
					BC->Blob_Info();
					printf("\n");
					Add_Blob(BC);
				}
			i++;
		}
		fscanf(fp,"%lf",&Threshold);
		CPoint_3D v0(xmin,ymin,zmin),v1(xmax,ymin,zmin),v2(xmax,ymin,zmax),v3(xmin,ymin,zmax),
				  v4(xmin,ymax,zmin),v5(xmax,ymax,zmin),v6(xmax,ymax,zmax),v7(xmin,ymax,zmax);
		Bounded_Box.Put_Vertex(0,v0);
		Bounded_Box.Put_Vertex(1,v1);
		Bounded_Box.Put_Vertex(2,v2);
		Bounded_Box.Put_Vertex(3,v3);
		Bounded_Box.Put_Vertex(4,v4);
		Bounded_Box.Put_Vertex(5,v5);
		Bounded_Box.Put_Vertex(6,v6);
		Bounded_Box.Put_Vertex(7,v7);
		printf("Seuil : %lf\n\n",Threshold);
		printf("Boite englobante :\n\n");
		Bounded_Box.Voxel_Info();
		printf("\n");
	}
}

void CList_BLob::Save_To_Povray(char *fabsolu)
{
	
	//FILE *fp;
	int i;
	if (Nb_Blobs>=1)
	{
		cout<<"ecriture dans : "<<fabsolu<<endl;
		//fp=fopen(fabsolu,"w+");
		ofstream fichier(fabsolu, ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

		//if (fp==NULL)
		if(fichier)
		{
			CPoint_3D c;

			c.Put_x((Bounded_Box.Get_Vertex(0).Get_x()+Bounded_Box.Get_Vertex(6).Get_x())/2);
			c.Put_y((Bounded_Box.Get_Vertex(0).Get_y()+Bounded_Box.Get_Vertex(6).Get_y())/2);
			c.Put_z((Bounded_Box.Get_Vertex(0).Get_z()+Bounded_Box.Get_Vertex(6).Get_z())/2);

			//fprintf(fp,"background {color red 1 green 1 blue 1}\n");
			fichier<<"background {color red 1 green 1 blue 1}"<<endl;
			//fprintf(fp,"camera {location <%lf, %lf, %lf> look_at <%lf, %lf, %lf> }\n",
				//0.0,0.0,0.0,
				//0.0,0.0,1.0);
			fichier<<"camera {location <"<<0.0<<", "<<0.0<<", "<<0.0<<"> look_at <"<<0.0<<", "<<0.0<<", "<<1.0<<"> }\n"<<endl;

				//tx,ty,tz,c.Get_x(),c.Get_y(),c.Get_z());
			//fprintf(fp,"light_source { <%lf, %lf, %lf> color red 1 green 1 blue 1 }\n",
			//	0.0,0.0,0.0);
			fichier<<"light_source { <"<<0.0<<", "<<0.0<<", "<<0.0<<"> color red 1 green 1 blue 1 }"<<endl;
				//tx,ty,tz);
			//fprintf(fp,"blob\n{\nthreshold %lf\n\n",Threshold);
			fichier<<"blob\n{\nthreshold "<<Threshold<<endl<<endl;
			
			i=1;
			CBlob_Linked *Current=First;
			for (i=1;i<=Nb_Blobs;i++)
			{
				switch(Current->Blob->Get_Type_Of_Blob()){
					case Spherique :
						//fprintf(fp,"sphere { < %lf, %lf, %lf >, %lf, %lf pigment { color red %lf green %lf blue %lf } rotate < 0.0, 0.0, %lf > rotate < 0.0, %lf, 0.0 >  rotate < %lf, 0.0, 0.0 >  translate < %lf, %lf, %lf >}\n",
						//	Current->Blob->Get_Center().Get_x(),Current->Blob->Get_Center().Get_y(),-Current->Blob->Get_Center().Get_z(),
						//	Current->Blob->Get_Ray(),Current->Blob->Get_Inf_Param(),
						//	Current->Blob->Get_Color()[0],Current->Blob->Get_Color()[1],Current->Blob->Get_Color()[2]
						//	,rz,ry,-rx
						//	,tx,ty,-tz);
						fichier<<"sphere { < "<<Current->Blob->Get_Center().Get_x()<<", "<<Current->Blob->Get_Center().Get_y()<<", "<<-Current->Blob->Get_Center().Get_z()<<"> "<<
							Current->Blob->Get_Ray()<<", "<<Current->Blob->Get_Inf_Param()<<" pigment { color red "<<Current->Blob->Get_Color()[0]<<" green "<<Current->Blob->Get_Color()[1]<<" blue "<< Current->Blob->Get_Color()[2]<<" } "<<
							" rotate < 0.0, 0.0, "<<rz<<" > rotate < 0.0, "<<ry<<", 0.0 >  rotate < "<<-rx<<", 0.0, 0.0 >  translate < "<<-tx<<", "<<ty<<", "<<-tz<<" >}"<<endl;
					break;
					case Cylindrique :
						fichier<<"cylinder { < "<<Current->Blob->Get_Segment_A().Get_x()<<", "<<Current->Blob->Get_Segment_A().Get_y()<<", "<<-Current->Blob->Get_Segment_A().Get_z()<<"> "<<
							" < "<<Current->Blob->Get_Segment_B().Get_x()<<", "<<Current->Blob->Get_Segment_B().Get_y()<<", "<<-Current->Blob->Get_Segment_B().Get_z()<<"> "<<
							Current->Blob->Get_Ray()<<", "<<Current->Blob->Get_Inf_Param()<<" pigment { color red "<<Current->Blob->Get_Color()[0]<<" green "<<Current->Blob->Get_Color()[1]<<" blue "<< Current->Blob->Get_Color()[2]<<" } "<<
							" rotate < 0.0, 0.0, "<<rz<<" > rotate < 0.0, "<<ry<<", 0.0 >  rotate < "<<-rx<<", 0.0, 0.0 >  translate < "<<-tx<<", "<<ty<<", "<<-tz<<" >}"<<endl;
					break;
				}
				Current=Current->Get_Next();
			}
			
//			fprintf(fp,"finish { ambient 0.2 diffuse 0.8 phong 1 }\n}\n");
//			fclose(fp);
			fichier<<"finish { ambient 0.2 diffuse 0.8 phong 1 }"<<endl<<"}"<<endl;
			fichier.flush();
			fichier.close();
			printf("fin d'écriture\n");
		}
		else{
			printf("Impossible d'ouvrir le fichier");
		}
	}
	else printf("\n Pas de blobs");
}

double CList_BLob::Compute_Val(CPoint_3D p)
{
	int i=1;
	double val=0,temp1=0,temp2=0;
	CBlob_Linked *Current=First;

	while (i<=Nb_Blobs)
	{
		temp1=Current->Blob->Compute_Dist(p);
		temp2=Current->Blob->Get_Ray()*Current->Blob->Get_Inf_Param();
		
		if (temp1<=temp2)
			val=val+Current->Blob->Compute_Val(temp1)*Current->Blob->Get_Inf_Param();		
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else
			break;
		i++;
	}
	return (val);
}

void CList_BLob::Compute_Color(CPoint_3D p,float c[4])
{
	int i=1,j;
	double temp1=0,temp2=0,temp3=0;
	float coltemp[4],temp4=0;
	
	CBlob_Linked *Current=First;

	for (j=0;j<4;j++)
	{
		coltemp[j]=0;
		c[j]=0;
	}
	
	while (i<=Nb_Blobs)
	{
		temp1=Current->Blob->Compute_Dist(p);
		temp2=Current->Blob->Get_Ray()*Current->Blob->Get_Inf_Param();
		
		if (temp1<=temp2)
		{
			temp3=Current->Blob->Compute_Val(temp1)*Current->Blob->Get_Inf_Param();
			for (j=0;j<4;j++)
				c[j]=c[j]+(float)temp3*Current->Blob->Get_Color()[j];
			temp4=temp4+(float)temp3;
		}
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else
			break;
		i++;
	}
	for (j=0;j<4;j++)
		c[j]=c[j]/temp4;
}

CPoint_3D CList_BLob::Compute_Gradient(CPoint_3D p)
{
	int i=1,j;
	double temp1=0,temp2=0,temp3=0,temp4=0;
	CPoint_3D gradtemp,grad;
	
	CBlob_Linked *Current=First;

		
	while (i<=Nb_Blobs)
	{
		temp1=Current->Blob->Compute_Dist(p);
		temp2=Current->Blob->Get_Ray()*Current->Blob->Get_Inf_Param();
		
		if (temp1<=temp2)
		{
			gradtemp=Current->Blob->Compute_Gradient(p);
			for (j=0;j<3;j++)
				grad=grad+gradtemp;
		}
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else
			break;
		i++;
	}
	
	return(grad);

}

void CList_BLob::Compute_Vertex(CVertex_3D &Vertex,double &Val)
{
	int i=1,j;
	double val=0,temp1=0,temp2=0,temp3=0,temp4=0;
	float coltemp[4]={0,0,0,0},c[4]={0,0,0,0};
	CBlob_Linked *Current=First;
	CPoint_3D gradtemp,grad;

	while (i<=Nb_Blobs) // Parcours des blobs
	{
		temp1=Current->Blob->Compute_Dist(Vertex.Get_Vertex());			// temp1 = distance (au carré) du Vertex au centre du blob
		temp2=Current->Blob->Get_Ray()*Current->Blob->Get_Inf_Param();	// temp2 = rayon d'influence
		
		if (temp1<=temp2)
		{
			temp3=Current->Blob->Compute_Val(temp1)*Current->Blob->Get_Inf_Param();
			val=val+temp3;		
			gradtemp=Current->Blob->Compute_Gradient(Vertex.Get_Vertex());
			grad=grad+gradtemp;
			for (j=0;j<4;j++)
				c[j]=c[j]+(float)temp3*Current->Blob->Get_Color()[j];
			temp4=temp4+(float)temp3;

		}
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else
			break;
		i++;

	}
	if (temp4!=0)
		for (j=0;j<4;j++)
			c[j]=c[j]/temp4;
	else
	{temp4=1;c[0]=1;c[1]=0;c[2]=0;c[3]=0;}

	Val=val;
	Vertex.Put_Color(c);
	Vertex.Put_Normal(grad);
}

void CList_BLob::Compute_Gradient_and_Color_on_Surface(CVertex_3D &Vertex)
{

	int i=1,j;
	double val=0,temp1=0,temp2=0,temp3=0,temp4=0;
	float coltemp[4]={0,0,0,0},c[4]={0,0,0,0};
	CBlob_Linked *Current=First;
	CPoint_3D gradtemp,grad;

	while (i<=Nb_Blobs) // Parcours des blobs
	{
		temp1=Current->Blob->Compute_Dist(Vertex.Get_Vertex());			// temp1 = distance (au carré) du Vertex au centre du blob
		temp2=Current->Blob->Get_Ray()*Current->Blob->Get_Inf_Param();	// temp2 = rayon d'influence
		
		if (temp1<=temp2)
		{
			gradtemp=Current->Blob->Compute_Gradient(Vertex.Get_Vertex());
			temp3=Current->Blob->Compute_Val(temp1);
			grad=grad+gradtemp;
			for (j=0;j<4;j++)
				c[j]=c[j]+(float)temp3*Current->Blob->Get_Color()[j];
			temp4=temp4+(float)temp3;

		}
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else
			break;
		i++;

	}
	if (temp4!=0)
		for (j=0;j<4;j++)
			c[j]=c[j]/temp4;
	else
	{temp4=1;c[0]=1;c[1]=0;c[2]=0;c[3]=0;}


	Vertex.Put_Color(c);
	Vertex.Put_Normal(grad);
	
}


void CList_BLob::Clear_Blobs_List(void)
{
	CBlob_Linked *Current;
	CPoint_3D O(0,0,0);
	int i;

	while (Last!=NULL && First!=NULL)
	{
		Current=Last;
		Last=Current->Get_Prec();
		delete Current;
	}

	xmin=ymin=zmin=xmax=ymax=zmax=0;

	Nb_Blobs=0;Threshold=0;
	First=Last=NULL;
	for (i=0;i<8;i++)
		Bounded_Box.Put_Vertex(i,O);
}

int CList_BLob::Get_Critical_Interval_Nb(void)
{
	return criticalIntervalIndex;
}

int CList_BLob::Get_Critical_Point_Nb(void)
{
	return criticalPointIndex;
}

void CList_BLob::Display_Critical_Intervals(void)
{
	for(int i=0;i<criticalIntervalIndex;i++)
	{
		printf("Intervalle critique num %d :\n",i);
		criticalIntervals[i].Display();
		printf("\n");
	}
}



void CList_BLob::Display_Critical_Points(void)
{
	for(int i=0; i<criticalPointIndex; i++)
	{
		printf("(%f, %f, %f)\n", criticalPoints[i].Get_x(), criticalPoints[i].Get_y(), criticalPoints[i].Get_z());
	}
}

char CList_BLob::Relative_Position(CInterval_3D inter)
{
	int i=0;
	char res=-1,temp;
	CBlob_Linked *current = First;
	
	while(i<Nb_Blobs)
	{
		temp=current->Blob->Relative_Position(inter);

		if (temp>res)
			res=temp;

		//if(current->Get_Next()!=NULL)
		current = current->Get_Next();
		
		if (res==1)
			i = Nb_Blobs+1;

		i++;
	}

	return res;
}

bool CList_BLob::IsEmpty(CInterval_3D inter, long double precision)
{
	int i=0;
	bool res = true;
	CBlob_Linked *current = First;

	while(i<Nb_Blobs)
	{
		if (current != NULL)
			res = current->Blob->IsEmpty(inter);

		if(current->Get_Next()!=NULL)
			current = current->Get_Next();
		else i = Nb_Blobs+1;

		if (!res)
			i = Nb_Blobs+1;

		i++;
	}
	return res;
}





CInterval CList_BLob::Compute_Val(CInterval inter[3])
{
	
	int i=0;
	CInterval val = CInterval(0.0, 0.0);
	CBlob_Linked *current = First;
	while(i<Nb_Blobs)
	{
		if (current != NULL)
			val = val + current->Blob->Compute_Val(inter);
		if(current->Get_Next()!=NULL)
			current = current->Get_Next();
		else i = Nb_Blobs+1;
		i++;
	}
	return val;
}



CInterval_3D CList_BLob::Compute_Gradient(CInterval_3D inter)
{
	
	CInterval_3D res;
	int i = 0;
	CBlob_Linked *current = First;
	//printf("Intervalle de travail :\n");
	//inter.Display();
	//printf("\n");
	while (i<Nb_Blobs)
	{
		//printf("Distance au blob de l'intervalle : \n");
		//inter.Distance(current->Blob->Get_Center()).Display();
		//printf("Distance carree au blob de l'intervalle : \n");
		//sqr(inter.Distance(current->Blob->Get_Center())).Display();
		//printf("Gradient de l'intervalle par rapport au blob : \n");
		//current->Blob->Compute_Gradient(inter).Display();
		res=res+current->Blob->Compute_Gradient(inter);
		
		if (current->Get_Next()!=NULL)
			current=current->Get_Next();
		else break;
		i++;
	}

	return res;
}



long double** CList_BLob::Compute_Hessien(CPoint_3D point)
{
	long double **res;
	int i = 0;
	int j, k;
	CBlob_Linked *current = First;

	res = new long double*[3];
	for (j=0; j<3; j++)
	{
		res[j] = new long double[3];
	}

	for(j=0; j<3; j++)
		for(k=0; k<3; k++)
			res[j][k] = 0;
	
	while (i<Nb_Blobs)
	{
		res[0][0]+=current->Blob->Compute_Hessien(point)[0][0];
		res[0][1]+=current->Blob->Compute_Hessien(point)[0][1];
		res[0][2]+=current->Blob->Compute_Hessien(point)[0][2];

		res[1][0]+=current->Blob->Compute_Hessien(point)[1][0];
		res[1][1]+=current->Blob->Compute_Hessien(point)[1][1];
		res[1][2]+=current->Blob->Compute_Hessien(point)[1][2];

		res[2][0]+=current->Blob->Compute_Hessien(point)[2][0];
		res[2][1]+=current->Blob->Compute_Hessien(point)[2][1];
		res[2][2]+=current->Blob->Compute_Hessien(point)[2][2];

		if (current->Get_Next()!=NULL)
			current=current->Get_Next();
		else break;
		i++;
	}

	return res;
}

void CList_BLob::Compute_Critical_Points(CTree_Interval_3D IT, long double precision)
{
	IT.Set_Root(xmin,xmax,ymin,ymax,zmin,zmax);
	printf("Intervalle de depart (boite englobante) :\n");
	IT.Get_Root()->Get_Node().Display();
	Compute_Critical_Points(static_cast<CNode_Interval_3D *> (IT.Get_Root()), precision);

	//Interval_To_Point();
	//Refine_Critical_Points(precision);

}

void CList_BLob::Compute_Critical_Points(CNode_Interval_3D * IntNode, long double precision)
{
	CInterval max;		// CInterval a tester et a subdiviser
	int coordMax;		// correspond a la coordonée de max (0,1ou2 pour x,y,ou z)
	long double midway;		// point milieu de max
	CInterval tempInf;	// CIntervalle max subdivisé contenant borne inférieure
	CInterval tempSup;	// CIntervalle max subdivisé contenant borne supérieure
	CInterval_3D Ltemp,Rtemp;
	long double lx,ly,lz;
	CPoint_3D zero(0,0,0);
	int Critical=0;
	CInterval_3D temp;
	char pos;

	pos=Relative_Position(IntNode->Get_Node());
//	printf("Position de l'intervalle : %d\n",pos);
	switch(pos)
	{
	case -1:
			
	break;
	
	case 0:
		// Recherche de la dimension la plus longue parmi les coordonnees de l'intervalle 3D
		lx = IntNode->Get_Node().Get_XLength();ly = IntNode->Get_Node().Get_YLength();lz = IntNode->Get_Node().Get_ZLength();
		if (lx>ly)
		{
			if (lx>lz)
			{
				max = IntNode->Get_Node().Get_X();coordMax=0;
			}
			else
			{
				max = IntNode->Get_Node().Get_Z();coordMax=2;
			}
		}
		else 
		{
			if (ly>lz)
			{
				max = IntNode->Get_Node().Get_Y();coordMax=1;
			}
			else
			{
				max = IntNode->Get_Node().Get_Z();coordMax=2;
			}
		}
		if(max.Get_Length()>=precision)
		{
			// subdivision de max
			midway = (max.Get_Bi()+max.Get_Bs()) / 2.0;
			midway = midway + (max.Get_Bs()-max.Get_Bi()) / 100.0;
			tempInf = CInterval(max.Get_Bi(), midway);
			tempSup = CInterval(midway, max.Get_Bs());
			
			//// création des CIntervalles 3D subdivisés
			Ltemp.Set(IntNode->Get_Node().Get_X(),IntNode->Get_Node().Get_Y(),IntNode->Get_Node().Get_Z());
			Rtemp.Set(IntNode->Get_Node().Get_X(),IntNode->Get_Node().Get_Y(),IntNode->Get_Node().Get_Z());

			switch(coordMax)
			{
				case 0 : Ltemp.Set_X(tempInf);Rtemp.Set_X(tempSup);	break;
				case 1 : Ltemp.Set_Y(tempInf);Rtemp.Set_Y(tempSup); break;
				case 2 : Ltemp.Set_Z(tempInf);Rtemp.Set_Z(tempSup); break;
			}
			IntNode->Alloc_Left(Ltemp);IntNode->Alloc_Right(Rtemp);		
			Compute_Critical_Points(static_cast<CNode_Interval_3D *> (IntNode->Get_Left()),  precision);
			Compute_Critical_Points(static_cast<CNode_Interval_3D *> (IntNode->Get_Right()), precision);
		}

	break;
	
	case 1:
		// Recherche de la dimension la plus longue parmi les coordonnees de l'intervalle 3D
		lx = IntNode->Get_Node().Get_XLength();ly = IntNode->Get_Node().Get_YLength();lz = IntNode->Get_Node().Get_ZLength();
		if (lx>ly)
		{
			if (lx>lz)
			{
				max = IntNode->Get_Node().Get_X();coordMax=0;
			}
			else
			{
				max = IntNode->Get_Node().Get_Z();coordMax=2;
			}
		}
		else 
		{
			if (ly>lz)
			{
				max = IntNode->Get_Node().Get_Y();coordMax=1;
			}
			else
			{
				max = IntNode->Get_Node().Get_Z();coordMax=2;
			}
		}

		// Calcul du gradient de l'intervalle
		temp=Compute_Gradient(IntNode->Get_Node());

		// Test si zero appartient à l'intervalle gradient 
		// => si oui l'intervalle de travail contient un point critique
		Critical=zero&temp;

		if(Critical==1)
		{
			// Test si la precision est atteinte
			if(max.Get_Length()<precision)
			{
				if (criticalIntervalIndex<MAX_POINT)
				{
					criticalIntervals[criticalIntervalIndex] = IntNode->Get_Node();
					criticalIntervalIndex++;
				}				
			}
			else
			{
				// subdivision de max
				midway = (max.Get_Bi()+max.Get_Bs()) / 2.0;
				midway = midway + (max.Get_Bs()-max.Get_Bi()) / 100.0;
				tempInf = CInterval(max.Get_Bi(), midway);
				tempSup = CInterval(midway, max.Get_Bs());
				
				//// création des CIntervalles 3D subdivisés
				Ltemp.Set(IntNode->Get_Node().Get_X(),IntNode->Get_Node().Get_Y(),IntNode->Get_Node().Get_Z());
				Rtemp.Set(IntNode->Get_Node().Get_X(),IntNode->Get_Node().Get_Y(),IntNode->Get_Node().Get_Z());

				switch(coordMax)
				{
					case 0 : Ltemp.Set_X(tempInf);Rtemp.Set_X(tempSup);	break;
					case 1 : Ltemp.Set_Y(tempInf);Rtemp.Set_Y(tempSup); break;
					case 2 : Ltemp.Set_Z(tempInf);Rtemp.Set_Z(tempSup); break;
				}
				IntNode->Alloc_Left(Ltemp);IntNode->Alloc_Right(Rtemp);		
				Compute_Critical_Points(static_cast<CNode_Interval_3D *> (IntNode->Get_Left()),  precision);
				Compute_Critical_Points(static_cast<CNode_Interval_3D *> (IntNode->Get_Right()), precision);
			}
		}
		
	break;

	}	
	
}

void CList_BLob::Interval_To_Point(void)
{
	int i;
	double x, y, z;

	criticalPointIndex = criticalIntervalIndex;
	for(i=0; i<criticalIntervalIndex; i++)
	{
		x = (criticalIntervals[i].Get_X().Get_Bi()+criticalIntervals[i].Get_X().Get_Bs())/2.0;
		y = (criticalIntervals[i].Get_Y().Get_Bi()+criticalIntervals[i].Get_Y().Get_Bs())/2.0;
		z = (criticalIntervals[i].Get_Z().Get_Bi()+criticalIntervals[i].Get_Z().Get_Bs())/2.0;

		criticalPoints[i] = CPoint_3D(x, y, z);
	}
}



void CList_BLob::Refine_Critical_Points(double precision)
{
	CPoint_3D refinedPoints[MAX_POINT];
	int refinedIndex = -1;
	//CInterval
	double tempx, tempy, tempz;
	bool found = false;
	int i, j;

	for(i=0; i<criticalPointIndex; i++)
	{
		for(j=0; j<refinedIndex; j++)
		{			
			tempx = criticalPoints[i].Get_x() - refinedPoints[j].Get_x();
			tempy = criticalPoints[i].Get_y() - refinedPoints[j].Get_y();
			tempz = criticalPoints[i].Get_z() - refinedPoints[j].Get_z();
			
			if(tempx<0)
				tempx = 0-tempx;
			if(tempy<0)
				tempy = 0-tempy;
			if(tempz<0)
				tempz = 0-tempz;
			
			if((tempx<=(100*precision))&&(tempy<=(100*precision))&&(tempz<=(100*precision)))
				found = true;
		}
		if(!found)
		{
			refinedIndex++;
			refinedPoints[refinedIndex].Put_x(criticalPoints[i].Get_x());
			refinedPoints[refinedIndex].Put_y(criticalPoints[i].Get_y());
			refinedPoints[refinedIndex].Put_z(criticalPoints[i].Get_z());
		}

		found = false;
	}

	criticalPointIndex = refinedIndex;
	for(i=0; i<refinedIndex; i++)
	{
		criticalPoints[i].Put_x(refinedPoints[i].Get_x());
		criticalPoints[i].Put_y(refinedPoints[i].Get_y());
		criticalPoints[i].Put_z(refinedPoints[i].Get_z());
	}
}
void CList_BLob::Fill_Gaps(double precision)
{
	//CInterval boundingBox[3];
	//double xmin, xmax;
	//double ymin, ymax;
	//double zmin, zmax;
	//CBlob_Linked *current = First;
	//CPoint_3D holes[MAX_POINT];
	//int holeIndex = -1;
	//bool found;
	//double dist;
	//CBlob *temp;
	//double tempRay;
	//int nbRay;
	//int i=0, j;

	//// recherche de la boite englobante (CIntervalle 3D)
	//xmin = current->Blob->Get_Center().Get_x();
	//ymin = current->Blob->Get_Center().Get_y();
	//zmin = current->Blob->Get_Center().Get_z();
	//xmax = xmin;
	//ymax = ymin;
	//zmax = zmin;

	//while (i<Nb_Blobs)
	//{
	//	if (current->Get_Next()!=NULL)
	//		current=current->Get_Next();
	//	else break;

	//	if (current->Blob->Get_Center().Get_x() < xmin)
	//		xmin = current->Blob->Get_Center().Get_x();

	//	if (current->Blob->Get_Center().Get_y() < ymin)
	//		ymin = current->Blob->Get_Center().Get_y();

	//	if (current->Blob->Get_Center().Get_z() < zmin)
	//		zmin = current->Blob->Get_Center().Get_z();

	//	if (current->Blob->Get_Center().Get_x() > xmax)
	//		xmax = current->Blob->Get_Center().Get_x();

	//	if (current->Blob->Get_Center().Get_y() > ymax)
	//		ymax = current->Blob->Get_Center().Get_y();

	//	if (current->Blob->Get_Center().Get_z() > zmax)
	//		zmax = current->Blob->Get_Center().Get_z();

	//	i++;
	//}
	//boundingBox[0] = CInterval(xmin-precision, xmax+precision);
	//boundingBox[1] = CInterval(ymin-precision, ymax+precision);
	//boundingBox[2] = CInterval(zmin-precision, zmax+precision);
	//
	//boundingBox[0].Display();
	//boundingBox[1].Display();
	//boundingBox[2].Display();
	//printf("\n\n");

	//// recherche des points critiques (!!!!! la methode ne renvoie rien a redefinir !!!!!)
	//Compute_Critical_Points(boundingBox, precision);

	//// parcours de la liste des points critiques et determination du type (!!! utilisation de la precision necessaire !!!)
	//for(i=0; i<criticalPointIndex; i++)
	//{
	//	current = First;
	//	j = 0;
	//	found = false;
	//	while((j<Nb_Blobs)||(!found))
	//	{
	//		dist = Distance3D(criticalPoints[i],current->Blob->Get_Center());
	//		if(dist<=(8*precision))
	//			found = true;

	//		if(current->Get_Next()!=NULL)
	//			current = current->Get_Next();
	//		else break;
	//		j++;
	//	}
	//	if(!found)
	//	{
	//		holeIndex++;
	//		holes[holeIndex] = criticalPoints[i];
	//		printf("Trou%d : (%f, %f, %f)\n", holeIndex, holes[holeIndex].Get_x(), holes[holeIndex].Get_y(), holes[holeIndex].Get_z());
	//		j = 0;
	//		current = First;
	//		tempRay = 0;
	//		nbRay = 0;
	//		while(j<Nb_Blobs)
	//		{
	//			dist = Distance3D(criticalPoints[i],current->Blob->Get_Center());
	//			if(dist<=current->Blob->Get_Ray())
	//			{
	//				tempRay+=current->Blob->Get_Ray();
	//				nbRay++;
	//			}
	//			if(current->Get_Next()!=NULL)
	//				current = current->Get_Next();
	//			else break;
	//			j++;
	//		}
	//		temp = new CBlob_Spherical(holes[holeIndex], tempRay/nbRay,1,1,rouge);
	//		Add_Blob(temp);
	//	}
	//}
	//printf("\n");

	//List_Info();

	// et des proches voisins pour chaque point => ajout d'un blob de taille correspondante
}

//******************************************************************************************************************
//---------------------------------- Fonction Réjoutées par Guillaume PERADON --------------------------------------
//---------------------------------- Pour l'utilisation de blobs cylindriques par l'application --------------------
//*****************************************************************************************************************

//void CList_BLob::Get_All_Types_Of_Blob(){
//	fonction utilisée pour le débogage, permet d'afficher les types de tous les blobs de la liste 
void CList_BLob::Get_All_Types_Of_Blob(){
	CBlob_Linked* current = First;
	for(int i=0;i<Nb_Blobs;i++){
		CPoint_3D centre = current->Blob->Get_Center();
		printf("blob i : centre %f %f, type %d\n",centre.Get_x(),centre.Get_y(),current->Get_Type_Of_Blob());
		current=current->Get_Next();
	}
}

//CBlob* CList_BLob::Nearest_Y_Blob(CPoint_3D* Point)
//	Retourne le blob le plus proche en Y d'un Point donné en Paramètre
//	On ne parcoure que les blobs sphériques dont les Coordonnées en Y
//	sont les mêmes que celles du point donné en paramètre.
CBlob* CList_BLob::Nearest_Y_Blob(CPoint_3D* Point,int type){ 
	int i=1;
	double distance=10000000000000000,dist=0.;

	CBlob_Linked *Current=First,*Temp=NULL;
	while (i<=Nb_Blobs)
	{
		if(Current->Blob->Get_Center().Get_y()!=Point->Get_y() && Current->Blob->Get_Type_Reconstruction()==type){
			if( (Current->Blob->Get_Center().Get_x()==Point->Get_x()) ){
				if( (Current->Blob->Get_Center().Get_z()==Point->Get_z()) &&(Current->Blob->Get_Type_Of_Blob()==Spherique)){
					if(type==2) puts("plop");
				dist=abs(Current->Blob->Get_Center().Get_y() - Point->Get_y());
				if (dist<distance && dist>0.)
				{
					distance=dist;
					Temp=Current;
				}
				}}
		}
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else break;
		i++;
	}
	return (Temp!=NULL)?Temp->Blob:NULL;
}

//CBlob* CList_BLob::Extremum_Y_Spherical_Blob(CPoint_3D* Point, int type)
//	Retourne les deux blobs extremum suivant l'axe Y, aux corrdonnés définis par le point Point placé en entrée
CPoint_3D* CList_BLob::Extremum_Y_Spherical_Blob(CPoint_3D* Point,int Type){
	CBlob_Linked *Current=First;
	CPoint_3D* Temp=new CPoint_3D[2];
	Temp[0]=*Point;Temp[1]=*Point;
	int i=1;
	double distance=1000000;
	while (i<=this->Get_Nb_Blobs())
	{
		if( Current->Blob->Get_Center().Get_x()==Point->Get_x() && Current->Blob->Get_Center().Get_z()==Point->Get_z() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==Type ){
			
			if(Current->Blob->Get_Center().Get_y()> Temp[1].Get_y())
			{
				Temp[1]=Current->Blob->Get_Center();
			}
			if(Current->Blob->Get_Center().Get_y()< Temp[0].Get_y()){
				Temp[0]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	return Temp;
}

//CBlob* CList_BLob::Extremum_Y_Spherical_Blob(CPoint_3D* Point, int type)
//	Retourne les deux blobs extremum suivant l'axe Y, aux coordonnés définis par le point Point placé en entrée
//	La distance est la distance maximum entre les blobs pour les faire fusionner
CPoint_3D* CList_BLob::Extremum_Y_Spherical_Blob(CPoint_3D* Point,int type,float distance){
	//printf("\non entre dans extremum.... Point [%f,%f,%f]",Point->Get_x(),Point->Get_y(),Point->Get_z());
	CBlob_Linked *Current=First;
	bool tmp_modifie=false;
	CPoint_3D* Temp=new CPoint_3D[2];
	Temp[0]=*Point;
	int i=1;
	//On parcours pour trouver le blob du type voulu le plus bas
	while (i<=this->Get_Nb_Blobs())
	{
		if(Current->Blob->Get_Center().Get_x()==Point->Get_x() && Current->Blob->Get_Center().Get_z()==Point->Get_z() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			if(Current->Blob->Get_Center().Get_y()< Temp[0].Get_y()){
				Temp[0]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	i=1;
	Current=First;
	Temp[1]=Temp[0];
	//parcours afin de trouver le blob le plus haut possible à une distance maximal qui vaut dist ( afin de ne pas sortir du nuage de point en cas de formes bizarres ( trouées par exemple )
	while (i<=this->Get_Nb_Blobs())
	{
		if(Current->Blob->Get_Center().Get_x()==Point->Get_x() && Current->Blob->Get_Center().Get_z()==Point->Get_z() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			if(Current->Blob->Get_Center().Get_y()<=Temp[1].Get_y()+(distance*1.1)){
				Temp[1]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	return Temp;
}

//CBlob* CList_BLob::Extremum_X_Spherical_Blob
//	Retourne les deux blobs extremum suivant l'axe X, aux corrdonnés définis par le point Point placé en entrée
CPoint_3D* CList_BLob::Extremum_X_Spherical_Blob(CPoint_3D* Point,int type){
	CBlob_Linked *Current=First;
	CPoint_3D* Temp=new CPoint_3D[2];
	Temp[0]=*Point;Temp[1]=*Point;
	int i=1;
	double distance=1000000;
	while (i<=this->Get_Nb_Blobs())
	{
		if(Current->Blob->Get_Center().Get_y()==Point->Get_y() && Current->Blob->Get_Center().Get_z()==Point->Get_z() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			if(Current->Blob->Get_Center().Get_x()> Temp[1].Get_x())
			{
				Temp[1]=Current->Blob->Get_Center();
			}
			if(Current->Blob->Get_Center().Get_x()< Temp[0].Get_x()){
				Temp[0]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	return Temp;
}

//CBlob* CList_BLob::Extremum_X_Spherical_Blob
//	Retourne les deux blobs extremum suivant l'axe X, aux corrdonnés définis par le point Point placé en entrée
//	Le paramètre distance sert à spécifier la distance maximum pour faire fusionner les blobs
CPoint_3D* CList_BLob::Extremum_X_Spherical_Blob(CPoint_3D* Point,int type,float distance){
	//printf("\non entre dans extremum.... Point [%f,%f,%f]",Point->Get_x(),Point->Get_y(),Point->Get_z());
	CBlob_Linked *Current=First;
	bool tmp_modifie=false;
	CPoint_3D* Temp=new CPoint_3D[2];
	Temp[0]=*Point;
	int i=1;
	//On parcours pour trouver le blob du type voulu le plus à gauche
	while (i<=this->Get_Nb_Blobs())
	{
		if(Current->Blob->Get_Center().Get_y()==Point->Get_y() && Current->Blob->Get_Center().Get_z()==Point->Get_z() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			if(Current->Blob->Get_Center().Get_x()< Temp[0].Get_x()){
				Temp[0]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	i=1;
	Current=First;
	Temp[1]=Temp[0];
	//parcours afin de trouver le blob le plus à droite possible à une distance maximal qui vaut dist ( afin de ne pas sortir du nuage de point en cas de formes bizarres ( trouées par exemple )
	while (i<=this->Get_Nb_Blobs())
	{
		if(Current->Blob->Get_Center().Get_y()==Point->Get_y() && Current->Blob->Get_Center().Get_z()==Point->Get_z() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			if(Current->Blob->Get_Center().Get_x()<=Temp[1].Get_x()+(distance*1.1)){
				Temp[1]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	return Temp;
}
//CBlob* CList_BLob::Extremum_Z_Spherical_Blob
//	Retourne les deux blobs extremum suivant l'axe Z, aux corrdonnés définis par le point Point placé en entrée
CPoint_3D* CList_BLob::Extremum_Z_Spherical_Blob(CPoint_3D* Point,int type){
	CBlob_Linked *Current=First;
	CPoint_3D* Temp=new CPoint_3D[2];
	Temp[0]=*Point;Temp[1]=*Point;
	int i=1;
	double distance=1000000;
	while (i)
	{
		if(Current->Blob->Get_Center().Get_x()==Point->Get_x() && Current->Blob->Get_Center().Get_y()==Point->Get_y() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			
			if(Current->Blob->Get_Center().Get_z()> Temp[1].Get_z())
			{
				Temp[1]=Current->Blob->Get_Center();
			}
			if(Current->Blob->Get_Center().Get_z()< Temp[0].Get_z()){
				Temp[0]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	return Temp;
}

//CBlob* CList_BLob::Extremum_Z_Spherical_Blob
//	Retourne les deux blobs extremum suivant l'axe X, aux corrdonnés définis par le point Point placé en entrée
//	Le paramètre distance sert à spécifier la distance maximum pour faire fusionner les blobs
CPoint_3D* CList_BLob::Extremum_Z_Spherical_Blob(CPoint_3D* Point,int type,float distance){
	CBlob_Linked *Current=First;
	bool tmp_modifie=false;
	CPoint_3D* Temp=new CPoint_3D[2];
	Temp[0]=*Point;
	int i=1;
	//On parcours pour trouver le blob du type voulu le plus proche
	while (i<=this->Get_Nb_Blobs())
	{
		if(Current->Blob->Get_Center().Get_x()==Point->Get_x() && Current->Blob->Get_Center().Get_y()==Point->Get_y() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			if(Current->Blob->Get_Center().Get_z()< Temp[0].Get_z()){
				Temp[0]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	i=1;
	Current=First;
	Temp[1]=Temp[0];
	//parcours afin de trouver le blob le plus loin possible à une distance maximal qui vaut dist ( afin de ne pas sortir du nuage de point en cas de formes bizarres ( trouées par exemple )
	while (i<=this->Get_Nb_Blobs())
	{
		if(Current->Blob->Get_Center().Get_x()==Point->Get_x() && Current->Blob->Get_Center().Get_y()==Point->Get_y() && Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
			if(Current->Blob->Get_Center().Get_z()<=Temp[1].Get_z()+(distance*1.1)){
				Temp[1]=Current->Blob->Get_Center();
			}
		}
		if (Current->Get_Next()!=NULL){
			Current=Current->Get_Next();
		}
		else {
			break;
		}
		i++;
	}
	return Temp;
}

//CBlob* CList_BLob::Spherical_To_Cylindric
//	fonction de fusion des blobs sphériques en blobs cylindriques le long des axes X,Y,Z
void CList_BLob::Spherical_To_Cylindric(int type){
	printf("nombre de Blobs avant l'éxécution du Sperical2cylindric : %d\n",Nb_Blobs);
	CBlob_Linked *Current = First;
	int i=1,cpt=0;
	double* couleur;double dist=0,min_dist=10000000;
	switch(type){
		case 1:couleur = vert;break;
		case 2:couleur = bleu;break;
		case 3:couleur = rose;break;
		default:couleur = rouge;break;
	}

	//si les blobs ne sont pas de type profond
	if(type!=3){
		float distx=0.,disty=0.,distz=0.;
		while(i<=Nb_Blobs){
			if(Current->Blob->Get_Type_Of_Blob()==Spherique && Current->Blob->Get_Type_Reconstruction()==type){
				cpt++;
			}
			if(Current->Get_Next()!=NULL){
				Current=Current->Get_Next();
				i++;
			}
			else
				break;
		}
		Current=First;
		while(Current->Blob->Get_Type_Reconstruction()!=type && Current->Get_Next()!=NULL) {Current=Current->Get_Next();}
		CBlob* point_temp=Nearest_Y_Blob(&Current->Blob->Get_Center(),type);
		if(point_temp!=NULL){
			dist = absolut(Current->Blob->Get_Center().Get_y()-point_temp->Get_Center().Get_y());
			if(dist==0.){
				dist = absolut(Current->Blob->Get_Center().Get_x()-point_temp->Get_Center().Get_x());
			}
			if(dist==0.){
				dist = absolut(Current->Blob->Get_Center().Get_z()-point_temp->Get_Center().Get_z());
			}
			if( (min_dist > dist && dist!=0.) ||min_dist==0.){
				min_dist=dist;
			}
		}
		else{
			min_dist=0;
		}
	}

	i=1;Current=First;
	while(i<=Nb_Blobs){
		if(Current->Blob->Get_Type_Reconstruction()==type && Current->Blob->Get_Type_Of_Blob()==Spherique){
			//On récupère les points Max et Min
			CPoint_3D* tab=NULL,*tab1=NULL,*tab2=NULL;int choix = 0;float t;
			switch(type){
				case Profond : {//Cas des blobs profonds
					float dist=0.;choix=0.;
					tab = Extremum_Y_Spherical_Blob(&Current->Blob->Get_Center(),type);
					if(tab!=NULL){
						dist = Manhattan_Distance3D(tab[0],tab[1]);
					}
					tab1 = Extremum_X_Spherical_Blob(&Current->Blob->Get_Center(),type);
					if(tab1!=NULL){
						t=Manhattan_Distance3D(tab1[0],tab1[1]);
						if(dist < t){
							choix=1;
							dist=t;
						}
					}
					tab2 =  Extremum_Z_Spherical_Blob(&Current->Blob->Get_Center(),type);
					if(tab1!=NULL){
						t=Manhattan_Distance3D(tab1[0],tab1[1]);
						if(dist<t){
							choix=2;
							dist=t;
						}
					}
					switch(choix){
						case 1 : tab=tab1;break;
						case 2 : tab=tab2;break;
						default : break;
					}
					break;
				}
				case Interieur:{
					if(min_dist!=0){
						choix=0;
						tab = Extremum_Y_Spherical_Blob(&Current->Blob->Get_Center(),type,min_dist);
						dist = Manhattan_Distance3D(tab[0],tab[1]);
						tab1 =Extremum_X_Spherical_Blob(&Current->Blob->Get_Center(),type,min_dist);
						if(tab1!=NULL){
							t=Manhattan_Distance3D(tab1[0],tab1[1]);
							if(t>dist){
								choix=1;
								dist=t;
							}
						}
						tab2 =Extremum_Z_Spherical_Blob(&Current->Blob->Get_Center(),type,min_dist);
						if(tab2!=NULL){
							t=Manhattan_Distance3D(tab2[0],tab2[1]);
							if(t>dist){
								choix=2;
								dist=t;
							}
						}
						switch(choix){
							case 1 : tab=tab1;break;
							case 2 : tab=tab2;break;
							default : break;
						}
					}
					break;
				}
				case Surface : {
					CBlob_Linked* Blob_proche = Nearest_Dif_LinkedBlob(Current->Blob->Get_Center());
					if(Blob_proche->Blob->Get_Ray()==Current->Blob->Get_Ray() && Blob_proche->Blob->Get_Inf_Param() ==Current->Blob->Get_Inf_Param() && Blob_proche->Blob->Get_Type_Of_Blob()==type)
					{
						CBlob_Cylindric* nouveau = new CBlob_Cylindric(Current->Blob->Get_Center(),Blob_proche->Blob->Get_Center(),Current->Blob->Get_Ray(),Current->Blob->Get_Inf_Param(),2,Current->Blob->Get_Color());
						nouveau->Put_Type_Reconstruction(Surface);
						this->Dealloc(Blob_proche);
						this->Dealloc(Current);
						//Current redevient le premier élément de la liste afin d'éviter des exceptions de pointeur
						//sur des éléments que nous avons supprimés
						Current=First;
						this->Add_Blob(nouveau);
					}
				}
				break;
			}
			if(tab!=NULL && (tab[0].Get_x()!=tab[1].Get_x() || tab[0].Get_y()!=tab[1].Get_y() || tab[0].Get_z()!=tab[1].Get_z())){
				CBlob_Cylindric* b1= new CBlob_Cylindric(tab[0] ,tab[1], Current->Blob->Get_Ray(),Current->Blob->Get_Inf_Param() , 1., Current->Blob->Get_Color());
				b1->Put_Type_Reconstruction(type);
				switch(choix){
					case 0:Delete_All_BetweenY(tab,type,Spherique);break;
					case 1:Delete_All_BetweenX(tab,type,Spherique);break;
					case 2:Delete_All_BetweenZ(tab,type,Spherique);break;
				}
				this->Add_Blob(b1);
				Current=First;
				i=1;
			}
		}
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		i++;
	}
	printf("nombre de blobs après l'execution = %d\n",this->Get_Nb_Blobs());
}


void CList_BLob::Dealloc(CBlob_Linked *Current){
	int i=0;
	if(Current==First)
	{
		First=First->Get_Next();
		delete(Current);
		Nb_Blobs-=1;
	}
	else
	{
		if(Current==Last)
		{
			Last = Current->Get_Prec();
			Last->Set_Next(NULL);
			delete(Current);
			Nb_Blobs-=1;
		}
		else
		{
			Current->Get_Prec()->Set_Next(Current->Get_Next());
			Current->Get_Next()->Set_Prec(Current->Get_Prec());
			delete(Current);
			Nb_Blobs-=1;
		}
	}
}

int CList_BLob:: Delete_All_BetweenY(CPoint_3D* tab,int type,int type_of_blob){
	CBlob_Linked* courant=First,*tmp;
	int i=0,cpt=0;
	printf("entre les points [%f,%f,%f] et [%f,%f,%f] :\n",tab[0].Get_x(),tab[0].Get_y(),tab[0].Get_z(),tab[1].Get_x(),tab[1].Get_y(),tab[1].Get_z());
	while(i<=Nb_Blobs){
		tmp=courant->clone();
		if(courant->Blob->Get_Center().Get_x()==tab[0].Get_x() 
			&& courant->Blob->Get_Center().Get_z()==tab[0].Get_z()
			&& courant->Blob->Get_Type_Reconstruction()==type 
			&& courant->Blob->Get_Type_Of_Blob()==type_of_blob
			&& courant->Blob->Get_Center().Get_y() >= tab[0].Get_y()
			&& courant->Blob->Get_Center().Get_y() <= tab[1].Get_y()
			)
		{
			printf("\t suppression du blob [%f,%f,%f] indice %d\n",courant->Blob->Get_Center().Get_x(),courant->Blob->Get_Center().Get_y(),courant->Blob->Get_Center().Get_z(),i);
			Dealloc(courant);
			cpt++;
			i--;
		}
		if(tmp->Get_Next()==NULL)
			break;
		else{
			courant=tmp->Get_Next();
			delete tmp;
			i++;
		}
	}
	delete tmp;
	return cpt;
}
int CList_BLob:: Delete_All_BetweenX(CPoint_3D* tab,int type,int type_of_blob){
	CBlob_Linked* courant=First,*tmp;
	int i=0,cpt=0;
	printf("entre les points [%f,%f,%f] et [%f,%f,%f] :\n",tab[0].Get_x(),tab[0].Get_y(),tab[0].Get_z(),tab[1].Get_x(),tab[1].Get_y(),tab[1].Get_z());
	while(i<=Nb_Blobs){
		tmp=courant->clone();
		if(courant->Blob->Get_Center().Get_y()==tab[0].Get_y() 
			&& courant->Blob->Get_Center().Get_z()==tab[0].Get_z()
			&& courant->Blob->Get_Type_Reconstruction()==type 
			&& courant->Blob->Get_Type_Of_Blob()==type_of_blob
			&& courant->Blob->Get_Center().Get_x() >= tab[0].Get_x()
			&& courant->Blob->Get_Center().Get_x() <= tab[1].Get_x()
			)
		{
			printf("\t suppression du blob [%f,%f,%f] indice %d\n",courant->Blob->Get_Center().Get_x(),courant->Blob->Get_Center().Get_y(),courant->Blob->Get_Center().Get_z(),i);
			Dealloc(courant);
			cpt++;
			i--;
		}
		if(tmp->Get_Next()==NULL)
			break;
		else{
			courant=tmp->Get_Next();
			delete tmp;
			i++;
		}
	}
	delete tmp;
	return cpt;
}
int CList_BLob:: Delete_All_BetweenZ(CPoint_3D* tab,int type,int type_of_blob){
	CBlob_Linked* courant=First,*tmp;
	int i=0,cpt=0;
	printf("entre les points [%f,%f,%f] et [%f,%f,%f] :\n",tab[0].Get_x(),tab[0].Get_y(),tab[0].Get_z(),tab[1].Get_x(),tab[1].Get_y(),tab[1].Get_z());
	while(i<=Nb_Blobs){
		tmp=courant->clone();
		if(courant->Blob->Get_Center().Get_y()==tab[0].Get_y() 
			&& courant->Blob->Get_Center().Get_x()==tab[0].Get_x()
			&& courant->Blob->Get_Type_Reconstruction()==type 
			&& courant->Blob->Get_Type_Of_Blob()==type_of_blob
			&& courant->Blob->Get_Center().Get_z() >= tab[0].Get_z()
			&& courant->Blob->Get_Center().Get_z() <= tab[1].Get_z()
			)
		{
			printf("\t suppression du blob [%f,%f,%f] indice %d\n",courant->Blob->Get_Center().Get_x(),courant->Blob->Get_Center().Get_y(),courant->Blob->Get_Center().Get_z(),i);
			Dealloc(courant);
			cpt++;
			i--;
		}
		if(tmp->Get_Next()==NULL)
			break;
		else{
			courant=tmp->Get_Next();
			delete tmp;
			i++;
		}
	}
	delete tmp;
	return cpt;
}
CBlob_Linked* CList_BLob::Nearest_Dif_LinkedBlob(CPoint_3D p)
{
	int i=1;
	double distance=1000000,dist;
	CBlob_Linked *Current=First,*Temp;
	while (i<=Nb_Blobs)
	{
		dist=Current->Blob->Compute_Dist(p);
		if (dist<distance && dist!=0.)
		{
			distance=dist;Temp=Current;
		}
		if (Current->Get_Next()!=NULL)
			Current=Current->Get_Next();
		else break;
		i++;
	}
	return Temp;
}
* */


