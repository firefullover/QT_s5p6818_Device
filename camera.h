#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <linux/videodev2.h>
#include <string.h>
#include <sys/mman.h>
#include <jpeglib.h>
#include <linux/fb.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QFile>
#include <QFileDevice>

//#include <cstring> // 用于memcpy
#include <QApplication>

class camera: public QObject
{
    Q_OBJECT
public:
    camera(bool *mark_camera,QLabel *lb);
    void rel_han6(void);
    void lcd_show_rgb(unsigned char *rgbdata,int w,int h,int size);
    int read_JPEG_file (unsigned char *jpegData,unsigned char *rgbdata, int size);
private:
    QLabel *l;
    bool *mark;
    int lcdfd;
    unsigned int *lcdptr;
    int lcd_w,lcd_h;
};

#endif // CAMERA_H
