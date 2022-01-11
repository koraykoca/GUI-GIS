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

#include <qtoolbutton.h>
#include <qlist.h>

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
    connect(actionMap_1, SIGNAL(triggered()), this, SLOT(addLayer1()));
    connect(actionMap_2, SIGNAL(triggered()), this, SLOT(addLayer2()));
    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(addLayer1()));
    connect(checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(addLayer2()));

    QToolButton* toolButton = new QToolButton();
    toolButton->setMenu(menuAdd_Layer);
    toolButton->setIcon(QIcon(":/mActionAddLayer.png"));
    toolButton->setPopupMode(QToolButton::InstantPopup);

    //create a little toolbar
    mpMapToolBar = addToolBar(tr("File"));
    mpMapToolBar->addWidget(toolButton);
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
  delete actionMap_1;
  delete actionMap_2;
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

void MainWindow::addLayer1()
{
    QString myLayerPath  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb01_f.shp";
    QString myLayerBaseName = "geb01_f";
    QString myProviderName = "ogr";

    QgsVectorLayer * mypLayer = new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);

    QgsSymbol *symbol = QgsSymbol::defaultSymbol(mypLayer->geometryType());

    symbol->setColor(QColor("#4d913d"));

    QgsSingleSymbolRenderer *mypRenderer = new QgsSingleSymbolRenderer(symbol);

    //QList <QgsMapLayer *> layers;

    mypLayer->setRenderer(mypRenderer);

    // Add the Vector Layer to the Project Registry
    QgsProject::instance()->addMapLayer(mypLayer, true);

    // Add the Layer to the Layer Set
    if (layer_names.contains("layer1") == false){
        layers.append(mypLayer);
        layer_names.append("layer1");
    }

    // set the canvas to the extent of our layer
    mpMapCanvas->setExtent(mypLayer->extent());

    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);

}

void MainWindow::addLayer2()
{
    QString myLayerPath2  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/ver01_l.shp";
    QString myLayerBaseName2 = "ver01.l_p";
    QString myProviderName = "ogr";

    QgsVectorLayer * mypLayer2 = new QgsVectorLayer(myLayerPath2, myLayerBaseName2, myProviderName);

    QgsSingleSymbolRenderer *mypRenderer2 = new QgsSingleSymbolRenderer(QgsSymbol::defaultSymbol(mypLayer2->geometryType()));

    mypLayer2->setRenderer(mypRenderer2);

    // Add the Vector Layer to the Project Registry
    QgsProject::instance()->addMapLayer(mypLayer2, true);

    // Add the Layer to the Layer Set
    if (layer_names.contains("layer2") == false){
        layers.push_front(mypLayer2);
        layer_names.append("layer2");
    }

    // set the canvas to the extent of our layer
    if (layer_names.contains("layer1") == false){
        mpMapCanvas->setExtent(mypLayer2->extent());
    }

    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);
}
