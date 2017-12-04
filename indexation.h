#ifndef INDEXATION_H
#define INDEXATION_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMessageBox>

#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace cv;

void histo_couleur(Mat src,QString j);

namespace Ui {
class Indexation;
}

class Indexation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Indexation(QWidget *parent = 0);
    ~Indexation();

    QStringList files;

    QString Filename;


private slots:
    void on_actionOuvrir_une_base_d_images_triggered();

  //  void on_actionSURF_triggered();

   // void on_actionSIFT_triggered();

    void on_actionHistogramme_Couleur_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_Indexattion_clicked();

    void on_actionRecherche_triggered();

private:
    Ui::Indexation *ui;
      //int algo;

};

#endif // INDEXATION_H
