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

#include "../headers/FenFichierVisualisation.h"

FenFichierVisualisation::FenFichierVisualisation(int affichage, QWidget *parent) : QDialog(parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QString dir = QApplication::applicationDirPath();
    direction = new QDir();
    direction->setPath(dir);
    direction->cd(QString(QDir::homePath() + "/Analyst/" + "DataBase")); qDebug() << QDir::homePath() + "/Analyst/" + "DataBase";

    QStringList files = direction->entryList();
    files.removeOne(".");
    files.removeOne("..");

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {

        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {

            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue = new QListView;
    vue->setSelectionMode(QAbstractItemView::ExtendedSelection);
    vue->setModel(modele2);



    if(affichage == 5)
    {

    }

    else if(affichage == 1)
    {
        afficherTextes();
    }

    else if(affichage == 2)
    {
        afficherImages();
    }

    else if(affichage == 3)
    {
        afficherMusiques();
    }

    else if(affichage == 4)
    {
        afficherVideos();
    }

    creerStatusBar();
    creerActions();
    creerFenetre();
}

void FenFichierVisualisation::fonctionParent()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    direction->cdUp();
    QStringList files = direction->entryList();
    files.removeOne(".");
    files.removeOne("..");

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {

        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::threadAjouter(QStringList fichiers)
{
    int i = 0;

    foreach(QString nomFichier, fichiers)
    {
        if(!arreter_copie)
        {
            i++;
            emit chargement(i);
            //dialog->setValue(i);
            QString destination = QDir::homePath() + "/Analyst/" + "DataBase/" + nomFichier.section('/', -1);
            QFile::copy(nomFichier, destination);
        }

        else
        {
            return;
        }
    }

    fonctionActualiser();
}

void FenFichierVisualisation::arreter()
{
    arreter_copie = true;
}

void FenFichierVisualisation::actualiser_chargement(int i)
{
    dialog->setValue(i);
}

void FenFichierVisualisation::ajouterFichier()
{
    QStringList fichiers = QFileDialog::getOpenFileNames(this, tr("Ajouter des fichiers"), QApplication::applicationFilePath());

    if(fichiers.isEmpty())
    {
        return;
    }

    arreter_copie = false;

    dialog = new QProgressDialog(this);
    dialog->setLabelText(tr("Ajout des fichiers..."));
    dialog->setModal(false);
    dialog->setRange(0, fichiers.size());
    dialog->show();

    QFutureWatcher<void> watcher;
    watcher.setFuture(QtConcurrent::run(this, &FenFichierVisualisation::threadAjouter, fichiers));

    connect(&watcher,SIGNAL(finished()),dialog ,SLOT(close()));
    connect(&watcher,SIGNAL(finished()),this ,SLOT(fonctionActualiser()));
    connect(this,SIGNAL(chargement(int)),this ,SLOT(actualiser_chargement(int)));
    connect(dialog,SIGNAL(canceled()),&watcher,SLOT(cancel()));
    connect(dialog,SIGNAL(canceled()),this,SLOT(arreter()));



    fonctionActualiser();
}

void FenFichierVisualisation::fonctionActualiser()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    direction->refresh();
    QStringList files = direction->entryList();
    files.removeOne(".");
    files.removeOne("..");

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::fonctionRenomer()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QItemSelectionModel *selection = vue->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();

    if(listeSelections.size() == 0)
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez selectionner un fichier à renomer"));
    }

    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modele->data(listeSelections[i], Qt::DisplayRole);

        bool ok = false;
        QString nomFichier = QInputDialog::getText(this, tr("Traitement du Fichier ") + elementSelectionne.toString(), tr("Nouveau nom du Fichier ") + elementSelectionne.toString(), QLineEdit::Normal, QString(), &ok);

        if (ok && !nomFichier.isEmpty())
        {
            QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + elementSelectionne.toString());
            QFile fichierTest(QDir::homePath() + "/Analyst/" + "DataBase/" + nomFichier);

            if(fichierTest.exists())
            {
                QMessageBox::critical(this, tr("Erreur"), tr("Le fichier \"") + nomFichier + tr("\" existe déjà. Veuillez entrer un autre nom ou supprimer l'ancien fichier"));
            }

            else
            {
                fichier.rename(QDir::homePath() + "/Analyst/" + "DataBase/" + nomFichier);
            }
        }

        else if(ok && nomFichier.isEmpty())
        {
            QMessageBox::critical(this, tr("Traitement du Fichier ") + elementSelectionne.toString(), tr("Veuillez entrer le nouveau nom du fichier"));
        }

        else if(!ok)
        {
            //break;
        }

        direction->refresh();
        QStringList files = direction->entryList();
        files.removeOne(".");
        files.removeOne("..");

        modele2 = new QStandardItemModel(0, 1, this);

        foreach(QString nomFichier, files)
        {
            QFileInfo nomFichierExtension(nomFichier);

            if(nomFichierExtension.isDir())
            {
                QIcon icon(":/icones/fichiers/folder_grey.png");

                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QString extension = nomFichierExtension.completeSuffix().toUpper();
                QFile fichier(":/icones/fichiers/" + extension + ".png");

                if(!fichier.exists())
                {
                    QIcon icon(":/icones/fichiers/fichier.png");
                    QStandardItem *item = new QStandardItem(icon, nomFichier);
                    modele2->appendRow(item);
                }

                else
                {
                    QIcon icon(":/icones/fichiers/" + extension + ".png");
                    QStandardItem *item = new QStandardItem(icon, nomFichier);
                    modele2->appendRow(item);
                }
            }
        }

        modele = new QStringListModel(files);
        vue->setModel(modele2);
    }
}

