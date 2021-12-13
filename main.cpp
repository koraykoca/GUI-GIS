// Qt includes
#include <QString>
#include <QMessageBox>
#include <QtDebug>

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
 QgsVectorLayer *vecLayer = new QgsVectorLayer(myLayerPath, myLayerBaseName, myProviderName);

 QgsSingleSymbolRenderer *vecRenderer = new QgsSingleSymbolRenderer(QgsSymbol::defaultSymbol(vecLayer->geometryType()));

 QList <QgsMapLayer*> myLayerSet;

 vecLayer->setRenderer(vecRenderer);

 if (vecLayer->isValid())
   qDebug() << "Layer is valid";  // or qDebug("Layer is valid");
 else
   QMessageBox::critical(NULL, "error", "Layer is NOT valid");

 // Add Vector Layer to the Layer Registry
 QgsProject::instance()->addMapLayer(vecLayer);

 // Add Layer to the Layer Set
 myLayerSet.append(vecLayer);

 QgsMapCanvas *mapcanvas = new QgsMapCanvas();
 mapcanvas->setExtent(vecLayer->extent());
 mapcanvas->enableAntiAliasing(true);
 mapcanvas->setCanvasColor(QColor(255, 255, 255));
 mapcanvas->freeze(false);
 mapcanvas->setWindowTitle("GUI GIS DATA");

 // Set the Map Canvas Layer Set
 mapcanvas->setLayers(myLayerSet);
 mapcanvas->setVisible(true);
 mapcanvas->refresh();

 return app.exec();
}
