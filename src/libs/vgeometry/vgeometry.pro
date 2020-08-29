include(../../../common.pri)
include(vgeometry.pri)
include(warnings.pri)
include (../libs.pri)

QT += \
    widgets \
    printsupport

TARGET = vgeometry
TEMPLATE = lib

CONFIG += \
    staticlib \

# Use out-of-source builds (shadow builds)
CONFIG -= debug_and_release debug_and_release_target

# Since Qt 5.4.0 the source code location is recorded only in debug builds.
# We need this information also in release builds. For this need define QT_MESSAGELOGCONTEXT.
DEFINES += QT_MESSAGELOGCONTEXT

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj

$$enable_ccache()

# Release mode
CONFIG(release, debug|release) {
    DEFINES += V_NO_ASSERT

    !*msvc*:CONFIG += silent

    !unix:*g++* {
        QMAKE_CXXFLAGS += -fno-omit-frame-pointer # Need for exchndl.dll
    }

    noDebugSymbols { # For enable run qmake with CONFIG+=noDebugSymbols
        # do nothing
    } else {
        !macx:!*msvc* {
            # Turn on debug symbols in release mode on Unix systems.
            # On Mac OS X temporarily disabled. TODO: find way how to strip binary file.
            QMAKE_CXXFLAGS_RELEASE += -g -gdwarf-3
            QMAKE_CFLAGS_RELEASE += -g -gdwarf-3
            QMAKE_LFLAGS_RELEASE =
        }
    }
}
