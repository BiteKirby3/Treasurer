#include "transactionview.h"
#include "ui_transactionview.h"

#include <QMessageBox>


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
    idTransactions.clear();
    nbOperationDeTransaction.clear();
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
        idTransactions.push_back(transaction.getId());
        QVector<Operation> operations=Operation::getOperationDeTran(transaction.getId());
        int cpt=1;
        QStandardItem* espace= new QStandardItem("");
        espace->setEditable(false);
        QStandardItem* espaceEditable= new QStandardItem("");
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
                    items.push_back(espaceEditable);
                }
                else
                {
                    QStandardItem* i5= new QStandardItem(QString::number(operation.getDebit()));
                    items.push_back(i5);
                }

                if(operation.getCredit()==0)
                {
                    items.push_back(espaceEditable);
                }
                else
                {
                    QStandardItem* i6= new QStandardItem(QString::number(operation.getCredit()));
                    items.push_back(i6);
                }
                QString boolText = transaction.isRapproche() ? "Oui" : "Non";
                QStandardItem* i7 = new QStandardItem(boolText);
                i7->setEditable(false);
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
                    items.push_back(espaceEditable);
                }
                else
                {
                    QStandardItem* i5= new QStandardItem(QString::number(operation.getDebit()));
                    items.push_back(i5);
                }

                if(operation.getCredit()==0)
                {
                    items.push_back(espaceEditable);
                }
                else
                {
                    QStandardItem* i6= new QStandardItem(QString::number(operation.getCredit()));
                    items.push_back(i6);
                }
                items.push_back(espace);
                cpt++;
            }
            if(transaction.isRapproche()){
                foreach(QStandardItem* ele, items)
                {
                    ele->setEditable(false);
                }
            }
            model->insertRow(count, items);
            count++;
        }
        this->nbOperationDeTransaction.push_back(cpt-1);
        model->insertRow(count);
        count++;
    }
    ui->transactions->verticalHeader()->hide();
    ui->transactions->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->transactions->setModel(model);
}

bool TransactionView::equilibre()
{
    int startrow=0;
    bool equilibre=true;
    foreach(int nb,this->nbOperationDeTransaction){
        double credits=0;
        double debits=0;
        for(int i=0;i<nb;i++){
         credits+=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,5)).toDouble();
         debits+=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,4)).toDouble();
        }
        startrow+=nb;
        startrow++;
        if(credits!=debits){
            equilibre=false;
        }
        if(!equilibre)
        {
            return false;
        }
    }
    return equilibre;
}

void TransactionView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    compteController->setSoldes();
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
    if(!this->equilibre()){
          QMessageBox::information(this, "Error", "La somme des débits doit être égale à la somme des crédits.");
    }
    else{
        int startrow=0;
        int idTran;
        QDate dateMod;
        QString reference;
        QString titre;
        bool rapproche;
        double debit;
        double credit;
        QString nomCompte;
        int cpt=0; //nb transaction traitee
        foreach(int nb,this->nbOperationDeTransaction){
            for(int i=0;i<nb;i++){
                idTran=this->idTransactions.at(cpt);
                nomCompte=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,3)).toString();
                credit=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,5)).toDouble();
                debit=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,4)).toDouble();
                if(i==0){
                    dateMod=QDate().fromString(ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,0)).toString(),"dd/MM/yyyy");
                    reference=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,1)).toString();
                    titre=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,2)).toString();
                    QString boolText=ui->transactions->model()->data(ui->transactions->model()->index(startrow+i,6)).toString();
                    if(boolText=="Oui")
                    {
                        rapproche=true;
                    }
                    else
                    {
                        rapproche=false;
                    }
                    //update la table transaction
                    Transaction::updateTransaction(idTran,dateMod,reference,titre,rapproche);

                    //update la table operation
                    if(credit-debit>0){
                        Operation::updateOperation(idTran,nomCompte,credit-debit,0);
                    }
                    else{
                        Operation::updateOperation(idTran,nomCompte,0,debit-credit);
                    }
                }
                else{
                    //update la table operation
                    if(credit-debit>0){
                        Operation::updateOperation(idTran,nomCompte,credit-debit,0);
                    }
                    else{
                        Operation::updateOperation(idTran,nomCompte,0,debit-credit);
                    }
                }
            }
            cpt++;
            startrow+=nb;
            startrow++;
        }
        //update le solde dans la table Compte
        QVector<Compte> csa=Compte::getComptes("actif");
        foreach(Compte c,csa)
        {
            c.updateSolde(c.calculerSolde());
        }
        QVector<Compte> csp=Compte::getComptes("passif");
        foreach(Compte c,csp)
        {
            c.updateSolde(c.calculerSolde());
        }
        QVector<Compte> csd=Compte::getComptes("depense");
        foreach(Compte c,csd)
        {
            c.updateSolde(c.calculerSolde());
        }
        QVector<Compte> csr=Compte::getComptes("recette");
        foreach(Compte c,csr)
        {
            c.updateSolde(c.calculerSolde());
        }
        this->actualiser();
    }
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

