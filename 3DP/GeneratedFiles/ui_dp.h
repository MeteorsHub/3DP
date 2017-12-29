/********************************************************************************
** Form generated from reading UI file 'dp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
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
    QAction *actionNeighbor_Point_of_Point;
    QAction *actionNeighbor_Face_of_Point;
    QAction *actionNeighbor_Face_of_Face;
    QAction *actionFace;
    QAction *actionDenoising;
    QAction *actionRegionFromPoints;
    QAction *actionAdd_Noise;
    QAction *actionClear;
    QAction *actionMSE;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QCheckBox *checkBox_2;
    QLabel *label_2;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QSpacerItem *verticalSpacer_2;
    MainGLWidget *mainglwidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuEdit;
    QMenu *menuSelection;
    QMenu *menuDraw;
    QMenu *menuNormal_Vector;
    QMenu *menuFunctions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DPClass)
    {
        if (DPClass->objectName().isEmpty())
            DPClass->setObjectName(QStringLiteral("DPClass"));
        DPClass->resize(941, 612);
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
        actionNeighbor_Point_of_Point = new QAction(DPClass);
        actionNeighbor_Point_of_Point->setObjectName(QStringLiteral("actionNeighbor_Point_of_Point"));
        actionNeighbor_Face_of_Point = new QAction(DPClass);
        actionNeighbor_Face_of_Point->setObjectName(QStringLiteral("actionNeighbor_Face_of_Point"));
        actionNeighbor_Face_of_Face = new QAction(DPClass);
        actionNeighbor_Face_of_Face->setObjectName(QStringLiteral("actionNeighbor_Face_of_Face"));
        actionFace = new QAction(DPClass);
        actionFace->setObjectName(QStringLiteral("actionFace"));
        actionDenoising = new QAction(DPClass);
        actionDenoising->setObjectName(QStringLiteral("actionDenoising"));
        actionRegionFromPoints = new QAction(DPClass);
        actionRegionFromPoints->setObjectName(QStringLiteral("actionRegionFromPoints"));
        actionAdd_Noise = new QAction(DPClass);
        actionAdd_Noise->setObjectName(QStringLiteral("actionAdd_Noise"));
        actionClear = new QAction(DPClass);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionMSE = new QAction(DPClass);
        actionMSE->setObjectName(QStringLiteral("actionMSE"));
        centralWidget = new QWidget(DPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
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

        checkBox_6 = new QCheckBox(centralWidget);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        checkBox_6->setChecked(true);

        verticalLayout->addWidget(checkBox_6);

        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setChecked(true);

        verticalLayout->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));
        checkBox_4->setChecked(true);

        verticalLayout->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(centralWidget);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setChecked(true);

        verticalLayout->addWidget(checkBox_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

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

        DPClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 941, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuSelection = new QMenu(menuEdit);
        menuSelection->setObjectName(QStringLiteral("menuSelection"));
        menuDraw = new QMenu(menuBar);
        menuDraw->setObjectName(QStringLiteral("menuDraw"));
        menuNormal_Vector = new QMenu(menuDraw);
        menuNormal_Vector->setObjectName(QStringLiteral("menuNormal_Vector"));
        menuFunctions = new QMenu(menuBar);
        menuFunctions->setObjectName(QStringLiteral("menuFunctions"));
        DPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DPClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DPClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DPClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DPClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuDraw->menuAction());
        menuBar->addAction(menuFunctions->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionQuit);
        menuEdit->addAction(actionColor);
        menuEdit->addAction(menuSelection->menuAction());
        menuSelection->addAction(actionNeighbor_Point_of_Point);
        menuSelection->addAction(actionNeighbor_Face_of_Point);
        menuSelection->addAction(actionNeighbor_Face_of_Face);
        menuSelection->addSeparator();
        menuSelection->addAction(actionRegionFromPoints);
        menuDraw->addAction(menuNormal_Vector->menuAction());
        menuNormal_Vector->addAction(actionFace);
        menuFunctions->addAction(actionAdd_Noise);
        menuFunctions->addAction(actionDenoising);
        menuFunctions->addAction(actionMSE);
        menuFunctions->addAction(actionClear);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionQuit);

        retranslateUi(DPClass);
        QObject::connect(actionQuit, SIGNAL(triggered()), DPClass, SLOT(close()));
        QObject::connect(actionOpen, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionOpen()));
        QObject::connect(checkBox, SIGNAL(toggled(bool)), DPClass, SLOT(on_checked_WiredCheckBox(bool)));
        QObject::connect(checkBox_2, SIGNAL(clicked(bool)), DPClass, SLOT(on_checked_axisCheckBox(bool)));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), DPClass, SLOT(on_checked_wiredCheckBox(bool)));
        QObject::connect(actionColor, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionColor()));
        QObject::connect(actionNeighbor_Point_of_Point, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionNeighborPoP()));
        QObject::connect(actionNeighbor_Face_of_Point, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionNeighborFoP()));
        QObject::connect(actionNeighbor_Face_of_Face, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionNeighborFoF()));
        QObject::connect(actionFace, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionNormalFromFace()));
        QObject::connect(actionRegionFromPoints, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionRegionFromPoints()));
        QObject::connect(actionAdd_Noise, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionAddNoise()));
        QObject::connect(actionDenoising, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionDenoising()));
        QObject::connect(actionClear, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionClear()));
        QObject::connect(checkBox_3, SIGNAL(toggled(bool)), DPClass, SLOT(on_checked_noiseObj(bool)));
        QObject::connect(checkBox_4, SIGNAL(toggled(bool)), DPClass, SLOT(on_checked_denoiseObj(bool)));
        QObject::connect(checkBox_5, SIGNAL(toggled(bool)), DPClass, SLOT(on_checked_mse(bool)));
        QObject::connect(checkBox_6, SIGNAL(toggled(bool)), DPClass, SLOT(on_checked_original(bool)));
        QObject::connect(actionMSE, SIGNAL(triggered()), DPClass, SLOT(on_clicked_actionMSE()));

        QMetaObject::connectSlotsByName(DPClass);
    } // setupUi

    void retranslateUi(QMainWindow *DPClass)
    {
        DPClass->setWindowTitle(QApplication::translate("DPClass", "3DP", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("DPClass", "Open", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("DPClass", "Quit", Q_NULLPTR));
        actionColor->setText(QApplication::translate("DPClass", "Color", Q_NULLPTR));
        actionNeighbor_Point_of_Point->setText(QApplication::translate("DPClass", "Neighbor Points of a Point", Q_NULLPTR));
        actionNeighbor_Face_of_Point->setText(QApplication::translate("DPClass", "Neighbor Faces of a Point", Q_NULLPTR));
        actionNeighbor_Face_of_Face->setText(QApplication::translate("DPClass", "Neighbor Faces of a Face", Q_NULLPTR));
        actionFace->setText(QApplication::translate("DPClass", "From Face", Q_NULLPTR));
        actionDenoising->setText(QApplication::translate("DPClass", "Denoising", Q_NULLPTR));
        actionRegionFromPoints->setText(QApplication::translate("DPClass", "Region from Points", Q_NULLPTR));
        actionAdd_Noise->setText(QApplication::translate("DPClass", "Add Noise", Q_NULLPTR));
        actionClear->setText(QApplication::translate("DPClass", "Clear", Q_NULLPTR));
        actionMSE->setText(QApplication::translate("DPClass", "MSE", Q_NULLPTR));
        label->setText(QApplication::translate("DPClass", "Axis", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("DPClass", "Display", Q_NULLPTR));
        label_2->setText(QApplication::translate("DPClass", "Wire", Q_NULLPTR));
        checkBox->setText(QApplication::translate("DPClass", "Wired", Q_NULLPTR));
        checkBox_6->setText(QApplication::translate("DPClass", "Original", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("DPClass", "noise obj", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("DPClass", "denoise obj", Q_NULLPTR));
        checkBox_5->setText(QApplication::translate("DPClass", "MSE", Q_NULLPTR));
        menu->setTitle(QApplication::translate("DPClass", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("DPClass", "Edit", Q_NULLPTR));
        menuSelection->setTitle(QApplication::translate("DPClass", "Selection", Q_NULLPTR));
        menuDraw->setTitle(QApplication::translate("DPClass", "Draw", Q_NULLPTR));
        menuNormal_Vector->setTitle(QApplication::translate("DPClass", "Normal Vector", Q_NULLPTR));
        menuFunctions->setTitle(QApplication::translate("DPClass", "Functions", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DPClass: public Ui_DPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DP_H
