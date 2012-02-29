# Add more folders to ship with the application, here

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT+= dbus declarative opengl
symbian:TARGET.UID3 = 0xE4389E3C

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    context2d.cpp \
    canvastimer.cpp \
    canvasplugin.cpp \
    canvas.cpp \
    mymovesinterface.cpp \
    qdeclarativetoucharea.cpp \
    listmodel.cpp \
    appitem.cpp \
    gestureitem.cpp \
    gesturelistmodel.cpp


OTHER_FILES += \
    qml/MainPage.qml \
    qml/main.qml \
    mymoves.desktop \
    mymoves.png \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qml/TextDialog.qml \
    qml/NewMove.qml \
    qml/AppList.qml \
    qml/GestureList.qml \
    qml/MyMoves.qml \
    qml/AddMove.qml \
    qml/BlackPage.qml \
    qml/BlackButton.qml \
    qml/MyMovesDelegate.qml \
    qml/MyText.qml \
    qml/serverstatus.js \
    qml/About.qml \
    qml/Howto.qml \
    qml/SelectLaunchable.qml

svgicon.files = mymoves.svg
svgicon.path = /usr/share/icons/hicolor/scalable/apps/
INSTALLS += svgicon

splash.files = images/splash.jpg
splash.path = /usr/share/mymoves
INSTALLS += splash

RESOURCES += \
    res.qrc

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

# enable booster
CONFIG += qdeclarative-boostable
QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
QMAKE_LFLAGS += -pie -rdynamic

HEADERS += \
    context2d.h \
    canvastimer.h \
    canvasplugin.h \
    canvas.h \
    mymovesinterface.h \
    qdeclarativetoucharea.h \
    listmodel.h \
    appitem.h \
    gestureitem.h \
    gesturelistmodel.h \
    constants.h
