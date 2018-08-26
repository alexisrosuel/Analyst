/*

Copyright © 2009-2010 Alexis Rosuel

Analyst is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Analyst is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Analyst.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "../headers/Tuto.h"

Tuto::Tuto(QWidget *parent = 0) : QDialog (parent)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();

    numero = 0;
}

void Tuto::fct_suivant()
{
    numero++;

    if(numero == 1)
    {
        tuto_accueil();
    }

    if(numero == 2)
    {
        tuto_recherche_bdd();
    }

    if(numero == 3)
    {
        tuto_resultat();
    }

    if(numero == 4)
    {
        tuto_texte();
    }

    if(numero == 5)
    {
        tuto_edition();
    }

    if(numero == 6)
    {
        tuto_video();
    }

    if(numero == 7)
    {
        tuto_internet();
    }

    if(numero == 8)
    {
        tuto_database();
    }

    if(numero == 9)
    {
        tuto_console();
    }

    if(numero == 10)
    {
        tuto_console_recherche();
    }

    if(numero == 11)
    {
        tuto_console_internet();
    }

    if(numero == 12)
    {
        tuto_console_ouverture();
    }

    if(numero == 13)
    {
        tuto_console_autres();
    }

    if(numero == 14)
    {
        tuto_fin();
    }
}

void Tuto::fct_precedent()
{
    numero--;

    if(numero == 0)
    {
        tuto_debut();
    }

    if(numero == 1)
    {
        tuto_accueil();
    }

    if(numero == 2)
    {
        tuto_recherche_bdd();
    }

    if(numero == 3)
    {
        tuto_resultat();
    }

    if(numero == 4)
    {
        tuto_texte();
    }

    if(numero == 5)
    {
        tuto_edition();
    }

    if(numero == 6)
    {
        tuto_video();
    }

    if(numero == 7)
    {
        tuto_internet();
    }

    if(numero == 8)
    {
        tuto_database();
    }

    if(numero == 9)
    {
        tuto_console();
    }

    if(numero == 10)
    {
        tuto_console_recherche();
    }

    if(numero == 11)
    {
        tuto_console_internet();
    }

    if(numero == 12)
    {
        tuto_console_ouverture();
    }

    if(numero == 13)
    {
        tuto_console_autres();
    }

    if(numero == 14)
    {
        tuto_fin();
    }
}

void Tuto::tuto_fin()
{
    item->changeSize(46,46);
    QString sdz = "http://www.siteduzero.com/forum-83-569890-p1-programme-analyst.html";
    QString addresse = "http://www.analyst-free.110mb.com/";
    presentation->setOpenExternalLinks(true);
    titre->setText(tr("<h3>Analyst"));
    presentation->setText(tr("Ce tutoriel est terminé. Vous savez maintenant utiliser la plupart des fonctionnalités de Analyst. <br /><br />N'oubliez pas que vous avez un updater qui vous permet de mettre a jour Analyst <br />automatiquement. Si vous avez des questions ou des remarques, postez les ici : <br />") + "<a href='" + sdz + "'>" + sdz + "</a>" + tr(" et visitez le site <br />web : ") + "<a href='" + addresse + "'>" + addresse + "</a>");
    QPixmap pixmap(":/icones/Tuto/Analyst-100.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    suivant->setEnabled(false);
}

void Tuto::tuto_console_autres()
{
    item->changeSize(135,135);
    titre->setText(tr("<h3>Console - Dernieres Commandes"));
    presentation->setText(tr("Il existe trois dernieres commandes : <br /><br />-\"general\" permet d'afficher les informations globales de la base de données.<br />-\"about\" affiche la fenetre \"A Propos...\".<br />-\"quit\" permet de quitter l'application."));
    QPixmap pixmap(":/icones/Tuto/Console-Autres.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    suivant->setEnabled(true);
}

void Tuto::tuto_console_ouverture()
{
    item->changeSize(135,135);
    titre->setText(tr("<h3>Console - Autres Commandes a Parametres"));
    presentation->setText(tr("Il existe trois autres commandes qui prennent en compte des paramatres.<br />-L'ouverture de fichier : \"open\", puis le type de fichier (\"-pictures\" par exemple), et le nom du <br />fichier. L'asterix (\"*\") signifie qu'il faut ouvrir tout les fichier qui commence par ce qui precede <br />l'asterix.<br />-Les informations des fichier : \"info\". Cette commande prend les mêmes parametres que la <br />précendente.<br />-Le lancement du gestionnaire de la base de données : \"database\". Cette commande prend les <br />mêmes parametres que les précedentes a l'exception de l'asterix."));
    QPixmap pixmap(":/icones/Tuto/Console-Parametres.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_console_internet()
{
    item->changeSize(135,135);
    titre->setText(tr("<h3>Console - Internet"));
    presentation->setText(tr("La recherche internet depuis la console s'effectue aussi par ligne de commande. Elle s'effectue <br />en 4 étapes : <br /><br />-Tapez \"internet\" pour spécifier que l'on lance une recherche.<br />-On donne les options : \"-texts\" (on veut le texte), \"-alltexts\" (on veut tout les textes),<br />\"-pictures\" (on veut les images), ou \"-allpictures\" (on veut toutes les images).<br />-On met \"-nodisplay\" si on veut que les resultats ne s'affichent pas.<br />-On ecrit ce que l'on veut rechercher."));
    QPixmap pixmap(":/icones/Tuto/Console-Internet.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_console_recherche()
{
    item->changeSize(160,160);
    titre->setText(tr("<h3>Console - Recherche"));
    presentation->setText(tr("La recherche depuis la console s'effectue par ligne de commande. Elle s'effectue en 4 étapes : <br /><br />-Tapez \"search\" pour spécifier que l'on lance une recherche.<br />-On donne les options : \"-sensitive\" (on respecte la casse) ou \"-entire\" (on veut le mot en entier).<br />-On decide de la sortie du type de fichier que l'on veut chercher : \"-texts\" pour les textes, <br />\"-movies\" pour les films par exemple (on ne met rien si on veut chercher dans toute la base<br />de données).<br />-On decide soit d'afficher la fenetre de résultats en tapant \"-results\" ou d'ouvrir directement <br />les resultats avec \"-open\"."));
    QPixmap pixmap(":/icones/Tuto/Console-Recherche.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_console()
{
    item->changeSize(135,135);
    titre->setText(tr("<h3>La Console"));
    presentation->setText(tr("La console vous permet d'aller plus vite dans vos recherche. <br /><br />Plusieurs commande disponibles vous seront présentées."));
    QPixmap pixmap(":/icones/Tuto/Console.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_database()
{
    item->changeSize(40,40);
    titre->setText(tr("<h3>Gestionnaire de la Base de Données"));
    presentation->setText(tr("Cette fenetre vous permet de gérer votre base de données. Vous pouvez ajouter, renomer, <br />supprimer des fichiers. Vous pouvez aussi afficher les informations de la base de donnnées <br />ou de certains fichiers, et enfin choisir de n'afficher qu'un type de fichier, via la barre d'outils."));
    QPixmap pixmap(":/icones/Tuto/Database.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_internet()
{
    item->changeSize(60,60);
    titre->setText(tr("<h3>Internet"));
    presentation->setText(tr("Cette fenetre vous permet de lancer des recherches internet. Vous pouvez rechercher le <br />texte et les images de bases, puis rechercher en plus tous les documents qui sont ratachés a <br />votre recherche.<br /><br /> Les resultats sont enregistrés dans votre base de données."));
    QPixmap pixmap(":/icones/Tuto/Internet.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_video()
{
    item->changeSize(35,35);
    titre->setText(tr("<h3>Videos"));
    presentation->setText(tr("Cette fenetre vous permet de lire des videos. Pour lancer la video, cliquez une fois sur le <br />centre de la fenetre, pour mettre en pause, recliquez, et pour relancer la video, doublecliquez. <br />Pour changer le volume ou le temps, passez la souris au dessus de la fenetre."));
    QPixmap pixmap(":/icones/Tuto/Video.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_edition()
{
    item->changeSize(38,38);
    titre->setText(tr("<h3>Edition"));
    presentation->setText(tr("Cette fenetre vous permet d'editer un fichier texte.  Vous pouvez suivant l'option que vous<br />avez choisi précédement editer l'integralité du texte ou seulement en partie."));
    QPixmap pixmap(":/icones/Tuto/Edition.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_texte()
{
    item->changeSize(100,100);
    titre->setText(tr("<h3>Fichier Texte"));
    presentation->setText(tr("Cette fenetre vous permet de visualiser le contenu d'un fichier texte. Vous pouvez rechercher<br />un mot dedans, ou lancer l'edition de ce fichier via la barre d'outils."));
    QPixmap pixmap(":/icones/Tuto/Texte.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_resultat()
{
    item->changeSize(90,90);
    titre->setText(tr("<h3>Résultat de la Recherche"));
    presentation->setText(tr("Une fois la recherche terminée, les résultats s'affichent classés par textes, images, musiques,<br />videos, puis les autres types de fichiers.<br />Vous pouvez affiner votre recherche, ouvrir ou afficher les fichiers que vous souhaitez via la <br />barre d'outils située en haut de la fenetre."));
    QPixmap pixmap(":/icones/Tuto/Results.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_recherche_bdd()
{
    item->changeSize(150,150);
    titre->setText(tr("<h3>Recherche dans la Base de Données"));
    presentation->setText(tr("La recherche dans la base de données est la principale fonctionalitée du logiciel. <br /><br />Elle vous permet de rechercher un mot en respectant la casse ou l'integralité du mot dans votre propre<br />base de donnée."));
    QPixmap pixmap(":/icones/Tuto/Recherche.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Tuto::tuto_accueil()
{
    item->changeSize(0,0);
    titre->setText(tr("<h3>Accueil"));
    presentation->setText(tr("L'accueil de Analyst est la premiere fenetre qui apparait. Vous pouvez lancer une recherche<br />sur votre base de donnée, sur internet, et gerer votre base de donnée."));
    QPixmap pixmap(":/icones/Tuto/Accueil.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    precedent->setEnabled(true);
}

void Tuto::tuto_debut()
{
    item->changeSize(100,100);
    titre->setText(tr("<h3>Tutoriel"));
    presentation->setText(tr("Bienvenue dans le tutoriel de Analyst.<br /><br />Vous allez apprendre a utiliser principalement la console, et plus generalement l'ensemble<br />du logiciel."));
    QPixmap pixmap(":/icones/Tuto/Analyst.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    precedent->setEnabled(false);
}

void Tuto::creerFenetre()
{
    suivant = new QPushButton(tr("Suivant"));
    precedent = new QPushButton(tr("Precedent"));
    precedent->setEnabled(false);

    presentation = new QLabel;
    presentation->setText(tr("Bienvenue dans le tutoriel de Analyst.<br /><br />Vous allez apprendre a utiliser principalement la console, et plus generalement l'ensemble<br />du logiciel."));

    titre = new QLabel(tr("<h3>Tutoriel"));
    trait = new QLabel("<hr />");

    image = new QLabel(this);
    QPixmap pixmap(":/icones/Tuto/Analyst.png");
    image->setPixmap(pixmap);
    image->resize(pixmap.size());
    image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *layoutBouton = new QHBoxLayout;
    layoutBouton->addWidget(precedent);
    layoutBouton->addWidget(suivant);

    item = new QSpacerItem(100,100);

    QHBoxLayout *layoutImage = new QHBoxLayout;
    layoutImage->addSpacerItem(item);
    layoutImage->addWidget(image);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(titre);
    layout->addWidget(trait);
    layout->addWidget(presentation);
    layout->addLayout(layoutImage);
    layout->addLayout(layoutBouton);

    setLayout(layout);

    setWindowTitle(tr("Analyst - Tutoriel"));
    setFixedSize(650,600);
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    connect(suivant, SIGNAL(clicked()), this, SLOT(fct_suivant()));
    connect(precedent, SIGNAL(clicked()), this, SLOT(fct_precedent()));

}
