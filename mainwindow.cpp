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

#include <qlist.h>
#include <qpoint.h>
#include <QGraphicsItem>

QString ProviderName = "ogr";

//MainWindow class Implementation
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

    mpMapCanvas->setContextMenuPolicy(Qt::CustomContextMenu);  // set context menu policy to custom

    scene = mpMapCanvas->scene();

    QPixmap pixmap = QPixmap(":/mapMarker.png");
    icon = new QGraphicsPixmapItem(pixmap);
    scene->addItem(icon);
    //qDebug() << "icon x:" << icon->x() << "icon y:" << icon->y() << icon->boundingRect();
    QSize size = pixmap.size();
    QTransform transform;
    transform.translate(-size.width()/2, -size.height());
    icon->setTransform(transform);
    //icon->setFlag(QGraphicsPixmapItem::ItemIgnoresTransformations,true);
    icon->hide();

    //pixmapc = pixmap.transformed(QTransform().rotate(12), Qt::SmoothTransformation);

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

    setAcceptDrops(true);
    mpMapCanvas->setAcceptDrops(true);

    //create the action behaviours
    connect(mpActionPan, SIGNAL(triggered()), this, SLOT(panMode()));
    connect(mpActionZoomIn, SIGNAL(triggered()), this, SLOT(zoomInMode()));
    connect(mpActionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOutMode()));
    connect(actionMap_1, SIGNAL(triggered()), this, SLOT(addLayer1(QString,QString,QString)));
    connect(actionMap_2, SIGNAL(triggered()), this, SLOT(addLayer2()));
    connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(addLayer1(QString,QString,QString)));
    connect(checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(addLayer2()));
    connect(checkBox_3, SIGNAL(stateChanged(int)), this, SLOT(addLayer3()));
    connect(checkBox_4, SIGNAL(stateChanged(int)), this, SLOT(addLayer4()));
    //connect(mpClickPoint, SIGNAL(canvasClicked(QgsPointXY,Qt::MouseButton)), this, SLOT(selectCoord(QgsPointXY)));
    connect(mpClickPoint, SIGNAL(canvasClicked(QgsPointXY,Qt::MouseButton)), this, SLOT(mouseEvent(QgsPointXY,Qt::MouseButton)));
    connect(mpMapCanvas, SIGNAL(xyCoordinates(QgsPointXY)), this, SLOT(showCoord(QgsPointXY)));
    connect(mpMapCanvas, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(mpMapCanvas, SIGNAL(), this, SLOT(showContextMenu(QPoint)));

    toolButton = new QToolButton();  // local variable
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

    setAcceptDrops(true);
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
  delete mpClickPoint;
  delete toolButton;
  delete icon;
  delete mypLayer2;
}

void MainWindow::showContextMenu(const QPoint &pos){
    pointf = QPointF(pos.x() , pos.y());

    QMenu menu;  // create menu and insert actions
    menu.addAction("Mark Drop", this, SLOT(dropMark()));
    menu.addAction("Zoom In", this, SLOT(zoomInMode()));
    menu.addAction("Zoom Out", this, SLOT(zoomOutMode()));
    menu.addAction("Pan", this, SLOT(panMode()));
    connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(set_checks(QAction*)));

    QPoint globalPos = mpMapCanvas->mapToGlobal(pos); // handle global position
    menu.exec(globalPos);  // menu.exec(QCursor::pos());  // show context menu at handling position
}

