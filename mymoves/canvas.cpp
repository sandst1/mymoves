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

#include "canvas.h"
#include "canvastimer.h"
#include "context2d.h"

#include <QDBusConnection>
#include <QDBusMessage>

#include <QtGui/QPainter>
#include <QTouchEvent>

#include <QFile>
#include <QTextStream>

void Canvas::registerQML()
{
    qmlRegisterType<Canvas>("QmlCanvas", 1, 0, "Canvas");
    qmlRegisterType<Context2D>("QmlCanvas", 1, 0, "Context2D");
    qmlRegisterUncreatableType<CanvasImage>("QmlCanvas", 1, 0, "CanvasImage", QString());
    qmlRegisterUncreatableType<CanvasGradient>("QmlCanvas", 1, 0, "Gradient", QString());
}

Canvas::Canvas(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
    m_context(new Context2D(this)),
    m_canvasWidth(0),
    m_canvasHeight(0),
    m_fillMode(Canvas::Stretch),
    m_color(Qt::white)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}


void Canvas::componentComplete()
{
    if (m_canvasWidth == 0 && m_canvasHeight == 0)
        m_context->setSize(width(), height());
    else
        m_context->setSize(m_canvasWidth, m_canvasHeight);

    connect(m_context, SIGNAL(changed()), this, SLOT(requestPaint()));
    emit init();
    QDeclarativeItem::componentComplete();
}

void Canvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    m_context->setInPaint(true);
    emit paint();

    //bool oldAA = painter->testRenderHint(QPainter::Antialiasing);
    //bool oldSmooth = painter->testRenderHint(QPainter::SmoothPixmapTransform);
    //if (smooth())
        //painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform, smooth());

    /*if (m_context->pixmap().isNull()) {
        painter->fillRect(0, 0, width(), height(), m_color);
    } else if (width() != m_context->pixmap().width() || height() != m_context->pixmap().height()) {
        if (m_fillMode>= Tile) {
            if (m_fillMode== Tile) {
                painter->drawTiledPixmap(QRectF(0,0,width(),height()), m_context->pixmap());
            } else {
                qreal widthScale = width() / qreal(m_context->pixmap().width());
                qreal heightScale = height() / qreal(m_context->pixmap().height());

                QTransform scale;
                if (m_fillMode== TileVertically) {
                    scale.scale(widthScale, 1.0);
                    QTransform old = painter->transform();
                    painter->setWorldTransform(scale * old);
                    painter->drawTiledPixmap(QRectF(0,0,m_context->pixmap().width(),height()), m_context->pixmap());
                    painter->setWorldTransform(old);
                } else {
                    scale.scale(1.0, heightScale);
                    QTransform old = painter->transform();
                    painter->setWorldTransform(scale * old);
                    painter->drawTiledPixmap(QRectF(0,0,width(),m_context->pixmap().height()), m_context->pixmap());
                    painter->setWorldTransform(old);
                }
            }
        } else {
            qreal widthScale = width() / qreal(m_context->pixmap().width());
            qreal heightScale = height() / qreal(m_context->pixmap().height());

            QTransform scale;

            if (m_fillMode== PreserveAspectFit) {
                if (widthScale <= heightScale) {
                    heightScale = widthScale;
                    scale.translate(0, (height() - heightScale * m_context->pixmap().height()) / 2);
                } else if(heightScale < widthScale) {
                    widthScale = heightScale;
                    scale.translate((width() - widthScale * m_context->pixmap().width()) / 2, 0);
                }
            } else if (m_fillMode== PreserveAspectCrop) {
                if (widthScale < heightScale) {
                    widthScale = heightScale;
                    scale.translate((width() - widthScale * m_context->pixmap().width()) / 2, 0);
                } else if(heightScale < widthScale) {
                    heightScale = widthScale;
                    scale.translate(0, (height() - heightScale * m_context->pixmap().height()) / 2);
                }
            }
            if (clip()) {
                painter->save();
                painter->setClipRect(boundingRect(), Qt::IntersectClip);
            }
            scale.scale(widthScale, heightScale);
            QTransform old = painter->transform();
            painter->setWorldTransform(scale * old);
            painter->drawPixmap(0, 0, m_context->pixmap());
            painter->setWorldTransform(old);
            if (clip()) {
                painter->restore();
            }
        }
    } else {
        painter->drawPixmap(0, 0, m_context->pixmap());
    }*/

    painter->drawPixmap(0, 0, m_context->pixmap());

    /*if (smooth()) {
        painter->setRenderHint(QPainter::Antialiasing, oldAA);
        painter->setRenderHint(QPainter::SmoothPixmapTransform, oldSmooth);
    }*/
    m_context->setInPaint(false);
}

Context2D *Canvas::getContext(const QString &contextId)
{
    if (contextId == QLatin1String("2d"))
        return m_context;
    qDebug("Canvas:requesting unsupported context");
    return 0;
}

void Canvas::requestPaint()
{
    update();
}

void Canvas::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (m_canvasWidth == 0 && m_canvasHeight == 0
        && newGeometry.width() > 0 && newGeometry.height() > 0) {
        m_context->setSize(width(), height());
    }
    QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);
}

void Canvas::setCanvasWidth(int newWidth)
{
    if (m_canvasWidth != newWidth) {
        m_canvasWidth = newWidth;
        m_context->setSize(m_canvasWidth, m_canvasHeight);
        emit canvasWidthChanged();
    }
}

void Canvas::setCanvasHeight(int newHeight)
{
    if (m_canvasHeight != newHeight) {
        m_canvasHeight = newHeight;
        m_context->setSize(m_canvasWidth, m_canvasHeight);
        emit canvasHeightChanged();
    }
}

void Canvas::setFillMode(FillMode mode)
{
    if (m_fillMode == mode)
        return;

    m_fillMode = mode;
    update();
    emit fillModeChanged();
}

QColor Canvas::color()
{
    return m_color;
}

void Canvas::setColor(const QColor &color)
{
    if (m_color !=color) {
        m_color = color;
        colorChanged();
    }
}

Canvas::FillMode Canvas::fillMode() const
{
    return m_fillMode;
}

bool Canvas::save(const QString &filename) const
{
    return m_context->pixmap().save(filename);
}

CanvasImage *Canvas::toImage() const
{
    return new CanvasImage(m_context->pixmap());
}

void Canvas::setTimeout(const QScriptValue &handler, long timeout)
{
    if (handler.isFunction())
        CanvasTimer::createTimer(this, handler, timeout, true);
}

void Canvas::setInterval(const QScriptValue &handler, long interval)
{
    if (handler.isFunction())
        CanvasTimer::createTimer(this, handler, interval, false);
}

void Canvas::clearTimeout(const QScriptValue &handler)
{
    CanvasTimer::removeTimer(handler);
}

void Canvas::clearInterval(const QScriptValue &handler)
{
    CanvasTimer::removeTimer(handler);
}
