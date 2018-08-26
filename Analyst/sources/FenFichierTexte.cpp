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

#include "../headers/FenFichierTexte.h"

int nombreTextesOuverts = 0;
int decalageTexte = 0;
int second_decalage_texte = 0;

bool trouve = false;
bool ok = true;

ProxyOpacity FenFichierTexte::proxy_opacity;

FenFichierTexte::FenFichierTexte(QString &texte, QString &fichier, QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    texteVrai = texte;
    nomFichier = fichier;
    creerStatusBar();
    creerActions();
    creerFenetre(texte, fichier);

    nombreTextesOuverts++;

    int abscisse = 20*nombreTextesOuverts + 300*decalageTexte + 20*second_decalage_texte;
    int ordonnee = 20*nombreTextesOuverts + 20*second_decalage_texte;

    for(int i = 0; i < abscisse; i += 0)
    {
        move(i, ordonnee);
        show();
        QEventLoop loop;
        QTimer::singleShot(1, &loop, SLOT(quit()));
        loop.exec();
        i += 3;

    }

    if(nombreTextesOuverts == 0)
    {
         move(abscisse, ordonnee);
    }

    else
    {
         move(abscisse, ordonnee + 30);
    }

    if(nombreTextesOuverts == 5)
    {
        nombreTextesOuverts = 0;
        decalageTexte++;
    }

    if(decalageTexte == 4)
    {
        decalageTexte = 0;
        nombreTextesOuverts = 0;
        second_decalage_texte++;
    }

}

void FenFichierTexte::threadChercher(QString texte, QTextEdit *zoneTexte)
{
    nombreResultatAfficher = 0;
    trouve = false;
    ok = true;

    emit mettreRouge();

    emit updateAffichage(0);

    if(texte.contains("</"))
    {
        emit signalHtml();
    }

    else
    {
        emit signalPlain();
    }

    emit changerPolice();
}


void FenFichierTexte::chercher()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if (mot->text().isEmpty())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer au moins un mot à rechercher"));
        return;
    }

    dialog = new QProgressDialog(this);
    dialog->setLabelText(tr("Analyse du document..."));
    dialog->setModal(false);

    QFutureWatcher<void> watcher;
    watcher.setFuture(QtConcurrent::run(this, &FenFichierTexte::threadChercher, texteVrai, zoneTexte));

    connect(&watcher,SIGNAL(finished()),dialog ,SLOT(close()));
    connect(dialog,SIGNAL(canceled()),&watcher,SLOT(cancel()));
    connect(dialog,SIGNAL(canceled()),this,SLOT(arreter()));

    connect(this, SIGNAL(signalPlain()), this, SLOT(mettrePlain()));
    connect(this, SIGNAL(signalHtml()), this, SLOT(mettreHtml()));
    connect(this, SIGNAL(updateAffichage(int)), this, SLOT(mettreUpdateAffichage(int)));
    connect(this, SIGNAL(changerPolice()), this, SLOT(fonctionChangerPolice()));
    connect(this, SIGNAL(signalCurseur()), this, SLOT(fonctionCurseur()));
    connect(this, SIGNAL(mettreRouge()), this, SLOT(fonctionRouge()));
    connect(this, SIGNAL(mettreVert()), this, SLOT(fonctionVert()));

    dialog->show();
}

void FenFichierTexte::mettreHtml()
{
    zoneTexte->setHtml(texteVrai);
}

void FenFichierTexte::mettrePlain()
{
    zoneTexte->setPlainText(texteVrai);
}

void FenFichierTexte::mettreUpdateAffichage(int value)
{
    dialog->setValue(value);
}

void FenFichierTexte::fonctionChangerPolice()
{
    while((zoneTexte->find(mot->text())) && ok)
    {
        if(!trouve)
        {
            trouve = true;
            emit mettreVert();
        }

        nombreResultatAfficher++;

        zoneTexte->insertHtml("<span style=\"color: red\">" + mot->text().toUpper() + "</span>");
        qApp->processEvents();
        emit updateAffichage(100*(zoneTexte->textCursor().position())/(texteVrai.length()));
    }

    emit updateAffichage(100);
    emit signalCurseur();
    arreter();

    QString statutNombre;
    statutNombre.setNum(nombreResultatAfficher);
    statut->showMessage("Nombre total d'occurences : " + statutNombre, 2000);
}

void FenFichierTexte::fonctionCurseur()
{
    QTextCursor curseur;
    curseur.setPosition(0);

    zoneTexte->setTextCursor(curseur);

    qApp->processEvents();
}

void FenFichierTexte::arreter()
{
    ok = false;
}

