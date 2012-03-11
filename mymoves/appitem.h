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
#ifndef APPITEM_H
#define APPITEM_H

#include <QByteArray>
#include <QHash>
#include <QObject>
#include <QString>
#include <QVariant>

#include <QDebug>
#include "listmodel.h"
//#include "app.h"

class AppItem : public ListItem
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole+1
        ,CommandRole
        ,IconRole
    };

    AppItem(QObject* parent = 0): ListItem(parent) {}
    explicit AppItem(const QString& name, const QString& command, const QString& icon, QObject *parent = 0);
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    inline QString id() const { return m_name; }

    inline QString name() const { return m_name; }
    inline QString command() const { return m_command; }
    inline QString icon() const { return m_icon; }
signals:
    void dataChanged();
public slots:

private:
    QString m_name;
    QString m_command;
    QString m_icon;
};

#endif // APPITEM_H
