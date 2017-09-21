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

    // 1/2 Initialisation des valeurs pour le QML avant chargement du fichier
    // propriétés simples
    setPropString("aucun fichier ouvert");//.... in .cpp 1/3  : Rajout propriété du Context QML
    setlargeurBouton(140);
}

void WManager::load()
{
    QList<QString> fichiersQML;
    // Chargement d'une ou plusieurs fenêtres avec pour fichiers sources :
    fichiersQML << QString("main"); // pour une source "main.qml"

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
    updateQML_model("listeEntierPourEvaluation", listeVide);
    updateQML_model("UnModelARenseigner", listeVide);
    //

    QString repertoireProjet = getRepertoireProjet();

    QString fichierQML = repertoireProjet + QString("/qml/") + nomFichierQMLsansExtension + QString(".qml");
    std::cout  << "charge le fichier QML : " << fichierQML.toLatin1().constData() << std::endl;

    // Chargement du fichier QML
    view->setSource( QUrl::fromLocalFile(fichierQML) ) ;
    view->show();
}

// Permet d'afficher des informations sur les répertoires du projet en cours
// Dans le paramétrage du projet "Project", necessite que "shadow build" soit décoché
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

void WManager::testActionQML(int i)
{
    qDebug() << "WManager::testActionQML : " << i;
}

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

void WManager::createTablesUnitaires()
{
   // actuellement, créé les tables unitaire sans demande QML

   table.CreateTableUnitaire(0);
   listeTables << "Ligne";

   table.CreateTableUnitaire(2);
   listeTables << "Desserte";

   table.CreateTableUnitaire(6);
   listeTables << "Departement";

   table.CreateTableUnitaire(7);
   listeTables << "CodePostal";


   updateQML_model("listeEntierPourEvaluation", listeTables);

}

void WManager::createTablesWithFK()
{

    table.CreateTableWithFK(8, 2);
    listeTables << "Ville" ;

    table.CreateTableWithFK(1, 4);
    listeTables << "Gare" ;

    updateQML_model("listeEntierPourEvaluation", listeTables);
}

void WManager::createTablesRelation()
{
    table.CreateTableRelation("3;4");
    listeTables << "Ville_CodePostal" ;

    table.CreateTableRelation("3;5");
    listeTables << "CP_Gare";

    table.CreateTableRelation("0;1;5", "3;4");
    listeTables << "Ligne_Desserte_Gare" ;

    updateQML_model("listeEntierPourEvaluation", listeTables);
}

void WManager::save(QString url)
{
    QString url_clear = url.remove(0,8);
    QFile loadFile (url_clear);

    table.saveNewCsvFiles(url_clear, listeTables);
    qDebug() << "fichiers CSV créés";
}




// Fonction appelée à partir du QML pour exécuter une action C++
void WManager::sendActionToCpp(QString nomAction, QString parametre/*=""*/)
{
    qDebug() << "WManager::sendActionfromQML : nomAction = " << nomAction;
    qDebug() << "WManager::sendActionfromQML : parametre = " << parametre;

    if ( nomAction == "monAction" )
    {
        // Détail d'une action appelée à partir du C++
    }
    else if ( nomAction == "autreAction" )
    {
        // Détail d'une autre action appelée à partir du C++
    }
}

//................ Rajout d'une propriété du Context pour le QML .............
//.... in .cpp 2/3  : Rajout propriété du Context QML
void WManager::setPropString(const QString &a) {
    if (a != m_propString) {
        m_propString = a;
        emit propStringChanged();
    }
}
//.... in .cpp 3/3  : Rajout propriété du Context QML
QString WManager::propString_r() const {
    return m_propString;
}

void WManager::setlargeurBouton(const int &i) {
    if (i != m_largeurBouton) {
        m_largeurBouton = i;
        emit largeurBoutonChanged();
    }
}

int WManager::largeurBouton_r() const {
    return m_largeurBouton;
}
