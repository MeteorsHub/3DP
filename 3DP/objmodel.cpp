#include "objmodel.h"
#include <QTextStream>
#include <QDebug>

ObjModel::ObjModel()
{
	this->vertices = new vector<vertice>(0);
	this->faces3 = new vector<face3>(0);
	this->color = new vector<float>(0);
	this->color3 = new vector<color3f>(0);
	this->colorMode = ColorFileLoader::ORIGINAL;
}

ObjModel::~ObjModel()
{
	delete this->faces3;
	delete this->vertices;
	delete this->color;
	delete this->color3;
	this->faces3 = nullptr;
	this->vertices = nullptr;
	this->color = nullptr;
	this->color3 = nullptr;
}


bool ObjModel::loadObjFile(QString filename) {
	QFile file(filename);

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		file.close();
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
	setColor3f();
	file.close();
	return true;

}

bool ObjModel::loadColorFile(QString filename)
{
	if (filename.isEmpty()) {
		setColor3f();
		return true;
	}
	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		file.close();
		return false;
	}
	if (getNumColor() != 0) {
		delete color;
		this->color = new vector<float>(0);
	}
	QTextStream in(&file);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		float colorLine = line.toFloat();
		this->color->push_back(colorLine);
	}
	if (getNumColor() != getNumFaces3()) {
		delete color;
		this->color = new vector<float>(0);
		file.close();
		return false;
	}
	setColor3f();
	file.close();
	return true;
}

bool ObjModel::setColorMode(ColorFileLoader::COLOR_MODE mode)
{
	this->colorMode = mode;
	return true;
}

void ObjModel::setColor3f()
{
	if (getNumColor() == 0) {
		for (int i = 0; i < getNumFaces3(); i++) {
			float *c = getColor3f(1.0f);
			color3f cf = { c[0], c[1], c[2] };
			color3->push_back(cf);
		}
	}
	else {
		color3->clear();
		for (int i = 0; i < getNumColor(); i++) {
			float *c = getColor3f(color->at(i));
			color3f cf = { c[0], c[1], c[2] };
			color3->push_back(cf);
		}
	}
}

bool ObjModel::loadOffFile(QString filename)
{
	QFile file(filename);

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		file.close();
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
	setColor3f();
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

int ObjModel::getNumColor()
{
	return this->color->size();
}

float * ObjModel::getColor3f(float grayScale)
{
	float* color3f = new float[3];
	auto interpolate = [](float val, float y0, float x0, float y1, float x1) {
		return (val - x0)*(y1 - y0) / (x1 - x0) + y0;
	};

	auto base = [interpolate](float val) {
		if (val <= -0.75) return 0.0f;
		else if (val <= -0.25) return interpolate(val, 0.0, -0.75, 1.0, -0.25);
		else if (val <= 0.25) return 1.0f;
		else if (val <= 0.75) return interpolate(val, 1.0, 0.25, 0.0, 0.75);
		else return 0.0f;
	};

	auto red = [base](float gray) {
		return base(gray - 0.5f);
	};
	auto green = [base](float gray) {
		return base(gray);
	};
	auto blue = [base](float gray) {
		return base(gray + 0.5f);
	};

	switch (this->colorMode)
	{
	case ColorFileLoader::ORIGINAL:
		color3f[0] = 0.1;
		color3f[1] = 0.7;
		color3f[2] = 0.1;
		return color3f;
	case ColorFileLoader::CONTINUOUS:
		grayScale = this->transformColorGray(grayScale);
		color3f[0] = red(grayScale);
		color3f[1] = green(grayScale);
		color3f[2] = blue(grayScale);
		return color3f;
	case ColorFileLoader::DISCRETE:
		grayScale = this->transformColorGray(std::roundf(grayScale));
		color3f[0] = red(grayScale);
		color3f[1] = green(grayScale);
		color3f[2] = blue(grayScale);
		return color3f;
	default:
		color3f[0] = 0.1;
		color3f[1] = 0.7;
		color3f[2] = 0.1;
		return color3f;
	}
}

float ObjModel::transformColorGray(float grayScale)
{
	// transform color scale to [-1, 1]
	float min = *std::min_element(color->begin(), color->end());
	float max = *std::max_element(color->begin(), color->end());
	float k = (1.0f - (-1.0f)) / (max - min);
	float b = -k * min - 1.0f;

	return k * grayScale + b;
}

