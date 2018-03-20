/*
 * Cloud.cpp
 *
 *  Created on: 6 déc. 2010
 *      Author: guillaume
 */

#include <GL/glew.h>
#include "cloud.h"
#include <QDebug>
#include <QStringList>
#include <QVectorIterator>

Cloud::Cloud() {
	mNbPoints = 0;
}

Cloud::Cloud( QString& pFile ){
	// TODO Auto-generated constructor stub
	QFile mFile(pFile);

	//load file content
	if(!mFile.open(QIODevice::ReadOnly)) {
		qWarning()<<"Error opening file";
		return;
	}

	//work on the file
	QString lDatas =  mFile.readAll();
	QStringList lTokens = lDatas.split(QRegExp("[ |\n]"), QString::SkipEmptyParts);
	QString nbInt = lTokens.at(0);
	mNbPoints = nbInt.toInt();
	//remove first item (size) from the list
	lTokens.removeFirst();

	QStringListIterator lTokIterator(lTokens);
	while(lTokIterator.hasNext()) {
                mPointList << lTokIterator.next().toFloat();
	}
        qWarning()<<mPointList.size()<<mNbPoints;

        glPointSize(5.0f);
        mGLBatch.Begin(GL_POINTS, mNbPoints);
        for(int i=0;i<mNbPoints;i++)
        {
            mGLBatch.Vertex3f(mPointList[i*3],mPointList[i*3+1], mPointList[i*3+2]);
        }
        mGLBatch.End();

}

Cloud::Cloud(QVector<QVector3D>& pCloud) {
    mNbPoints = pCloud.size();
    for(int i=0;i<pCloud.size();++i)
    {
        const QVector3D& lTemp = pCloud.at(i);
        mPointList<<lTemp.x()<<lTemp.y()<<lTemp.z();
    }
}

Cloud::~Cloud() {
	// TODO Auto-generated destructor stub
}

void Cloud::Draw() {
	if(mNbPoints == 0)	return;

    glColor3f(1.0f,0.0f,0.0f);
    mGLBatch.Draw();
}


int Cloud::getNbPoints() {
	return mNbPoints;
}

QVector<QVector3D> Cloud::getPoints(){
	QVector<QVector3D> lResult;
    for(int i=0; i<mNbPoints*3; i+=3)
    {
		lResult << QVector3D(mPointList[i],mPointList[i+1], mPointList[i+2]);
	}
	return lResult;
}

CVoxel_8 Cloud::boundingBox() {
	QVector<QVector3D> lTab = getPoints();
	CVoxel_8 Bounding_Box;
	double xmax,ymax,zmax,xmin,ymin,zmin;
	xmax=ymax=zmax=-100000;
	xmin=ymin=zmin=100000;
	for(int i=0; i<lTab.size();i++) {
		xmax = qMax(lTab[i].x(), xmax);
		xmin = qMin(lTab[i].x(), xmin);
		ymax = qMax(lTab[i].y(), ymax);
		ymin = qMin(lTab[i].y(), ymin);
        zmax = qMax(lTab[i].z(), zmax);
		zmin = qMin(lTab[i].z(), zmin);
	}

	Bounding_Box.Put_Vertex(0,xmin,ymin,zmin);
	Bounding_Box.Put_Vertex(1,xmax,ymin,zmin);
	Bounding_Box.Put_Vertex(2,xmax,ymin,zmax);
	Bounding_Box.Put_Vertex(3,xmin,ymin,zmax);
	Bounding_Box.Put_Vertex(4,xmin,ymax,zmin);
	Bounding_Box.Put_Vertex(5,xmax,ymax,zmin);
	Bounding_Box.Put_Vertex(6,xmax,ymax,zmax);
	Bounding_Box.Put_Vertex(7,xmin,ymax,zmax);
	return Bounding_Box;
}

 const QVector<float>& Cloud::getFloatsList() const
 {
     return mPointList;
 }
