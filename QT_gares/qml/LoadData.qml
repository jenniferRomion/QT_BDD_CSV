import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0


import "content/MyScript.js" as MyScript

Rectangle {
    width: 400
    height : 200
    color : "lightblue"
    id : root2

    ScrollView {
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
                text : "Load Data"
                font.family: "Comic Sans MS"
                font.pointSize: 14
                verticalAlignment : TextEdit.AlignVCenter
            }

            Row {
                spacing : 10

                Button {
                    id : idboutonconnexion
                    width : ref.width
                    text : "Open file"
                    onClicked : {
                        navigateur2.open()
                    }}

                Rectangle {
                    width: 400 ; height: idboutonconnexion.height
                    border.color: "grey"
                    color: "white"

                    TextEdit {
                        id : dbname
                        anchors.fill : parent
                        text : navigateur2.fileUrl
                        font.family: "Calibri"
                        font.pointSize: 12
                        verticalAlignment : TextEdit.AlignVCenter
                        horizontalAlignment : TextEdit.AlignHCenter
                    } }
            }

            Row {
                spacing : 10

                Text {
                    height : idboutonconnexion.height
                    width : ref.width
                    color : "blue"
                    text : "Nom de la table"
                    font.family: "Calibri"
                    font.pointSize: 10
                    verticalAlignment : TextEdit.AlignVCenter
                }

                Rectangle {
                    width: 400 ; height: idboutonconnexion.height
                    border.color: "grey"
                    color: "white"

                    TextEdit {
                        id : tablename
                        anchors.fill : parent
                        text : ""
                        font.family: "Calibri"
                        font.pointSize: 10
                        verticalAlignment : TextEdit.AlignVCenter
                        horizontalAlignment : TextEdit.AlignHCenter
                        selectByMouse: true
                    } }
            }

            Row {
                spacing : 10

                Text {
                    id : ref
                    height : idboutonconnexion.height
                    color : "blue"
                    text : "Nom des champs"
                    font.family: "Calibri"
                    font.pointSize: 10
                    verticalAlignment : TextEdit.AlignVCenter
                }

                Rectangle {
                    width: 400 ; height: idboutonconnexion.height
                    border.color: "grey"
                    color: "white"

                    TextEdit {
                        id : colonnes
                        anchors.fill : parent
                        text : "champs1, champs2, ..."
                        font.family: "Calibri"
                        font.pointSize: 10
                        verticalAlignment : TextEdit.AlignVCenter
                        horizontalAlignment : TextEdit.AlignHCenter
                        selectByMouse: true
                    } }
            }

            Rectangle {
                width: 400 + 10 + ref.width ; height: idboutonconnexion.height
                border.color: "grey"
                color: "white"
                ScrollView{
                    id :view
                    anchors.fill :parent
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                    TextEdit {
                        id : texte
                        anchors.fill : parent
                        text : MyScript.insertInto()
                        font.family: "Calibri"
                        font.pointSize: 10
                        verticalAlignment : TextEdit.AlignVCenter
                        horizontalAlignment : TextEdit.AlignHCenter
                        selectByMouse: true
                    } } }

            Button {
                id : idboutonsubmit
                width : ref.width
                text : "Submit"
                onClicked : {
                    Context.executeScriptSQL()
                    MyScript.reset2(view.text);
                }}

        }


        FileDialog {
            id: navigateur2
            folder: shortcuts.documents
            selectFolder: false
            onAccepted: {
                Context.insertDataFromCSVFile(navigateur2.fileUrl)
                navigateur2.close()
            }}
    }} //fin rectangle
