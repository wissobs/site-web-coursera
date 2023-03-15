#ifndef GESTIONLOCATION_H
#define GESTIONLOCATION_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include<QDateTime>

class gestionlocation
{ private :
    int idvehicule;
    QString typev;
    QString idclient;
  int numberv;

public:
    gestionlocation();
    gestionlocation(int iv,QString t,QString ic,int n);
    //getrs
    int get_idvehicule()
    {
        return idvehicule ;
    }
    QString get_typev()
    {
        return typev;
    }
    QString get_idclient()
    {
        return idclient ;
    }
    int get_numberv()
    {
        return numberv;
    }
    //setters
    void set_id(int  id)
    {
     idvehicule = id ;
    }
    void set_typev(QString X)
    {
      typev= X ;

    }
    void set_idclient(QString X)
    {
     idclient = X ;
    }
    void set_numberv(int a)
    {
     numberv= a ;
    }
    bool ajouter() ;
    QSqlQueryModel *  afficher()  ;
    bool  modifier(int id)  ;
    bool  supprimer(int)  ;
    QSqlQueryModel * Recherche(QString a)   ;//cls=ASC ou DESC

};

#endif // GESTIONLOCATION_H
