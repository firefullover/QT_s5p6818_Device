#include "lab.h"
#include "ui_lab.h"


lab::lab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lab)
{
    ui->setupUi(this);
    // eng2_deg=90;
    // eng3_deg=90;
    mark=false;
    mark_camera=false;
//--------------------engine-----------------------------------
    engine_ptr=new engine(&mark,ui->status_lb,ui->deg_lb);
    engine_thread=new QThread();
    engine_ptr->moveToThread(engine_thread);
    connect(ui->left_bt,SIGNAL(pressed()),this,SLOT(engine_left()));
    connect(this,&lab::sig_left,engine_ptr,&engine::to_left);
    connect(ui->right_bt,SIGNAL(pressed()),this,SLOT(engine_right()));
    connect(this,&lab::sig_right,engine_ptr,&engine::to_right);
    connect(ui->up_bt,SIGNAL(pressed()),this,SLOT(engine_up()));
    connect(this,&lab::sig_up,engine_ptr,&engine::to_up);
    connect(ui->down_bt,SIGNAL(pressed()),this,SLOT(engine_down()));
    connect(this,&lab::sig_down,engine_ptr,&engine::to_down);

    connect(ui->reset_bt,SIGNAL(clicked(bool)),this,SLOT(engine_reset()));
    connect(this,&lab::sig_reset,ll,&engine::reset);
    engine_thread->start();
//---------------------camera------------------------------------
    camera_ptr=new camera(&mark_camera,ui->camera_show_lb);
    camera_thread=new QThread();
    engine_ptr->moveToThread(camera_thread);
    connect(ui->camera_show_bt,SIGNAL(clicked(bool)),this,SLOT(camera_up()));
    connect(this,&lab::sig_camera,engine_ptr,&camera::rel_han6);
    camera_thread->start();
}

lab::~lab()
{
    delete ui;
}

void lab::engine_left()
{
    emit sig_left();
}
void lab::engine_right()
{
    emit sig_right();
}
void lab::engine_up()
{
    emit sig_up();
}
void lab::engine_down()
{
    emit sig_down();
}
void lab::engine_reset()
{
    emit sig_reset();
}
void lab::camera_up()
{
    emit sig_camera();
}

void lab::on_left_bt_released()
{
    qDebug()<<"release...\n";
    mark=false;
}

void lab::on_right_bt_released()
{
    qDebug()<<"release...\n";
    mark=false;
}

void lab::on_up_bt_released()
{
    qDebug()<<"release...\n";
    mark=false;
}

void lab::on_down_bt_released()
{
    qDebug()<<"release...\n";
    mark=false;
}

void lab::on_down_bt_pressed()
{
    mark=true;
}

void lab::on_left_bt_pressed()
{
    mark=true;
}

void lab::on_up_bt_pressed()
{
    mark=true;
}

void lab::on_right_bt_pressed()
{
    mark=true;
}

void lab::on_camera_stop_bt_clicked()
{
    mark_camera=false;
}

void lab::on_camera_show_bt_clicked()
{
    mark_camera=true;
}
