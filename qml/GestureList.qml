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

Item {
    id: container
    anchors.centerIn: parent
    width: 400
    height: 800

    property string selectedGesture: ""
    property int    selectedIndex: -1

    ListView {
        anchors.fill: parent
        spacing: 10
        model: GestureListModel
        delegate: Rectangle {
                      id: delrect
                      width: 400
                      height: 200
                      anchors.horizontalCenter: parent.horizontalCenter
                      border.color: "#0000ff"
                      border.width: 3
                      color: reserved ? "#8c8c8c" : "#ffffff"
                      radius: 5                      
                      Image {
                          width: 200
                          height: 200
                          anchors.centerIn: parent
                          source: image
                      }

                      MouseArea {
                          anchors.fill: parent

                          onReleased: {
                              if (!reserved) {
                                  container.selectedGesture = image;
                                  container.selectedIndex   = index;
                                  container.visible = false;
                              }
                          }
                      }
                  }
    }
}
