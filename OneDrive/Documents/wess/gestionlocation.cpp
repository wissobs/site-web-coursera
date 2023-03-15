#include "gestionlocation.h"

gestionlocation::gestionlocation()
{
   idvehicule=0;
   typev="";
   idclient="";
   numberv=0;


}
gestionlocation::gestionlocation(int iv,QString t,QString ic,int n)
{

    idvehicule=iv;
    typev=t;
    idclient=ic;
    numberv=n;
}


QSqlQueryModel * gestionlocation ::Recherche(QString a)//cls=ASC ou DESC
{
QSqlQueryModel *model=new QSqlQueryModel();

model->setQuery("select * from GESTIONLOCATION WHERE IDVEHICULE LIKE '%"+a+"%' OR NUMBERV LIKE '%"+a+"%' OR TYPEV LIKE '%"+a+"%'" );
model->setHeaderData(0, Qt::Horizontal,QObject :: tr("IDVEHICULE"));
model->setHeaderData(1, Qt::Horizontal, QObject :: tr("NOMBREV"));
model->setHeaderData(2, Qt::Horizontal, QObject :: tr("TYPEV"));
model->setHeaderData(3, Qt::Horizontal, QObject :: tr("IDCLIENT"));





return model ;

}


bool gestionlocation::ajouter()
{

    QSqlQuery query;
    QString id_string =QString::number(idvehicule) ;
    QString id_string2 =QString::number(numberv) ;


    query.prepare("INSERT INTO gestionlocation(idvehicule,typev,idclient,numberv) " "   VALUES (:idvehicule, :typev, :idclient , :numberv)");
    query.bindValue(":idvehicule", id_string);
    query.bindValue(":typev", typev);
    query.bindValue(":idclinet", idclient);
    query.bindValue(":numberv", id_string2);




    return query.exec() ;


}
QSqlQueryModel * gestionlocation  :: afficher()
{
    QSqlQueryModel *  model = new QSqlQueryModel ()    ;
        model->setQuery("select * from gestionlocation ");
        model->setHeaderData(0, Qt::Horizontal,QObject :: tr("IDVEHICULE"));
        model->setHeaderData(1, Qt::Horizontal, QObject :: tr("NOMBREV"));
        model->setHeaderData(2, Qt::Horizontal, QObject :: tr("TYPEV"));
        model->setHeaderData(3, Qt::Horizontal, QObject :: tr("IDCLIENT"));



return model ;
}
bool gestionlocation :: modifier(int id)
{
     QSqlQuery query;

       // QString res= QString::number(identifiant);

        QString res= QString::number(id);
        query.prepare("UPDATE gestionlocation SET  idvehicule=:idvehicule,typev=:typev,idclient=:idclient ,numberv=:numberv   WHERE idvehicule=:idvehicule");
        query.bindValue(":idvehicule", idvehicule);
        query.bindValue(":typev", typev);
        query.bindValue(":idclient", idclient);
        query.bindValue(":numberv", numberv);



           return    query.exec();

}
bool gestionlocation :: supprimer(int)
{
    QSqlQuery query;

    query.prepare("Delete from gestionlocation  where idvehicule=:idvehicule ") ;
    query.bindValue(":idvehicule",idvehicule);


    query.exec();
    return query.exec() ;


}

