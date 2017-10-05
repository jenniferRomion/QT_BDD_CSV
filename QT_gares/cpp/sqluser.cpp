#include "sqluser.h"

using namespace std;



SqlUser::SqlUser()
{

}

void SqlUser::newDatabase(QString nameDataBase)
{
    QSqlQuery query("CREATE DATABASE IF NOT EXISTS " + nameDataBase);

    if (query.exec())
    {
        qDebug() << "la BDD " + nameDataBase + " a ete cree" << endl;
    }

    else
    {
        qDebug() << "erreur : " << endl;
    }
}

void SqlUser::deleteDatabase(QString nameDataBase)
{
    QSqlQuery query("DROP DATABASE " + nameDataBase);

    if (query.exec())
    {
        qDebug() << "la BDD " + nameDataBase + " a ete supprimee" << endl;
    }

    else
    {
        qDebug() << "erreur : " << (query.lastError().text())<< endl;
    }
}

void SqlUser::executeScriptSQL(QString script)
{
    script.remove('\n');
    script.remove("`");

    QSqlQuery query;
    if (query.exec(script))
    {
        qDebug() << "requete executée";
    }

    else
    {
        qDebug() << "erreur : " << (query.lastError().text())<< endl;
    }
}

void SqlUser::connectToDatabase(QString nameDataBase)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setDatabaseName(nameDataBase);
    m_db.setHostName("localhost");
    m_db.setUserName("root");
    m_db.setPassword("afpa");

    if (m_db.open())
    {
        qDebug() << "connexion etablie à " << nameDataBase;
    }

    else
    {
        qDebug() << "echec de la connexion" << endl;
        qDebug() << "erreur : " << (m_db.lastError().text()) << endl;
    }
}

