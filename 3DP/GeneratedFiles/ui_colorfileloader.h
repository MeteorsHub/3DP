/********************************************************************************
** Form generated from reading UI file 'colorfileloader.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLORFILELOADER_H
#define UI_COLORFILELOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorFileLoader
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;
    QComboBox *comboBox;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *ColorFileLoader)
    {
        if (ColorFileLoader->objectName().isEmpty())
            ColorFileLoader->setObjectName(QStringLiteral("ColorFileLoader"));
        ColorFileLoader->resize(420, 250);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ColorFileLoader->sizePolicy().hasHeightForWidth());
        ColorFileLoader->setSizePolicy(sizePolicy);
        ColorFileLoader->setMinimumSize(QSize(420, 250));
        ColorFileLoader->setMaximumSize(QSize(420, 250));
        widget = new QWidget(ColorFileLoader);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(70, 60, 218, 89));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        widget1 = new QWidget(ColorFileLoader);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(220, 190, 158, 25));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(widget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(widget1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);


        retranslateUi(ColorFileLoader);
        QObject::connect(pushButton_3, SIGNAL(clicked()), ColorFileLoader, SLOT(reject()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), ColorFileLoader, SLOT(accept()));
        QObject::connect(pushButton, SIGNAL(clicked()), ColorFileLoader, SLOT(on_pushed_buttonBrose()));

        QMetaObject::connectSlotsByName(ColorFileLoader);
    } // setupUi

    void retranslateUi(QDialog *ColorFileLoader)
    {
        ColorFileLoader->setWindowTitle(QApplication::translate("ColorFileLoader", "Choose Color File", Q_NULLPTR));
        label_2->setText(QApplication::translate("ColorFileLoader", "Choose color file", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ColorFileLoader", "Brose", Q_NULLPTR));
        label->setText(QApplication::translate("ColorFileLoader", "Color mode", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("ColorFileLoader", "Original", Q_NULLPTR)
         << QApplication::translate("ColorFileLoader", "Continuous", Q_NULLPTR)
         << QApplication::translate("ColorFileLoader", "Descrete", Q_NULLPTR)
        );
        pushButton_2->setText(QApplication::translate("ColorFileLoader", "Ok", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ColorFileLoader", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ColorFileLoader: public Ui_ColorFileLoader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLORFILELOADER_H