void MainWindow::set_checks(QAction* action){
    // to get which QActions triggered

    if (action->text() == "Zoom In"){
        mpActionZoomIn->setChecked(true);
        mpMapCanvas->setMapTool(mpZoomInTool);
    }
    if (action->text() == "Zoom Out"){
        mpActionZoomOut->setChecked(true);
        mpMapCanvas->setMapTool(mpZoomOutTool);
    }
    if (action->text() == "Pan"){
        mpActionPan->setChecked(true);
        mpMapCanvas->setMapTool(mpPanTool);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event){
    setBackgroundRole(QPalette::Highlight);
//    if (event->mimeData()->hasFormat("x-special/gnome-icon-list"))
//        event->acceptProposedAction();
    event->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event){
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event){
    const QMimeData *mimeData = event->mimeData();
    QUrl dataUrl = mimeData->urls().takeFirst();  // take url from list
    QString dataPath = dataUrl.path();  // or dataUrl.toLocalFile()
    int idx_s = dataPath.lastIndexOf('/');  // get index of last / in the path
    int idx_e = dataPath.lastIndexOf('.');  // get index of last . in the path
    QString name = dataPath.mid(idx_s + 1, idx_e - idx_s - 1);  // get the name of the file
    MainWindow::addLayer1(dataUrl.path(), name, ProviderName);
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event){
    event->accept();
}

void MainWindow::createLayer(QString type, QPointF point){
    auto vecLayer = new QgsVectorLayer(type, "temporary_points", "memory");  // create Layer
    auto layerData = vecLayer->dataProvider();
    vecLayer->startEditing();
    auto layerFtr = QgsFeature();
    layerFtr.setGeometry(QgsGeometry::fromPointXY(point + QPointF(5,5)));
    features.push_back(layerFtr);
    layerData->addFeatures(features);
    vecLayer->commitChanges();
    QgsSymbol *symbol = QgsSymbol::defaultSymbol(vecLayer->geometryType());
    symbol->setColor(QColor("#CD736C"));
    QgsSingleSymbolRenderer *vecRenderer = new QgsSingleSymbolRenderer(symbol);

    QgsProject::instance()->addMapLayer(vecLayer, true);
    vecLayer->setRenderer(vecRenderer);

    qDebug() << "new layer added" << vecLayer->geometryType();
    layers.push_front(vecLayer);
    mpMapCanvas->setLayers(layers);
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
        //qDebug() << "SelCoo Trans" << "x: " << point_trans.x() << "y:" << point_trans.y() << '\n';
        textBrowser->setText(QString::number(point_trans.y(), 'f', 4) + " " + QString::number(point_trans.x(), 'f', 4));
    }
    else{
        textBrowser->setText(QString::number(point.y(), 'f', 4) + " " + QString::number(point.x(), 'f', 4));
    }

    x = point.x();
    y = point.y();
    mpMapCanvas->getCoordinateTransform()->transformInPlace(x, y);

    pointf = QPointF(x , y);
    //qDebug() << "SelCoo" << "x: " << pointf.x() << "y:" << pointf.y() << '\n';
}

void MainWindow::mouseEvent(QgsPointXY point, Qt::MouseButton button){
    if (button == Qt::LeftButton){
        if (layers.isEmpty() == false){
            selectCoord(point);
            dropMark();
            createLayer("Point", pointf);
        }
    }
}

void MainWindow::dropMark(){
    if (layers.isEmpty() == false){
        icon->setPos(pointf.x(), pointf.y());
        icon->show();
    }
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

void MainWindow::addLayer1(QString myLayerPath, QString myLayerBaseName, QString myProviderName)
{
//    if (layers.contains(ptrLayer4) == true){
//        layers.removeOne(ptrLayer4);
//    }

    //if (layers.contains(ptrLayer1) == false){
    if (true){

        //QString myLayerPath  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb01_f.shp";
        //myLayerPath  = "/home/unibw/dev/cpp/ldbv_bayern/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb01_f.shp";
        //myLayerBaseName = "geb01_f";
        //QString myProviderName = "ogr";

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
             icon->hide();
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

        mypLayer2 = new QgsVectorLayer(myLayerPath2, myLayerBaseName2, myProviderName);

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
            icon->hide();
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
            icon->hide();
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
            icon->hide();
        }
    }
    // Set the Map Canvas Layers
    mpMapCanvas->setLayers(layers);
}
