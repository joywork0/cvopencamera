#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<opencv4/opencv2/core.hpp>
#include<opencv4/opencv2/highgui.hpp>
#include<opencv4/opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setScaledContents(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QImage  Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,COLOR_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }

    return qImg;

}
void MainWindow::nextFrame()
{
    capture>>frame;
    if(!frame.empty())
    {
        image=Mat2QImage(frame);
        ui->label->setPixmap(QPixmap::fromImage(image));

    }


}

void MainWindow::on_pushButton_clicked()
{
    if (capture.isOpened())
            capture.release();     //decide if capture is already opened; if so,close it
        QString filename =QFileDialog::getOpenFileName(this,tr("Open Video File"),".",tr("Video Files(*.avi *.mp4 *.flv *.mkv)"));
        capture.open(filename.toLocal8Bit().data());
        if (capture.isOpened())
        {
            rate= capture.get(CAP_PROP_FPS);
            capture >> frame;
            if (!frame.empty())
            {

                image = Mat2QImage(frame);
                ui->label->setPixmap(QPixmap::fromImage(image));
                QTimer *timer = new QTimer(this);
                timer->setInterval(1000/rate);   //set timer match with FPS
                connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
                timer->start();
            }
        }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (capture.isOpened())
           capture.release();     //decide if capture is already opened; if so,close it
       capture.open(0);           //open the default camera
       if (capture.isOpened())
       {
           rate= capture.get(CAP_PROP_FPS);
           capture >> frame;
           if (!frame.empty())
           {

               image = Mat2QImage(frame);
               ui->label->setPixmap(QPixmap::fromImage(image));
               QTimer *timer = new QTimer(this);
               timer->setInterval(1000/rate);   //set timer match with FPS
               connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
               timer->start();
           }
       }
}

void MainWindow::on_pushButton_3_clicked()
{
    cv::Mat cannyImg ;
    cv::Canny(frame, cannyImg, 0, 30, 3);
    cv::namedWindow("Canny");
    cv::imshow("Canny", cannyImg);
}

void MainWindow::on_pushButton_4_clicked()
{
    writer.open("./myrec.avi",cv::VideoWriter::fourcc('P','I','M','1'), /*capture.get(CV_CAP_PROP_FPS)*/30, cv::Size(frame.cols, frame.rows),true);
    int t=100; while(t--) {writer.write(frame);} //record 100 frames
    ui->pushButton_4->setDisabled(true); //if successfully start videoWriter, disable the button
}

void MainWindow::on_pushButton_5_clicked()
{
    writer.release();
}

//void MainWindow::on_pushButton_6_clicked()
//{
//    Mat image1;
//    cvtColor(frame,edges,CV_BGR2GRAY);//把影象轉換為灰度影象
//    blur(edges,edges,Size(7,7));//模糊降噪
//    Canny(edges,edges,3,9,3);//Canny 邊緣檢測
//         image1 = Mat2QImage(edges);
//      ui->label->setPixmap(QPixmap::fromImage(image1));

//    QTimer *timer = new QTimer(this);
//    timer->setInterval(1000/rate);   //set timer match with FPS
//    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
//    timer->start();
//}

void MainWindow::on_openimage_clicked()
{
//       Mat image = imread("1.jpg");
//       QImage frame = Mat2QImage(image);
//        ui->label->setPixmap(QPixmap::fromImage(frame));
//        複製程式碼

            QString filename;
            filename=QFileDialog::getOpenFileName(this,
                                                  tr("選擇影象"),
                                                  "",
                                                  tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
            if(filename.isEmpty())
            {
                 return;
            }
            else
            {
                QImage* img=new QImage;

                if(! ( img->load(filename) ) ) //載入影象
                {
                    QMessageBox::information(this,
                                             tr("開啟影象失敗"),
                                             tr("開啟影象失敗!"));
                    delete img;
                    return;
                }
                ui->label->setPixmap(QPixmap::fromImage(*img));
            }
}
