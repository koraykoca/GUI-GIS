# CPP_GUI
C++ Graphical User Interface (GUI) Programming in Qt Creator using QGIS3 C++ API as an embedded mapping component. 
Developing a standalone Qt 5.12.8 application using QGIS3 C++ API.

## Build and Running Steps
- Clone the branch "release-3_24" from QGIS official repository:
    - https://github.com/qgis/QGIS/tree/release-3_24

- Set up QGIS build environment. Following links are helpful:
    - https://github.com/qgis/QGIS/blob/master/INSTALL.md
    - https://www.youtube.com/watch?v=Nn3zt6IwphY&list=PLhZmjLdJAZWwTZIWKo5cZfKHW-606qw7p

- Clone this repo and open the project file(.pro) in Qt Creator. Update path variable values accordingly in cockpit.pro and map.cpp files. 
    - The path variables in cockpit.pro file are:
        - QGIS_DIR 
        - BUILD_DIR

    - The path variables in map.cpp file are:
        - QString myPluginsDir
        - QString path
        - QString myLayerPath2
        - QString myLayerPath3
        - QString myLayerPath4 

- In Qt Creator go to Project/Build Settings and configure your build path. Then specify your KIT settings like Qt-Version, Compiler etc. Currently, QGIS builds are only supported on version 5 of the Qt libraries. Thus, select Qt version 5.
Finally compile and run the project in Qt Creator. 
