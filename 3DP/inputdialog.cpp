#include "inputdialog.h"

InputDialog::InputDialog(QWidget *parent, QString title)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(title);
}

InputDialog::~InputDialog()
{
}

void InputDialog::setInfoText(QString info)
{
	this->ui.infoLabel->setText(info);
}

QString InputDialog::getInputText()
{
	QString inputText = this->ui.lineEdit->text();
	return inputText;
}
