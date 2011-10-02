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
        id: titleText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
        font.pointSize: 40
        text: "Using MyMoves"
    }

    Rectangle {
        id: textRect
        width: 460
        height: 675
        anchors.topMargin: 10
        anchors.centerIn: parent
        border.color: "#ffffff"
        border.width: 3
        radius: 5
        color: "#000000"

        Column {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            spacing: 10
            MyText {
                width: parent.width
                text: "1. Select your applications in the 'My Moves' view."
                wrapMode: Text.WordWrap
            }

            MyText {
                width: parent.width
                text: "2. Make sure the main page text is saying 'Observing gestures'."
                wrapMode: Text.WordWrap
            }

            MyText {
                width: parent.width
                text: "Now you're ready to use the gestures. They work anywhere in the system."
                wrapMode: Text.WordWrap
            }

            MyText {
                width: parent.width
                text: "<b>Using two-finger gestures:</b> hold your fingers together like holding a pencil and make a gesture."
                wrapMode: Text.WordWrap
            }

            MyText {
                width: parent.width
                text: "<b>Using three-finger gestures:</b> hold your fingers like in two-finger gestures but add a third finger on top and make a gesture."
                wrapMode: Text.WordWrap
            }
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
