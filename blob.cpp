#include "blob.h"
#include <GL/freeglut.h>
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
        qWarning()<<"Couleur :"<<mColor;
}

//calcul de la distance par rapport au 
double CBlob_Spherical::computeDistance(const QVector3D& pt) const
{
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
double CBlob_Spherical::computeVal(const QVector3D& pPoint) const
{	
        double lVal;
        double lDistance=computeDistance(pPoint);
        switch (mTypeFunction)
	{
		case 1 :
		{
                        lVal=Muraki(lDistance,mRadius);
			break;
		}

		case 2 :
		{
                        lVal=Wywill(lDistance,mRadius);
                        break;
		}

		default:
		{
			printf("Mauvais type de fonction pour le calcul !\n");
                        lVal=0.0;
			break;
		}
	}
        return (lVal);
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
 
//permet de savoir si un point est à l'interieur du blob
bool CBlob_Spherical::isInside(const QVector3D& pPoint) const
{
        return ((Distance3D(mCenter,pPoint)<=mRadius)?true:false);
}

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
        /** New code */
        int lCount = 0;
        qWarning()<<"Affichage de "<<mBlobList.size()<<" blobs :";
        QVectorIterator<CBlob*> lIte(mBlobList);
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
    /** New Code */
    CBlob* lClosestBlob = mBlobList.first();
    double lDist = 1000000000;
    /*QVectorIterator<CBlob*> lIte(mBlobList);
    while(lIte.hasNext()) {
        CBlob* lTemp = lIte.next();
        double lTempDist = lTemp->computeDistance(p);
        if( lTempDist < lDist) {
            lClosestBlob = lTemp;
            lDist = lTempDist;
        }
    }*/
    double lTempDist = 0.0;
    for(int i=0;i<mBlobList.size();++i)
    {
        CBlob* lTemp = mBlobList.at(i);
        lTempDist=lTemp->computeDistance(p);
        if(lTempDist<lDist)
        {
            lClosestBlob = lTemp;
            lDist = lTempDist;
        }
    }
    return lClosestBlob;
}


void CList_BLob::drawBlobsThreshold(int pBlobType) const
{
    QVectorIterator<CBlob*> lIte(mBlobList);
    while(lIte.hasNext()) {
        CBlob* lTemp = lIte.next();
        if( lTemp->getTypeReconstruction() == pBlobType ) {
            lTemp->drawThreshold();
        }
    }

   /* for(int i=0;i<mBlobList.size();++i)
    {
        const CBlob* lTemp = mBlobList.at(i);
        if( lTemp->getTypeReconstruction()==pBlobType )
        {
            lTemp->drawThreshold();
        }
    }*/
}

void CList_BLob::drawBlobsInfluence(int pBlobType) const
{
    //QListIterator<CBlob*> lIte(mBlobList);
    QVectorIterator<CBlob*> lIte(mBlobList);
    while(lIte.hasNext()) {
        CBlob* lTemp = lIte.next();
        if( lTemp->getTypeReconstruction() == pBlobType ) {
            lTemp->drawInfluence();
        }
    }
    /*for(int i=0;i<mBlobList.size();++i)
    {
        const CBlob* lTemp = mBlobList.at(i);
        if( lTemp->getTypeReconstruction()==pBlobType )
        {
            lTemp->drawInfluence();
        }
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
}

double CList_BLob::Compute_Val(const QVector3D& pPoint) const
{
    /**
      * New code
      */
    double lValue = 0; double lTemp1=0.0, lTemp2=0.0, dInfParam=0.0;
   // QVectorIterator<CBlob*> lIte(mBlobList);
    /*while(lIte.hasNext()) {
        const CBlob* lTemp = lIte.next();
        dInfParam=lTemp->getInfParam();

        lTemp1=lTemp->computeDistance(pPoint);
        lTemp2=lTemp->getRadius()*dInfParam;

        if (lTemp1<=lTemp2)
                lValue=lValue+lTemp->computeVal(lTemp1)*dInfParam;
    }*/
    for(int i=0;i<mBlobList.size();++i)
    {
        const CBlob* lTemp = mBlobList.at(i);
        dInfParam=lTemp->getInfParam();

        lTemp1=lTemp->computeDistance(pPoint);
        lTemp2=lTemp->getRadius()*dInfParam;

        if (lTemp1<=lTemp2)
                lValue=lValue+lTemp->computeVal(lTemp1)*dInfParam;
    }
    return lValue;
}
