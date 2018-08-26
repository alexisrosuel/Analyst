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

#include "../headers/FenInternet.h"

using namespace std;

FenInternet::FenInternet(bool textes, bool images, bool tout_texts, bool toute_images, bool console, bool display, QString mot_recherche, QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    textes_vrai = textes;
    images_vrai = images;
    tout_texts_vrai = tout_texts;
    toute_images_vrai = toute_images;

    display_vrai = display;

    mot_recherche_vrai = mot_recherche;

    console_vrai = console;

    creerFenetre();
}

void FenInternet::rechercheInternet()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    if(!texteSeulement->isChecked() && !imagesSeulement->isChecked() && !console_vrai)
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous devez cocher au moins une des deux cases"));
        return;
    }

    if(motInternet->text().isEmpty() && !console_vrai)
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez entrer au moins un mot à rechercher"));
        return;
    }

    numeroImage = 0;

    if(!console_vrai)
    {
        QString rechercheInternetVrai = motInternet->text();
        rechercheInternetVrai = rechercheInternetVrai.toLower();
        rechercheInternetVrai = rechercheInternetVrai.replace(0,1,rechercheInternetVrai.at(0).toUpper());

        if(rechercheInternetVrai.endsWith(' '))
        {
            rechercheInternetVrai.remove(rechercheInternetVrai.length()-1, rechercheInternetVrai.length());
        }

        int numeroDuCaractere = 0;

        while(numeroDuCaractere < rechercheInternetVrai.size())
        {
            numeroDuCaractere++;

            if(rechercheInternetVrai.at(numeroDuCaractere).isSpace())
            {
                rechercheInternetVrai = rechercheInternetVrai.replace(numeroDuCaractere,1,"_");
                numeroDuCaractere++;

                if(rechercheInternetVrai.at(numeroDuCaractere).isLower())
                {
                    rechercheInternetVrai = rechercheInternetVrai.replace(numeroDuCaractere,1,rechercheInternetVrai.at(numeroDuCaractere).toUpper());
                }

                else if(rechercheInternetVrai.at(numeroDuCaractere).isSpace())
                {
                    numeroDuCaractere--;
                }
            }
        }

        dialog = new QProgressDialog();
        dialog->setLabelText(tr("Téléchargement des informations..."));
        dialog->setModal(true);
        dialog->setWindowFlags(Qt::WindowStaysOnTopHint);
        dialog->setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));
        dialog->setWindowTitle(tr("Téléchargement..."));
        dialog->show();
        connect(dialog, SIGNAL(canceled()), dialog, SLOT(close()));

        connect(dialog,SIGNAL(canceled()),this,SLOT(arreter()));

        erreur = false;
        ok = true;

        //motInternet->setText(rechercheInternetVrai);
        motInternet->setReadOnly(true);

        QString nomSite;
        nomSite = "http://en.wikipedia.org/wiki/" + rechercheInternetVrai;

        const QUrl url = QUrl(nomSite);
        const QNetworkRequest requete(url);
        QNetworkAccessManager *manager = new QNetworkAccessManager;
        QNetworkReply *reponse = manager->get(requete);

        connect(reponse, SIGNAL(finished()), this, SLOT(telechargementTermine()));
        connect(reponse, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur_texte(QNetworkReply::NetworkError)));
        connect(reponse, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressionTelechargement(qint64, qint64) ));

    }

    else
    {
        QString rechercheInternetVrai = mot_recherche_vrai;
        rechercheInternetVrai = rechercheInternetVrai.toLower();
        rechercheInternetVrai = rechercheInternetVrai.replace(0,1,rechercheInternetVrai.at(0).toUpper());

        if(rechercheInternetVrai.endsWith(' '))
        {
            rechercheInternetVrai.remove(rechercheInternetVrai.length()-1, rechercheInternetVrai.length());
        }

        int numeroDuCaractere = 0;

        while(numeroDuCaractere < rechercheInternetVrai.size())
        {
            numeroDuCaractere++;

            if(rechercheInternetVrai.at(numeroDuCaractere).isSpace())
            {
                rechercheInternetVrai = rechercheInternetVrai.replace(numeroDuCaractere,1,"_");
                numeroDuCaractere++;

                if(rechercheInternetVrai.at(numeroDuCaractere).isLower())
                {
                    rechercheInternetVrai = rechercheInternetVrai.replace(numeroDuCaractere,1,rechercheInternetVrai.at(numeroDuCaractere).toUpper());
                }

                else if(rechercheInternetVrai.at(numeroDuCaractere).isSpace())
                {
                    numeroDuCaractere--;
                }
            }
        }

        dialog = new QProgressDialog();
        dialog->setLabelText(tr("Téléchargement des informations..."));
        dialog->setModal(true);
        dialog->setWindowFlags(Qt::WindowStaysOnTopHint);
        dialog->setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));
        dialog->setWindowTitle(tr("Téléchargement..."));
        dialog->show();
        connect(dialog, SIGNAL(canceled()), dialog, SLOT(close()));

        connect(dialog,SIGNAL(canceled()),this,SLOT(arreter()));

        erreur = false;
        ok = true;

        //motInternet->setText(rechercheInternetVrai);
        motInternet->setReadOnly(true);

        QString nomSite;
        nomSite = "http://en.wikipedia.org/wiki/" + rechercheInternetVrai;

        const QUrl url = QUrl(nomSite);
        const QNetworkRequest requete(url);
        QNetworkAccessManager *manager = new QNetworkAccessManager;
        QNetworkReply *reponse = manager->get(requete);

        connect(reponse, SIGNAL(finished()), this, SLOT(telechargementTermine()));
        connect(reponse, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur_texte(QNetworkReply::NetworkError)));
        connect(reponse, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressionTelechargement(qint64, qint64) ));
    }
}

