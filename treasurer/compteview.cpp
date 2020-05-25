#include "compteview.h"
#include "ui_compteview.h"

CompteView::CompteView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CompteView)
{
    ui->setupUi(this);
}

CompteView::~CompteView()
{
    delete ui;
}

void CompteView::setTypeCompteLabel(QString typeCompte)
{
    this->ui->typeCompteLabel->setText(typeCompte);
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

void CompteView::selectPremierCompte(QString typeCompte)
{
    Compte compte = Compte::getPremierCompte(typeCompte);
    ui->compteLabel->setText(compte.getNom());
    ui->DerniereModificationLabel->setText(compte.getDerniereModification().toString());
}

void CompteView::creerArborescence(QString typeCompte)
{
    QStandardItemModel* model = new QStandardItemModel();
    QMap<int, QStandardItem*> items;
    QVector<QStandardItem*> itemsToPush;
    QVector<Compte> comptes = Compte::getComptes(typeCompte);

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
    AjouterCompteModal* ajouterCompteMododal = new AjouterCompteModal;
    ajouterCompteMododal->show();
    QString typeCompte = ui->typeCompteLabel->text().toLower();
    typeCompte.chop(1);
    QString titre;
    if (typeCompte == "actif")
    {
        titre = "Ajouter un compte d'" + typeCompte;
    }
    else
    {
        titre = "Ajouter un compte de " + typeCompte;
    }
    ajouterCompteMododal->setTitreModal(titre);
}
