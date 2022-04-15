TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -LC:/SFML/lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += 'C:/Program Files (x86)/SFML/include'
DEPENDPATH += 'C:/Program Files (x86)/SFML/include'

SOURCES += \
    IA/IAAbstraite.cpp \
    IA/IACplx.cpp \
    IA/IASimple.cpp \
    jeu/JeuAffBasique.cpp \
    main.cpp \
    CarteDeTuile.cpp \
    jeu/Jeu.cpp \
    jeu/JeuAff.cpp \
    jeu/JeuIA.cpp \
    jeu/JeuIAAff.cpp \
    neat/Evolutor.cpp \
    neat/Individu.cpp \
    neat/Liaison.cpp \
    neat/Neurone.cpp \

HEADERS += \
    CarteDeTuile.h \
    IA/IAAbstraite.h \
    IA/IACplx.h \
    IA/IASimple.h \
    jeu/Jeu.h \
    jeu/JeuAff.h \
    jeu/JeuAffBasique.h \
    jeu/JeuIA.h \
    jeu/JeuIAAff.h \
    neat/Evolutor.h \
    neat/Individu.h \
    neat/Liaison.h \
    neat/Neurone.h \
