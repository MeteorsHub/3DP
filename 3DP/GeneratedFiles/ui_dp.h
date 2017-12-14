/********************************************************************************
** Form generated from reading UI file 'dp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DP_H
#define UI_DP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_DPClass
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionColor;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    MainGLWidget *mainglwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QCheckBox *checkBox_2;
    QLabel *label_2;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DPClass)
    {
        if (DPClass->objectName().isEmpty())
            DPClass->setObjectName(QStringLiteral("DPClass"));
        DPClass->resize(767, 543);
        actionOpen = new QAction(DPClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/Resources/icon/open-folder-with-document.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionQuit = new QAction(DPClass);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/Resources/icon/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon1);
        actionColor = new QAction(DPClass);
        actionColor->setObjectName(QStringLiteral("actionColor"));
        centralWidget = new QWidget(DPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mainglwidget = new MainGLWidget(centralWidget);
        mainglwidget->setObjectName(QStringLiteral("mainglwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainglwidget->sizePolicy().hasHeightForWidth());
        mainglwidget->setSizePolicy(sizePolicy);
        mainglwidget->setMouseTracking(false);
        mainglwidget->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(mainglwidget, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setChecked(true);

        verticalLayout->addWidget(checkBox_2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        DPClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 767, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        DPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DPClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DPClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DPClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DPClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionQuit);
        menuEdit->addAction(actionColor);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionQuit);

        retranslateUi(DPClass);
        QObject::connect(actionQuit, SIGNAL(triggered()), DPClass, SLOT(close()));
        QObject::connect(actionOpen, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionOpen()));
        QObject::connect(checkBox, SIGNAL(toggled(bool)), DPClass, SLOT(on_checked_WiredCheckBox(bool)));
        QObject::connect(checkBox_2, SIGNAL(clicked(bool)), DPClass, SLOT(on_checked_axisCheckBox(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), DPClass, SLOT(on_checked_wiredCheckBox(bool)));
        QObject::connect(actionColor, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionColor()));

        QMetaObject::connectSlotsByName(DPClass);
    } // setupUi

    void retranslateUi(QMainWindow *DPClass)
    {
        DPClass->setWindowTitle(QApplication::translate("DPClass", "3DP", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("DPClass", "Open", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("DPClass", "Quit", Q_NULLPTR));
        actionColor->setText(QApplication::translate("DPClass", "Color", Q_NULLPTR));
        label->setText(QApplication::translate("DPClass", "Axis", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("DPClass", "Display", Q_NULLPTR));
        label_2->setText(QApplication::translate("DPClass", "Wire", Q_NULLPTR));
        checkBox->setText(QApplication::translate("DPClass", "Wired", Q_NULLPTR));
        menu->setTitle(QApplication::translate("DPClass", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("DPClass", "Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DPClass: public Ui_DPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DP_H
