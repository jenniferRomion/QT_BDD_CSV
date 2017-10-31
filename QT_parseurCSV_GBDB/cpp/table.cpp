#include "table.h"
#include "utile.h"

Table::Table()
{
}

/* ******* méthodes publiques ************* */

void Table::CreateTableUnitaire(const int &indice)
{
    table tableUnitaire;
    QStringList valeurs;

    valeurs = fillMainColumn(indice);

    tableUnitaire = joinColumnsIntoTable(valeurs);

    m_base.push_back(tableUnitaire);
    m_baseMCD.push_back(tableUnitaire);
}

void Table::CreateTableRelation(QString &idTables, QString idColumsToAdd)
{
    table tableRelation, temp;
    QStringList columnsCSVToCompare;
    QStringList valeursTableRelation, valeurs;

    QStringList indices;
    indices << idTables.split(";");

    for (size_t i(0) ; i < indices.size() ; i++)
    {
        columnsCSVToCompare.clear();
        valeursTableRelation.clear();

        int id = indices[(int)i].toInt();

        columnsCSVToCompare = extractDatasFromCSV(id);
        valeursTableRelation = extractDatasFromTablesInRelation(id, columnsCSVToCompare);
        temp.push_back(valeursTableRelation);
    }

    if (idColumsToAdd != "")
    {
        QStringList indicesCSV;
        indicesCSV << idColumsToAdd.split(";");

        for (size_t i(0) ; i < indicesCSV.size() ; i++)
        {
            int idCSV = indicesCSV[(int)i].toInt();
            QStringList valeurs;

            for (size_t j(0) ; j < m_tableau_valeurs.size()-1 ; j++)
            {
                valeurs << m_tableau_valeurs[(int)j][idCSV];
            }
            temp.push_back(valeurs);
        }
    }

    valeurs = mergeDatas(temp, valeurs);

    valeurs.removeDuplicates();
    tableRelation.push_back(valeurs);

    m_base.push_back(tableRelation);
    m_baseMCD.push_back(tableRelation);
}


void Table::CreateTableWithFK(const int &indiceColonne, const int &indiceTableToLink)
{
    table tableWithFK, tableMCDwithFK;
    QStringList valeurs, valeursMCD;

    valeurs = fillMainColumn(indiceColonne);
    valeursMCD = valeurs;

    QStringList colonneCSV = extractDatasFromCSV(indiceTableToLink);

    for (size_t i(0) ; i < colonneCSV.size() ; i++)
    {
        QString valColonnesInCSV = colonneCSV[(int)i];

        for (size_t j(0) ; j < m_baseMCD[indiceTableToLink][1].size() ; j++)
        {
            QString valColonnesInTableMCD = m_baseMCD[indiceTableToLink][1][(int)j];

            if ( valColonnesInCSV.contains(valColonnesInTableMCD) )
            {
                QString idColonneToLink = m_baseMCD[indiceTableToLink][0][(int)j];
                valeurs[(int)i].append(";" + idColonneToLink);
                break;
            }
        }
    }

    //tableMCD
    for (size_t i(0) ; i < valeurs.size() ; i++)
    {
        valeursMCD[(int)i].append(";" + colonneCSV[(int)i]);
    }
    tableMCDwithFK = joinColumnsIntoTable(valeursMCD);
    m_baseMCD.push_back(tableMCDwithFK);


    tableWithFK = joinColumnsIntoTable(valeurs);
    m_base.push_back(tableWithFK);
}

void Table::saveNewCsvFiles(const QString &url, const QStringList &nameFiles)
{
    for (size_t i(0) ; i < m_base.size() ; i++)
    {
        QStringList valeurs;
        table t = m_base[i];
        QString urlFile = url;

        QString nomTable = nameFiles[(int)i];

        if (t.size() > 1)
        {
            for (size_t j(0) ; j < t[0].size() ; j++)
            {
                valeurs << t[0][(int)j];
            }

            for (size_t k(0) ; k < valeurs.size() ; k++)
            {
                valeurs[(int)k].append(";" + t[1][(int)k]);
            }
        }

        else
        {
            for (size_t j(0) ; j < t.size() ; j++)
            {
                valeurs << t[(int)j];
            }
        }

        urlFile += "/";
        urlFile += nomTable;
        urlFile += ".csv";

        Utile::setLinesInFile(urlFile, valeurs);
    }
}

