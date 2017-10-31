import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0

import "content/MyScript.js" as MyScript

Rectangle {
    id : root2

    width: 825
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
                    color: "#cedbd0"

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
            }

            Rectangle {
                height: 20
                width : 20
            }

            Row {
                spacing : 10

                Rectangle {
                    width: 140 ; height: 30
                    border.color: "#1b6d2b"
                    color: "white"

                    TextEdit {
                        id : dbname
                        anchors.fill : parent
                        text : ""
                        font.family: "Calibri"
                        font.pointSize: 12
                        verticalAlignment : TextEdit.AlignVCenter
                        horizontalAlignment : TextEdit.AlignHCenter
                    } }

                MyButton {
                    id : idboutonconnexion
                    width : Context.largeurBouton
                    text : "Connexion"
                    onClicked : {
                        Context.usingDatabase("connexion", dbname.text)
                    }}

                MyButton {
                    width : Context.largeurBouton
                    text : "Nouvelle Db"
                    onClicked : {
                        Context.usingDatabase("create", dbname.text)
                    }}

                MyButton {
                    width : Context.largeurBouton
                    text : "Supprimer Db"
                    onClicked : {
                        Context.usingDatabase("delete", dbname.text)
                    }}

                MyButton {
                    width : Context.largeurBouton
                    text : "Insérer données"
                    onClicked : {
                        Context.load("LoadData")
                    }}
            }

            ComboBox {
                id :querySelector
                width: 740
                height : 30
                editable: true

                model : ListModel {
                    ListElement {text : "SHOW DATABASES"}
                    ListElement {text : "SHOW FULL TABLES;"}
                    ListElement {text : "SHOW COLUMNS FROM 'table'"}
                    ListElement {text : "SHOW FULL FIELDS FROM 'table'"}
                    ListElement {text : "DESCRIBE 'table'"}
                    ListElement {text : "SELECT * FROM 'table'"}
                    ListElement {text : "EXPLAIN 'table'"}

                }}

            ScrollView{
                id :view
                width: 740 ; height: 150
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                TextArea {
                    id : script
                    text : querySelector.currentText
                    font.family: "Calibri"
                    font.pointSize: 11
                    verticalAlignment : TextEdit.AlignVCenter
                    selectByMouse: true
                    wrapMode: TextEdit.Wrap

                    background : Rectangle {
                        border.color: "#1b6d2b"
                        color: "white"
                    }}}

            MyButton {
                width : Context.largeurBouton
                text : "Executer script"
                onClicked : {
                    Context.executeScriptSQL(script.text)
                }}

            TableView {
                id : test
                model : Context.queryResult
                width :740

                TableViewColumn{
                    title : "Result"
                }
            }

        }//fin Column
} //fin Rectangle

