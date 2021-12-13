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
}
