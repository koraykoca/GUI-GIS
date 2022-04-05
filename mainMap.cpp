// Qt includes

#include <QApplication>
#include <map.h>
#include <QString>

#include <QMessageBox>
#include <QtDebug>

// QGIS Includes
#include <qgsapplication.h>

int main(int argc, char **argv)
{
    // Start the Application
    QgsApplication app(argc, argv, true);

    Map* map = new Map();
    map->show();
    // Start the Application Event Loop
    return app.exec();
}
