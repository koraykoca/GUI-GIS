#include "mainwindow.h"

// QGIS Includes

#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsproject.h>
#include <qgsvectorlayer.h>
#include <qgsmapcanvas.h>
#include <qgssymbol.h>
#include <qgsmapcanvasitem.h>

// QGIS Map tools
#include "qgsmaptoolpan.h"
#include "qgsmaptoolzoom.h"

#include <qtoolbutton.h>
#include <qlist.h>
#include <qpoint.h>
#include <QGraphicsItem>

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

    //Lay our widgets out in the main window
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
    connect(checkBox_4, SIGNAL(stateChanged(int)), this, SLOT(addLayer4()));
    connect(mpClickPoint, SIGNAL(canvasClicked(QgsPointXY,Qt::MouseButton)), this, SLOT(selectCoord(QgsPointXY)));
    connect(mpMapCanvas, SIGNAL(xyCoordinates(QgsPointXY)), this, SLOT(showCoord(QgsPointXY)));

    QToolButton* toolButton = new QToolButton();  // local variable
    toolButton->setMenu(menuAdd_Layer);
    toolButton->setIcon(QIcon(":/mActionAddLayer.png"));
    toolButton->setPopupMode(QToolButton::InstantPopup);

    //create a little toolbar
    mpMapToolBar = addToolBar(tr("Canvas Actions"));
    mpMapToolBar->addWidget(toolButton);
    mpMapToolBar->addAction(mpActionZoomIn);
    mpMapToolBar->addAction(mpActionZoomOut);
    mpMapToolBar->addAction(mpActionPan);

    mpActionZoomIn->setCheckable(true);
    mpActionZoomOut->setCheckable(true);
    mpActionPan->setCheckable(true);

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
    if (layers.contains(ptrLayer4) == false){
        point = mTransform.transform(point);
    }
    this->label_2->setText(QString::number(point.y(), 'f', 4) + " " + QString::number(point.x(), 'f', 4));
}

void MainWindow::selectCoord(QgsPointXY point)
{
    if (layers.contains(ptrLayer4) == false){
        QgsPointXY point_trans = point;
        point_trans = mTransform.transform(point_trans);
        textBrowser->setText(QString::number(point_trans.y(), 'f', 4) + " " + QString::number(point_trans.x(), 'f', 4));
    }
    else{
        textBrowser->setText(QString::number(point.y(), 'f', 4) + " " + QString::number(point.x(), 'f', 4));
    }

    QLabel *marker = new QLabel(mpMapCanvas);
    marker->setPixmap(QPixmap(":/mapMarker.png"));
//    marker->move(point.x(), point.y());
//    marker->show();

    qDebug() << "x:" << point.x() << "y:" << point.y();

    qreal x = point.x();
    qreal y = point.y();
    mpMapCanvas->getCoordinateTransform()->transformInPlace(x, y);
    QPointF pointf = QPointF(x , y);

    marker->move(pointf.x(), pointf.y());
    marker->show();

    qDebug() << "x:" << pointf.x() << "y:" << pointf.y();

//    QPoint pointq = pointf.toPoint();

//    qDebug() << "x:" << pointq.x() << "y:" << pointq.y();

//    QPoint pos = mpMapCanvas->mapToGlobal(pointq);
//    qDebug() << "x:" << pos.x() << "y:" << pos.y();
//    marker->move(pos.x(), pos.y());
//    marker->show();



//QgsLabeling * qmarker = new QgsLabeling(mpMapCanvas);

//    QPoint sPoint;
//    sPoint.setX(pointf.rx());
//    sPoint.setY(float(pointf.y()));

//    qDebug() << "x:" << sPoint.x() << "y:" << sPoint.y();

//    QPoint viewP = mpMapCanvas->mapFromScene(pointf);

//    qDebug() << "x:" << viewP.x() << "y:" << viewP.y();

// QPoint points = mpMapCanvas->mapToGlobal(point);

//    qDebug() << "x:" << points.x() << "y:" << points.y();



    //marker->move();

    //QgsPointXY pointc = QgsMapCanvas::setCenter(point);

    //qDebug() << "x:" << qPoint.x() << "y:" << qPoint.y();
    //marker->setVisible(true);
    //

//    QgsVertexMarker *marker2 = new QgsVertexMarker(mpMapCanvas);  // to create a marker using the class into the canvas
//    marker2->setIconType(QgsVertexMarker::ICON_X);
//    marker2->setVisible(true);
//    marker2->setCenter(point);

//    qDebug() << "x:" << marker2->x() << "y:" << marker2->y();
}

void MainWindow::putMarker()
{
    QMainWindow::statusBar()->showMessage(tr("Clicked"));

}

