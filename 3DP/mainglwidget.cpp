#define _USE_MATH_DEFINES
#include <cmath>
#include "mainglwidget.h"
#include <GL/glut.h>
#include <QDebug>

using namespace std;

MainGLWidget::MainGLWidget(QWidget *parent)
	:QGLWidget(parent)
{
	obj_model = new ObjModel();
	toggleWired = false;
	toggleAxis = true;
	noiseObj = true;
	denoiseObj = true;
	mse = true;
	original = true;

	leftBtnClk = false;
	leftBtnLastPos = QPoint(0, 0);
	lines = vector<line>(0);

	cameraAngle = 40.0;
	cameraRadius = 4.0;
	theta = 70.0;
	phi = 30.0;
}

bool MainGLWidget::bindModel(ObjModel *model)
{
	obj_model = model;
	lines = vector<line>(0);
	return true;
}

bool MainGLWidget::loadColor(QString filename)
{
	lines = vector<line>(0);
	return this->obj_model->loadColorFile(filename);
}

bool MainGLWidget::setColorMode(ColorFileLoader::COLOR_MODE mode)
{
	lines = vector<line>(0);
	return this->obj_model->setColorMode(mode);
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
		// vertice selections
		if (obj_model->verticesColor1->size() != 0) {
			glColor3f(0.9, 0.1, 0.1);
			for (int i = 0; i < obj_model->verticesColor1->size(); i++) {
				glPushMatrix();
				vertice point = obj_model->verticesColor1->at(i);
				glTranslatef(point.x, point.y, point.z);
				glutSolidSphere(0.005, 20, 20);
				glPopMatrix();
			}
		}
		if (obj_model->verticesColor2->size() != 0) {
			glColor3f(0.1, 0.1, 0.9);
			for (int i = 0; i < obj_model->verticesColor2->size(); i++) {
				glPushMatrix();
				vertice point = obj_model->verticesColor2->at(i);
				glTranslatef(point.x, point.y, point.z);
				glutSolidSphere(0.002, 20, 20);
				glPopMatrix();
			}
		}
		// face selections
		if (obj_model->faces3Color1->size() != 0) {
			glColor3f(0.1, 0.1, 0.9);
			for (int i = 0; i < obj_model->faces3Color1->size(); i++) {
				face3 face = obj_model->faces3Color1->at(i);
				glBegin(GL_TRIANGLES);
				glVertex3d(face.v1.x, face.v1.y, face.v1.z);
				glVertex3d(face.v2.x, face.v2.y, face.v2.z);
				glVertex3d(face.v3.x, face.v3.y, face.v3.z);
				glEnd();
			}
		}
		if (obj_model->faces3Color2->size() != 0) {
			glColor3f(0.1, 0.9, 0.5);
			for (int i = 0; i < obj_model->faces3Color2->size(); i++) {
				face3 face = obj_model->faces3Color2->at(i);
				glBegin(GL_TRIANGLES);
				glVertex3d(face.v1.x, face.v1.y, face.v1.z);
				glVertex3d(face.v2.x, face.v2.y, face.v2.z);
				glVertex3d(face.v3.x, face.v3.y, face.v3.z);
				glEnd();
			}
		}
		// line drawing
		for (int i = 0; i < lines.size(); i++) {
			glColor3f(0.95, 0.2, 0.3);
			glBegin(GL_LINES);
			glVertex3f(lines.at(i).v1.x, lines.at(i).v1.y, lines.at(i).v1.z);
			glVertex3f(lines.at(i).v2.x, lines.at(i).v2.y, lines.at(i).v2.z);
			glEnd();
		}
		// original obj
		if (original) {
			glColor3f(0.1, 0.1, 0.1);
			for (int i = 0; i < obj_model->getNumFaces3(); i++) {
				glBegin(GL_LINE_LOOP);
				glVertex3d(obj_model->faces3->at(i).v1.x, obj_model->faces3->at(i).v1.y, obj_model->faces3->at(i).v1.z);
				glVertex3d(obj_model->faces3->at(i).v2.x, obj_model->faces3->at(i).v2.y, obj_model->faces3->at(i).v2.z);
				glVertex3d(obj_model->faces3->at(i).v3.x, obj_model->faces3->at(i).v3.y, obj_model->faces3->at(i).v3.z);
				glEnd();
			}
			if (!toggleWired) {
				for (int i = 0; i < obj_model->getNumFaces3(); i++) {
					if (obj_model->getNumColor() != 0) {
						color3f c = obj_model->color3->at(i);
						glColor3f(c.red, c.green, c.blue);
					}
					else glColor3f(0.1, 0.7, 0.1);
					glBegin(GL_TRIANGLES);
					glVertex3d(obj_model->faces3->at(i).v1.x, obj_model->faces3->at(i).v1.y, obj_model->faces3->at(i).v1.z);
					glVertex3d(obj_model->faces3->at(i).v2.x, obj_model->faces3->at(i).v2.y, obj_model->faces3->at(i).v2.z);
					glVertex3d(obj_model->faces3->at(i).v3.x, obj_model->faces3->at(i).v3.y, obj_model->faces3->at(i).v3.z);
					glEnd();
				}
			}
		}
		// noise drawing
		if (noiseObj && obj_model->faces3Noise->size() != 0) {
			glColor3f(0.1, 0.1, 0.1);
			for (int i = 0; i < obj_model->getNumFaces3(); i++) {
				glBegin(GL_LINE_LOOP);
				glVertex3d(obj_model->faces3Noise->at(i).v1.x, obj_model->faces3Noise->at(i).v1.y, obj_model->faces3Noise->at(i).v1.z);
				glVertex3d(obj_model->faces3Noise->at(i).v2.x, obj_model->faces3Noise->at(i).v2.y, obj_model->faces3Noise->at(i).v2.z);
				glVertex3d(obj_model->faces3Noise->at(i).v3.x, obj_model->faces3Noise->at(i).v3.y, obj_model->faces3Noise->at(i).v3.z);
				glEnd();
			}
			for (int i = 0; i < obj_model->faces3Noise->size(); i++) {
				glColor3f(0.7, 0.7, 0.1);
				glBegin(GL_TRIANGLES);
				glVertex3d(obj_model->faces3Noise->at(i).v1.x, obj_model->faces3Noise->at(i).v1.y, obj_model->faces3Noise->at(i).v1.z);
				glVertex3d(obj_model->faces3Noise->at(i).v2.x, obj_model->faces3Noise->at(i).v2.y, obj_model->faces3Noise->at(i).v2.z);
				glVertex3d(obj_model->faces3Noise->at(i).v3.x, obj_model->faces3Noise->at(i).v3.y, obj_model->faces3Noise->at(i).v3.z);
				glEnd();
			}
		}
		// denoise drawing
		if (denoiseObj && obj_model->faces3Denoise->size() != 0) {
			glColor3f(0.1, 0.1, 0.1);
			for (int i = 0; i < obj_model->getNumFaces3(); i++) {
				glBegin(GL_LINE_LOOP);
				glVertex3d(obj_model->faces3Denoise->at(i).v1.x, obj_model->faces3Denoise->at(i).v1.y, obj_model->faces3Denoise->at(i).v1.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v2.x, obj_model->faces3Denoise->at(i).v2.y, obj_model->faces3Denoise->at(i).v2.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v3.x, obj_model->faces3Denoise->at(i).v3.y, obj_model->faces3Denoise->at(i).v3.z);
				glEnd();
			}
			for (int i = 0; i < obj_model->faces3Denoise->size(); i++) {
				glColor3f(0.7, 0.1, 0.7);
				glBegin(GL_TRIANGLES);
				glVertex3d(obj_model->faces3Denoise->at(i).v1.x, obj_model->faces3Denoise->at(i).v1.y, obj_model->faces3Denoise->at(i).v1.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v2.x, obj_model->faces3Denoise->at(i).v2.y, obj_model->faces3Denoise->at(i).v2.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v3.x, obj_model->faces3Denoise->at(i).v3.y, obj_model->faces3Denoise->at(i).v3.z);
				glEnd();
			}
		}
		// mse drawing
		if (mse && obj_model->mseColor3->size() != 0) {
			glColor3f(0.1, 0.1, 0.1);
			for (int i = 0; i < obj_model->getNumFaces3(); i++) {
				glBegin(GL_LINE_LOOP);
				glVertex3d(obj_model->faces3Denoise->at(i).v1.x, obj_model->faces3Denoise->at(i).v1.y, obj_model->faces3Denoise->at(i).v1.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v2.x, obj_model->faces3Denoise->at(i).v2.y, obj_model->faces3Denoise->at(i).v2.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v3.x, obj_model->faces3Denoise->at(i).v3.y, obj_model->faces3Denoise->at(i).v3.z);
				glEnd();
			}
			for (int i = 0; i < obj_model->mseColor3->size(); i++) {
				glColor3f(obj_model->mseColor3->at(i).red, obj_model->mseColor3->at(i).green, obj_model->mseColor3->at(i).blue);
				glBegin(GL_TRIANGLES);
				glVertex3d(obj_model->faces3Denoise->at(i).v1.x, obj_model->faces3Denoise->at(i).v1.y, obj_model->faces3Denoise->at(i).v1.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v2.x, obj_model->faces3Denoise->at(i).v2.y, obj_model->faces3Denoise->at(i).v2.z);
				glVertex3d(obj_model->faces3Denoise->at(i).v3.x, obj_model->faces3Denoise->at(i).v3.y, obj_model->faces3Denoise->at(i).v3.z);
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

void MainGLWidget::neighborPoP(int pId)
{
	lines = vector<line>(0);
	obj_model->neighborPoP(pId);
	updateGL();
}

void MainGLWidget::neighborFoP(int pId)
{
	lines = vector<line>(0);
	obj_model->neighborFoP(pId);
	updateGL();
}

void MainGLWidget::neighborFoF(int fId)
{
	lines = vector<line>(0);
	obj_model->neighborFoF(fId);
	updateGL();
}

void MainGLWidget::regionFromPoints(vector<int> pIds, bool strict)
{
	lines = vector<line>(0);
	obj_model->regionFromPoints(pIds, strict);
	updateGL();
}

void MainGLWidget::drawNormalLineFromFace(int fId)
{
	lines = vector<line>(0);
	line norm = obj_model->getNormalLineFromFace(fId);
	lines.push_back(norm);
	updateGL();
}

void MainGLWidget::addNoise(double deviation)
{
	obj_model->addNoise(deviation);
	updateGL();
}

void MainGLWidget::deNoise()
{
	obj_model->deNoise();
	updateGL();
}

double MainGLWidget::computeMSE()
{
	double mse = obj_model->computeMSE();
	updateGL();
	return mse;
}

void MainGLWidget::clearNoise()
{
	obj_model->clearNoise();
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
