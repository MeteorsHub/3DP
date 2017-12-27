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

	bool operator==(const vertice &other) const
	{
		if ((abs(x - other.x) < 1e-10) && (abs(y - other.y) < 1e-10) && abs(abs(z - other.z) < 1e-10))
			return true;
		return false;
	}
};

struct face3 {
	vertice v1;
	vertice v2;
	vertice v3;
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

	int getNumVertices();
	int getNumFaces3();
	int getNumColor();
	vector<int> getNeighborPoP(int pId);
	vector<int> getNeighborFoP(int pId);
	vector<int> getNeighborFoF(int fId);
	bool isVerticeInFace(int vId, int fId);
	bool isTwoFacesColine(int fId1, int fId2);
	int getVerticeId(vertice v);
	line getNormalLineFromFace(int fId);

	float* getColor3f(float);
	float transformColorGray(float);

	vector<vertice> *vertices;
	vector<vertice> *verticesColor1;
	vector<vertice> *verticesColor2;
	vector<face3> *faces3;
	vector<face3> *faces3Color1;
	vector<face3> *faces3Color2;
	vector<float> *color;
	vector<color3f> *color3;
	ColorFileLoader::COLOR_MODE colorMode;

private:
	
};

