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
#ifndef GESTUREITEM_H
#define GESTUREITEM_H

#include "listmodel.h"

class GestureItem : public ListItem
{
    Q_OBJECT

    Q_PROPERTY(bool reserved READ reserved WRITE setReserved)
public:
    enum Roles {
        ImageRole = Qt::UserRole+1,
        ReservedRole,
        AppRole,
        CommandRole
    };

    GestureItem(QObject *parent = 0): ListItem(parent) {}
    explicit GestureItem(const QString& id, const QString& image, QObject *parent = 0);
    GestureItem(const GestureItem& item, QObject* parent = 0);

    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    void setReserved(bool res);
    void setApp(const QString& app);
    void setCommand(const QString& cmd);

    inline QString id() const { return m_id; }
    inline QString image() const { return m_image; }
    inline bool reserved() const { return m_reserved; }
    inline QString app() const { return m_app; }    
    inline QString command() const { return m_command; }

signals:
    void dataChanged();
public slots:

private:
    QString m_id;
    QString m_image;
    bool m_reserved;
    QString m_app;
    QString m_command;
};

#endif // GESTUREITEM_H
