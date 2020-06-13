#include <QBrush>

#include "transactionview.h"
#include "ui_transactionview.h"


TransactionView::TransactionView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TransactionView)
{
    ui->setupUi(this);
    this->actualiser();
}

TransactionView::~TransactionView()
{
    delete ui;
}

void TransactionView::setMenuButtonColor(){
    this->ui->rapports_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->cloture_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->comptes_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->transaction_button->setStyleSheet("color:rgb(0,0,255)");
}

void TransactionView::actualiser(){
    this->setMenuButtonColor();
    this->afficherTransactions();
}

void TransactionView::afficherTransactions(){
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("Date"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Référence"));
    model->setHorizontalHeaderItem(2, new QStandardItem("Titre"));
    model->setHorizontalHeaderItem(3, new QStandardItem("Comptes"));
    model->setHorizontalHeaderItem(4, new QStandardItem("Débit"));
    model->setHorizontalHeaderItem(5, new QStandardItem("Crédit"));
    model->setHorizontalHeaderItem(6, new QStandardItem("Rapproché"));
    QVector<Transaction> transactions = Transaction::getTransactionParDate();
    int count=0;
    foreach (Transaction transaction, transactions)
    {
        QVector<Operation> operations=Operation::getOperationDeTran(transaction.getId());
        int cpt=1;
        QStandardItem* espace= new QStandardItem("");
        espace->setEditable(false);
        foreach(Operation operation,operations)
        {
            QList<QStandardItem*> items;
            if(cpt==1){
                QStandardItem* i1 = new QStandardItem(transaction.getDate().toString("dd/MM/yyyy"));
                items.push_back(i1);

                QStandardItem* i2 = new QStandardItem(transaction.getReference());
                i2->setData(QVariant::fromValue<Transaction>(transaction));
                items.push_back(i2);

                QStandardItem* i3 = new QStandardItem(transaction.getTitre());
                items.push_back(i3);

                QStandardItem* i4 = new QStandardItem(Compte::getNom(operation.getIdCompte()));
                items.push_back(i4);

                if(operation.getDebit()==0)
                {
                    items.push_back(espace);
                }
                else
                {
                    QStandardItem* i5= new QStandardItem(QString::number(operation.getDebit()));
                    items.push_back(i5);
                }

                if(operation.getCredit()==0)
                {
                    items.push_back(espace);
                }
                else
                {
                    QStandardItem* i6= new QStandardItem(QString::number(operation.getCredit()));
                    items.push_back(i6);
                }
                QString boolText = transaction.isRapproche() ? "Oui" : "Non";
                QStandardItem* i7 = new QStandardItem(boolText);
                items.push_back(i7);
                cpt++;
            }
            else{
                items.push_back(espace);
                items.push_back(espace);
                items.push_back(espace);
                QStandardItem* i4 = new QStandardItem(Compte::getNom(operation.getIdCompte()));
                items.push_back(i4);
                if(operation.getDebit()==0)
                {
                    items.push_back(espace);
                }
                else
                {
                    QStandardItem* i5= new QStandardItem(QString::number(operation.getDebit()));
                    items.push_back(i5);
                }

                if(operation.getCredit()==0)
                {
                    items.push_back(espace);
                }
                else
                {
                    QStandardItem* i6= new QStandardItem(QString::number(operation.getCredit()));
                    items.push_back(i6);
                }
                items.push_back(espace);
                cpt++;
            }
            model->insertRow(count, items);
            count++;
        }
        model->insertRow(count);
        count++;
    }
    ui->transactions->verticalHeader()->hide();
    ui->transactions->setModel(model);
}

void TransactionView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    this->close();
}

void TransactionView::on_rapports_button_clicked()
{
    RapportsView* rapports=new RapportsView;
    rapports->show();
    this->close();
}


void TransactionView::on_logout_button_clicked()
{
    CompteController::getInstance()->setViewLogout("transactionview");
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}



void TransactionView::on_ajouter_transaction_button_clicked()
{
    AjouterTransactionModal* ajouterTransactionMododal = new AjouterTransactionModal(this);
    ajouterTransactionMododal->show();
}

void TransactionView::on_save_button_clicked()
{

}

void TransactionView::on_cloture_button_clicked()
{
    this->ui->rapports_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->cloture_button->setStyleSheet("color:rgb(0,0,255)");
    this->ui->comptes_button->setStyleSheet("color:rgb(255,255,255)");
    this->ui->transaction_button->setStyleSheet("color:rgb(255,255,255)");
    ClotureModal* clo=new ClotureModal(this);
    clo->show();
}

