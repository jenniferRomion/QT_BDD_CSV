import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0

import "content/MyScript.js" as MyScript

Rectangle {
    id : root

    width: 880
    height : 600
    radius : 30
    border.width: 30
    border.color: "#1b6d2b"
    color : "white"

    Column {
        spacing : 10
        x : 40
        y : 40

        Row {
            spacing : 16

            Rectangle {
                width: 37 ; height: 40
                Image {
                    anchors.fill : parent
                    source : "content/images/logo.jpg"
                    sourceSize.width: 215
                    sourceSize.height: 234
                }}

            Rectangle {
                height : 40
                width : 340

                Text {
                    id : titreGBDG
                    anchors.fill : parent
                    color : "#1b6d2b"
                    text : "QT-ParseurCSV"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Comic Sans MS"
                    font.pointSize: 20
                    verticalAlignment : TextEdit.AlignVCenter
                }}

            Rectangle {
                height : 40
                width : 340
                color: "#cedbd0"

                MouseArea {
                    z : 3
                    anchors.fill: parent
                    onClicked : { Context.load("gbdb") }
                }

                Text {
                    id : titre
                    width: 350
                    anchors.fill : parent
                    color : "#1b6d2b"
                    text : "Gestionnaire BdD"
                    horizontalAlignment: Text.AlignHCenter
                    font.family: "Comic Sans MS"
                    font.pointSize: 20
                    verticalAlignment : TextEdit.AlignVCenter

                }}

            Rectangle {
                width: 39.3 ; height: 40
                MouseArea {
                    z : 3
                    anchors.fill: parent
                    onClicked: {Context.load("help")} }
                Image {
                    anchors.fill : parent
                    source : "content/images/help.jpg"
                    sourceSize.width: 161
                    sourceSize.height: 164

                }}
        }

        Rectangle {
            height: 20
            width : 20
        }

        Row {

            Rectangle {
                width: 660 ; height: 30
                border.color: "#1b6d2b"
                radius : 4
                color: "white"

                TextEdit {
                    id : openedfilename
                    anchors.fill : parent
                    text : navigateur.fileUrl

                    font.family: "Calibri"
                    verticalAlignment : TextEdit.AlignVCenter
                }}

            MyButton {
                id : idBoutonCharger
                text : "Charger"
                onClicked : { navigateur.open() }
            }
        }

        ScrollView{
            id :view
            width: 800 ; height: 100
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn

            TextArea {
                id : previsualisationCSV
                anchors.fill : parent
                text : Context.propString
                font.family: "Calibri"

                background: Rectangle {
                    border.color: "#1b6d2b"
                    radius : 4
                    color: "white"
                }}}


        MyButton {
            id : idBoutonConvertfile
            text : "Convertir"
            onClicked : {
                if (openedfilename.text != "")
                    Context.splitCSVFile()
            }}

        Row {
            spacing: 5

            TableView {
                id : idCSV
                width: 200; height: 200
                selectionMode : SelectionMode.MultiSelection

                TableViewColumn{
                    role : "Valeurs"
                    title: "Valeurs"
                }

                itemDelegate : Rectangle {
                    color : styleData.selected ? "#1b6d2b" : "transparent"
                    Text{
                        text : modelData}
                }

                model: UnModelARenseigner
            }

            TableView {
                id : idtables
                width: 200; height: 200
                selectionMode : SelectionMode.MultiSelection

                TableViewColumn {
                    role : "Tables"
                    title: "Tables"
                }

                itemDelegate : Rectangle {
                    color : styleData.selected ? "#1b6d2b" : "transparent"
                    Text{
                        text : modelData}
                }

                model: ListeTables
            }

            Column {
                spacing : 10

                Rectangle {
                    width: Context.largeurBouton ; height: idBoutonCharger.height
                    border.color: "#1b6d2b"
                    color: "white"

                    TextEdit {
                        id : tablename
                        anchors.fill : parent
                        text : ""
                        font.family: "Calibri"
                        font.pointSize: 12
                        verticalAlignment : TextEdit.AlignVCenter
                        horizontalAlignment : TextEdit.AlignHCenter
                        wrapMode: TextEdit.Wrap

                    } }

                Row {
                    spacing : 30

                    Column {
                        spacing: 5

                        MyButton {
                            width : 50
                            text : "U+"
                            onClicked : {
                                MyScript.tableunitaire();
                            }}

                        MyButton {
                            width : 50
                            text : "FK+"
                            onClicked : {
                                MyScript.tableFK();
                            }}

                        MyButton {
                            width : 50
                            text : "R+"
                            onClicked : {
                                MyScript.tableRelation();
                            }}
                    }

                    Text {
                        id : messageErreur
                        height : 15
                        width : 140
                        color : "red"
                        text : Context.messageErreur
                        font.family: "Calibri"
                        font.pointSize: 10
                    }
                }
            }}

        MyButton {
            text : "Sauvegarder"
            onClicked : {
                Context.save(navigateur.folder)
            }}



    } //fin column


    FileDialog {
        id: navigateur
        folder: shortcuts.documents
        selectFolder: false
        onAccepted: {
            Context.openCSVfile(navigateur.fileUrl)
            navigateur.close()
        }}

} //fin Rectangle
