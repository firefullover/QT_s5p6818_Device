#ifndef LAB_H
#define LAB_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QObject>
#include "engine.h"
#include "camera.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QDebug>
#include <QFile>
#include <QFileDevice>
#include <QLabel>

namespace Ui {
class lab;
}

class lab : public QWidget
{
    Q_OBJECT
signals:
    void sig_left();
    void sig_right();
    void sig_up();
    void sig_down();
    void sig_reset();
    void sig_camera();
public slots:
     void engine_left();
     void engine_right();
     void engine_up();
     void engine_down();
     void engine_reset();
     void camera_up();
public:
    explicit lab(QWidget *parent = 0);
    ~lab();
     void lcd_show_rgb(unsigned char *rgbdata,int w,int h);
     int read_JPEG_file (unsigned char *jpegData,unsigned char *rgbdata, int size);

private slots:

    void on_left_bt_released();

    void on_right_bt_released();

    void on_up_bt_released();

    void on_down_bt_released();

    void on_down_bt_pressed();

    void on_left_bt_pressed();

    void on_up_bt_pressed();

    void on_right_bt_pressed();

    void on_camera_stop_bt_clicked();

    void on_camera_show_bt_clicked();

private:
    Ui::lab *ui;
    QString status;
    int fd,led;
    QFile file;
    float eng2_deg;
    float eng3_deg;

    QThread *engine_thread;
    engine *engine_ptr;
    QThread *camera_thread;
    camera *camera_ptr;
    bool mark;
    bool mark_camera;
};

#endif // LAB_H