void MainWindow::panMode()
{
    if (mpActionPan->isChecked()){
        mpMapCanvas->setMapTool(mpPanTool);
    }
    else{
        mpMapCanvas->unsetMapTool(mpPanTool);
        mpMapCanvas->setMapTool(mpClickPoint);
    }
}

void MainWindow::zoomInMode()
{
    if (mpActionZoomIn->isChecked()){
        mpMapCanvas->setMapTool(mpZoomInTool);
    }
    else{
        mpMapCanvas->unsetMapTool(mpZoomInTool);
        mpMapCanvas->setMapTool(mpClickPoint);
    }
}

void MainWindow::zoomOutMode()
{
   if (mpActionZoomOut->isChecked()){
       mpMapCanvas->setMapTool(mpZoomOutTool);
   }
   else{
       mpMapCanvas->unsetMapTool(mpZoomOutTool);
       mpMapCanvas->setMapTool(mpClickPoint);
   }
}

void MainWindow::addLayer1()
{
    if (layers.contains(ptrLayer4) == true){
        layers.removeOne(ptrLayer4);
    }

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

        // Add the Vector Layer to the Project Registry. Before map layers can be rendered,
        // they need to be stored in a QgsMapLayerStore. This will be done by adding the current QgsProject instance
        QgsProject::instance()->addMapLayer(mypLayer, true);

        mypLayer->setRenderer(mypRenderer);

        // Add the Layer to the Layer Set
        layers.append(mypLayer);
        mpMapCanvas->setMapTool(mpClickPoint);

        // set the canvas to the extent of our layer. We focus the map canvas to the spatial extent of our layer
        mpMapCanvas->setExtent(mypLayer->extent());
    }

    else{
        layers.removeOne(ptrLayer1);
        if (layers.isEmpty() == true){
             mpMapCanvas->unsetMapTool(mpClickPoint);
        }
    }
    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);
}

void MainWindow::addLayer2()
{    
    if (layers.contains(ptrLayer4) == true){
        layers.removeOne(ptrLayer4);
    }

    if (layers.contains(ptrLayer2) == false){

        //QString myLayerPath2  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/ver01_l.shp";
        QString myLayerPath2  = "/home/unibw/dev/cpp/ldbv_bayern/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/ver01_l.shp";
        QString myLayerBaseName2 = "ver01_l";
        QString myProviderName = "ogr";

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
        mpMapCanvas->setMapTool(mpClickPoint);
    }

    else{
        layers.removeOne(ptrLayer2);
         if (layers.isEmpty() == true){
            mpMapCanvas->unsetMapTool(mpClickPoint);
         }
    }
    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);
}

void MainWindow::addLayer3()
{
    if (layers.contains(ptrLayer4) == true){
        layers.removeOne(ptrLayer4);
    }

    if (layers.contains(ptrLayer3) == false){

        //QString myLayerPath3  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/veg02_f.shp";
        QString myLayerPath3  = "/home/unibw/dev/cpp/ldbv_bayern/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/veg02_f.shp";
        QString myLayerBaseName3 = "veg02_f";
        QString myProviderName = "ogr";

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
        mpMapCanvas->setMapTool(mpClickPoint);
    }

    else{
        layers.removeOne(ptrLayer3);
        if (layers.isEmpty() == true){
            mpMapCanvas->unsetMapTool(mpClickPoint);
        }
    }
    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);
}

void MainWindow::addLayer4()
{
    if (layers.contains(ptrLayer4) == false){

        //QString myLayerPath4  = "/home/koray/work-unibw/2021_11_Airspace_Germany.txt";
        QString myLayerPath4  = "/home/unibw/dev/cpp/2021_11_Airspace_Germany.txt";
        QString myLayerBaseName4 = "2021_11_Airspace_Germany — airspaces";
        QString myProviderName = "ogr";

        QgsVectorLayer * mypLayer4 = new QgsVectorLayer(myLayerPath4, myLayerBaseName4, myProviderName);

        ptrLayer4 = mypLayer4;

        QgsSymbol *symbol = QgsSymbol::defaultSymbol(mypLayer4->geometryType());

        QgsSingleSymbolRenderer *mypRenderer4 = new QgsSingleSymbolRenderer(symbol);

        mypLayer4->setRenderer(mypRenderer4);

        // Add the Vector Layer to the Project Registry
        QgsProject::instance()->addMapLayer(mypLayer4, true);

        mpMapCanvas->setExtent(mypLayer4->extent());

        layers.clear();
        layers.append(mypLayer4);

        mpMapCanvas->setMapTool(mpClickPoint);
    }
    else{
        layers.removeOne(ptrLayer4);
        if (layers.isEmpty() == true){
            mpMapCanvas->unsetMapTool(mpClickPoint);
        }
    }
    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);
}
