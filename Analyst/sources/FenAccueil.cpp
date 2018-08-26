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

#include "../headers/FenAccueil.h"

FenAccueil::FenAccueil()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();
}

void Bouton::enterEvent(QEvent *)
{
    setIconSize(QSize(128, 128));

    emit(signalMessages());
}
void Bouton::leaveEvent(QEvent *)
{
    setIconSize(QSize(113, 113));

    emit(cleanMessage());
}

void FenAccueil::changerMessagesRecherche()
{
    phrase->setText("<h1><span style=\"color: white\"> Research </span></h1>");
}

void FenAccueil::changerMessagesInternet()
{
    phrase->setText("<h1><span style=\"color: white\"> Internet </span></h1>");
}

void FenAccueil::changerMessagesGestion()
{
    phrase->setText("<h1><span style=\"color: white\"> Database </span></h1>");
}

void FenAccueil::clean()
{
    phrase->setText("<h1><span style=\"color: white\"> Analyst </span></h1>");
}

void FenAccueil::lancerRecherche()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(!boutonPetitEcran->isEnabled())
    {
        FenRecherche *fenetreDebut = new FenRecherche(this);
        fenetreDebut->show();
    }

    else
    {
        QMessageBox::information(this, tr("Information"), tr("Cette fonction n'est pas encore disponible"));
        return;

        FenRechercheEntier *fenetreRechercheEntier = new FenRechercheEntier(this);
        fenetreRechercheEntier->show();
    }
}

void FenAccueil::lancerInternet()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(!boutonPetitEcran->isEnabled())
    {
        FenInternet *fenetreInternet = new FenInternet(false, false, false, false, false, true, NULL, this);
        fenetreInternet->show();
    }

    else
    {
        //FenInternetPleinEcran *fenetreInternetPleinEcran = new FenInternetPleinEcran(this);
        //fenetreInternetPleinEcran->show();
    }
}

void FenAccueil::lancerVisualisation()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenFichierVisualisation *fenetreVisualisation = new FenFichierVisualisation(5, this);
    fenetreVisualisation->show();
}

void FenAccueil::fonctionLicence()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenLicence *fenetreLicence = new FenLicence(this);
    fenetreLicence->show();
}

void FenAccueil::report_bug()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenBug *fenetre_bug = new FenBug(this);
    fenetre_bug->show();
}

void FenAccueil::lancer_tuto()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    Tuto *fenetre_tuto = new Tuto(this);
    fenetre_tuto->show();
}

void FenAccueil::fonctionPetitEcran()
{
    boutonPleinEcran->setEnabled(true);
    boutonPetitEcran->setEnabled(false);
}

void FenAccueil::fonctionPleinEcran()
{
    boutonPleinEcran->setEnabled(false);
    boutonPetitEcran->setEnabled(true);
}

