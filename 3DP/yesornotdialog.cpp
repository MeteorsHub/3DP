#include "yesornotdialog.h"

YesOrNotDialog::YesOrNotDialog(QWidget *parent, QString title)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(title);
	isYes = false;
}

YesOrNotDialog::~YesOrNotDialog()
{
}

void YesOrNotDialog::setInstruction(QString text)
{
	this->ui.instruction->setText(text);
}

bool YesOrNotDialog::getYesState()
{
	return isYes;
}

void YesOrNotDialog::on_clicked_no()
{
	isYes = false;
	this->accept();
}

void YesOrNotDialog::on_clicked_yes()
{
	isYes = true;
	this->accept();
}

