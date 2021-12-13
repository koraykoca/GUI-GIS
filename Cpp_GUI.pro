SOURCES += \
    main.cpp

HEADERS += \
    main.h

TEMPLATE = app
TARGET = GUI

QT += core gui xml

CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QGIS_DIR = /home/koray/dev/cpp/QGIS

LIBS += -L/$${QGIS_DIR}/build-master-qtcreator/output/lib -lqgis_core -lqgis_gui -lqgis_app

DEFINES += CORE_EXPORT= GUI_EXPORT=


