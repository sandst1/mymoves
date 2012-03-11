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
#include "gestureitem.h"

GestureItem::GestureItem(const QString& id, const QString& image, QObject *parent)
    : ListItem(parent),
      m_id(id),
      m_image(image),
      m_reserved(false),
      m_app(),
      m_command()
{}

GestureItem::GestureItem(const GestureItem& item, QObject* parent)
    : ListItem(parent)
{
    m_id = item.m_id;
    m_image = item.m_image;
    m_reserved = item.m_reserved;
    m_app = item.m_app;
    m_command = item.m_command;
}

QVariant GestureItem::data(int role) const
{
    switch (role)
    {
        case ImageRole:
            return m_image;
        break;

        case ReservedRole:
            return m_reserved;
        break;

        case AppRole:
            return m_app;
        break;

        case CommandRole:
            return m_command;
        break;

        default:
            return QVariant();
        break;
    }
}

QHash<int, QByteArray> GestureItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ImageRole] = "image";
    names[ReservedRole] = "reserved";
    names[AppRole] = "app";
    names[CommandRole] = "command";
    return names;
}

void GestureItem::setReserved(bool res)
{
    m_reserved = res;
}

void GestureItem::setApp(const QString& app)
{
    m_app = app;
}

void GestureItem::setCommand(const QString& cmd)
{
    m_command = cmd;
}
