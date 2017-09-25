#include "utile.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextStream>

using namespace std;

int Utile::test = 0;

Utile::Utile()
{}


void Utile::setLinesInFile(const QString &url, const QStringList &sl)
{
    QFile saveFile(url);

    if (!saveFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Ouverture Impossible" << url << "n'a pas pu être ouvert";
    }
    else
    {
        QTextStream fluxEcriture( &saveFile );
        fluxEcriture.setCodec("UTF-8");

        for ( QString ligne : sl )
        {
            fluxEcriture << ligne << endl;
        }

        qDebug() << "Save in :" << url;
    }
}

QString Utile::getLinesFromFile(const QString &url)
{
    QString sl;
    QFile loadFile (url);

    if (loadFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream fluxLecture(&loadFile);
        fluxLecture.setCodec("UTF-8");

        while ( !fluxLecture.atEnd() )
        {
            sl += fluxLecture.readAll();
        }
        loadFile.close();
    }
    else
    {
        qDebug() << "Erreur : ouverture du fichier impossible";
    }

    return sl;
}

std::vector<std::vector<int> > Utile::getTabtabFromList(const QStringList &sl)
{
    std::vector<std::vector<int>> grid;

    for (int i(0); i<sl.size(); i++)
    {
        grid.push_back( std::vector<int>() );
        QString ligne = sl[ i ];

        for (int j(0); j<ligne.size(); j++)
        {
            QString c = ligne.at( j );
            grid[i].push_back( c.toInt() );
        }
    }

    return grid;
}

QString Utile::getURLFromCpp(QString url)
{
    QString url_clear = url.remove(0,8);
    qDebug() << url_clear;

    return url_clear;
}

void Utile::afficheTabTab(std::vector <std::vector<QString> > tab)
{
    for (std::vector<QString> ligneVal : tab)
    {
        for (QString val : ligneVal)
        {
            qDebug() << val << " ";
        }
        qDebug() << endl;
    }
}

QStringList Utile::getLines2(const QString &url)
{
    QStringList sl;

    QFile loadFile (url);

    if (loadFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream fluxLecture(&loadFile);

        while ( !fluxLecture.atEnd() )
        {
            sl << fluxLecture.readLine();
        }
        loadFile.close();
    }
    else
    {
        qDebug() << "Erreur : ouverture du fichier impossible";
    }

    return sl;
}

std::vector<std::vector<QString> > Utile::pushListIntoTabtab(QStringList sl)
{
    QStringList sl2;
    QString ligne ="";
    vector <vector<QString>> tabTab;

    for (size_t j(0) ; j < sl.size() ; j++)
    {
        ligne = sl[(int)j];
        sl2 << ligne.split(";");

        tabTab.push_back( vector<QString>() );

        for (size_t k = 0; k < sl2.size() ; k++)
        {
            tabTab[j].push_back( sl2[(int)k] );
        }

        sl2.clear();
    }

    return tabTab;
}