void FenFichierVisualisation::fonctionSupprimer()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QItemSelectionModel *selection = vue->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();

    if(listeSelections.size() == 0)
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez selectionner un fichier à supprimer"));
    }

    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modele->data(listeSelections[i], Qt::DisplayRole);

        //int reponse = QMessageBox::warning(this, tr("Attention"), tr("Voulez vous supprimer le fichier \"") + elementSelectionne.toString() + "\" ?", QMessageBox::Yes | QMessageBox::No);

        /*QMessageBox msgBox(this);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle(tr("Attention"));
        msgBox.setText(tr("Voulez vous supprimer le fichier \"") + elementSelectionne.toString() + "\" ?");
        msgBox.addButton(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);

        QAbstractButton *button = msgBox.addButton("Ne plus me demander !", QMessageBox::ActionRole);

        int reponse = msgBox.exec();
		QAbstractButton *testButton = msgBox.clickedButton();*/

		/*QDialog *widget = new QDialog();
		widget->setWindowTitle(tr("Attention"));

		QCheckBox *box = new QCheckBox;
		box->setChecked(false);
		box->setText(tr("Ne plus me demander"));

		QLabel *label = new QLabel;
		label->setText(tr("Voulez vous supprimer le fichier \"") + elementSelectionne.toString() + "\" ?");

		QPushButton *button_oui = new QPushButton(tr("Oui"));
		QPushButton *button_non = new QPushButton(tr("Non"));

		QHBoxLayout *layout_bouton = new QHBoxLayout;
		layout_bouton->addWidget(button_oui);
		layout_bouton->addWidget(button_non);

		QVBoxLayout *layout = new QVBoxLayout;
		layout->addWidget(label);
		layout->addLayout(layout_bouton);
		layout->addWidget(box);

		widget->setLayout(layout);
		widget->show();
		widget->setVisible(true);
		*/
		//connect(button_non, SLOT(clicked()), this, SLOT(())
		//widget->resize(300,300);

        //if (reponse == QMessageBox::Yes)
        //{
            QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + elementSelectionne.toString());
            fichier.remove();
        //}


    }

    direction->refresh();
    QStringList files = direction->entryList();
    files.removeOne(".");
    files.removeOne("..");

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::afficherTextes()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QStringList fichierTextes;
    fichierTextes << "*.txt" << "*.txt" << "*.doc" << "*.pdf" << "*.postscript" << "*.html" << "*.xhtml" << "*.odt" << "*.rtf";

    QStringList files = direction->entryList(fichierTextes);

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::afficherImages()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QStringList fichierImages;
    fichierImages << "*.jpg" << "*.png" << "*.mng" << "*.tiff" << "*.jpeg" << "*.gif" << "*.tga" << "*.rtf" << "*.openexr" << "*.bmp";

    QStringList files = direction->entryList(fichierImages);

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::afficherMusiques()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QStringList fichierMusiques;
    fichierMusiques << "*.ogg" << "*.flac" << "*.mp3" << "*.wav" << "*.wma" << "*.aac" << "*.spx";

    QStringList files = direction->entryList(fichierMusiques);

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::afficherVideos()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QStringList fichierVideos;
    fichierVideos << "*.mov" << "*.mpeg" << "*.ogm" << "*.avi" << "*.theora" << "*.flv" << "*.wmv";

    QStringList files = direction->entryList(fichierVideos);

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::afficherTout()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    direction->refresh();
    QStringList files = direction->entryList();
    files.removeOne(".");
    files.removeOne("..");

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::afficherInformation()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    FenInfoFichiers *fenetreInfoFichiers = new FenInfoFichiers(this);
    fenetreInfoFichiers->show();
}

