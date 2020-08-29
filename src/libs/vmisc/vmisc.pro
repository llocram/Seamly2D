include(../../../common.pri)
include(vmisc.pri)
include(warnings.pri)
include (../libs.pri)

QT += \
    widgets \
    printsupport \
    testlib \
    gui

TARGET = vmisc
TEMPLATE = lib

CONFIG += staticlib

# Use out-of-source builds (shadow builds)
CONFIG -= debug_and_release debug_and_release_target

# Since Qt 5.4.0 the source code location is recorded only in debug builds.
# We need this information also in release builds. For this need define QT_MESSAGELOGCONTEXT.
DEFINES += QT_MESSAGELOGCONTEXT

RESOURCES += \
    share/resources/theme.qrc \ # Windows theme icons.
    share/resources/icon.qrc \ # All other icons except cursors and Windows theme.
    share/resources/flags.qrc

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj

$$enable_ccache()

CONFIG(debug, debug|release) {
    # Debug mode
    #Calculate latest tag distance and build revision only in release mode. Change number each time requare
    #recompilation precompiled headers file.
    DEFINES += "LATEST_TAG_DISTANCE=0"
} else {
    # Release mode
    DEFINES += V_NO_ASSERT

    !*msvc*:CONFIG += silent
    !unix:*g++* {
        QMAKE_CXXFLAGS += -fno-omit-frame-pointer # Need for exchndl.dll
    }

    noDebugSymbols { # For enable run qmake with CONFIG+=noDebugSymbols
        # do nothing
    } else {
        !macx:!*msvc*{
            # Turn on debug symbols in release mode on Unix systems.
            # On Mac OS X temporarily disabled. TODO: find way how to strip binary file.
            QMAKE_CXXFLAGS_RELEASE += -g -gdwarf-3
            QMAKE_CFLAGS_RELEASE += -g -gdwarf-3
            QMAKE_LFLAGS_RELEASE =
        }
    }

    #comment out HG tag & version - slspencer 20171012
    #macx{
        #HG = /usr/local/bin/hg # Can't defeat PATH variable on Mac OS.
    #}else {
        #HG = hg # All other platforms all OK.
    #}
    #latest tag distance number for using in version
    #HG_DISTANCE=$$system($${HG} log -r. --template '{latesttagdistance}')
    #isEmpty(HG_DISTANCE){
        #HG_DISTANCE = 0 # if we can't find local revision left 0.
    #}
    #message("Latest tag distance:" $${HG_DISTANCE})
    #DEFINES += "LATEST_TAG_DISTANCE=$${HG_DISTANCE}" # Make available latest tag distance number in sources.
    #DEFINES += HG_VERSION=\\"$$HG_VERSION\\"

    #get latest git tag and it's distance from HEAD
    macx {
        GIT = /usr/local/bin/git # Can't defeat PATH variable on Mac OS.
    } else {
        GIT = GIT # All other platforms all OK.
    }

    # tag is formatted as TAG-N-gSHA:
    # 1. latest stable version is TAG, or vX.Y.Z
    # 2. number of commits since latest stable version is N
    # 3. latest commit is gSHA
    tag_all = $$system(git describe --tags)
    tag_split = $$split(tag_all, "-") #split at the dashes
    GIT_DISTANCE = $$member(tag_split,1) #get 2nd element of results

    isEmpty(GIT_DISTANCE) {
        GIT_DISTANCE = 0 # if we can't find local revision left 0.
    }
    message("vmisc.pro: Latest tag distance:" $${GIT_DISTANCE})
    DEFINES += "LATEST_TAG_DISTANCE=$${GIT_DISTANCE}" # Make available latest tag distance number in sources.
    DEFINES += GIT_VERSION=\\"$$GIT_VERSION\\"

}
