#include "indexation.h"
#include "moteur_de_recherche.h"
#include "ui_moteur_de_recherche.h"
#include "ui_indexation.h"

string im[1000];

Moteur_De_Recherche::Moteur_De_Recherche(QWidget *parent) :

    //m_algo(t_algo),
    QMainWindow(parent),
  //  QWidget(parent),
    ui(new Ui::Moteur_De_Recherche)
{
    ui->setupUi(this);
    /*if(m_algo==1)
    {
    ui->comboBox->addItem("Brute Force Matching");
    ui->comboBox->addItem("FLANN based Matcher");
    this->setWindowTitle("Recherche Avec SIFT");
    }
    else if(m_algo==2)
    {
    ui->comboBox->addItem("Brute Force Matching");
    ui->comboBox->addItem("FLANN based Matcher");
    this->setWindowTitle("Recherche Avec SURF");
    }
    else if(m_algo==3)
    {
    ui->comboBox->addItem("Correlation");
    ui->comboBox->addItem("Chi-Square");
    ui->comboBox->addItem("Intersection");
    ui->comboBox->addItem("Bhattacharyya");
    this->setWindowTitle("Recherche Avec Histogramme Couleur");
    }
    else if(m_algo==4)
    {
    ui->comboBox->addItem("Correlation");
    ui->comboBox->addItem("Chi-Square");
    ui->comboBox->addItem("Intersection");
    ui->comboBox->addItem("Bhattacharyya");
    this->setWindowTitle("Recherche Avec Histogramme HSV");
    }*/

}

void tricroissant( double tab1[],string tab2[], int tab_size)
{
    int i=0;
    double tmp1=0;
    string tmp2;
    int j=0;
    for(i = 0; i < tab_size; i++)
    {
        for(j = i+1; j < tab_size; j++)
        {
            if(tab1[j] < tab1[i])
            {
                tmp1 = tab1[i];
                tmp2=tab2[i];
                tab1[i] = tab1[j];
                tab2[i] = tab2[j];
                tab1[j] = tmp1;
                tab2[j] = tmp2;
            }
        }
    }
}

// fonction permet d’ouvrir une image requête et calcul son descripteur




// cette fonction permet de lancer le moteur de recherche



// cette fonction permet de calculer R/P
/*void Form::on_pushButton_7_clicked()
{
    ofstream myfile;
    myfile.open ("test.dat");
    QFileInfo text1(fileName);
    QString text2=text1.fileName();
    cout << text2.toStdString() << endl;
    String text3=text2.toStdString().substr(0,text2.toStdString().find("."));
    stringstream ss1(text3);
    int position1;
    ss1 >> position1;
    position1/=100;
    int nombre=20;
    String pertinant[nombre];

    for (int i=0;i<nombre;i++)
    {
        stringstream ss2(im[i]);
        int position2;
        ss2 >> position2;
        position2/=100;

        if(position1==position2)
            pertinant[i]="pertinant";
        else
            pertinant[i]="non pertinant" ;
    }
int j;// mettre ceci en comment

    cout << pertinant[0] << endl;

    for (int i=0;i<nombre;i++)
    {
        int j=i;
        float val=0;
        while(j>=0)
        {
            if(pertinant[j]=="pertinant")
            val++;
            j--;
        }
       myfile << (val/(i+1))*100 << " " << val/20)*100 <<endl;
    }

    myfile.close();
    FILE *gp;
    if(WIN32)
    gp=_popen("gnuplot", "w");
    else
    gp=popen("gnuplot", "w");
    (val/20)*100 <<endl;

    if(gp == NULL)
    {
        fprintf(stderr, "Oops, I can't find %s.");
        //exit(EXIT_FAILURE);
    }

fprintf(gp, "load \"config\"\n");
fflush(gp); /* On oublie pas le buffer. */
//pclose(gp); //retirer ce comment

//}

Moteur_De_Recherche::~Moteur_De_Recherche()
{
    delete ui;
}



