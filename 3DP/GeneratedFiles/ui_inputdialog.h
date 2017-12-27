/********************************************************************************
** Form generated from reading UI file 'inputdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDIALOG_H
#define UI_INPUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputDialog
{
public:
    QLabel *infoLabel;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *InputDialog)
    {
        if (InputDialog->objectName().isEmpty())
            InputDialog->setObjectName(QStringLiteral("InputDialog"));
        InputDialog->resize(325, 229);
        InputDialog->setMinimumSize(QSize(325, 229));
        InputDialog->setMaximumSize(QSize(325, 229));
        infoLabel = new QLabel(InputDialog);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        infoLabel->setGeometry(QRect(50, 50, 54, 12));
        lineEdit = new QLineEdit(InputDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 80, 201, 20));
        pushButton = new QPushButton(InputDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(130, 150, 75, 23));
        pushButton_2 = new QPushButton(InputDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 150, 75, 23));

        retranslateUi(InputDialog);
        QObject::connect(pushButton, SIGNAL(clicked()), InputDialog, SLOT(accept()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), InputDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputDialog);
    } // setupUi

    void retranslateUi(QDialog *InputDialog)
    {
        InputDialog->setWindowTitle(QApplication::translate("InputDialog", "InputDialog", Q_NULLPTR));
        infoLabel->setText(QApplication::translate("InputDialog", "Info", Q_NULLPTR));
        pushButton->setText(QApplication::translate("InputDialog", "Ok", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("InputDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InputDialog: public Ui_InputDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDIALOG_H
