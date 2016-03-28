SOURCES += \
    main.cpp \
    Test.cpp

QT  += network

INCLUDEPATH += ../VirtinV4/include
INCLUDEPATH += ../GenLib/include/

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE += -std=c++11

CONFIG(debug, debug|release) {
    LIBS += ../build-GenLib-Desktop-Debug/libGenLib.a
    LIBS += ../build-VirtinV4-Desktop-Debug/libVirtinV4.a
}
CONFIG(release, debug|release) {
    LIBS += ../build-GenLib-Desktop-Release/libGenLib.a
    LIBS += ../build-VirtinV4-Desktop-Release/libVirtinV4.a
}

HEADERS += \
    Test.hpp
