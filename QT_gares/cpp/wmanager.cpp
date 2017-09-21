#include "wmanager.h"
#include "table.h"
#include <QApplication>

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
}

void WManager::load(QString modeleQML)
{
    QList<QString> fichiersQML;
    // Chargement d'une ou plusieurs fenêtres avec pour fichiers sources :
    fichiersQML << modeleQML; // pour une source "main.qml"

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

    view->setResizeMode( QQuickView::SizeRootObjectToView);
    view->setGeometry(QRect(120, 120, 900, 600));

    // Mise en mémoire des objets pour communiquer avec le QML (avant le chargement de la page)
    m_QMLcontexts << view->engine()->rootContext();

    m_qmlContext = m_QMLcontexts.at(0);
    m_qmlContext->setContextProperty("Context", this->getInstance());
    //

    // 2/2 Initialisation des valeurs pour le QML avant chargement du fichier
    // Initialisation des modèles (même vides)
    QStringList listeVide;
    updateQML_model("ListeTables", listeVide);
    updateQML_model("UnModelARenseigner", listeVide);
    //

    QString repertoireProjet = getRepertoireProjet();

    QString fichierQML = repertoireProjet + QString("/qml/") + nomFichierQMLsansExtension + QString(".qml");
    std::cout  << "charge le fichier QML : " << fichierQML.toLatin1().constData() << std::endl;

    // Chargement du fichier QML
    view->setSource( QUrl::fromLocalFile(fichierQML) ) ;
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
// Mise à jour du modele de xxxxView du QML (du type Context.nomModele)
void WManager::updateQML_model(QString nomModele, QStringList sl)
{
    m_qmlContext = m_QMLcontexts.at(0);
    m_qmlContext->setContextProperty(nomModele, QVariant::fromValue( sl ) );
}

/* ***** lecture du fichier CVS ***** */
void WManager::openCSVfile(QString url)
{

    QString url_clear = url.remove(0,8);
    QFile loadFile (url_clear);

    QString previsualisation = Utile::getLinesFromFile(url_clear);
    setPropString(previsualisation);

    qDebug() << "chargement ok";

    table.setFileCSV(previsualisation);

    previsualisation ="";
}

void WManager::splitCSVFile()
{

    vector<vector<QString>> tableau_valeurs = Utile::pushListIntoTabtab(table.fileCSV());
    table.setTableau_valeurs(tableau_valeurs);


    QStringList titreColonne; //a sortir
    for (int j(0) ; j < tableau_valeurs[0].size() ; j++)
    {
        titreColonne << tableau_valeurs[0][j];
    }

    updateQML_model("UnModelARenseigner", titreColonne);
}

/* ***** gestion des tables ; sans demande QML *****/
void WManager::createTablesUnitaires()
{
    table.CreateTableUnitaire(0);
    listeTables << "Ligne";

    table.CreateTableUnitaire(2);
    listeTables << "Desserte";

    table.CreateTableUnitaire(6);
    listeTables << "Departement";

    table.CreateTableUnitaire(7);
    listeTables << "CodePostal";

    updateQML_model("ListeTables", listeTables);
}

void WManager::createTablesWithFK()
{
    table.CreateTableWithFK(8, 2);
    listeTables << "Ville" ;

    table.CreateTableWithFK(1, 4);
    listeTables << "Gare" ;

    updateQML_model("ListeTables", listeTables);
}

void WManager::createTablesRelation()
{
    table.CreateTableRelation("3;4");
    listeTables << "Ville_CodePostal" ;

    table.CreateTableRelation("3;5");
    listeTables << "CP_Gare";

    table.CreateTableRelation("0;1;5", "3;4");
    listeTables << "Ligne_Desserte_Gare" ;

    updateQML_model("ListeTables", listeTables);
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
        setMessageErreur("table " + nomTable + "créée");
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
        setMessageErreur("table " + nomTable + "créée");
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
        setMessageErreur("table " + nomTable + "créée");
    }

    else
    {
        setMessageErreur("erreur : table existante");
    }
}

/* **** sauvegarde **** */
void WManager::save(QString url)
{
    QString url_clear = url.remove(0,8);
    QFile loadFile (url_clear);

    table.saveNewCsvFiles(url_clear, listeTables);
    qDebug() << "fichiers CSV créés";
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
