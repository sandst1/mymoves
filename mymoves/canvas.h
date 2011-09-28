/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CANVAS_H
#define CANVAS_H

#include <QDeclarativeItem>
#include "context2d.h"
#include "canvastimer.h"
#include <QList>
#include <QPoint>

class Canvas : public QDeclarativeItem
{
    Q_OBJECT

    Q_ENUMS(FillMode)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged);
    Q_PROPERTY(int canvasWidth READ canvasWidth WRITE setCanvasWidth NOTIFY canvasWidthChanged);
    Q_PROPERTY(int canvasHeight READ canvasHeight WRITE setCanvasHeight NOTIFY canvasHeightChanged);
    Q_PROPERTY(FillMode fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)

public:
    static void registerQML();
    Canvas(QDeclarativeItem *parent = 0);
    enum FillMode { Stretch, PreserveAspectFit, PreserveAspectCrop, Tile, TileVertically, TileHorizontally };

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
    void setCanvasWidth(int newWidth);
    int canvasWidth() {return m_canvasWidth;}

    void setCanvasHeight(int canvasHeight);
    int canvasHeight() {return m_canvasHeight;}

    void componentComplete();

public Q_SLOTS:    
    Context2D *getContext(const QString & = QString("2d"));
    void requestPaint();

    FillMode fillMode() const;
    void setFillMode(FillMode);

    QColor color();
    void setColor(const QColor &);

    // Save current canvas to disk
    bool save(const QString& filename) const;

    // Timers
    void setInterval(const QScriptValue &handler, long timeout);
    void setTimeout(const QScriptValue &handler, long timeout);
    void clearInterval(const QScriptValue &handler);
    void clearTimeout(const QScriptValue &handler);

Q_SIGNALS:
    void fillModeChanged();
    void canvasWidthChanged();
    void canvasHeightChanged();
    void colorChanged();
    void init();
    void paint();

private:
    // Return canvas contents as a drawable image
    CanvasImage *toImage() const;
    Context2D *m_context;
    int m_canvasWidth;
    int m_canvasHeight;
    FillMode m_fillMode;
    QColor m_color;

    friend class Context2D;
};

#endif //CANVAS_H
