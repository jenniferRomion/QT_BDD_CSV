#ifndef SQLUSER_H
#define SQLUSER_H

#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQuery>

#include <iostream>
#include <QString>
#include <QDebug>

class SqlUser
{

public:

    SqlUser();

    //autres méthodes

    void connectToDatabase(QString nameDataBase = "");
    void newDatabase(QString nameDataBase);
    void deleteDatabase(QString nameDataBase);

    void executeScriptSQL(QString script);
    QStringList afficheRequeteSQL(QSqlQuery query);


    //set_get


private :

    //méthodes


    //attributs
    QSqlDatabase m_db;

};

#endif // SQLUSER_H
