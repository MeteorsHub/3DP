/********************************************************************************
** Form generated from reading UI file 'yesornotdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YESORNOTDIALOG_H
#define UI_YESORNOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_YesOrNotDialog
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *instruction;

    void setupUi(QDialog *YesOrNotDialog)
    {
        if (YesOrNotDialog->objectName().isEmpty())
            YesOrNotDialog->setObjectName(QStringLiteral("YesOrNotDialog"));
        YesOrNotDialog->resize(368, 200);
        YesOrNotDialog->setMinimumSize(QSize(368, 200));
        YesOrNotDialog->setMaximumSize(QSize(368, 200));
        pushButton = new QPushButton(YesOrNotDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 150, 75, 23));
        pushButton_2 = new QPushButton(YesOrNotDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 150, 75, 23));
        pushButton_3 = new QPushButton(YesOrNotDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(280, 150, 75, 23));
        instruction = new QLabel(YesOrNotDialog);
        instruction->setObjectName(QStringLiteral("instruction"));
        instruction->setGeometry(QRect(10, 30, 341, 81));

        retranslateUi(YesOrNotDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), YesOrNotDialog, SLOT(on_clicked_yes()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), YesOrNotDialog, SLOT(on_clicked_no()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), YesOrNotDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(YesOrNotDialog);
    } // setupUi

    void retranslateUi(QDialog *YesOrNotDialog)
    {
        YesOrNotDialog->setWindowTitle(QApplication::translate("YesOrNotDialog", "YesOrNotDialog", Q_NULLPTR));
        pushButton->setText(QApplication::translate("YesOrNotDialog", "Yes", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("YesOrNotDialog", "No", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("YesOrNotDialog", "Cancel", Q_NULLPTR));
        instruction->setText(QApplication::translate("YesOrNotDialog", "Instruction", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class YesOrNotDialog: public Ui_YesOrNotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YESORNOTDIALOG_H
