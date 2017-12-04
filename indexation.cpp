#include "indexation.h"
#include "ui_indexation.h"
#include "moteur_de_recherche.h"

Indexation::Indexation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Indexation)
{
    ui->setupUi(this);
}

Indexation::~Indexation()
{
    delete ui;
}

void Indexation::on_actionOuvrir_une_base_d_images_triggered()
{
    files = QFileDialog::getOpenFileNames(this,"Ouvrir","\image.orig","Images (*.jpg)"); // files = ensemble des images (base de données)

    QStandardItemModel *model = new QStandardItemModel(files.length(),2,this); // declaration pour QT
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Image"))); // on affiche l'image
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Chemin"))); // on affiche le chemin
    ui->tableView->setModel(model);

    for(int i=0;i<files.length();i++)
    {
        QFile text1(files[i]);
        QString text2=text1.fileName();
        QStandardItem *secondRow = new QStandardItem(text2.section("/",-1,-1));
        QStandardItem *firstRow = new QStandardItem(QString(files[i]));
         model->setItem(i,1,firstRow);
         model->setItem(i,0,secondRow);
    }
        QPixmap image(files[0]);
        ui->ImageShow->setPixmap(image);
}

void Indexation::on_actionHistogramme_Couleur_triggered()
{
    //algo=3;
 //   ui->actionSIFT->setChecked(0);
   // ui->actionGLCM->setChecked(0);
    ui->actionHistogramme_Couleur->setChecked(1);
  //  ui->actionHistogramme_HSV->setChecked(0);
  //  ui->actionSURF->setChecked(0);
}


/*void Indexation::on_actionSURF_triggered()
{
    algo=2;
    ui->actionSIFT->setChecked(0);
    ui->actionGLCM->setChecked(0);
    ui->actionHistogramme_Couleur->setChecked(0);
    ui->actionHistogramme_HSV->setChecked(0);
    ui->actionSURF->setChecked(1);
}*/



/*void Indexation::on_actionSIFT_triggered()
{
    algo=1;
    ui->actionSIFT->setChecked(1);
    ui->actionGLCM->setChecked(0);
    ui->actionHistogramme_Couleur->setChecked(0);
    ui->actionHistogramme_HSV->setChecked(0);
    ui->actionSURF->setChecked(0);
}*/


void Indexation::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString name = index.sibling(row, 1).data().toString(); // permpet de récuperer toutes les colonnes et 1 colonne pour le chemin
    QPixmap image(name);
    ui->ImageShow->setPixmap(image);
}

void Indexation::on_Indexattion_clicked()
{
     //  if(!ui->actionSURF->isChecked()&&!ui->actionSIFT->isChecked()&&!ui->actionHistogramme_Couleur->isChecked()&&!ui->actionHistogramme_HSV->isChecked())
     if(!ui->actionHistogramme_Couleur->isChecked())

    {
        QMessageBox msgBox;
        msgBox.setText("Il faut au moins choisir un algorithme");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }

    else
    {
        ui->progressBar->setMaximum(files.length());
        ui->progressBar->setValue(0);

    for(int i=0;i<files.length();i++)
    {
        cout<<"i="<<i<<endl;
        Mat image1,image2;
        QFile text1(files[i]);
        QString text2=text1.fileName();
        image1 = imread(QString(files[i]).toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
        image2 = imread(QString(files[i]).toStdString(), 1); // 1 c'est pour avoir l'image en couleur


        if(ui->actionHistogramme_Couleur->isChecked()) // on cree un dossier par descripteur pour stocker les infos
        {
            cout<<"creation de dossier"<<endl;

            if(!QDir("Histogramme_Couleur").exists())
            QDir().mkdir("Histogramme_Couleur");
            histo_couleur(image2,text2.section("/",-1,-1)); // histo_c est une fonction permettant de faire l'indexation et le deuxième paramètre permet de dire soit ne fait l'indéxation, soit on fait de la recherche
        }

      /*  else if(ui->actionSIFT->isChecked())
        {
            if(!QDir("SIFT").exists())
            QDir().mkdir("SIFT");
            sift(image1,text2.section("/",-1,-1));
        }

        else if(ui->actionSURF->isChecked())
         {

            if(!QDir("SURF").exists())
            QDir().mkdir("SURF");
            surf(image1,text2.section("/",-1,-1));
        }

        else if(ui->actionHistogramme_HSV->isChecked())
        {

            if(!QDir("Histogramme_HSV").exists())
            QDir().mkdir("Histogramme_HSV");

            histo_hsv(image2,text2.section("/",-1,-1));
        }*/

    ui->progressBar->setValue(i+1);

    }

    QMessageBox msgBox;
    msgBox.setText("Indexation Terminé");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();

    }
}

void Indexation::on_actionRecherche_triggered()
{
    Moteur_De_Recherche *a = new Moteur_De_Recherche();
    a->show();
}