void FenFichierTexte::fonctionVert()
{
    mot->setStyleSheet("background-color: #bbffbb;");
}

void FenFichierTexte::fonctionRouge()
{
    mot->setStyleSheet("background-color: #ffb3b3;");
}

void FenFichierTexte::fonctionToutEditer()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenFichierEditerTout *fenetreEditerTout = new FenFichierEditerTout(nomFichier, texteVrai, NULL, NULL, false, this);
    fenetreEditerTout->show();
}

void FenFichierTexte::fonctionEditerPartie()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(zoneTexte->textCursor().selectedText().isNull())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous devez séléctionner du texte pour pouvoir l'éditer"));
        return;
    }

    QMessageBox::warning(this, "Attention", "Si vous utilisez un document texte sous forme html, il est conseillé de ne pas l'utiliser car est encore en développement et peut provoquer l'écrasement de vos données.");

    FenFichierEditerTout *fenetreEditerTout = new FenFichierEditerTout(nomFichier, zoneTexte->textCursor().selectedText(), texteVrai, zoneTexte->textCursor().position() - zoneTexte->textCursor().selectedText().length(), true, this);
    fenetreEditerTout->show();
}

void FenFichierTexte::fonctionMotChercher()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(mot->text().isEmpty())
    {
        suivantMot->setEnabled(false);
        precedentMot->setEnabled(false);
    }

    else
    {
        suivantMot->setEnabled(true);
        precedentMot->setEnabled(true);
    }
}

void FenFichierTexte::fonctionSelection()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(zoneTexte->textCursor().selectedText().isNull())
    {
        editerPartie->setEnabled(false);
    }

    else
    {
        editerPartie->setEnabled(true);
    }
}

void FenFichierTexte::fonctionSuivantMot()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte->find(mot->text());
}

void FenFichierTexte::fonctionPrecedentMot()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte->find(mot->text(), QTextDocument::FindBackward);
}

void FenFichierTexte::fonctionZoomMoins()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte->zoomOut(1.2);
}

void FenFichierTexte::fonctionZoomPlus()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte->zoomIn(1.2);
}

void FenFichierTexte::creerStatusBar()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut = new QStatusBar();
    statut->showMessage(tr("Pret"));
}

void FenFichierTexte::afficherToutEditer()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Editer le document"), 2000);
}

void FenFichierTexte::afficherEditerPartie()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Editer le texte séléctionné"), 2000);
}

void FenFichierTexte::afficherPrecedentMot()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Aller au précédent"), 2000);
}

void FenFichierTexte::afficherSuivantMot()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Aller au suivant"), 2000);
}

void FenFichierTexte::afficherZoomMoins()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Dézoomer"), 2000);
}

void FenFichierTexte::afficherZoomPlus()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    statut->showMessage(tr("Zoomer"), 2000);
}

void FenFichierTexte::creerActions()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    editerTous = new QAction(this);
    editerTous->setIcon(QIcon(":/icones/Fenetre Texte/kedit.png"));
    editerTous->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
    editerTous->setToolTip(tr("Editer le document  Ctrl+E"));
    connect(editerTous, SIGNAL(hovered()), this, SLOT(afficherToutEditer()));
    connect(editerTous, SIGNAL(triggered()), this, SLOT(fonctionToutEditer()));
    toolBar->addAction(editerTous);

    editerPartie = new QAction(this);
    editerPartie->setIcon(QIcon(":/icones/Fenetre Texte/editpaste.png"));
    editerPartie->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    editerPartie->setToolTip(tr("Editer le texte séléctionné  Ctrl+S"));
    connect(editerPartie, SIGNAL(hovered()), this, SLOT(afficherEditerPartie()));
    connect(editerPartie, SIGNAL(triggered()), this, SLOT(fonctionEditerPartie()));
    editerPartie->setEnabled(false);
    toolBar->addAction(editerPartie);

    toolBar->addSeparator();

    precedentMot = new QAction(this);
    precedentMot->setIcon(QIcon(":/icones/Fenetre Texte/agt_back.png"));
    precedentMot->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    precedentMot->setToolTip(tr("Aller à la prochaine occurence  Ctrl+P"));
    connect(precedentMot, SIGNAL(hovered()), this, SLOT(afficherPrecedentMot()));
    connect(precedentMot, SIGNAL(triggered()), this, SLOT(fonctionPrecedentMot()));
    precedentMot->setEnabled(false);
    toolBar->addAction(precedentMot);

    suivantMot = new QAction(this);
    suivantMot->setIcon(QIcon(":/icones/Fenetre Texte/agt_forward.png"));
    suivantMot->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    suivantMot->setToolTip(tr("Aller à la précédente occurence  Ctrl+F"));
    connect(suivantMot, SIGNAL(hovered()), this, SLOT(afficherSuivantMot()));
    connect(suivantMot, SIGNAL(triggered()), this, SLOT(fonctionSuivantMot()));
    suivantMot->setEnabled(false);
    toolBar->addAction(suivantMot);

    toolBar->addSeparator();

    zoomPlus = new QAction(this);
    zoomPlus->setIcon(QIcon(":/icones/Fenetre Texte/Zoom-in.png"));
    zoomPlus->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    zoomPlus->setToolTip(tr("Zoomer  Ctrl+I"));
    connect(zoomPlus, SIGNAL(hovered()), this, SLOT(afficherZoomPlus()));
    connect(zoomPlus, SIGNAL(triggered()), this, SLOT(fonctionZoomPlus()));
    toolBar->addAction(zoomPlus);

    zoomMoins = new QAction(this);
    zoomMoins->setIcon(QIcon(":/icones/Fenetre Texte/Zoom-out.png"));
    zoomMoins->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    zoomMoins->setToolTip(tr("Dézoomer  Ctrl+O"));
    connect(zoomMoins, SIGNAL(hovered()), this, SLOT(afficherZoomMoins()));
    connect(zoomMoins, SIGNAL(triggered()), this, SLOT(fonctionZoomMoins()));
    toolBar->addAction(zoomMoins);

}

