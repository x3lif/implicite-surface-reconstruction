/*
 * Cloud.h
 *
 *  Created on: 6 déc. 2010
 *      Author: guillaume
 */

#ifndef CLOUD_H_
#define CLOUD_H_

#include <GLTools.h>
#include <QString>
#include <QFile>
#include <QVector>
#include <QVector3D>
#include "voxel.h"

class Cloud {
public:
	Cloud();
	Cloud( QString& pFile );
        Cloud(QVector<QVector3D>& pCloud);
	virtual ~Cloud();
	void Draw();
	int getNbPoints();
        QVector<QVector3D> getPoints();
	CVoxel_8 boundingBox();
    const QVector<float>& getFloatsList() const;

public :
        int             mNbPoints;
        QFile 		mFile;
	QVector<float> 	mPointList;
        GLBatch         mGLBatch;
};

#endif /* CLOUD_H_ */