void FenInternet::telechargementTermine()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #elif defined (WIN32)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    #endif

    if(erreur)
    {
        QMessageBox::critical(this, "Erreur", "Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard. Vérifiez aussi l'orthographe de votre recherche.");
        motInternet->setReadOnly(false);
        return;
    }

    QNetworkReply *reponse = qobject_cast<QNetworkReply*>(sender());

    contenuFichier = reponse->readAll();

    if(texteSeulement->isChecked() && !console_vrai)
    {
        enregistrer_texte();
    }

    if(imagesSeulement->isChecked() && !console_vrai)
    {
        rechercher_images();
    }

    if(textes_vrai && console_vrai)
    {
        enregistrer_texte();
    }

    if(images_vrai && console_vrai)
    {
        rechercher_images();
    }

    rechercher_texte_suplementaires();

    if(images_suplementaires->isChecked())
    {
        //rechercher_images_suplementaires();
    }

    reponse->deleteLater();


    termine = true;
    if(ok)
    {
        dialog->setValue(100);
        dialog->close();
    }

    motInternet->setReadOnly(false);
}

void FenInternet::enregistrer_texte()
{
    QString nomFichierDonnees;
    QString nomFichier;

    if(console_vrai)
    {
        nomFichierDonnees = QDir::homePath() + "/Analyst/" + "DataBase/" + mot_recherche_vrai + ".html";
        nomFichier = mot_recherche_vrai;
    }

    else if(!console_vrai)
    {
        nomFichierDonnees = QDir::homePath() + "/Analyst/" + "DataBase/" + motInternet->text() + ".html";
        nomFichier = motInternet->text();
    }

    //QString nomFichierDonnees = "DataBase/" + nomFichier;


    nomFichierDonnees.replace('_', ' ');

    const char* contenuFichierChar = contenuFichier.toStdString().c_str();

    if(contenuFichier.isEmpty())
    {
        QMessageBox::warning(this, tr("Attention"), tr("Analyst a détécté une erreur durant le téléchargement des données. Verifiez votre connexion internet puis rééssayez."));
        return;
    }

    QFile fichier(nomFichierDonnees);
    fichier.open(QIODevice::WriteOnly);
    fichier.write(contenuFichierChar);
    fichier.close();


    if(display_vrai)
    {
        FenFichierTexte *fenetreTexte = new FenFichierTexte(contenuFichier, nomFichier, this);
        fenetreTexte->show();
    }
}