/* ********methodes privées*********** */

QStringList Table::addIdToTable(const QStringList &valTab)
{
    QStringList id;

    for (int j(0) ; j< valTab.size() ; j++)
    {
        id << QString::number((int)j);
    }

    return id;
}

QStringList Table::fillMainColumn(const int &indice)
{
    QStringList valeurs;

    for (size_t i(0) ; i < m_tableau_valeurs.size()-1 ; i++)
    {
        if ( m_tableau_valeurs[i][indice] != "" )
        {
            valeurs << m_tableau_valeurs[i][indice];
        }
    }

    return valeurs;
}

std::vector<QStringList> Table::joinColumnsIntoTable(QStringList &valeurs)
{
    table t;

    valeurs.removeDuplicates();
    t.push_back(addIdToTable(valeurs));
    t.push_back(valeurs);

    return t;
}

QStringList Table::extractTitlesofTables(const int &idTable)
{
    QString titreTable = m_baseMCD[idTable][1][0];
    QStringList titrecolonne;
    titrecolonne << titreTable.split(";");

    return titrecolonne;
}

QStringList Table::extractDatasFromCSV(const int &idTable)
{
    QStringList titrecolonne = extractTitlesofTables(idTable);

    QStringList columnsCSV;

    for (size_t j(0) ; j< m_tableau_valeurs[0].size() ; j++)
    {
        if (m_tableau_valeurs[0][j] == titrecolonne[0])
        {
            columnsCSV << fillMainColumn( (int)j ) ;
            break;
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
                        columnsCSV[(int)l].append(";" + m_tableau_valeurs[(int)l][(int)j]);
                    }
                    break;
                }
            }
        }
    }

    return columnsCSV;
}

std::vector<QStringList> Table::CreateTableMCDwithLink(const int &indiceColonne, const int &indiceTableToLink)
{
    table tableMCDWithFK;

    QStringList valeurs;
    valeurs = fillMainColumn(indiceColonne);

    QStringList colonneCSV = extractDatasFromCSV(indiceTableToLink);

    for (size_t i(0) ; i < valeurs.size() ; i++)
    {
        QString valColonneInCSV = colonneCSV[(int)i];

        for (size_t j(0) ; j < m_base[indiceTableToLink][1].size() ; j++)
        {
            QString valColonneToLinkInTable = m_base[indiceTableToLink][1][(int)j];

            if ( valColonneInCSV.contains(valColonneToLinkInTable) )
            {
                valeurs[(int)i].append(";" + valColonneToLinkInTable);
            }
        }
    }

    tableMCDWithFK = joinColumnsIntoTable(valeurs);

    return tableMCDWithFK;
}

QStringList Table::extractDatasFromTablesInRelation(const int &id, const QStringList &columnsCSVToCompare)
{
    QStringList valeursTableRelation;

    for ( size_t j(0) ; j < columnsCSVToCompare.size() ; j++)
    {
        QString valCSV = columnsCSVToCompare[(int)j];

        for ( size_t k(0) ; k < m_baseMCD[id][1].size() ; k++)
        {
            QString valMCD = m_baseMCD[id][1][(int)k];

            if ( valCSV.contains(valMCD) )
            {
                valeursTableRelation << m_baseMCD[id][0][(int)k];
                k = m_baseMCD[id][1].size();
            }
        }
    }

    return valeursTableRelation;
}

QStringList Table::mergeDatas(const table &temp, QStringList &valeurs)
{
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
    return valeurs;
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

void Table::setTableau_valeurs(const tableau &tableau_valeurs)
{
    m_tableau_valeurs = tableau_valeurs;
}
