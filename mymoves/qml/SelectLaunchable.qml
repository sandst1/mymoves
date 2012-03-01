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

Rectangle {
    id: selectPage
    anchors.fill: parent
    color: "#000000"

    property string selectedName: ""
    property string selectedCmd: ""
    visible: false;

    signal itemSelected()

    Column {
        id: buttonCol
        anchors.centerIn: parent
        spacing: 30

        BlackButton {
            id: actionBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Action"
            onClicked: {
                actionList.visible = true;
            }
        }

        BlackButton {
            id: appBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Application"
            onClicked: {
                appList.visible = true;
            }
        }

        BlackButton {
            id: bookmarkBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Bookmark"
            onClicked: {
                bookmarksList.visible = true;
            }
        }

        BlackButton {
            id: clearBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Clear item"
            onClicked: {
                selectPage.selectedName = "";
                selectPage.selectedCmd = "";
                selectPage.visible = false;
                selectPage.itemSelected();
            }
        }

        BlackButton {
            id: cancelBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Cancel"
            onClicked: {
                selectPage.visible = false;
            }
        }

        /*BlackButton {
            id: contactBtn
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Contact"
            onClicked: {
            }
        }*/
    }

    AppList {
        id: appList
        visible: false

        model: AppListModel

        onItemSelected: {
            selectPage.selectedName = appList.selectedApp;
            selectPage.selectedCmd = appList.selectedCmd;
            selectPage.visible = false;
            selectPage.itemSelected();
        }
    }

    AppList {
        id: actionList
        visible: false

        model: ActionsModel

        onItemSelected: {
            selectPage.selectedName = actionList.selectedApp;
            selectPage.selectedCmd = actionList.selectedCmd;
            selectPage.visible = false;
            selectPage.itemSelected();
        }
    }

    AppList {
        id: bookmarksList
        visible: false

        model: BookmarksModel

        onItemSelected: {
            selectPage.selectedName = bookmarksList.selectedApp;
            selectPage.selectedCmd = bookmarksList.selectedCmd;
            selectPage.visible = false;
            selectPage.itemSelected();
        }
    }
}
