#ifndef SQLUSER_H
#define SQLUSER_H

#include <QSqlDatabase>
#include <QtSql>
#include<QString>
#include<QDebug>

class SqlUser
{

public:

    SqlUser();

    //autres méthodes

    void connectToDatabase(QString nameDataBase);

    //set_get



private :

    //méthodes


    //attributs
    QSqlDatabase m_db;

};

#endif // SQLUSER_H
