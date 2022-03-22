#include "mainwindow.h"
#include "map.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto layout = new QVBoxLayout();
    Map* map = new Map();
    layout->addWidget(map);
    ui->Map->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

