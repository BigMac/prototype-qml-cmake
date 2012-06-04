// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 80
    height: 60
    color: "blue"
    border.color: "yellow"
    border.width: 2
    Text {
        text: qsTr("sub2")
        anchors.centerIn: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }
}
