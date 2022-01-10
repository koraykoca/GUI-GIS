QT += core gui xml  # includes core, gui, and xml libraries

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  # widget application

TEMPLATE = app  # GUI application
TARGET = Cpp_GUI  # name of the project

SOURCES += main.cpp

HEADERS += main.h

FORMS +=

QGIS_DIR = /home/koray/dev/cpp/QGIS

LIBS += -L/$${QGIS_DIR}/build-master-qtcreator/output/lib -lqgis_core -lqgis_gui -lqgis_app

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
