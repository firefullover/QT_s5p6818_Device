/********************************************************************************
** Form generated from reading UI file 'lab.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB_H
#define UI_LAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab
{
public:
    QLabel *status_lb;
    QPushButton *right_bt;
    QLabel *camera_show_lb;
    QPushButton *down_bt;
    QPushButton *up_bt;
    QPushButton *reset_bt;
    QPushButton *camera_show_bt;
    QPushButton *left_bt;
    QPushButton *camera_stop_bt;
    QLabel *deg_lb;

    void setupUi(QWidget *lab)
    {
        if (lab->objectName().isEmpty())
            lab->setObjectName(QStringLiteral("lab"));
        lab->resize(1024, 600);
        status_lb = new QLabel(lab);
        status_lb->setObjectName(QStringLiteral("status_lb"));
        status_lb->setGeometry(QRect(730, 110, 221, 71));
        QFont font;
        font.setPointSize(15);
        status_lb->setFont(font);
        status_lb->setLayoutDirection(Qt::LeftToRight);
        status_lb->setStyleSheet(QStringLiteral("background-color: rgb(234, 160, 43);"));
        status_lb->setAlignment(Qt::AlignCenter);
        right_bt = new QPushButton(lab);
        right_bt->setObjectName(QStringLiteral("right_bt"));
        right_bt->setGeometry(QRect(920, 400, 81, 71));
        camera_show_lb = new QLabel(lab);
        camera_show_lb->setObjectName(QStringLiteral("camera_show_lb"));
        camera_show_lb->setGeometry(QRect(20, 20, 640, 480));
        camera_show_lb->setStyleSheet(QStringLiteral("background-color: rgb(0,0,0);"));
        down_bt = new QPushButton(lab);
        down_bt->setObjectName(QStringLiteral("down_bt"));
        down_bt->setGeometry(QRect(800, 490, 91, 61));
        up_bt = new QPushButton(lab);
        up_bt->setObjectName(QStringLiteral("up_bt"));
        up_bt->setGeometry(QRect(800, 320, 91, 71));
        reset_bt = new QPushButton(lab);
        reset_bt->setObjectName(QStringLiteral("reset_bt"));
        reset_bt->setGeometry(QRect(800, 410, 91, 61));
        reset_bt->setFont(font);
        camera_show_bt = new QPushButton(lab);
        camera_show_bt->setObjectName(QStringLiteral("camera_show_bt"));
        camera_show_bt->setGeometry(QRect(310, 520, 91, 51));
        left_bt = new QPushButton(lab);
        left_bt->setObjectName(QStringLiteral("left_bt"));
        left_bt->setGeometry(QRect(690, 400, 81, 71));
        camera_stop_bt = new QPushButton(lab);
        camera_stop_bt->setObjectName(QStringLiteral("camera_stop_bt"));
        camera_stop_bt->setGeometry(QRect(460, 520, 91, 51));
        deg_lb = new QLabel(lab);
        deg_lb->setObjectName(QStringLiteral("deg_lb"));
        deg_lb->setGeometry(QRect(730, 210, 221, 71));
        deg_lb->setFont(font);
        deg_lb->setLayoutDirection(Qt::LeftToRight);
        deg_lb->setStyleSheet(QStringLiteral("background-color: rgb(234, 160, 43);"));
        deg_lb->setAlignment(Qt::AlignCenter);

        retranslateUi(lab);

        QMetaObject::connectSlotsByName(lab);
    } // setupUi

    void retranslateUi(QWidget *lab)
    {
        lab->setWindowTitle(QApplication::translate("lab", "lab", 0));
        status_lb->setText(QString());
        right_bt->setText(QApplication::translate("lab", "\345\217\263", 0));
        camera_show_lb->setText(QString());
        down_bt->setText(QApplication::translate("lab", "\344\270\213", 0));
        up_bt->setText(QApplication::translate("lab", "\344\270\212", 0));
        reset_bt->setText(QApplication::translate("lab", "\345\244\215\344\275\215", 0));
        camera_show_bt->setText(QApplication::translate("lab", "show", 0));
        left_bt->setText(QApplication::translate("lab", "\345\267\246", 0));
        camera_stop_bt->setText(QApplication::translate("lab", "stop", 0));
        deg_lb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class lab: public Ui_lab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB_H
