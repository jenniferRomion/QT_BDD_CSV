#include "sqluser.h"

using namespace std;



SqlUser::SqlUser()
{

}

QString SqlUser::newDatabase(const QString &nameDataBase)
{
    QString message("");

    QSqlQuery query("CREATE DATABASE IF NOT EXISTS " + nameDataBase);

    if (query.exec())
    {
        message = "la BDD " + nameDataBase + " a ete cree";
    }

    else
    {
        message = "Erreur : impossible de créer la base " + nameDataBase;
        qDebug() << query.lastError().text();
    }

    return message;
}

QString SqlUser::deleteDatabase(const QString &nameDataBase)
{
    QString message("");

    QSqlQuery query("DROP DATABASE " + nameDataBase);

    if (query.exec())
    {
        message = "la BDD " + nameDataBase + " a ete supprimee";
    }

    else
    {
        message = "Erreur : impossible de supprimer la base " + nameDataBase;
        qDebug() << query.lastError().text();
    }

    return message;
}

QString SqlUser::executeScriptSQL(QString &script)
{
    QString message("");

    script.remove('\n');
    script.remove("`");

    QSqlQuery query;
    if (query.exec(script))
    {
        message = "requete executée";
    }

    else
    {
        message = "script non execute _ verifier la syntaxe de la requète";
        qDebug() << query.lastError().text();
    }

    return message;
}

QStringList SqlUser::afficheRequeteSQL(QString script)
{
    QStringList sl;

    QSqlQueryModel model;
    model.setQuery(script);

    for (int i(0) ; i < model.rowCount(); i++)
    {
        QString ligne1 = model.record(i).value(0).toString();
        for (int j(1) ; j < model.columnCount() ; j++)
        {
            QString ligne2 = model.record(i).value(j).toString();
            ligne1.append("\t" + ligne2);
        }
        sl << ligne1;
    }

    return sl;
}

QString SqlUser::connectToDatabase(const QString &nameDataBase)
{
    QString message("");

    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_db.setDatabaseName(nameDataBase);
    m_db.setHostName("localhost");
    m_db.setUserName("root");
    m_db.setPassword("afpa");

    if (m_db.open())
    {
        message= "connexion etablie à " + nameDataBase;
    }

    else
    {
        message = "echec de la connexion";
        qDebug() << (m_db.lastError().text());
    }

    return message;
}

