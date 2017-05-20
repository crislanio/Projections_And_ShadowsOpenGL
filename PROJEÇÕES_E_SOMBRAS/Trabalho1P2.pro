TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

INCLUDEPATH += bib
INCLUDEPATH += gui_glut
INCLUDEPATH += user

DEFINES += USE_SDL
LIBS += -lglut -l3ds -lGLU -lGL -lm -lSDL -lSDL_image #-lgsl
#LIBS += -lGL -lGLU -lglut

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/Vetor3D.h \
    bib/model3ds.h \
    bib/Objeto.h \
    modelos/Banco.h \
    modelos/Placa.h \
    modelos/Cerca.h \
    modelos/Arvore.h \
    bib/stanfordbunny.h \
    gui_glut/extra.h \
    gui_glut/gui.h

SOURCES += \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Objeto.cpp \
    bib/Vetor3D.cpp \
    main.cpp \
    modelos/Banco.cpp \
    modelos/Arvore.cpp \
    modelos/Cerca.cpp \
    modelos/Placa.cpp \
    bib/model3ds.cpp \
    gui_glut/extra.cpp \
    gui_glut/gui.cpp

