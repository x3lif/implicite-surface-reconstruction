#ifndef PFE_H
#define PFE_H

#include "utils.h"
#include <QtGui/QWidget>
#include <QDebug>
#include "ui_pfe.h"
#include "renderer.h"

class QButtonGroup;

class PFE : public QWidget
{
    Q_OBJECT

public:
    PFE(QWidget *parent = 0);
    ~PFE();

protected slots:
    void openFileDialog();
    void reconstruction();
    void drawCloud(int pValue);
    void drawOuterOctree( int pValue );
    void drawInOutOctree( int pValue );
    void drawInnerOctree( int pValue );
    void drawDeepOctree( int pValue );
    void setDrawingRadius(int pValue);
    void computeBlobsRendering();

protected:
    QVector<float> fromTriangleListToVertexes(const QList<CTriangle>& pList);

private:
    Ui_Main 	ui;
    Renderer* 	mRenderer;
    QButtonGroup* mGroupInfluence;
};

#endif // PFE_H
