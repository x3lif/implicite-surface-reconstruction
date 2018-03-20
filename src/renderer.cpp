/*
 * Renderer.cpp
 *
 *  Created on: 5 déc. 2010
 *      Author: guillaume
 */

#include "renderer.h"
#include <QTime>
#include <QVector3D>

GLfloat gLight0[3][4] = { {0.1f, 0.1f, 0.3f, 1.0f},
                             {0.5f, 0.5f, 1.0f, 1.0f},
                             {3.0f, 3.0f, 0.0f, 0.0f} };

GLfloat gLight1[3][4] = { {0.1f, 0.1f, 0.3f, 1.0f},
                             {1.0f, 0.5f, 0.5f, 1.0f},
                             {-4.0f, -4.0f, 4.0f, 0.0f} };

Renderer::Renderer( QWidget* pParent):
    mCameraFrame()
{
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
    mProjectionMatrix.LoadIdentity();
    mModelViewMatrix.LoadIdentity();

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


    // Color values
    /*   static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};
       static GLfloat vTorusColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };

       // Time Based animation
       static float yRot = 0;
       yRot += 0.016 * 60.0f;

       // Clear the color and depth buffers
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


       // Save the current modelview matrix (the identity matrix)
       modelViewMatrix.PushMatrix();

       // Draw the ground
       mShaderManager.UseStockShader(GLT_SHADER_FLAT,
                                    mTransformPipeline.GetModelViewProjectionMatrix(),
                                    vFloorColor);
       floorBatch.Draw();

       // Draw the spinning Torus
       modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
       modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
       mShaderManager.UseStockShader(GLT_SHADER_FLAT, mTransformPipeline.GetModelViewProjectionMatrix(),
                                   vTorusColor);
       torusBatch.Draw();
       sphereBatch.Draw();

       // Restore the previous modleview matrix (the idenity matrix)
       modelViewMatrix.PopMatrix();
      */


        QTime lTime;
        lTime.start();

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
     float lColor[] = {1.0,0,0,1.0};
     //glEnable(GL_POINT);

     //glMatrixMode( GL_PROJECTION );
     //glLoadIdentity();
         //gluPerspective( 45, (float)this->width()/(float)this->height(), 0.0001, 999.0 );

     //glMatrixMode( GL_MODELVIEW );
     //glLoadIdentity();
//   gluLookAt(	mCam[0], mCam[1], mCam[2],
//				mCam[3], mCam[4], mCam[5],
//              mCam[6], mCam[7], mCam[8]);
//

     //glRotatef( mRot[0], 0.0f, 0.0f, 1.0f );
     //glRotatef( mRot[1], 1.0f, 0.0f, 0.0f );
     modelViewMatrix.PushMatrix();

//     mShaderManager.UseStockShader(GLT_SHADER_FLAT,
//                                      mTransformPipeline.GetModelViewProjectionMatrix(),
//                                      lColor);

     M3DMatrix44f mCamera;
     mCameraFrame.GetCameraMatrix(mCamera);
     //mModelViewMatrix.PushMatrix(mCamera);
     modelViewMatrix.PushMatrix(mCamera);

     modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
     modelViewMatrix.Rotate(0, 0.0f, 1.0f, 0.0f);
     //mModelViewMatrix.PushMatrix();
//   mModelViewMatrix.Rotate(mRot[0],0,0,1);
//     mModelViewMatrix.Rotate(mRot[1],1,0,1);
//

     glPointSize(2.0f);
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     mShaderManager.UseStockShader(GLT_SHADER_FLAT,
                                      mTransformPipeline.GetModelViewProjectionMatrix(),
                                      lColor);
     //sphereBatch.Draw();

      // Draw the Cloud
      if(mCloud != NULL && (mThingsToDraw & DRAW_CLOUDS ) ) {
          mCloud->Draw();
      }
      //mModelViewMatrix.PopMatrix();

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

     modelViewMatrix.PopMatrix();
     modelViewMatrix.PopMatrix();

   if( mThingsToDraw & DRAW_BLOBS_THR_DEEP ) {
         mListBlobs.drawBlobsInfluence( 3 );
     }
     if( mThingsToDraw & DRAW_BLOBS_THR_IN ) {
         mListBlobs.drawBlobsInfluence( 2 );
     }
     if( mThingsToDraw & DRAW_BLOBS_THR_INOUT ) {
         mListBlobs.drawBlobsInfluence( 1 );
     }


     if( !mTriangleVertex.isEmpty() && (mThingsToDraw&DRAW_FUSION) ) {
         /*QListIterator<CTriangle> lIte(mTriangleList);
         while( lIte.hasNext() ) {
             CTriangle lTemp = lIte.next();
             lTemp.Draw();
         }*/

         //mShaderManager.UseStockShader(GLT_SHADER_IDENTITY, lRed);
    /*     glEnable(GL_COLOR_MATERIAL);
         glColor3f(1.0,1.0,1.0);
         glPushMatrix();
            lColor[0] = lColor[1] = lColor[2] = 0.5; lColor[3]=1.0;
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lColor);
            mGLTriangles.Draw();
         glPopMatrix();
         glDisable(GL_COLOR_MATERIAL);
     */
     }
     //qWarning()<<lTime.elapsed();
}


