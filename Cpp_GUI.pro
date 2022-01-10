SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    main.h \
    mainwindow.h

TEMPLATE = app
TARGET = GUI

QT += core gui xml

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QGIS_DIR = /home/koray/dev/cpp/QGIS
BUILD_DIR = /home/koray/dev/cpp/QGIS/build-master-qtcreator

LIBS += -L$${QGIS_DIR}/output/lib -lqgis_app -lqgis_core -lqgis_gui

INCLUDEPATH += $$QGIS_DIR
INCLUDEPATH += $$QGIS_DIR/src/core
INCLUDEPATH += $$QGIS_DIR/src/core/settings
INCLUDEPATH += $$QGIS_DIR/src/core/providers
INCLUDEPATH += $$QGIS_DIR/src/core/geometry
INCLUDEPATH += $$QGIS_DIR/src/core/proj
INCLUDEPATH += $$QGIS_DIR/src/core/metadata
INCLUDEPATH += $$QGIS_DIR/src/core/symbology
INCLUDEPATH += $$QGIS_DIR/external/nlohmann
INCLUDEPATH += $$QGIS_DIR/src/core/expression
INCLUDEPATH += $$QGIS_DIR/src/core/project
INCLUDEPATH += $$QGIS_DIR/src/core/vector
INCLUDEPATH += $$QGIS_DIR/src/core/editform
INCLUDEPATH += $$QGIS_DIR/src/gui
INCLUDEPATH += $$QGIS_DIR/src/core/labeling
INCLUDEPATH += $$QGIS_DIR/src/core/raster
INCLUDEPATH += $$QGIS_DIR/src/core/layertree
INCLUDEPATH += $$QGIS_DIR/src/core/textrenderer

DEFINES += CORE_EXPORT= GUI_EXPORT=

FORMS += \
    mainwindowbase.ui
