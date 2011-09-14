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
import QmlCanvas 1.0
Page {
    id: mainPage
    tools: commonTools    

    orientationLock: PageOrientation.LockPortrait

    Column {
        anchors.centerIn: parent
        spacing: 20
        /*Button {
            id: recButton
            text: "New Move"
            onClicked: {
                pageStack.push("qrc:/qml/NewMove.qml");
            }
        }*/

        Button {
            id: myMoves
            text: "My moves"
            onClicked: {
                pageStack.push("qrc:/qml/MyMoves.qml");
            }
        }

        Button {
            id: addMove
            text: "Add a move"
            onClicked: {
                pageStack.push("qrc:/qml/AddMove.qml");
            }
        }

        Button {
            id: observeButton
            text: "Start observing gestures"
            onClicked: {
                MyMovesInterface.observeGestures();
            }
        }

        Button {
            id: stopObserving
            text: "Stop observing"
            onClicked: {
                MyMovesInterface.stopObserving();
            }
        }
    }
}
