/*
 * Renderer.h
 *
 *  Created on: 5 déc. 2010
 *      Author: guillaume
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <QDebug>
#include <QGLWidget>
#include <QtCore/QTimer>
#include <QMouseEvent>
#include "cloud.h"
#include "octree.h"

#define DRAW_CLOUDS 0x001

#define DRAW_OCTREE_DEEP	0x010
#define DRAW_OCTREE_INNER	0x020
#define DRAW_OCTREE_INOUT	0x040
#define DRAW_OCTREE_OUT		0x080


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

};

#endif /* RENDERER_H_ */
