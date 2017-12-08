#pragma once
#include <QGLWidget>
#include <QTimer>
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

	ObjModel *obj_model;
	bool wired;
	double projection_angle;

private:
	QTimer timer;
};
