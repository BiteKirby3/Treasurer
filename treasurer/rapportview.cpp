#include "rapportview.h"
#include "ui_rapportview.h"

RapportView::RapportView(QString typeRapport, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RapportView)
{
    this->typeRapport = typeRapport;
    ui->setupUi(this);
    setTypeRapportLabel(typeRapport);
    setDateLabel(QDateTime::currentDateTime().toString("dd/MM/yyyy"));
    setRapport();
}

RapportView::~RapportView()
{
    delete ui;
}

void RapportView::setTypeRapportLabel(QString typeRapport)
{
    ui->typeRapportLabel->setText(typeRapport);
}

void RapportView::setDateLabel(QString date){
    ui->dateLabel->setText("Date : " + QString("%1").arg(date));
}

QMap<int, double*> RapportView::calculSoldes(int id, QMap<int, QVector<int>> successors, QMap<int, double*> soldesComptes) {
    if (successors[id].empty())
        return soldesComptes;
    for (int i = 0; i < successors[id].size(); i++){
        if (id != idRacine)
            *(soldesComptes[id]) += *(calculSoldes(successors[id][i], successors, soldesComptes)[successors[id][i]]);
        else
            calculSoldes(successors[id][i], successors, soldesComptes);
    }
    return soldesComptes;
}

QMap<int, QVector<QString>> RapportView::ordreArborescence(QMap<int, QVector<QString>> result,
                                                           int id,
                                                           QMap<int, QVector<int>> successors,
                                                           QMap<int, QString> nomsComptes,
                                                           QMap<int, QString> soldesComptes,
                                                           int count = 0){
    if (successors[id].empty())
        return result;
    for (int i = 0; i < successors[id].size(); i++){
        QString tabulation = "";
        for (int j = 0; j < count; j++)
            tabulation += "\t";
        result[0].push_back(tabulation+nomsComptes[successors[id][i]]);
        result[1].push_back(QString("%1").arg(soldesComptes[successors[id][i]])+"€"+tabulation);
        result = ordreArborescence(result, successors[id][i], successors, nomsComptes, soldesComptes, count+1);
    }
    return result;
}

QMap<int, QVector<QString>> RapportView::creerArborescence(QString typeCompte, double* soldeTotal){
    QVector<Compte> comptes = Compte::getComptes(typeCompte);
    QMap<int, QVector<int>> successors;
    QMap<int, QString> nomsComptes;
    QMap<int, double> soldesComptes;
    QMap<int, double*> soldesComptesPt;
    QMap<int, QString> soldesComptesToQString;
    QVector<int> idComtpesRacines;

    for (int i = 0; i < comptes.size(); i++){
        if (!comptes[i].getIdParent())
            successors[idRacine].push_back(comptes[i].getId());
        else
            successors[comptes[i].getIdParent()].push_back(comptes[i].getId());
        if (comptes[i].isVirtuel())
            nomsComptes[comptes[i].getId()] = comptes[i].getNom() + "  [virtuel]";
        else
            nomsComptes[comptes[i].getId()] = comptes[i].getNom();
        soldesComptes[comptes[i].getId()] = comptes[i].getSolde();
    }

    foreach (int id, soldesComptes.keys()){
        soldesComptesPt[id] = &(soldesComptes[id]);
    }

    soldesComptesPt = calculSoldes(idRacine, successors, soldesComptesPt);

    for (int i = 0; i < successors[idRacine].size(); i++)
        *soldeTotal += *(soldesComptesPt[successors[idRacine][i]]);

    foreach (int id, soldesComptes.keys())
        soldesComptesToQString[id] = QString("%1").arg(*soldesComptesPt[id]);

    QMap<int, QVector<QString>> arborescence;
    arborescence = ordreArborescence(arborescence, idRacine, successors, nomsComptes, soldesComptesToQString, 0);
    return arborescence;
}

