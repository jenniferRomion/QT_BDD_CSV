import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0


import "content/MyScript.js" as MyScript

Rectangle {
    width: 550
    height : 370
    radius : 10
    border.width: 15
    border.color: "#1b6d2b"
    color : "white"
    id : root2

    Column {
        spacing : 10
        x : 25 ; y : 20

        Text {
            id : titre
            height : 40
            width : 140
            color : "#1b6d2b"
            text : "Insertion de données"
            font.family: "Comic Sans MS"
            font.pointSize: 14
            verticalAlignment : TextEdit.AlignVCenter

        }

        Row {
            spacing : 10

            MyButton {
                id : idboutonconnexion
                width : ref.width
                text : "Open file"
                onClicked : {
                    navigateur2.open()
                }}

            Rectangle {
                width: 400 ; height: idboutonconnexion.height
                border.color: "#1b6d2b"
                color: "white"

                TextEdit {
                    id : dbname
                    anchors.fill : parent
                    text : ""
                    font.family: "Calibri"
                    font.pointSize: 10
                    verticalAlignment : TextEdit.AlignVCenter
                    wrapMode: TextEdit.Wrap

                } }
        }

        Row {
            spacing : 10

            Text {
                height : idboutonconnexion.height
                width : ref.width
                color : "#1b6d2b"
                text : "Nom de la table"
                font.family: "Calibri"
                font.pointSize: 10
                verticalAlignment : TextEdit.AlignVCenter
                wrapMode: TextEdit.Wrap
            }

            Rectangle {
                width: 400 ; height: idboutonconnexion.height
                border.color: "#1b6d2b"
                color: "white"

                TextEdit {
                    id : tablename
                    anchors.fill : parent
                    text : ""
                    font.family: "Calibri"
                    font.pointSize: 10
                    verticalAlignment : TextEdit.AlignVCenter
                    horizontalAlignment : TextEdit.AlignHCenter
                    wrapMode: TextEdit.Wrap
                    selectByMouse: true
                } }
        }

        Row {
            spacing : 10

            Text {
                id : ref
                height : idboutonconnexion.height
                color : "#1b6d2b"
                text : "Nom des champs"
                font.family: "Calibri"
                font.pointSize: 10
                verticalAlignment : TextEdit.AlignVCenter
                wrapMode: TextEdit.Wrap

            }

            Rectangle {
                width: 400 ; height: idboutonconnexion.height
                border.color: "#1b6d2b"
                color: "white"

                TextEdit {
                    id : colonnes
                    anchors.fill : parent
                    text : "champs1, champs2, ..."
                    font.family: "Calibri"
                    font.pointSize: 10
                    verticalAlignment : TextEdit.AlignVCenter
                    horizontalAlignment : TextEdit.AlignHCenter
                    wrapMode: TextEdit.Wrap
                    selectByMouse: true
                }}
        }

        ScrollView{
            id :view
            width: 400 + 10 + ref.width ; height: 100
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            TextArea {
                id : texte
                text : MyScript.insertInto()
                font.family: "Calibri"
                font.pointSize: 10
                wrapMode: TextEdit.WordWrap
                selectByMouse: true

                background : Rectangle {
                    border.color: "#1b6d2b"
                    color: "white"
                }}}

        MyButton {
            id : idboutonsubmit
            width : ref.width
            text : "Submit"
            onClicked : {
                Context.executeScriptSQL(texte.text)
                MyScript.reset2(view.text);
            }}

    }


    FileDialog {
        id: navigateur2
        folder: shortcuts.documents
        selectFolder: false
        onAccepted: {
            dbname.text = navigateur2.fileUrl
            Context.insertDataFromCSVFile(navigateur2.fileUrl)
            navigateur2.close()
        }}
} //fin rectangle
