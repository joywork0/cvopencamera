QT       += core gui multimediawidgets multimedia



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++0x

TARGET = opentest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


INCLUDEPATH += .
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/lib
#INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv4


LIBS += /usr/local/lib/libopencv_core.so\
/usr/local/lib/libopencv_highgui.so\
/usr/local/lib/libopencv_imgproc.so\
/usr/local/lib/libopencv_videoio.so\
