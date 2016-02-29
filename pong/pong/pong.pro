SOURCES += \
    main.cpp \
    Player.cpp \
    IAPlayer.cpp \
    RealPlayer.cpp \
    ../../GenLibTester/BrainView.cpp \
    Board.cpp \
    Ball.cpp

INCLUDEPATH += ../../VirtinV4/include
INCLUDEPATH += ../../GenLib/include/

CONFIG(debug, debug|release) {
    LIBS += ../../build-GenLib-Desktop-Debug/libGenLib.a
    LIBS += ../../build-VirtinV4-Desktop-Debug/libVirtinV4.a
}
CONFIG(release, debug|release) {
    LIBS += ../../build-GenLib-Desktop-Release/libGenLib.a
    LIBS += ../../build-VirtinV4-Desktop-Release/libVirtinV4.a
}

LIBS += /usr/lib/x86_64-linux-gnu/libboost_thread.a
LIBS += /usr/lib/x86_64-linux-gnu/libboost_system.a
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lX11

HEADERS += \
    include/Player.hpp \
    include/IA.hpp \
    include/RealPlayer.hpp \
    include/Board.hpp \
    include/Ball.hpp
