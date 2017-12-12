#include "colorfileloader.h"
#include <QDebug>
#include <QFileDialog>

ColorFileLoader::ColorFileLoader(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

ColorFileLoader::~ColorFileLoader()
{
}

void ColorFileLoader::on_pushed_buttonBrose()
{
	QString filename = QFileDialog::getOpenFileName(this, "open color file", "C:\\", "*.txt;");
	this->ui.lineEdit->setText(filename);
}

QString ColorFileLoader::getColorFileName()
{
	return this->ui.lineEdit->text();
}

ColorFileLoader::COLOR_MODE ColorFileLoader::getColorMode()
{
	switch (this->ui.comboBox->currentIndex())
	{
	case 0:
		return ColorFileLoader::ORIGINAL;
	case 1:
		return ColorFileLoader::CONTINUOUS;
	case 2:
		return ColorFileLoader::DISCRETE;
	default:
		return ColorFileLoader::ORIGINAL;
	}
}
