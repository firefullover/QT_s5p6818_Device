#include "engine.h"

engine::engine(bool *mark,QLabel *tx_lb,QLabel *bire_lb)
{
    eng2_deg=90;//舵机初始坐标
    eng3_deg=90;
    new_mark=mark;//舵机位置标记
    l1=tx_lb;
    l2=bire_lb;
}

void engine::to_left(void)
{
    while(*new_mark)
    {
        double d;
        int c;
        status="left";
        l1->setText(status);

        int fd = ::open("/dev/myengine", O_RDWR); // 使用标准C函数打开设备文件
        if (fd <0)
        {
            printf("open file failed\n");
            return;
        }

        if(eng2_deg<=0)
        {
            printf("deg is 0,can't turn left\n");
        }
        else{
            d=eng2_deg-deg;
            c=d/1.8; //舵机转动最小单位deg=1.8度
            ::ioctl(fd, c, Engine2);
            eng2_deg=d;
        }

        status=QString::number(eng2_deg);
        l2->setText(status);
        ::close(fd);

        QThread::msleep(ss);//延时：长按时50ms变化1.8度
    }

}

void engine::to_right(void)
{
    while(*new_mark)
     {
        double d;
        int c;
        status="right";
        l1->setText(status);

        int fd = ::open("/dev/myengine", O_RDWR); // 使用标准C函数打开设备文件
        if (fd <0)
        {
            printf("open file failed\n");
            return;
        }
        if(eng2_deg>=180)
        {
            printf("deg is 180,can't turn right\n");
        }else{
            d=eng2_deg+deg;
            c=d/1.8;
            ::ioctl(fd, c, Engine2);
            eng2_deg=d;
        }
        status=QString::number(eng2_deg);
        l2->setText(status);
        ::close(fd);

        QThread::msleep(ss);
    }
}

void engine::to_up(void)
{
    while(*new_mark)
    {
        double d;
        int c;
        status="up";
        l1->setText(status);

        int fd = ::open("/dev/myengine", O_RDWR); // 使用标准C函数打开设备文件
        if (fd <0)
        {
            printf("open file failed\n");
            return;
        }
        if(eng3_deg<=0)
        {
            printf("deg is 0,can't turn up\n");
        }
        else{
            d=eng3_deg-deg;
            c=d/1.8;
            ::ioctl(fd, c, Engine3);
            eng3_deg=d;
        }
        status=QString::number(eng3_deg);
        l2->setText(status);
        ::close(fd);

        QThread::msleep(ss);
    }
}

void engine::to_down(void)
{
    while(*new_mark)
    {
        double d;
        int c;
        status="down";
        l1->setText(status);

        int fd = ::open("/dev/myengine", O_RDWR); // 使用标准C函数打开设备文件
        if (fd <0)
        {
            printf("open file failed\n");
            return;
        }
        if(eng3_deg>=180){
            printf("deg is 180,can't turn down\n");
        }else{
            d=eng3_deg+deg;
            c=d/1.8;
            ::ioctl(fd, c, Engine3);
            eng3_deg=d;
        }
        status=QString::number(eng3_deg);
        l2->setText(status);
        ::close(fd);

        QThread::msleep(ss);
    }
}

void engine::reset(void)
{
    float d=90;
    int c=d/1.8;
    status="reset";
    l1->setText(status);
    status="90";
    l2->setText(status);
    int fd = ::open("/dev/myengine", O_RDWR); // 使用标准C函数打开设备文件
    if (fd <0) {
            return;
        }
    ::ioctl(fd, c, Engine2);
    ::ioctl(fd, c, Engine3);
    eng3_deg=90;
    eng2_deg=90;
    ::close(fd);
//    QThread::msleep(ss);
}
