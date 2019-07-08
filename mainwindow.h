/*-------------------------------------------------
#
#     Stereo Camera Calibration with OpenCV
#
#    by AbsurdePhoton - www.absurdephoton.fr
#
#                v1 - 2018/07/10
#
#-------------------------------------------------*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_Abort_clicked();

private:
    Ui::MainWindow *ui;
    void Calibration();
    bool abort;

};

#endif // MAINWINDOW_H
