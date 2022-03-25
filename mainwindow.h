#ifndef MAINWINDOW_H
#define MAINWINDOW_H

<<<<<<< HEAD
//QGIS Includes
#include <qgsmapcanvas.h>
#include <qgsmaptool.h>
#include <qgsmaptoolemitpoint.h>
#include "qgscoordinatereferencesystem.h"
#include <qgsmarkersymbol.h>
#include <qgsmarkersymbollayer.h>

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

// MainWindow class definition
class MainWindow : public QMainWindow, private Ui::MainWindowBase
=======
#include <QMainWindow>
#include <QVBoxLayout>
#include "map.h"
#include "infogeneral.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
>>>>>>> cockpit
{
    Q_OBJECT

public:
<<<<<<< HEAD
    MainWindow(QWidget* parent = nullptr, Qt::WindowFlags fl = Qt::WindowFlags());
    ~MainWindow();
    QList <QgsMapLayer *> layers;
    QList <QgsFeature> features;

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
    void showContextMenu(const QPoint&); // create slot for opening context menu
    void set_checks(QAction*);
    void dropMark();
    void mouseEvent(QgsPointXY, Qt::MouseButton);
    void createLayer(QString, QgsPointXY);

protected:
    // reimplement some functions
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
    QgsVectorLayer * ptrLayer1 = nullptr;
    QgsVectorLayer * ptrLayer2 = nullptr;
    QgsVectorLayer * ptrLayer3 = nullptr;
    QgsVectorLayer * ptrLayer4 = nullptr;
    QgsVectorLayer * mypLayer2;
    QToolButton* toolButton;
    QGraphicsScene * scene;
    QGraphicsPixmapItem * icon;
    QPointF pointf;
    qreal x;
    qreal y;
    QPainter* painter;
    QSize size;
    QgsSymbol *symbol;
    QgsMarkerSymbol* symbol2;

signals:
    void changed(const QMimeData *mimeData = nullptr);
};

#endif // MAINWINDOW_H
=======
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout* layoutMap;
    Map* map;
    InfoGeneral* clock;
    QVBoxLayout* layoutGenInfo;
};

#endif // MAINWINDOW_H


>>>>>>> cockpit
