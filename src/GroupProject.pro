QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG   += console

INCLUDEPATH += C:\Users\lehuy\Documents\Map-Reduce-USTH-M1-2019\boost_1_66_0
INCLUDEPATH += C:\Users\lehuy\Documents\Map-Reduce-USTH-M1-2019\eigen-3.3.7


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrayexperiment.cpp \
    arraygenerator.cpp \
    csvfile.cpp \
    main.cpp \
    mainwindow.cpp \
    matrixexperiment.cpp \
    matrixgenerator.cpp \
    parserwrapper.cpp \
    randomgenerator.cpp \
    utils.cpp

HEADERS += \
    arrayexperiment.h \
    arraygenerator.h \
    basedatatype.h \
    baseexperiment.h \
    csvfile.h \
    NormalDistribution.h \
    distribution.h \
    exponentialdistribution.h \
    ifloat.h \
    mainwindow.h \
    matrix.h \
    matrixexperiment.h \
    matrixgenerator.h \
    numerical.h \
    parser.h \
    parserwrapper.h \
    randomgenerator.h \
    uniformdistribution.h \
    utils.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
