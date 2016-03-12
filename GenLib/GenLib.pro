
QT       -= core gui

TARGET = GenLib
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += ../VirtinV4/include
INCLUDEPATH += include/

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

QMAKE_CXXFLAGS_RELEASE *= -O3

CONFIG(debug, debug|release) {
    LIBS += ../build-VirtinV4-Desktop-Debug/libVirtinV4.a
}
CONFIG(release, debug|release) {
    LIBS += ../build-VirtinV4-Desktop-Release/libVirtinV4.a
}

LIBS += -lboost_thread

SOURCES += \
    Cell/Module.cpp \
    Cell/CellClass.cpp \
    Cell/Brain.cpp \
    Decriptor/Decriptor.cpp \
    Decriptor/DrecriptorManager.cpp \
    Decriptor/ExecDecriptor.cpp \
    Decriptor/LineDecriptor.cpp \
    Cell/Skeleton.cpp \
    Object/SignalManager.cpp \
    Object/Object.cpp \
    Object/Movable.cpp \
    Decriptor/Chanel.cpp \
    Decriptor/ChanPropriety.cpp \
    Object/ObjectMap.cpp \
    Map/ClassCase.cpp \
    Map/ClassMap.cpp \
    Map/LnkCase.cpp \
    Map/MapController.cpp \
    Object/MovableLine.cpp \
    Network/Sender.cpp \
    Network/Receiver.cpp

HEADERS += \
    include/Cell/Module.hpp \
    include/Cell/CellClass.hpp \
    include/Cell/Brain.hpp \
    include/Cell/Skeleton.hpp \
    include/Decriptor/LineDecrip.hpp \
    include/Decriptor/Decriptor.hpp \
    include/Decriptor/DecriptorManager.hpp \
    include/Decriptor/Opt.hpp \
    include/Object/Signal.hpp \
    include/Object/Object.hpp \
    include/Object/Movable.hpp \
    include/Decriptor/chanel.hpp \
    include/Decriptor/ChanelPropriety.hpp \
    include/Object/ObjectMap.hpp \
    include/Map/ClassMap.hpp \
    include/Map/LnkCase.hpp \
    include/Map/ClassCase.hpp \
    include/Map/MapController.hpp \
    include/Object/MovableLine.hpp \
    include/Monitor.hpp \
    include/Network/Sender.hpp \
    include/Network/Receiver.hpp \
    include/Network/Package.hpp
