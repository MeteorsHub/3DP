#pragma once

#include <QDialog>
#include "ui_yesornotdialog.h"

class YesOrNotDialog : public QDialog
{
	Q_OBJECT

public:
	YesOrNotDialog(QWidget *parent = Q_NULLPTR);
	~YesOrNotDialog();

private:
	Ui::YesOrNotDialog ui;
};
