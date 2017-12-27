#include "dp.h"
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "colorfileloader.h"
#include "inputdialog.h"

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
	ColorFileLoader dialog(this);
	if (dialog.exec() == QDialog::Accepted) {
		this->ui.mainglwidget->setColorMode(dialog.getColorMode());
		if (!this->ui.mainglwidget->loadColor(dialog.getColorFileName())) {
			QString msg = "File ";
			msg += dialog.getColorFileName() + " cannot be loaded";
			QMessageBox::warning(this, "Color loading failed", msg);
		}
		this->ui.mainglwidget->updateGL();
	}
}

void DP::on_clicked_actionNeighborPoP()
{
	QString title = "Neighbor Points of a Point";
	InputDialog dialog(this, title);
	int pointNum = this->ui.mainglwidget->obj_model->getNumVertices();
	QString info = "Input the point id (1 ~ ";
	info += QString::number(pointNum);
	info += ")";
	dialog.setInfoText(info);
	if (dialog.exec() == QDialog::Accepted) {
		QString inputText = dialog.getInputText();
		int pointId = inputText.toInt();
		if (pointId < 1 || pointId > pointNum) {
			QMessageBox::warning(this, "Input Invalid Format", "Please input an integer between 1 and " + pointNum);
			return;
		}
		this->ui.mainglwidget->neighborPoP(pointId - 1);
	}
}

void DP::on_clicked_actionNeighborFoP()
{
	QString title = "Neighbor Faces of a Point";
	InputDialog dialog(this, title);
	int pointNum = this->ui.mainglwidget->obj_model->getNumVertices();
	QString info = "Input the point id (1 ~ ";
	info += QString::number(pointNum);
	info += ")";
	dialog.setInfoText(info);
	if (dialog.exec() == QDialog::Accepted) {
		QString inputText = dialog.getInputText();
		int pointId = inputText.toInt();
		if (pointId < 1 || pointId > pointNum) {
			QMessageBox::warning(this, "Input Invalid Format", "Please input an integer between 1 and " + pointNum);
			return;
		}
		this->ui.mainglwidget->neighborFoP(pointId - 1);
	}
}

void DP::on_clicked_actionNeighborFoF()
{
	QString title = "Neighbor Faces of a Face";
	InputDialog dialog(this, title);
	int faceNum = this->ui.mainglwidget->obj_model->getNumFaces3();
	QString info = "Input the face id (1 ~ ";
	info += QString::number(faceNum);
	info += ")";
	dialog.setInfoText(info);
	if (dialog.exec() == QDialog::Accepted) {
		QString inputText = dialog.getInputText();
		int faceId = inputText.toInt();
		if (faceId < 1 || faceId > faceNum) {
			QMessageBox::warning(this, "Input Invalid Format", "Please input an integer between 1 and " + faceNum);
			return;
		}
		this->ui.mainglwidget->neighborFoF(faceId - 1);
	}
}

void DP::on_clicked_actionNormalFromFace()
{
	QString title = "Nromal line of a Face";
	InputDialog dialog(this, title);
	int faceNum = this->ui.mainglwidget->obj_model->getNumFaces3();
	QString info = "Input the face id (1 ~ ";
	info += QString::number(faceNum);
	info += ")";
	dialog.setInfoText(info);
	if (dialog.exec() == QDialog::Accepted) {
		QString inputText = dialog.getInputText();
		int faceId = inputText.toInt();
		if (faceId < 1 || faceId > faceNum) {
			QMessageBox::warning(this, "Input Invalid Format", "Please input an integer between 1 and " + faceNum);
			return;
		}
		this->ui.mainglwidget->drawNormalLineFromFace(faceId);
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