void FenInternet::rechercher_images()
{
    nomFichier = "";

    int i = 0;

    while(i < contenuFichier.size() && ok)
    {
        ++i;

        if(contenuFichier.at(i) == 'h')
        {
            ++i;
            if(contenuFichier.at(i) == 't')
            {
                ++i;
                if(contenuFichier.at(i) == 't')
                {
                    ++i;
                    if(contenuFichier.at(i) == 'p')
                    {
                        ++i;
                        if(contenuFichier.at(i) == ':')
                        {
                            ++i;
                            if(contenuFichier.at(i) == '/')
                            {
                                ++i;
                                if(contenuFichier.at(i) == '/')
                                {
                                    ++i;
                                    nomFichier = "http://";
                                    while(contenuFichier.at(i) != '"')
                                    {
                                        nomFichier += contenuFichier.at(i);
                                        ++i;
                                    }

                                    if(nomFichier.startsWith("http://upload.wikimedia.org/wikipedia") && nomFichier.endsWith(".jpg", Qt::CaseInsensitive))
                                    {
                                        vraiNomFichier = nomFichier;

                                        if(imagesSeulement->isChecked())
                                        {
                                            const QUrl url = QUrl(nomFichier);
                                            const QNetworkRequest requete(url);
                                            QNetworkAccessManager *managerImage = new QNetworkAccessManager;
                                            QNetworkReply *reponseImage = managerImage->get(requete);

                                            connect(reponseImage, SIGNAL(finished()), this, SLOT(telechargementImageTermine()));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}



void FenInternet::rechercher_texte_suplementaires()
{
    nomFichier_additionel = "";

    dialog->setRange(0, (contenuFichier.size())/3);

    int i = 0;

    while(i < contenuFichier.size() && ok)
    {
        ++i;

        if(contenuFichier.at(i) == 'h')
        {
            ++i;
            if(contenuFichier.at(i) == 'r')
            {
                ++i;
                if(contenuFichier.at(i) == 'e')
                {
                    ++i;
                    if(contenuFichier.at(i) == 'f')
                    {
                        ++i;
                        if(contenuFichier.at(i) == '=')
                        {
                            ++i;
                            if(contenuFichier.at(i) == '"')
                            {
                                ++i;
                                if(contenuFichier.at(i) == '/')
                                {
                                    ++i;
                                    if(contenuFichier.at(i) == 'w')
                                    {
                                        ++i;
                                        if(contenuFichier.at(i) == 'i')
                                        {
                                            ++i;
                                            if(contenuFichier.at(i) == 'k')
                                            {
                                                ++i;
                                                if(contenuFichier.at(i) == 'i')
                                                {
                                                    ++i;
                                                    if(contenuFichier.at(i) == '/')
                                                    {

                                                        nomFichier_additionel = "href=/wiki";
                                                        while(contenuFichier.at(i) != '"')
                                                        {
                                                            nomFichier_additionel += contenuFichier.at(i);
                                                            ++i;
                                                        }

                                                        if(ok)
                                                        {
                                                            dialog->setValue(i);
                                                        }

                                                        if(nomFichier_additionel.startsWith("href=/wiki/") && !nomFichier_additionel.startsWith("href=/wiki/Wikipedia") && !nomFichier_additionel.startsWith("href=/wiki/Portal") && !nomFichier_additionel.startsWith("href=/wiki/Help") && !nomFichier_additionel.startsWith("href=/wiki/Special") && !nomFichier_additionel.startsWith("href=/wiki/Category") && !nomFichier_additionel.startsWith("href=/wiki/Book") && !nomFichier_additionel.startsWith("href=/wiki/Talk") && !nomFichier_additionel.contains("."))
                                                        {
                                                            if(!list_document_additionnels.contains(nomFichier_additionel))
                                                            {
                                                                list_document_additionnels << nomFichier_additionel;

                                                                vraiNomFichier_additionel = nomFichier_additionel;
                                                                nomFichier_additionel = nomFichier_additionel.remove(0,5);

                                                                QString nomSiteSuplementaire;
                                                                nomSiteSuplementaire = "http://en.wikipedia.org" + nomFichier_additionel;

                                                                QEventLoop loop;
                                                                QTimer::singleShot(1000, &loop, SLOT(quit()));
                                                                loop.exec();


                                                                const QUrl urlSuplementaire = QUrl(nomSiteSuplementaire);
                                                                const QNetworkRequest requeteSuplementaire(urlSuplementaire);
                                                                QNetworkAccessManager *managerSuplementaire = new QNetworkAccessManager;
                                                                QNetworkReply *reponseSuplementaire = managerSuplementaire->get(requeteSuplementaire);

                                                                connect(reponseSuplementaire, SIGNAL(finished()), this, SLOT(telechargementTermine_additionnel()));
                                                                //connect(reponse, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur_texte(QNetworkReply::NetworkError)));
                                                                //connect(reponse, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressionTelechargement(qint64, qint64) ));






                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(ok)
    {
        dialog->setValue((contenuFichier.size())/3);
    }
}


void FenInternet::rechercher_images_suplementaires(QString nomFichier_image_additionel)
{


    //foreach(QString nomFichier, list_document_additionnels)
    //{


        QFile fichier_additionel(nomFichier_image_additionel);

        if(fichier_additionel.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            contenuFichier_additionel = fichier_additionel.readAll();
        }

        int i = 0;

        while(i < contenuFichier_additionel.size() && ok)
        {
            ++i;

            if(contenuFichier_additionel.at(i) == 'h')
            {
                ++i;
                if(contenuFichier_additionel.at(i) == 't')
                {
                    ++i;
                    if(contenuFichier_additionel.at(i) == 't')
                    {
                        ++i;
                        if(contenuFichier_additionel.at(i) == 'p')
                        {
                            ++i;
                            if(contenuFichier_additionel.at(i) == ':')
                            {
                                ++i;
                                if(contenuFichier_additionel.at(i) == '/')
                                {
                                    ++i;
                                    if(contenuFichier_additionel.at(i) == '/')
                                    {
                                        ++i;
                                        QString addresse_nomFichier = "http://";
                                        while(contenuFichier_additionel.at(i) != '"')
                                        {
                                            addresse_nomFichier += contenuFichier_additionel.at(i);
                                            ++i;
                                        }

                                        if(addresse_nomFichier.startsWith("http://upload.wikimedia.org/wikipedia") && addresse_nomFichier.endsWith(".jpg", Qt::CaseInsensitive))
                                        {
                                            vraiNomFichier_image_additionel = addresse_nomFichier;


                                                /*QEventLoop loop;
    QTimer::singleShot(1000, &loop, SLOT(quit()));
    loop.exec();*/

                                                const QUrl url = QUrl(vraiNomFichier_image_additionel);
                                                const QNetworkRequest requete(url);
                                                QNetworkAccessManager *managerImage_suplementaire = new QNetworkAccessManager;
                                                QNetworkReply *reponseImage_suplementaire = managerImage_suplementaire->get(requete);

                                                connect(reponseImage_suplementaire, SIGNAL(finished()), this, SLOT(telechargementImageSuplementaireTermine()));

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    //}
}

void FenInternet::telechargementImageTermine()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QNetworkReply *reponseImage = qobject_cast<QNetworkReply*>(sender());

    QString nomImageFichier = vraiNomFichier.section("/",8,8);
    QString nomImageFichierDonnees = QDir::homePath() + "/Analyst/" + "DataBase/" + nomImageFichier;
    nomImageFichierDonnees.replace('_', ' ');

    QFile fichier(nomImageFichierDonnees);

    if(fichier.exists())
    {
        numeroImage++;
        QString numeroString;
        numeroString.setNum(numeroImage);
        nomImageFichierDonnees.insert(nomImageFichierDonnees.length() - 4, "-" + numeroString);
    }

    fichier.close();
    QFile nouveauFichier(nomImageFichierDonnees);

    nouveauFichier.open(QIODevice::WriteOnly);
    nouveauFichier.write(reponseImage->readAll());
    nouveauFichier.close();
    reponseImage->deleteLater();

    if(display_vrai)
    {
        FenFichierImage *fenetreImage = new FenFichierImage(nomImageFichierDonnees, this);
        fenetreImage->show();
    }
}

void FenInternet::telechargementTermine_additionnel()
{

    /*QEventLoop loop;
    QTimer::singleShot(1000, &loop, SLOT(quit()));
    loop.exec();*/

    QNetworkReply *reponseSuplementaire = qobject_cast<QNetworkReply*>(sender());
    QString contenu = reponseSuplementaire->readAll();

    QString nomDocument = "";

    int i = 0;

    while(i < contenu.size())
    {
        ++i;

        if(contenu.at(i) == '<')
        {
            ++i;
            if(contenu.at(i) == 't')
            {
                ++i;
                if(contenu.at(i) == 'i')
                {
                    ++i;
                    if(contenu.at(i) == 't')
                    {
                        ++i;
                        if(contenu.at(i) == 'l')
                        {
                            ++i;
                            if(contenu.at(i) == 'e')
                            {
                                ++i;
                                if(contenu.at(i) == '>')
                                {
                                    i++;
                                    while(contenu.at(i) != '-')
                                    {
                                        nomDocument += contenu.at(i);
                                        ++i;
                                    }

                                    nomDocument.remove(nomDocument.length()-1, nomDocument.length());
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    QString nomFichierDonnees = QDir::homePath() + "/Analyst/" + "DataBase/" + nomDocument + ".html";
    nomFichierDonnees.replace('_', ' ');

    const char* contenuFichierChar = contenu.toStdString().c_str();

    QFile fichier(nomFichierDonnees);
    fichier.open(QIODevice::WriteOnly);
    fichier.write(contenu.toStdString().c_str());
    fichier.close();
    reponseSuplementaire->deleteLater();

    if(afficher_texte_suplementaires->isChecked() && ok && group_suplementaire->isChecked() && !console_vrai)
    {
        FenFichierTexte *fenetreTexte = new FenFichierTexte(contenu, nomDocument, this);
        fenetreTexte->show();
    }

    if(images_suplementaires->isChecked() && ok && group_suplementaire->isChecked() && !console_vrai)
    {
        rechercher_images_suplementaires(nomFichierDonnees);
    }

    if(tout_texts_vrai && ok && console_vrai && display_vrai)
    {
        FenFichierTexte *fenetreTexte = new FenFichierTexte(contenu, nomDocument, this);
        fenetreTexte->show();
    }

    if(toute_images_vrai && ok && console_vrai)
    {
        rechercher_images_suplementaires(nomFichierDonnees);
    }
}

void FenInternet::telechargementImageSuplementaireTermine()
{
    QNetworkReply *reponseImage_suplementaire = qobject_cast<QNetworkReply*>(sender());

    //QString nomImageFichier = vraiNomFichier.section("/",8,8);
    //QString nomImageFichierDonnees = "DataBase/" + vraiNomFichier_image + ".jpg";

    QString nomImageFichierDonnees = QDir::homePath() + "/Analyst/" + "DataBase/" + vraiNomFichier_image_additionel.section('/', 8, 8);
    nomImageFichierDonnees.replace('_', ' ');

    QFile fichier(nomImageFichierDonnees);

    if(!fichier.exists())
    {
        numeroImageSuplementaire = 0;
    }

    else
    {
        numeroImageSuplementaire++;
        QString numeroString;
        numeroString.setNum(numeroImage);
        nomImageFichierDonnees.insert(nomImageFichierDonnees.length() - 4, "-" + numeroString);
    }


    QFile nouveauFichier(nomImageFichierDonnees);

    nouveauFichier.open(QIODevice::WriteOnly);
    nouveauFichier.write(reponseImage_suplementaire->readAll());
    nouveauFichier.close();
    reponseImage_suplementaire->deleteLater();

    if(afficher_images_suplementaires->isChecked() && ok && !console_vrai)
    {
        FenFichierImage *fenetreImage = new FenFichierImage(nomImageFichierDonnees, this);
        fenetreImage->show();
    }

    if(toute_images_vrai && ok && console_vrai && display_vrai)
    {
        FenFichierImage *fenetreImage = new FenFichierImage(nomImageFichierDonnees, this);
        fenetreImage->show();
    }
}

void FenInternet::arreter()
{
    ok = false;
    dialog->close();
}

void FenInternet::messageErreur(QNetworkReply::NetworkError)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard <br /><br /> Code de l'erreur : <br /><em>") + r->errorString() + "</em>");
    close();
}

void FenInternet::progressionTelechargement(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal != -1)
    {
        //dialog->setRange(0, 100);
        //dialog->setValue(100*bytesReceived/bytesTotal);
    }
}

void FenInternet::messageErreur_texte(QNetworkReply::NetworkError)
{
    erreur = true;
    dialog->close();
}

void FenInternet::lancer_recherche_internet()
{
    rechercheInternet();
}

void FenInternet::creerFenetre()
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    phraseInternet = new QLabel(tr("Mot à Rechercher sur Internet :"));
    motInternet = new QLineEdit;
    boutonInternet = new QPushButton();

    boutonInternet->setIcon(QIcon(":/icones/Fenetre Internet/web.png"));
    boutonInternet->setIconSize(QSize(64,64));

    texteSeulement = new QCheckBox(tr("Afficher le Texte"));
    imagesSeulement = new QCheckBox(tr("Afficher les Images              "));
    texteSeulement->setChecked(true);
    imagesSeulement->setChecked(true);

    images_suplementaires = new QCheckBox(tr("Télécharger les images suplémentaires"));
    images_suplementaires->setChecked(true);
    texte_suplementaires = new QCheckBox(tr("Télécharger les textes suplémentaires"));

    afficher_images_suplementaires = new QCheckBox(tr("Les afficher"));
    afficher_images_suplementaires->setChecked(true);
    afficher_texte_suplementaires = new QCheckBox(tr("Les afficher"));

    QHBoxLayout *layout_images_suplementaires = new QHBoxLayout;
    layout_images_suplementaires->addWidget(images_suplementaires);
    layout_images_suplementaires->addWidget(afficher_images_suplementaires);

    QHBoxLayout *layout_textes_suplementaires = new QHBoxLayout;
    layout_textes_suplementaires->addWidget(texte_suplementaires);
    layout_textes_suplementaires->addWidget(afficher_texte_suplementaires);

    QFormLayout *layout_suplementaire = new QFormLayout;
    layout_suplementaire->addRow(tr("Textes :"), layout_textes_suplementaires);
    layout_suplementaire->addRow(tr("Images :"), layout_images_suplementaires);

    group_suplementaire = new QGroupBox(tr("Rechercher des informations suplémentaires"));
    group_suplementaire->setCheckable(true);
    group_suplementaire->setChecked(false);
    group_suplementaire->setLayout(layout_suplementaire);

    QVBoxLayout *layoutMotInternet = new QVBoxLayout;
    layoutMotInternet->addWidget(phraseInternet);
    layoutMotInternet->addWidget(motInternet);

    QVBoxLayout *layoutOptionsInternet = new QVBoxLayout;
    layoutOptionsInternet->addWidget(texteSeulement);
    layoutOptionsInternet->addWidget(imagesSeulement);
    layoutOptionsInternet->addWidget(group_suplementaire);

    QHBoxLayout *layoutInternetBouton = new QHBoxLayout;
    layoutInternetBouton->addLayout(layoutOptionsInternet);
    layoutInternetBouton->addWidget(boutonInternet);

    QVBoxLayout *layoutInternet = new QVBoxLayout;
    layoutInternet->addLayout(layoutMotInternet);
    layoutInternet->addLayout(layoutInternetBouton);

    setLayout(layoutInternet);

    setWindowTitle(tr("Analyst - Recherche Internet"));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    #if defined(Q_WS_WIN)

    #endif

    #if defined(Q_WS_X11)

    #endif


    //setFixedSize(340,170);

    connect(boutonInternet, SIGNAL(clicked()), this, SLOT(lancer_recherche_internet()));
}

void FenInternet::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        rechercheInternet();
    }
}

void FenInternet::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
