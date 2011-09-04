/*
 * MyMoves - Configurable gestures for Harmattan
 * Copyright (C) 2011 Topi Santakivi <topi.santakivi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
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
#include "mymovesinterface.h"
#include "qdeclarativetoucharea.h"
#include "listmodel.h"


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
        bool itemReady = false;
        do
        {
            if (line.startsWith("Name="))
            {
                name = line.mid(5);
                //qDebug() << name;
                if ( !command.isEmpty())
                    itemReady = true;
            }
            else if (line.startsWith("Exec="))
            {
                command = line.mid(5);
                //qDebug() << command;
                if ( !name.isEmpty())
                    itemReady = true;
            }
            line = dfile.readLine();
        } while (!line.isEmpty());

        if (itemReady)
            applist->appendRow(new AppItem(name, command, applist));

        dfile.close();
    }
    applist->sort();
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

    MyMovesInterface mymoves;
    view.rootContext()->setContextProperty("MyMovesInterface", &mymoves);
    view.rootContext()->setContextProperty("AppListModel", applist);

    Canvas::registerQML();
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.showFullScreen();
    return app.exec();
}