void RapportView::setRapport(){
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("Comtpes"));
    model->horizontalHeaderItem(0)->setFont(font);
    model->setHorizontalHeaderItem(1, new QStandardItem("Montants"));
    model->horizontalHeaderItem(1)->setFont(font);

    QString typeCompte1, total1, typeCompte2, total2, total;
    if (this->typeRapport == "Bilan"){
        typeCompte1 = "actif";
        total1 = "Total Actifs";
        typeCompte2 = "passif";
        total2 = "Total Passifs";
        total = "Actifs - Passifs";
    }
    else{
        typeCompte1 = "recette";
        total1 = "Total Recettes";
        typeCompte2 = "depense";
        total2 = "Total Dépenses";
    }

    QList<QStandardItem*> items;

    double s = 0;
    double* soldeTotal1 = &s;
    QMap<int, QVector<QString>> arborescence1 = creerArborescence(typeCompte1, soldeTotal1);
    for (int i = 0; i < arborescence1[0].size(); i++){
        QStandardItem* item1 = new QStandardItem(arborescence1[0][i]);
        QStandardItem* item2 = new QStandardItem(arborescence1[1][i]);
        item2->setTextAlignment(Qt::AlignRight);
        items << item1 << item2;
        model->appendRow(items);
        items.clear();
    }

    QStandardItem* itemTotal1 = new QStandardItem(total1);
    QStandardItem* itemSoldeTotal1 = new QStandardItem(QString("%1").arg(*soldeTotal1)+"€");
    itemTotal1->setForeground(QColor::fromRgb(0,0,255));
    itemSoldeTotal1->setForeground(QColor::fromRgb(0,0,255));
    itemSoldeTotal1->setTextAlignment(Qt::AlignRight);
    items << itemTotal1 << itemSoldeTotal1;
    model->appendRow(items);
    items.clear();

    double s2 = 0;
    double* soldeTotal2 = &s2;
    QMap<int, QVector<QString>> arborescence2 = creerArborescence(typeCompte2, soldeTotal2);
    for (int i = 0; i < arborescence2[0].size(); i++){
        QStandardItem* item1 = new QStandardItem(arborescence2[0][i]);
        QStandardItem* item2 = new QStandardItem(arborescence2[1][i]);
        item2->setTextAlignment(Qt::AlignRight);
        items << item1 << item2;
        model->appendRow(items);
        items.clear();
    }

    QStandardItem* itemTotal2 = new QStandardItem(total2);
    QStandardItem* itemSoldeTotal2 = new QStandardItem(QString("%1").arg(*soldeTotal2)+"€");
    itemTotal2->setForeground(QColor::fromRgb(0,0,255));
    itemSoldeTotal2->setForeground(QColor::fromRgb(0,0,255));
    itemSoldeTotal2->setTextAlignment(Qt::AlignRight);
    items << itemTotal2 << itemSoldeTotal2;
    model->appendRow(items);
    items.clear();

    double soldeTotal3 = *soldeTotal1 - *soldeTotal2;
    if (soldeTotal3 > 0)
        total = "Bénéfice";
    else
        total = "Perte";
    QStandardItem* itemTotal3 = new QStandardItem(total);
    QStandardItem* itemSoldeTotal3 = new QStandardItem(QString("%1").arg(soldeTotal3)+"€");
    itemTotal3->setForeground(QColor::fromRgb(0,0,255));
    itemSoldeTotal3->setForeground(QColor::fromRgb(0,0,255));
    itemSoldeTotal3->setTextAlignment(Qt::AlignRight);
    items << itemTotal3 << itemSoldeTotal3;
    model->appendRow(items);
    items.clear();

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setModel(model);
}

void RapportView::on_comptes_button_clicked()
{
    CompteController* compteController = CompteController::getInstance();
    compteController->showComptes();
    compteController->setSoldes();
    this->close();
}

void RapportView::on_rapports_button_clicked()
{
    RapportsView* rapports = new RapportsView;
    rapports->show();
    this->close();
}


void RapportView::on_logout_button_clicked()
{
CompteController::getInstance()->setViewLogout("rapportview");
    ConnexionView* connexion = new ConnexionView;
    connexion->show();
    this->close();
}



