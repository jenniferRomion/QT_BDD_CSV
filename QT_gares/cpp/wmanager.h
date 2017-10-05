#ifndef WMANAGER_H
#define WMANAGER_H

#include <QObject>
// #include <QQuickWidget>
#include <QQuickView>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QQmlEngine>
#include <QQmlContext>

#include <QDebug>
#include <QStringList>
#include <vector>
#include <QStringList>

#include "utile.h"
#include "table.h"
#include "sqluser.h"

using namespace std;

class WManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString propString READ propString_r WRITE setPropString NOTIFY propStringChanged)
    Q_PROPERTY(int largeurBouton READ largeurBouton_r WRITE setlargeurBouton NOTIFY largeurBoutonChanged)
    Q_PROPERTY(QString messageErreur READ messageErreur WRITE setMessageErreur NOTIFY messageErreurChanged)
    Q_PROPERTY(QString messageSGBD READ messageSGBD WRITE setMessageSGBD NOTIFY messageSGBDChanged)
    Q_PROPERTY(QStringList queryResult READ queryResult WRITE SetQueryResult NOTIFY queryResultChanged)
    Q_PROPERTY(std::vector<std::vector<QString>> resultQuery READ resultQuery WRITE setResultQuery NOTIFY resultQueryChanged)

public:
    explicit WManager(QObject *parent = 0);

    static WManager *getInstance() {
        if(nullptr == _singleton) {
            _singleton = new WManager ;
        }
        return _singleton ;
    }

    Q_INVOKABLE void load(QString modeleQML);

    void displayInitialInformations();

    /* ************** */
    void updateQML_model(QString nomModele, QStringList sl);

    /* ************** */

    Q_INVOKABLE void openCSVfile(QString url);
    Q_INVOKABLE void splitCSVFile();

    Q_INVOKABLE void createTablesUnitaires(QString nomTable, int indice);
    Q_INVOKABLE void createTablesWithFK(QString nomTable, int indiceColonne, int indiceTable);
    Q_INVOKABLE void createTablesRelation(QString nomTable, QString indicesTables, QString indicesColonnes);

    Q_INVOKABLE void save(QString url);

    Q_INVOKABLE void usingDatabase(QString action, QString nameDataBase);
    Q_INVOKABLE void executeScriptSQL(QString script);
    Q_INVOKABLE void insertDataFromCSVFile(QString url);



    QStringList listeTables;
    Table table;
    SqlUser sqluser;

/* ************** */

protected:
    std::vector<QQuickView*> quickViews;

    QString getRepertoireProjet(bool trace = false);

    QVector<QQmlContext *>          m_QMLcontexts;
    QQmlContext*                    m_qmlContext;

signals:
    void propStringChanged();
    void largeurBoutonChanged();
    void messageErreurChanged();
    void messageSGBDChanged();
    void queryResultChanged();
    void resultQueryChanged();

public slots:
    void setPropString(const QString &a);
    QString propString_r() const;

    void setlargeurBouton(const int &i);
    int largeurBouton_r() const;

    void setMessageErreur(const QString &message);
    QString messageErreur() const;

    void setMessageSGBD(const QString &message);
    QString messageSGBD() const;

    void SetQueryResult(const QStringList &sl);
    QStringList queryResult() const;

    void setResultQuery(const std::vector<std::vector<QString>> &vec);
    std::vector<std::vector<QString>> resultQuery() const;

private :
    static WManager *_singleton ;
    void makeQMLtab(QString nomFichierQMLsansExtension);

    QString m_propString;
    int m_largeurBouton;
    QString m_messageErreur;
    QString m_messageSGBD;
    QStringList m_queryResult;
    std::vector<std::vector<QString>> m_resultQuery;


};

#endif // WMANAGER_H


