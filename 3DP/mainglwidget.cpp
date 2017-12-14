#define _USE_MATH_DEFINES
#include <cmath>
#include "mainglwidget.h"
#include <GL/glut.h>
#include <QDebug>

using namespace std;

MainGLWidget::MainGLWidget(QWidget *parent)
	:QGLWidget(parent)
{
	obj_model = nullptr;
	toggleWired = false;
	toggleAxis = true;

	leftBtnClk = false;
	leftBtnLastPos = QPoint(0, 0);

	cameraAngle = 40.0;
	cameraRadius = 4.0;
	theta = 70.0;
	phi = 30.0;
}

void MainGLWidget::bindModel(ObjModel *model)
{
	obj_model = model;
}

void MainGLWidget::initializeGL()
{
	glClearColor(0.8, 0.8, 0.8, 1);
	glEnable(GL_DEPTH_TEST);
	//GLfloat lightPos[4] = { 0, 1, 0, 1 };
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	//glEnable(GL_LIGHT0);
	GLfloat lmodel_ambient[] = { 0.7,0.7,0.7,1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
}

void MainGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	GLfloat cmrX = cameraRadius * sinf(M_PI*theta/180.0) * sinf(M_PI*phi/180.0);
	GLfloat cmrY = cameraRadius * cosf(M_PI*theta/180.0);
	GLfloat cmrZ = cameraRadius * sinf(M_PI*theta/180.0) * cosf(M_PI*phi/180.0);
	gluLookAt(cmrX, cmrY, cmrZ, 0, 0, 0, 0, 1, 0);

	if (toggleAxis) {
		/*  Length of axes */
		double len = 2.0;
		glColor3f(0.1, 0.1, 0.7);
		glBegin(GL_LINES);
		glVertex3d(0, 0, 0);
		glVertex3d(len, 0, 0);
		glVertex3d(0, 0, 0);
		glVertex3d(0, len, 0);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, len);
		glEnd();

	}
	if (obj_model != nullptr) {
		for (int i = 0; i < obj_model->getNumFaces3(); i++) {
			glColor3f(0.1, 0.1, 0.1);
			glBegin(GL_LINE_LOOP);
			glVertex3d(obj_model->faces3->at(i).v1.x, obj_model->faces3->at(i).v1.y, obj_model->faces3->at(i).v1.z);
			glVertex3d(obj_model->faces3->at(i).v2.x, obj_model->faces3->at(i).v2.y, obj_model->faces3->at(i).v2.z);
			glVertex3d(obj_model->faces3->at(i).v3.x, obj_model->faces3->at(i).v3.y, obj_model->faces3->at(i).v3.z);
			glEnd();
		}
		if (!toggleWired) {
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
	
}

void MainGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cameraAngle, float(w) / float(h), 0.01, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	updateGL();
}

void MainGLWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		leftBtnClk = true;
		leftBtnLastPos = event->pos();
	}
	event->ignore();

}

void MainGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		leftBtnClk = false;
		leftBtnLastPos = QPoint(0, 0);
	}
	event->ignore();
}

// rotate the model
void MainGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		if (leftBtnClk) {
			QPoint movement = event->pos() - leftBtnLastPos;
			theta = min(179.9f, max(0.1f, theta - 0.5f*movement.y()));
			phi = phi - 0.5f*movement.x();
			updateGL();
			qDebug() << "LeftButton:" << (event->pos() - leftBtnLastPos).x() << " " << (event->pos() - leftBtnLastPos).y();
			leftBtnLastPos = event->pos();
		}
	}
}

// zoom the model
void MainGLWidget::wheelEvent(QWheelEvent *event)
{
	cameraAngle = min(150.0f, max(0.1f, cameraAngle - event->angleDelta().y() / 60.0f));
	resizeGL(size().width(), size().height());
	qDebug() << "wheel angle: " << event->angleDelta().x() << " " << event->angleDelta().y();
}
