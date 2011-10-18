TEMPLATE = app
TARGET = PFE

QMAKE_CXXFLAGS_RELEASE	= -march=native

QT += core \
    gui \
    opengl
HEADERS += utils.h \
    voxel.h \
    cloud.h \
    renderer.h \
    pfe.h \
    octree.h \
    blob.h \
    mc.h \
    triangle.h
SOURCES += utils.cpp \
    voxel.cpp \
    cloud.cpp \
    renderer.cpp \
    main.cpp \
    pfe.cpp \
    octree.cpp \
    blob.cpp \
    mc.cpp \
    triangle.cpp
FORMS += pfe.ui
RESOURCES += 
LIBS += -lGLU \
    -lGLEW \
    -lglut












