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

    QString connectToDatabase(const QString &nameDataBase = "");
    QString newDatabase(const QString &nameDataBase);
    QString deleteDatabase(const QString &nameDataBase);

    QString executeScriptSQL(QString &script);
    QStringList afficheRequeteSQL(QString script);


    //set_get


private :

    //méthodes


    //attributs
    QSqlDatabase m_db;

};

#endif // SQLUSER_H
