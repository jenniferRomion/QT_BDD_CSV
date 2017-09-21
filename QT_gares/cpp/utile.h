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

    static QStringList getStringListFromFile(QString nomFichier);
    static void setLinesInFile(const QString &url, const QStringList &sl);
    static QString getLinesFromFile(const QString &url);
    static std::vector<std::vector<int>> getTabtabFromList (const QStringList &sl);
    static QString getURLFromCpp(QString url);
    static void afficheTabTab (std::vector <std::vector<QString>> tab);
    static QStringList getLines2(const QString &url);
    static std::vector<std::vector<QString>> pushListIntoTabtab (QStringList sl);



private:
    static int test ;
};



#endif // UTILE_H
