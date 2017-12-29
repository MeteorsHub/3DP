#include "objmodel.h"
#include <QTextStream>
#include <QDebug>
#include <set>
#include <random>

ObjModel::ObjModel()
{
	this->vertices = new vector<vertice>(0);
	this->verticesColor1 = new vector<vertice>(0);
	this->verticesColor2 = new vector<vertice>(0);
	this->verticesNoise = new vector<vertice>(0);
	this->verticesDenoise = new vector<vertice>(0);
	this->faces3 = new vector<face3>(0);
	this->faces3Color1 = new vector<face3>(0);
	this->faces3Color2 = new vector<face3>(0);
	this->faces3Noise = new vector<face3>(0);
	this->faces3Denoise = new vector<face3>(0);
	this->faces3id = new vector<face3id>(0);
	this->color = new vector<float>(0);
	this->color3 = new vector<color3f>(0);
	this->mseColor3 = new vector<color3f>(0);
	this->colorMode = ColorFileLoader::ORIGINAL;
}

ObjModel::~ObjModel()
{
	delete this->faces3;
	delete this->faces3Color1;
	delete this->faces3Color2;
	delete this->faces3Noise;
	delete this->faces3Denoise;
	delete this->vertices;
	delete this->verticesColor1;
	delete this->verticesColor2;
	delete this->color;
	delete this->color3;
	this->faces3 = nullptr;
	this->faces3Color1 = nullptr;
	this->faces3Color2 = nullptr;
	this->faces3Noise = nullptr;
	this->faces3Denoise = nullptr;
	this->vertices = nullptr;
	this->verticesColor1 = nullptr;
	this->verticesColor2 = nullptr;
	this->color = nullptr;
	this->color3 = nullptr;
}


