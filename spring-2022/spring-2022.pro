TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    State.cpp \
	../grid2d/Coord2.cpp \
    Unit.cpp \
    Monster.cpp

HEADERS += \
    State.h \
	../grid2d/Coord2.h \
    Unit.h \
    Monster.h \
    Action.h

INCLUDEPATH += ../grid2d/
