#include "pfe.h"
#include "voxel.h"
#include "blob.h"
#include "mc.h"
#include <QFileDialog>
#include <QTime>
#include <QButtonGroup>

PFE::PFE(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	mRenderer = new Renderer( ui.mGLContainer );

        mGroupInfluence = new QButtonGroup;
        mGroupInfluence->setParent(this);
        mGroupInfluence->setExclusive(true);
        mGroupInfluence->addButton(ui.mBlobsNone);
        mGroupInfluence->addButton(ui.mContourERadiusCheckbox);
        mGroupInfluence->addButton(ui.mDeepInnerERadiuscheckbox);
        mGroupInfluence->addButton(ui.mNearInnerERadiusCheckbox);
        mGroupInfluence->addButton(ui.mContourIRadiusCheckbox);
        mGroupInfluence->addButton(ui.mDeepInnerIRadiusCheckbox);
        mGroupInfluence->addButton(ui.mNearInnerIRadiusCheckbox);
        mGroupInfluence->addButton(ui.mBlobFusionCheckbox);

        mGroupInfluence->setId(ui.mContourERadiusCheckbox, 1);
        mGroupInfluence->setId(ui.mNearInnerERadiusCheckbox, 2);
        mGroupInfluence->setId(ui.mDeepInnerERadiuscheckbox , 3);
        mGroupInfluence->setId(ui.mContourIRadiusCheckbox, 4);
        mGroupInfluence->setId(ui.mNearInnerIRadiusCheckbox, 5);
        mGroupInfluence->setId(ui.mDeepInnerIRadiusCheckbox , 6);
        mGroupInfluence->setId(ui.mBlobFusionCheckbox, 7);

	connect( ui.mOpenFileButton, SIGNAL(clicked()), this, SLOT(openFileDialog()) );
	connect( ui.mReconctructionButton, SIGNAL(clicked()), this, SLOT(reconstruction()));
        connect( ui.mCloudPointCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawCloud(int)) );
	connect( ui.mOuterOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawOuterOctree(int)));
	connect( ui.mcontourOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawInOutOctree(int)));
	connect( ui.mNearInnerOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawInnerOctree(int)));
	connect( ui.mDeepInnerOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawDeepOctree(int)));
        connect( mGroupInfluence, SIGNAL(buttonClicked(int)), this, SLOT(setDrawingRadius(int)));
        connect( ui.mRenderButton, SIGNAL(clicked()), this, SLOT(computeBlobsRendering() ) );

}

PFE::~PFE()
{

}

void PFE::openFileDialog() {
        static QString sPath = "../implicite-surface-reconstruction/samples";
	QString lFile = QFileDialog::getOpenFileName(this, "select a file", sPath);
	mRenderer->openCloudFile(lFile);
}

void PFE::reconstruction() {
    if( mRenderer->cloud() == NULL)  return;
    if( mRenderer->cloud()->getNbPoints() == 0) return;

    if( mRenderer->blobList()->size() != 0 )   {
        qWarning()<<"rend deja fait TODO : vider la liste";
        return;
    }

    CVoxel_Tab* lVT = mRenderer->voxelTab();
    QTime lStart; lStart.start();

    qWarning()<<"Voxelisation du nuage";
    lVT->Create_Square_Enum( mRenderer->cloud() );

    //trouve les voxels de surface
    lVT->Find_Boundary_Voxels( mRenderer->cloud() );
    //permet de diffrencier les voxels intérieur des voxels extrieurs
    lVT->Find_InOut_Voxels();
    //permet de trouver les voxels "profonds"
    lVT->Find_Deep_Voxels();
    qWarning()<<"La voxelisation  pris"<< lStart.elapsed()<<"ms";

    lStart.restart();

    qWarning()<<"groupement des voxels en octrees";
    COctree* lOctree = mRenderer->octree();
    lOctree->Create_From_Voxellization( *lVT );
    lOctree->Find_List_Leaves( mRenderer->mListNodes );
    qWarning()<<"le groupement   pris "<<lStart.elapsed()<<" ms";

    lStart.restart();
    qWarning()<<"Calcul des blobs ";
    mRenderer->blobList()->Set_Threshold(ui.mTresholdSpinBox->value());
    qWarning()<<'\t'<<"lecture de la voxelisation";
    mRenderer->blobList()->readVoxellization(mRenderer->cloud()->getPoints(), lVT, ui.mTresholdSpinBox->value());
    qWarning()<<'\t'<<"ajout des blobs de surface";
    mRenderer->blobList()->addBoundaryBlobsFromVoxels(mRenderer->cloud()->getPoints(), lVT );
    qWarning()<<"durée d'ajout des blobs : "<<lStart.elapsed()<<"ms "<<"\n -- nombre de blobs dans la liste : "<<mRenderer->blobList()->size();
}

