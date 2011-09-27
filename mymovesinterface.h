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
#ifndef MYMOVESINTERFACE_H
#define MYMOVESINTERFACE_H

#include <QList>
#include <QObject>

class MyMovesInterface : public QObject
{
    Q_OBJECT
public:
    explicit MyMovesInterface(QObject *parent = 0);
    ~MyMovesInterface();
signals:

public slots:   
    Q_INVOKABLE void observeGestures();
    Q_INVOKABLE void stopObserving();
    Q_INVOKABLE void loadGestures();
    Q_INVOKABLE int  serverStatus();

    Q_INVOKABLE void setServerObservingOnExit(bool set);
private:
    struct Gesture
    {
        QString command;
        QString imagePath;
    };
    QList<Gesture> m_gestures;
    bool m_setObserving;
};

#endif // MYMOVESINTERFACE_H
