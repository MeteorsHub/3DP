/********************************************************************************
** Form generated from reading UI file 'yesornotdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
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

QT_BEGIN_NAMESPACE

class Ui_YesOrNotDialog
{
public:

    void setupUi(QDialog *YesOrNotDialog)
    {
        if (YesOrNotDialog->objectName().isEmpty())
            YesOrNotDialog->setObjectName(QStringLiteral("YesOrNotDialog"));
        YesOrNotDialog->resize(400, 300);

        retranslateUi(YesOrNotDialog);

        QMetaObject::connectSlotsByName(YesOrNotDialog);
    } // setupUi

    void retranslateUi(QDialog *YesOrNotDialog)
    {
        YesOrNotDialog->setWindowTitle(QApplication::translate("YesOrNotDialog", "YesOrNotDialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class YesOrNotDialog: public Ui_YesOrNotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YESORNOTDIALOG_H
