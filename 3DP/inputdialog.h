#pragma once

#include <QDialog>
#include "ui_inputdialog.h"

class InputDialog : public QDialog
{
	Q_OBJECT

public:
	InputDialog(QWidget *parent = Q_NULLPTR);
	~InputDialog();

	void setInfoText(QString);
	QString getInputText();

private:
	Ui::InputDialog ui;
};
