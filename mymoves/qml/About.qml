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

BlackPage {
    id: about

    MyText {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 20
        font.pointSize: 48
        text: "About"
    }

    Column {
        id: aboutText
        anchors.centerIn: parent
        anchors.margins: 20
        spacing: 20

        MyText {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "MyMoves 0.1.4" // TODO: Get version number from elsewhere
        }

        MyText {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Topi Santakivi (sandst1)"
        }

        MyText {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "topi.santakivi@gmail.com"
        }
    }

    BlackButton {
        id: backbtn
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Back"
        onClicked: {
            pageStack.pop();
        }
    }
}
