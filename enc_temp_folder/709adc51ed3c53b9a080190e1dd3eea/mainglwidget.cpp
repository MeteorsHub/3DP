#include <cmath>
#include "mainglwidget.h"
#include <GL/glut.h>
#include <QDebug>

MainGLWidget::MainGLWidget(QWidget *parent)
	:QGLWidget(parent)
{
	obj_model = nullptr;
	wired = false;
	projection_angle = 45.0;

	leftBtnClk = false;
	rightBtnClk = false;
	leftBtnLastPos = QPoint(0, 0);
	rightBtnLastPos = QPoint(0, 0);
	translated = QVector3D(0, 0, 0);
	rotated = QVector3D(0, 0, 0);
}

void MainGLWidget::bindModel(ObjModel *model)
{
	obj_model = model;
}

void MainGLWidget::initializeGL()
{
	glClearColor(0.8, 0.8, 0.8, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
}

void MainGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslated(translated.x()/100, -translated.y()/100, translated.z());
	if (obj_model != nullptr) {
		for (int i = 0; i < obj_model->getNumFaces3(); i++) {
			glColor3f(0.1, 0.1, 0.1);
			glBegin(GL_LINE_LOOP);
			glVertex3d(obj_model->faces3->at(i).v1.x, obj_model->faces3->at(i).v1.y, obj_model->faces3->at(i).v1.z);
			glVertex3d(obj_model->faces3->at(i).v2.x, obj_model->faces3->at(i).v2.y, obj_model->faces3->at(i).v2.z);
			glVertex3d(obj_model->faces3->at(i).v3.x, obj_model->faces3->at(i).v3.y, obj_model->faces3->at(i).v3.z);
			glEnd();
		}
		if (!wired) {
			for (int i = 0; i < obj_model->getNumFaces3(); i++) {
				glColor3f(0.1, 0.7, 0.1);
				glBegin(GL_TRIANGLES);
				glVertex3d(obj_model->faces3->at(i).v1.x, obj_model->faces3->at(i).v1.y, obj_model->faces3->at(i).v1.z);
				glVertex3d(obj_model->faces3->at(i).v2.x, obj_model->faces3->at(i).v2.y, obj_model->faces3->at(i).v2.z);
				glVertex3d(obj_model->faces3->at(i).v3.x, obj_model->faces3->at(i).v3.y, obj_model->faces3->at(i).v3.z);
				glEnd();
			}
		}
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	
}

void MainGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(projection_angle, (float)w / h, 0.01, 100.0);
	updateGL();
}

void MainGLWidget::mousePressEvent(QMouseEvent *event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
			leftBtnClk = true;
			leftBtnLastPos = event->pos();
			break;
	case Qt::RightButton:
			rightBtnClk = true;
			rightBtnLastPos = event->pos();
			break;
	}
	event->ignore();

}

void MainGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
			leftBtnClk = false;
			leftBtnLastPos = QPoint(0, 0);
			break;
	case Qt::RightButton:
			rightBtnClk = false;
			rightBtnLastPos = QPoint(0, 0);
			break;
	}
	event->ignore();
}

// rotate the model
void MainGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		if (leftBtnClk) {
			translated = translated + QVector3D(event->pos() - leftBtnLastPos);
			updateGL();
			qDebug() << "LeftButton:" << (event->pos() - leftBtnLastPos).x() << " " << (event->pos() - leftBtnLastPos).y();
			leftBtnLastPos = event->pos();
		}
	}
	if (event->buttons() & Qt::RightButton)
	{
		if (rightBtnClk) {
			;
		}
	}
}

// zoom the model
void MainGLWidget::wheelEvent(QWheelEvent *event)
{
	projection_angle = std::min(160.0, std::max(1.0, projection_angle - double(event->angleDelta().y()) / 60));
	qDebug() << "wheel angle: " << event->angleDelta().x() << " " << event->angleDelta().y();
	resizeGL(size().width(), size().height());
}
