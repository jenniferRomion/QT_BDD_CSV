import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0

import "content"
import "content/MyScript.js" as MyScript

Rectangle {
    width: 600
    height : 600
    color : "lightblue"
    id : root

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
                text : "Gestion des gares ferrovières de la région Ile de France"
                font.family: "Comic Sans MS"
                font.pointSize: 20
                verticalAlignment : TextEdit.AlignVCenter
            }

            Row {
                spacing : 10

                Button {
                    id : idBoutonCharger
                    width : root.largeurBouton
                    text : "Charger un fichier CSV"
                    onClicked : { navigateur.open()
                        MyScript.test()
                    }
                }

                Rectangle {
                    width: 600 ; height: idBoutonCharger.height
                    border.color: "grey"
                    color: "white"

                    TextEdit {
                        id : openedfilename
                        anchors.fill : parent
                        text : navigateur.fileUrl

                        font.family: "Calibri"
                    } }
            }

            Rectangle {
                width: 750 ; height: 100
                border.color: "grey"
                color: "white"
                ScrollView{
                    id :view
                    anchors.fill :parent
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                    TextArea {
                        id : previsualisationCSV
                        anchors.fill : parent
                        text : Context.propString
                        font.family: "Calibri"
                    } }}


            Button {
                id : idBoutonConvertfile
                width : root.largeurBouton
                text : "Convertir"
                onClicked : {
                    if (openedfilename.text != "")
                        Context.splitCSVFile()
                }
            }

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
                    model: UnModelARenseigner
                }

                TableView {
                    id : idtables
                    width: 200; height: 200
                    selectionMode : SelectionMode.MultiSelection
                    TableViewColumn{
                        role : "Tables"
                        title: "Tables"
                    }
                    model: ListeTables
                }

                Column {
                    spacing : 10

                    Rectangle {
                        width: Context.largeurBouton ; height: idBoutonCharger.height
                        border.color: "grey"
                        color: "white"

                        TextEdit {
                            id : tablename
                            anchors.fill : parent
                            text : ""
                            font.family: "Calibri"
                            font.pointSize: 12
                            verticalAlignment : TextEdit.AlignVCenter
                            horizontalAlignment : TextEdit.AlignHCenter
                        } }

                    Row {
                        spacing : 5

                        Button {
                            width : Context.largeurBouton
                            text : "Créer tables unitaires"
                            onClicked : {
                                //Context.createTablesUnitaires()
                                MyScript.tableunitaire();
                            }}

                        Button {
                            width : Context.largeurBouton
                            text : "Créer tables avec FK"
                            onClicked : {
                                //Context.createTablesWithFK()
                                MyScript.tableFK();
                            }}

                        Button {
                            width : Context.largeurBouton
                            text : "Créer tables relation"
                            onClicked : {
                                //Context.createTablesRelation()
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
                } //fin column
            }

            Button {
                width : Context.largeurBouton
                text : "Save in CSV"
                onClicked : {
                    Context.save(navigateur.folder)
                }}

            Button {
                width : Context.largeurBouton
                text : "test"
                onClicked : {

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

    }} //fin Rectangle
