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
    id: newMove
    tools: commonTools

    orientationLock: PageOrientation.LockPortrait

    Column {
        id: pageColumn
        height: children.height
        anchors.margins: 20
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        Rectangle {
            id: box
            border.width: 5
            border.color: "#0000bb"
            radius: 10
            color: "#000000"
            width: 440
            height: 600
            anchors.horizontalCenter: parent.horizontalCenter

            property bool pressed: false
            property bool gestureExists: false

            property variant ctx: canvas.getContext("2d");

            Canvas {
                id: canvas
                anchors.fill: parent
            }           

            /*MouseArea {
                anchors.fill: parent
                id: touchArea
                onPressed: {
                    box.ctx.fillStyle="#000000";
                    box.ctx.clear();
                    box.ctx.fillStyle = "#ffffff";
                    box.ctx.strokeStyle = "#ffffff";
                    box.ctx.fillRect(mouseX-4, mouseY-4, 9, 9);
                }

                onPositionChanged: {
                    box.ctx.fillRect(mouseX-4, mouseY-4, 9, 9);
                }

                onReleased: {
                    box.gestureExists = true;
                    box.ctx.fillRect(mouseX-4, mouseY-4, 9, 9);
                }
            }*/

            TouchArea {
                  id: touchArea
                  anchors.fill: parent

                  minimumTouches: 1
                  maximumTouches: 5

                  touchPoints: [
                      TouchPoint {
                      },
                      TouchPoint {
                      },
                      TouchPoint {
                      },
                      TouchPoint {
                      },
                      TouchPoint {
                      }
                  ]

                  onTouchStart: {
                      box.gestureExists = false;
                      for (var i=0; i < touchArea.touches.length; i++) {                          
                          var touch = touchArea.touches[i];                          
                          box.ctx.fillStyle="#000000";
                          box.ctx.clear();                          
                          box.ctx.fillStyle = "#ffffff";
                          box.ctx.strokeStyle = "#ffffff";
                          box.ctx.fillRect(touch.x-4, touch.y-4, 9, 9);
                      }
                  }

                  onTouchMove: {
                      for (var i=0; i < touchArea.touches.length; i++) {
                          var touch = touchArea.touches[i];
                          box.ctx.fillRect(touch.x-4, touch.y-4, 9, 9);
                      }
                  }

                  onTouchEnd: {
                      console.log("Setting gestureExists to true");
                      box.gestureExists = true;
                  }
            }

            Component.onCompleted: {
                box.ctx.fillStyle="#000000";
                box.ctx.clear();
                MyMovesInterface.recordGesture(20, 20, 20+box.width, 20+box.height);
            }
        }
/*
        TextField {
            id: commandText
            anchors.horizontalCenter: parent.horizontalCenter
            width: newMove.width*0.8
            placeholderText: "Command"
            maximumLength: 120
        }
*/
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            id: saveButton
            text: "Save"
            onClicked: {
                console.log("Save button clicked!");
                if (box.gestureExists) {
                    console.log("Gesture exists!");
                    canvas.save("/home/user/MyDocs/.moves/imgmymove"+MyMovesInterface.newGestureNumber()+".png");
                    //MyMovesInterface.saveGesture(commandText.text);
                    MyMovesInterface.saveGesture("Add your command here");
                    textDialog.text = "Gesture Saved";
                    textDialog.show();
                } else {
                    console.log("Gesture doesn't exist!");
                }
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            id: clearButton
            text: "Clear"
            onClicked: {
                if (box.gestureExists) {
                    box.ctx.fillStyle="#000000";
                    box.ctx.clear();
                    box.gestureExists = false;
                }
            }
        }
    }


    TextDialog {
        id: textDialog
        onDialogClosing: {
            pageStack.pop();
        }
    }
}
