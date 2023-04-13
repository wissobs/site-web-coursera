#include <QMovie>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLabel>
#include"QMessageBox"
#include <QPdfWriter>
#include <QtGui/QDesktopServices>
#include <QUrl>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlQuery>
#include <QPrinter>
#include <QPrintDialog>
#include <QtSvg/QSvgRenderer>
#include <QFileDialog>
#include <fstream>
#include "QrCode.hpp"
#include <QAxObject>
#include <QObject>
#include <QDesktopServices>
//#include "qrcodelabel.h"
#include"QrCode.hpp"
#include "stat_categorie.h"


#include <QPainter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include<QString>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QTcpSocket>
//#include <QQuickItem>
#include <QSystemTrayIcon>
#include <QIntValidator>
#include <QDebug>




using qrcodegen::QrCode;
using qrcodegen::QrSegment;


using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->Tab_gestionlo->setModel(g.afficher());
            ui->le_idv->setValidator(new QRegExpValidator(QRegExp("[1-9]+"), parent));
            ui->le_type->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), parent));
            ui->le_nombre->setValidator(new QRegExpValidator(QRegExp("[1-9]+"), parent));

            QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                               QCoreApplication::organizationName(), QCoreApplication::applicationName());


              ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/A%C3%A9roport+de+Tunis-Carthage/@36.8475605,10.2149852,17z/data=!3m1!4b1!4m5!3m4!1s0x12e2cad2e1d7f1bb:0x902488d100b5819b!8m2!3d36.8475562!4d10.2175601");





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
    QString matreculev = ui->le_matrecule->text();

    gestionlocation  g (idvehicule,typev,idclient,numberv,matreculev);

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
      query.prepare("Select * from GESTIONCLIENT where IDCLIENT=:IDCLIENT");


      query.bindValue(":IDVEHICULE",val);


      if(query.exec())
         {
             while(query.next())
             {

                 ui->le_idv->setText(query.value(0).toString());
                 ui->le_idc->setText(query.value(3).toString());
                 ui->le_type->setText(query.value(2).toString());
                 ui->le_nombre->setText(query.value(1).toString());
                 ui->le_matrecule->setText(query.value(4).toString());


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
    QString matv= ui->le_matrecule->text();
     gestionlocation g(idlocat,type,idclient,nbre,matv);
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
        ui->le_matrecule->clear();
        //ui->lineEdit_date->clear();

    }
    ui->Tab_gestionlo->setModel(g.afficher());//refresh
}

void MainWindow::on_pushButton_21_clicked()
{

    QString ids =ui->le_idv->text() ;




    int id=ui->le_idv->text().toInt()  ;
    gestionlocation G1;
    G1.set_id(id)    ;


       bool test =G1.supprimer(id)    ;
       if(test)
       {
                ui->Tab_gestionlo->setModel(G1.afficher())    ;

                ui->le_idc->clear();
                ui->le_idv->clear();
                ui->le_type->clear();
                ui->le_nombre->clear();
                ui->le_matrecule->clear();


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



void MainWindow::on_pushButton_48_clicked()
{
     QString type = ui->comboBox->currentText();
     qDebug() << type;
     QString critere ="select * from gestionlocation ORDER BY "+type;
     ui->Tab_gestionlo->setModel(g.Trier(critere));
}

void MainWindow::on_pushButton_22_clicked()
{
    QPdfWriter pdf(qApp->applicationDirPath()+"//listedeslocations.pdf");

       QPainter painter(&pdf);

                        int i = 4000;


                        painter.drawText(4500,1500,"LISTE DES vehicules ");
                        painter.setPen(Qt::blue);
                        painter.setFont(QFont("Arial", 50));
                        painter.drawRect(2000,200,6300,2600);
                        painter.setPen(Qt::black);


                        QSqlQuery query;
                        query.prepare("select * from gestionlocation");
                        query.exec();
                        while (query.next())

                        {
                            painter.setPen(Qt::red);
                            painter.setPen(Qt::black);
                            painter.setFont(QFont("Arial", 9));
                            painter.drawRect(-50,1000+i,3600,2500);
                            painter.drawText(0,1300+i,"IDVEHICULE");
                            painter.drawText(0,1600+i,"NOMBREV");
                            painter.drawText(0,1900+i,"TYPEV");
                            painter.drawText(0,2200+i,"IDCLIENT");
                            painter.drawText(0,2500+i,"MATRECULEV");



                            painter.drawText(1600,1300+i,query.value(0).toString());
                            painter.drawText(1600,1600+i,query.value(1).toString());
                            painter.drawText(1600,1900+i,query.value(2).toString());
                            painter.drawText(1600,2200+i,query.value(3).toString());
                            painter.drawText(1600,2500+i,query.value(4).toString());

                            i = i +3000;
                        }

                        int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                        if (reponse == QMessageBox::Yes)
                        {
                            QDesktopServices::openUrl(QUrl::fromLocalFile(qApp->applicationDirPath()+"//listedeslocations.pdf"));

                            painter.end();
                        }
                        if (reponse == QMessageBox::No)
                        {
                            painter.end();
                        }
}



void MainWindow::on_qrcodegen_2_clicked()
{
    using namespace qrcodegen;


                QTableView Tab_gestionlo;
                QSqlQueryModel * Mod=new  QSqlQueryModel();
                QString value=ui->lineEdit_qrcode_2->text();


                     QSqlQuery qry;




                     qry.prepare("select * from GESTIONLOCATION where IDVEHICULE='"+value+"'");
                     qry.exec();
                     Mod->setQuery(qry);
                     Tab_gestionlo.setModel(Mod);




                    QString idvehicule = Tab_gestionlo.model()->data(Tab_gestionlo.model()->index(0, 0)).toString().simplified();
                    QString idclient= Tab_gestionlo.model()->data(Tab_gestionlo.model()->index(0, 2)).toString().simplified();
                    QString typev = Tab_gestionlo.model()->data(Tab_gestionlo.model()->index(0, 1)).toString().simplified();
                    QString matreculev = Tab_gestionlo.model()->data(Tab_gestionlo.model()->index(0, 4)).toString().simplified();
                    QString numberv = Tab_gestionlo.model()->data(Tab_gestionlo.model()->index(0, 3)).toString().simplified();




                QString text = idvehicule+"\n"+typev+"\n"+idclient+"\n"+numberv+"\n"+matreculev+"\n";
                  // Create the QR Code object
                  QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

                  qint32 sz = qr.getSize();
                  QImage im(sz,sz, QImage::Format_RGB32);
                    QRgb black = qRgb( 191,112,105 );
                    QRgb white = qRgb(255,255,255);
                  for (int y = 0; y < sz; y++)
                    for (int x = 0; x < sz; x++)
                      im.setPixel(x,y,qr.getModule(x, y) ? black : white );//setpixelmap tafichilek qr code
                  ui->qrcodecommande_2->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}

void MainWindow::on_pushButton_26_clicked()
{
    s = new stat_categorie();
     s->choix_pie();
     s->show();

}
