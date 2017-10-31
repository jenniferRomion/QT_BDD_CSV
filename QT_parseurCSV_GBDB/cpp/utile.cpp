#include "utile.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextStream>

using namespace std;

int Utile::test = 0;

Utile::Utile()
{}

/* *** Lecture / ecriture  *** */

QString Utile::clearURL(QString &url)
{
#ifdef _WIN32
        QString url_clear = url.remove(0,8);
#else
        QString url_clear = url.remove(0,7);
#endif

        qDebug() << url_clear;

        return url_clear;
}

QStringList Utile::getStringListFromFile(const QString &url)
{
    QStringList sl;
    QFile loadFile (url);

    if (loadFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream fluxLecture(&loadFile);
        fluxLecture.setCodec("UTF-8");

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

vector<QStringList> Utile::splitColumns(QStringList &sl)
{
    vector< QStringList > tablist;

    for (size_t i(0) ; i < sl.size() ; i++)
    {

        if (sl[(int)i].contains("#")) //supprime le premier #
        {
            sl[(int)i].remove(0, 1);

            if (tablist.size() > 0)
            {
                for (size_t j(0) ; j < tablist.size() ; j++)
                {
                    tablist[j][i].remove(0, 1);
                }
            }


            if (sl[(int)i].contains("#")) // parse la ligne s'il reste des #
            {
                QStringList valTemp;
                valTemp << sl[(int)i].split("#");

                if (tablist.size() == 0)
                {
                    for (QString val : valTemp)
                    {
                        QStringList sl2(sl);
                        sl2[(int)i] = val;

                        tablist.push_back(sl2);
                    }
                }

                else
                {
                    vector< QStringList > tablistcopie (tablist);
                    tablist.clear();

                    for (QStringList liste : tablistcopie)
                    {
                        for (QString val : valTemp)
                        {
                            QStringList sl2(liste);
                            sl2[(int)i] = val;

                            tablist.push_back(sl2);
                        }
                    }
                }

            }

            else // envoie la-les lignes si plus de #
            {
                if (tablist.size() == 0)
                {
                    tablist.push_back(sl);
                }
            }
        }
    }

    return tablist;
}

/* *** Gestion des tableaux *** */

std::vector<std::vector<QString> > Utile::pushListIntoTabtab(const QStringList &sl)
{
    QStringList sl2;
        QString ligne ="";
        vector <vector<QString>> tabTab;
        vector<QStringList> tablist;

        for (size_t j(0) ; j < sl.size() ; j++)
        {
            tablist.clear();

            ligne = sl[(int)j];
            sl2 << ligne.split(";");

            for (auto val : sl2)
            {
                if (val.contains("#"))
                {
                    tablist = splitColumns(sl2);
                    break;
                }
            }

            if (tablist.size() == 0)
            {
                vector<QString> temp;

                for (auto val : sl2)
                {
                    temp.push_back( val );
                }
                tabTab.push_back( temp );
            }

            else
            {
                for (auto ligne : tablist)
                {
                    vector<QString> temp;
                    for (auto val : ligne)
                    {
                        temp.push_back( val );
                    }
                    tabTab.push_back( temp );
                }
            }

            sl2.clear();
        }

        return tabTab;
}