void FenFichierVisualisation::afficherInformationFichier()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QItemSelectionModel *selection = vue->selectionModel();
    QModelIndexList listeSelections = selection->selectedIndexes();

    if(listeSelections.size() == 0)
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez selectionner au moins un fichier"));
        return;
    }

    for (int i = 0 ; i < listeSelections.size() ; i++)
    {
        QVariant elementSelectionne = modele->data(listeSelections[i], Qt::DisplayRole);

        QString nomFichier = elementSelectionne.toString();

        FenInfoFichiersIndividuels *fenetreInfoFichiersIndividuels = new FenInfoFichiersIndividuels(nomFichier, this);
        fenetreInfoFichiersIndividuels->show();
    }
}

void FenFichierVisualisation::fonctionNouveauFichier()
{
    bool ok = false;
    QString nomFichier = QInputDialog::getText(this, tr("Creation de fichier"), tr("Nom du fichier :"), QLineEdit::Normal, QString(), &ok);

    while(ok && nomFichier.isEmpty())
    {
        QMessageBox::critical(this, tr("Creation de fichier"), tr("Veuillez entrer le nom du fichier"));
        QString nomFichier = QInputDialog::getText(this, tr("Creation de fichier"), tr("Nom du fichier :"), QLineEdit::Normal, QString(), &ok);
    }

    if (ok && !nomFichier.isEmpty())
    {
        QFile fichier(QDir::homePath() + "/Analyst/" + "DataBase/" + nomFichier);

        if(fichier.exists())
        {
            QMessageBox::critical(this, tr("Erreur"), tr("Le fichier \"") + nomFichier + tr("\" existe déjà. Veuillez entrer un autre nom ou supprimer l'ancien fichier"));
        }

        else
        {
            fichier.open(QIODevice::WriteOnly);
            fichier.write("");
            fichier.close();
        }
    }

    else
    {
        return;
    }

    direction->refresh();
    QStringList files = direction->entryList();
    files.removeOne(".");
    files.removeOne("..");

    modele2 = new QStandardItemModel(0, 1, this);

    foreach(QString nomFichier, files)
    {
        QFileInfo nomFichierExtension(nomFichier);

        if(nomFichierExtension.isDir())
        {
            QIcon icon(":/icones/fichiers/folder_grey.png");

            QStandardItem *item = new QStandardItem(icon, nomFichier);
            modele2->appendRow(item);
        }

        else
        {
            QString extension = nomFichierExtension.completeSuffix().toUpper();
            QFile fichier(":/icones/fichiers/" + extension + ".png");

            if(!fichier.exists())
            {
                QIcon icon(":/icones/fichiers/fichier.png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }

            else
            {
                QIcon icon(":/icones/fichiers/" + extension + ".png");
                QStandardItem *item = new QStandardItem(icon, nomFichier);
                modele2->appendRow(item);
            }
        }
    }

    modele = new QStringListModel(files);
    vue->setModel(modele2);
}

void FenFichierVisualisation::creerStatusBar()
{
    statut = new QStatusBar();
    statut->showMessage(tr("Prêt"));
}

void FenFichierVisualisation::afficherMessageAjouterFichier()
{
    statut->showMessage(tr("Ajouter des fichiers a la base de donnée"), 2000);
}

void FenFichierVisualisation::afficherParent()
{
    statut->showMessage(tr("Remonter au répertoire parent"), 2000);
}

void FenFichierVisualisation::afficherActualiser()
{
    statut->showMessage(tr("Actualiser"), 2000);
}

void FenFichierVisualisation::afficherRenommer()
{
    statut->showMessage(tr("Renomer le ou les fichiers séléctionnés"), 2000);
}

void FenFichierVisualisation::afficherSupprimer()
{
    statut->showMessage(tr("Supprimer le ou les fichiers séléctionnés"), 2000);
}

void FenFichierVisualisation::afficherMessageTextes()
{
    statut->showMessage(tr("Afficher uniquement les textes"), 2000);
}

void FenFichierVisualisation::afficherMessageImages()
{
    statut->showMessage(tr("Afficher uniquement les images"), 2000);
}

void FenFichierVisualisation::afficherMessagesMusiques()
{
    statut->showMessage(tr("Afficher uniquement les musiques"), 2000);
}

void FenFichierVisualisation::afficherMessagesVideos()
{
    statut->showMessage(tr("Afficher uniquement les videos"), 2000);
}

void FenFichierVisualisation::afficherMessagesTout()
{
    statut->showMessage(tr("Afficher tous les fichiers"), 2000);
}

void FenFichierVisualisation::afficherMessageInformation()
{
    statut->showMessage(tr("Afficher les informations de la base de données"), 2000);
}

void FenFichierVisualisation::afficherMessageInformationFichier()
{
    statut->showMessage(tr("Afficher les informations du ou des fichier(s) séléctionné(s)"), 2000);
}

void FenFichierVisualisation::afficherNouveauFichier()
{
    statut->showMessage(tr("Creer un nouveau fichier"), 2000);
}

void FenFichierVisualisation::creerActions()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    repertoireParent = new QAction(this);
    repertoireParent->setIcon(QIcon(":/icones/folder_red.png"));
    connect(repertoireParent, SIGNAL(hovered()), this, SLOT(afficherParent()));
    connect(repertoireParent, SIGNAL(triggered()), this, SLOT(fonctionParent()));

    actualiser = new QAction(this);
    actualiser->setIcon(QIcon(":/icones/Fenetre Visualisation/reload.png"));
    actualiser->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
    actualiser->setToolTip(tr("Actualiser  Ctrl+U"));
    connect(actualiser, SIGNAL(hovered()), this, SLOT(afficherActualiser()));
    connect(actualiser, SIGNAL(triggered()), this, SLOT(fonctionActualiser()));
    toolBar->addAction(actualiser);

    renomer = new QAction(this);
    renomer->setIcon(QIcon(":/icones/Fenetre Visualisation/edit.png"));
    renomer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    renomer->setToolTip(tr("Renomer  Ctrl+R"));
    connect(renomer, SIGNAL(hovered()), this, SLOT(afficherRenommer()));
    connect(renomer, SIGNAL(triggered()), this, SLOT(fonctionRenomer()));
    toolBar->addAction(renomer);

    supprimer = new QAction(this);
    supprimer->setIcon(QIcon(":/icones/Fenetre Visualisation/edittrash.png"));
    supprimer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    supprimer->setToolTip(tr("Supprimer  Ctrl+D"));
    connect(supprimer, SIGNAL(hovered()), this, SLOT(afficherSupprimer()));
    connect(supprimer, SIGNAL(triggered()), this, SLOT(fonctionSupprimer()));
    toolBar->addAction(supprimer);

    outilsNouveauFichier = new QAction(this);
    outilsNouveauFichier->setIcon(QIcon(":/icones/Fenetre Visualisation/lists.png"));
    outilsNouveauFichier->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    outilsNouveauFichier->setToolTip(tr("Nouveau fichier  Ctrl+N"));
    connect(outilsNouveauFichier, SIGNAL(hovered()), this, SLOT(afficherNouveauFichier()));
    connect(outilsNouveauFichier, SIGNAL(triggered()), this, SLOT(fonctionNouveauFichier()));
    toolBar->addAction(outilsNouveauFichier);

    toolBar->addSeparator();

    outilsTexte = new QAction(this);
    outilsTexte->setIcon(QIcon(":/icones/Fenetre Visualisation/folder_documents.png"));
    outilsTexte->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    outilsTexte->setToolTip(tr("Seulement les textes  Ctrl+T"));
    connect(outilsTexte, SIGNAL(hovered()), this, SLOT(afficherMessageTextes()));
    connect(outilsTexte, SIGNAL(triggered()), this, SLOT(afficherTextes()));
    toolBar->addAction(outilsTexte);

    outilsImage = new QAction(this);
    outilsImage->setIcon(QIcon(":/icones/Fenetre Visualisation/folder_images.png"));
    outilsImage->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    outilsImage->setToolTip(tr("Seulement les images  Ctrl+P"));
    connect(outilsImage, SIGNAL(hovered()), this, SLOT(afficherMessageImages()));
    connect(outilsImage, SIGNAL(triggered()), this, SLOT(afficherImages()));
    toolBar->addAction(outilsImage);

    outilsVideo = new QAction(this);
    outilsVideo->setIcon(QIcon(":/icones/Fenetre Visualisation/folder_video.png"));
    outilsVideo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    outilsVideo->setToolTip(tr("Seulement les videos  Ctrl+V"));
    connect(outilsVideo, SIGNAL(hovered()), this, SLOT(afficherMessagesVideos()));
    connect(outilsVideo, SIGNAL(triggered()), this, SLOT(afficherVideos()));
    toolBar->addAction(outilsVideo);

    outilsMusique = new QAction(this);
    outilsMusique->setIcon(QIcon(":/icones/Fenetre Visualisation/folder_music.png"));
    outilsMusique->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    outilsMusique->setToolTip(tr("Seulement les musiques  Ctrl+M"));
    connect(outilsMusique, SIGNAL(hovered()), this, SLOT(afficherMessagesMusiques()));
    connect(outilsMusique, SIGNAL(triggered()), this, SLOT(afficherMusiques()));
    toolBar->addAction(outilsMusique);

    toolBar->addSeparator();

    outilsInformation = new QAction(this);
    outilsInformation->setIcon(QIcon(":/icones/Fenetre Visualisation/info.png"));
    outilsInformation->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    outilsInformation->setToolTip(tr("Informations Generales  Ctrl+G"));
    connect(outilsInformation, SIGNAL(hovered()), this, SLOT(afficherMessageInformation()));
    connect(outilsInformation, SIGNAL(triggered()), this, SLOT(afficherInformation()));
    toolBar->addAction(outilsInformation);

    outilsInformationFichier = new QAction(this);
    outilsInformationFichier->setIcon(QIcon(":/icones/Fenetre Visualisation/info-fichier.png"));
    outilsInformationFichier->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    outilsInformationFichier->setToolTip(tr("Informations du fichier  Ctrl+F"));
    connect(outilsInformationFichier, SIGNAL(hovered()), this, SLOT(afficherMessageInformationFichier()));
    connect(outilsInformationFichier, SIGNAL(triggered()), this, SLOT(afficherInformationFichier()));
    toolBar->addAction(outilsInformationFichier);

    outilsTout = new QAction(this);
    outilsTout->setIcon(QIcon(":/icones/Fenetre Visualisation/folder_document.png"));
    outilsTout->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    outilsTout->setToolTip(tr("Afficher tout  Ctrl+A"));
    connect(outilsTout, SIGNAL(hovered()), this, SLOT(afficherMessagesTout()));
    connect(outilsTout, SIGNAL(triggered()), this, SLOT(afficherTout()));
    toolBar->addAction(outilsTout);

    ajouter_fichier = new QAction(this);
    ajouter_fichier->setIcon(QIcon(":/icones/Fenetre Visualisation/download.png"));
    ajouter_fichier->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    ajouter_fichier->setToolTip(tr("Importer des fichiers  Ctrl+I"));
    connect(ajouter_fichier, SIGNAL(hovered()), this, SLOT(afficherMessageAjouterFichier()));
    connect(ajouter_fichier, SIGNAL(triggered()), this, SLOT(ajouterFichier()));
    toolBar->addAction(ajouter_fichier);
}

void FenFichierVisualisation::creerFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(toolBar);
    layout->addWidget(vue);
    layout->addWidget(statut);

    setLayout(layout);

    #if defined(Q_WS_WIN)
        setFixedSize(650,500);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(650,500);
    #endif

    setWindowTitle(tr("Analyst - Gestion de la Base de Donnée"));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));
}

void FenFichierVisualisation::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