bool ObjModel::loadObjFile(QString filename) {
	QFile file(filename);
	unselect();
	clearNoise();
	

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		file.close();
		return false;
	}
	if (getNumVertices() != 0) {
		delete vertices, faces3, faces3id;
		this->vertices = new vector<vertice>(0);
		this->faces3 = new vector<face3>(0);
		this->faces3id = new vector<face3id>(0);
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
			face3id f3id;
			f3.v1 = this->vertices->at(list[1].toInt() - 1);
			f3id.vId1 = list[1].toInt() - 1;
			f3.v2 = this->vertices->at(list[2].toInt() - 1);
			f3id.vId2 = list[2].toInt() - 1;
			f3.v3 = this->vertices->at(list[3].toInt() - 1);
			f3id.vId3 = list[3].toInt() - 1;
			this->faces3id->push_back(f3id);
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
	unselect();
	clearNoise();
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
			float *c = getColor3f(1.0f, ColorFileLoader::ORIGINAL);
			color3f cf = { c[0], c[1], c[2] };
			color3->push_back(cf);
		}
	}
	else {
		color3->clear();
		// transform color scale to [-1, 1]
		float min = *std::min_element(color->begin(), color->end());
		float max = *std::max_element(color->begin(), color->end());
		float k = (1.0f - (-1.0f)) / (max - min);
		float b = -k * min - 1.0f;
		for (int i = 0; i < getNumColor(); i++) {
			double grayscale;
			if (this->colorMode == ColorFileLoader::CONTINUOUS)
				grayscale = color->at(i);
			else
				grayscale = std::roundf(color->at(i));
			grayscale = k * (grayscale) + b;
			float *c = getColor3f(grayscale, this->colorMode);
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

void ObjModel::regionFromPoints(vector<int> pIds, bool strict)
{
	this->unselect();
	for (int i = 0; i < getNumFaces3(); i++) {
		int id1 = getVerticeId(faces3->at(i).v1);
		int id2 = getVerticeId(faces3->at(i).v2);
		int id3 = getVerticeId(faces3->at(i).v3);
		vertice v3 = faces3->at(i).v3;
		int count = 0;
		if (std::find(pIds.begin(), pIds.end(), id1) != pIds.end())
			count++;
		if (std::find(pIds.begin(), pIds.end(), id2) != pIds.end())
			count++;
		if (std::find(pIds.begin(), pIds.end(), id3) != pIds.end())
			count++;
		if (strict && count == 3)
			faces3Color1->push_back(faces3->at(i));
		if (!strict && count >= 2)
			faces3Color1->push_back(faces3->at(i));
	}
}

void ObjModel::addNoise(double deviation)
{
	this->clearNoise();
	std::default_random_engine g;
	std::normal_distribution<double> d(0.0, deviation);
	for (int i = 0; i < getNumVertices(); i++) {
		verticesNoise->push_back(noiseVertice(i, d(g), d(g), d(g)));
	}
	for (int i = 0; i < faces3id->size(); i++) {
		face3 f;
		vertice v;
		f.v1 = verticesNoise->at(faces3id->at(i).vId1);
		f.v2 = verticesNoise->at(faces3id->at(i).vId2);
		f.v3 = verticesNoise->at(faces3id->at(i).vId3);
		faces3Noise->push_back(f);
	}
}

void ObjModel::deNoise(double sigma)
{
	delete faces3Denoise, verticesDenoise;
	faces3Denoise = new vector<face3>(0);
	verticesDenoise = new vector<vertice>(0);
	if (faces3Noise->size() == 0)
		return;
	// compute normal lines
	vector<std::set<int>> neighborFaceids(getNumVertices());
	vector<std::set<int>> neighborVerticeids(getNumVertices());
	for (int i = 0; i < getNumFaces3(); i++) {
		face3id f3id = faces3id->at(i);
		neighborFaceids[f3id.vId1].insert(i);
		neighborFaceids[f3id.vId2].insert(i);
		neighborFaceids[f3id.vId3].insert(i);
		neighborVerticeids[f3id.vId1].insert(f3id.vId2);
		neighborVerticeids[f3id.vId1].insert(f3id.vId3);
		neighborVerticeids[f3id.vId2].insert(f3id.vId1);
		neighborVerticeids[f3id.vId2].insert(f3id.vId3);
		neighborVerticeids[f3id.vId3].insert(f3id.vId1);
		neighborVerticeids[f3id.vId3].insert(f3id.vId2);
	}
	
	for (int i = 0; i < neighborFaceids.size(); i++) {
		vertice n(0, 0, 0);
		for (std::set<int>::iterator j = neighborFaceids[i].begin(); j != neighborFaceids[i].end();j++) {
			int fid = *j;
			line norm = getNormalLineFromFace(fid, true);
			n = n + (norm.v2 - norm.v1);
		}
		n = n.normal();
		// denoising
		double sigma_c = sigma;
		double sigma_s = sigma;
		vertice v = verticesNoise->at(i);
		vector<int> qIds;
		std::copy(neighborVerticeids[i].begin(), neighborVerticeids[i].end(), std::back_inserter(qIds));
		vector<vertice> qs(0);
		for (int j = 0; j < qIds.size(); j++)
			qs.push_back(verticesNoise->at(qIds[j]));
		double sum = 0.0;
		double normalizer = 0.0;
		for (int j = 0; j < qs.size(); j++) {
			double t = (v - qs[j]).mod();
			double h = n.dotProduct(v - qs[j]);
			double wc = exp(-t * t / (2 * (sigma_c*sigma_c)));
			double ws = exp(-h * h / (2 * (sigma_s*sigma_s)));
			sum += wc * ws * h;
			normalizer += wc * ws;
		}
		vertice blend = n * (sum / normalizer);
		vertice v_ = v - blend;
		verticesDenoise->push_back(v_);
		
	}
	for (int i = 0; i < faces3id->size(); i++) {
		face3 f;
		vertice v;
		f.v1 = verticesDenoise->at(faces3id->at(i).vId1);
		f.v2 = verticesDenoise->at(faces3id->at(i).vId2);
		f.v3 = verticesDenoise->at(faces3id->at(i).vId3);
		faces3Denoise->push_back(f);
	}
}

double ObjModel::computeMSE()
{
	delete mseColor3;
	mseColor3 = new vector<color3f>(0);
	if (verticesNoise->size() == 0 || verticesDenoise->size() == 0)
		return 0;
	vector<double> delta(getNumVertices());
	for (int i = 0; i < getNumVertices(); i++) {
		delta[i] = pow((vertices->at(i) - verticesDenoise->at(i)).mod(), 2);
	}
	
	double sum = 0.0;
	for (int i = 0; i < delta.size(); i++) {
		sum += delta[i];
	}
	// compute mean delta of a face
	vector<double> deltaFace(getNumFaces3());
	for (int i = 0; i < getNumFaces3(); i++) {
		face3id f = faces3id->at(i);
		double deltaMean = 0;
		deltaMean += delta[f.vId1];
		deltaMean += delta[f.vId2];
		deltaMean += delta[f.vId3];
		deltaFace[i] = deltaMean;
	}
	double maxe = *std::max_element(deltaFace.begin(), deltaFace.end());
	for (int i = 0; i < deltaFace.size(); i++) {
		float* color = getColor3f(2 * (deltaFace[i] / maxe) - 1.0, ColorFileLoader::CONTINUOUS);
		color3f c;
		c.red = color[0]; c.green = color[1]; c.blue = color[2];
		mseColor3->push_back(c);
	}
	return sum / getNumVertices();
}

void ObjModel::clearNoise()
{
	delete faces3Noise, faces3Denoise, verticesNoise, verticesDenoise, mseColor3;
	faces3Noise = new vector<face3>(0);
	faces3Denoise = new vector<face3>(0);
	verticesNoise = new vector<vertice>(0);
	verticesDenoise = new vector<vertice>(0);
	mseColor3 = new vector<color3f>(0);
}

bool ObjModel::loadOffFile(QString filename)
{
	unselect();
	clearNoise();
	QFile file(filename);

	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		file.close();
		return false;
	}

	if (getNumVertices() != 0) {
		delete vertices, faces3, faces3id;
		this->vertices = new vector<vertice>(0);
		this->faces3 = new vector<face3>(0);
		this->faces3id = new vector<face3id>(0);
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
		face3id f3id;
		f3.v1 = this->vertices->at(list[1].toInt());
		f3id.vId1 = list[1].toInt();
		f3.v2 = this->vertices->at(list[2].toInt());
		f3id.vId2 = list[2].toInt();
		f3.v3 = this->vertices->at(list[3].toInt());
		f3id.vId3 = list[3].toInt();
		this->faces3->push_back(f3);
		this->faces3id->push_back(f3id);
	}
	
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
			face3id fids = faces3id->at(i);
			pIds.insert(fids.vId1);
			pIds.insert(fids.vId2);
			pIds.insert(fids.vId3);
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
	face3id f3id = faces3id->at(fId);
	if (f3id.vId1 == vId)
		return true;
	if (f3id.vId2 == vId)
		return true;
	if (f3id.vId3 == vId)
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

line ObjModel::getNormalLineFromFace(int fId, bool isNoise)
{
	face3 face;
	if (isNoise && faces3Noise->size() != 0)
		face = faces3Noise->at(fId);
	else
		face = faces3->at(fId);
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
	r = sqrt(a*a + b * b + c * c);
	norm1.x = a / r + norm0.x;
	norm1.y = b / r + norm0.y;
	norm1.z = c / r + norm0.z;
	line l;
	l.v1 = norm0;
	l.v2 = norm1;
	return l;
}

line ObjModel::getNormalLineFromVertice(int vId, bool isNoise)
{
	vector<int> neighbor = getNeighborFoP(vId);
	vertice sum(0, 0, 0);
	for (int i = 0; i < neighbor.size(); i++) {
		line norm = getNormalLineFromFace(neighbor.at(i), isNoise);
		sum = sum + (norm.v2 - norm.v1);
	}
	line l;
	if (isNoise)
		l.v1 = verticesNoise->at(vId);
	else
		l.v1 = vertices->at(vId);
	l.v2 = l.v1 + sum/double(neighbor.size());
	return l;
}

vertice ObjModel::noiseVertice(int vId, double b1, double b2, double b3)
{
	vertice v;
	v.x = vertices->at(vId).x + b1;
	v.y = vertices->at(vId).y + b2;
	v.z = vertices->at(vId).z + b3;
	return v;
}

vertice ObjModel::denoiseVertice(int vId, vertice n)
{
	double sigma_c = 0.05;
	double sigma_s = 0.05;
	vertice v = verticesNoise->at(vId);
	vector<int> qIds = getNeighborPoP(vId);
	vector<vertice> qs(0);
	for (int i = 0; i < qIds.size(); i++) 
		qs.push_back(verticesNoise->at(qIds[i]));
	double sum = 0.0;
	double normalizer = 0.0;
	for (int i = 0; i < qs.size(); i++) {
		double t = (v - qs[i]).mod();
		double h = n.dotProduct(v - qs[i]);
		double wc = exp(-t * t / (2 * (sigma_c*sigma_c)));
		double ws = exp(-h * h / (2 * (sigma_s*sigma_s)));
		sum += wc * ws * h;
		normalizer += wc * ws;
	}
	vertice blend = n * (sum / normalizer);
	vertice v_ = v - blend;
	return v_;
}

float * ObjModel::getColor3f(float grayScale, ColorFileLoader::COLOR_MODE colorMode)
{
	// grayscale is [-1, 1]
	float* color3f = new float[3];
	if (grayScale > 1.0f) grayScale = 1.0f;
	if (grayScale < -1.0f) grayScale = -1.0f;
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

	switch (colorMode)
	{
	case ColorFileLoader::ORIGINAL:
		color3f[0] = 0.1;
		color3f[1] = 0.7;
		color3f[2] = 0.1;
		return color3f;
	case ColorFileLoader::CONTINUOUS:
		color3f[0] = red(grayScale);
		color3f[1] = green(grayScale);
		color3f[2] = blue(grayScale);
		return color3f;
	case ColorFileLoader::DISCRETE:
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
