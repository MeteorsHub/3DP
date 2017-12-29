#include "dp.h"
#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "colorfileloader.h"
#include "inputdialog.h"
#include "yesornotdialog.h"

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

void DP::on_clicked_actionRegionFromPoints()
{
	QString title = "Region of Multi-Points";
	InputDialog dialog1(this, title);
	int pointNum = this->ui.mainglwidget->obj_model->getNumVertices();
	QString info = "Input the points ids (each 1 ~ ";
	info += QString::number(pointNum);
	info += ")\nEach seperated by blank space.\ni.e: 1 3 14 15";
	dialog1.setInfoText(info);

	title = "Whether to Use Strict Mode";
	YesOrNotDialog dialog2(this, title);
	info = "Whether to use strict egion selection mode?\n";
	info += "If 'Yes', only faces whose all three points\n\tare selected will be selected\n";
	info += "If 'No', faces which have two points selected\n\tat leastwill all be selected";
	dialog2.setInstruction(info);

	vector<int> pointIds(0);
	if (dialog1.exec() == QDialog::Accepted) {
		QString inputText = dialog1.getInputText();
		QStringList inputTextList = inputText.split(" ");
		inputTextList.removeDuplicates();
		for (int i = 0; i < inputTextList.size(); i++) {
			if (inputTextList.at(i).isEmpty())
				continue;
			int pointId = inputTextList.at(i).toInt();
			if (pointId < 1 || pointId > pointNum) {
				QMessageBox::warning(this, "Input Invalid Format", "Please input any integers between 1 and " + pointNum);
				return;
			}
			pointIds.push_back(pointId);
		}
		
		if (dialog2.exec() == QDialog::Accepted) {
			bool strict = dialog2.getYesState();
			this->ui.mainglwidget->regionFromPoints(pointIds, strict);
		}
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
		this->ui.mainglwidget->drawNormalLineFromFace(faceId - 1);
	}
}

void DP::on_clicked_actionAddNoise()
{
	QString title = "Add noise";
	InputDialog dialog(this, title);
	QString info = "Input the deviation (ie. 0.05)";
	dialog.setInfoText(info);
	if (dialog.exec() == QDialog::Accepted) {
		QString inputText = dialog.getInputText();
		double deviation = inputText.toDouble();
		if (deviation <= 0.0) {
			QMessageBox::warning(this, "Input Invalid Format", "Please input a double greater than 0");
			return;
		}
		this->ui.mainglwidget->addNoise(deviation);
	}
}

void DP::on_clicked_actionDenoising()
{
	this->ui.mainglwidget->deNoise();
}

void DP::on_clicked_actionMSE()
{
	double mse = this->ui.mainglwidget->computeMSE();
	QString info = "Mean Square Error (MSE) is ";
	info += QString::number(mse);
	info += ".";
	QMessageBox::information(this, "MSE", info);
}

void DP::on_clicked_actionClear()
{
	this->ui.mainglwidget->clearNoise();
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

void DP::on_checked_original(bool flag)
{
	this->ui.mainglwidget->original = flag;
	this->ui.mainglwidget->updateGL();
}

void DP::on_checked_noiseObj(bool flag)
{
	this->ui.mainglwidget->noiseObj = flag;
	this->ui.mainglwidget->updateGL();
}

void DP::on_checked_denoiseObj(bool flag)
{
	this->ui.mainglwidget->denoiseObj = flag;
	this->ui.mainglwidget->updateGL();
}

void DP::on_checked_mse(bool flag)
{
	this->ui.mainglwidget->mse = flag;
	this->ui.mainglwidget->updateGL();
}
