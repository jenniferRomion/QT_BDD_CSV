import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0

Rectangle {
    width: 600
    height : 600
    color : "lightblue"
    id : root
    property int largeurBouton : 140 // Context.largeurBoutton



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
            onClicked : { Context.splitCSVFile()
            }
        }

        Row {
            spacing: 10

            TableView {
                id : idTV
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
                model: listeEntierPourEvaluation
            }
        }

        Row {
            spacing : 10

            Button {
                width : Context.largeurBouton
                text : "Créer tables unitaires"
                onClicked : {
                    var ligne = ''
                    idTV.selection.forEach( function(rowIndex) {
                        ligne += idTV.model[rowIndex] + ";"
                    } )

                    Context.createTablesUnitaires()
                }
            }

            Button {
                width : Context.largeurBouton
                text : "Créer tables avec FK"
                onClicked : {
                    var ligne = ''
                    idTV.selection.forEach( function(rowIndex) {
                        ligne += idTV.model[rowIndex] + ";"
                    } )

                    Context.createTablesWithFK()
                }
            }

            Button {
                width : Context.largeurBouton
                text : "Créer tables relation"
                onClicked : {
                    var ligne = ''
                    idTV.selection.forEach( function(rowIndex) {
                        ligne += idTV.model[rowIndex] + ";"
                    } )

                    Context.createTablesRelation()
                }
            }
        }

        Button {
            width : Context.largeurBouton
            text : "Save in CSV"
            onClicked : {
                Context.save(navigateur.folder)
            }
        }

    }


    FileDialog {
        id: navigateur
        folder: shortcuts.documents
        selectFolder: false
        onAccepted: {
            Context.openCSVfile(navigateur.fileUrl)
            navigateur.close()}
    }




}
