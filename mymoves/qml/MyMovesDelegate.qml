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
import QtQuick 1.1
import com.meego 1.0

Rectangle {
    id: delrect
    width: 350
    height: 300
    anchors.horizontalCenter: parent.horizontalCenter
    border.color: "#000080"
    border.width: 3
    color: "#000000"
    radius: 5

    property string appText: (app == "") ? "no app" : app

    signal clicked()
    Item {
        id: img
        width: 220
        height: 220
        anchors.topMargin: 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        Image {
            width: 200
            height: 200
            anchors.centerIn: parent
            source: image
        }
    }

    MyText {
        anchors.top: img.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        text: delrect.appText
        color: "#ffffff"
    }

    MouseArea {
        id: marea
        anchors.fill: parent       

        onClicked: {
            delrect.clicked();
        }
    }
}
