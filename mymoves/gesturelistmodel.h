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
#ifndef GESTURELISTMODEL_H
#define GESTURELISTMODEL_H

#include <QDeclarativeContext>
#include "listmodel.h"

class GestureItem;
class GestureListModel : public ListModel
{
    Q_OBJECT
public:
    explicit GestureListModel(ListItem* prototype, QObject *parent = 0);
    Q_INVOKABLE void saveItem(int index, const QString& app, const QString& command);
    void loadFromDisk();
    void saveToDisk();

    void setContextProperties(QDeclarativeContext* ctx);
signals:

public slots:

private:
    GestureListModel* m_selectedGests;

};

#endif // GESTURELISTMODEL_H
