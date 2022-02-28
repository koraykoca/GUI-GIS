#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QGIS Includes
#include <qgsmapcanvas.h>
#include <qgsmaptool.h>
#include <qgsmaptoolemitpoint.h>
#include "qgscoordinatereferencesystem.h"
#include <qgsvertexmarker.h>

#include <qgslabeling.h>
#include <qgslabelfeature.h>
#include <qgsfield.h>

//QT Includes
#include <QtGui>
#include <QWidget>
#include <qtoolbar.h>
#include <QVBoxLayout>
#include <QObject>
#include <QLabel>

//Local Includes
#include <ui_mainwindowbase.h>


class MainWindow : public QMainWindow, private Ui::MainWindowBase
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::WindowFlags());
    ~MainWindow();
    QList <QgsMapLayer *> layers;

public slots:
    void zoomInMode();
    void zoomOutMode();
    void panMode();
    void addLayer1(QString, QString);
    void addLayer2();
    void addLayer3();
    void addLayer4();
    void showCoord(QgsPointXY);
    void selectCoord(QgsPointXY);
    void putMarker();

protected:
    void dragEnterEvent(QDragEnterEvent *) override;
    void dropEvent(QDropEvent *) override;
    void dragMoveEvent(QDragMoveEvent *) override;
    void dragLeaveEvent(QDragLeaveEvent *) override;

private:
    QgsMapCanvas * mpMapCanvas;
    QVBoxLayout  * mpLayout;
    QToolBar * mpMapToolBar;
    QgsMapTool * mpPanTool;
    QgsMapTool * mpZoomInTool;
    QgsMapTool * mpZoomOutTool;
    QgsMapTool * mpCoordTool;
    QgsMapToolEmitPoint * mpClickPoint;
    QgsCoordinateReferenceSystem crsSrc;
    QgsCoordinateReferenceSystem crsDest;
    QgsCoordinateTransform mTransform;
    QLabel *marker;
    QgsVectorLayer * ptrLayer1 = nullptr;
    QgsVectorLayer * ptrLayer2 = nullptr;
    QgsVectorLayer * ptrLayer3 = nullptr;
    QgsVectorLayer * ptrLayer4 = nullptr;

    QPainter * painter;

signals:
    void changed(const QMimeData *mimeData = nullptr);
};

#endif // MAINWINDOW_H