void Moteur_De_Recherche::on_open_btn_clicked()
{

    filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/project_folder ", tr("Image Files (*.png *.jpeg *.jpg *.bmp)"));
    QPixmap image(filename);
    ui->ImShow->setPixmap(image);

    //filename = QFileDialog::getOpenFileName(this,"Ouvrir","\image.orig","Images (*.jpg)");
    /*filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "\image.orig", tr("Image Files(*.png *.jpeg *.jpg *.bmp)"));
    QPixmap image(filename);
    ui->ImShow->setPixmap(image);*/
    Mat image1,image2;
    image1=imread(filename.toStdString(),0); // l'image au niveau de grille (noir)
    image2=imread(filename.toStdString(),1); // l'image en couleur

    histo_couleur(image2,"requete");
    /*if(m_algo==1)
        sift(image1,"requete");
    else if(m_algo==2)
        surf(image1,"requete");
    else if(m_algo==3)
        histo_c(image2,"requete");*/
}

void Moteur_De_Recherche::on_pushButton_clicked()
{
    filename = QFileDialog::getOpenFileName(this,tr("Open Image"), "\image.orig", tr("Image Files(*.png *.jpeg *.jpg *.bmp)"));
    QPixmap image(filename);
    ui->ImShow->setPixmap(image);
    Mat image1,image2;
    //image1=imread(filename.toStdString(),0); // l'image au niveau de grille (noir)
    image2=imread(filename.toStdString(),1); // l'image en couleur
    histo_couleur(image2,"requete");

    /*if(m_algo==1)
        sift(image1,"requete");
    else if(m_algo==2)
        surf(image1,"requete");
    else if(m_algo==3)
        histo_c(image2,"requete");*/
}

void Moteur_De_Recherche::on_pushButton_2_clicked()
{
    QString path;

    path="Histogramme_Couleur";

   /* if(m_algo==1)
    {
        path="SIFT";
    }
    else if(m_algo==2)
    {
        path="SURF";
    }
    else if(m_algo==3)
    {
        path="Histogramme_Couleur";
    }*/

    QDir dir(path);
    Mat descriptor1,descriptor2;
    FileStorage file1("requete.txt", cv::FileStorage::READ);
    file1[path.toStdString()] >> descriptor1;
    dir.setNameFilters(QStringList()<<"*.txt");
    QStringList features = dir.entryList();
    double distance[features.length()];
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(features.length());

    for (int i=0;i<features.length();i++)
    {
        FileStorage file2(path.toStdString()+"/"+QString(features[i]).toStdString(),
        cv::FileStorage::READ);
        file2[path.toStdString()] >> descriptor2;

      /*  if(m_algo==1||m_algo==2)
        {
            distance[i]=dist(descriptor1, descriptor2,1,ui->comboBox->currentIndex());
        }*/

        //else
            distance[i]=dist(descriptor1, descriptor2,2,1);//ui->comboBox->currentIndex());

        im[i]=QString(features[i]).toStdString().substr(0,QString(features[i]).toStdString().find("."));
        cout << distance[i] << " : " << im[i] <<endl;
        ui->progressBar->setValue(i+1);
    }

    tricroissant(distance,im,features.length());
    int taille;

    if(features.length()<=8)
        taille=features.length();
    else
        taille=8;

    for (int i=0;i<taille;i++)
    {
        QLabel * L = new QLabel;
        L->setScaledContents(true);
        QProgressBar *dist=new QProgressBar;
        //QLabel * dist =new QLabel;
        L->setGeometry(250,150, 100, 100);
        dist->setGeometry(250,150,100,100);
        L->setObjectName("lab" + (i+1));
        dist->setObjectName("d" + (i+1));
        QString chemin ="image.orig\\"+QString::fromStdString(im[i])+".jpg";
        QPixmap image(chemin);
        L->setPixmap(image.scaled(L->size()));
        cout << distance[i]*100 << endl;

        if((m_algo==3||m_algo==4)&&ui->comboBox->currentIndex()==0)
            dist->setValue(distance[i]*100);
        else
            dist->setValue(100-(distance[i]*100));

         ui->Search->setPixmap(image);

      //  ui->gridLayout->addWidget(L, 2*(i/4),i%4);
       // ui->gridLayout->addWidget(dist,2*(i/4)+1,i%4);
    }
}
