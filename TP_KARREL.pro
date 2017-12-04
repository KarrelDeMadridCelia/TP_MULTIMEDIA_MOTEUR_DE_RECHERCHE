#-------------------------------------------------
#
# Project created by QtCreator 2017-11-27T09:40:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP_KARREL
TEMPLATE = app


INCLUDEPATH += /usr/local/include/
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

SOURCES += main.cpp\
        indexation.cpp \
    fonctions.cpp \
    moteur_de_recherche.cpp

HEADERS  += indexation.h \
    moteur_de_recherche.h

FORMS    += indexation.ui \
    moteur_de_recherche.ui
