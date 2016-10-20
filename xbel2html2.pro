HEADERS       = mainwindow.h \
                xbelgenerator.h \
                xbelhandler.h \
                htmlgenerator.h \
    generator.h \
    jsongenerator.h
SOURCES       = main.cpp \
                mainwindow.cpp \
                xbelgenerator.cpp \
                xbelhandler.cpp \
                htmlgenerator.cpp \
    generator.cpp
QT           += xml widgets

EXAMPLE_FILES = frank.xbel jennifer.xbel

# install
target.path = $$[QT_INSTALL_EXAMPLES]/xml/xbel2html
INSTALLS += target

wince {
     addFiles.files = frank.xbel jennifer.xbel
     addFiles.path = "\\My Documents"
     DEPLOYMENT += addFiles
}
