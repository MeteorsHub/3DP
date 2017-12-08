#pragma once
#include <vector>
#include <QFile>
#include <QTextStream>
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

class ObjModel
{
public:
	ObjModel();
	~ObjModel();

	bool loadObjFile(QString);
	bool loadOffFile(QString);
	bool loadColorFile(QString);

	int getNumVertices();
	int getNumFaces3();

	vector<vertice> *vertices;
	vector<face3> *faces3;

private:
	
};