void Renderer::initializeGL() {
    gltSetWorkingDirectory("");
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        qWarning()<<"GLEW Error: "<<glewGetErrorString(err);
    }

  /*  glClearColor(0, 0, 0, 0);
    this->resizeGL( parentWidget()->size() );

    mCameraFrame.MoveForward(-4.0);

    mShaderManager.InitializeStockShaders();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2,0.2,0.2,1.0f);

//   glEnable(GL_LIGHTING);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_COLOR_MATERIAL);
//    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

//    glShadeModel(GL_SMOOTH);

//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, gLight0[0]);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, gLight0[1]);
//    glLightfv(GL_LIGHT0, GL_POSITION, gLight0[2]);

//    glEnable(GL_LIGHT1);
//    glLightfv(GL_LIGHT1, GL_AMBIENT, gLight1[0]);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, gLight1[1]);
//    glLightfv(GL_LIGHT1, GL_POSITION, gLight1[2]);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_FRONT_AND_BACK);

//    mCameraFrame.SetForwardVector(0,0,1);
//    mCameraFrame.SetUpVector(0,1,0);
//    mCameraFrame.SetOrigin(0,0,0);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT_AND_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnableClientState(GLT_ATTRIBUTE_VERTEX);

    gltMakeSphere(sphereBatch, 1.3f, 15, 15);*/



    // Initialze Shader Manager
    mShaderManager.InitializeStockShaders();
    gltMakeSphere(sphereBatch, 0.3f, 15, 15);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::resizeGL( int width, int height ){
    this->resize(width, height);
    glViewport(0, 0, width, height);
    mViewFrustum.SetPerspective(35.0f, float(width)/float(height), 0.1f, 500.0f);
    mProjectionMatrix.LoadMatrix(mViewFrustum.GetProjectionMatrix());

    //mTransformPipeline.SetMatrixStacks(mModelViewMatrix,mProjectionMatrix);

    // Create the projection matrix, and load it on the projection matrix stack
    projectionMatrix.LoadMatrix(mViewFrustum.GetProjectionMatrix());

    // Set the transformation pipeline to use the two matrix stacks
    mTransformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void Renderer::resizeGL( QSize pSize ){
    this->resizeGL(pSize.width(), pSize.height());
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
            //mCam[3] += (float)lTemp.x();
            //mCam[4] -= (float)lTemp.y();
            mCameraFrame.MoveUp((float)lTemp.y());
            mCameraFrame.MoveRight((float)lTemp.x());

			mMousePos = pEvent->pos();
		}	break;
		case Qt::RightButton  : {
			lTemp = (mMousePos - pEvent->posF())/10.0;
            //mRot[0] -= (float)lTemp.x();
            //mRot[1] += (float)lTemp.y();
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
        mCameraFrame.MoveForward((float)pEvent->delta()/100);
}

CList_BLob* Renderer::blobList() {
    return &mListBlobs;
}

QVector<float>& Renderer::triangleVertexes() {
    return mTriangleVertex;
}

void Renderer::setTriangleVertexes(const QVector<float>& pVertexs) {
    if(pVertexs.size()%3 != 0)  return;

    mTriangleVertex = pVertexs;
    // specify the type pf draw and nbVertex per coordinate
    mGLTriangles.Begin(GL_TRIANGLES, pVertexs.size()/3);
    //copy informations
    mGLTriangles.CopyVertexData3f( (GLfloat*)mTriangleVertex.data() );
    // need explications?
    mGLTriangles.End();
}
