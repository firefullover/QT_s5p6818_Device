#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QDebug>
#include <QFile>
#include <QFileDevice>
#include <QLabel>

#define Engine2 0x1
#define Engine3 0x2
#define deg1 0x31
#define deg2 0x32
#define deg3 0x33
#define deg4 0x34
#define deg5 0x35
#define deg 1.8
#define ss 50

class engine : public QObject
{
    Q_OBJECT
public:
    explicit engine(bool *mark,QLabel *tx_lb,QLabel *bire_lb);
    void run(void);
    void to_left(void);
    void to_right(void);
    void to_up(void);
    void to_down(void);
    void reset(void);
private:
    bool *new_mark;
    QString status;
    int fd;
    QFile file;
    QLabel *l1;
    QLabel *l2;
    double eng2_deg;
    double eng3_deg;
};

#endif // ENGINE_H
