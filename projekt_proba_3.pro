TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}
SOURCES += \
        bohater.cpp \
        bonus.cpp \
        main.cpp \
        platforma.cpp \
        pocisk.cpp \
        przeciwnik.cpp

HEADERS += \
    bohater.h \
    bonus.h \
    platforma.h \
    pocisk.h \
    przeciwnik.h \
    wczytywanie.hpp \
    dane_platformy.hpp \
    difficulty_level.hpp \
    difficulty_levels.cfg \
    start_map.cfg
