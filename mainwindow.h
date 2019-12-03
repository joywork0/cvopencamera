#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<opencv2/opencv.hpp>
#include<QtGui>
#include <QMainWindow>
#include<QFileDialog>
#include<QLabel>
#include <QWidget>
#include <QImage>
#include <QTimer>
#include <QTime>
#include<QTimerEvent>
#include<QTimeEdit>
#include <QImage>
#include <QDialog>
#include <QColor>
#include <QDir>
#include <QDebug>
#include <QIcon>
#include <QPalette>
#include <QListWidget>
#include<QWidget>
#include<QPushButton>
#include<QToolButton>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QListView>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QStringListModel>
#include<QSlider>
#include<QStackedWidget>
#include<QKeyEvent>
#include<QLabel>
#include <QWidget>
#include <QVideoWidget>
#include<QMessageBox>

#include <QListWidget>  //列表控制元件

#include <QListWidgetItem> //列表控制元件條目
#include<QtGui/QTouchEvent>
using namespace cv;
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
//protected:
protected:

   // void paintEvent(QPaintEvent *);

private slots:
    void nextFrame();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    //void on_pushButton_6_clicked();

    void on_openimage_clicked();

private:
    Ui::MainWindow *ui;
    Mat frame;
    Mat  edges;
    VideoCapture capture;
    QImage image;
    QTime *timer;
    double rate;
    VideoWriter writer;
};

#endif // MAINWINDOW_H
