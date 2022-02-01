// Qt includes

#include <QApplication>
#include <mainwindow.h>
#include <QString>

#include <QMessageBox>
#include <QtDebug>

// QGIS Includes
#include <qgsapplication.h>

int main(int argc, char **argv)
{
    // Start the Application
    QgsApplication app(argc, argv, true);

    MainWindow * mypMainWindow = new MainWindow();
    mypMainWindow->show();
    // Start the Application Event Loop
    return app.exec();
}
