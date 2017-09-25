#include "sqluser.h"

SqlUser::SqlUser()
{

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
        qDebug() << "connexion etablie";
    }

    else
    {
        qDebug() << "echec de la connexion" << endl;
        qDebug() << "erreur : " << (m_db.lastError().text()) << endl;
    }
}
