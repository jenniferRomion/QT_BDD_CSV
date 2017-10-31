#ifndef UTILE_H
#define UTILE_H

#include <QStringList>
#include <iostream>
#include <vector>
#include <QString>


class Utile
{
public:
    Utile();

    /* *** Lecture / ecriture  *** */
    static QString clearURL(QString &url);
    static QStringList getStringListFromFile(const QString &url);
    static QString getLinesFromFile(const QString &url);
    static void setLinesInFile(const QString &url, const QStringList &sl);
    static std::vector<QStringList>splitColumns(QStringList &sl);

    /* *** Gestion des tableaux *** */
    static std::vector<std::vector<QString>> pushListIntoTabtab (const QStringList &sl);



private:
    static int test ;
};



#endif // UTILE_H