void FenAccueil::creerFenetre()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    boutonRecherche = new Bouton;
    boutonRecherche->setObjectName("recherche");
    boutonRecherche->setIcon(QIcon(":/icones/Fenetre Accueil/find.png"));
    boutonRecherche->setFixedSize(135, 135);
    boutonRecherche->setIconSize(QSize(113, 113));
    boutonRecherche->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    connect(boutonRecherche, SIGNAL(clicked()), this, SLOT(lancerRecherche()));

    boutonInternet = new Bouton;
    boutonInternet->setIcon(QIcon(":/icones/Fenetre Accueil/agt_web.png"));
    boutonInternet->setFixedSize(135, 135);
    boutonInternet->setIconSize(QSize(113, 113));
    boutonInternet->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    connect(boutonInternet, SIGNAL(clicked()), this, SLOT(lancerInternet()));

    boutonGestion = new Bouton;
    boutonGestion->setIcon(QIcon(":/icones/Fenetre Accueil/kfm.png"));
    boutonGestion->setFixedSize(135, 135);
    boutonGestion->setIconSize(QSize(113, 113));
    boutonGestion->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    connect(boutonGestion, SIGNAL(clicked()), this, SLOT(lancerVisualisation()));

    phrase = new QLabel;
    phrase->setText("<h1><span style=\"color: white\"> Analyst </span></h1>");
    phrase->setAlignment(Qt::AlignCenter);

    connect(boutonRecherche, SIGNAL(signalMessages()), this, SLOT(changerMessagesRecherche()));
    connect(boutonInternet, SIGNAL(signalMessages()), this, SLOT(changerMessagesInternet()));
    connect(boutonGestion, SIGNAL(signalMessages()), this, SLOT(changerMessagesGestion()));

    connect(boutonRecherche, SIGNAL(cleanMessage()), this, SLOT(clean()));
    connect(boutonInternet, SIGNAL(cleanMessage()), this, SLOT(clean()));
    connect(boutonGestion, SIGNAL(cleanMessage()), this, SLOT(clean()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(boutonInternet, 0, 0);
    layout->addWidget(boutonGestion, 0, 2);
    layout->addWidget(phrase, 0,1);
    layout->addWidget(boutonRecherche, 1, 1);

    QMdiArea *aireCentrale = new QMdiArea;
    aireCentrale->setBackground(Qt::black);
    aireCentrale->setLayout(layout);

    boutonPleinEcran = new QPushButton(aireCentrale);
    boutonPleinEcran->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    boutonPleinEcran->move(10, 10);
    boutonPleinEcran->resize(50, 50);
    boutonPleinEcran->setIcon(QIcon(":/icones/Fenetre Accueil/kpersonalizer.png"));
    boutonPleinEcran->setIconSize(QSize(48, 48));
    connect(boutonPleinEcran, SIGNAL(clicked()), this, SLOT(fonctionPleinEcran()));

    boutonPetitEcran = new QPushButton(aireCentrale);
    boutonPetitEcran->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    boutonPetitEcran->setEnabled(false);
    boutonPetitEcran->move(10, 70);
    boutonPetitEcran->resize(50, 50);
    boutonPetitEcran->setIcon(QIcon(":/icones/Fenetre Accueil/kcmkwm.png"));
    boutonPetitEcran->setIconSize(QSize(48, 48));
    connect(boutonPetitEcran, SIGNAL(clicked()), this, SLOT(fonctionPetitEcran()));

    boutonLicence = new QPushButton(aireCentrale);
    boutonLicence->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    boutonLicence->move(760, 370);
    boutonLicence->resize(50, 50);
    boutonLicence->setIcon(QIcon(":/icones/Fenetre Accueil/readme.png"));
    boutonLicence->setIconSize(QSize(48, 48));
    connect(boutonLicence, SIGNAL(clicked()), this, SLOT(fonctionLicence()));

    boutonLicenceQt = new QPushButton(aireCentrale);
    boutonLicenceQt->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    boutonLicenceQt->move(760, 430);
    boutonLicenceQt->resize(50, 50);
    boutonLicenceQt->setIcon(QIcon(":/icones/Fenetre Accueil/linguist.png"));
    boutonLicenceQt->setIconSize(QSize(48, 48));
    connect(boutonLicenceQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));

    boutonBug = new QPushButton(aireCentrale);
    boutonBug->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    boutonBug->move(10, 430);
    boutonBug->resize(50, 50);
    boutonBug->setIcon(QIcon(":/icones/Fenetre Accueil/bug.png"));
    boutonBug->setIconSize(QSize(48, 48));
    connect(boutonBug, SIGNAL(clicked()), this, SLOT(report_bug()));

    boutonTuto = new QPushButton(aireCentrale);
    boutonTuto->setStyleSheet("background-color: transparent; border: 0; outline: 0;");
    boutonTuto->move(760, 10);
    boutonTuto->resize(50, 50);
    boutonTuto->setIcon(QIcon(":/icones/Fenetre Accueil/demo.png"));
    boutonTuto->setIconSize(QSize(48, 48));
    connect(boutonTuto, SIGNAL(clicked()), this, SLOT(lancer_tuto()));

    QHBoxLayout *layoutCentral = new QHBoxLayout;
    layoutCentral->addWidget(aireCentrale);

    setLayout(layoutCentral);

    setWindowTitle("Analyst");
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));


    #if defined(Q_WS_WIN)

    #endif

    #if defined(Q_WS_X11)
        setFixedSize(845,530);
    #endif
}

void FenAccueil::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        if(event->key() == Qt::Key_Control )
        {
            lancerInternet();
        }

        else if(event->key() == Qt::Key_Alt)
        {
            lancerVisualisation();
        }

        else
        {
            lancerRecherche();
        }
    }
}
