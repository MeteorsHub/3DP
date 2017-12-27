#include "objmodel.h"
#include <QTextStream>
#include <QDebug>
#include <set>

ObjModel::ObjModel()
{
	this->vertices = new vector<vertice>(0);
	this->verticesColor1 = new vector<vertice>(0);
	this->verticesColor2 = new vector<vertice>(0);
	this->faces3 = new vector<face3>(0);
	this->faces3Color1 = new vector<face3>(0);
	this->faces3Color2 = new vector<face3>(0);
	this->color = new vector<float>(0);
	this->color3 = new vector<color3f>(0);
	this->colorMode = ColorFileLoader::ORIGINAL;
}

ObjModel::~ObjModel()
{
	delete this->faces3;
	delete this->faces3Color1;
	delete this->faces3Color2;
	delete this->vertices;
	delete this->verticesColor1;
	delete this->verticesColor2;
	delete this->color;
	delete this->color3;
	this->faces3 = nullptr;
	this->faces3Color1 = nullptr;
	this->faces3Color2 = nullptr;
	this->vertices = nullptr;
	this->verticesColor1 = nullptr;
	this->verticesColor2 = nullptr;
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
	unselect();
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
	unselect();
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

void ObjModel::unselect()
{
	delete this->verticesColor1, this->verticesColor2, this->faces3Color1, this->faces3Color2;
	this->verticesColor1 = new vector<vertice>(0);
	this->verticesColor2 = new vector<vertice>(0);
	this->faces3Color1 = new vector<face3>(0);
	this->faces3Color2 = new vector<face3>(0);
}

void ObjModel::neighborPoP(int pId)
{
	this->unselect();
	this->setColorMode(ColorFileLoader::ORIGINAL);
	this->setColor3f();
	vector<int> neighbors = this->getNeighborPoP(pId);
	this->verticesColor1->push_back(vertices->at(pId));
	for (int i = 0; i < neighbors.size(); i++) {
		this->verticesColor2->push_back(vertices->at(neighbors.at(i)));
	}
}

void ObjModel::neighborFoP(int pId)
{
	this->unselect();
	this->setColorMode(ColorFileLoader::ORIGINAL);
	this->setColor3f();
	vector<int> neighbors = this->getNeighborFoP(pId);
	this->verticesColor1->push_back(vertices->at(pId));
	for (int i = 0; i < neighbors.size(); i++) {
		this->faces3Color2->push_back(faces3->at(neighbors.at(i)));
	}
}

void ObjModel::neighborFoF(int fId)
{
	this->unselect();
	this->setColorMode(ColorFileLoader::ORIGINAL);
	this->setColor3f();
	vector<int> neighbors = this->getNeighborFoF(fId);
	this->faces3Color1->push_back(faces3->at(fId));
	for (int i = 0; i < neighbors.size(); i++) {
		this->faces3Color2->push_back(faces3->at(neighbors.at(i)));
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
	unselect();
	setColor3f();
	file.close();
	return true;
}

int ObjModel::getNumVertices()
{
	if (this->vertices == nullptr)
		return -1;
	return this->vertices->size();
}

int ObjModel::getNumFaces3()
{
	if (this->faces3 == nullptr)
		return -1;
	return this->faces3->size();
}

int ObjModel::getNumColor()
{
	return this->color->size();
}

vector<int> ObjModel::getNeighborPoP(int pId)
{
	std::set<int> pIds;
	for (int i = 0; i < getNumFaces3(); i++) {
		if (isVerticeInFace(pId, i)) {
			face3 face = faces3->at(i);
			pIds.insert(getVerticeId(face.v1));
			pIds.insert(getVerticeId(face.v2));
			pIds.insert(getVerticeId(face.v3));
		}
	}
	pIds.erase(pId);
	vector<int> pIdsv;
	std::copy(pIds.begin(), pIds.end(), std::back_inserter(pIdsv));
	return pIdsv;
}

vector<int> ObjModel::getNeighborFoP(int pId)
{
	std::set<int> fIds;
	for (int i = 0; i < getNumFaces3(); i++) {
		if (isVerticeInFace(pId, i)) {
			fIds.insert(i);
		}
	}
	vector<int> fIdsv;
	std::copy(fIds.begin(), fIds.end(), std::back_inserter(fIdsv));
	return fIdsv;
}

vector<int> ObjModel::getNeighborFoF(int fId)
{
	std::set<int> fIds;
	for (int i = 0; i < getNumFaces3(); i++) {
		if (isTwoFacesColine(fId, i)) {
			fIds.insert(i);
		}
	}
	vector<int> fIdsv;
	std::copy(fIds.begin(), fIds.end(), std::back_inserter(fIdsv));
	return fIdsv;
}

bool ObjModel::isVerticeInFace(int vId, int fId)
{
	face3 face = faces3->at(fId);
	vertice v = vertices->at(vId);
	if (face.v1 == v)
		return true;
	if (face.v2 == v)
		return true;
	if (face.v3 == v)
		return true;
	return false;
}

bool ObjModel::isTwoFacesColine(int fId1, int fId2)
{
	face3 f1 = faces3->at(fId1);
	face3 f2 = faces3->at(fId2);
	int count = 0;
	if (f1.v1 == f2.v1) count++;
	if (f1.v1 == f2.v2) count++;
	if (f1.v1 == f2.v3) count++;
	if (f1.v2 == f2.v1) count++;
	if (f1.v2 == f2.v2) count++;
	if (f1.v2 == f2.v3) count++;
	if (f1.v3 == f2.v1) count++;
	if (f1.v3 == f2.v2) count++;
	if (f1.v3 == f2.v3) count++;
	if (count == 2) return true;
	return false;
}

int ObjModel::getVerticeId(vertice v)
{
	for (int i = 0; i < getNumVertices(); i++) {
		if (vertices->at(i) == v)
			return i;
	}
	return -1;
}

line ObjModel::getNormalLineFromFace(int fId)
{
	face3 face = faces3->at(fId);
	double a, b, c;
	double r;
	vertice vc1, vc2;
	vertice norm0, norm1;
	norm0.x = (face.v1.x + face.v2.x + face.v3.x) / 3;
	norm0.y = (face.v1.y + face.v2.y + face.v3.y) / 3;
	norm0.z = (face.v1.z + face.v2.z + face.v3.z) / 3;
	vc1.x = face.v2.x - face.v1.x;
	vc1.y = face.v2.y - face.v1.y;
	vc1.z = face.v2.z - face.v1.z;
	vc2.x = face.v3.x - face.v1.x;
	vc2.y = face.v3.y - face.v1.y;
	vc2.z = face.v3.z - face.v1.z;
	a = vc1.y*vc2.z - vc2.y*vc1.z;
	b = vc2.x*vc1.z - vc1.x*vc2.z;
	c = vc1.x*vc2.y - vc2.x*vc1.y;
	r = 50 * sqrt(a*a + b * b + c * c);
	norm1.x = a / r + norm0.x;
	norm1.y = b / r + norm0.y;
	norm1.z = c / r + norm0.z;
	line l;
	l.v1 = norm0;
	l.v2 = norm1;
	return l;
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

