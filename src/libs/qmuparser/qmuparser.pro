include(../../../common.pri)
include(qmuparser.pri)
include(warnings.pri)
include (../libs.pri)

QT -= gui

TARGET = qmuparser
TEMPLATE = lib

# Use out-of-source builds (shadow builds)
CONFIG -= debug_and_release debug_and_release_target

# Since Qt 5.4.0 the source code location is recorded only in debug builds.
# We need this information also in release builds. For this need define QT_MESSAGELOGCONTEXT.
DEFINES += QT_MESSAGELOGCONTEXT

DEFINES += QMUPARSER_LIBRARY

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj

VERSION = 2.5.0

# Allow MAC OS X to find library inside a bundle
macx:QMAKE_SONAME_PREFIX = @rpath

# Allow MAC OS X to find library inside a bundle
macx:QMAKE_SONAME_PREFIX = @rpath

# Set "make install" command for Unix-like systems.
unix:!macx {
    isEmpty(PREFIX_LIB) {
        isEmpty(PREFIX) {
            PR_LIB = $$DEFAULT_PREFIX
        } else {
            PR_LIB = $$PREFIX
        }
        contains(QMAKE_HOST.arch, x86_64) {
            PREFIX_LIB = $$PR_LIB/lib64/Seamly2D
        } else {
            PREFIX_LIB = $$PR_LIB/lib/Seamly2D
        }
    }
    target.path = $$PREFIX_LIB
    INSTALLS += target
}

$$enable_ccache()

# Release mode
CONFIG(release, debug|release) {
    DEFINES += V_NO_ASSERT
    
    !*msvc*:CONFIG += silent

    !unix:*g++* {
        QMAKE_CXXFLAGS += -fno-omit-frame-pointer # Need for exchndl.dll
    }

    noStripDebugSymbols {
        # do nothing
    } else {
        !macx:!*msvc* {
            noDebugSymbols { # For enable run qmake with CONFIG+=noDebugSymbols
                # do nothing
            } else {
                # Turn on debug symbols in release mode on Unix systems.
                # On Mac OS X temporarily disabled. TODO: find way how to strip binary file.
                QMAKE_CXXFLAGS_RELEASE += -g -gdwarf-3
                QMAKE_CFLAGS_RELEASE += -g -gdwarf-3
                QMAKE_LFLAGS_RELEASE =

                noStripDebugSymbols { # For enable run qmake with CONFIG+=noStripDebugSymbols
                    # do nothing
                } else {
                    # Strip debug symbols.
                    QMAKE_POST_LINK += objcopy --only-keep-debug bin/${TARGET} bin/${TARGET}.dbg &&
                    QMAKE_POST_LINK += objcopy --strip-debug bin/${TARGET} &&
                    QMAKE_POST_LINK += objcopy --add-gnu-debuglink="bin/${TARGET}.dbg" bin/${TARGET}
                }

                QMAKE_DISTCLEAN += bin/${TARGET}.dbg
            }
        }
    }
}
