#include <QMovie>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include"QMessageBox"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->Tab_gestionlo->setModel(g.afficher())    ;


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::wissoanimation( void )
{

    QMovie *movie = new QMovie ("Data Streams.gif");
    ui->label_5->setMovie(movie);
    movie->start();

}




void MainWindow::on_pushButton_8_clicked()
{
    QString idclient = ui->le_idc ->text();

    int idvehicule = ui->le_idv->text().toInt();

    QString typev= ui->le_type->text();

    int numberv = ui->le_nombre->text().toInt();

    gestionlocation  g (idvehicule,typev,idclient,numberv);

    bool test=g.ajouter();

    if (test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                              QObject::tr("Ajout effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->Tab_gestionlo->setModel(g.afficher())    ;

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                              QObject::tr("Ajout  non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }


}


void MainWindow::on_Tab_gestionlo_activated(const QModelIndex &index)
{



    QSqlQuery query;

    QString val=ui->Tab_gestionlo->model()->data(index).toString();
      query.prepare("Select * from GESTIONLOCATION where IDVEHICULE=:IDVEHICULE");

      query.bindValue(":IDVEHICULE",val);


      if(query.exec())
         {
             while(query.next())
             {

                 ui->le_idv->setText(query.value(0).toString());
                 ui->le_idc->setText(query.value(3).toString());
                 ui->le_type->setText(query.value(2).toString());
                 ui->le_nombre->setText(query.value(1).toString());


             }
         }
}

void MainWindow::on_pushButton_19_clicked()
{
    QString idloca = ui->le_idv->text();

    int idlocat = ui->le_idv->text().toInt();
    QString type= ui->le_type->text();
     int nbre = ui->le_nombre->text().toInt();
    QString idclient =  ui->le_idc->text();
     gestionlocation g(idlocat,type,idclient,nbre);
    bool test=g.modifier(idlocat);
    if(test)
    {

        ui->Tab_gestionlo->setModel(g.afficher());//refresh




              QMessageBox::information(nullptr, QObject::tr("effectué"),
                    QObject::tr(" Modifié.\n"
                      "Click Cancel to exit."), QMessageBox::Cancel);
               ui->le_idc->clear();
               ui->le_type->clear();
               ui->le_nombre->clear();
               ui->le_idv->clear();
               //ui->lineEdit_date->clear();

   }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("non effectué"),
                    QObject::tr("non modifié !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->le_idc->clear();
        ui->le_idv->clear();
        ui->le_type->clear();
        ui->le_nombre->clear();
        //ui->lineEdit_date->clear();

    }
    ui->Tab_gestionlo->setModel(g.afficher());//refresh
}

void MainWindow::on_pushButton_21_clicked()
{

    QString ids =ui->le_idv->text() ;
       // Client C1;
      // C1.set_id(ui->Id_supp->text().toInt())    ;

    int id=ui->le_idv->text().toInt()  ;
    gestionlocation G1;
    G1.set_id(id)    ;
      // if ( C1.chercherParCin () ==0 )

      // {
       bool test =G1.supprimer(id)    ;
       if(test)
       {
                ui->Tab_gestionlo->setModel(G1.afficher())    ;

                ui->le_idc->clear();
                ui->le_idv->clear();
                ui->le_type->clear();
                ui->le_nombre->clear();


           QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("Suppression effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
      ui->Tab_gestionlo->setModel(G1.afficher())    ;
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                QObject::tr("Suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


       }

}

void MainWindow::on_lineEdit_rech_textChanged(const QString &arg1)
{
    ui->Tab_gestionlo->setModel((g.Recherche(arg1)));
    if(ui->lineEdit_rech->text().isEmpty())
    {
        ui->Tab_gestionlo->setModel(g.afficher());
    }
}
