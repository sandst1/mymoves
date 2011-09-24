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
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include "mymovesinterface.h"

#define GESTURES_PATH "/home/user/MyDocs/.moves"
#define NAME_FILTER "mymove*"

MyMovesInterface::MyMovesInterface(QObject *parent) :
    QObject(parent)
{
    loadGestures();

    serverStatus();
}

MyMovesInterface::~MyMovesInterface()
{}

void MyMovesInterface::observeGestures()
{
    qDebug("MyMovesInterface::observeGestures");
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage msg = QDBusMessage::createMethodCall("org.sandst1.mymoves", "/sandst1/mymoves", "org.sandst1.mymoves", "observeGestures");
    QDBusMessage reply = bus.call(msg);
    qDebug() << reply;
}

void MyMovesInterface::stopObserving()
{
    qDebug("MyMovesInterface::stopObserving");
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage msg = QDBusMessage::createMethodCall("org.sandst1.mymoves", "/sandst1/mymoves", "org.sandst1.mymoves", "stopObserving");
    QDBusMessage reply = bus.call(msg);
    qDebug() << reply;
}

void MyMovesInterface::loadGestures()
{
    m_gestures.clear();
    qDebug("MyMoveServer::loadGestures");
    QDir gdir(GESTURES_PATH);
    QStringList namefilter(NAME_FILTER);
    QStringList files = gdir.entryList(namefilter);

    for (int i = 0; i < files.count(); i++)
    {
        QFile gestFile(QString(GESTURES_PATH) + "/" + files.at(i));
        QString line;
        int x = 0;
        int y = 0;
        gestFile.open(QIODevice::ReadOnly);
        QTextStream gstream(&gestFile);
        Gesture gesture;
        // Read the command attached to this gesture
        line = gstream.readLine();
        gesture.command = line;
        qDebug() << "Command for this gesture: " << gesture.command;

        gesture.imagePath = QString(GESTURES_PATH) + "/" + files.at(i) + ".png";

        gestFile.close();

        m_gestures.append(gesture);
    }
}

int MyMovesInterface::serverStatus()
{
    qDebug("MyMovesInterface::serverStatus");
    QDBusConnection bus = QDBusConnection::sessionBus();
    QDBusMessage msg = QDBusMessage::createMethodCall("org.sandst1.mymoves", "/sandst1/mymoves", "org.sandst1.mymoves", "serverStatus");
    QDBusMessage reply = bus.call(msg);
    qDebug() << "Server status: " << reply.arguments().at(0).toString();
    return reply.arguments().at(0).toInt();
}
