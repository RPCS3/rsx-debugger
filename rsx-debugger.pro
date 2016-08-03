TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    ../rpcs3/Emu/RSX/gcm_enums.cpp \
    ../Utilities/StrFmt.cpp \
    ../rpcs3/Emu/RSX/Common/BufferUtils.cpp \
    ../rpcs3/Emu/RSX/gcm_printing.cpp

RESOURCES += qml.qrc

INCLUDEPATH += ../ \
    ../rpcs3/ \
    ../rsx_program_decompiler/rsx_decompiler/ \
    ../3rdparty/cereal/include/ \
    ../3rdparty/GSL/include/

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    state.h
