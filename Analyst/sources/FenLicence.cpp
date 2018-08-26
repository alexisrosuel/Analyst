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

#include "../headers/FenLicence.h"

FenLicence::FenLicence(QWidget *parent = 0) : QDialog (parent)
{
     #if defined (linux)
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    #endif

    boolProducteurs = false;
    boolLicence = false;
    boolAPropos = true;

    producteurs = new QPushButton(tr("Développeurs ->"));
    licence = new QPushButton(tr("Licence"));

    QString addresse = "http://www.analyst-free.110mb.com/";

    texte = new QLabel("<center>"
					"<p>"
						"<img src=':/icones/Icones/Analyst-64.png'/>"
					"</p>"
					"<h1>Analyst 1.3</h1>"
					"<p>"
						"Analyst is a software which can do research in Database, or on the Internet.<br />"
						"It is a powerful tool because you can easily manage your database,<br />"
						"add or remove files, get informations, and sort results."
					"</p>"
					"<p>"
						"Copyright © 2010-2011 Alexis ROSUEL"
					"</p>"
					"<p>"
						"<a href='" + addresse + "'>" + addresse + "</a>"
					"</p>"
				"</center>");

    texte->setOpenExternalLinks(true);

    QVBoxLayout *layoutV = new QVBoxLayout;
    layoutV->addWidget(texte);

    QHBoxLayout *layoutH = new QHBoxLayout;
    layoutH->addWidget(producteurs, Qt::AlignRight);
    layoutH->addWidget(licence, Qt::AlignRight);

    layout = new QVBoxLayout;
    layout->addLayout(layoutV);
    layout->addLayout(layoutH);

    setLayout(layout);

    setFixedSize(510,500);
    setWindowTitle(tr("Analyst - A Propos..."));
    setWindowIcon(QIcon(":/icones/Icones/Analyst.png"));

    connect(producteurs, SIGNAL(clicked()), this, SLOT(choisir()));
    connect(licence, SIGNAL(clicked()), this, SLOT(fonctionLicence()));
}

void FenLicence::choisir()
{
    if(!boolProducteurs)
    {
        fonctionProducteurs();
    }

    else
    {
        fonctionAPropos();
    }
}
void FenLicence::fonctionProducteurs()
{
    if(boolLicence)
    {
        texte2->deleteLater();
        boolLicence = false;
    }

    else if(boolAPropos)
    {
        texte->deleteLater();
        boolAPropos = false;
    }

    boolProducteurs = true;

    licence->setEnabled(true);

    QStandardItemModel *modele = new QStandardItemModel;

    item = new QStandardItem("Rosuel Alexis (Alexiron)");
    modele->appendRow(item);
    item->appendRow(new QStandardItem(tr("Chef de projet")));
    item->setEditable(false);

    item = new QStandardItem("Xavier (Xavi91)");
    modele->appendRow(item);
    item->appendRow(new QStandardItem(tr("Graphiste")));
    item->setEditable(false);

    item = new QStandardItem("Maxence Rosuel (Spont)");
    modele->appendRow(item);
    item->appendRow(new QStandardItem(tr("Bande son")));
    item->setEditable(false);

    item = new QStandardItem("Zakatchi");
    modele->appendRow(item);
    item->appendRow(new QStandardItem(tr("Traducteur")));
    item->setEditable(false);

    item = new QStandardItem("Alessandro Rei (www.mentalrey.it)");
    modele->appendRow(item);
    item->appendRow(new QStandardItem(tr("Icônes \"Dark Glass\"")));
    item->setEditable(false);

    item = new QStandardItem("Everaldo COELHO (www.everaldo.com)");
    modele->appendRow(item);
    item->appendRow(new QStandardItem(tr("Icônes \"Crystal\"")));
    item->setEditable(false);

    vue = new QTreeView;
    vue->setModel(modele);
    vue->header()->hide();

    layout->insertWidget(1, vue);

    producteurs->setText(tr("<- A propos..."));

    setFixedSize(480,260);
    setWindowTitle(tr("Analyst - Développeurs"));
}

void FenLicence::fonctionLicence()
{
    boolLicence = true;

    if(boolProducteurs)
    {
        vue->deleteLater();
        boolProducteurs = false;
    }

    else if(boolAPropos)
    {
        texte->deleteLater();
        boolAPropos = false;
    }

    licence->setEnabled(false);

    texte2 = new QLabel;

    texte2->setText("Copyright © 2010-2011 Alexis Rosuel\n"
				"\n"
				"Analyst is free software: you can redistribute it and/or modify\n"
				"it under the terms of the GNU General Public License as published by\n"
				"the Free Software Foundation, either version 3 of the License, or\n"
				"(at your option) any later version.\n"
				"\n"
				"Analyst is distributed in the hope that it will be useful,\n"
				"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
				"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
				"GNU General Public License for more details.\n"
				"\n"
				"You should have received a copy of the GNU General Public License\n"
				"along with Analyst.  If not, see <http://www.gnu.org/licenses/>");
    //licence->setText("A propos...");

    layout->insertWidget(1, texte2);

    setFixedSize(480,260);
    setWindowTitle(tr("Analyst - Licence"));
}

void FenLicence::fonctionAPropos()
{
    if(boolLicence)
    {
        texte2->deleteLater();
        boolLicence = false;
    }

    else if(boolProducteurs)
    {
        vue->deleteLater();
        boolProducteurs = false;
    }

    boolAPropos = true;

    QString addresse = "http://www.analyst-free.110mb.com/";

    licence->setEnabled(true);

    texte = new QLabel("<center>"
					"<p>"
						"<img src=':/icones/Icones/Analyst-64.png'/>"
					"</p>"
					"<h1>Analyst 1.3</h1>"
					"<p>"
						"Analyst is a software which can do research in Database, or on the Internet.<br />"
						"It is a powerful tool because you can easily manage your Database,<br />"
						"add or remove files, get informations, and sort results."
					"</p>"
					"<p>"
						"Copyright © 2010-2011 Alexis ROSUEL"
					"</p>"
					"<p>"
						"<a href='" + addresse + "'>" + addresse + "</a>"
					"</p>"
				"</center>");

    layout->insertWidget(1, texte);
    producteurs->setText(tr("Développeurs ->"));

    setWindowTitle(tr("Analyst - A Propos..."));

    #if defined(Q_WS_WIN)
        setFixedSize(510,500);
    #endif

    #if defined(Q_WS_X11)
        setFixedSize(510,500);
    #endif
}

void FenLicence::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return)
    {
        this->deleteLater();
    }
}

void FenLicence::closeEvent(QCloseEvent*)
{
    this->deleteLater();
}
