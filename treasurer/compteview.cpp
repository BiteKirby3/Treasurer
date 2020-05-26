#include "compteview.h"
#include "ui_compteview.h"

CompteView::CompteView(QString typeCompte, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompteView)
{
    this->typeCompte = typeCompte;
    ui->setupUi(this);
}

CompteView::~CompteView()
{
    delete ui;
}

void CompteView::setTypeCompteLabel()
{
    QString copie = this->typeCompte;
    this->ui->typeCompteLabel->setText(copie.append("s").toUpper());
}

void CompteView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    this->close();
}

void CompteView::on_logout_button_clicked()
{
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}

void CompteView::creerArborescence()
{
    QStandardItemModel* model = new QStandardItemModel();
    QMap<int, QStandardItem*> items;
    QVector<QStandardItem*> itemsToPush;
    QVector<Compte> comptes = Compte::getComptes(this->typeCompte);

    foreach(Compte compte, comptes)
    {
        if (compte.isVirtuel())
        {
            if (compte.getIdParent())
            {
                QStandardItem* i = new QStandardItem(QIcon("../ressources/folder.svg"), compte.getNom());
                i->setData(QVariant::fromValue<Compte>(compte));
                items[compte.getId()] = i;
                items[compte.getIdParent()]->appendRow(i);
            }
            else
            {
                QStandardItem* i = new QStandardItem(QIcon("../ressources/folder.svg"), compte.getNom());
                i->setData(QVariant::fromValue<Compte>(compte));
                itemsToPush.push_back(i);
                items[compte.getId()] = i;
            }
        }
        else
        {
            if (compte.getIdParent())
            {
                QStandardItem* i = new QStandardItem(compte.getNom());
                i->setData(QVariant::fromValue<Compte>(compte));
                items[compte.getId()] = i;
                items[compte.getIdParent()]->appendRow(i);
            }
            else
            {
                QStandardItem* i = new QStandardItem(compte.getNom());
                i->setData(QVariant::fromValue<Compte>(compte));
                itemsToPush.push_back(i);
                items[compte.getId()] = i;
            }
        }
    };

    foreach (QStandardItem* item, itemsToPush)
    {
        model->appendRow(item);
    }

    ui->arborescence->setModel(model);
    ui->arborescence->expandAll();
}

void CompteView::setTransactions()
{
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("Référence"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Titre"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Date"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Débit"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Crédit"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Solde"));
    model->setHorizontalHeaderItem(6, new QStandardItem("Rapproché"));

    int count = 0;
    int solde = 0;

    QVector<Transaction> transactions = Transaction::getTransactionsDuCompte(this->compteActuel.getId());

    foreach (Transaction transaction, transactions)
    {
        QList<QStandardItem*> items;

        QStandardItem* i1 = new QStandardItem(transaction.getReference());
        items.push_back(i1);

        QStandardItem* i2 = new QStandardItem(transaction.getTitre());
        items.push_back(i2);

        QStandardItem* i3 = new QStandardItem(transaction.getDate().toString());
        items.push_back(i3);

        QStandardItem* i4 = new QStandardItem(QString::number(transaction.getDebit()));
        items.push_back(i4);

        QStandardItem* i5 = new QStandardItem(QString::number(transaction.getCredit()));
        items.push_back(i5);

        if (this->typeCompte == "actif" || this->typeCompte == "recette")
        {
            solde += transaction.getDebit();
            solde -= transaction.getCredit();
        }
        else {
            solde -= transaction.getDebit();
            solde += transaction.getCredit();
        }

        QStandardItem* i6 = new QStandardItem(QString::number(solde));
        items.push_back(i6);

        QString boolText = transaction.isRapproche() ? "Oui" : "Non";
        QStandardItem* i7 = new QStandardItem(boolText);
        items.push_back(i7);

        model->insertRow(count, items);
        count++;
    }



    ui->transactions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->transactions->setModel(model);
}

void CompteView::on_arborescence_clicked(const QModelIndex &index)
{
    this->compteActuel = index.data(Qt::UserRole +1).value<Compte>();

    if (!this->compteActuel.isVirtuel())
    {
        ui->compteLabel->setText(this->compteActuel.getNom());
        ui->DerniereModificationLabel->setText(this->compteActuel.getDerniereModification().toString());
        this->setTransactions();
    }
}

void CompteView::on_ajouter_compte_button_clicked()
{
    QString titre;
    if (this->typeCompte == "actif")
    {
        titre = "Ajouter un compte d'" + this->typeCompte;
    }
    else
    {
        titre = "Ajouter un compte de " + this->typeCompte;
    }

    AjouterCompteModal* ajouterCompteMododal = new AjouterCompteModal(this->typeCompte, this);
    ajouterCompteMododal->show();
    ajouterCompteMododal->setTitreModal(titre);
    ajouterCompteMododal->setComptesParents();
    ajouterCompteMododal->setComptesCapitauxPropres();
}
