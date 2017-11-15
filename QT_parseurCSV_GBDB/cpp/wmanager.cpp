#include "wmanager.h"
#include "table.h"
#include <QApplication>
#include <QTableView>

#include <QDir>
#include <QFileDialog>
#include <iostream>
#include <vector>

using namespace std;
WManager::WManager(QObject *parent) : QObject(parent)
{
    qDebug() << "WManager::instance construite ";

    setPropString("aucun fichier ouvert");
    setlargeurBouton(140);
    setMessageErreur("");
    setMessageSGBD("");
    setMessageBD("");
}

void WManager::load(QString modeleQML)
{
    QList<QString> fichiersQML;
    fichiersQML << modeleQML;

    for( int t=0 ; t<1 ; t++)
    {
        makeQMLtab(fichiersQML[t] );
        std::cout << "tab " << t << " ready." << std::endl;
    }
}

void WManager::makeQMLtab(QString nomFichierQMLsansExtension)
{
    QQuickView* view = new QQuickView();
    quickViews.push_back(view);

    view->setResizeMode( QQuickView::SizeViewToRootObject);

    m_QMLcontexts << view->engine()->rootContext();
    m_qmlContext = m_QMLcontexts.last();
    m_qmlContext->setContextProperty("Context", this->getInstance());


    QStringList listeVide;
    updateQML_model("ListeTables", listeVide);
    updateQML_model("UnModelARenseigner", listeVide);
    updateQML_model("sqlResult", listeVide);


#ifdef _WIN32
    QString repertoireProjet = getRepertoireProjet();
    QString fichierQML = repertoireProjet + QString("/qml/") + nomFichierQMLsansExtension + QString(".qml");
    std::cout  << "charge le fichier QML : " << fichierQML.toLatin1().constData() << std::endl;

    view->setSource( QUrl::fromLocalFile(fichierQML) ) ;

#else
    QString fichierQML = QString("qml/") + nomFichierQMLsansExtension + QString(".qml");
    QUrl urlQML = QUrl::fromLocalFile(fichierQML);

    std::cout  << "charge le fichier QML : " << fichierQML.toLatin1().constData() << std::endl;

    view->setSource( urlQML ) ;
    qDebug() << "test";

#endif

    view->show();
}

QString WManager::getRepertoireProjet(bool trace)//false

{
    QString repertoireDuFichierApplication( qApp->applicationFilePath() );
    if( trace)
        std::cout << "qApp->applicationFilePath() = "<< repertoireDuFichierApplication.toLatin1().constData() << std::endl;

    QDir fichier(repertoireDuFichierApplication);
    fichier.cdUp() ;
    fichier.cdUp() ;
    if( trace)
        std::cout << "qApp->applicationName() = "<< qApp->applicationName().toLatin1().constData() << std::endl;

    fichier.cd(qApp->applicationName());

    QString repertoireProjet  = fichier.absolutePath() ;

    if( trace)
        std::cout  << "repertoireProjet : " << repertoireProjet.toLatin1().constData() << std::endl;

    return repertoireProjet;
}

void WManager::displayInitialInformations()
{
    getRepertoireProjet(true);
}

//.............................................................
void WManager::updateQML_model(QString nomModele, QStringList sl)
{
    m_qmlContext = m_QMLcontexts.at(0);
    m_qmlContext->setContextProperty(nomModele, QVariant::fromValue( sl ) );
}

/* ***** lecture du fichier CVS ***** */
void WManager::openCSVfile(QString url)
{
    QString previsualisation = Utile::getLinesFromFile(Utile::clearURL(url));
    setPropString(previsualisation);

    qDebug() << "chargement ok";

    table.setFileCSV(previsualisation);
    previsualisation ="";
}

void WManager::splitCSVFile()
{
    vector<vector<QString>> tableau_valeurs = Utile::pushListIntoTabtab(table.fileCSV());
    table.setTableau_valeurs(tableau_valeurs);

    QStringList titreColonne;
    for (size_t j(0) ; j < tableau_valeurs[0].size() ; j++)
    {
        titreColonne << tableau_valeurs[0][(int)j];
    }

    updateQML_model("UnModelARenseigner", titreColonne);
}

/* ***** gestion des tables ; via interface QML *****/
void WManager::createTablesUnitaires(QString nomTable, int indice)
{
    setMessageErreur("");

    if ( !listeTables.contains(nomTable) )
    {
        table.CreateTableUnitaire(indice);
        listeTables << nomTable;
        updateQML_model("ListeTables", listeTables);
        setMessageErreur("table " + nomTable + " créée");
    }

    else
    {
        setMessageErreur("erreur : table existante");
    }
}

