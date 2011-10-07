/*
 * Renderer.cpp
 *
 *  Created on: 5 déc. 2010
 *      Author: guillaume
 */

#include "renderer.h"
#include <QTime>

GLfloat gLight0[3][4] = { {0.1f, 0.1f, 0.3f, 1.0f},
                             {0.5f, 0.5f, 1.0f, 1.0f},
                             {3.0f, 3.0f, 0.0f, 0.0f} };

GLfloat gLight1[3][4] = { {0.1f, 0.1f, 0.3f, 1.0f},
                             {1.0f, 0.5f, 0.5f, 1.0f},
                             {-4.0f, -4.0f, 4.0f, 0.0f} };

Renderer::Renderer( QWidget* pParent) {
	// TODO Auto-generated constructor stub
        mThingsToDraw = DRAW_CLOUDS;
	QObject::connect( &mTimer, SIGNAL(timeout()), this, SLOT(updateGL()));

	this->setParent( pParent );
	mCloud = NULL;

	// cam Parameters
	mCam << 0.0f<<0.0f<<6.0f;
	mCam << 0.0f<<0.0f<<0.0f;
	mCam << 0.0f<<1.0f<<0.0f;

	// Rotation parameters
	mRot<<0<<0;

	mTimer.start( 24 );

        this->setMouseTracking(true);
}

Renderer::~Renderer() {
	// TODO Auto-generated destructor stub
	delete(mCloud);
	mCloud = NULL;
}


void Renderer::openCloudFile(QString& pPath) {
	if (mCloud != NULL ) {
		delete(mCloud);
		mCloud = NULL;
	}
	mCloud  = new Cloud( pPath );
	mVT.Clear_Voxel_Tab();
}

void Renderer::paintGL() {

        QTime lTime;
        lTime.start();

	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	 glMatrixMode( GL_PROJECTION );
	 glLoadIdentity();
         gluPerspective( 45, (float)this->width()/(float)this->height(), 0.0001, 999.0 );

	 glMatrixMode( GL_MODELVIEW );
	 glLoadIdentity();
	 gluLookAt(	mCam[0], mCam[1], mCam[2],
				mCam[3], mCam[4], mCam[5],
                                mCam[6], mCam[7], mCam[8]);

	 glRotatef( mRot[0], 0.0f, 0.0f, 1.0f );
	 glRotatef( mRot[1], 1.0f, 0.0f, 0.0f );
	 glPointSize(2);

         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	 // Draw voxels
	 if( mThingsToDraw & DRAW_OCTREE_OUT) {
		 mVT.Draw_State( 0 );
	 }
	 if( mThingsToDraw & DRAW_OCTREE_INOUT ) {
		 mVT.Draw_State( 1 );
	 }
	 if( mThingsToDraw & DRAW_OCTREE_INNER ) {
		 mVT.Draw_State( 2 );
	 }
         if( mThingsToDraw & DRAW_OCTREE_DEEP ) {
		 mVT.Draw_State( 3 );
	 }

         if( mThingsToDraw & DRAW_BLOBS_EFF_DEEP ) {
             mListBlobs.drawBlobsThreshold( 3 );
         }
         if( mThingsToDraw & DRAW_BLOBS_EFF_IN ) {
             mListBlobs.drawBlobsThreshold( 2 );
         }
         if( mThingsToDraw & DRAW_BLOBS_EFF_INOUT ) {
             mListBlobs.drawBlobsThreshold( 1 );
         }

         if( mThingsToDraw & DRAW_BLOBS_THR_DEEP ) {
             mListBlobs.drawBlobsInfluence( 3 );
         }
         if( mThingsToDraw & DRAW_BLOBS_THR_IN ) {
             mListBlobs.drawBlobsInfluence( 2 );
         }
         if( mThingsToDraw & DRAW_BLOBS_THR_INOUT ) {
             mListBlobs.drawBlobsInfluence( 1 );
         }

         // Draw the Cloud
         if(mCloud != NULL && (mThingsToDraw & DRAW_CLOUDS ) ) {
                 mCloud->Draw();
         }
}


void Renderer::initializeGL() {
    glClearColor(0, 0, 0, 0);
    resizeGL( parentWidget()->size() );
    /*glDisable(GL_TEXTURE_2D);
    //glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);*/

    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, gLight0[0] );
    glLightfv(GL_LIGHT0, GL_DIFFUSE, gLight0[1] );
    glLightfv(GL_LIGHT0, GL_POSITION, gLight0[2] );

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, gLight1[0] );
    glLightfv(GL_LIGHT1, GL_DIFFUSE, gLight1[1] );
    glLightfv(GL_LIGHT1, GL_POSITION, gLight1[2] );

}

void Renderer::resizeGL( int width, int height ){
	this->resize(width, height);
}

void Renderer::resizeGL( QSize pSize ){
	this->resize(pSize);
}

Cloud* Renderer::cloud(){
	return mCloud;
}

COctree* Renderer::octree() {
    return &mOctree;
}

void Renderer::setThingstoDraw(int pValue){
    mThingsToDraw ^= pValue;
}

CVoxel_Tab* Renderer::voxelTab() {
	return &mVT;
}

void Renderer::mouseMoveEvent( QMouseEvent* pEvent) {
	pEvent->accept();
	QPointF lTemp(0,0);
	switch(mButtonPressed) {
		case Qt::LeftButton : {
			lTemp = (mMousePos - pEvent->posF())/100.0;
			mCam[3] += (float)lTemp.x();
			mCam[4] -= (float)lTemp.y();

			mMousePos = pEvent->pos();
		}	break;
		case Qt::RightButton  : {
			lTemp = (mMousePos - pEvent->posF())/10.0;
			mRot[0] -= (float)lTemp.x();
			mRot[1] += (float)lTemp.y();
		} break;
	}
}

void Renderer::mousePressEvent( QMouseEvent* pEvent ) {
	pEvent->accept();
	mButtonPressed = pEvent->button();
	mMousePos = pEvent->pos();
}

void Renderer::mouseReleaseEvent( QMouseEvent* pEvent ) {
	pEvent->accept();
	mButtonPressed = Qt::NoButton;
}

void Renderer::wheelEvent( QWheelEvent* pEvent ) {
	pEvent->accept();
        mCam[2] -=(pEvent->delta()/100);
}

CList_BLob* Renderer::blobList() {
    return &mListBlobs;
}
