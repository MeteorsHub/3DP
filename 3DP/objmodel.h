#pragma once
#include <vector>
#include <cmath>
#include <QFile>
#include <QTextStream>
#include "colorfileloader.h"
using std::vector;

struct vertice {
	double x;
	double y;
	double z;
	vertice() {
		this->x = 0; this->y = 0; this->z = 0;
	}
	vertice(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	bool operator==(const vertice &other) const
	{
		if ((abs(x - other.x) < 1e-10) && (abs(y - other.y) < 1e-10) && abs(abs(z - other.z) < 1e-10))
			return true;
		return false;
	}

	double mod() {
		return sqrt(x*x + y * y + z * z);
	}

	vertice normal() {
		double length = this->mod();
		return vertice(x / length, y / length, z / length);
	}

	double dotProduct(const vertice &other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	vertice operator-(const vertice &other) const
	{
		return vertice(this->x - other.x, this->y - other.y, this->z - other.z);
	}
	vertice operator+(const vertice &other) const
	{
		return vertice(this->x + other.x, this->y + other.y, this->z + other.z);
	}
	vertice operator*(const double k) const {
		return vertice(x * k, y * k, z * k);
	}
	vertice operator/(const double k) const {
		return vertice(x / k, y / k, z / k);
	}
};

struct face3 {
	vertice v1;
	vertice v2;
	vertice v3;
};

struct face3id {
	int vId1;
	int vId2;
	int vId3;
};


struct line{
	vertice v1;
	vertice v2;
};

struct color3f {
	float red;
	float green;
	float blue;
};

class ObjModel
{
public:
	ObjModel();
	~ObjModel();

	bool loadObjFile(QString);
	bool loadOffFile(QString);
	bool loadColorFile(QString);
	bool setColorMode(ColorFileLoader::COLOR_MODE);
	void setColor3f();

	void unselect();
	void neighborPoP(int pId);
	void neighborFoP(int pId);
	void neighborFoF(int fId);
	void regionFromPoints(vector<int> pIds, bool strict=true);
	void addNoise(double deviation);
	void deNoise(double sigma);
	double computeMSE();
	void clearNoise();

	int getNumVertices();
	int getNumFaces3();
	int getNumColor();
	vector<int> getNeighborPoP(int pId);
	vector<int> getNeighborFoP(int pId);
	vector<int> getNeighborFoF(int fId);
	bool isVerticeInFace(int vId, int fId);
	bool isTwoFacesColine(int fId1, int fId2);
	int getVerticeId(vertice v);
	line getNormalLineFromFace(int fId, bool isNoise=false);
	line getNormalLineFromVertice(int vId, bool isNoise=false);
	vertice noiseVertice(int vId, double b1, double b2, double b3);
	vertice denoiseVertice(int vId, vertice n);

	float* getColor3f(float, ColorFileLoader::COLOR_MODE);

	vector<vertice> *vertices;
	vector<vertice> *verticesColor1;
	vector<vertice> *verticesColor2;
	vector<vertice> *verticesNoise;
	vector<vertice> *verticesDenoise;
	vector<face3> *faces3;
	vector<face3id> *faces3id;
	vector<face3> *faces3Color1;
	vector<face3> *faces3Color2;
	vector<face3> *faces3Noise;
	vector<face3> *faces3Denoise;
	vector<float> *color;
	vector<color3f> *color3;
	vector<color3f> *mseColor3;
	ColorFileLoader::COLOR_MODE colorMode;

private:
	
};

