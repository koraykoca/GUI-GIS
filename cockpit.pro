QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    infogeneral.cpp \

HEADERS += \
    mainwindow.h \
    map.h \
    infogeneral.h \

FORMS += \
    mainwindow.ui \
    mainwindowbase.ui

RESOURCES += \
    resources.qrc

TEMPLATE = app
TARGET = Cpp_GUI

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
