TEMPLATE = app
TARGET = PFE

#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg

QMAKE_CXXFLAGS_RELEASE	+= -march=native \
                            -O3

INCLUDEPATH += ./third-party/GLTools/

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
    triangle.h \
    ./third-party/GLTools/GLTools.h \
    ./third-party/GLTools/GLBatch.h \
    ./third-party/GLTools/GLTriangleBatch.h  \
    ./third-party/GLTools/GLShaderManager.h

SOURCES += utils.cpp \
    voxel.cpp \
    cloud.cpp \
    renderer.cpp \
    main.cpp \
    pfe.cpp \
    octree.cpp \
    blob.cpp \
    mc.cpp \
    triangle.cpp \
    ./third-party/GLTools/GLTools.cpp \
    ./third-party/GLTools/GLBatch.cpp \
    ./third-party/GLTools/GLTriangleBatch.cpp \
    ./third-party/GLTools/GLShaderManager.cpp

FORMS += pfe.ui
RESOURCES += 
LIBS += -lGLU \
    -lGLEW \
    -lglut












