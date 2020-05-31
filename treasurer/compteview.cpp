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

Compte CompteView::getCompteActuel() {
    return this->compteActuel;
}

QString CompteView::getTypeCompte() {
    return this->typeCompte;
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

void CompteView::on_rapports_button_clicked()
{
    RapportsView* rapports=new RapportsView;
    rapports->show();
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
        i1->setData(QVariant::fromValue<Transaction>(transaction));
        items.push_back(i1);

        QStandardItem* i2 = new QStandardItem(transaction.getTitre());
        items.push_back(i2);

        QStandardItem* i3 = new QStandardItem(transaction.getDate().toString("dd/MM/yyyy"));
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
        i6->setEditable(false);
        items.push_back(i6);

        QString boolText = transaction.isRapproche() ? "Oui" : "Non";
        QStandardItem* i7 = new QStandardItem(boolText);
        i7->setEditable(false);
        items.push_back(i7);

        model->insertRow(count, items);
        count++;
    }


    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onItemChanged(QStandardItem*)));
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
        ui->rapprocher_button->setStyleSheet(" QPushButton{ background : #1556C7; color : #FFFFFF; font-weight: bold; border-radius: 5px; border: none; }");
        ui->rapprocher_button->setDisabled(false);
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

void CompteView::onItemChanged(QStandardItem* item)
{
    Transaction transaction = qobject_cast<QStandardItemModel *>(ui->transactions->model())->item(item->row())->data().value<Transaction>();

    switch (item->column()) {
        case 0:
            transaction.setReference(item->text());
        break;

        case 1:
            transaction.setTitre(item->text());
        break;

        case 2:
            transaction.setDate(QDate().fromString(item->text(), "dd/MM/yyyy"));
        break;

        case 3:
            transaction.setDebit(item->text().toDouble());
        break;

        case 4:
            transaction.setCredit(item->text().toDouble());
        break;
    }

    qobject_cast<QStandardItemModel *>(ui->transactions->model())->item(item->row())->setData(QVariant::fromValue<Transaction>(transaction));
    transactionsModifiees.insert(item->row());
}

QVector<Transaction> CompteView::getTransactionsModifiees()
{
    QVector<Transaction> transactions;

    foreach (int ligne, this->transactionsModifiees)
    {
        transactions.push_back(qobject_cast<QStandardItemModel *>(ui->transactions->model())->item(ligne)->data().value<Transaction>());
    }

    return transactions;
}

void CompteView::rapprocherCompteActuel() {
    this->compteActuel.setDateDernierRapprochement(QDate::currentDate());
    this->compteActuel.setSoldeDernierRapprochement(this->compteActuel.getSolde());
}

void CompteView::on_save_button_clicked()
{
    Transaction::editTransactions(this->getTransactionsModifiees(), this->compteActuel.getId());
    this->setTransactions();
    Compte::editDerniereModification(this->compteActuel.getId());
    this->compteActuel.setDerniereModification(QDate::currentDate());
    ui->DerniereModificationLabel->setText(this->compteActuel.getDerniereModification().toString());
}

void CompteView::on_rapprocher_button_clicked()
{
    RapprocherCompteModal* rapprocher = new RapprocherCompteModal(this);
    rapprocher->setLabels();
    rapprocher->show();
}
