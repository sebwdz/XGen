SOURCES += \
    main.cpp

INCLUDEPATH += ../VirtinV4/include
INCLUDEPATH += ../GenLib/include/

CONFIG(debug, debug|release) {
    LIBS += ../build-GenLib-Desktop-Debug/libGenLib.a
    LIBS += ../build-VirtinV4-Desktop-Debug/libVirtinV4.a
}
CONFIG(release, debug|release) {
    LIBS += ../build-GenLib-Desktop-Release/libGenLib.a
    LIBS += ../build-VirtinV4-Desktop-Release/libVirtinV4.a
}

LIBS += /usr/lib/x86_64-linux-gnu/libboost_thread.so -lpthread
LIBS += /usr/lib/x86_64-linux-gnu/libboost_system.so
