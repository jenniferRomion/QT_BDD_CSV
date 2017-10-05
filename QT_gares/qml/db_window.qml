import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0

import "content/MyScript.js" as MyScript

Rectangle {
    width: 600
    height : 600
    color : "lightblue"
    id : root2

    ScrollView{
        anchors.fill :parent
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        Column {
            spacing : 10
            x : 10

            Text {
                id : titre
                height : 40
                width : 140
                color : "blue"
                text : "QT-Gestionnaire BDD"
                font.family: "Comic Sans MS"
                font.pointSize: 20
                verticalAlignment : TextEdit.AlignVCenter
            }

            Row {
                spacing : 10

                Rectangle {
                    width: Context.largeurBouton ; height: idboutonconnexion.height
                    border.color: "grey"
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

                Button {
                    id : idboutonconnexion
                    width : Context.largeurBouton
                    text : "connexion"
                    onClicked : {
                        Context.usingDatabase("connexion", dbname.text)
                    }}

                Button {
                    width : Context.largeurBouton
                    text : "create"
                    onClicked : {
                        Context.usingDatabase("create", dbname.text)
                    }}

                Button {
                    width : Context.largeurBouton
                    text : "delete"
                    onClicked : {
                        Context.usingDatabase("delete", dbname.text)
                    }}

                Button {
                    width : Context.largeurBouton
                    text : "load data"
                    onClicked : {
                        Context.load("LoadData")
                    }}
            }

            ComboBox {
                id :querySelector
                width: 500
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

            Rectangle {
                width: 500 ; height: 150
                border.color: "grey"
                color: "white"
                ScrollView{
                    id :view
                    anchors.fill :parent
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                    TextEdit {
                        id : script
                        anchors.fill : parent
                        text : querySelector.currentText
                        font.family: "Calibri"
                        font.pointSize: 11
                        verticalAlignment : TextEdit.AlignVCenter
                        horizontalAlignment : TextEdit.AlignHCenter
                        selectByMouse: true
                    }}}

            Button {
                width : Context.largeurBouton
                text : "executer script"
                onClicked : {
                    Context.executeScriptSQL(script.text)
                }}

            TableView {
                id : test
                model : Context.queryResult
                width :500

                TableViewColumn{
                    title : "Result"
                }
            }

        }//fin Column
    } //fin ScrollView
} //fin Rectangle

