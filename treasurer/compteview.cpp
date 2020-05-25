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

void CompteView::on_arborescence_clicked(const QModelIndex &index)
{
    Compte compte = index.data(Qt::UserRole +1).value<Compte>();

    if (!compte.isVirtuel())
    {
        ui->compteLabel->setText(compte.getNom());
        ui->DerniereModificationLabel->setText(compte.getDerniereModification().toString());
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
