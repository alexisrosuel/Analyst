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

#include "../headers/FenBug.h"

FenBug::FenBug(QWidget *parent = 0) : QDialog (parent)
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    creerFenetre();
}

void FenBug::envoi()
{
    if(objet->text().isEmpty() || description->toPlainText().isEmpty())
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));
        return;
    }

    envoyer->setEnabled(false);
    const QUrl url = QUrl("http://analyst.site11.com/Bugs.php?objet=" + objet->text() + "&description=" + description->toPlainText());
    const QNetworkRequest requete(url);

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkReply *reponse = manager->get(requete);
    connect(reponse, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
    connect(reponse, SIGNAL(finished()), this, SLOT(fin()));
    connect(reponse, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(progressionEnvoi(qint64, qint64)));
}

void FenBug::fin()
{
	QMessageBox::information(this, tr("Analyst - Rapport de bug"), tr("Votre rapport à été envoyé. Merci de votre contribution."));
	close();
}

void FenBug::messageErreur(QNetworkReply::NetworkError)
{
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors du chargement. Vérifiez votre connexion internet ou réessayez plus tard <br /><br /> Code de l'erreur : <br /><em>") + r->errorString() + "</em>");
    close();
}

void FenBug::progressionEnvoi(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal != -1)
    {
        progression->setRange(0, bytesTotal);
        progression->setValue(bytesReceived);
    }
}

void FenBug::creerFenetre()
{
    #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif


    label_objet = new QLabel;
    label_objet->setText(tr("Objet :       "));


    objet = new QLineEdit;
    objet->setToolTip(tr("Entrez ici l'objet du bug"));

    label_description = new QLabel(this);
    label_description->setText(tr("Decription :"));


    description = new QTextEdit;
    description->setToolTip(tr("Entrez ici la description détaillée du probleme"));

    envoyer = new QPushButton(tr("Envoyer !"));

    annuler = new QPushButton(tr("Annuler"));

    progression = new QProgressBar;
    progression->setValue(0);

    QHBoxLayout *layout_objet = new QHBoxLayout;
    layout_objet->addWidget(label_objet);
    layout_objet->addWidget(objet);

    QHBoxLayout *layout_description = new QHBoxLayout;
    layout_description->addWidget(label_description);
    layout_description->addWidget(description);

    QHBoxLayout *layout_bouton = new QHBoxLayout;
    layout_bouton->addWidget(annuler);
    layout_bouton->addWidget(envoyer);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout_objet);
    layout->addLayout(layout_description);
    layout->addLayout(layout_bouton);
    layout->addWidget(progression);

    //layoutCentral->addWidget(aireCentrale);
    setLayout(layout);

    setWindowTitle(tr("Analyst - Rapporter un bug"));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    connect(envoyer, SIGNAL(clicked()), this, SLOT(envoi()));
    connect(annuler, SIGNAL(clicked()), this, SLOT(deleteLater()));


    #if defined(Q_WS_WIN)
        setFixedSize(600,500);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(600,500);
    #endif
}
