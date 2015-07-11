
QT += gui core
TEMPLATE = app

TARGET = Tester

INCLUDEPATH += ../../Virtin/include
INCLUDEPATH += ../../VirtinV4/include
INCLUDEPATH += ../VirtualMachineV1/
INCLUDEPATH += ../VirtualMachineV1/include

LIBS += ../../build-VirtinV4-Desktop-Debug/libVirtinV4.a -lboost_thread -lboost_system

SOURCES += \
    main.cpp \
    ../../Virtin/Plugin.cpp

HEADERS += \
    ../../Virtin/include/Plugin.hpp
