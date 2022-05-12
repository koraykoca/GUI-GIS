# CPP_GUI
Programming Graphical User Interface (GUI) in Qt Creator using QGIS API as an embedded mapping component. Developing a standalone QT 5.12.8 application using QGIS 3.23 C++ API.

## Build Steps
First, you need to set up QGIS build environment. Following links are helpful: 
- https://github.com/qgis/QGIS/blob/master/INSTALL.md
- https://www.youtube.com/watch?v=Nn3zt6IwphY&list=PLhZmjLdJAZWwTZIWKo5cZfKHW-606qw7p

Then clone this repo and open the project file(.pro) in Qt Creator. Update path variable values accordingly in cockpit.pro and map.cpp files. 
The path variables in cockpit.pro file are:
- QGIS_DIR 
- BUILD_DIR

The path variables in map.cpp file are:
- QString myPluginsDir
- QString path
- QString myLayerPath2
- QString myLayerPath3
- QString myLayerPath4 

In Project/Build Settings, configure your build path. Then compile and run the project in Qt Creator. 
