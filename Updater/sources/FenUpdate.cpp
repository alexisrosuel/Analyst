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

#include "../headers/FenUpdate.h"

FenUpdate::FenUpdate()
{
    label = new QLabel(this);
    QPixmap pixmap(":/icones/Analyst.png");

    label->setPixmap(pixmap);
    label->resize(pixmap.size());

    label_texte = new QLabel(this);

    label_vitesse = new QLabel(this);

    label_nombre = new QLabel(this);
    label_nombre->setAlignment(Qt::AlignRight);

    bar = new QProgressBar(this);
    bar->setValue(0);

    QHBoxLayout *layout_nombres = new QHBoxLayout;
    //layout_nombres->addWidget(label_vitesse, Qt::AlignLeft);
    layout_nombres->addWidget(label_nombre, Qt::AlignLeft);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout_nombres, Qt::AlignRight);
    layout->addWidget(label);
    layout->addWidget(label_texte);
    layout->addWidget(bar);

    setLayout(layout);
    setWindowTitle("Analyst - Updater");
    setWindowIcon(QIcon(":/icones/Analyst.png"));

    verif_version();
}

void FenUpdate::verif_version()
{
    label_texte->setText(tr("Vérification de votre version actuelle..."));

    QSettings settings(QString(QDir::homePath() + "/Analyst/" + "update.ini"), QSettings::IniFormat);
    version_actuel = settings.value("version").toString();

    label_texte->setText(tr("Vérification de votre version actuelle... (") + version_actuel + ")");

    settings.deleteLater();

    QString string_fichier_version;
    string_fichier_version = "http://master.dl.sourceforge.net/project/analyst/Update/update.ini";

    erreur = false;

    const QUrl url_fichier = QUrl(string_fichier_version);
    const QNetworkRequest requete_fichier(url_fichier);
    QNetworkAccessManager *manager_fichier = new QNetworkAccessManager;
    QNetworkReply *reponse_fichier = manager_fichier->get(requete_fichier);

    connect(reponse_fichier, SIGNAL(finished()), this, SLOT(telechargement_fichier_termine()));
    connect(reponse_fichier, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(message_erreur(QNetworkReply::NetworkError)));
    connect(reponse_fichier, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progression_telechargement(qint64, qint64)));
}

void FenUpdate::progression_telechargement(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal != -1)
    {
        label_nombre->setText(QString::number(bytesReceived) + "/" + QString::number(bytesTotal) + " octets");
        //label_vitesse->setText(QString::number((bytesReceived - precedent) / timer->elapsed()));

        bar->setRange(0, bytesTotal);
        bar->setValue(bytesReceived);

        //precedent = bytesReceived;
    }
}

void FenUpdate::message_erreur(QNetworkReply::NetworkError)
{
    QNetworkReply *reponse_fichier = qobject_cast<QNetworkReply*>(sender());

    if(reponse_fichier->error() == QNetworkReply::NoError)
    {
        int v= reponse_fichier->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (v >= 300 && v < 400)
        {
            QUrl newUrl = reponse_fichier->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
            newUrl = reponse_fichier->url().resolved(newUrl);

            QNetworkRequest redirection(newUrl);
            QNetworkAccessManager *new_manager = new QNetworkAccessManager;
            QNetworkReply *newReply = new_manager->get(redirection);
            connect(newReply, SIGNAL(finished()), this, SLOT(telechargement_fichier_termine()));

        }
    }

    QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard <br /><br /> Code de l'erreur : <br /><em>") + reponse_fichier->errorString() + "</em>");
    erreur = true;
    qApp->quit();
    return;
}

void FenUpdate::telechargement_fichier_termine()
{
    label_texte->setText(tr("Lecture des informations du serveur..."));

    QNetworkReply *reponse_fichier = qobject_cast<QNetworkReply*>(sender());
    version_fichier = reponse_fichier->readAll();

    version_fichier.remove(version_fichier.length()-1, version_fichier.length());

    if(erreur || !version_fichier.at(0).isNumber())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard."));
        qApp->quit();
        return;
    }

    else
    {
        if(version_fichier.startsWith(version_actuel) and version_fichier.endsWith(version_actuel))
        {
             a_jour_ok();
        }

        else
        {
            telecharger_md5();
        }
    }

    reponse_fichier->deleteLater();
}

void FenUpdate::a_jour_ok()
{
    QMessageBox::information(this, "Analyst - Updater", tr("Votre version de Analyst est à jour."));
    qApp->quit();
}

void FenUpdate::telecharger_md5()
{
    label_texte->setText(tr("Une nouvelle version est disponible..."));

    QString string_md5;

    #if defined(Q_WS_WIN)
        string_md5 = "http://master.dl.sourceforge.net/project/analyst/Update/md5_windows.ini";
    #endif

    #if defined(Q_WS_X11)
        string_md5 = "http://master.dl.sourceforge.net/project/analyst/Update/md5_linux.ini";
    #endif

    const QUrl url_md5 = QUrl(string_md5);
    const QNetworkRequest requete_md5(url_md5);
    QNetworkAccessManager *manager_md5 = new QNetworkAccessManager;
    QNetworkReply *reponse_md5 = manager_md5->get(requete_md5);

    connect(reponse_md5, SIGNAL(finished()), this, SLOT(telechargement_md5_termine()));
    connect(reponse_md5, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(message_erreur(QNetworkReply::NetworkError)));
    connect(reponse_md5, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progression_telechargement(qint64, qint64)));
}

