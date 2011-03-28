#include "pfe.h"
#include "voxel.h"
#include <QFileDialog>
#include <QTime>

PFE::PFE(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	mRenderer = new Renderer( ui.mGLContainer );

	connect( ui.mOpenFileButton, SIGNAL(clicked()), this, SLOT(openFileDialog()) );
	connect( ui.mReconctructionButton, SIGNAL(clicked()), this, SLOT(reconstruction()));
	connect( ui.mCloudPointCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawCloud(int)) );
	connect( ui.mOuterOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawOuterOctree(int)));
	connect( ui.mcontourOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawInOutOctree(int)));
	connect( ui.mNearInnerOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawInnerOctree(int)));
	connect( ui.mDeepInnerOctreeCheckbox, SIGNAL(stateChanged(int)), this, SLOT(drawDeepOctree(int)));
}

PFE::~PFE()
{

}

void PFE::openFileDialog() {
	static QString sPath = "./samples";
	QString lFile = QFileDialog::getOpenFileName(this, "select a file", sPath);
	mRenderer->openCloudFile(lFile);
}

void PFE::reconstruction() {
    CVoxel_Tab* lVT = mRenderer->voxelTab();
    if(lVT == NULL)	return;

    QTime lStart; lStart.start();

    qWarning()<<"Voxelisation du nuage";
    lVT->Create_Square_Enum( mRenderer->cloud() );

    //trouve les voxels de surface
    lVT->Find_Boundary_Voxels( mRenderer->cloud() );
    //permet de différencier les voxels intérieur des voxels extérieurs
    lVT->Find_InOut_Voxels();
    //permet de trouver les voxels "profonds"
    lVT->Find_Deep_Voxels();
    qWarning()<<"La voxelisation "<< lStart.elapsed()<<"ms";

    lStart.restart();
    qWarning()<<"groupement des voxels en octrees";
    COctree* lOctree = mRenderer->octree();
    lOctree->Create_From_Voxellization( *lVT );
    lOctree->Find_List_Leaves( mRenderer->mListNodes );
    qWarning()<<"le groupement à pris "<<lStart.elapsed()<<" ms";
}

void PFE::drawCloud( int pValue ){
    pValue = 0;
	mRenderer->setThingstoDraw( DRAW_CLOUDS );
}

void PFE::drawOuterOctree( int pValue ) {
	mRenderer->setThingstoDraw( DRAW_OCTREE_OUT );
}

void PFE::drawInOutOctree( int pValue ) {
	mRenderer->setThingstoDraw( DRAW_OCTREE_INOUT );
}

void PFE::drawInnerOctree( int pValue ) {
	mRenderer->setThingstoDraw( DRAW_OCTREE_INNER );
}

void PFE::drawDeepOctree( int pValue ) {
	mRenderer->setThingstoDraw( DRAW_OCTREE_DEEP );
}
