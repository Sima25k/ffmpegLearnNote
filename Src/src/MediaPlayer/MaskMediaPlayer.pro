QT += core opengl gui multimedia widgets openglextensions

QMAKE_CXXFLAGS += -std=c++11 -g

TARGET = MaskMediaPlayer
TEMPLATE = app

SOURCES += main.cpp\
	XVideoWidget.cpp \
	XVideoThread.cpp\
	XSlider.cpp \
	XResample.cpp \
	XPlay2.cpp \
	XDemuxThread.cpp \
	XAudioPlay.cpp \
	XAudioThread.cpp \
	XAudioThread.cpp \
	XDecode.cpp \
	XAudioThread.cpp \
	XDecodeThread.cpp \
	XDemux.cpp


HEADERS  += IVideoCall.h \
	XAudioPlay.h \
	XAudioThread.h \
	XDecode.h \
	XDecodeThread.h \
	XDemux.h \
	XDemuxThread.h \
	XResample.h \
	XVideoThread.h \
	XPlay2.h \
	XSlider.h \
	XVideoWidget.h

FORMS += ./XPlay2.ui
RESOURCES += XPlay2.qrc

DESTDIR = $$PWD/../../bin/win32
LIBS += -L$$PWD/../../lib/win32
INCLUDEPATH += $$PWD/../../include


