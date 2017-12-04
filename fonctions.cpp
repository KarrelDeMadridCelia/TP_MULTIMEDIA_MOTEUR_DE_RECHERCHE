#include "indexation.h"
#include "moteur_de_recherche.h"

bool compare_response(KeyPoint first, KeyPoint second) //utilisée par sift

{
if (first.response > second.response) return true;
else return false;
}

void histo_couleur(Mat src,QString j)
{
    vector<Mat> bgr_planes;
    split( src, bgr_planes );
    int histSize = 256;
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    int channels[] = { 0, 1 };
    Mat b_hist, g_hist, r_hist;

    calcHist( &bgr_planes[0], 1, channels, Mat(), b_hist, 1,&histSize, &histRange, true, false );
    calcHist( &bgr_planes[1], 1, channels, Mat(), g_hist, 1,&histSize, &histRange, true, false );
    calcHist( &bgr_planes[2], 1, channels, Mat(), r_hist, 1,&histSize, &histRange, true, false );
    MatND hist_base,la;
    hconcat(b_hist,g_hist,la);
    hconcat(la,r_hist,hist_base);
    string path;

    if(j=="requete")
    path = "requete.txt";
    else
    path = "Histogramme_Couleur/" + j.toStdString().substr(0,j.toStdString().find(".")) +".txt";
    FileStorage fs(path, FileStorage::WRITE);
    fs << "Histogramme_Couleur" << hist_base;
    fs.release();
}

/*void sift(Mat img, QString j)
{
    SiftFeatureDetector detector;
    vector<KeyPoint> keypoints;
    detector.detect(img, keypoints);
    sort(keypoints.begin(), keypoints.end(), compare_response);
    vector<KeyPoint> keypoints_2;
    for (int i = 0; i < (keypoints.size())/4; i++)
    {
    keypoints_2.push_back(keypoints[i]);
    }
    SiftDescriptorExtractor extractor;
    Mat descriptors;
    extractor.compute(img, keypoints_2, descriptors);
    string path;
    if(j=="requete")
    path = "requete.txt";
    else
    path = "SIFT/" + j.toStdString().substr(0,j.toStdString().find(".")) +".txt";
    FileStorage fs(path, FileStorage::WRITE);
    fs << "SIFT" << descriptors;
}

void surf(Mat img, QString j)
{
    int minHessian = 400;
    SurfFeatureDetector detector(minHessian);
    vector<KeyPoint> keypoints_1;
    detector.detect(img, keypoints_1);
    sort(keypoints_1.begin(), keypoints_1.end(), compare_response);
    vector<KeyPoint> keypoints_2;
    for (int i = 0; i <(keypoints_1.size()) / 4; i++)
    {
    keypoints_2.push_back(keypoints_1[i]);
    }
    SurfDescriptorExtractor extractor;
    Mat descriptors_1;
    extractor.compute(img, keypoints_2, descriptors_1);
    string path;
    if(j=="requete")
    path = "requete.txt";
    else
    path = "SURF/" + j.toStdString().substr(0,j.toStdString().find(".")) +".txt";
    FileStorage fs(path, FileStorage::WRITE);
    fs << "SURF" << descriptors_1;
    fs.release();
}*/

double dist(Mat descriptors_1, Mat descriptors_2, int type, int curr)
{
    // type : 1 si sift ou surf
    //0 si histogramme
    //curr : un parametre de la fonction compareHist d’OpenCV (voir doc) pour histogramme
    //ou différentiateur pour le type de comparaison Flann ou Brut Force BF pour sift et surf

    if(type==1)
    {
    if(curr==0)
    {
        FlannBasedMatcher matcher;
        vector< DMatch > matches;
        matcher.match(descriptors_1, descriptors_2, matches);
        double max_dist = 0.0;
    for (int i = 0; i < matches.size(); i++)
    {
        double dist = matches[i].distance;
         if (dist > max_dist) max_dist = dist;
    }
    if (max_dist != 0.0)
    {
        for (int i = 0; i < matches.size(); i++)
        {
             matches[i].distance = (matches[i].distance) / max_dist;
        }
    }

    double moy = 0.0;
    for (int i = 0; i < matches.size(); i++)
    {
        moy += matches[i].distance;
    }
        moy /= matches.size();
        std::vector< DMatch > good_matches;
    for (int i = 0; i < matches.size(); i++)
    {
        if (matches[i].distance <= moy)
        {
            good_matches.push_back(matches[i]);
        }
    }
    double good_moy = 0.0;
    for (int i = 0; i < good_matches.size(); i++)
    {
        good_moy += good_matches[i].distance;
    }
        good_moy /= good_matches.size();
        return good_moy;
    }

    else
    {
        BFMatcher matcher(NORM_L2);
        vector< DMatch > matches;
        matcher.match(descriptors_1, descriptors_2, matches);
        double max_dist = 0.0;
    for (int i = 0; i < matches.size(); i++)
    {
        double dist = matches[i].distance;
        if (dist > max_dist) max_dist = dist;
    }

    if (max_dist != 0.0)
    {
    for (int i = 0; i < matches.size(); i++)
    {
    matches[i].distance = (matches[i].distance) / max_dist;
    }
    }
    double moy = 0.0;
    for (int i = 0; i < matches.size(); i++)
    {
    moy += matches[i].distance;
    }
    moy /= matches.size();
    std::vector< DMatch > good_matches;
    for (int i = 0; i < matches.size(); i++)
    {
    if (matches[i].distance <= moy)
    {
    good_matches.push_back(matches[i]);
    }
    }
    double good_moy = 0.0;
    for (int i = 0; i < good_matches.size(); i++)
    {
    good_moy += good_matches[i].distance;
    }
    good_moy /= good_matches.size();
    return good_moy;
    }
    }
    else
    {
    return compareHist(descriptors_1, descriptors_2, curr); //fonction OpenCV
    }
}