void PFE::computeBlobsRendering() {
    // if no blobs to draw
    if( mRenderer->blobList()->size() == 0) return;

    // si le rendu à deja été calculé : effacement de la liste de triangle
    if( !mRenderer->triangleList().isEmpty() ) mRenderer->triangleList().clear();

    QTime lTime;
    lTime.start();

    QList<CTriangle> lListTriangles;

    qWarning()<<"calcul du Rendu des blobs : ";

    // Creation de la marching Grid
    CMarching_Grid lMarchingGrid;
    lMarchingGrid.setDimension( ui.mVoxelNumberSpinbox->value() );
    qWarning()<<"Marching grid de dimension : "<<lMarchingGrid.dimension();

    lMarchingGrid.Allocate();
    lMarchingGrid.Init_Boxes( mRenderer->blobList()->Get_Bounded_Box() );
    lMarchingGrid.boundingBox().Voxel_Info();
    lMarchingGrid.Init_Grid();

    qWarning()<<"1/ "<<lTime.elapsed()<<" ms";
    lTime.restart();
    // calculs des valeurs de la grille

    lMarchingGrid.Compute_Val( *mRenderer->blobList() );

    qWarning()<<"2/ "<<lTime.elapsed()<<" ms";
    lTime.restart();

    // calcul des triangles
    lMarchingGrid.computeTriangles(*mRenderer->blobList(), lListTriangles);

    qWarning()<<"le calcul du rendu à pris "<<lTime.elapsed()<<" ms";
    mRenderer->setTriangleList( lListTriangles );
}

void PFE::drawCloud( int pValue ){
    Q_UNUSED(pValue);
    mRenderer->setThingstoDraw( DRAW_CLOUDS );
}

void PFE::drawOuterOctree( int pValue ) {
    Q_UNUSED(pValue);
    mRenderer->setThingstoDraw( DRAW_OCTREE_OUT );
}

void PFE::drawInOutOctree( int pValue ) {
    Q_UNUSED(pValue);
	mRenderer->setThingstoDraw( DRAW_OCTREE_INOUT );
}

void PFE::drawInnerOctree( int pValue ) {
    Q_UNUSED(pValue);
	mRenderer->setThingstoDraw( DRAW_OCTREE_INNER );
}

void PFE::drawDeepOctree( int pValue ) {
    Q_UNUSED(pValue);
	mRenderer->setThingstoDraw( DRAW_OCTREE_DEEP );
}

void PFE::setDrawingRadius(int pValue) {
    qWarning()<<pValue;
    static int sPreviousValue = 0;

    // clearing old value to render
    mRenderer->setThingstoDraw(sPreviousValue);
    switch(pValue) {
        case 1: {
            sPreviousValue = DRAW_BLOBS_EFF_INOUT;
            break;
        }
        case 2:{
            sPreviousValue = DRAW_BLOBS_EFF_IN;
            break;
        }
        case 3:{
            sPreviousValue = DRAW_BLOBS_EFF_DEEP;
            break;
        }

        case 4: {
            sPreviousValue = DRAW_BLOBS_THR_INOUT;
            break;
        }
        case 5:{
            sPreviousValue = DRAW_BLOBS_THR_IN;
            break;
        }
        case 6:{
            sPreviousValue = DRAW_BLOBS_THR_DEEP;
            break;
        }
        case 7: {
            sPreviousValue = DRAW_FUSION;
            break;
        }
        default: {
            sPreviousValue = DRAW_BLOBS_NONE;
            break;
        }
    }
    // send new value to render
    mRenderer->setThingstoDraw(sPreviousValue);
}
