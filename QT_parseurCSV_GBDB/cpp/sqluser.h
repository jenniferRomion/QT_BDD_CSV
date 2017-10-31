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

    void connectToDatabase(const QString &nameDataBase = "");
    void newDatabase(const QString &nameDataBase);
    void deleteDatabase(const QString &nameDataBase);

    void executeScriptSQL(QString &script);
    QStringList afficheRequeteSQL(QString script);


    //set_get


private :

    //méthodes


    //attributs
    QSqlDatabase m_db;

};

#endif // SQLUSER_H
