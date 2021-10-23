TARGET = stack
CONFIG += c++14
QT += core widgets gui dbus

SOURCES += myapp.cpp myvision.cpp myengine.cpp main.cpp myresultimage.cpp customresultimage.cpp
HEADERS += myapp.h myvision.h myengine.h myresultimage.h customresultimage.h
DEFINES += 
DISTFILES += license.txt qtlogging.ini

NXT_SDK = 2.3.0
AVATAR = avatar.png
MANIFEST = manifest.json
TRANSLATION = translation.json
LICENSE = license.txt

DEPLOYFILES += $$PWD/qtlogging.ini


QMAKE_CFLAGS += ${QMAKE_CFLAGS} -mtune=cortex-a53 -march=armv8-a+simd
QMAKE_CXXFLAGS += ${QMAKE_CXXFLAGS} -mtune=cortex-a53 -march=armv8-a+simd




include($(NXT_FRAMEWORK)/qmake/nxt_rio.pri)
