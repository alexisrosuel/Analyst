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

#include "../headers/FenConsole.h"

FenConsole::FenConsole()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();
}

void FenConsole::analyser()
{
    QString commande_entree = commande->toPlainText().section('\n', -1);
    commande->textCursor().insertText("\n");

    if(commande_entree.startsWith("open"))
    {
        QString fichier;
        fichier = commande_entree.section("open", 1, 2);
        fichier.remove(0, 1);

        if((commande_entree.contains(".txt", Qt::CaseInsensitive)) || (commande_entree.contains(".pdf", Qt::CaseInsensitive)) || (commande_entree.contains(".postscript", Qt::CaseInsensitive)) || (commande_entree.contains(".html", Qt::CaseInsensitive)) || (commande_entree.contains(".xhtml", Qt::CaseInsensitive)) || (commande_entree.contains(".rtf", Qt::CaseInsensitive)))
        {
            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + fichier;

            QFile lancementFichier(nomFichier);
            QString texte;

            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                texte = lancementFichier.readAll();
                lancementFichier.close();

                FenFichierTexte *fenetreTexte = new FenFichierTexte(texte, nomFichier, NULL);
                fenetreTexte->show();
            }

            else
            {
                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
            }
        }

        else if((commande_entree.contains(".jpg", Qt::CaseInsensitive)) || (commande_entree.contains(".png", Qt::CaseInsensitive)) || (commande_entree.contains(".mng", Qt::CaseInsensitive)) || (commande_entree.contains(".tiff", Qt::CaseInsensitive)) || (commande_entree.contains(".jpeg", Qt::CaseInsensitive)) || (commande_entree.contains(".gif", Qt::CaseInsensitive)) || (commande_entree.contains(".tga", Qt::CaseInsensitive))  || (commande_entree.contains(".bmp", Qt::CaseInsensitive)) || (commande_entree.contains(".openexr", Qt::CaseInsensitive)))
        {
            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + fichier;

            if(!QFile::exists(nomFichier))
            {
                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                return;
            }

            else
            {
                FenFichierImage *fenetreImage = new FenFichierImage(nomFichier, NULL);
                fenetreImage->show();
            }
        }

        else if(((commande_entree.contains(".mov", Qt::CaseInsensitive)) || (commande_entree.contains(".mpeg", Qt::CaseInsensitive)) || (commande_entree.contains(".ogm", Qt::CaseInsensitive)) || (commande_entree.contains(".avi", Qt::CaseInsensitive)) || (commande_entree.contains(".theora", Qt::CaseInsensitive)) || (commande_entree.contains(".flv", Qt::CaseInsensitive)) || (commande_entree.contains(".wmv", Qt::CaseInsensitive))))
        {
            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + fichier;

            if(!QFile::exists(nomFichier))
            {
                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                return;
            }

            else
            {
                FenFichierVideo *fenetreVideo = new FenFichierVideo(nomFichier, NULL);
                fenetreVideo->show();
            }
        }

        else if(((commande_entree.contains(".ogg", Qt::CaseInsensitive)) || (commande_entree.contains(".flac", Qt::CaseInsensitive)) || (commande_entree.contains(".mp3", Qt::CaseInsensitive)) || (commande_entree.contains(".wav", Qt::CaseInsensitive)) || (commande_entree.contains(".wma", Qt::CaseInsensitive)) || (commande_entree.contains(".aac", Qt::CaseInsensitive)) || (commande_entree.contains(".spx", Qt::CaseInsensitive))))
        {
            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + fichier;

            if(!QFile::exists(nomFichier))
            {
                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                return;
            }

            else
            {
                FenFichierMusique *fenetreMusique = new FenFichierMusique(nomFichier, NULL);
                fenetreMusique->show();
            }
        }

        else
        {
            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + fichier;
            QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/" + nomFichier));
        }

        if(commande_entree.contains("*"))
        {
            //commande_entree = fichier;

            while(fichier.startsWith("-"))
            {
                while(!fichier.at(0).isSpace())
                {
                    fichier.remove(0, 1);
                }

                fichier.remove(0, 1);

                //QMessageBox::information(this, "test", "test");
            }


            QDir direction;
            direction.cd(QDir::homePath() + "/Analyst/" + "DataBase");
            QStringList nom_des_fichiers = direction.entryList();

            fichier.remove(fichier.length()-1, 1);

            foreach(QString files, nom_des_fichiers)
            {
                if(files.startsWith(fichier))
                {
                    if(commande_entree.contains("-texts"))
                    {
                       if((files.contains(".txt", Qt::CaseInsensitive)) || (files.contains(".pdf", Qt::CaseInsensitive)) || (files.contains(".postscript", Qt::CaseInsensitive)) || (files.contains(".html", Qt::CaseInsensitive)) || (files.contains(".xhtml", Qt::CaseInsensitive)) || (files.contains(".rtf", Qt::CaseInsensitive)))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            QFile lancementFichier(nomFichier);
                            QString texte;

                            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
                            {
                                texte = lancementFichier.readAll();
                                lancementFichier.close();

                                FenFichierTexte *fenetreTexte = new FenFichierTexte(texte, nomFichier, NULL);
                                fenetreTexte->show();
                            }

                            else
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                            }
                        }

                        if((files.contains(".doc", Qt::CaseInsensitive)) || (files.contains(".docx", Qt::CaseInsensitive)) || (files.contains(".odt", Qt::CaseInsensitive)))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;
                            QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/" + nomFichier));
                        }
                    }

                    if(commande_entree.contains("-pictures"))
                    {
                        if((files.contains(".jpg", Qt::CaseInsensitive)) || (files.contains(".png", Qt::CaseInsensitive)) || (files.contains(".mng", Qt::CaseInsensitive)) || (files.contains(".tiff", Qt::CaseInsensitive)) || (files.contains(".jpeg", Qt::CaseInsensitive)) || (files.contains(".gif", Qt::CaseInsensitive)) || (files.contains(".tga", Qt::CaseInsensitive))  || (files.contains(".bmp", Qt::CaseInsensitive)) || (files.contains(".openexr", Qt::CaseInsensitive)))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            if(!QFile::exists(nomFichier))
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                                return;
                            }

                            else
                            {
                                FenFichierImage *fenetreImage = new FenFichierImage(nomFichier, NULL);
                                fenetreImage->show();
                            }
                        }
                    }

                    if(commande_entree.contains("-musics"))
                    {
                        if(((files.contains(".ogg", Qt::CaseInsensitive)) || (files.contains(".flac", Qt::CaseInsensitive)) || (files.contains(".mp3", Qt::CaseInsensitive)) || (files.contains(".wav", Qt::CaseInsensitive)) || (files.contains(".wma", Qt::CaseInsensitive)) || (files.contains(".aac", Qt::CaseInsensitive)) || (files.contains(".spx", Qt::CaseInsensitive))))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            if(!QFile::exists(nomFichier))
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                                return;
                            }

                            else
                            {
                                FenFichierMusique *fenetreMusique = new FenFichierMusique(nomFichier, NULL);
                                fenetreMusique->show();
                            }
                        }
                    }

                    if(commande_entree.contains("-movies"))
                    {
                        if(((files.contains(".mov", Qt::CaseInsensitive)) || (files.contains(".mpeg", Qt::CaseInsensitive)) || (files.contains(".ogm", Qt::CaseInsensitive)) || (files.contains(".avi", Qt::CaseInsensitive)) || (files.contains(".theora", Qt::CaseInsensitive)) || (files.contains(".flv", Qt::CaseInsensitive)) || (files.contains(".wmv", Qt::CaseInsensitive))))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            if(!QFile::exists(nomFichier))
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                                return;
                            }

                            else
                            {
                                FenFichierVideo *fenetreVideo = new FenFichierVideo(nomFichier, NULL);
                                fenetreVideo->show();
                            }
                        }
                    }

                    if(!commande_entree.contains("-texts") && !commande_entree.contains("-pictures") && !commande_entree.contains("-musics") && !commande_entree.contains("-movies"))
                    {
                        if((files.contains(".txt", Qt::CaseInsensitive)) || (files.contains(".pdf", Qt::CaseInsensitive)) || (files.contains(".postscript", Qt::CaseInsensitive)) || (files.contains(".html", Qt::CaseInsensitive)) || (files.contains(".xhtml", Qt::CaseInsensitive)) || (files.contains(".rtf", Qt::CaseInsensitive)))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            QFile lancementFichier(nomFichier);
                            QString texte;

                            if(lancementFichier.open(QIODevice::ReadOnly | QIODevice::Text))
                            {
                                texte = lancementFichier.readAll();
                                lancementFichier.close();

                                FenFichierTexte *fenetreTexte = new FenFichierTexte(texte, nomFichier, NULL);
                                fenetreTexte->show();
                            }

                            else
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                            }
                        }

                        else if((files.contains(".doc", Qt::CaseInsensitive)) || (files.contains(".docx", Qt::CaseInsensitive)) || (files.contains(".odt", Qt::CaseInsensitive)))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "/DataBase/" + files;
                            QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + nomFichier));
                        }

                        else if((files.contains(".jpg", Qt::CaseInsensitive)) || (files.contains(".png", Qt::CaseInsensitive)) || (files.contains(".mng", Qt::CaseInsensitive)) || (files.contains(".tiff", Qt::CaseInsensitive)) || (files.contains(".jpeg", Qt::CaseInsensitive)) || (files.contains(".gif", Qt::CaseInsensitive)) || (files.contains(".tga", Qt::CaseInsensitive))  || (files.contains(".bmp", Qt::CaseInsensitive)) || (files.contains(".openexr", Qt::CaseInsensitive)))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            if(!QFile::exists(nomFichier))
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                                return;
                            }

                            else
                            {
                                FenFichierImage *fenetreImage = new FenFichierImage(nomFichier, NULL);
                                fenetreImage->show();
                            }
                        }

                        else if(((files.contains(".ogg", Qt::CaseInsensitive)) || (files.contains(".flac", Qt::CaseInsensitive)) || (files.contains(".mp3", Qt::CaseInsensitive)) || (files.contains(".wav", Qt::CaseInsensitive)) || (files.contains(".wma", Qt::CaseInsensitive)) || (files.contains(".aac", Qt::CaseInsensitive)) || (files.contains(".spx", Qt::CaseInsensitive))))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            if(!QFile::exists(nomFichier))
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                                return;
                            }

                            else
                            {
                                FenFichierMusique *fenetreMusique = new FenFichierMusique(nomFichier, NULL);
                                fenetreMusique->show();
                            }
                        }

                        else if(((files.contains(".mov", Qt::CaseInsensitive)) || (files.contains(".mpeg", Qt::CaseInsensitive)) || (files.contains(".ogm", Qt::CaseInsensitive)) || (files.contains(".avi", Qt::CaseInsensitive)) || (files.contains(".theora", Qt::CaseInsensitive)) || (files.contains(".flv", Qt::CaseInsensitive)) || (files.contains(".wmv", Qt::CaseInsensitive))))
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "DataBase/" + files;

                            if(!QFile::exists(nomFichier))
                            {
                                commande->insertPlainText(tr("Le fichier n'existe pas\n"));
                                return;
                            }

                            else
                            {
                                FenFichierVideo *fenetreVideo = new FenFichierVideo(nomFichier, NULL);
                                fenetreVideo->show();
                            }
                        }

                        else
                        {
                            QString nomFichier = QDir::homePath() + "/Analyst/" + "/DataBase/" + files;
                            QDesktopServices::openUrl(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + nomFichier));
                        }
                    }
                }
            }
        }
    }

    if(commande_entree.startsWith("about"))
    {
        FenLicence *licence = new FenLicence(NULL);
        licence->show();
    }


    if(commande_entree.startsWith(QDir::homePath() + "/Analyst/" + "database"))
    {
        if(commande_entree.contains("-texts"))
        {
            FenFichierVisualisation *visualisation = new FenFichierVisualisation(1, NULL);
            visualisation->show();
        }

        else if(commande_entree.contains("-pictures"))
        {
            FenFichierVisualisation *visualisation = new FenFichierVisualisation(2, NULL);
            visualisation->show();
        }

        else if(commande_entree.contains("-musics"))
        {
            FenFichierVisualisation *visualisation = new FenFichierVisualisation(3, NULL);
            visualisation->show();
        }

        else if(commande_entree.contains("-movies"))
        {
            FenFichierVisualisation *visualisation = new FenFichierVisualisation(4, NULL);
            visualisation->show();
        }

        else
        {
            FenFichierVisualisation *visualisation = new FenFichierVisualisation(5, NULL);
            visualisation->show();
        }
    }

    if(commande_entree.startsWith("search"))
    {
        int afficher = 5;

        if(commande_entree.contains("-texts"))
        {
            afficher = 1;
        }

        if(commande_entree.contains("-pictures"))
        {
            afficher = 2;
        }

        if(commande_entree.contains("-musics"))
        {
            afficher = 3;
        }

        if(commande_entree.contains("-movies"))
        {
            afficher = 4;
        }

        if(commande_entree.contains("-sensitive") && commande_entree.contains("-entire"))
        {
            QString fichier = commande_entree.section("search", 1, 2);
            fichier.remove(0,1);

            while(fichier.startsWith("-"))
            {
                while(!fichier.at(0).isSpace())
                {
                    fichier.remove(0, 1);
                }

                fichier.remove(0, 1);
            }

            FenRecherche *recherche = new FenRecherche(NULL);
            QString resultat = recherche->rechercheCasseEntier(fichier);

            FenResultat *fenetreResultat = new FenResultat(resultat, recherche->resultatAffiner, afficher, NULL);

            if(commande_entree.contains("-results"))
            {
                fenetreResultat->show();
            }

            if(commande_entree.contains("-openall"))
            {
                FenOuvertureFichier *fenetreOuverture = new FenOuvertureFichier(resultat, NULL);
                fenetreOuverture->nomFichier->setHtml(resultat);
                fenetreOuverture->ouvrir();
            }

            if(commande_entree.contains("-texts") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirTousTextes();
            }

            if(commande_entree.contains("-pictures") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesImages();
            }

            if(commande_entree.contains("-musics") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesMusiques();
            }

            if(commande_entree.contains("-movies") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesVideos();
            }
        }

        else if(!commande_entree.contains("-sensitive") && !commande_entree.contains("-entire"))
        {
            QString fichier = commande_entree.section("search", 1, 2);
            fichier.remove(0,1);

            while(fichier.startsWith("-"))
            {
                while(!fichier.at(0).isSpace())
                {
                    fichier.remove(0, 1);
                }

                fichier.remove(0, 1);
            }

            FenRecherche *recherche = new FenRecherche(NULL);
            QString resultat = recherche->recherche(fichier);

            FenResultat *fenetreResultat = new FenResultat(resultat, recherche->resultatAffiner, afficher, NULL);

            if(commande_entree.contains("-results"))
            {
                fenetreResultat->show();
            }

            if(commande_entree.contains("-openall"))
            {
                FenOuvertureFichier *fenetreOuverture = new FenOuvertureFichier(resultat, NULL);
                fenetreOuverture->nomFichier->setHtml(resultat);
                fenetreOuverture->ouvrir();
            }

            if(commande_entree.contains("-texts") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirTousTextes();
            }

            if(commande_entree.contains("-pictures") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesImages();
            }

            if(commande_entree.contains("-musics") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesMusiques();
            }

            if(commande_entree.contains("-movies") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesVideos();
            }
        }

        else if(commande_entree.contains("-sensitive"))
        {
            QString fichier = commande_entree.section("search", 1, 2);
            fichier.remove(0,1);

            while(fichier.startsWith("-"))
            {
                while(!fichier.at(0).isSpace())
                {
                    fichier.remove(0, 1);
                }

                fichier.remove(0, 1);
            }

            FenRecherche *recherche = new FenRecherche(NULL);
            QString resultat = recherche->rechercheCasse(fichier);

            FenResultat *fenetreResultat = new FenResultat(resultat, recherche->resultatAffiner, afficher, NULL);

            if(commande_entree.contains("-results"))
            {
                fenetreResultat->show();
            }

            if(commande_entree.contains("-openall"))
            {
                FenOuvertureFichier *fenetreOuverture = new FenOuvertureFichier(resultat, NULL);
                fenetreOuverture->nomFichier->setHtml(resultat);
                fenetreOuverture->ouvrir();
            }

            if(commande_entree.contains("-texts") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirTousTextes();
            }

            if(commande_entree.contains("-pictures") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesImages();
            }

            if(commande_entree.contains("-musics") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesMusiques();
            }

            if(commande_entree.contains("-movies") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesVideos();
            }
        }

        else if(commande_entree.contains("-entire"))
        {
            QString fichier = commande_entree.section("search", 1, 2);
            fichier.remove(0,1);

            while(fichier.startsWith("-"))
            {
                while(!fichier.at(0).isSpace())
                {
                    fichier.remove(0, 1);
                }

                fichier.remove(0, 1);
            }

            FenRecherche *recherche = new FenRecherche(NULL);
            QString resultat = recherche->rechercheEntier(fichier);

            FenResultat *fenetreResultat = new FenResultat(resultat, recherche->resultatAffiner, afficher, NULL);

            if(commande_entree.contains("-results"))
            {
                fenetreResultat->show();
            }

            if(commande_entree.contains("-openall"))
            {
                FenOuvertureFichier *fenetreOuverture = new FenOuvertureFichier(resultat, NULL);
                fenetreOuverture->nomFichier->setHtml(resultat);
                fenetreOuverture->ouvrir();
            }

            if(commande_entree.contains("-texts") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirTousTextes();
            }

            if(commande_entree.contains("-pictures") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesImages();
            }

            if(commande_entree.contains("-musics") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesMusiques();
            }

            if(commande_entree.contains("-movies") && commande_entree.contains("-open"))
            {
                fenetreResultat->fonctionOuvrirToutesVideos();
            }
        }

    }


    if(commande_entree.startsWith("internet"))
    {
        bool texte = false;
        bool images = false;
        bool tout_textes = false;
        bool toutes_images = false;
        bool console = true;
        bool display = true;

        if(commande_entree.contains("-texts"))
        {
            texte = true;
        }

        if(commande_entree.contains("-pictures"))
        {
            images = true;
        }

        if(commande_entree.contains("-alltexts"))
        {
            tout_textes = true;
        }

        if(commande_entree.contains("-allpictures"))
        {
            toutes_images = true;
        }

        if(commande_entree.contains("-nodisplay"))
        {
            display = false;
        }

        QString fichier = commande_entree.section("internet", 1, 2);
        fichier.remove(0,1);

        while(fichier.startsWith("-"))
        {
            while(!fichier.at(0).isSpace())
            {
                fichier.remove(0, 1);
            }

            fichier.remove(0, 1);
        }

        FenInternet *recherche_internet = new FenInternet(texte, images, tout_textes, toutes_images, console, display, fichier, NULL);
        recherche_internet->rechercheInternet();

        //FenConsole *nouvelle_console = new FenConsole();
        //nouvelle_console->show();
        //nouvelle_console->commande->setPlainText(commande->toPlainText());
    }

    if(commande_entree.startsWith("general"))
    {
        FenInfoFichiers *infoFichier = new FenInfoFichiers(NULL);
        infoFichier->show();
    }

    if(commande_entree.startsWith("info"))
    {
        QString fichier;
        fichier = commande_entree.section("info", 1, 2);
        fichier.remove(0, 1);

        if(commande_entree.contains("*"))
        {
            QString fichier = commande_entree.section("info", 1, 2);
            fichier.remove(0,1);

            while(fichier.startsWith("-"))
            {
                while(!fichier.at(0).isSpace())
                {
                    fichier.remove(0, 1);
                }

                fichier.remove(0, 1);
            }

            if(commande_entree.contains("-texts"))
            {
                QDir direction;
                direction.cd(QDir::homePath() + "/Analyst/" + "DataBase");
                QStringList nom_des_fichiers = direction.entryList();

                fichier.remove(fichier.length()-1, 1);

                foreach(QString files, nom_des_fichiers)
                {
                    if(files.startsWith(fichier) && ((files.contains(".txt", Qt::CaseInsensitive) || (files.contains(".doc", Qt::CaseInsensitive)) || (files.contains(".pdf", Qt::CaseInsensitive)) || (files.contains(".postscript", Qt::CaseInsensitive)) || (files.contains(".html", Qt::CaseInsensitive)) || (files.contains(".xhtml", Qt::CaseInsensitive)) || (files.contains(".odt", Qt::CaseInsensitive)) || (files.contains(".rtf", Qt::CaseInsensitive)))))
                    {
                            FenInfoFichiersIndividuels *individuels = new FenInfoFichiersIndividuels(files, NULL);
                            individuels->show();
                    }
                }
            }

            if(commande_entree.contains("-pictures"))
            {
                QDir direction;
                direction.cd(QDir::homePath() + "/Analyst/" + "DataBase");
                QStringList nom_des_fichiers = direction.entryList();

                fichier.remove(fichier.length()-1, 1);

                foreach(QString files, nom_des_fichiers)
                {
                    if(files.startsWith(fichier) && ((files.contains(".jpg", Qt::CaseInsensitive)) || (files.contains(".png", Qt::CaseInsensitive)) || (files.contains(".mng", Qt::CaseInsensitive)) || (files.contains(".tiff", Qt::CaseInsensitive)) || (files.contains(".jpeg", Qt::CaseInsensitive)) || (files.contains(".gif", Qt::CaseInsensitive)) || (files.contains(".tga", Qt::CaseInsensitive)) || (files.contains(".rtf", Qt::CaseInsensitive)) || (files.contains(".openexr", Qt::CaseInsensitive) || (files.contains(".bmp", Qt::CaseInsensitive)))))
                    {
                            FenInfoFichiersIndividuels *individuels = new FenInfoFichiersIndividuels(files, NULL);
                            individuels->show();
                    }
                }
            }

            if(commande_entree.contains("-musics"))
            {
                QDir direction;
                direction.cd(QDir::homePath() + "/Analyst/" + "DataBase");
                QStringList nom_des_fichiers = direction.entryList();

                fichier.remove(fichier.length()-1, 1);

                foreach(QString files, nom_des_fichiers)
                {
                    if(files.startsWith(fichier) && ((files.contains(".ogg", Qt::CaseInsensitive)) || (files.contains(".flac", Qt::CaseInsensitive)) || (files.contains(".mp3", Qt::CaseInsensitive)) || (files.contains(".wav", Qt::CaseInsensitive)) || (files.contains(".wma", Qt::CaseInsensitive)) || (files.contains(".aac", Qt::CaseInsensitive)) || (files.contains(".spx", Qt::CaseInsensitive))))
                    {
                            FenInfoFichiersIndividuels *individuels = new FenInfoFichiersIndividuels(files, NULL);
                            individuels->show();
                    }
                }
            }

            if(commande_entree.contains("-movies"))
            {
                QDir direction;
                direction.cd(QDir::homePath() + "/Analyst/" + "DataBase");
                QStringList nom_des_fichiers = direction.entryList();

                fichier.remove(fichier.length()-1, 1);

                foreach(QString files, nom_des_fichiers)
                {
                    if(files.startsWith(fichier) && ((files.contains(".mov", Qt::CaseInsensitive)) || (files.contains(".mpeg", Qt::CaseInsensitive)) || (files.contains(".ogm", Qt::CaseInsensitive)) || (files.contains(".avi", Qt::CaseInsensitive)) || (files.contains(".theora", Qt::CaseInsensitive)) || (files.contains(".flv", Qt::CaseInsensitive)) || (files.contains(".wmv", Qt::CaseInsensitive))))
                    {
                            FenInfoFichiersIndividuels *individuels = new FenInfoFichiersIndividuels(files, NULL);
                            individuels->show();
                    }
                }
            }

            if(!commande_entree.contains("-texts") && !commande_entree.contains("-pictures") && !commande_entree.contains("-musics") && !commande_entree.contains("-movies"))
            {
                QDir direction;
                direction.cd(QDir::homePath() + "/Analyst/" + "DataBase");
                QStringList nom_des_fichiers = direction.entryList();

                fichier.remove(fichier.length()-1, 1);

                foreach(QString files, nom_des_fichiers)
                {
                    if(files.startsWith(fichier))
                    {
                            FenInfoFichiersIndividuels *individuels = new FenInfoFichiersIndividuels(files, NULL);
                            individuels->show();
                    }
                }
            }
        }

        else
        {
            QString fichier;
            fichier = commande_entree.section("info", 1, 2);
            fichier.remove(0, 1);

            FenInfoFichiersIndividuels *individuels = new FenInfoFichiersIndividuels(fichier, NULL);
            individuels->show();
        }
    }

    if(commande_entree.startsWith("quit"))
    {
        qApp->quit();
    }


    hide();
    show();
    //setWindowModality(Qt::WindowModal);//
    activateWindow();
}

