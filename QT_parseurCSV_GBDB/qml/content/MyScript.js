function test() {
    console.log("test ok");

}

function tableunitaire() {
    var indice = '';
    indice = idCSV.currentRow;
    var nbIndice = '';
    nbIndice = idCSV.selection.count;

    if ( indice > -1 && tablename.text != "" && nbIndice ===1 ) {
        Context.createTablesUnitaires(tablename.text, indice);
        reset();
    }

    else {
        Context.setMessageErreur("Erreur dans l'initialisation des données \n
Entrer un nom de table \n
Selectionner une colonne CVS");
    }
}

function tableFK() {
    var indicecolonne = '';
    indicecolonne = idCSV.currentRow;

    var indiceTable;
    indiceTable = idtables.currentRow;

    var nbIndiceColonne = '';
    nbIndiceColonne = idCSV.selection.count;

    var nbIndiceTable ='';
    nbIndiceTable = idtables.selection.count;

    if ( indicecolonne > -1 && nbIndiceColonne ===1 && indiceTable > -1 && nbIndiceTable ===1 && tablename.text != "" ) {
        Context.createTablesWithFK(tablename.text, indicecolonne, indiceTable);
        reset();
    }
    else {
        Context.setMessageErreur("Erreur dans l'initialisation des données \n
Entrer un nom de table \n
Selectionner une colonne CVS \n
Selectionner une table à lier");
    }
}

function tableRelation() {
    var indicescolonnes = '';
    idCSV.selection.forEach( function(rowIndex) { indicescolonnes += (rowIndex + ";") } )
    console.log(indicescolonnes);

    var indicesTables = '';
    idtables.selection.forEach( function(rowIndex) { indicesTables += (rowIndex + ";") } )
    console.log(indicesTables);

    if ( indicesTables != "" && tablename.text != "" ) {
        Context.createTablesRelation(tablename.text, indicesTables, indicescolonnes);
        reset();
    }

    else {
        Context.setMessageErreur("Erreur dans l'initialisation des données \n
Entrer un nom de table \n
Selectionner les tables à lier \n
Selectionner les colonnes CSV à ajouter");
    }
}

function reset() {
    idCSV.selection.clear();
    idtables.selection.clear();
    tablename.text = "";
}

function reset2() {
    dbname.text = "";
    tablename.text = "";
    colonnes.text = "champs1, champs2, ...";
    Context.messageSGBD = "";
}

function insertInto() {
    var texte;
    texte = "INSERT INTO " + tablename.text + " ( "+ colonnes.text + " ) VALUES \n"
            + Context.messageSGBD + ";";
    return texte;
}
