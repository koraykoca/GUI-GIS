#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QGIS Includes
#include <qgsmapcanvas.h>
#include <qgsmaptool.h>
#include <qgsmaptoolemitpoint.h>
#include "qgscoordinatereferencesystem.h"

//QT Includes
#include <QtGui>
//#include <QWidget>
#include <qtoolbar.h>
#include <QVBoxLayout>
#include <QObject>
#include <QtCore>
#include <qtoolbutton.h>

//Local Includes
#include <ui_mainwindowbase.h>

extern QString ProviderName;

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
    void addLayer1(QString, QString, QString);
    void addLayer2();
    void addLayer3();
    void addLayer4();
    void showCoord(QgsPointXY);
    void selectCoord(QgsPointXY);
<<<<<<< HEAD
    void showContextMenu(const QPoint&);
=======
>>>>>>> 08d088796c5ffe43492f4760d74a2c1f3b101ecb

protected:
    void dragEnterEvent(QDragEnterEvent *) override;
    void dropEvent(QDropEvent *) override;
    void dragMoveEvent(QDragMoveEvent *) override;
    void dragLeaveEvent(QDragLeaveEvent *) override;
<<<<<<< HEAD
    // QMenu* createPopupMenu() override;
=======
>>>>>>> 08d088796c5ffe43492f4760d74a2c1f3b101ecb

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
    QgsVectorLayer * ptrLayer1 = nullptr;
    QgsVectorLayer * ptrLayer2 = nullptr;
    QgsVectorLayer * ptrLayer3 = nullptr;
    QgsVectorLayer * ptrLayer4 = nullptr;
    QToolButton* toolButton;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * icon;
    QPointF pointf;
<<<<<<< HEAD
    qreal x;
    qreal y;
=======
>>>>>>> 08d088796c5ffe43492f4760d74a2c1f3b101ecb

signals:
    void changed(const QMimeData *mimeData = nullptr);
};

#endif // MAINWINDOW_H
