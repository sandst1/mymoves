/*
 * MyMoves - Configurable gestures for Harmattan
 * Copyright (C) 2011 Topi Santakivi <topi.santakivi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <QDebug>
#include <QFile>
#include <QGLFormat>
#include <QGLWidget>
#include <QString>
#include <QtGui/QApplication>
#include <QtDeclarative>

#include "appitem.h"
#include "canvas.h"
#include "constants.h"
#include "gestureitem.h"
#include "listmodel.h"
#include "gesturelistmodel.h"
#include "mymovesinterface.h"
#include "qdeclarativetoucharea.h"

void createAppList(ListModel* applist)
{
    QDir dir("/usr/share/applications");
    QStringList filter("*.desktop");
    QStringList files = dir.entryList(filter);
    for (int i = 0; i < files.count(); i++)
    {
        QFile dfile(QString("/usr/share/applications/") + files.at(i));
        dfile.open(QIODevice::ReadOnly);

        QString line = dfile.readLine();
        QString name("");
        QString command("");
        QString icon("");
        bool itemReady = false;
        bool itemShownOnAppGrid = true;
        do
        {
            if (line.startsWith("Name="))
            {
                name = line.trimmed().mid(5);
                //qDebug() << name;
                if ( !command.isEmpty())
                    itemReady = true;
            }
            else if (line.startsWith("Icon="))
            {
                //qDebug() << "Icon found: " << line;
                icon = line.trimmed().mid(5);
                if (!icon.contains("/"))
                {
                    if (QFile::exists(QString(ICON_PATH) + icon + ".png"))
                        icon = "file://" + QString(ICON_PATH) + icon + ".png";
                    if (QFile::exists(QString(ICON_PATH) + icon + ".svg"))
                        icon = "file://" + QString(ICON_PATH) + icon + ".svg";
                    else if (QFile::exists(QString(ICON_PATH2) + icon + ".png"))
                        icon = "file://" + QString(ICON_PATH2) + icon + ".png";
                    else if (QFile::exists(QString(ICON_PATH2) + icon + ".svg"))
                        icon = "file://" + QString(ICON_PATH2) + icon + ".svg";

                }
                else
                {
                    icon = "file://" + icon;
                }
                //qDebug() << "Parsed icon: " << icon;
            }
            else if (line.startsWith("Exec="))
            {
                command = line.mid(5);
                //qDebug() << command;
                if ( !name.isEmpty())
                    itemReady = true;
            }
            else if (line.startsWith("NotShowIn=X-MeeGo"))
            {
                itemShownOnAppGrid = false;
            }
            line = dfile.readLine();
        } while (!line.isEmpty());

        if (itemReady && itemShownOnAppGrid)
        {
            if (icon.size() == 0)
            {
                icon = QString(DEFAULT_APP_ICON);
            }
            applist->appendRow(new AppItem(name, command, icon, applist));
        }

        dfile.close();
    }
    applist->sort();
}

void createBookmarkList(ListModel* bmarks)
{
    QDir dir("/home/user/.local/share/applications");
    QStringList filter("browser*.desktop");
    QStringList files = dir.entryList(filter);
    for (int i = 0; i < files.count(); i++)
    {
        QFile dfile(QString("/home/user/.local/share/applications/") + files.at(i));
        dfile.open(QIODevice::ReadOnly);

        QString line = dfile.readLine();
        QString name("");
        QString command("");
        QString icon("");
        bool itemReady = false;
        do
        {
            if (line.startsWith("Name="))
            {
                name = line.trimmed().mid(5);
                //qDebug() << name;
                if ( !command.isEmpty())
                    itemReady = true;
            }
            else if (line.startsWith("Icon="))
            {
                //qDebug() << "Icon found: " << line;
                icon = line.trimmed().mid(5);
                icon = "file://" + icon;
                //qDebug() << "Parsed icon: " << icon;
            }
            else if (line.startsWith("URL="))
            {
                command = "/usr/bin/invoker --type=m /usr/bin/grob " + line.mid(4);
                //qDebug() << command;
                if ( !name.isEmpty())
                    itemReady = true;
            }
            line = dfile.readLine();
        } while (!line.isEmpty());

        if (itemReady)
        {
            if (icon.size() == 0)
            {
                icon = QString(DEFAULT_APP_ICON);
            }
            bmarks->appendRow(new AppItem(name, command, icon, bmarks));
        }

        dfile.close();
    }
    bmarks->sort();
}

void createScriptList(ListModel* scripts)
{
    QDir dir("/home/user/.config/mymovescripts");
    QStringList filter("*.sh");
    QStringList files = dir.entryList(filter);
    for (int i = 0; i < files.count(); i++)
    {
        QFile dfile(QString("/home/user/.config/mymovescripts/") + files.at(i));
        dfile.open(QIODevice::ReadOnly);

        QString line = dfile.readLine();
        QString name("");
        QString command("");
        do
        {
            if (line.startsWith("#Name="))
            {
                name = line.trimmed().mid(6);
            }
            line = dfile.readLine();
        } while (!line.isEmpty());

        command = "sh " + QString("/home/user/.config/mymovescripts/") + files.at(i);

        scripts->appendRow(new AppItem(name, command, "", scripts));

        dfile.close();
    }
    scripts->sort();
}

void createGestureList(ListModel* gesturelist)
{
    /*for (int i = 0; i < SINGLE_GESTURES; i++)
    {
        QVariant gnum(i);
        QString imgPath = QString(GESTURE_IMG_PATH) + gnum.toString() + GESTURE_IMG_EXT;
        gesturelist->appendRow(new GestureItem(QString(gnum.toString()),imgPath, gesturelist));
    }*/

    for (int i = 0; i < DOUBLE_GESTURES; i++)
    {
        QVariant gnum(i);
        QString imgPath = QString(GESTURE_IMG_PATH) + "d" + gnum.toString() + GESTURE_IMG_EXT;
        gesturelist->appendRow(new GestureItem(QString("d"+gnum.toString()), imgPath, gesturelist));
    }

    for (int i = 0; i < TRIPLE_GESTURES; i++)
    {
        QVariant gnum(i);
        QString imgPath = QString(GESTURE_IMG_PATH) + "t" + gnum.toString() + GESTURE_IMG_EXT;
        gesturelist->appendRow(new GestureItem(QString("t"+gnum.toString()), imgPath, gesturelist));
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setGraphicsSystem("raster");
    QDeclarativeView view;    

    QGLWidget glWidget(QGLFormat(QGL::SampleBuffers));
    view.setViewport(&glWidget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QDeclarativeTouchArea::registerQML();

    ListModel* applist = new ListModel(new AppItem, &app);
    createAppList(applist);

    ListModel* bookmarks = new ListModel(new AppItem, &app);
    createBookmarkList(bookmarks);

    ListModel* scripts = new ListModel(new AppItem, &app);
    createScriptList(scripts);


    GestureListModel* gesturelist = new GestureListModel(new GestureItem, &app);

    // Create the gesture file if it doesn't exist
    if (!QFile::exists(GESTURES_CONF_FILE))
    {
        createGestureList(gesturelist);
        gesturelist->saveToDisk();
    }
    else
    {
        gesturelist->loadFromDisk();
    }

    MyMovesInterface mymoves;
    view.rootContext()->setContextProperty("MyMovesInterface", &mymoves);
    view.rootContext()->setContextProperty("AppListModel", applist);
    view.rootContext()->setContextProperty("BookmarksModel", bookmarks);
    view.rootContext()->setContextProperty("ActionsModel", scripts);
    gesturelist->setContextProperties(view.rootContext());

    Canvas::registerQML();
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.showFullScreen();
    return app.exec();
}
