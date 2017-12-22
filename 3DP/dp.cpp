#include "dp.h"
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "colorfileloader.h"

DP::DP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	obj_model = new ObjModel();
}


void DP::on_clicked_actionOpen() {
	QString filename = QFileDialog::getOpenFileName(this, "open obj or off  model file", "C:\\", "*.obj;*.off");
	if (filename.endsWith(".obj")) {
		if (!this->obj_model->loadObjFile(filename))
		{
			QString msg = "File ";
			msg += filename + " cannot open";
			QMessageBox::warning(this, "File cannot open", msg);
		}
	}
	else if (filename.endsWith(".off")) {
		if (!this->obj_model->loadOffFile(filename))
		{
			QString msg = "File ";
			msg += filename + " cannot open";
			QMessageBox::warning(this, "File cannot open", msg);
		}
	}
	this->ui.mainglwidget->bindModel(this->obj_model);
	this->ui.mainglwidget->updateGL();
	qDebug() << "Number of vertices is " << this->obj_model->getNumVertices();
	qDebug() << "Number of faces3 is " << this->obj_model->getNumFaces3();
}

void DP::on_clicked_actionColor() 
{
	ColorFileLoader dialog;
	if (dialog.exec() == QDialog::Accepted) {
		this->ui.mainglwidget->setColorMode(dialog.getColorMode());
		if (!this->ui.mainglwidget->loadColor(dialog.getColorFileName())) {
			QString msg = "File ";
			msg += dialog.getColorFileName() + " cannot open";
			QMessageBox::warning(this, "Color loading failed", msg);
		}
		this->ui.mainglwidget->updateGL();
	}
}

void DP::on_checked_wiredCheckBox(bool wired)
{
	this->ui.mainglwidget->toggleWired = wired;
	this->ui.mainglwidget->updateGL();
}

void DP::on_checked_axisCheckBox(bool axis)
{
	this->ui.mainglwidget->toggleAxis = axis;
	this->ui.mainglwidget->updateGL();
}
