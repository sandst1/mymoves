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
    id: container
    anchors.centerIn: parent
    color: "#000000"
    width: 400
    height: 800
    signal appSelected()

    property string selectedApp: ""
    property string selectedCmd: ""
    ListView {
        anchors.fill: parent
        spacing: 10
        model: AppListModel
        delegate: Rectangle {
                      id: delrect
                      width: 400
                      height: 100
                      border.width: 2
                      border.color: "#ffffff"
                      color: marea.pressed ? "#ffffff" : "#000000"
                      radius: 5
                      MyText {
                          id: nameText
                          anchors.fill: parent
                          anchors.centerIn: parent
                          text: name
                          color: marea.pressed ? "#000000" : "#ffffff"
                          horizontalAlignment: Text.AlignHCenter
                          verticalAlignment: Text.AlignVCenter
                      }

                      MouseArea {
                          id: marea
                          anchors.fill: parent

                          onReleased: {
                              container.selectedApp = name;
                              container.selectedCmd = command;
                              container.visible = false;
                              container.appSelected();
                          }
                      }
                  }
    }
}
