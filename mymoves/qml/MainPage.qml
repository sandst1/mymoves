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
import "serverstatus.js" as SERVER

BlackPage {
    id: mainPage
    property int serverStatusToPreserve: -1
    property int serverStatus: -1

    Column {
        anchors.centerIn: parent
        spacing: 100
        Image {
            id: logo
            source: "qrc:///images/mymoves_120x120.png"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Column {
            id: buttonCol
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 30

            MyText {
                anchors.horizontalCenter: parent.horizontalCenter
                text: mainPage.serverStatus == SERVER.IDLE ? "Not observing gestures" : "Observing gestures"
            }

            BlackButton {
                id: serverCtrlBtn
                anchors.horizontalCenter: parent.horizontalCenter
                text: mainPage.serverStatus == SERVER.IDLE ? "Start observing" : "Stop observing"
                onClicked: {
                    if (mainPage.serverStatus == SERVER.IDLE)
                    {
                        MyMovesInterface.observeGestures();
                        MyMovesInterface.setServerObservingOnExit(true);
                    }
                    else
                    {
                        MyMovesInterface.stopObserving();
                        MyMovesInterface.setServerObservingOnExit(false);
                    }
                    mainPage.serverStatus = MyMovesInterface.serverStatus();
                }
            }

            BlackButton {
                id: myMoves
                anchors.horizontalCenter: parent.horizontalCenter
                text: "My moves"
                onClicked: {
                    pageStack.push("qrc:/qml/MyMoves.qml");
                    mainPage.serverStatusToPreserve = mainPage.serverStatus;
                    if (mainPage.serverStatus != SERVER.IDLE)
                    {
                        MyMovesInterface.stopObserving();
                    }
                }
            }

            BlackButton {
                id: about
                anchors.horizontalCenter: parent.horizontalCenter
                text: "About"
                onClicked: {
                    pageStack.push("qrc:/qml/About.qml");
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("MainPage onCompleted");
        mainPage.serverStatus = MyMovesInterface.serverStatus();
        if (mainPage.serverStatus == SERVER.IDLE)
        {
            MyMovesInterface.setServerObservingOnExit(false);
        }
        else
        {
            MyMovesInterface.setServerObservingOnExit(true);
        }
    }
}
