#include "table.h"
#include "utile.h"

Table::Table()
{
}

//Get & Set

QStringList Table::fileCSV() const
{
    return m_fileCSV;
}

void Table::setFileCSV(const QString &fileCSV)
{
    m_fileCSV = fileCSV.split('\n');
}

std::vector<std::vector<QString> > Table::tableau_valeurs() const
{
    return m_tableau_valeurs;
}

void Table::setTableau_valeurs(const std::vector<std::vector<QString> > &tableau_valeurs)
{
    m_tableau_valeurs = tableau_valeurs;
}

/* ********methodes privées*********** */

QStringList Table::addIdToTable(QStringList valTab)
{
    QStringList id;

    for (int j(0) ; j< valTab.size() ; j++)
    {
        id << QString::number(j);
    }

    return id;
}

QStringList Table::fillMainColumn(int indice)
{
    QStringList valeurs;

    for (size_t i(0) ; i < m_tableau_valeurs.size()-1 ; i++)
    {
        valeurs << m_tableau_valeurs[i][indice];
    }

    return valeurs;
}

std::vector<QStringList> Table::joinColumnsIntoTable(QStringList valeurs)
{
    std::vector<QStringList> table;

    valeurs.removeDuplicates();
    table.push_back(addIdToTable(valeurs));
    table.push_back(valeurs);

    return table;
}

QStringList Table::extractColumnCSVFromIdTable(int idTable)
{
    QStringList columnsCSV;

    QString titreTable = m_baseMCD[idTable][1][0];

    QStringList titrecolonne;
    titrecolonne << titreTable.split(";");

    for (size_t j(0) ; j< m_tableau_valeurs[0].size() ; j++)
    {
        if (m_tableau_valeurs[0][j] == titrecolonne[0])
        {
            columnsCSV << fillMainColumn( (int)j) ;
            j = m_tableau_valeurs[0].size();
        }
    }

    if (titrecolonne.size() > 1)
    {
        for (size_t k(1) ; k < titrecolonne.size() ; k++)
        {
            for (size_t j(0) ; j< m_tableau_valeurs[0].size() ; j++)
            {
                if (m_tableau_valeurs[0][(int)j] == titrecolonne[(int)k])
                {
                    for ( size_t l(0) ; l < columnsCSV.size() ; l++)
                    {
                        columnsCSV[(int)l].append(";" + m_tableau_valeurs[l][j]);
                    }
                    j = m_tableau_valeurs[0].size();
                }
            }
        }
    }

    return columnsCSV;
}

std::vector<QStringList> Table::CreateTableMCDwithLink(int indiceColonne, int indiceTableToLink)
{
    std::vector<QStringList> tableMCDWithFK;
    QStringList valeurs;

    valeurs = fillMainColumn(indiceColonne);
    QStringList colonneCSV = extractColumnCSVFromIdTable(indiceTableToLink);


    for (size_t i(0) ; i < valeurs.size() ; i++)
    {
        QString valColonneInCSV = colonneCSV[(int)i];



        for (size_t j(0) ; j < m_base[indiceTableToLink][1].size() ; j++)
        {
            QString valColonneToLinkInTable = m_base[indiceTableToLink][1][(int)j];

            if ( valColonneInCSV == valColonneToLinkInTable )
            {
                valeurs[(int)i].append(";"+valColonneToLinkInTable);
            }
        }
    }

    tableMCDWithFK = joinColumnsIntoTable(valeurs);

    return tableMCDWithFK;
}


/* ******* méthodes publiques ************* */

void Table::CreateTableUnitaire(int indice)
{
    std::vector<QStringList> tableUnitaire;
    QStringList valeurs;

    valeurs = fillMainColumn(indice);

    tableUnitaire = joinColumnsIntoTable(valeurs);

    m_base.push_back(tableUnitaire);
    m_baseMCD.push_back(tableUnitaire);
}

