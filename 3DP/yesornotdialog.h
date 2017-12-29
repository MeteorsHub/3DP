#pragma once

#include <QDialog>
#include "ui_yesornotdialog.h"

class YesOrNotDialog : public QDialog
{
	Q_OBJECT

public:
	YesOrNotDialog(QWidget *parent = Q_NULLPTR, QString title = "Yes Or Not");
	~YesOrNotDialog();

	void setInstruction(QString text);
	bool getYesState();

private:
	Ui::YesOrNotDialog ui;
	bool isYes;

public slots:
	void on_clicked_yes();
	void on_clicked_no();
};
