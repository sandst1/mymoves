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
#include <QStringList>
#include <QTextStream>
#include <QFile>

#include "constants.h"
#include "gestureitem.h"
#include "gesturelistmodel.h"

GestureListModel::GestureListModel(ListItem* prototype, QObject *parent)
    : ListModel(prototype, parent)
{
}


void GestureListModel::saveItem(int index, const QString& app, const QString& command)
{
    qDebug("GestureListModel::saveItem %d %s %s", index, app.toLatin1().data(), command.toLatin1().data());
    GestureItem* item = static_cast<GestureItem*>(m_list[index]);
    item->setReserved(true);
    item->setApp(app);
    item->setCommand(command);
    saveToDisk();
    qDebug("GestureListModel::saveItem done");
}

void GestureListModel::loadFromDisk()
{
    qDebug() << __PRETTY_FUNCTION__;
    QFile gfile(GESTURES_CONF_FILE);
    gfile.open(QIODevice::ReadOnly);
    QTextStream stream(&gfile);

    // Read the gesture file version
    QString version = stream.readLine();

    QString line = stream.readLine();
    do
    {
        QStringList data = line.split("###");
        QString id;
        QString app;
        QString command;
        bool reserved = false;
        qDebug("### Gesture ###");
        for (int i = 0; i < data.size(); i++)
        {
            qDebug("data %d %s", i, data.at(i).toLatin1().data());
        }

        id = data.at(0);
        app = data.at(1);
        command = data.at(2);
        if (app.size() > 0)
        {
            reserved = true;
        }
        QString image = QString(GESTURE_IMG_PATH) + id + GESTURE_IMG_EXT;
        qDebug("### Gesture END ###");

        GestureItem* item = new GestureItem(id, image, this);
        item->setApp(app);
        item->setCommand(command);
        item->setReserved(reserved);
        this->appendRow(item);

        line = stream.readLine();
    } while (!line.isEmpty());
    qDebug() << __PRETTY_FUNCTION__ << "end";
}

void GestureListModel::saveToDisk()
{
    qDebug() << __PRETTY_FUNCTION__;
    QFile gfile(GESTURES_CONF_FILE);
    gfile.open(QIODevice::WriteOnly);
    QTextStream stream(&gfile);

    // Insert version
    stream << CONFIG_FILE_VERSION << endl;

    for (int i = 0; i < m_list.size(); i++)
    {
        GestureItem* item = static_cast<GestureItem*>(m_list[i]);
        stream << item->id() << "###" << item->app().trimmed() << "###" << item->command().trimmed() << endl;
    }

    gfile.close();
    qDebug() << __PRETTY_FUNCTION__ << "end";
}

void GestureListModel::setContextProperties(QDeclarativeContext* ctx)
{
    qDebug() << __PRETTY_FUNCTION__;
    ctx->setContextProperty("GestureListModel", this);
    qDebug() << __PRETTY_FUNCTION__ << "end";
}
