#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    layoutMap = new QVBoxLayout();
    map = new Map();
    layoutMap->addWidget(map);
    ui->Map->setLayout(layoutMap);

    layoutGenInfo = new QVBoxLayout;
    clock = new InfoGeneral();
    layoutGenInfo->addWidget(clock);
    ui->analogClock->setLayout(layoutGenInfo);

    connect(map, SIGNAL(coordChanged(QgsPointXY)), this, SLOT(printCoord(QgsPointXY)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete layoutMap;
    delete map;
    delete clock;
    delete layoutGenInfo;
}

void MainWindow::printCoord(QgsPointXY point){
    ui->textBrowser_4->setText(QString::number(point.y(), 'f', 4) + " " + QString::number(point.x(), 'f', 4));
}
