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

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtCore/QTimer>

#include "canvastimer.h"

Q_GLOBAL_STATIC(QList<CanvasTimer*> , activeTimers);

CanvasTimer::CanvasTimer(QObject *parent, const QScriptValue &data)
    : QTimer(parent), m_value(data)
{
}

void CanvasTimer::handleTimeout()
{
    Q_ASSERT(m_value.isFunction());
    m_value.call();
    if (isSingleShot()) {
        removeTimer(this);
    }
}

void CanvasTimer::createTimer(QObject *parent, const QScriptValue &val, long timeout, bool singleshot)
{

    CanvasTimer *timer = new CanvasTimer(parent, val);
    timer->setInterval(timeout);
    timer->setSingleShot(singleshot);
    connect(timer, SIGNAL(timeout()), timer, SLOT(handleTimeout()));
    activeTimers()->append(timer);
    timer->start();
}

void CanvasTimer::removeTimer(CanvasTimer *timer)
{
    activeTimers()->removeAll(timer);
    timer->deleteLater();
}

void CanvasTimer::removeTimer(const QScriptValue &val)
{
    if (!val.isFunction())
        return;

    for (int i = 0 ; i < activeTimers()->count() ; ++i) {
        CanvasTimer *timer = activeTimers()->at(i);
        if (timer->equals(val)) {
            removeTimer(timer);
            return;
        }
    }
}
