#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gestionlocation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void wissoanimation();

private slots:



    void on_pushButton_8_clicked();


    void on_Tab_gestionlo_activated(const QModelIndex &index);

    void on_pushButton_19_clicked();

    void on_pushButton_21_clicked();


    void on_lineEdit_rech_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    gestionlocation g;
};
#endif // MAINWINDOW_H
