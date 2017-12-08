#include "objmodel.h"
#include <QTextStream>
#include <QDebug>

ObjModel::ObjModel()
{
	this->vertices = new vector<vertice>(0);
	this->faces3 = new vector<face3>(0);
}

ObjModel::~ObjModel()
{
	delete this->faces3;
	delete this->vertices;
	this->faces3 = nullptr;
	this->vertices = nullptr;
}


bool ObjModel::loadObjFile(QString filename) {
	QFile file(filename);

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return false;
	}
	if (getNumVertices() != 0) {
		delete vertices, faces3;
		this->vertices = new vector<vertice>(0);
		this->faces3 = new vector<face3>(0);
	}
	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		if (line.startsWith("#") || line.isEmpty() || line.isNull()) {
			continue;
		}
		if (line.startsWith("v ")) {
			QStringList list = line.split(" ", QString::SkipEmptyParts);
			if (list.size() != 4) {
				file.close();
				return false;
			}
			vertice v;
			v.x = list[1].toDouble();
			v.y = list[2].toDouble();
			v.z = list[3].toDouble();
			this->vertices->push_back(v);
		}
		else if (line.startsWith("f ")) {
			QStringList list = line.split(" ", QString::SkipEmptyParts);
			if (list.size() != 4) {
				file.close();
				return false;
			}
			face3 f3;
			f3.v1 = this->vertices->at(list[1].toInt() - 1);
			f3.v2 = this->vertices->at(list[2].toInt() - 1);
			f3.v3 = this->vertices->at(list[3].toInt() - 1);
			this->faces3->push_back(f3);
		}
		else {
			qDebug() << "unknown line of obj file " << line;
		}
	}
	file.close();
	return true;

}

bool ObjModel::loadColorFile(QString)
{
	return false;
}

bool ObjModel::loadOffFile(QString filename)
{
	QFile file(filename);

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return false;
	}

	if (getNumVertices() != 0) {
		delete vertices, faces3;
		this->vertices = new vector<vertice>(0);
		this->faces3 = new vector<face3>(0);
	}
	QTextStream in(&file);
	if (in.readLine() != "OFF") {
		file.close();
		return false;
	}
	QString line = in.readLine();
	QStringList list = line.split(" ");
	int vn = list[0].toInt();
	int fn = list[1].toInt();
	for (int i = 0; i < vn; i++) {
		QString line = in.readLine();
		QStringList list = line.split(" ", QString::SkipEmptyParts);
		if (list.size() != 3) {
			file.close();
			return false;
		}
		vertice v;
		v.x = list[0].toDouble();
		v.y = list[1].toDouble();
		v.z = list[2].toDouble();
		this->vertices->push_back(v);
	}
	for (int i = 0; i < fn; i++) {
		QString line = in.readLine();
		QStringList list = line.split(" ", QString::SkipEmptyParts);
		if (list.size() != 4 || list[0] != "3") {
			file.close();
			return false;
		}
		face3 f3;
		f3.v1 = this->vertices->at(list[1].toInt());
		f3.v2 = this->vertices->at(list[2].toInt());
		f3.v3 = this->vertices->at(list[3].toInt());
		this->faces3->push_back(f3);
	}
	file.close();
	return true;
}

int ObjModel::getNumVertices()
{
	return this->vertices->size();
}

int ObjModel::getNumFaces3()
{
	return this->faces3->size();
}
