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

#include <QGLFormat>
#include <QGLWidget>
#include <QtGui/QApplication>
#include <QtDeclarative>
#include "canvas.h"
#include "mymovesinterface.h"
#include "qdeclarativetoucharea.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setGraphicsSystem("raster");
    QDeclarativeView view;    

    QGLWidget glWidget(QGLFormat(QGL::SampleBuffers));
    view.setViewport(&glWidget);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    QDeclarativeTouchArea::registerQML();

    MyMovesInterface mymoves;
    view.rootContext()->setContextProperty("MyMovesInterface", &mymoves);

    Canvas::registerQML();
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.showFullScreen();
    return app.exec();
}
