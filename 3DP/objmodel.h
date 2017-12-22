#pragma once
#include <vector>
#include <QFile>
#include <QTextStream>
#include "colorfileloader.h"
using std::vector;

struct vertice {
	double x;
	double y;
	double z;
};

struct face3 {
	vertice v1;
	vertice v2;
	vertice v3;
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

	int getNumVertices();
	int getNumFaces3();
	int getNumColor();

	float* getColor3f(float);
	float transformColorGray(float);

	vector<vertice> *vertices;
	vector<face3> *faces3;
	vector<float> *color;
	vector<color3f> *color3;
	ColorFileLoader::COLOR_MODE colorMode;

private:
	
};

