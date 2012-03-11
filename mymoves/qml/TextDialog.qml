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
import QtQuick 1.1

Rectangle {
    id: textDialog
    width: parent.width * 0.8
    height: parent.height * 0.5
    anchors.centerIn: parent
    state: "hidden"
    color: "#000000"
    radius: 10
    signal dialogClosing()

    property alias timer: dialogTimer;
    property string text: "Default"

    function show() {
        textDialog.state = "visible";
        textDialog.timer.start();
    }

    Text {
        id: textBox
        anchors.centerIn: parent
        font.pointSize: 25
        color: "#ffffff"
        text: textDialog.text
    }

    Timer {
        id: dialogTimer
        repeat: false
        interval: 2000

        onTriggered: {
            textDialog.dialogClosing();
            textDialog.state = "hidden";
        }
    }

    states: [
        State {
            name: "hidden"
            PropertyChanges { target: textDialog; opacity: 0; }
        },
        State {
            name: "visible"
            PropertyChanges { target: textDialog; opacity: 0.8; }
        }
    ]

    transitions: [
        Transition {
            to: "visible"
            from: "hidden"
            reversible: true
            PropertyAnimation {
                target: textDialog
                property: "opacity"
                duration: 500
            }
        }
    ]
}