void Table::CreateTableRelation(QString tables, QString columsToAdd)
{
    std::vector<QStringList> tableRelation, temp;
    QStringList columnsCSVToCompare;
    QStringList valeursTableRelation, valeurs;

    QStringList indices;
    indices << tables.split(";");


    for (size_t i(0) ; i < indices.size() ; i++)
    {
        columnsCSVToCompare.clear();
        valeursTableRelation.clear();

        int id = indices[(int)i].toInt();
        columnsCSVToCompare = extractColumnCSVFromIdTable(id);

        for ( size_t j(0) ; j < columnsCSVToCompare.size() ; j++)
        {
            QString valCSV = columnsCSVToCompare[(int)j];

            for ( size_t k(0) ; k < m_baseMCD[id][1].size() ; k++)
            {
                QString valMCD = m_baseMCD[id][1][(int)k];

                if (valCSV == valMCD)
                {
                    valeursTableRelation << m_baseMCD[id][0][(int)k];
                    k = m_baseMCD[id][1].size();
                }
            }
        }

        temp.push_back(valeursTableRelation);
    }

    if (columsToAdd != "")
    {
        QStringList indicesCSV;
        indicesCSV << columsToAdd.split(";");

        for (size_t i(0) ; i < indicesCSV.size() ; i++)
        {
            int idCSV = indicesCSV[(int)i].toInt();
            QStringList valeurs;

            for (size_t j(0) ; j < m_tableau_valeurs.size()-1 ; j++)
            {
                valeurs << m_tableau_valeurs[j][idCSV];
            }
            temp.push_back(valeurs);
        }
    }

    //mettre le contenu du tableau de valeurs dans une seule QStringList

    for (size_t i(0) ; i < temp[0].size() ; i++)
    {
        valeurs << temp[0][(int)i];
    }

    for (size_t i(0) ; i < valeurs.size() ; i++)
    {
        for (size_t j(1) ; j < temp.size(); j++)
        {
            valeurs[(int)i].append(";" + temp[(int)j][(int)i]);
        }
    }

    valeurs.removeDuplicates();
    tableRelation.push_back(valeurs);

    m_base.push_back(tableRelation);
    m_baseMCD.push_back(tableRelation);
}

void Table::CreateTableWithFK(int indiceColonne, int indiceTableToLink)
{
    std::vector<QStringList> tableWithFK, tableMCDwithFK;
    QStringList valeurs, valeursMCD;
    QStringList fk;

    valeurs = fillMainColumn(indiceColonne);
    valeursMCD = valeurs;

    QStringList colonneCSV = extractColumnCSVFromIdTable(indiceTableToLink);

    for (size_t i(0) ; i < colonneCSV.size() ; i++)
    {
        QString valColonnesInCSV = colonneCSV[(int)i];

        for (size_t j(0) ; j < m_baseMCD[indiceTableToLink][1].size() ; j++)
        {
            QString valColonnesInTableMCD = m_baseMCD[indiceTableToLink][1][(int)j];

            if ( valColonnesInCSV == valColonnesInTableMCD)
            {
                QString idColonneToLink = m_baseMCD[indiceTableToLink][0][(int)j];
                valeurs[(int)i].append(";"+idColonneToLink);
                j = m_baseMCD[indiceTableToLink][1].size();
            }
        }
    }

    //tableMCD
    for (size_t i(0) ; i < valeurs.size() ; i++)
    {
        valeursMCD[(int)i].append(";"+colonneCSV[(int)i]);
    }
    tableMCDwithFK = joinColumnsIntoTable(valeursMCD);
    m_baseMCD.push_back(tableMCDwithFK);


    tableWithFK = joinColumnsIntoTable(valeurs);
    m_base.push_back(tableWithFK);
}

void Table::saveNewCsvFiles(QString url, QStringList nameFiles)
{
    for (size_t i(0) ; i < m_base.size() ; i++)
    {
        QStringList valeurs;
        std::vector<QStringList> table = m_base[i];
        QString urlFile = url;

        QString nomTable = nameFiles[(int)i];

        if (table.size() > 1)
        {
            for (size_t j(0) ; j < table[0].size() ; j++)
            {
                valeurs << table[0][(int)j];
            }

            for (size_t k(0) ; k < valeurs.size() ; k++)
            {
                valeurs[(int)k].append(";" + table[1][(int)k]);
            }
        }

        else
        {
            for (size_t j(0) ; j < table.size() ; j++)
            {
                valeurs << table[(int)j];
            }
        }

        urlFile += "/";
        urlFile += nomTable;
        urlFile += ".csv";

        Utile::setLinesInFile(urlFile, valeurs);
    }
}