void FenUpdate::telechargement_md5_termine()
{
    QNetworkReply *reponse_md5 = qobject_cast<QNetworkReply*>(sender());
    nouveau_md5 = reponse_md5->readAll();
    nouveau_md5.remove(nouveau_md5.length()-1, 1);
    reponse_md5->deleteLater();

    telecharger_nouveau();
}

void FenUpdate::telecharger_nouveau()
{
    label_texte->setText(tr("Une nouvelle version est disponible..."));

    QString string_nouveau;

    #if defined(Q_WS_WIN)
        string_nouveau = "http://master.dl.sourceforge.net/project/analyst/Update/windows.ini";
    #endif

    #if defined(Q_WS_X11)
        string_nouveau = "http://master.dl.sourceforge.net/project/analyst/Update/linux.ini";
    #endif

    const QUrl url_nouveau = QUrl(string_nouveau);
    const QNetworkRequest requete_nouveau(url_nouveau);
    QNetworkAccessManager *manager_nouveau = new QNetworkAccessManager;
    QNetworkReply *reponse_nouveau = manager_nouveau->get(requete_nouveau);

    connect(reponse_nouveau, SIGNAL(finished()), this, SLOT(telechargement_nouvelle_version_termine()));
    connect(reponse_nouveau, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(message_erreur(QNetworkReply::NetworkError)));
    connect(reponse_nouveau, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progression_telechargement(qint64, qint64)));
}

void FenUpdate::telechargement_nouvelle_version_termine()
{
    QNetworkReply *reponse_nouveau = qobject_cast<QNetworkReply*>(sender());
    QString nouvelle_version;
    nouvelle_version = reponse_nouveau->readAll();
    reponse_nouveau->deleteLater();

    const QUrl url_nouveau_analyst = QUrl(nouvelle_version);
    const QNetworkRequest requete_nouveau_analyst(url_nouveau_analyst);
    QNetworkAccessManager *manager_nouveau_analyst = new QNetworkAccessManager;
    QNetworkReply *reponse_nouveau_analyst = manager_nouveau_analyst->get(requete_nouveau_analyst);

    label_texte->setText(tr("Téléchargement de Analyst en cours..."));

    connect(reponse_nouveau_analyst, SIGNAL(finished()), this, SLOT(telechargement_nouvelle_version_analyst_termine()));
    connect(reponse_nouveau_analyst, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(message_erreur(QNetworkReply::NetworkError)));
    connect(reponse_nouveau_analyst, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progression_telechargement(qint64, qint64)));
}

void FenUpdate::telechargement_nouvelle_version_analyst_termine()
{
    QNetworkReply *reponse_nouveau_analyst = qobject_cast<QNetworkReply*>(sender());

    QByteArray nouvelle_version = reponse_nouveau_analyst->readAll();

    QFile fichier_tmp_ecrire("Analyst-tmp");

    if (fichier_tmp_ecrire.open(QIODevice::WriteOnly))
    {
        fichier_tmp_ecrire.write(nouvelle_version);
        fichier_tmp_ecrire.close();
        fichier_tmp_ecrire.deleteLater();
    }

    QFile fichier_tmp_lire("Analyst-tmp");
    QByteArray byteArray;
    QString texte;
    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Md5);

    if (fichier_tmp_lire.open(QIODevice::ReadOnly))
    {
        while (!fichier_tmp_lire.atEnd())
        {
            byteArray = fichier_tmp_lire.read(1024);

            hash->addData(byteArray);
        }
    }

    if(hash->result().toHex() != nouveau_md5)
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors du chargement, le fichier est corrompu. Vérifiez votre connexion internet ou réessayez plus tard."));
        fichier_tmp_lire.remove();
        fichier_tmp_lire.close();
        qApp->quit();
        return;
    }

    label_texte->setText(tr("Enregistrement de la derniere version..."));

    QFile ancien_analyst("Analyst");
    ancien_analyst.remove();
    ancien_analyst.close();
    ancien_analyst.deleteLater();

    QFile tmp("Analyst-tmp");
    tmp.remove();
    tmp.close();
    tmp.deleteLater();

    #if defined(Q_WS_WIN)
        QFile file("Analyst.exe");
        file.open(QIODevice::WriteOnly);
        file.write(nouvelle_version);
        file.close();
    #endif

    #if defined(Q_WS_X11)
        QFile file("Analyst");
        file.open(QIODevice::WriteOnly);
        file.write(nouvelle_version);
        file.close();
    #endif

    reponse_nouveau_analyst->deleteLater();

    operation_fichier();

    QMessageBox::information(this, "Analyst - Updater", tr("Analyst a été mis a jour."));
    qApp->quit();
}

void FenUpdate::operation_fichier()
{
    QSettings settings(QString(QDir::homePath() + "/Analyst/" + "update.ini"), QSettings::IniFormat);
    settings.setValue("version", version_fichier);
    settings.deleteLater();

    QSettings settings_premier(QString(QDir::homePath() + "/Analyst/" + "analyst.ini"), QSettings::IniFormat);
    settings_premier.setValue("premier", "1");
    settings_premier.deleteLater();

    #if defined(Q_WS_X11)
        system("chmod 731 Analyst");
    #endif
}

