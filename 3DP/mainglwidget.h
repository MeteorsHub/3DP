#pragma once
#include <QGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QVector3D>
#include "objmodel.h"

class MainGLWidget: public QGLWidget
{
	Q_OBJECT
public:
	explicit MainGLWidget(QWidget *parent = nullptr);

	bool bindModel(ObjModel*);
	bool loadColor(QString);
	bool setColorMode(ColorFileLoader::COLOR_MODE);

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int, int) override;

	void neighborPoP(int pId);
	void neighborFoP(int pId);
	void neighborFoF(int fId);
	void drawNormalLineFromFace(int fId);

	void mousePressEvent(QMouseEvent*) override;
	void mouseReleaseEvent(QMouseEvent*) override;
	void mouseMoveEvent(QMouseEvent*) override;
	void wheelEvent(QWheelEvent*) override;

	ObjModel *obj_model;
	bool toggleWired;
	bool toggleAxis;

protected:
	

private:
	QTimer timer;
	bool leftBtnClk;
	QPoint leftBtnLastPos;

	GLfloat cameraAngle;
	GLfloat cameraRadius;
	GLfloat theta;
	GLfloat phi;
	vector<line> lines;
};
