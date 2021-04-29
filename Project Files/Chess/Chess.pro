QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Logic/Board.cpp \
    Logic/Board_HelperFunctions.cpp \
    Logic/Board_IsAttacked.cpp \
    Logic/Game.cpp \
    Logic/Game_AllMoves.cpp \
    Logic/Game_HelperFunctions.cpp \
    Logic/Game_LegalMoves.cpp \
    Logic/Game_MakeMove.cpp \
    Logic/Game_SetupGame.cpp \
    Logic/HelperFunctions.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Logic/Board.hpp \
    Logic/Constants.hpp \
    Logic/Enums.hpp \
    Logic/Game.hpp \
    Logic/GameState.hpp \
    Logic/HelperFunctions.hpp \
    Logic/Typedefs.hpp \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resources.qrc
