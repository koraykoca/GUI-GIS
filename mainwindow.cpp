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
    //QString myPluginsDir = "/home/koray/dev/cpp/QGIS/build-master-qtcreator/output/lib/qgis";
    QString myPluginsDir = "/home/unibw/dev/cpp/QGIS/build-master-qtcreator/output/lib/qgis";

    crsSrc = QgsCoordinateReferenceSystem("EPSG:25832");  // UTM Zone 32
    crsDest = QgsCoordinateReferenceSystem("EPSG:4326");  // WGS 84

    QgsCoordinateTransformContext context;
    mTransform = QgsCoordinateTransform(crsSrc, crsDest, context);

    QgsProviderRegistry::instance(myPluginsDir);

    mpMapCanvas = new QgsMapCanvas();  // QgsMapCanvas to visualize QgsMapLayers like QgsVectorLayer or QgsRasterLayer

    mpMapCanvas->enableAntiAliasing(true);
    mpMapCanvas->setCanvasColor(QColor(255, 255, 255));
    mpMapCanvas->freeze(false);
    mpMapCanvas->setVisible(true);
    mpMapCanvas->refresh();
    mpMapCanvas->show();
    mpMapCanvas->setMouseTracking(true);

    mpClickPoint = new QgsMapToolEmitPoint(mpMapCanvas);
    mpMapCanvas->setMapTool(mpClickPoint);

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
    connect(checkBox_3, SIGNAL(stateChanged(int)), this, SLOT(addLayer3()));
    connect(mpClickPoint, SIGNAL(canvasClicked(QgsPointXY,Qt::MouseButton)), this, SLOT(showCoord(QgsPointXY)));


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

    //create the map tools
    mpPanTool = new QgsMapToolPan(mpMapCanvas);
    mpPanTool->setAction(mpActionPan);

    mpZoomInTool = new QgsMapToolZoom(mpMapCanvas, false); // false = zoom in
    mpZoomInTool->setAction(mpActionZoomIn);

    mpZoomOutTool = new QgsMapToolZoom(mpMapCanvas, true ); //true = zoom out
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
  delete checkBox;
  delete checkBox_2;
  delete checkBox_3;
}

void MainWindow::showCoord(QgsPointXY point)
{
    point = mTransform.transform(point);
    this->label_2->setText(QString::number(point.y(), 'f', 4));
    this->label_3->setText(QString::number(point.x(), 'f', 4));
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

QgsVectorLayer * ptrLayer1 = nullptr;
QgsVectorLayer * ptrLayer2 = nullptr;
QgsVectorLayer * ptrLayer3 = nullptr;

void MainWindow::addLayer1()
{
    if (layers.contains(ptrLayer1) == false){

        //QString myLayerPath  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb01_f.shp";
        QString myLayerPath  = "/home/unibw/dev/cpp/ldbv_bayern/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb01_f.shp";
        QString myLayerBaseName = "geb01_f";
        QString myProviderName = "ogr";

        QgsVectorLayer * mypLayer = new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);

        ptrLayer1 = mypLayer;

        QgsSymbol *symbol = QgsSymbol::defaultSymbol(mypLayer->geometryType());

        symbol->setColor(QColor("#CD736C"));

        QgsSingleSymbolRenderer *mypRenderer = new QgsSingleSymbolRenderer(symbol);

        qDebug() << mypLayer;

        // Add the Vector Layer to the Project Registry. Before map layers can be rendered,
        // they need to be stored in a QgsMapLayerStore. This will be done by adding the current QgsProject instance
        QgsProject::instance()->addMapLayer(mypLayer, true);

        mypLayer->setRenderer(mypRenderer);

        // Add the Layer to the Layer Set
        layers.append(mypLayer);

        // set the canvas to the extent of our layer. We focus the map canvas to the spatial extent of our layer
        mpMapCanvas->setExtent(mypLayer->extent());
        }

    else{
        layers.removeOne(ptrLayer1);
        }

        // Set the Map Canvas Layers
        mpMapCanvas->setLayers(layers);
}

void MainWindow::addLayer2()
{
    //QString myLayerPath2  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/ver01_l.shp";
    QString myLayerPath2  = "/home/unibw/dev/cpp/ldbv_bayern/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/ver01_l.shp";
    QString myLayerBaseName2 = "ver01_l";
    QString myProviderName = "ogr";

    if (layers.contains(ptrLayer2) == false){
        QgsVectorLayer * mypLayer2 = new QgsVectorLayer(myLayerPath2, myLayerBaseName2, myProviderName);

        ptrLayer2 = mypLayer2;

        QgsSymbol *symbol = QgsSymbol::defaultSymbol(mypLayer2->geometryType());

        symbol->setColor(QColor("#AFE52F"));

        QgsSingleSymbolRenderer *mypRenderer2 = new QgsSingleSymbolRenderer(symbol);

        mypLayer2->setRenderer(mypRenderer2);

        // Add the Vector Layer to the Project Registry
        QgsProject::instance()->addMapLayer(mypLayer2, true);

        if (layers.isEmpty() == true){
             mpMapCanvas->setExtent(mypLayer2->extent());
        }

        layers.push_front(mypLayer2);
    }

        else{
            layers.removeOne(ptrLayer2);
        }

        // Set the Map Canvas Layers
        mpMapCanvas->setLayers(layers);
}

void MainWindow::addLayer3()
{
    //QString myLayerPath3  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/veg02_f.shp";
    QString myLayerPath3  = "/home/unibw/dev/cpp/ldbv_bayern/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/veg02_f.shp";
    QString myLayerBaseName3 = "veg02_f";
    QString myProviderName = "ogr";

    if (layers.contains(ptrLayer3) == false){

        QgsVectorLayer * mypLayer3 = new QgsVectorLayer(myLayerPath3, myLayerBaseName3, myProviderName);

        ptrLayer3 = mypLayer3;

        QgsSymbol *symbol = QgsSymbol::defaultSymbol(mypLayer3->geometryType());

        symbol->setColor(QColor("#B35BBD"));

        QgsSingleSymbolRenderer *mypRenderer3 = new QgsSingleSymbolRenderer(symbol);

        mypLayer3->setRenderer(mypRenderer3);

        // Add the Vector Layer to the Project Registry
        QgsProject::instance()->addMapLayer(mypLayer3, true);

        if (layers.isEmpty() == true){
            mpMapCanvas->setExtent(mypLayer3->extent());
        }

        layers.push_front(mypLayer3);
    }

        else{
            layers.removeOne(ptrLayer3);
        }

        // Set the Map Canvas Layers
        mpMapCanvas->setLayers(layers);
}

