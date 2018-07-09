#-------------------------------------------------
#
#     Stereo Camera Calibration with OpenCV
#
#    by AbsurdePhoton - www.absurdephoton.fr
#
# Project created by QtCreator 2018-07-01T23:09:47
#
#-------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_load_clicked();

private:
    Ui::MainWindow *ui;
    void Calibration();

};

#endif // MAINWINDOW_H
