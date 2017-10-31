#ifndef TABLE_H
#define TABLE_H

#include<vector>
#include<QStringList>
#include<QString>
#include<QDebug>

typedef std::vector<QStringList> table;
typedef std::vector<std::vector<QString>> tableau;
typedef std::vector<QString> ligne;

class Table
{

public:
    Table();

//methodes
    void CreateTableUnitaire (const int &indice);
    void CreateTableRelation (QString &idTables, QString idColumsToAdd ="");
    void CreateTableWithFK (const int &indiceColonne, const int &indiceTableToLink);

    void saveNewCsvFiles(const QString &url, const QStringList &nameFiles);


//set_get
    QStringList fileCSV() const;
    void setFileCSV(const QString &fileCSV);

    std::vector< std::vector<QString> > tableau_valeurs() const;
    void setTableau_valeurs(const tableau &tableau_valeurs);


private :
    //methodes

    QStringList fillMainColumn (const int &indice);
    QStringList extractDatasFromCSV (const int &idTable);
    QStringList extractTitlesofTables(const int &idTable);
    QStringList extractDatasFromTablesInRelation(const int &id, const QStringList &columnsCSVToCompare);
    QStringList mergeDatas(const table &temp, QStringList &valeurs);

    std::vector< QStringList > CreateTableMCDwithLink (const int &indiceColonne, const int &indiceTableToLink);
    void addDatasToColumnsCSV(const QStringList &titrecolonne, QStringList &columnsCSV);


    std::vector< QStringList > joinColumnsIntoTable (QStringList &valeurs);
    QStringList addIdToTable(const QStringList &valTab);


    //attributs
    table m_tableMPD;
    table m_tableMCD;

    QStringList m_fileCSV;

    tableau m_tableau_valeurs;

    std::vector< table > m_base;
    std::vector< table > m_baseMCD;

};

#endif // TABLE_H
