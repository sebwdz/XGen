SOURCES += \
    main.cpp

INCLUDEPATH += ../GenLib/include
INCLUDEPATH += ../VirtinV4/include

LIBS += ../build-VirtinV4-Desktop-Release/libVirtinV4.a
LIBS += ../build-GenLib-Desktop-Release/libGenLib.a

QT += network
