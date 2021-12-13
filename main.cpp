#include <iostream>
#include <string>

// Qt includes
#include <QApplication>  // create QApplication instance
#include <QPushButton>  // base class of all Qt push buttons
#include <QWidget>   // base class of all Qt widgets

// QGIS Includes
#include <qgsapplication.h>
#include <qgsproviderregistry.h>
#include <qgssinglesymbolrenderer.h>
#include <qgsvectorlayer.h>
#include <qgsrasterlayer.h>
#include <qgsproject.h>
#include <qgsmapcanvas.h>

// QGIS Map tools
#include "qgsmaptoolzoom.h"
#include "qgsmaptoolpan.h"

int main(int argc, char **argv)
{
 QgsApplication app (argc, argv, true);

 QString uri = "crs=EPSG:3857&format&type=xyz&url=https://mt1.google.com/vt/lyrs%3Ds%26x%3D%7Bx%7D%26y%3D%7By%7D%26z%3D%7Bz%7D&zmax=19&zmin=0";

 QgsRasterLayer *rastlayer = new QgsRasterLayer(uri, "google maps", "wms");

 if (rastlayer->isValid())
    qDebug("Layer is valid");
 else
    qDebug("Layer is NOT valid");

 QgsProject::instance()->addMapLayer(rastlayer);

 QgsMapCanvas *mapcanvas = new QgsMapCanvas();
 QList<QgsMapLayer*> layers;
 layers.append(rastlayer);

 mapcanvas->setWindowTitle("MAP");
 mapcanvas->setLayers(layers);
 mapcanvas->setExtent(rastlayer->extent());
 mapcanvas->setDestinationCrs(rastlayer->crs());
 mapcanvas->show();
 return app.exec();

 /*
 QFont font ("Courier");

 QPushButton button;
 button.setText("\n\nhier ist mein erster Button!");
 button.setWindowTitle(("Hello"));
 button.setToolTip("A tooltip");
 button.setFont(font);
 button.setIcon(QIcon::fromTheme("face-smile"));
 button.show();

 return app.exec(); // it tells our QApplication instance to enter the event loop. This loop
                    // regularly checks if there are any user inputs.
*/
}