void FenConsole::retour()
{
     QString nouveau = commande->toPlainText().remove(commande->toPlainText().length()-1, 1);
     commande->clear();
     commande->insertPlainText(nouveau);
     //commande->setTextCursor(*cursor);
     //commande->setTextCursor(QTextCursor::End);
}

void FenConsole::update_affichage(QChar car)
{
    //commande->setTextCursor(*cursor);

    commande->textCursor().insertText(car);
}

void FenConsole::bouger(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left && !commande->textCursor().atStart())
    {
        cursor->setPosition(commande->textCursor().position() - 1);
        //commande->setTextCursor(*cursor);
    }

    if(event->key() == Qt::Key_Right && !commande->textCursor().atEnd())
    {
        cursor->setPosition(commande->textCursor().position() + 1);
        commande->setTextCursor(*cursor);
    }

    if(event->key() == Qt::Key_Up)
    {
        QString commande_entree = commande->toPlainText().section('\n', -2);
        commande->textCursor().insertText(commande_entree);
    }
}

void FenConsole::creerFenetre()
{
    commande = new Entre_console;
    commande->setStyleSheet("background-color: black;");
    //commande->setTextBackgroundColor(QColor(Qt::black));
    commande->setTextColor(QColor(Qt::white));

    cursor = new QTextCursor;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(commande);

    setLayout(layout);

    connect(commande, SIGNAL(signal_analyser()), this, SLOT(analyser()));
    connect(commande, SIGNAL(signal_retour()), this, SLOT(retour()));
    connect(commande, SIGNAL(signal_update_affichage(QChar)), this, SLOT(update_affichage(QChar)));
    connect(commande, SIGNAL(signal_bouger(QKeyEvent*)), this, SLOT(bouger(QKeyEvent*)));

    //installEventFilter(commande);

    //setWindowFlags(Qt::WindowStaysOnTopHint);

    setWindowTitle("Analyst - Console");
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    #if defined(Q_WS_WIN)
        setFixedSize(350,350);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(350,350);
    #endif

}

void Entre_console::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        emit signal_analyser();
    }

    else if(event->key() == Qt::Key_Backspace)
    {
        emit signal_retour();
    }

    else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Right || event->key() == Qt::Key_Up)
    {
        emit signal_bouger(event);
    }

    else if(event->text().at(0).isLetterOrNumber() || event->text().at(0).isSpace() || event->text().at(0).isPunct() || event->text().at(0).isPrint() || event->text().at(0).isMark() || event->text().at(0).isSymbol())
    {
        emit signal_update_affichage(event->text().at(0));
    }
}

void FenConsole::closeEvent(QCloseEvent *event)
{
    int reponse = QMessageBox::warning(this, tr("Attention"), tr("Vous allez quitter Analyst. Voulez vous continuer"), QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        qApp->quit();
    }
    else if (reponse == QMessageBox::No)
    {
        event->ignore();
    }
}


