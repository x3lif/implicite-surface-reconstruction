/*
 * Renderer.h
 *
 *  Created on: 5 déc. 2010
 *      Author: guillaume
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <GLTools.h>
#include <QDebug>
#include <QGLWidget>
#include <QtCore/QTimer>
#include <QMouseEvent>
#include "cloud.h"
#include "octree.h"
#include "blob.h"
#include "triangle.h"
#include <math3d.h>
#include <GLFrame.h>
#include <GLGeometryTransform.h>
#include <GLMatrixStack.h>
#include <GLFrustum.h>
#include <GL/glew.h>
#include <GL/freeglut.h>


#define DRAW_CLOUDS             0x0001
#define DRAW_FUSION             0x0002

#define DRAW_OCTREE_DEEP	0x0010
#define DRAW_OCTREE_INNER	0x0020
#define DRAW_OCTREE_INOUT	0x0040
#define DRAW_OCTREE_OUT		0x0080

#define DRAW_BLOBS_EFF_DEEP     0x0100
#define DRAW_BLOBS_EFF_IN       0x0200
#define DRAW_BLOBS_EFF_INOUT    0x0400

#define DRAW_BLOBS_THR_DEEP     0x1000
#define DRAW_BLOBS_THR_IN       0x2000
#define DRAW_BLOBS_THR_INOUT    0x4000
#define DRAW_BLOBS_NONE         0x8800


class Renderer :public QGLWidget {
	Q_OBJECT
public:
	Renderer( QWidget* pParent = NULL);
        virtual     ~Renderer();
        void        openCloudFile(QString& pPath);
        Cloud*      cloud();
        void        setThingstoDraw(int pValue);
	CVoxel_Tab* voxelTab();
        COctree*    octree();
        CList_BLob* blobList();
        QVector<float>& triangleVertexes();
        void        setTriangleVertexes(const QVector<float>& pVertexs);


protected:
	// inerhited methods.
	virtual void initializeGL();
	virtual void resizeGL( int width, int height );
	virtual void resizeGL( QSize pSize );

public slots :
	virtual void paintGL();
	void mouseMoveEvent( QMouseEvent* pEvent);
	void mousePressEvent( QMouseEvent* pEvent);
	void mouseReleaseEvent( QMouseEvent* pEvent);
	void wheelEvent( QWheelEvent* pEvent );


public:
    CList_Octree_Node mListNodes;
private:
	int mThingsToDraw;
	Cloud* mCloud;
	QTimer mTimer;
        QVector<float> mCam;
        QVector<float> mRot;
        CVoxel_Tab mVT;
        Qt::MouseButtons mButtonPressed;
        QPointF mMousePos;
        COctree mOctree;
        CList_BLob mListBlobs;
        GLShaderManager mShaderManager;
        QVector<float> mTriangleVertex;
        GLBatch     mGLTriangles;
        GLFrame     mCameraFrame;
        GLGeometryTransform mTransformPipeline;

        GLMatrixStack mModelViewMatrix;
        GLMatrixStack mProjectionMatrix;
        GLFrustum mViewFrustum;

        GLBatch				floorBatch;
        GLBatch             mCloudBatch;
        GLTriangleBatch     sphereBatch;
};

#endif /* RENDERER_H_ */
