TEMPLATE = app
TARGET = PFE
QT += core \
    gui \
    opengl
HEADERS += utils.h \
    voxel.h \
    cloud.h \
    renderer.h \
    pfe.h \
    octree.h
SOURCES += utils.cpp \
    voxel.cpp \
    cloud.cpp \
    renderer.cpp \
    main.cpp \
    pfe.cpp \
    octree.cpp
FORMS += pfe.ui
RESOURCES += 
LIBS += -lGLU \
    -lGLEW
