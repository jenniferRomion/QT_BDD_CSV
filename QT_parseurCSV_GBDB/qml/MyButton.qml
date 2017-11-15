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
                            GradientStop { position: 0 ; color: control.hovered ? "#65d877" : "#40a479" }
                            GradientStop { position: 1 ; color: control.hovered ? "#40a479" : "#65d877" }
        }
    }
}}
