#include "mainwindow.h"

// QGIS Includes

#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsproject.h>
#include <qgsvectorlayer.h>
#include <qgsmapcanvas.h>
#include <qgssymbol.h>

// QGIS Map tools
#include "qgsmaptoolpan.h"
#include "qgsmaptoolzoom.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags fl)
    : QMainWindow(parent,fl)
{
    //required by Qt4 to initialise the ui
    setupUi(this);

    // Instantiate Provider Registry
    QString myPluginsDir = "/home/koray/dev/cpp/QGIS/build-master-qtcreator/output/lib/qgis";

    QgsProviderRegistry::instance(myPluginsDir);

    mpMapCanvas = new QgsMapCanvas();

    mpMapCanvas->enableAntiAliasing(true);
    mpMapCanvas->setCanvasColor(QColor(255, 255, 255));
    mpMapCanvas->freeze(false);
    mpMapCanvas->setVisible(true);
    mpMapCanvas->refresh();
    mpMapCanvas->show();

    // Lay our widgets out in the main window
    mpLayout = new QVBoxLayout(frameMap);
    mpLayout->addWidget(mpMapCanvas);

    //create the action behaviours
    connect(mpActionPan, SIGNAL(triggered()), this, SLOT(panMode()));
    connect(mpActionZoomIn, SIGNAL(triggered()), this, SLOT(zoomInMode()));
    connect(mpActionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOutMode()));
    connect(mpActionAddLayer, SIGNAL(triggered()), this, SLOT(addLayer()));

    //create a little toolbar
    mpMapToolBar = addToolBar(tr("File"));
    mpMapToolBar->addAction(mpActionAddLayer);
    mpMapToolBar->addAction(mpActionZoomIn);
    mpMapToolBar->addAction(mpActionZoomOut);
    mpMapToolBar->addAction(mpActionPan);

    //create the maptools
    mpPanTool = new QgsMapToolPan(mpMapCanvas);
    mpPanTool->setAction(mpActionPan);

    mpZoomInTool = new QgsMapToolZoom(mpMapCanvas, false); // false = in
    mpZoomInTool->setAction(mpActionZoomIn);

    mpZoomOutTool = new QgsMapToolZoom(mpMapCanvas, true ); //true = out
    mpZoomOutTool->setAction(mpActionZoomOut);
}

MainWindow::~MainWindow()
{
  delete mpZoomInTool;
  delete mpZoomOutTool;
  delete mpPanTool;
  delete mpMapToolBar;
  delete mpMapCanvas;
  delete mpLayout;
}

void MainWindow::panMode()
{
    mpMapCanvas->setMapTool(mpPanTool);
}

void MainWindow::zoomInMode()
{
    mpMapCanvas->setMapTool(mpZoomInTool);
}

void MainWindow::zoomOutMode()
{
    mpMapCanvas->setMapTool(mpZoomOutTool);
}

void MainWindow::addLayer()
{
    QString myLayerPath  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb01_f.shp";
    QString myLayerBaseName = "geb01_f";
    QString myProviderName = "ogr";

    QString myLayerPath2  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb03_p.shp";
    QString myLayerBaseName2 = "geb03_p";

    QgsVectorLayer * mypLayer = new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);
    QgsVectorLayer * mypLayer2 = new QgsVectorLayer(myLayerPath2, myLayerBaseName2, myProviderName);

    QgsSingleSymbolRenderer *mypRenderer = new QgsSingleSymbolRenderer(QgsSymbol::defaultSymbol(mypLayer->geometryType()));
    QgsSingleSymbolRenderer *mypRenderer2 = new QgsSingleSymbolRenderer(QgsSymbol::defaultSymbol(mypLayer2->geometryType()));

    QList <QgsMapLayer *> layers;

    mypLayer->setRenderer(mypRenderer);
    mypLayer2->setRenderer(mypRenderer2);

    if (mypLayer->isValid())
    {
    qDebug("Layer is valid");
    }
    else
    {
    qDebug("Layer is NOT valid");
    return;
    }

    // Add the Vector Layer to the Project Registry
    QgsProject::instance()->addMapLayer(mypLayer, true);
    QgsProject::instance()->addMapLayer(mypLayer2, true);

    // Add the Layer to the Layer Set
    layers.append(mypLayer2);
    layers.append(mypLayer);

    // set the canvas to the extent of our layer
    mpMapCanvas->setExtent(mypLayer->extent());
    //mpMapCanvas->setExtent(mypLayer2->extent());

    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);
}
