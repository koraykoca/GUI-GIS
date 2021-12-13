// Qt includes
#include <QString>
#include <QApplication>               // create QApplication instance

// QGIS Includes
#include <qgsapplication.h>           // QgsApplication instead of Qt's QApplication to get some added benifits of various static methods that can be used to locate library paths and so on.
#include <qgsproviderregistry.h>      // The provider registry is a singleton that keeps track of vector data provider plugins. It does all the work for you of loading the plugins and so on.
#include <qgssinglesymbolrenderer.h>  // most basic symbology class. It renders points, lines or polygons in a single colour. Every vector layer must have a symbology associated with it.
#include <qgsproject.h>
#include <qgsvectorlayer.h>           // The vector layer class inherits from maplayer and extends it to include specialist functionality for vector data.
#include <qgsmapcanvas.h>             // the nub of the matter. Its the drawable widget that our map will be drawn onto.
#include <qgssymbol.h>

int main(int argc, char **argv)
{
 // Start the Application
 QgsApplication app (argc, argv, true);

 // define some variables
 QString myPluginsDir = "/home/koray/dev/cpp/QGIS/build-master-qtcreator/output/lib/qgis";
 QString myLayerPath  = "/home/koray/work-unibw/ldbv_bayern/ATKIS_DGM5_Bereich_Gauting_Luftfahrttechnik_Luft_und_Raumfahrttechnik/Vektordaten_ATKIS_UTM32/601_DLM25_clip_n/geb01_f.shp";
 QString myLayerBaseName = "geb01_f";  // point to the shapefile
 QString myProviderName = "ogr";       // it tells qgis which data provider to use to load the file

 // Instantiate Provider Registry
 QgsProviderRegistry::instance(myPluginsDir);  // Its a singleton class so we use the static instance call and pass it the provider lib search path. As it initialises it will scan this path for provider libs.

 // create a maplayer instance / create the layer object
 QgsVectorLayer *mypLayer = new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);

 QgsSingleSymbolRenderer *mypRenderer = new QgsSingleSymbolRenderer(QgsSymbol::defaultSymbol(mypLayer->geometryType()));

 QList <QgsMapLayer*> myLayerSet;

 mypLayer->setRenderer(mypRenderer);
 if (mypLayer->isValid())
 {
   qDebug("Layer is valid");
 }
 else
 {
   qDebug("Layer is NOT valid");
 }

 QgsProject::instance()->addMapLayer(mypLayer);

 myLayerSet.append(mypLayer);

 QgsMapCanvas *mapcanvas = new QgsMapCanvas();
 mapcanvas->setExtent(mypLayer->extent());
 mapcanvas->enableAntiAliasing(true);
 mapcanvas->setCanvasColor(QColor(255, 255, 255));
 mapcanvas->freeze(false);
 mapcanvas->setWindowTitle("GUI MAP");

 mapcanvas->setLayers(myLayerSet);
 mapcanvas->setVisible(true);
 mapcanvas->refresh();

 return app.exec();
}
