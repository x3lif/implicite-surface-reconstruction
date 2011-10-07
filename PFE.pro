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
    octree.h \
    blob.h
SOURCES += utils.cpp \
    voxel.cpp \
    cloud.cpp \
    renderer.cpp \
    main.cpp \
    pfe.cpp \
    octree.cpp \
    blob.cpp
FORMS += pfe.ui
RESOURCES += 
LIBS += -lGLU \
    -lGLEW \
    -lglut