void FenFichierTexte::creerFenetre(QString texte, QString fichier)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    zoneTexte = new QTextEdit();

    if(texte.contains("</"))
    {
        zoneTexte->setHtml(texte);
    }

    else
    {
        zoneTexte->setPlainText(texte);
    }

    zoneTexte->setReadOnly(true);
    zoneTexte->setFont(QFont("Courier"));
    zoneTexte->setTextInteractionFlags(Qt::NoTextInteraction);
    connect(zoneTexte, SIGNAL(selectionChanged()), this, SLOT(fonctionSelection()));

    afficherRecherche = new QPushButton(tr("Rechercher le mot dans le fichier !"));

    mot = new QLineEdit;
    connect(mot, SIGNAL(textEdited(QString)), this, SLOT(fonctionMotChercher()));

    progression = new QProgressBar;


    /****

    QGraphicsScene *scene = new QGraphicsScene();

    proxy = new QGraphicsProxyWidget();
    proxy->setWidget(zoneTexte);

    scene->addItem(proxy);

    QGraphicsView *view = new QGraphicsView(scene, this);
    //view->show();


    *****/


    layout = new QVBoxLayout;
    layout->addWidget(toolBar);
    layout->addWidget(zoneTexte); // Mettre zoneTexte
    layout->addWidget(mot);
    layout->addWidget(afficherRecherche);
    layout->addWidget(statut);

    setLayout(layout);

    #if defined(Q_WS_WIN)
        resize(650,650);
    #endif

    #if defined(Q_WS_X11)
        resize(650,650);
    #endif

    fichier = fichier.section('/', -1);
    setWindowTitle("Analyst - \"" + fichier + "\"");

    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    connect(afficherRecherche, SIGNAL(clicked()), this, SLOT(chercher()));

    connect(this, SIGNAL(changerOpacite(FenFichierTexte*)), &proxy_opacity, SLOT(setOpacity(FenFichierTexte*)));
	connect(&proxy_opacity, SIGNAL(opacityChanged(FenFichierTexte*)), this, SLOT(setOpacity(FenFichierTexte*)));
}

/****

void FenFichierTexte::mouseDoubleClickEvent(QMouseEvent*)
{
    for(int i = 0; i <= 360; i++)
    {

    QTransform matrix;
    matrix.rotate(i, Qt::YAxis);
    proxy->setTransform(matrix);

    QEventLoop loop;
QTimer::singleShot(1, &loop, SLOT(quit()));
loop.exec();


    }
}

*****/

void FenFichierTexte::setOpacity(FenFichierTexte* w)
{
	if(w == this)
	{
		setWindowOpacity(1.0);
	}
	else
	{
		setWindowOpacity(0.8);
	}
}

void FenFichierTexte::enterEvent(QEvent *e)
{
	e->accept();
	emit changerOpacite(this);
}


void FenFichierTexte::mousePressEvent(QMouseEvent *e)
{
    //emit(clickOpacite());
    e->accept();

   /* QEventLoop loop;
QTimer::singleShot(100, &loop, SLOT(quit()));
loop.exec();
*/
    //emit(changerOpacite());

}

void FenFichierTexte::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        chercher();
    }
}

void FenFichierTexte::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}


