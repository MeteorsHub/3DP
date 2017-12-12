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

	void bindModel(ObjModel*);

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int, int) override;

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
};
