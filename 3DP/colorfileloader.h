#pragma once

#include <QDialog>
#include "ui_colorfileloader.h"

class ColorFileLoader : public QDialog
{
	Q_OBJECT

public:
	enum COLOR_MODE { ORIGINAL, CONTINUOUS, DISCRETE };

	ColorFileLoader(QWidget *parent = Q_NULLPTR);
	~ColorFileLoader();

	QString getColorFileName();
	COLOR_MODE getColorMode();


public slots:
	void on_pushed_buttonBrose();

private:
	Ui::ColorFileLoader ui;
};
