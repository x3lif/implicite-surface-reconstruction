TEMPLATE = app
TARGET = PFE

#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg
#QMAKE_CXXFLAGS_DEBUG    += -Wall -Werror
#QMAKE_CXXFLAGS_RELEASE	+= -march=native \
#                            -O3 \ -Werror


DESTDIR = bin
OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
UI_DIR = $${DESTDIR}/.ui
RCC_DIR = $${DESTDIR}/.rcc


INCLUDEPATH += ./third-party/GLTools/ \
		./include

QT += core \
    gui \
    opengl
HEADERS += include/utils.h \
    include/voxel.h \
    include/cloud.h \
    include/renderer.h \
    include/pfe.h \
    include/octree.h \
    include/blob.h \
    include/mc.h \
    include/triangle.h \
    ./third-party/GLTools/GLTools.h \
    ./third-party/GLTools/GLBatch.h \
    ./third-party/GLTools/GLTriangleBatch.h  \
    ./third-party/GLTools/GLShaderManager.h  \
    ./third-party/GLTools/GLBatchBase.h \
    ./third-party/GLTools/math3D.h \
    ./third-party/GLTools/GLFrame.h \
    ./third-party/GLTools/GLGeometryTransform.h \
    ./third-party/GLTools/GLMatrixStack.h   \
    ./third-party/GLTools/GLFrustum.h \
    ./third-party/GLTools/math3d.h


SOURCES += src/utils.cpp \
    src/voxel.cpp \
    src/cloud.cpp \
    src/renderer.cpp \
    src/main.cpp \
    src/pfe.cpp \
    src/octree.cpp \
    src/blob.cpp \
    src/mc.cpp \
    src/triangle.cpp \
    ./third-party/GLTools/GLTools.cpp \
    ./third-party/GLTools/GLBatch.cpp \
    ./third-party/GLTools/GLTriangleBatch.cpp \
    ./third-party/GLTools/GLShaderManager.cpp \
    ./third-party/GLTools/math3d.cpp

FORMS += ui/pfe.ui
RESOURCES += 
LIBS += -lGLU \
    -lGLEW \
    -lglut












