#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_dp.h"
#include "objmodel.h"

class DP : public QMainWindow
{
	Q_OBJECT

public:
	DP(QWidget *parent = Q_NULLPTR);

private:
	Ui::DPClass ui;
	ObjModel *obj_model;

public slots:
	void on_clicked_actionOpen();
	void on_clicked_actionColor();

	void on_checked_wiredCheckBox(bool);
	void on_checked_axisCheckBox(bool);

};
