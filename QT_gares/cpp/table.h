#ifndef TABLE_H
#define TABLE_H

#include<vector>
#include<QStringList>
#include<QString>
#include<QDebug>

class Table
{

public:
    Table();
//autres methodes
    void CreateTableUnitaire (int indice);
    void CreateTableRelation (QString tables, QString columsToAdd ="");
    void CreateTableWithFK (int indiceColonne, int indiceTableToLink);

    void saveNewCsvFiles(QString url, QStringList nameFiles);


//set_get

    QStringList fileCSV() const;
    void setFileCSV(const QString &fileCSV);

    std::vector<std::vector<QString> > tableau_valeurs() const;
    void setTableau_valeurs(const std::vector<std::vector<QString> > &tableau_valeurs);

private :
    //methodes
    QStringList addIdToTable(QStringList valTab);
    QStringList fillMainColumn (int indice);
    std::vector<QStringList> joinColumnsIntoTable (QStringList valeurs);
    QStringList extractColumnCSVFromIdTable (int idTable);
    std::vector<QStringList> CreateTableMCDwithLink (int indiceColonne, int indiceTableToLink);


    //attributs
    std::vector<QStringList> m_tableMPD;
    std::vector<QStringList> m_tableMCD;

    QStringList m_fileCSV;

    std::vector<std::vector<QString>> m_tableau_valeurs;

    std::vector< std::vector<QStringList> > m_base;
    std::vector< std::vector<QStringList> > m_baseMCD;







};

#endif // TABLE_H
