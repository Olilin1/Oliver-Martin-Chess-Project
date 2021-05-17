QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Logic/Bitboard.cpp \
    Logic/Game_EvaluatePosition.cpp \
    Logic/Game_GenerateAttackSets.cpp \
    Logic/Game_GenerateBlockerMoves.cpp \
    Logic/Game_GeneratePseudoMoves.cpp \
    Logic/Game_HelperFunctions.cpp \
    Logic/Game_InitializeGame.cpp \
    Logic/Game_IsOver.cpp \
    Logic/Game_KingKnightMoves.cpp \
    Logic/Game_MagicNumberGeneration.cpp \
    Logic/Game_MakeAllMoves.cpp \
    Logic/Game_MakeLegalMove.cpp \
    Logic/Game_MiniMax.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Logic/Bitboard.hpp \
    Logic/Enums.hpp \
    Logic/Game.hpp \
    Logic/GameState.hpp \
    Logic/Move.hpp \
    Logic/RanksFilesBitboards.hpp \
    Logic/Typedefs.hpp \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resources.qrc
