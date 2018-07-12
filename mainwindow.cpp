/*-------------------------------------------------
#
#     Stereo Camera Calibration with OpenCV
#
#    by AbsurdePhoton - www.absurdephoton.fr
#
#                v1 - 2018/07/10
#
#-------------------------------------------------*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/ximgproc/disparity_filter.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/utility.hpp"

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

#include "mpo.h"
#include "mat-image-tools.h"

using namespace cv;
using namespace cv::ximgproc;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcd_good->setPalette(Qt::green);
    ui->lcd_bad->setPalette(Qt::red);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Calibration() {

    std::string fileType;
    if (ui->radioButton_MPO->isChecked()) fileType = "MPO";
    if (ui->radioButton_alternate->isChecked()) fileType = "alt";
    QStringList filenames;
    if (fileType == "MPO")
        filenames = QFileDialog::getOpenFileNames(this, "Choose MPO files to calibrate...", "/home", "*.mpo *.MPO");
    if (fileType == "alt")
        filenames = QFileDialog::getOpenFileNames(this, "Choose files (alternate left/right) to calibrate...", "/home", "*.jpg *.JPG *.png *.PNG *.tif *.TIF");
    if (filenames.isEmpty())
        return;
    if ((fileType == "alt") && ((filenames.size() % 2) == 1))
    {
        QMessageBox::information(this, "List error", "The number of files must be even!");
        return;
    }

    bool success;
    int total = 0;
    int good = 0;
    int failed = 0;
    int ref_width = ui->spinBox_width->value();
    int ref_height = ui->spinBox_height->value();
    int ref_size = ui->spinBox_size->value();
    QString type;
    if (ui->radioButton_checkerboards->isChecked()) type = "checkerboards";
    if (ui->radioButton_circles_symmetric->isChecked()) type = "circles";
    if (ui->radioButton_circles_asymmetric->isChecked()) type = "circles_asymmetric";
    ui->progres->setRange(0, filenames.size());
    if (fileType == "alt") ui->progres->setRange(0, filenames.size() / 2);
    ui->failed->setRange(0, filenames.size());
    ui->lcd_good->display(total);
    ui->lcd_bad->display(failed);
    qApp->processEvents();

    SimpleBlobDetector::Params parameters;
    parameters.maxArea = 100000;
    parameters.minArea = 500;
    parameters.filterByColor = false;
    parameters.minDistBetweenBlobs = 25;
    Ptr<FeatureDetector> blobDetector = SimpleBlobDetector::create(parameters);

    vector<vector<Point3f>> object_points;
    vector<vector<Point3f>> object_pointsL;
    vector<vector<Point2f>> image_pointsL;
    vector<vector<Point3f>> object_pointsR;
    vector<vector<Point2f>> image_pointsR;
    cv::Size size;

    for (QStringList::const_iterator it = filenames.begin(); it != filenames.end(); ++it) {
        total++;
        ui->progres->setValue(total);
        qApp->processEvents();

        vector<cv::Mat> matImages(2); // container to COMPUTE stereo images

        if (fileType == "MPO") {
            success = MPO2Mat(*it, matImages);
        }
        if (fileType == "alt") {
            std::string name = (*it).toStdString();
            matImages[0] = cv::imread(name, CV_LOAD_IMAGE_COLOR);
            success = (matImages[0].data != NULL);
            if (success) {
                it++;
                matImages[1] = cv::imread((*it).toStdString(), CV_LOAD_IMAGE_COLOR);
                success = (matImages[1].data != NULL);
            }
        }

        if (success) {
            // display the 2 jpegs
            ui->gauche->setPixmap(Mat2QPixmapResized(matImages[0], ui->gauche->width(), ui->gauche->height()));
            ui->droite->setPixmap(Mat2QPixmapResized(matImages[1], ui->droite->width(), ui->droite->height()));
            qApp->processEvents();

            // LEFT IMAGE

            vector<Point2f> cornersL;

            cv::Mat grayL;
            cv::cvtColor(matImages[0], grayL, CV_BGR2GRAY);

            bool foundL = false;
            if (type == "checkerboards") foundL = cv::findChessboardCorners(grayL, cv::Size(ref_width,ref_height), cornersL,
                                 CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FILTER_QUADS);
            if (type == "circles") foundL = cv::findCirclesGrid(grayL, cv::Size(ref_width,ref_height), cornersL, CALIB_CB_SYMMETRIC_GRID, blobDetector);
            if (type == "circles_asymmetric") foundL = cv::findCirclesGrid(grayL, cv::Size(ref_width,ref_height), cornersL, CALIB_CB_ASYMMETRIC_GRID, blobDetector);

            vector<Point3f> objL;

            if (foundL) {

                cv::Mat disp_colorL = matImages[0];
                if (type == "checkerboards") cv::cornerSubPix(grayL, cornersL, cv::Size(ref_width, ref_height), cv::Size(-1, -1),
                                       cv::TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 50, 0.1));
                cv::drawChessboardCorners(disp_colorL, cvSize(ref_width,ref_height), cornersL, foundL);

                QPixmap disp_pixmapL = Mat2QPixmapResized(disp_colorL, ui->result_left->width(), ui->result_left->height());
                ui->result_left->setPixmap(disp_pixmapL);
                qApp->processEvents();

                for (int i = 0; i < ref_height; i++)
                for (int j = 0; j < ref_width; j++) {
                  if (type == "checkerboards") objL.push_back(Point3f((float)j * ref_size, (float)i * ref_size, 0));
                  if (type == "circles") objL.push_back(Point3f((float)j * ref_size, (float)i * ref_size, 0));
                  if (type == "circles_asymmetric") objL.push_back(Point3f(float((2*j + i % 2) * ref_size), (float)i * ref_size, 0));
                }
            }
            else {
                ui->result_left->setText("Checkerboard NOT FOUND");
                qApp->processEvents();
            }

            // RIGHT IMAGE

            vector<Point2f> cornersR;

            cv::Mat grayR;
            cv::cvtColor(matImages[1], grayR, CV_BGR2GRAY);

            bool foundR = false;
            if (type == "checkerboards") foundR = cv::findChessboardCorners(grayR, cv::Size(ref_width,ref_height), cornersR,
                                      CALIB_CB_NORMALIZE_IMAGE | CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FILTER_QUADS);
            if (type == "circles") foundR = cv::findCirclesGrid(grayR, cv::Size(ref_width,ref_height), cornersR, CALIB_CB_SYMMETRIC_GRID, blobDetector);
            if (type == "circles_asymmetric") foundR = cv::findCirclesGrid(grayR, cv::Size(ref_width,ref_height), cornersR, CALIB_CB_ASYMMETRIC_GRID, blobDetector);

            vector< Point3f > objR;

            if (foundR) {

              cv::Mat disp_colorR = matImages[1];
              if (type == "checkerboards") cv::cornerSubPix(grayR, cornersR, cv::Size(ref_width, ref_height), cv::Size(-1, -1),
                                     cv::TermCriteria(TermCriteria::EPS | TermCriteria::COUNT, 50, 0.1));
              cv::drawChessboardCorners(disp_colorR, cvSize(ref_width,ref_height), cornersR, foundR);

              QPixmap disp_pixmapR = Mat2QPixmapResized(disp_colorR, ui->result_right->width(), ui->result_right->height());
              ui->result_right->setPixmap(disp_pixmapR);
              qApp->processEvents();


              for (int i = 0; i < ref_height; i++)
              for (int j = 0; j < ref_width; j++) {
                if (type == "checkerboards") objR.push_back(Point3f((float)j * ref_size, (float)i * ref_size, 0));
                if (type == "circles") objR.push_back(Point3f((float)j * ref_size, (float)i * ref_size, 0));
                if (type == "circles_asymmetric") objR.push_back(Point3f(float((2*j + i % 2) * ref_size), (float)i * ref_size, 0));
              }
            }
            else {
                ui->result_right->setText("Checkerboard NOT FOUND");
                qApp->processEvents();
            }
            if (!(foundL && foundR)) { // Board not found
                failed++;
                ui->failed->setValue(failed);
                ui->lcd_bad->display(failed);
                qApp->processEvents();
            }
            else { // Board found
                good++;
                ui->lcd_good->display(good);
                qApp->processEvents();
                vector<Point3f> obj;
                    for (int i = 0; i < ref_height; i++)
                      for (int j = 0; j < ref_width; j++) {
                        if (type == "checkerboards") obj.push_back(Point3f((float)j * ref_size, (float)i * ref_size, 0));
                        if (type == "circles") obj.push_back(Point3f((float)j * ref_size, (float)i * ref_size, 0));
                        if (type == "circles_asymmetric") obj.push_back(Point3f(float((2*j + i % 2) * ref_size), (float)i * ref_size, 0));
                      }
                object_points.push_back(obj);
                image_pointsL.push_back(cornersL);
                object_pointsL.push_back(objL);
                size = grayL.size();
                image_pointsR.push_back(cornersR);
                object_pointsR.push_back(objR);
                size = grayR.size();
            }
        }
        else {
            ui->gauche->setText("IMAGE NOT LOADED");
            ui->droite->setText("IMAGE NOT LOADED");
            ui->result_left->setText("Could not compute");
            ui->result_right->setText("Could not compute");
            qApp->processEvents();
            QMessageBox::information(this, "Image error", "File : " + *it);
        }
    }
    // Calibrate Left camera
    Mat KL;
    Mat DL;
    vector<Mat> rvecsL, tvecsL;
    int flagL = 0;
    double errorL;
    if (total != failed) errorL = cv::calibrateCamera(object_pointsL, image_pointsL, size, KL, DL, rvecsL, tvecsL, flagL);

    // Calibrate Right camera
    Mat KR;
    Mat DR;
    vector<Mat> rvecsR, tvecsR;
    int flagR = 0;
    double errorR;
    if (total != failed) errorR = cv::calibrateCamera(object_pointsR, image_pointsR, size, KR, DR, rvecsR, tvecsR, flagR);

    // Calibrate both cameras
    Mat R, F, E;
    Vec3d T;
    int flag = CALIB_FIX_INTRINSIC;
    double error;
    if (total != failed) error = stereoCalibrate(object_points, image_pointsL, image_pointsR, KL, DL, KR, DR, size, R, T, E, F, flag);

    // Computes lens values
    double apertureWidth = ui->sensor_width->value(), apertureHeight = ui->sensor_height->value();
    double fovxL, fovyL, focalLengthL, aspectRatioL;
    cv::Point2d principalPointL;
    cv::calibrationMatrixValues(KL, size, apertureWidth, apertureHeight, fovxL, fovyL, focalLengthL, principalPointL, aspectRatioL);
    double fovxR, fovyR, focalLengthR, aspectRatioR;
    cv::Point2d principalPointR;
    cv::calibrationMatrixValues(KL, size, apertureWidth, apertureHeight, fovxR, fovyR, focalLengthR, principalPointR, aspectRatioR);

    // End of procedure
    if (total != failed) { // at least one valid pattern found
        QMessageBox::information(this, "Calibration finished !", "Estimated errors : \nLeft : " + QString::number(errorL) \
                                       + "\n Right : " + QString::number(errorR) \
                                       + "\n Stereo : " + QString::number(error) + "\n");

        // Write results to a directory
        QString dir(QFileDialog::getExistingDirectory(this, "Choose location to save xml calibration files..."));
        if (dir.isNull())
            return;

        // we convert filename from QString to std::string (needed by OpenCV)
        std::string filename_left = dir.toUtf8().constData() + std::string("/calibration-left.xml");
        std::string filename_right = dir.toUtf8().constData() + std::string("/calibration-right.xml");
        std::string filename_stereo = dir.toUtf8().constData() + std::string("/calibration-stereo.xml");

        // Left
        FileStorage fs_left(filename_left, FileStorage::WRITE);
        fs_left << "BoardWidth" << ref_width;
        fs_left << "BoardHeight" << ref_height;
        fs_left << "PatternSize" << ref_size;
        fs_left << "K" << KL;
        fs_left << "D" << DL;
        fs_left << "Error" << errorL;
        fs_left << "ApertureWidth" << apertureWidth;
        fs_left << "ApertureHeight" << apertureHeight;
        fs_left << "LensFOVx" << fovxL;
        fs_left << "LensFOVy" << fovyL;
        fs_left << "LensFocalLength" << focalLengthL;
        fs_left << "PrincipalPoint" << principalPointL;
        fs_left << "AspectRatio" << aspectRatioL;

        // Right
        FileStorage fs_right(filename_right, FileStorage::WRITE);
        fs_right << "BoardWidth" << ref_width;
        fs_right << "BoardHeight" << ref_height;
        fs_right << "PatternSize" << ref_size;
        fs_right << "K" << KR;
        fs_right << "D" << DR;
        fs_right << "Error" << errorR;
        fs_right << "ApertureWidth" << apertureWidth;
        fs_right << "ApertureHeight" << apertureHeight;
        fs_right << "LensFOVx" << fovxR;
        fs_right << "LensFOVy" << fovyR;
        fs_right << "LensFocalLength" << focalLengthR;
        fs_right << "PrincipalPoint" << principalPointR;
        fs_right << "AspectRatio" << aspectRatioR;

        // Stereo
        FileStorage fs_stereo(filename_stereo, FileStorage::WRITE);
        fs_stereo << "BoardWidth" << ref_width;
        fs_stereo << "BoardHeight" << ref_height;
        fs_stereo << "PatternSize" << ref_size;
        fs_stereo << "KL" << KL;
        fs_stereo << "KR" << KR;
        fs_stereo << "DL" << DL;
        fs_stereo << "DR" << DR;
        fs_stereo << "R" << R;
        fs_stereo << "T" << T;
        fs_stereo << "E" << E;
        fs_stereo << "F" << F;
        fs_stereo << "ErrorStereo" << error;
    }
}

void MainWindow::on_load_clicked() {
    Calibration();
}
