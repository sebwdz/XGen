SOURCES += \
    main.cpp \
    Snake.cpp \
    Map.cpp \
    Window.cpp

INCLUDEPATH += ../../VirtinV4/include
INCLUDEPATH += ../../GenLib/include/

QT  += network

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE += -std=c++11

CONFIG(debug, debug|release) {
    LIBS += ../../build-GenLib-Desktop-Debug/libGenLib.a
    LIBS += ../../build-VirtinV4-Desktop-Debug/libVirtinV4.a
}
CONFIG(release, debug|release) {
    LIBS += ../../build-GenLib-Desktop-Release/libGenLib.a
    LIBS += ../../build-VirtinV4-Desktop-Release/libVirtinV4.a
}

LIBS += -lsfml-graphics -lsfml-system -lsfml-window

HEADERS += \
    include/Snake.hpp \
    include/Map.hpp \
    include/Window.hpp
