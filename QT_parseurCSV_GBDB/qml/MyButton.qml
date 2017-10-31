import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button {
    style: ButtonStyle {
        background: Rectangle {
            implicitWidth : 140
            implicitHeight: 30
            radius : 4
            border.color: "#1b6d2b"


            gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#65d877" : "#7ae28a" }
                            GradientStop { position: 1 ; color: control.pressed ? "#7ae28a" : "#65d877" }
        }
    }
}}
