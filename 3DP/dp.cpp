#include "dp.h"
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

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

void DP::on_checked_WiredCheckBox(bool wired)
{
	this->ui.mainglwidget->wired = wired;
	this->ui.mainglwidget->updateGL();
}

void DP::on_slideMoved_size(int size)
{
	this->ui.mainglwidget->projection_angle = 100.0 - size;
	QSize window_size = this->ui.mainglwidget->size();
	this->ui.mainglwidget->resizeGL(window_size.width(), window_size.height());
}
