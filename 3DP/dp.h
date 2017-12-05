#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_dp.h"

class DP : public QMainWindow
{
	Q_OBJECT

public:
	DP(QWidget *parent = Q_NULLPTR);

private:
	Ui::DPClass ui;
};
