import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2

Rectangle {
    id : root

    width: 500
    height : 600
    radius : 10
    border.width: 5
    border.color: "#1b6d2b"

    Column {
        x : 30 ;  y : 30
        spacing: 30

        TextArea {
            id : helptitre
            font.family: "Calibri"
            font.pointSize: 20
            font.bold: true

            text : "Aide"
        }

        TextArea {
            anchors.fill : root
            font.family: "Calibri"
            font.pointSize: 10

            text : "
1. Ouvrir le fichier .csv à parser \n
2. Lancer le parseur \n
3. Créer les tables unitaires (format : id ; valeur) \n
    - selectionner une colonne du fichier .csv \n
    - entrer le nom de la table à créer \n
    - cliquer sur U+ \n
4. Créer les tables de relation (x,1)-(x,n) \
    - selectionner une colonne du fichier .csv \n
    - selectionner la table liée \n
    - entrer le nom de la table à créer \n
    - cliquer sur FK+ \n
5. Créer les tables de relation (x,n)-(x,n) ou n-tiers \n
    - selectionner les tables liées \n
    - selectionner les colonnes du fichier .csv à ajouter (facultatif) \n
    - entrer le nom de la table à créer \n
    - cliquer sur R+ \n
6. Sauvergarder les tables crées sous forme de fichiers .csv"
        }


}
    }
