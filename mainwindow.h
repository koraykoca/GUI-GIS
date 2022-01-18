#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QGIS Includes
#include <qgsmapcanvas.h>
#include <qgsmaptool.h>
#include <qgsmaptoolemitpoint.h>

//QT Includes
#include <QtGui>
#include <QWidget>
#include <qtoolbar.h>
#include <QVBoxLayout>
#include <QObject>

//Local Includes
#include <ui_mainwindowbase.h>

class MainWindow : public QMainWindow, private Ui::MainWindowBase
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0, Qt::WindowFlags fl = 0 );
    ~MainWindow();
    QList <QgsMapLayer *> layers;

public slots:
    void zoomInMode();
    void zoomOutMode();
    void panMode();
    void addLayer1();
    void addLayer2();
    void addLayer3();
    void showCoord(QgsPointXY);

private:
    QgsMapCanvas * mpMapCanvas;
    QVBoxLayout  * mpLayout;
    QToolBar * mpMapToolBar;
    QgsMapTool * mpPanTool;
    QgsMapTool * mpZoomInTool;
    QgsMapTool * mpZoomOutTool;
    QgsMapTool * mpCoordTool;
    QgsMapToolEmitPoint *mpClickPoint;

};

#endif // MAINWINDOW_H
