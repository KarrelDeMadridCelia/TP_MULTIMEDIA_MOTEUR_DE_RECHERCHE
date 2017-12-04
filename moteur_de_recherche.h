#ifndef MOTEUR_DE_RECHERCHE_H
#define MOTEUR_DE_RECHERCHE_H
#include <QWidget>
#include <QFileDialog>
#include <QImage>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMessageBox>

#include <QMainWindow>

namespace Ui {
class Moteur_De_Recherche;
}

using namespace std;

class Moteur_De_Recherche : public QMainWindow
{
    Q_OBJECT

public:
    explicit Moteur_De_Recherche(QWidget *parent = 0);
    ~Moteur_De_Recherche();


private slots:
    void on_pushButton_clicked();

    void on_Button_ouvrir_clicked();

    void on_open_btn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Moteur_De_Recherche *ui;
    QString filename;
    int m_algo=3;
};

#endif // MOTEUR_DE_RECHERCHE_H