void WManager::createTablesWithFK(QString nomTable, int indiceColonne, int indiceTable)
{
    setMessageErreur("");

    if ( !listeTables.contains(nomTable) )
    {
        table.CreateTableWithFK(indiceColonne, indiceTable);
        listeTables << nomTable;
        updateQML_model("ListeTables", listeTables);
        setMessageErreur("table " + nomTable + " créée");
    }

    else
    {
        setMessageErreur("erreur : table existante");
    }
}

void WManager::createTablesRelation(QString nomTable, QString indicesTables, QString indicesColonnes)
{
    setMessageErreur("");

    if ( !listeTables.contains(nomTable) )
    {
        indicesTables = indicesTables.mid(0, indicesTables.size() -1);
        indicesColonnes = indicesColonnes.mid(0, indicesColonnes.size() -1);

        table.CreateTableRelation(indicesTables, indicesColonnes);
        listeTables << nomTable;
        updateQML_model("ListeTables", listeTables);
        setMessageErreur("table " + nomTable + " créée");
    }

    else
    {
        setMessageErreur("erreur : table existante");
    }
}

/* **** sauvegarde **** */
void WManager::save(QString url)
{
    if (listeTables.size() != 0)
    {
        table.saveNewCsvFiles(Utile::clearURL(url), listeTables);
        qDebug() << "fichiers CSV créés";
    }
}

/* **** Gestion BDD **** */
void WManager::usingDatabase(QString action, QString nameDataBase)
{
    if (action == "connexion")
    {
        setMessageBD(sqluser.connectToDatabase(nameDataBase));
    }
    else if (action == "create")
    {
        setMessageBD(sqluser.newDatabase(nameDataBase));
    }

    else if (action == "delete")
    {
        setMessageBD(sqluser.deleteDatabase(nameDataBase));
    }

    else
    {
        qDebug() << "rien";
    }
}

void WManager::executeScriptSQL(QString &script)
{
    QStringList sl;

    setMessageBD(sqluser.executeScriptSQL(script));
    sl = sqluser.afficheRequeteSQL(script);

    SetQueryResult(sl);
}

void WManager::insertDataFromCSVFile(QString url)
{
    QStringList datas;

    datas << Utile::getStringListFromFile(Utile::clearURL(url));
    datas.replaceInStrings("'", "-");
    datas.replaceInStrings("/", "-");
    datas.replaceInStrings(";", "', '");

    QString CSVdata("");

    for (size_t i(1) ; i < datas.size() ; i++)
    {
        CSVdata += "('" + datas[(int)i] + "'), \n";
    }

    CSVdata.remove(CSVdata.size() -1, CSVdata.size());

    setMessageSGBD(CSVdata);
}


/* ******** Rajout des propriétés du Context pour le QML **** */
void WManager::setPropString(const QString &a) {
    if (a != m_propString) {
        m_propString = a;
        emit propStringChanged();
    }
}

void WManager::setMessageErreur(const QString &message) {
    if (message != m_messageErreur) {
        m_messageErreur = message;
        emit messageErreurChanged();
    }
}

void WManager::setlargeurBouton(const int &i) {
    if (i != m_largeurBouton) {
        m_largeurBouton = i;
        emit largeurBoutonChanged();
    }
}

void WManager::setMessageSGBD(const QString &message) {
    if (message != m_messageSGBD) {
        m_messageSGBD = message;
        emit messageSGBDChanged();
    }
}

void WManager::setMessageBD(const QString &message) {
    if (message != m_messageBD) {
        m_messageBD = message;
        emit messageBDChanged();
    }
}

void WManager::SetQueryResult(const QStringList &sl)
{
    if (sl != m_queryResult) {
        m_queryResult = sl;
        emit queryResultChanged();
    }
}

void WManager::setResultQuery(const std::vector<std::vector<QString> > &vec)
{
    if (vec != m_resultQuery) {
        m_resultQuery = vec;
        emit resultQueryChanged();
    }
}


/* ********** */

QString WManager::propString_r() const {
    return m_propString;
}

int WManager::largeurBouton_r() const {
    return m_largeurBouton;
}

QString WManager::messageErreur() const {
    return m_messageErreur;
}

QString WManager::messageSGBD() const {
    return m_messageSGBD;
}

QString WManager::messageBD() const {
    return m_messageBD;
}

QStringList WManager::queryResult() const
{
    return m_queryResult;
}

std::vector<std::vector<QString> > WManager::resultQuery() const
{
    return m_resultQuery;
}
